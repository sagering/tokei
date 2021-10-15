#include "pokei.h"

#include "common.h"

#define VOLK_IMPLEMENTATION
#include <volk/volk.h>
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#include "allocators.h"
#include "resources.h"

struct DeviceInternal;

struct QueueInternal
{
  DeviceInternal* device = nullptr;
  VkQueue queue = VK_NULL_HANDLE;
  uint32_t queueFamilyIdx = VK_QUEUE_FAMILY_IGNORED;

  uint64_t seqNr = 0;
  std::deque<std::pair<VkFence, uint64_t>> fences;
};

struct Descriptor
{
  VkDescriptorBufferInfo bufferInfo = {};
  uint32_t dynamicOffset = 0;
  VkDescriptorImageInfo imageInfo = {};
};

struct Set
{
  Descriptor bindings[8] = {};
  VkDescriptorSet set = VK_NULL_HANDLE;
  bool dirty = false;
  bool dynamicOffsetsDirty = false;
};

struct CmdBufferInternal
{
  QueueInternal* queue = nullptr;
  VkCommandBuffer cmdBuffer = VK_NULL_HANDLE;
  VkRenderPass renderPass = VK_NULL_HANDLE;
  uint32_t subpass = 0;
  VkPipelineLayout vkPipelineLayout = VK_NULL_HANDLE;
  PipelineLayout pipelineLayout = {};
  Set sets[8] = {};
};

struct DeviceInternal
{
  VkInstance instance = VK_NULL_HANDLE;
#ifdef _DEBUG
  VkDebugReportCallbackEXT callback;
#endif
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  VmaAllocator vmaAllocator = VK_NULL_HANDLE;

  QueueInternal queues[3] = {};

  uint32_t graphicsQueueIdx = 0;
  uint32_t transferQueueIdx = 0;
  uint32_t computeQueueIdx = 0;

  uint64_t frame = 0;

  DescriptorSetAllocator dsetAllocator = {};
  CommandBufferAllocator cmdBufferAllocator = {};
  FenceAllocator fenceAllocator = {};
  SemaphoreAllocator semaphoreAllocator = {};

  Shared shared = {};

  // released resources waiting for their frame to be finished
  std::deque<std::pair<Buffer, uint64_t>> buffers = {};
  std::deque<std::pair<Texture, uint64_t>> textures = {};
  std::deque<std::pair<Swapchain, uint64_t>> swapchains = {};
};

struct SwapchainInternal
{
  VkSwapchainKHR swapchain = VK_NULL_HANDLE;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  Texture textures[8] = {};
  uint32_t textureCnt = 0;
  uint32_t nextTextureIdx = 0;
};

struct BufferInternal
{
  BufferCreateInfo desc = {};
  VkDeviceSize size = 0;
  VmaAllocation allocation = VK_NULL_HANDLE;
  VkBuffer buffer = VK_NULL_HANDLE;
};

struct TextureInternal
{
  TextureCreateInfo desc = {};
  VkDeviceSize size = 0;
  VmaAllocation allocation = VK_NULL_HANDLE;
  VkImage image = VK_NULL_HANDLE;
  VkImageView view = VK_NULL_HANDLE;
  VkImageSubresourceRange subresource = {};
};

static VkBool32 VKAPI_CALL
debugReportCallback(VkDebugReportFlagsEXT flags,
                    VkDebugReportObjectTypeEXT objectType,
                    uint64_t object,
                    size_t location,
                    int32_t messageCode,
                    const char* pLayerPrefix,
                    const char* pMessage,
                    void* pUserData)
{
  const char* type = (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)     ? "ERROR"
                     : (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) ? "WARNING"
                                                                 : "INFO";

  char message[4096];
  snprintf(message, 4096, "%s: %s\n", type, pMessage);

  printf("%s", message);

#ifdef _WIN32
  OutputDebugStringA(message);
#endif

  if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
    assert(!"Validation error encountered!");

  return VK_FALSE;
}

inline VkBlendFactor
GetVkBlendFactor(BlendFactor blendFactor)
{
  switch (blendFactor) {
    case BlendFactor::ZERO:
      return VK_BLEND_FACTOR_ZERO;
    case BlendFactor::ONE:
      return VK_BLEND_FACTOR_ONE;
    case BlendFactor::SRC0_COLOR:
      return VK_BLEND_FACTOR_SRC_COLOR;
    case BlendFactor::ONE_MINUS_SRC0_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
    case BlendFactor::DST_COLOR:
      return VK_BLEND_FACTOR_DST_COLOR;
    case BlendFactor::ONE_MINUS_DST_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
    case BlendFactor::SRC0_ALPHA:
      return VK_BLEND_FACTOR_SRC_ALPHA;
    case BlendFactor::ONE_MINUS_SRC0_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    case BlendFactor::DST_ALPHA:
      return VK_BLEND_FACTOR_DST_ALPHA;
    case BlendFactor::ONE_MINUS_DST_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
    case BlendFactor::CONSTANT_COLOR:
      return VK_BLEND_FACTOR_CONSTANT_COLOR;
    case BlendFactor::ONE_MINUS_CONSTANT_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
    case BlendFactor::CONSTANT_ALPHA:
      return VK_BLEND_FACTOR_CONSTANT_ALPHA;
    case BlendFactor::ONE_MINUS_CONSTANT_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
    case BlendFactor::SRC0_ALPHA_SATURATE:
      return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
    case BlendFactor::SRC1_COLOR:
      return VK_BLEND_FACTOR_SRC1_COLOR;
    case BlendFactor::ONE_MINUS_SRC1_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
    case BlendFactor::SRC1_ALPHA:
      return VK_BLEND_FACTOR_SRC1_ALPHA;
    case BlendFactor::ONE_MINUS_SRC1_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
    default:
      return VK_BLEND_FACTOR_ONE;
  }
}

inline VkVertexInputRate
GetVkVertexInputRate(VertexInputRate inputRate)
{
  switch (inputRate) {
    case VertexInputRate::VERTEX:
      return VK_VERTEX_INPUT_RATE_VERTEX;
    case VertexInputRate::INSTANCE:
      return VK_VERTEX_INPUT_RATE_INSTANCE;
    default:
      return VK_VERTEX_INPUT_RATE_VERTEX;
  }
}

inline VkFormat
GetVkFormat(VertexFormat format)
{
  switch (format) {
    case VertexFormat::UCHAR:
      return VK_FORMAT_R8_UINT;
    case VertexFormat::UCHAR2:
      return VK_FORMAT_R8G8_UINT;
    case VertexFormat::UCHAR3:
      return VK_FORMAT_R8G8B8_UINT;
    case VertexFormat::UCHAR4:
      return VK_FORMAT_R8G8B8A8_UINT;
    case VertexFormat::CHAR:
      return VK_FORMAT_R8_SINT;
    case VertexFormat::CHAR2:
      return VK_FORMAT_R8G8_SINT;
    case VertexFormat::CHAR3:
      return VK_FORMAT_R8G8B8_SINT;
    case VertexFormat::CHAR4:
      return VK_FORMAT_R8G8B8A8_SINT;
    case VertexFormat::UCHAR_N:
      return VK_FORMAT_R8_UNORM;
    case VertexFormat::UCHAR2_N:
      return VK_FORMAT_R8G8_UNORM;
    case VertexFormat::UCHAR3_N:
      return VK_FORMAT_R8G8B8_UNORM;
    case VertexFormat::UCHAR4_N:
      return VK_FORMAT_R8G8B8A8_UNORM;
    case VertexFormat::CHAR_N:
      return VK_FORMAT_R8_SNORM;
    case VertexFormat::CHAR2_N:
      return VK_FORMAT_R8G8_SNORM;
    case VertexFormat::CHAR3_N:
      return VK_FORMAT_R8G8B8_SNORM;
    case VertexFormat::CHAR4_N:
      return VK_FORMAT_R8G8B8A8_SNORM;
    case VertexFormat::USHORT:
      return VK_FORMAT_R16_UINT;
    case VertexFormat::USHORT2:
      return VK_FORMAT_R16G16_UINT;
    case VertexFormat::USHORT3:
      return VK_FORMAT_R16G16B16_UINT;
    case VertexFormat::USHORT4:
      return VK_FORMAT_R16G16B16A16_UINT;
    case VertexFormat::SHORT:
      return VK_FORMAT_R16_SINT;
    case VertexFormat::SHORT2:
      return VK_FORMAT_R16G16_SINT;
    case VertexFormat::SHORT3:
      return VK_FORMAT_R16G16B16_SINT;
    case VertexFormat::SHORT4:
      return VK_FORMAT_R16G16B16A16_SINT;
    case VertexFormat::USHORT_N:
      return VK_FORMAT_R16_UNORM;
    case VertexFormat::USHORT2_N:
      return VK_FORMAT_R16G16_UNORM;
    case VertexFormat::USHORT3_N:
      return VK_FORMAT_R16G16B16_UNORM;
    case VertexFormat::USHORT4_N:
      return VK_FORMAT_R16G16B16A16_UNORM;
    case VertexFormat::SHORT_N:
      return VK_FORMAT_R16_SNORM;
    case VertexFormat::SHORT2_N:
      return VK_FORMAT_R16G16_SNORM;
    case VertexFormat::SHORT3_N:
      return VK_FORMAT_R16G16B16_SNORM;
    case VertexFormat::SHORT4_N:
      return VK_FORMAT_R16G16B16A16_SNORM;
    case VertexFormat::UINT:
      return VK_FORMAT_R32_UINT;
    case VertexFormat::UINT2:
      return VK_FORMAT_R32G32_UINT;
    case VertexFormat::UINT3:
      return VK_FORMAT_R32G32B32_UINT;
    case VertexFormat::UINT4:
      return VK_FORMAT_R32G32B32A32_UINT;
    case VertexFormat::INT:
      return VK_FORMAT_R32_SINT;
    case VertexFormat::INT2:
      return VK_FORMAT_R32G32_SINT;
    case VertexFormat::INT3:
      return VK_FORMAT_R32G32B32_SINT;
    case VertexFormat::INT4:
      return VK_FORMAT_R32G32B32A32_SINT;
    case VertexFormat::HALF:
      return VK_FORMAT_R16_SFLOAT;
    case VertexFormat::HALF2:
      return VK_FORMAT_R16G16_SFLOAT;
    case VertexFormat::HALF3:
      return VK_FORMAT_R16G16B16_SFLOAT;
    case VertexFormat::HALF4:
      return VK_FORMAT_R16G16B16A16_SFLOAT;
    case VertexFormat::FLOAT:
      return VK_FORMAT_R32_SFLOAT;
    case VertexFormat::FLOAT2:
      return VK_FORMAT_R32G32_SFLOAT;
    case VertexFormat::FLOAT3:
      return VK_FORMAT_R32G32B32_SFLOAT;
    case VertexFormat::FLOAT4:
      return VK_FORMAT_R32G32B32A32_SFLOAT;
    default:
      return VK_FORMAT_R32G32B32A32_SFLOAT;
  }
}

