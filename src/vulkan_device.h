#pragma once

#include "cmd_buffer.h"
#include "common.h"
#include "device.h"
#include "vulkan_resources.h"

#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

namespace {

VkAccessFlags const writeMask =
  VK_ACCESS_SHADER_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
  VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT |
  VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_MEMORY_WRITE_BIT;

}

struct AccessScope
{
  VkPipelineStageFlags stageFlags = 0;
  VkAccessFlags accessFlags = 0;
  VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  VkImageLayout finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;

  inline bool HasWriteFlags() const { return (accessFlags & writeMask) > 0; }
  inline bool HasLayoutChange() const { return initialLayout != finalLayout; }
  inline bool ReadOnly() const
  {
    return !HasWriteFlags() && !HasLayoutChange();
  }

  static inline AccessScope None()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    scope.accessFlags = 0;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    scope.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope ColorOutputAttachment()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    scope.accessFlags = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    scope.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    return scope;
  }

  static inline AccessScope DepthStencilAttachment()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT |
                       VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    scope.accessFlags = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
                        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    scope.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    return scope;
  }

  inline bool IsAttachmentAccess()
  {
    VkAccessFlags const attachmentMask =
      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
      VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
      VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    return (accessFlags & attachmentMask) > 0;
  }

  static inline AccessScope Sampled(VkPipelineStageFlags stage)
  {
    AccessScope scope;
    scope.stageFlags = stage;
    scope.accessFlags = VK_ACCESS_SHADER_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    scope.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    return scope;
  }

  static inline AccessScope PresentSrc()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    scope.accessFlags = 0;
    scope.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    scope.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    return scope;
  }

  static inline AccessScope BufferTransferSrc()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
    scope.accessFlags = VK_ACCESS_TRANSFER_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    scope.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope BufferTransferDst()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
    scope.accessFlags = VK_ACCESS_TRANSFER_WRITE_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    scope.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope TextureTransferSrc()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
    scope.accessFlags = VK_ACCESS_TRANSFER_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    scope.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    return scope;
  }

  static inline AccessScope TextureTransferDst()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
    scope.accessFlags = VK_ACCESS_TRANSFER_WRITE_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    scope.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    return scope;
  }

  static inline AccessScope IndexBuffer()
  {
    AccessScope scope;
    scope.stageFlags =
      VK_PIPELINE_STAGE_VERTEX_INPUT_BIT | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
    scope.accessFlags = VK_ACCESS_INDEX_READ_BIT;
    return scope;
  }

  static inline AccessScope VertexBuffer()
  {
    AccessScope scope;
    scope.stageFlags =
      VK_PIPELINE_STAGE_VERTEX_INPUT_BIT | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
    scope.accessFlags = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope IndirectBuffer()
  {
    AccessScope scope;
    scope.stageFlags = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
    scope.accessFlags = VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope UniformTexelBuffer(VkPipelineStageFlags stage)
  {
    AccessScope scope;
    scope.stageFlags = stage;
    scope.accessFlags = VK_ACCESS_SHADER_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope UniformBuffer(VkPipelineStageFlags stage)
  {
    AccessScope scope;
    scope.stageFlags = stage;
    scope.accessFlags = VK_ACCESS_UNIFORM_READ_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope StorageTexelBuffer(VkPipelineStageFlags stage)
  {
    AccessScope scope;
    scope.stageFlags = stage;
    scope.accessFlags = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }

  static inline AccessScope StorageBuffer(VkPipelineStageFlags stage)
  {
    AccessScope scope;
    scope.stageFlags = stage;
    scope.accessFlags = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
    scope.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    return scope;
  }
};

class VulkanDevice;

struct VulkanCmdBufferData
{};

class VulkanCmdBuffer : CmdBuffer
{
public:
  friend VulkanDevice;

  VulkanCmdBuffer(VulkanDevice* device_, VkCommandBuffer cmdBuffer_)
    : device(device_)
    , cmdBuffer(cmdBuffer_)
  {}

  void Copy(Buffer dst, Buffer src) override;
  void CopyBufferToTexture(Texture dst, Buffer src) override;

  void BufferBarrier(BufferBarrierInfo const& info) override;
  void TextureBarrier(TextureBarrierInfo const& info) override;

  void BeginRenderPass(RenderPassBeginInfo const& beginInfo) override;

  void BindVertexBuffer(Buffer vertex_buffer, uint64_t offset) override;
  void BindIndexBuffer(Buffer index_buffer) override;

  void BindUniformBuffer(Buffer buffer,
                         uint32_t set,
                         uint32_t binding,
                         uint32_t offset,
                         uint32_t range) override;
  void BindStorageBuffer(Buffer buffer,
                         uint32_t set,
                         uint32_t binding,
                         uint32_t offset,
                         uint32_t range) override;
  void BindSampler(uint32_t set, uint32_t binding) override;
  void BindSampledTexture(Texture texture,
                          uint32_t set,
                          uint32_t binding) override;

  void SetPipelineState(PipelineState pipelineState) override;
  void Draw(uint32_t cnt) override;
  void DrawIndexed(uint32_t cnt) override;
  void Dispatch(uint32_t x, uint32_t y, uint32_t z) override;

  void EndRenderPass() override;

private:
  VulkanDevice* device = nullptr;
  VkCommandBuffer cmdBuffer = VK_NULL_HANDLE;

  struct Descriptor
  {
    VkDescriptorBufferInfo bufferInfo;
    uint32_t dynamicOffset;
    VkDescriptorImageInfo imageInfo;
  };

  struct Set
  {
    Descriptor bindings[8];
    VkDescriptorSet set;
    bool dirty;
    bool dynamicOffsetsDirty;
  };

  void flushDescriptorSets(VkPipelineBindPoint bindPoint);

  struct CmdBufferState
  {
    VkRenderPass renderPass = VK_NULL_HANDLE;
    uint32_t subpass = 0;
    PipelineLayout pipelineLayout = {};
    Set sets[8];
  } cmdBufferState;
};

class VulkanDevice : public Device
{
public:
  friend VulkanCmdBuffer;

  std::pair<Buffer, void*> CreateBuffer(
    BufferCreateInfo const& createInfo) override;

  Texture CreateTexture(TextureCreateInfo const& createInfo) override;
  Swapchain CreateSwapchain(SwapchainCreateInfo const& createInfo) override;

  bool AquireNext(Swapchain swapchain, Texture* texture);
  bool Present(Swapchain swapchain);

  void Release(Buffer buffer) override;
  void Release(Swapchain swapchain) override;
  void Release(Texture texture);

  void Recycle() override;

  CmdBuffer* GetCmdBuffer() override;
  Ticket Submit(CmdBuffer* cmdBuffer) override;
  void Wait(Ticket ticket) override;

  VulkanDevice();
  ~VulkanDevice();

private:
  struct Properties
  {
    Properties() = default;
    Properties(VkPhysicalDevice physicalDevice);

    uint32_t GetGrahicsQueueFamiliyIdx();
    bool HasGraphicsSupport();

    VkPhysicalDeviceProperties device = {};
    VkPhysicalDeviceFeatures features = {};
    VkPhysicalDeviceMemoryProperties memory = {};
    std::vector<VkQueueFamilyProperties> queueFamilies = {};
  };

  enum ResourceType
  {
    BUFFER,
    TEXTURE,
    SWAPCHAIN,
  };

  struct Trash
  {
    struct Resource
    {

      void* resource;
      ResourceType type;
    };

    enum
    {
      RING_BUFFER_SIZE = 1024
    };

    uint64_t start = 0;
    uint64_t cnt = 0;

    Resource resources[RING_BUFFER_SIZE] = {};

    VkFence fence = VK_NULL_HANDLE;
    uint64_t fencedResCnt = 0;
  };

  struct BufferInfo
  {
    BufferCreateInfo desc;
    VkDeviceSize size;
    VmaAllocation allocation;
    AccessScope accessScope;
    VkBuffer buffer;

    VkEvent event = VK_NULL_HANDLE;
    VkSemaphore sem = VK_NULL_HANDLE;
    uint32_t queueCnt = 1;
  };

  struct TextureInfo
  {
    VkDeviceSize size;
    VmaAllocation allocation;
    AccessScope accessScope;
    VkImage image;
    VkImageView view;
    TextureCreateInfo desc;
    VkImageSubresourceRange subresource;

    VkEvent event = VK_NULL_HANDLE;
    VkSemaphore sem = VK_NULL_HANDLE;
    uint32_t submitTypeCnt = 1;
  };

  struct SwapchainInfo
  {
    VkSwapchainKHR swapchain;
    VkSurfaceKHR surface;
    std::vector<Texture> textures;
    uint32_t nextTextureIdx;
  };

  Properties props = {};
  VkInstance instance = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  VkQueue queue = VK_NULL_HANDLE;
#ifdef _DEBUG
  VkDebugReportCallbackEXT callback;
#endif

  VmaAllocator vmaAllocator;
  StaticResources staticResources;
  ResourceArenaAllocator arena;
  ResourceAllocator allocator;
  VkCommandPool cmdPool = VK_NULL_HANDLE;

  uint64_t ticketCounter = 0;
  struct TicketFence
  {
    uint64_t ticket;
    VkFence fence;
  };
  std::queue<TicketFence> ticketFences;

  std::vector<BufferInfo*> buffers = {};
  std::vector<TextureInfo*> textures = {};
  std::vector<SwapchainInfo*> swapchains = {};

  Trash trash = {};

  CmdBuffer* AllocateCmdBuffer();

  void CreateResources();
  void DestroyResources();
};