inline VkFormat
GetVkFormat(PixelFormat pixelFormat)
{
  switch (pixelFormat) {
    case A8_UNORM: // fallthrough
    case R8_UNORM:
      return VK_FORMAT_R8_UNORM;
    case R8_UNORM_SRGB:
      return VK_FORMAT_R8_SRGB;
    case R8_SNORM:
      return VK_FORMAT_R8_SNORM;
    case R8_UINT:
      return VK_FORMAT_R8_UINT;
    case R8_SINT:
      return VK_FORMAT_R8_SINT;
    case R16_UNORM:
      return VK_FORMAT_R16_UNORM;
    case R16_SNORM:
      return VK_FORMAT_R16_SNORM;
    case R16_UINT:
      return VK_FORMAT_R16_UINT;
    case R16_SINT:
      return VK_FORMAT_R16_SINT;
    case R16_FLOAT:
      return VK_FORMAT_R16_SFLOAT;
    case RG8_UNORM:
      return VK_FORMAT_R8G8_UNORM;
    case RG8_UNORM_SRGB:
      return VK_FORMAT_R8G8_SRGB;
    case RG8_SNORM:
      return VK_FORMAT_R8G8_SNORM;
    case RG8_UINT:
      return VK_FORMAT_R8G8_UINT;
    case RG8_SINT:
      return VK_FORMAT_R8G8_SINT;
    case B5G6R5_UNORM:
      return VK_FORMAT_B5G6R5_UNORM_PACK16;
    case A1BGR5_UNORM:
      return VK_FORMAT_A1R5G5B5_UNORM_PACK16;
      // case ABGR4_UNORM:
      //	break;
    case BGR5A1_UNORM:
      return VK_FORMAT_B5G5R5A1_UNORM_PACK16;
    case R32_UINT:
      return VK_FORMAT_R32_UINT;
    case R32_SINT:
      return VK_FORMAT_R32_SINT;
    case R32_FLOAT:
      return VK_FORMAT_R32_SFLOAT;
    case RG16_UNORM:
      return VK_FORMAT_R16G16_UNORM;
    case RG16_SNORM:
      return VK_FORMAT_R16G16_SNORM;
    case RG16_UINT:
      return VK_FORMAT_R16G16_UINT;
    case RG16_SINT:
      return VK_FORMAT_R16G16_SINT;
    case RG16_FLOAT:
      return VK_FORMAT_R16G16_SFLOAT;
    case RGBA8_UNORM:
      return VK_FORMAT_R8G8B8A8_UNORM;
    case RGBA8_UNORM_SRGB:
      return VK_FORMAT_R8G8B8A8_SRGB;
    case RGBA8_SNORM:
      return VK_FORMAT_R8G8B8A8_SNORM;
    case RGBA8_UINT:
      return VK_FORMAT_R8G8B8A8_UINT;
    case RGBA8_SINT:
      return VK_FORMAT_R8G8B8A8_SINT;
    case BGRA8_UNORM:
      return VK_FORMAT_B8G8R8A8_UNORM;
    case BGRA8_UNORM_SRGB:
      return VK_FORMAT_B8G8R8A8_SRGB;
    case D16_UNORM:
      return VK_FORMAT_D16_UNORM;
    case D32_FLOAT:
      return VK_FORMAT_D32_SFLOAT;
    case D24S8_UNORM_UINT:
      return VK_FORMAT_D24_UNORM_S8_UINT;
    case S8_UINT:
      return VK_FORMAT_S8_UINT;
    default:
      return VK_FORMAT_UNDEFINED;
  }
}

inline VkPrimitiveTopology
GetVkPrimitiveTopology(PrimitiveTopology topo)
{
  switch (topo) {
    case PrimitiveTopology::POINT_LIST:
      return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case PrimitiveTopology::LINE_LIST:
      return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case PrimitiveTopology::LINE_STRIP:
      return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case PrimitiveTopology::TRIANGLE_LIST:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case PrimitiveTopology::TRIANGLE_STRIP:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    case PrimitiveTopology::TRIANGLE_FAN:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
    case PrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
    case PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
    case PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
    case PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
    case PrimitiveTopology::PATCH_LIST:
      return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
    default:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  }
}

inline VkPolygonMode
GetVkPolygonMode(PolygonMode mode)
{
  switch (mode) {
    case PolygonMode::FILL:
      return VK_POLYGON_MODE_FILL;
    case PolygonMode::LINE:
      return VK_POLYGON_MODE_LINE;
    case PolygonMode::POINT:
      return VK_POLYGON_MODE_POINT;
    default:
      return VK_POLYGON_MODE_FILL;
  }
}

inline VkCullModeFlags
GetVkCullModeFlags(CullMode mode)
{
  switch (mode) {
    case CullMode::NONE:
      return 0;
    case CullMode::FRONT:
      return VK_CULL_MODE_FRONT_BIT;
    case CullMode::BACK:
      return VK_CULL_MODE_BACK_BIT;
    case CullMode::FRONT_AND_BACK:
      return VK_CULL_MODE_FRONT_BIT | VK_CULL_MODE_BACK_BIT;
    default:
      return 0;
  }
}

inline VkFrontFace
GetVkFrontFace(FrontFace face)
{
  switch (face) {
    case FrontFace::COUNTER_CLOCKWISE:
      return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    case FrontFace::CLOCKWISE:
      return VK_FRONT_FACE_CLOCKWISE;
    default:
      return VK_FRONT_FACE_CLOCKWISE;
  }
}

inline VkCompareOp
GetVkCompareOp(CompareOp op)
{
  switch (op) {
    case CompareOp::NEVER:
      return VK_COMPARE_OP_NEVER;
    case CompareOp::LESS:
      return VK_COMPARE_OP_LESS;
    case CompareOp::EQUAL:
      return VK_COMPARE_OP_EQUAL;
    case CompareOp::LESS_OR_EQUAL:
      return VK_COMPARE_OP_LESS_OR_EQUAL;
    case CompareOp::GREATER:
      return VK_COMPARE_OP_GREATER;
    case CompareOp::NOT_EQUAL:
      return VK_COMPARE_OP_NOT_EQUAL;
    case CompareOp::GREATER_OR_EQUAL:
      return VK_COMPARE_OP_LESS_OR_EQUAL;
    case CompareOp::ALWAYS:
      return VK_COMPARE_OP_ALWAYS;
    default:
      return VK_COMPARE_OP_NEVER;
  }
}

inline VkStencilOp
GetVkStencilOp(StencilOp op)
{
  switch (op) {
    case StencilOp::KEEP:
      return VK_STENCIL_OP_KEEP;
    case StencilOp::ZERO:
      return VK_STENCIL_OP_ZERO;
    case StencilOp::REPLACE:
      return VK_STENCIL_OP_REPLACE;
    case StencilOp::INCREMENT_AND_CLAMP:
      return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
    case StencilOp::DECREMENT_AND_CLAMP:
      return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
    case StencilOp::INVERT:
      return VK_STENCIL_OP_INVERT;
    case StencilOp::INCREMENT_AND_WRAP:
      return VK_STENCIL_OP_INCREMENT_AND_WRAP;
    case StencilOp::DECREMENT_AND_WRAP:
      return VK_STENCIL_OP_DECREMENT_AND_WRAP;
    default:
      return VK_STENCIL_OP_KEEP;
  }
}

inline VkAttachmentLoadOp
GetVkAttachmentLoadOp(LoadOp op)
{
  switch (op) {
    case LoadOp::CLEAR:
      return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case LoadOp::LOAD:
      return VK_ATTACHMENT_LOAD_OP_LOAD;
    default:
      return VK_ATTACHMENT_LOAD_OP_CLEAR;
  }
}

inline VkAttachmentStoreOp
GetVkAttachmentStoreOp(StoreOp op)
{
  switch (op) {
    case StoreOp::DONT_CARE:
      return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    case StoreOp::STORE:
      return VK_ATTACHMENT_STORE_OP_STORE;
    default:
      return VK_ATTACHMENT_STORE_OP_STORE;
  }
}

inline VkStencilOpState
GetVkStencilOpState(PipelineState::DepthStencilState::FaceState in)
{
  VkStencilOpState out = {};
  out.compareMask = in.compareMask;
  out.compareOp = GetVkCompareOp(in.compareOp);
  out.depthFailOp = GetVkStencilOp(in.depthFailOp);
  out.failOp = GetVkStencilOp(in.failOp);
  out.passOp = GetVkStencilOp(in.passOp);
  out.reference = in.reference;
  out.writeMask = in.writeMask;

  return out;
}

inline VkSampleCountFlagBits
GetVkSampleCountFlagBits(uint32_t samples)
{
  switch (samples) {
    case 1:
    default:
      return VK_SAMPLE_COUNT_1_BIT;
    case 2:
      return VK_SAMPLE_COUNT_2_BIT;
    case 4:
      return VK_SAMPLE_COUNT_4_BIT;
    case 8:
      return VK_SAMPLE_COUNT_8_BIT;
    case 16:
      return VK_SAMPLE_COUNT_16_BIT;
    case 32:
      return VK_SAMPLE_COUNT_32_BIT;
  }
}

inline VkImageAspectFlags
GetImageAspectFlags(VkFormat format)
{
  VkImageAspectFlags flags = 0;
  switch (format) {
    case VK_FORMAT_D16_UNORM:           // fallthrough
    case VK_FORMAT_X8_D24_UNORM_PACK32: // fallthrough
    case VK_FORMAT_D32_SFLOAT:          // fallthrough
      flags = VK_IMAGE_ASPECT_DEPTH_BIT;
      break;
    case VK_FORMAT_S8_UINT:
      flags = VK_IMAGE_ASPECT_STENCIL_BIT;
      break;
    case VK_FORMAT_D16_UNORM_S8_UINT: // fallthrough
    case VK_FORMAT_D24_UNORM_S8_UINT: // fallthrough
    case VK_FORMAT_D32_SFLOAT_S8_UINT:
      flags = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
      break;
    default:
      flags = VK_IMAGE_ASPECT_COLOR_BIT;
      break;
  }
  return flags;
}

struct PhysicalDevice
{
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  uint32_t graphicQueueFamilyIdx = VK_QUEUE_FAMILY_IGNORED;
  uint32_t computeQueueFamilyIdx = VK_QUEUE_FAMILY_IGNORED;
  uint32_t transferQueueFamilyIdx = VK_QUEUE_FAMILY_IGNORED;
};

bool
selectDevice(VkInstance instance, PhysicalDevice* out)
{
  uint8_t const maxNumPhysicalDevices = 16;
  uint8_t const maxNumQueueFamilies = 16;

  // Required: graphics queue family
  // Optional: dedicated transfer/compute queue

  // Scores (highest is best):
  // 0 := no graphics
  // 1 := shared graphics/transfer/compute
  // 2 := dedicated graphics, shared transfer/compute
  // 3 := dedicated graphics/transfer/compute

  uint32_t bestScore = 0;

  uint32_t physicalDeviceCount = 0;
  VkPhysicalDevice physicalDevices[maxNumPhysicalDevices];

  vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
  if (physicalDeviceCount > maxNumPhysicalDevices)
    physicalDeviceCount = maxNumPhysicalDevices;

  vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);

  for (uint32_t i = 0; i < physicalDeviceCount; ++i) {

    VkPhysicalDeviceProperties physicalDeviceProps;
    vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProps);

    uint32_t queueFamilyCnt = 0;
    VkQueueFamilyProperties queueFamilyProps[maxNumQueueFamilies];

    vkGetPhysicalDeviceQueueFamilyProperties(
      physicalDevices[i], &queueFamilyCnt, nullptr);
    if (queueFamilyCnt > maxNumQueueFamilies)
      queueFamilyCnt = maxNumQueueFamilies;

    vkGetPhysicalDeviceQueueFamilyProperties(
      physicalDevices[i], &queueFamilyCnt, queueFamilyProps);

    int32_t graphicsIdx = -1;
    int32_t computeIdx = -1;
    int32_t transferIdx = -1;

    for (uint32_t idx = 0; idx < queueFamilyCnt; ++idx) {
      if (queueFamilyProps[idx].queueCount == 0)
        continue;

      if (queueFamilyProps[idx].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        graphicsIdx = idx;
      } else if (queueFamilyProps[idx].queueFlags & VK_QUEUE_COMPUTE_BIT) {
        computeIdx = idx;
      } else if (queueFamilyProps[idx].queueFlags & VK_QUEUE_TRANSFER_BIT) {
        transferIdx = idx;
      }
    }

    uint32_t score = 0;

    if (graphicsIdx >= 0 && computeIdx >= 0 && transferIdx >= 0) {
      score = 3;
    } else if (graphicsIdx >= 0 && computeIdx >= 0) {
      score = 2;
    } else if (graphicsIdx >= 0) {
      score = 1;
    }

    if (score > bestScore) {
      bestScore = score;
      out->physicalDevice = physicalDevices[i];
      out->graphicQueueFamilyIdx = graphicsIdx;
      out->computeQueueFamilyIdx = computeIdx >= 0 ? computeIdx : graphicsIdx;
      out->transferQueueFamilyIdx =
        transferIdx >= 0 ? transferIdx : out->computeQueueFamilyIdx;
    }
  }

  return bestScore > 0;
}

bool
pkCreateDevice(Device* dev)
{
  if (!dev)
    return false;

  auto devInternal = new DeviceInternal();

  // instance

  volkInitialize();
  assert(volkGetInstanceVersion() >= VK_API_VERSION_1_1);

  VkApplicationInfo appInfo =
    vkiApplicationInfo(nullptr, 0, nullptr, 0, VK_API_VERSION_1_1);

  VkInstanceCreateInfo instInfo =
    vkiInstanceCreateInfo(&appInfo, 0, nullptr, 0, nullptr);

#ifdef _DEBUG
  char const* layers[] = { "VK_LAYER_KHRONOS_validation" };
  instInfo.enabledLayerCount = sizeof(layers) / sizeof(layers[0]);
  instInfo.ppEnabledLayerNames = layers;
#endif

  char const* extensions[] = {
    VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef _WIN32
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
#ifdef _DEBUG
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
#endif
  };

  instInfo.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]);
  instInfo.ppEnabledExtensionNames = extensions;

  uint32_t layerCnt = 0;
  VkLayerProperties layerProperties[512];
  vkEnumerateInstanceLayerProperties(&layerCnt, layerProperties);

  vkCreateInstance(&instInfo, nullptr, &devInternal->instance);

  assert(devInternal->instance != VK_NULL_HANDLE);

  volkLoadInstance(devInternal->instance);

#ifdef _DEBUG
  auto createInfo =
    vkiDebugReportCallbackCreateInfoEXT(debugReportCallback, nullptr);
  createInfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT |
                     VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
                     VK_DEBUG_REPORT_ERROR_BIT_EXT;
  vkCreateDebugReportCallbackEXT(
    devInternal->instance, &createInfo, 0, &devInternal->callback);
#endif // DEBUG

  // device
  char const* deviceExtensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

  uint32_t physicalDeviceCount = 0;
  vkEnumeratePhysicalDevices(
    devInternal->instance, &physicalDeviceCount, nullptr);
  VkPhysicalDevice physicalDevices[16];
  vkEnumeratePhysicalDevices(
    devInternal->instance, &physicalDeviceCount, physicalDevices);

  PhysicalDevice physicalDevice;
  selectDevice(devInternal->instance, &physicalDevice);
  assert(physicalDevice.physicalDevice != VK_NULL_HANDLE);

  devInternal->physicalDevice = physicalDevice.physicalDevice;

  float queuePriority = 1.0f;

  // We create at most 3 queues:
  // - a single graphics queue
  // - additional compute and transfer queues, if available
  // - queues are assumed to be subsets of each other, i.e. graphics > compute >
  // transfer
  VkDeviceQueueCreateInfo queueCreateInfos[3];
  uint32_t numQueues = 1;
  queueCreateInfos[0] = vkiDeviceQueueCreateInfo(
    physicalDevice.graphicQueueFamilyIdx, 1, &queuePriority);

  if (physicalDevice.computeQueueFamilyIdx !=
      physicalDevice.graphicQueueFamilyIdx) {
    queueCreateInfos[1] = vkiDeviceQueueCreateInfo(
      physicalDevice.computeQueueFamilyIdx, 1, &queuePriority);
    numQueues += 1;
  }

  if (physicalDevice.transferQueueFamilyIdx !=
      physicalDevice.computeQueueFamilyIdx) {
    queueCreateInfos[2] = vkiDeviceQueueCreateInfo(
      physicalDevice.transferQueueFamilyIdx, 1, &queuePriority);
    numQueues += 1;
  }

  VkPhysicalDeviceFeatures deviceFeatures = {};
  deviceFeatures.textureCompressionBC = true;
  deviceFeatures.fillModeNonSolid = true;
  deviceFeatures.multiDrawIndirect = true;

  VkDeviceCreateInfo deviceCreateInfo =
    vkiDeviceCreateInfo(numQueues,
                        queueCreateInfos,
                        0,
                        nullptr,
                        sizeof(deviceExtensions) / sizeof(deviceExtensions[0]),
                        deviceExtensions,
                        &deviceFeatures);

  vkCreateDevice(devInternal->physicalDevice,
                 &deviceCreateInfo,
                 nullptr,
                 &devInternal->device);

  assert(devInternal->device != VK_NULL_HANDLE);

  volkLoadDevice(devInternal->device);

  vkGetDeviceQueue(devInternal->device,
                   physicalDevice.graphicQueueFamilyIdx,
                   0,
                   &devInternal->queues[0].queue);
  devInternal->queues[0].queueFamilyIdx = physicalDevice.graphicQueueFamilyIdx;
  devInternal->queues[0].device = devInternal;

  devInternal->graphicsQueueIdx = 0;
  devInternal->computeQueueIdx = 0;
  devInternal->transferQueueIdx = 0;

  if (physicalDevice.computeQueueFamilyIdx !=
      physicalDevice.graphicQueueFamilyIdx) {
    vkGetDeviceQueue(devInternal->device,
                     physicalDevice.computeQueueFamilyIdx,
                     0,
                     &devInternal->queues[1].queue);
    devInternal->queues[1].queueFamilyIdx =
      physicalDevice.computeQueueFamilyIdx;
    devInternal->queues[1].device = devInternal;

    devInternal->computeQueueIdx = 1;
    devInternal->transferQueueIdx = 1;
  }

  if (physicalDevice.transferQueueFamilyIdx !=
      physicalDevice.computeQueueFamilyIdx) {
    vkGetDeviceQueue(devInternal->device,
                     physicalDevice.transferQueueFamilyIdx,
                     0,
                     &devInternal->queues[2].queue);
    devInternal->queues[2].queueFamilyIdx =
      physicalDevice.transferQueueFamilyIdx;
    devInternal->queues[2].device = devInternal;

    devInternal->transferQueueIdx = 2;
  }

  VmaAllocatorCreateInfo allocatorInfo = {};
  allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_1;
  allocatorInfo.instance = devInternal->instance;
  allocatorInfo.physicalDevice = devInternal->physicalDevice;
  allocatorInfo.device = devInternal->device;

  vmaCreateAllocator(&allocatorInfo, &devInternal->vmaAllocator);

  devInternal->dsetAllocator.device = devInternal->device;
  devInternal->cmdBufferAllocator.device = devInternal->device;
  devInternal->fenceAllocator.device = devInternal->device;
  devInternal->semaphoreAllocator.device = devInternal->device;
  devInternal->shared.device = devInternal->device;

  *dev = (Device)devInternal;

  return true;
}

uint32_t
getQueueIdx(DeviceInternal* dev, QueueType type)
{
  switch (type) {
    case Graphics:
      return dev->graphicsQueueIdx;
    case Compute:
      return dev->computeQueueIdx;
    case Transfer:
      return dev->transferQueueIdx;
  }
}

bool
pkGetQueue(Device dev, QueueType type, Queue* queue)
{
  if (!queue)
    return false;

  auto devInternal = (DeviceInternal*)dev;
  *queue = (Queue)&devInternal->queues[getQueueIdx(devInternal, type)];

  return true;
}

bool
pkCreateSwapchain(Device dev,
                  SwapchainCreateInfo const* createInfo,
                  Swapchain* swapchainOut)
{
  if (!createInfo || !swapchainOut)
    return false;

  auto devInternal = (DeviceInternal*)dev;

  VkSurfaceKHR surface = VK_NULL_HANDLE;

  if (createInfo->oldSwapchain != nullptr) {
    auto oldSwapchain = (SwapchainInternal*)createInfo->oldSwapchain;
    surface = oldSwapchain->surface;
    oldSwapchain->surface = VK_NULL_HANDLE;
  } else {
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceCreateInfo.pNext = nullptr;
    surfaceCreateInfo.flags = 0;
    surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);
    surfaceCreateInfo.hwnd = (HWND)createInfo->platformHandle;

    vkCreateWin32SurfaceKHR(
      devInternal->instance, &surfaceCreateInfo, nullptr, &surface);
  }

  assert(surface != VK_NULL_HANDLE);

  VkBool32 supported;
  vkGetPhysicalDeviceSurfaceSupportKHR(
    devInternal->physicalDevice,
    devInternal->queues[devInternal->graphicsQueueIdx].queueFamilyIdx,
    surface,
    &supported);

  assert(surface != VK_NULL_HANDLE);

  VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  VkCompositeAlphaFlagBitsKHR compositeAlpha =
    VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  VkPresentModeKHR presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
  VkBool32 clipped = VK_TRUE;

  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    devInternal->physicalDevice, surface, &capabilities);

  auto swapchainCreateInfo =
    vkiSwapchainCreateInfoKHR(surface,
                              createInfo->textureCnt,
                              GetVkFormat(createInfo->format),
                              colorSpace,
                              { createInfo->width, createInfo->height },
                              1,
                              VkImageUsageFlags{ createInfo->usageFlags },
                              VK_SHARING_MODE_EXCLUSIVE,
                              1,
                              nullptr,
                              capabilities.currentTransform,
                              compositeAlpha,
                              presentMode,
                              clipped,
                              VK_NULL_HANDLE);

  VkSwapchainKHR swapchain = VK_NULL_HANDLE;
  vkCreateSwapchainKHR(
    devInternal->device, &swapchainCreateInfo, nullptr, &swapchain);

  VkImage swapchainImages[8];
  uint32_t imageCnt = 8;

  vkGetSwapchainImagesKHR(devInternal->device, swapchain, &imageCnt, nullptr);
  assert(imageCnt <= 8);
  vkGetSwapchainImagesKHR(
    devInternal->device, swapchain, &imageCnt, swapchainImages);

  auto swapchainInternal = new SwapchainInternal();
  swapchainInternal->surface = surface;
  swapchainInternal->swapchain = swapchain;

  for (uint32_t i = 0; i < imageCnt; ++i) {
    auto texture = new TextureInternal();
    texture->image = swapchainImages[i];
    texture->size = 0;
    texture->desc.width = createInfo->width;
    texture->desc.height = createInfo->height;
    texture->desc.format = createInfo->format;
    texture->desc.usageFlags = createInfo->usageFlags;
    texture->desc.depth = 1;
    texture->desc.layers = 1;
    texture->desc.mipLevels = 1;
    texture->subresource.aspectMask =
      GetImageAspectFlags(GetVkFormat(texture->desc.format));
    texture->subresource.baseMipLevel = 0;
    texture->subresource.baseArrayLayer = 0;
    texture->subresource.levelCount = texture->desc.mipLevels;
    texture->subresource.layerCount = texture->desc.layers;

    auto imageViewCreateInfo =
      vkiImageViewCreateInfo(texture->image,
                             VK_IMAGE_VIEW_TYPE_2D,
                             GetVkFormat(texture->desc.format),
                             { VK_COMPONENT_SWIZZLE_IDENTITY,
                               VK_COMPONENT_SWIZZLE_IDENTITY,
                               VK_COMPONENT_SWIZZLE_IDENTITY,
                               VK_COMPONENT_SWIZZLE_IDENTITY },
                             { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

    vkCreateImageView(
      devInternal->device, &imageViewCreateInfo, nullptr, &texture->view);

    swapchainInternal->textures[swapchainInternal->textureCnt] =
      (Texture)texture;
    swapchainInternal->textureCnt++;
  }

  *swapchainOut = (Swapchain)swapchainInternal;
  return true;
}

bool
pkCreateBuffer(Device dev,
               BufferCreateInfo const* createInfo,
               Buffer* bufferOut,
               void** data)
{
  if (!createInfo || !bufferOut || !data)
    return false;

  auto devInternal = (DeviceInternal*)dev;

  VkBufferUsageFlags usage{ createInfo->usageFlags };

  VkBufferCreateInfo bufferCreateInfo = {
    VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO
  };
  bufferCreateInfo.size = createInfo->size;
  bufferCreateInfo.usage = usage;

  VmaAllocationCreateInfo allocCreateInfo = {};
  allocCreateInfo.usage = static_cast<VmaMemoryUsage>(createInfo->memoryUsage);
  allocCreateInfo.flags =
    VMA_ALLOCATION_CREATE_MAPPED_BIT; // automatically maps memory

  VkBuffer buffer;
  VmaAllocation allocation = {};
  VmaAllocationInfo allocInfo = {};

  vmaCreateBuffer(devInternal->vmaAllocator,
                  &bufferCreateInfo,
                  &allocCreateInfo,
                  &buffer,
                  &allocation,
                  &allocInfo);

  auto bufferInternal =
    new BufferInternal{ *createInfo, createInfo->size, allocation, buffer };

  *bufferOut = (Buffer)bufferInternal;
  *data = allocInfo.pMappedData;

  return true;
}

bool
pkCreateTexture(Device dev,
                TextureCreateInfo const* createInfo,
                Texture* textureOut)
{
  if (!createInfo || !textureOut)
    return false;

  auto devInternal = (DeviceInternal*)dev;

  VkFormat format = GetVkFormat(createInfo->format);
  VkImageType imageType = VK_IMAGE_TYPE_2D;
  VkImageViewType imageViewType = VK_IMAGE_VIEW_TYPE_2D;

  VkSampleCountFlagBits samples = GetVkSampleCountFlagBits(createInfo->samples);

  // TODO: replace wonky this derivation of image type
  if (createInfo->height == 1 && createInfo->depth == 1) {
    imageType = VK_IMAGE_TYPE_1D;
    imageViewType = VK_IMAGE_VIEW_TYPE_1D;
  } else if (createInfo->depth > 1) {
    imageType = VK_IMAGE_TYPE_3D;
    imageViewType = VK_IMAGE_VIEW_TYPE_3D;
  }

  VkExtent3D extent = { 1, 1, 1 };

  switch (imageType) {
    case VK_IMAGE_TYPE_1D:
      extent.width = createInfo->width;
      break;
    case VK_IMAGE_TYPE_2D:
      extent.width = createInfo->width;
      extent.height = createInfo->height;
      break;
    case VK_IMAGE_TYPE_3D:
      extent.width = createInfo->width;
      extent.height = createInfo->height;
      extent.depth = createInfo->depth;
      break;
    default:
      break;
  }

  VmaAllocationCreateInfo allocCreateInfo = {};
  allocCreateInfo.usage = static_cast<VmaMemoryUsage>(MemoryUsage::GPU_ONLY);
  allocCreateInfo.flags = 0;

  VkImage image = VK_NULL_HANDLE;
  VmaAllocation allocation = {};
  VmaAllocationInfo allocInfo = {};
  VkImageUsageFlags usage = createInfo->usageFlags;

  auto imageCreateInfo = vkiImageCreateInfo(imageType,
                                            format,
                                            extent,
                                            createInfo->mipLevels,
                                            createInfo->layers,
                                            samples,
                                            VK_IMAGE_TILING_OPTIMAL,
                                            usage,
                                            VK_SHARING_MODE_EXCLUSIVE,
                                            0,
                                            nullptr,
                                            VK_IMAGE_LAYOUT_UNDEFINED);

  vmaCreateImage(devInternal->vmaAllocator,
                 &imageCreateInfo,
                 &allocCreateInfo,
                 &image,
                 &allocation,
                 &allocInfo);

  VkComponentMapping componentMapping = { VK_COMPONENT_SWIZZLE_IDENTITY,
                                          VK_COMPONENT_SWIZZLE_IDENTITY,
                                          VK_COMPONENT_SWIZZLE_IDENTITY,
                                          VK_COMPONENT_SWIZZLE_IDENTITY };

  VkImageSubresourceRange subresource = {};
  subresource.aspectMask = GetImageAspectFlags(format);
  subresource.baseMipLevel = 0;
  subresource.baseArrayLayer = 0;
  subresource.levelCount = createInfo->mipLevels;
  subresource.layerCount = createInfo->layers;

  // view is the whole image
  auto imageViewCreateInfo = vkiImageViewCreateInfo(
    image, imageViewType, format, componentMapping, subresource);

  VkImageView view = VK_NULL_HANDLE;
  vkCreateImageView(devInternal->device, &imageViewCreateInfo, nullptr, &view);

  auto textureInternal = new TextureInternal();
  textureInternal->desc = *createInfo;
  textureInternal->image = image;
  textureInternal->view = view;
  textureInternal->allocation = allocation;
  textureInternal->size = allocInfo.size;
  textureInternal->subresource = subresource;

  *textureOut = (Texture)textureInternal;

  return true;
}

bool
pkDestroySwapchain(Device dev, Swapchain res)
{
  auto devInternal = (DeviceInternal*)dev;
  devInternal->swapchains.push_back({ res, devInternal->frame });
  return true;
}

bool
pkDestroyBuffer(Device dev, Buffer res)
{
  auto devInternal = (DeviceInternal*)dev;
  devInternal->buffers.push_back({ res, devInternal->frame });
  return true;
}

bool
pkDestroyTexture(Device dev, Texture res)
{
  auto devInternal = (DeviceInternal*)dev;
  devInternal->textures.push_back({ res, devInternal->frame });
  return true;
}

bool
pkCreateCmdBuffer(Queue queue, CmdBuffer* cmdBufferOut)
{
  if (!cmdBufferOut)
    return false;

  auto queueInternal = (QueueInternal*)queue;
  auto devInternal = queueInternal->device;

  auto cmdBuffer = devInternal->cmdBufferAllocator.getCommandBuffer(
    queueInternal->queueFamilyIdx, devInternal->frame);
  auto cmdBufferInternal = new CmdBufferInternal;
  cmdBufferInternal->cmdBuffer = cmdBuffer;
  cmdBufferInternal->queue = queueInternal;

  auto cmdBufferBeginInfo = vkiCommandBufferBeginInfo(nullptr);
  vkBeginCommandBuffer(cmdBuffer, &cmdBufferBeginInfo);

  *cmdBufferOut = (CmdBuffer)cmdBufferInternal;

  return true;
}

void
pkCopy(CmdBuffer cmdBuffer, Buffer dst, Buffer src)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto dstBufferInfo = (BufferInternal*)dst;
  auto srcBufferInfo = (BufferInternal*)src;

  VkBufferCopy pkCopy =
    vkiBufferCopy(0, 0, std::min(srcBufferInfo->size, dstBufferInfo->size));

  vkCmdCopyBuffer(cmdBufferInternal->cmdBuffer,
                  srcBufferInfo->buffer,
                  dstBufferInfo->buffer,
                  1,
                  &pkCopy);
}

void
pkCopyBufferToTexture(CmdBuffer cmdBuffer, Texture texture, Buffer buffer)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto textureInternal = (TextureInternal*)texture;
  auto bufferInternal = (BufferInternal*)buffer;

  VkImageSubresourceLayers subresouce = {};
  subresouce.aspectMask = textureInternal->subresource.aspectMask;
  subresouce.baseArrayLayer = textureInternal->subresource.baseArrayLayer;
  subresouce.layerCount = textureInternal->subresource.layerCount;
  subresouce.mipLevel = textureInternal->subresource.baseMipLevel;

  VkBufferImageCopy pkCopy =
    vkiBufferImageCopy(0,
                       0,
                       0,
                       subresouce,
                       { 0, 0, 0 },
                       { textureInternal->desc.width,
                         textureInternal->desc.height,
                         textureInternal->desc.depth });

  vkCmdCopyBufferToImage(cmdBufferInternal->cmdBuffer,
                         bufferInternal->buffer,
                         textureInternal->image,
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                         1,
                         &pkCopy);
}

void
insertBarrier(CmdBuffer cmdBuffer, BufferBarrier const* bufferBarrier)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto bufferInternal = (BufferInternal*)bufferBarrier->buffer;

  auto barrier = vkiBufferMemoryBarrier(bufferBarrier->src.access,
                                        bufferBarrier->dst.access,
                                        -1,
                                        -1,
                                        bufferInternal->buffer,
                                        0,
                                        bufferInternal->size);

  vkCmdPipelineBarrier(cmdBufferInternal->cmdBuffer,
                       bufferBarrier->src.stage,
                       bufferBarrier->dst.stage,
                       VK_DEPENDENCY_BY_REGION_BIT,
                       0,
                       nullptr,
                       1,
                       &barrier,
                       0,
                       nullptr);
}

uint32_t
getQueueFamilyIdx(DeviceInternal* dev, QueueType type)
{
  return dev->queues[getQueueIdx(dev, type)].queueFamilyIdx;
}

void
insertBarrier(CmdBuffer cmdBuffer, TextureBarrier const* textureBarrier)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto textureInternal = (TextureInternal*)textureBarrier->texture;

  auto devInternal = cmdBufferInternal->queue->device;

  auto const barrier = vkiImageMemoryBarrier(
    textureBarrier->src.access,
    textureBarrier->dst.access,
    (VkImageLayout)textureBarrier->initialLayout,
    (VkImageLayout)textureBarrier->finalLayout,
    getQueueFamilyIdx(devInternal, textureBarrier->src.queue),
    getQueueFamilyIdx(devInternal, textureBarrier->dst.queue),
    textureInternal->image,
    textureInternal->subresource);

  vkCmdPipelineBarrier(cmdBufferInternal->cmdBuffer,
                       textureBarrier->src.stage,
                       textureBarrier->dst.stage,
                       VK_DEPENDENCY_BY_REGION_BIT,
                       0,
                       nullptr,
                       0,
                       nullptr,
                       1,
                       &barrier);
}

void
beginRenderPass(CmdBuffer cmdBuffer, RenderPass const* renderPass)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto devInternal = cmdBufferInternal->queue->device;

  cmdBufferInternal->renderPass = VK_NULL_HANDLE;

  RenderPassInternal rp = {};
  rp.subpassCnt = 1;

  Framebuffer fb = {};
  VkClearValue clearValues[Framebuffer::MAX_NUM_ATTACHMENTS] = {};

  // TODO: explicitly set external subpass dependency if initial -> final
  // layout transition happend, to avoid an implicitly inserted, probably
  // costly external subpass dependency.
  for (uint32_t i = 0; i < renderPass->attachmentCnt; ++i) {
    auto const& info = renderPass->attachmentInfos[i];
    auto textureInternal = (TextureInternal const*)info.texture;

    switch (info.type) {
      case AttachmentType::COLOR: {
        // attachments
        rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
          GetVkFormat(textureInternal->desc.format),
          GetVkSampleCountFlagBits(textureInternal->desc.samples),
          GetVkAttachmentLoadOp(info.loadOp),
          GetVkAttachmentStoreOp(info.storeOp),
          VK_ATTACHMENT_LOAD_OP_CLEAR,
          VK_ATTACHMENT_STORE_OP_STORE,
          VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
          info.makePresentable ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
                               : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

        // attachment refs for subpass 0
        rp.attachmentRefs[0]
          .colorAttachments[rp.attachmentRefs[0].colorAttachmentCnt] = {
          rp.attachmentCnt, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };
        ++rp.attachmentRefs[0].colorAttachmentCnt;

        rp.subpassess[0].pColorAttachments =
          rp.attachmentRefs->colorAttachments;
        rp.subpassess[0].colorAttachmentCount =
          rp.attachmentRefs->colorAttachmentCnt;

        clearValues[rp.attachmentCnt] = { info.clearValue.color.float32[0],
                                          info.clearValue.color.float32[1],
                                          info.clearValue.color.float32[2],
                                          info.clearValue.color.float32[3] };

        ++rp.attachmentCnt;

        // framebuffer
        fb.width = textureInternal->desc.width;
        fb.height = textureInternal->desc.height;
        fb.layers = textureInternal->desc.layers;
        fb.attachments[fb.attachmentCnt] = textureInternal->view;
        ++fb.attachmentCnt;

        break;
      }
      case AttachmentType::DEPTH: {
        // TODO: depth stencil attachments and depth only attachments need
        // different layouts
        rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
          GetVkFormat(textureInternal->desc.format),
          GetVkSampleCountFlagBits(textureInternal->desc.samples),
          VK_ATTACHMENT_LOAD_OP_CLEAR,
          VK_ATTACHMENT_STORE_OP_STORE,
          GetVkAttachmentLoadOp(info.loadOp),
          GetVkAttachmentStoreOp(info.storeOp),
          VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
          VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

        // attachment refs for subpass 0
        rp.attachmentRefs[0].depthStencilAttachments
          [rp.attachmentRefs[0].depthStencilAttachmentCnt] = {
          rp.attachmentCnt, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        };
        ++rp.attachmentRefs[0].depthStencilAttachmentCnt;

        rp.subpassess[0].pDepthStencilAttachment =
          rp.attachmentRefs[0].depthStencilAttachments;

        // we use the color clear value here, but since it's a union, the depth
        // clear value will be set properly
        clearValues[rp.attachmentCnt] = { info.clearValue.color.float32[0],
                                          info.clearValue.color.float32[1],
                                          info.clearValue.color.float32[2],
                                          info.clearValue.color.float32[3] };

        ++rp.attachmentCnt;

        // framebuffer
        fb.width = textureInternal->desc.width;
        fb.height = textureInternal->desc.height;
        fb.layers = textureInternal->desc.layers;
        fb.attachments[fb.attachmentCnt] = textureInternal->view;
        ++fb.attachmentCnt;

        break;
      }
      case AttachmentType::RESOLVE: {
        // COLOR resolve attachment
        rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
          GetVkFormat(textureInternal->desc.format),
          GetVkSampleCountFlagBits(textureInternal->desc.samples),
          GetVkAttachmentLoadOp(info.loadOp),
          GetVkAttachmentStoreOp(info.storeOp),
          VK_ATTACHMENT_LOAD_OP_CLEAR,
          VK_ATTACHMENT_STORE_OP_STORE,
          VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
          info.makePresentable ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
                               : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

        // attachment refs for subpass 0
        rp.attachmentRefs[0]
          .resolveAttachments[rp.attachmentRefs[0].resolveAttachmentCnt] = {
          rp.attachmentCnt, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };
        ++rp.attachmentRefs[0].resolveAttachmentCnt;

        rp.subpassess[0].pResolveAttachments =
          rp.attachmentRefs->resolveAttachments;

        clearValues[rp.attachmentCnt] = { info.clearValue.color.float32[0],
                                          info.clearValue.color.float32[1],
                                          info.clearValue.color.float32[2],
                                          info.clearValue.color.float32[3] };

        ++rp.attachmentCnt;

        // framebuffer
        fb.width = textureInternal->desc.width;
        fb.height = textureInternal->desc.height;
        fb.layers = textureInternal->desc.layers;
        fb.attachments[fb.attachmentCnt] = textureInternal->view;
        ++fb.attachmentCnt;

        break;
      }
      default:
        break;
    }
  }

  devInternal->shared.getRenderPass(&rp, &cmdBufferInternal->renderPass);
  cmdBufferInternal->subpass = 0;

  fb.renderPass = cmdBufferInternal->renderPass;
  VkFramebuffer framebuffer;
  devInternal->shared.getFramebuffer(&fb, &framebuffer);

  VkRect2D renderArea = { {}, { fb.width, fb.height } };

  VkRenderPassBeginInfo renderPassBeginInfo =
    vkiRenderPassBeginInfo(cmdBufferInternal->renderPass,
                           framebuffer,
                           renderArea,
                           rp.attachmentCnt,
                           clearValues);
  vkCmdBeginRenderPass(cmdBufferInternal->cmdBuffer,
                       &renderPassBeginInfo,
                       VK_SUBPASS_CONTENTS_INLINE);
}

void
bindVertexBuffer(CmdBuffer cmdBuffer, Buffer buffer, uint64_t offset)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto bufferInternal = (BufferInternal*)buffer;
  vkCmdBindVertexBuffers(
    cmdBufferInternal->cmdBuffer, 0, 1, &bufferInternal->buffer, &offset);
}

void
bindIndexBuffer(CmdBuffer cmdBuffer, Buffer buffer)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto bufferInternal = (BufferInternal*)buffer;
  vkCmdBindIndexBuffer(cmdBufferInternal->cmdBuffer,
                       bufferInternal->buffer,
                       0,
                       VkIndexType::VK_INDEX_TYPE_UINT32);
}

void
setPipelineState(CmdBuffer cmdBuffer, PipelineState const* pipelineState)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto devInternal = cmdBufferInternal->queue->device;

  Shared::Pipeline pipeline;

  if (pipelineState->shader.computeShader) {
    devInternal->shared.getComputePipeline(pipelineState->shader.computeShader,
                                           &pipeline);
    vkCmdBindPipeline(cmdBufferInternal->cmdBuffer,
                      VK_PIPELINE_BIND_POINT_COMPUTE,
                      pipeline.vkPipeline);
  } else {

    GraphicsPipelineState gps;

    gps.vertexInput.bindingDescriptionCnt =
      pipelineState->vertexInput.bindingDescriptionCnt;

    for (uint32_t i = 0; i < pipelineState->vertexInput.bindingDescriptionCnt;
         ++i) {
      gps.vertexInput.bindingDescriptions[i].binding =
        pipelineState->vertexInput.bindingDescriptions[i].binding;
      gps.vertexInput.bindingDescriptions[i].inputRate = GetVkVertexInputRate(
        pipelineState->vertexInput.bindingDescriptions[i].inputRate);
      gps.vertexInput.bindingDescriptions[i].stride =
        pipelineState->vertexInput.bindingDescriptions[i].stride;
    }

    gps.vertexInput.attributeDescriptionCnt =
      pipelineState->vertexInput.attributeDescriptionCnt;

    for (uint32_t i = 0; i < pipelineState->vertexInput.attributeDescriptionCnt;
         ++i) {
      gps.vertexInput.attributeDescriptions[i].binding =
        pipelineState->vertexInput.attributeDescriptions[i].binding;
      gps.vertexInput.attributeDescriptions[i].location =
        pipelineState->vertexInput.attributeDescriptions[i].location;
      gps.vertexInput.attributeDescriptions[i].offset =
        pipelineState->vertexInput.attributeDescriptions[i].offset;
      gps.vertexInput.attributeDescriptions[i].format =
        GetVkFormat(pipelineState->vertexInput.attributeDescriptions[i].format);
    }

    // input assembly
    gps.inputAssembly.primitiveRestartEnable =
      pipelineState->inputAssembly.primitiveRestartEnable;
    gps.inputAssembly.topology =
      GetVkPrimitiveTopology(pipelineState->inputAssembly.topology);

    // viewport
    gps.viewport.viewport.x = pipelineState->viewport.viewport.x;
    gps.viewport.viewport.y = pipelineState->viewport.viewport.x;
    gps.viewport.viewport.width = pipelineState->viewport.viewport.width;
    gps.viewport.viewport.height = pipelineState->viewport.viewport.height;
    gps.viewport.viewport.minDepth = pipelineState->viewport.viewport.minDepth;
    gps.viewport.viewport.maxDepth = pipelineState->viewport.viewport.maxDepth;

    gps.viewport.scissors.offset.x = pipelineState->viewport.scissors.x;
    gps.viewport.scissors.offset.y = pipelineState->viewport.scissors.y;
    gps.viewport.scissors.extent.width = pipelineState->viewport.scissors.width;
    gps.viewport.scissors.extent.height =
      pipelineState->viewport.scissors.height;

    // rasterization
    gps.rasterization.cullMode =
      GetVkCullModeFlags(pipelineState->rasterization.cullMode);
    gps.rasterization.polygonMode =
      GetVkPolygonMode(pipelineState->rasterization.polygonMode);
    gps.rasterization.frontFace =
      GetVkFrontFace(pipelineState->rasterization.frontFace);

    // multisample
    gps.multisample.rasterizationSamples =
      GetVkSampleCountFlagBits(pipelineState->multisample.rasterizationSamples);

    // depth stencil
    gps.depthStencil.depthTestenable =
      pipelineState->depthStencil.depthTestenable;
    gps.depthStencil.depthWriteEnable =
      pipelineState->depthStencil.depthWriteEnable;
    gps.depthStencil.depthCompareOp =
      GetVkCompareOp(pipelineState->depthStencil.depthCompareOp),
    gps.depthStencil.front =
      GetVkStencilOpState(pipelineState->depthStencil.front);
    gps.depthStencil.back =
      GetVkStencilOpState(pipelineState->depthStencil.back);
    gps.depthStencil.stencilTestEnable =
      pipelineState->depthStencil.stencilTestEnable;

    // blend
    gps.blend.enable = pipelineState->blend.enable;
    gps.blend.srcColorFactor =
      GetVkBlendFactor(pipelineState->blend.srcColorFactor);
    gps.blend.dstColorFactor =
      GetVkBlendFactor(pipelineState->blend.dstColorFactor);
    gps.blend.srcAlphaFactor =
      GetVkBlendFactor(pipelineState->blend.srcAlphaFactor);
    gps.blend.dstAlphaFactor =
      GetVkBlendFactor(pipelineState->blend.dstAlphaFactor);
    gps.blend.colorOp = static_cast<VkBlendOp>(pipelineState->blend.colorOp);
    gps.blend.alphaOp = static_cast<VkBlendOp>(pipelineState->blend.alphaOp);

    devInternal->shared.getGraphicsPipeline(
      pipelineState->shader.vertexShader,
      pipelineState->shader.fragmentShader,
      &gps,
      cmdBufferInternal->renderPass,
      cmdBufferInternal->subpass,
      &pipeline);

    vkCmdBindPipeline(cmdBufferInternal->cmdBuffer,
                      VK_PIPELINE_BIND_POINT_GRAPHICS,
                      pipeline.vkPipeline);
  }

  cmdBufferInternal->vkPipelineLayout = pipeline.vkPipelineLayout;
  cmdBufferInternal->pipelineLayout = pipeline.pipelineLayout;
}

void
bindUniformBuffer(CmdBuffer cmdBuffer,
                  Buffer buffer,
                  uint32_t set,
                  uint32_t binding,
                  uint32_t offset,
                  uint32_t range)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto bufferInternal = (BufferInternal*)buffer;
  auto& d = cmdBufferInternal->sets[set].bindings[binding];

  if (d.bufferInfo.buffer == bufferInternal->buffer &&
      d.bufferInfo.range == range) {
    cmdBufferInternal->sets[set].dynamicOffsetsDirty = true;
  } else {
    d.bufferInfo = vkiDescriptorBufferInfo(bufferInternal->buffer, 0, range);
    cmdBufferInternal->sets[set].dirty = true;
  }

  d.dynamicOffset = offset;
}

void
bindStorageBuffer(CmdBuffer cmdBuffer,
                  Buffer buffer,
                  uint32_t set,
                  uint32_t binding,
                  uint32_t offset,
                  uint32_t range)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto bufferInternal = (BufferInternal*)buffer;

  auto& d = cmdBufferInternal->sets[set].bindings[binding];

  if (d.bufferInfo.buffer == bufferInternal->buffer &&
      d.bufferInfo.range == range) {
    cmdBufferInternal->sets[set].dynamicOffsetsDirty = true;
  } else {
    d.bufferInfo = vkiDescriptorBufferInfo(bufferInternal->buffer, 0, range);
    cmdBufferInternal->sets[set].dirty = true;
  }

  d.dynamicOffset = offset;
}

void
bindSampler(CmdBuffer cmdBuffer, uint32_t set, uint32_t binding)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto devInternal = cmdBufferInternal->queue->device;
  VkSampler sampler = VK_NULL_HANDLE;
  devInternal->shared.getSampler(&sampler);
  auto& d = cmdBufferInternal->sets[set].bindings[binding];
  d.imageInfo =
    vkiDescriptorImageInfo(sampler, VK_NULL_HANDLE, VK_IMAGE_LAYOUT_UNDEFINED);
  cmdBufferInternal->sets[set].dirty = true;
}

void
bindSampledTexture(CmdBuffer cmdBuffer,
                   Texture texture,
                   uint32_t set,
                   uint32_t binding)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  auto textureInternal = (TextureInternal*)texture;

  auto& d = cmdBufferInternal->sets[set].bindings[binding];
  d.imageInfo =
    vkiDescriptorImageInfo(VK_NULL_HANDLE,
                           textureInternal->view,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  cmdBufferInternal->sets[set].dirty = true;
}

void
flushDescriptorSets(CmdBufferInternal* cmdBufferInternal,
                    VkPipelineBindPoint bindPoint)
{
  auto devInternal = cmdBufferInternal->queue->device;

  for (uint32_t i = 0; i < cmdBufferInternal->pipelineLayout.layoutCnt; ++i) {
    if (!cmdBufferInternal->sets[i].dirty &&
        !cmdBufferInternal->sets[i].dynamicOffsetsDirty) {
      continue;
    }

    uint32_t dynamicOffsets[8] = {};
    uint32_t dynamicOffsetCnt = 0;

    if (cmdBufferInternal->sets[i].dirty) {
      VkWriteDescriptorSet writes[8] = {};
      uint32_t writeCnt = 0;

      VkDescriptorSetLayout layout;
      devInternal->shared.getDescriptorSetLayout(
        &cmdBufferInternal->pipelineLayout.layouts[i], &layout);

      devInternal->dsetAllocator.getDescriptorSet(
        layout,
        &cmdBufferInternal->pipelineLayout.layouts[i],
        devInternal->frame,
        &cmdBufferInternal->sets[i].set);

      auto const& bindings = cmdBufferInternal->sets[i].bindings;
      auto bindingCnt = cmdBufferInternal->pipelineLayout.layouts[i].bindingCnt;

      if (bindingCnt > 8) {
        bindingCnt = 8;
      }

      for (uint32_t j = 0; j < bindingCnt; ++j) {
        writes[j] = vkiWriteDescriptorSet(
          cmdBufferInternal->sets[i].set,
          cmdBufferInternal->pipelineLayout.layouts[i].bindings[j].binding,
          0,
          1,
          cmdBufferInternal->pipelineLayout.layouts[i]
            .bindings[j]
            .descriptorType,
          nullptr,
          nullptr,
          nullptr);

        switch (cmdBufferInternal->pipelineLayout.layouts[i]
                  .bindings[j]
                  .descriptorType) {
          case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
          case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC: {
            writes[j].pBufferInfo = &bindings[j].bufferInfo;
            dynamicOffsets[dynamicOffsetCnt++] = bindings[j].dynamicOffset;
            break;
          }
          case VK_DESCRIPTOR_TYPE_SAMPLER:
          case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE: {
            writes[j].pImageInfo = &bindings[j].imageInfo;
            break;
          }
        }
      }

      if (bindingCnt > 0) {
        vkUpdateDescriptorSets(
          devInternal->device, bindingCnt, writes, 0, nullptr);
      }
    } else if (cmdBufferInternal->sets[i].dynamicOffsetsDirty) {
      auto const& bindings = cmdBufferInternal->sets[i].bindings;
      auto bindingCnt = cmdBufferInternal->pipelineLayout.layouts[i].bindingCnt;

      if (bindingCnt > 8) {
        bindingCnt = 8;
      }

      for (uint32_t j = 0; j < bindingCnt; ++j) {
        switch (cmdBufferInternal->pipelineLayout.layouts[i]
                  .bindings[j]
                  .descriptorType) {
          case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
          case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC: {
            dynamicOffsets[dynamicOffsetCnt++] = bindings[j].dynamicOffset;
            break;
          }
        }
      }
    }

    vkCmdBindDescriptorSets(cmdBufferInternal->cmdBuffer,
                            bindPoint,
                            cmdBufferInternal->vkPipelineLayout,
                            0,
                            1,
                            &cmdBufferInternal->sets[i].set,
                            dynamicOffsetCnt,
                            dynamicOffsets);

    cmdBufferInternal->sets[i].dirty = false;
    cmdBufferInternal->sets[i].dynamicOffsetsDirty = false;
  }
}
void
draw(CmdBuffer cmdBuffer, uint32_t cnt)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  flushDescriptorSets(cmdBufferInternal, VK_PIPELINE_BIND_POINT_GRAPHICS);
  vkCmdDraw(cmdBufferInternal->cmdBuffer, cnt, 1, 0, 0);
}

void
drawIndexed(CmdBuffer cmdBuffer, uint32_t cnt)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  flushDescriptorSets(cmdBufferInternal, VK_PIPELINE_BIND_POINT_GRAPHICS);
  vkCmdDrawIndexed(cmdBufferInternal->cmdBuffer, cnt, 1, 0, 0, 0);
}

void
endRenderPass(CmdBuffer cmdBuffer)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  vkCmdEndRenderPass(cmdBufferInternal->cmdBuffer);
}

void
dispatch(CmdBuffer cmdBuffer, uint32_t x, uint32_t y, uint32_t z)
{
  auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer;
  flushDescriptorSets(cmdBufferInternal, VK_PIPELINE_BIND_POINT_COMPUTE);
  vkCmdDispatch(cmdBufferInternal->cmdBuffer, x, y, z);
}

bool
submit(Queue queue,
       CmdBuffer* cmdBuffer,
       uint32_t cnt,
       Semaphore* wait,
       PipelineStageFlags* stage,
       uint32_t waitCnt,
       Semaphore* signal,
       uint32_t signalCnt,
       Fence* fenceOut)
{
  auto queueInternal = (QueueInternal*)queue;
  auto devInternal = queueInternal->device;

  VkCommandBuffer vkCommandBuffers[8] = {};

  for (uint32_t i = 0; i < cnt; ++i) {
    auto cmdBufferInternal = (CmdBufferInternal*)cmdBuffer[i];
    vkEndCommandBuffer(cmdBufferInternal->cmdBuffer);
    vkCommandBuffers[i] = cmdBufferInternal->cmdBuffer;
    delete cmdBufferInternal;
  }

  // TODO:
  // - need for better design
  // - a "frame" and "fence" are not always equivalent; one might wait for a
  // fence that occurs within a frame
  VkFence fence = VK_NULL_HANDLE;
  if (fenceOut) {
    fence = devInternal->fenceAllocator.getFence(devInternal->frame);
    queueInternal->fences.push_back({ fence, devInternal->frame });
    *fenceOut = (Fence)devInternal->frame;
  }

  VkSemaphore vkSemaphores[8] = {};
  for (uint32_t i = 0; i < signalCnt; ++i) {
    vkSemaphores[i] =
      devInternal->semaphoreAllocator.getSemaphore(devInternal->frame);
    signal[i] = (Semaphore)vkSemaphores[i];
  }

  auto submitInfo = vkiSubmitInfo(waitCnt,
                                  (VkSemaphore*)wait,
                                  (VkPipelineStageFlags*)stage,
                                  cnt,
                                  vkCommandBuffers,
                                  signalCnt,
                                  vkSemaphores);

  vkQueueSubmit(queueInternal->queue, 1, &submitInfo, fence);

  return true;
}

bool
acquireNext(Device dev,
            Swapchain swapchain,
            Texture* texture,
            Semaphore* signal)
{
  auto devInternal = (DeviceInternal*)dev;
  auto swapchainInternal = (SwapchainInternal*)swapchain;

  VkSemaphore sem = VK_NULL_HANDLE;

  if (signal) {
    sem = devInternal->semaphoreAllocator.getSemaphore(devInternal->frame);
    *signal = (Semaphore)sem;
  }

  auto result = vkAcquireNextImageKHR(devInternal->device,
                                      swapchainInternal->swapchain,
                                      -1,
                                      sem,
                                      VK_NULL_HANDLE,
                                      &swapchainInternal->nextTextureIdx);

  auto textureInfo =
    (TextureInternal*)
      swapchainInternal->textures[swapchainInternal->nextTextureIdx];

  *texture = (Texture)textureInfo;

  return result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR;
}

bool
present(Queue queue, Swapchain swapchain, Semaphore* wait)
{
  auto queueInternal = (QueueInternal*)queue;
  auto swapchainInternal = (SwapchainInternal*)swapchain;
  VkResult result = {};

  auto textureInfo =
    (TextureInternal*)
      swapchainInternal->textures[swapchainInternal->nextTextureIdx];
  auto presentInfo = vkiPresentInfoKHR(0,
                                       nullptr,
                                       1,
                                       &swapchainInternal->swapchain,
                                       &swapchainInternal->nextTextureIdx,
                                       &result);

  presentInfo.waitSemaphoreCount = wait ? 1 : 0;
  presentInfo.pWaitSemaphores = (VkSemaphore*)wait;

  vkQueuePresentKHR(queueInternal->queue, &presentInfo);

  return result == VK_SUCCESS;
}

bool
wait(Device dev, Fence fence)
{
  auto devInternal = (DeviceInternal*)dev;

  // TODO:
  // - we could remove fences alltogether and use timeline semaphores instead

  // TODO:
  // - again, frame and fence should not actually be equivalent
  // - because of possibly multiple fences per frame, a fence might be set
  // before a frame ends
  // - here we are just waiting until the frame ends, so we might be waiting
  // longer than actually
  //   necessary
  uint64_t frame = fence;
  if (devInternal->queues[devInternal->graphicsQueueIdx].fences.empty())
    return true;

  // not popping things of the the fence deque, this will happen in "frame()"
  for (auto const& pair :
       devInternal->queues[devInternal->graphicsQueueIdx].fences) {
    if (pair.second > frame) {
      return true;
    }

    vkWaitForFences(devInternal->device, 1, &pair.first, VK_TRUE, -1);
  }

  return true;
}

void
frame(Device dev)
{
  auto devInternal = (DeviceInternal*)dev;

  // TODO: Since a single fence only covers submitted commands to a single
  // queue,
  //       we will need to submit fences to all active queues

  // NOTE:
  // There can be multiple active fences in one frame for a queue. The code
  // below makes sure that resources are freed after the last set fence of a
  // frame (assuming frames are always increasing).
  devInternal->frame++;
  auto fence = devInternal->fenceAllocator.getFence(devInternal->frame);
  vkQueueSubmit(devInternal->queues[devInternal->graphicsQueueIdx].queue,
                0,
                nullptr,
                fence);
  devInternal->queues[devInternal->graphicsQueueIdx].fences.push_back(
    { fence, devInternal->frame });

  uint64_t lastPopped = 0;

  while (!devInternal->queues[devInternal->graphicsQueueIdx].fences.empty() &&
         vkGetFenceStatus(devInternal->device,
                          devInternal->queues[devInternal->graphicsQueueIdx]
                            .fences.front()
                            .first) != VK_NOT_READY) {

    auto popped =
      devInternal->queues[devInternal->graphicsQueueIdx].fences.front().second;
    devInternal->queues[devInternal->graphicsQueueIdx].fences.pop_front();

    if (lastPopped == popped)
      continue;

    devInternal->cmdBufferAllocator.freeResources(lastPopped);
    devInternal->fenceAllocator.freeResources(lastPopped);
    devInternal->dsetAllocator.freeResources(lastPopped);
    devInternal->semaphoreAllocator.freeResources(lastPopped);

    while (!devInternal->buffers.empty() &&
           devInternal->buffers.front().second <= lastPopped) {
      auto bufferInternal = (BufferInternal*)devInternal->buffers.front().first;
      vkDestroyBuffer(devInternal->device, bufferInternal->buffer, nullptr);
      vmaFreeMemory(devInternal->vmaAllocator, bufferInternal->allocation);
      devInternal->buffers.pop_front();
      delete bufferInternal;
    }

    while (!devInternal->textures.empty() &&
           devInternal->textures.front().second <= lastPopped) {
      auto textureInternal =
        (TextureInternal*)devInternal->textures.front().first;
      vkDestroyImageView(devInternal->device, textureInternal->view, nullptr);
      vkDestroyImage(devInternal->device, textureInternal->image, nullptr);
      vmaFreeMemory(devInternal->vmaAllocator, textureInternal->allocation);
      devInternal->textures.pop_front();
      delete textureInternal;
    }

    while (!devInternal->swapchains.empty() &&
           devInternal->swapchains.front().second <= lastPopped) {
      auto swapchainInternal =
        (SwapchainInternal*)devInternal->swapchains.front().first;
      for (auto texture : swapchainInternal->textures) {
        auto textureInternal = (TextureInternal*)texture;
        vkDestroyImageView(devInternal->device, textureInternal->view, nullptr);
        delete textureInternal;
      }
      vkDestroySwapchainKHR(
        devInternal->device, swapchainInternal->swapchain, nullptr);
      vkDestroySurfaceKHR(
        devInternal->instance, swapchainInternal->surface, nullptr);
      devInternal->swapchains.pop_front();
      delete swapchainInternal;
    }

    lastPopped = popped;
  }
}
