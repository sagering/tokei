#include "vulkan_device.h"

#include "common.h"
#include "vulkan_types.h"

#define VOLK_IMPLEMENTATION
#include <volk/volk.h>
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#include <assert.h>
#include <iostream>

Device*
Device::Create()
{
  return new VulkanDevice();
}

uint32_t
FindMemoryTypeIdx(const VkMemoryRequirements& memoryRequirements,
                  const VkPhysicalDeviceMemoryProperties& memoryProperties,
                  const VkMemoryPropertyFlags& propertyFlags)
{
  for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {
    if (memoryRequirements.memoryTypeBits & (1 << i) &&
        (memoryProperties.memoryTypes[i].propertyFlags & propertyFlags) ==
          propertyFlags) {
      return i;
    }
  }

  return -1;
}

VkSurfaceKHR
CreateSurface(VkInstance instance, void* windowHandle)
{
  VkWin32SurfaceCreateInfoKHR createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.pNext = nullptr;
  createInfo.flags = 0;
  createInfo.hinstance = GetModuleHandle(nullptr);
  createInfo.hwnd = (HWND)windowHandle;

  VkSurfaceKHR surface = VK_NULL_HANDLE;

  vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface);
  return surface;
}

std::pair<Buffer, void*>
VulkanDevice::CreateBuffer(BufferCreateInfo const& createInfo)
{
  VkBufferUsageFlags usage{ createInfo.usageFlags };

  VkBufferCreateInfo bufferCreateInfo = {
    VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO
  };
  bufferCreateInfo.size = createInfo.size;
  bufferCreateInfo.usage = usage;

  VmaAllocationCreateInfo allocCreateInfo = {};
  allocCreateInfo.usage = static_cast<VmaMemoryUsage>(createInfo.memoryUsage);
  allocCreateInfo.flags =
    VMA_ALLOCATION_CREATE_MAPPED_BIT; // automatically maps memory

  VkBuffer buffer;
  VmaAllocation allocation = {};
  VmaAllocationInfo allocInfo = {};

  vmaCreateBuffer(vmaAllocator,
                  &bufferCreateInfo,
                  &allocCreateInfo,
                  &buffer,
                  &allocation,
                  &allocInfo);

  auto bufferInfo =
    new BufferInfo{ createInfo, createInfo.size, allocation, {}, buffer };
  buffers.push_back(bufferInfo);

  return { (Buffer)bufferInfo, allocInfo.pMappedData };
}

VkImageAspectFlags
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

Texture
VulkanDevice::CreateTexture(TextureCreateInfo const& desc)
{
  VkFormat format = GetVkFormat(desc.format);
  VkImageType imageType = VK_IMAGE_TYPE_2D;
  VkImageViewType imageViewType = VK_IMAGE_VIEW_TYPE_2D;

  // TODO: replace wonky this derivation of image type
  if (desc.height == 1 && desc.depth == 1) {
    imageType = VK_IMAGE_TYPE_1D;
    imageViewType = VK_IMAGE_VIEW_TYPE_1D;
  } else if (desc.depth > 1) {
    imageType = VK_IMAGE_TYPE_3D;
    imageViewType = VK_IMAGE_VIEW_TYPE_3D;
  }

  VkExtent3D extent = { 1, 1, 1 };

  switch (imageType) {
    case VK_IMAGE_TYPE_1D:
      extent.width = desc.width;
      break;
    case VK_IMAGE_TYPE_2D:
      extent.width = desc.width;
      extent.height = desc.height;
      break;
    case VK_IMAGE_TYPE_3D:
      extent.width = desc.width;
      extent.height = desc.height;
      extent.depth = desc.depth;
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
  VkImageUsageFlags usage = desc.usageFlags;

  auto imageCreateInfo = vkiImageCreateInfo(imageType,
                                            format,
                                            extent,
                                            desc.mipLevels,
                                            desc.layers,
                                            VK_SAMPLE_COUNT_1_BIT,
                                            VK_IMAGE_TILING_OPTIMAL,
                                            usage,
                                            VK_SHARING_MODE_EXCLUSIVE,
                                            0,
                                            nullptr,
                                            VK_IMAGE_LAYOUT_UNDEFINED);

  vmaCreateImage(vmaAllocator,
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
  subresource.levelCount = desc.mipLevels;
  subresource.layerCount = desc.layers;

  // view is the whole image
  auto imageViewCreateInfo = vkiImageViewCreateInfo(
    image, imageViewType, format, componentMapping, subresource);

  VkImageView view = VK_NULL_HANDLE;
  vkCreateImageView(device, &imageViewCreateInfo, nullptr, &view);

  auto info = new TextureInfo{};
  info->desc = desc;
  info->image = image;
  info->view = view;
  info->allocation = allocation;
  info->size = allocInfo.size;
  info->subresource = subresource;
  info->accessScope = { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                        0,
                        VK_IMAGE_LAYOUT_UNDEFINED };

  textures.push_back(info);
  return (Texture)info;
}

Swapchain
VulkanDevice::CreateSwapchain(SwapchainCreateInfo const& createInfo)
{
  VkSurfaceKHR surface = VK_NULL_HANDLE;

  if (createInfo.oldSwapchain != nullptr) {
    auto oldSwapchain = (SwapchainInfo*)createInfo.oldSwapchain;
    surface = oldSwapchain->surface;
    oldSwapchain->surface = VK_NULL_HANDLE;
  } else {
    surface = CreateSurface(instance, createInfo.platformHandle);
  }

  VkBool32 supported;
  vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, 0, surface, &supported);

  VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  VkSurfaceTransformFlagBitsKHR transform =
    VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  VkCompositeAlphaFlagBitsKHR compositeAlpha =
    VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  VkPresentModeKHR presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
  VkBool32 clipped = VK_TRUE;

  {
    uint32_t formatCnt = 0;
    std::vector<VkSurfaceFormatKHR> surfaceFormats;
    vkGetPhysicalDeviceSurfaceFormatsKHR(
      physicalDevice, surface, &formatCnt, nullptr);
    surfaceFormats.resize(formatCnt);
    vkGetPhysicalDeviceSurfaceFormatsKHR(
      physicalDevice, surface, &formatCnt, surfaceFormats.data());
  }

  {
    uint32_t presentModeCnt = 0;
    std::vector<VkPresentModeKHR> presentModes;
    vkGetPhysicalDeviceSurfacePresentModesKHR(
      physicalDevice, surface, &presentModeCnt, nullptr);
    presentModes.resize(presentModeCnt);
    vkGetPhysicalDeviceSurfacePresentModesKHR(
      physicalDevice, surface, &presentModeCnt, presentModes.data());
  }

  {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
      physicalDevice, surface, &capabilities);

    transform = capabilities.currentTransform;
  }

  auto swapchainCreateInfo =
    vkiSwapchainCreateInfoKHR(surface,
                              createInfo.textureCnt,
                              GetVkFormat(createInfo.format),
                              colorSpace,
                              { createInfo.width, createInfo.height },
                              1,
                              VkImageUsageFlags{ createInfo.usageFlags },
                              VK_SHARING_MODE_EXCLUSIVE,
                              1,
                              nullptr,
                              transform,
                              compositeAlpha,
                              presentMode,
                              clipped,
                              VK_NULL_HANDLE);

  VkSwapchainKHR swapchain = VK_NULL_HANDLE;
  vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain);

  std::vector<VkImage> swapchainImages;
  uint32_t imageCnt;

  vkGetSwapchainImagesKHR(device, swapchain, &imageCnt, nullptr);
  swapchainImages.resize(imageCnt);

  vkGetSwapchainImagesKHR(device, swapchain, &imageCnt, swapchainImages.data());

  swapchainImages.resize(imageCnt);

  auto swapchainInfo = new SwapchainInfo{};
  swapchainInfo->surface = surface;
  swapchainInfo->swapchain = swapchain;

  for (uint32_t i = 0; i < imageCnt; ++i) {
    auto info = new TextureInfo{};
    info->image = swapchainImages[i];
    info->size = 0;
    info->accessScope = { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                          0,
                          VK_IMAGE_LAYOUT_UNDEFINED };
    info->desc.width = createInfo.width;
    info->desc.height = createInfo.height;
    info->desc.format = createInfo.format;
    info->desc.usageFlags = createInfo.usageFlags;
    info->desc.depth = 1;
    info->desc.layers = 1;
    info->desc.mipLevels = 1;
    info->desc.name = createInfo.name;
    info->subresource.aspectMask =
      GetImageAspectFlags(GetVkFormat(info->desc.format));
    info->subresource.baseMipLevel = 0;
    info->subresource.baseArrayLayer = 0;
    info->subresource.levelCount = info->desc.mipLevels;
    info->subresource.layerCount = info->desc.layers;

    info->submitTypeCnt = 3;

    auto imageViewCreateInfo =
      vkiImageViewCreateInfo(info->image,
                             VK_IMAGE_VIEW_TYPE_2D,
                             GetVkFormat(info->desc.format),
                             { VK_COMPONENT_SWIZZLE_IDENTITY,
                               VK_COMPONENT_SWIZZLE_IDENTITY,
                               VK_COMPONENT_SWIZZLE_IDENTITY,
                               VK_COMPONENT_SWIZZLE_IDENTITY },
                             { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

    vkCreateImageView(device, &imageViewCreateInfo, nullptr, &info->view);

    textures.push_back(info);
    swapchainInfo->textures.push_back((Texture)info);
  }

  swapchains.push_back(swapchainInfo);
  return (Swapchain)swapchainInfo;
}

bool
VulkanDevice::AquireNext(Swapchain swapchain, Texture* texture)
{
  auto info = (SwapchainInfo*)swapchain;
  auto sem = AllocateSemaphore(&allocator);

  auto result = vkAcquireNextImageKHR(
    device, info->swapchain, -1, sem, VK_NULL_HANDLE, &info->nextTextureIdx);

  auto textureInfo = (TextureInfo*)info->textures[info->nextTextureIdx];

  if (textureInfo->submitTypeCnt > 1) {
    assert(textureInfo->sem == VK_NULL_HANDLE);

    textureInfo->sem = sem;

    // layout not changed by "aquire" op
    textureInfo->accessScope.stageFlags = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
    textureInfo->accessScope.accessFlags = VK_ACCESS_MEMORY_WRITE_BIT;
  }

  *texture = (Texture)textureInfo;

  return result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR;
}

bool
VulkanDevice::Present(Swapchain swapchain)
{
  auto info = (SwapchainInfo*)swapchain;
  VkResult result;

  auto textureInfo = (TextureInfo*)info->textures[info->nextTextureIdx];

  auto presentInfo = vkiPresentInfoKHR(
    0, nullptr, 1, &info->swapchain, &info->nextTextureIdx, &result);

  VkSemaphore sem = VK_NULL_HANDLE;

  if (textureInfo->submitTypeCnt > 1) {
    assert(textureInfo->sem != VK_NULL_HANDLE);
    sem = textureInfo->sem;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &sem;
    ReleaseSemaphore(&allocator, textureInfo->sem);
    textureInfo->sem = VK_NULL_HANDLE;
  }

  vkQueuePresentKHR(queue, &presentInfo);

  return result == VK_SUCCESS;
}

void
VulkanDevice::Release(Buffer buffer)
{
  auto i = (trash.start + trash.cnt) % Trash::RING_BUFFER_SIZE;
  trash.resources[i].resource = buffer;
  trash.resources[i].type = ResourceType::BUFFER;
  ++trash.cnt;
}

void
VulkanDevice::Release(Swapchain swapchain)
{
  auto i = (trash.start + trash.cnt) % Trash::RING_BUFFER_SIZE;
  trash.resources[i].resource = swapchain;
  trash.resources[i].type = ResourceType::SWAPCHAIN;
  ++trash.cnt;
}

void
VulkanDevice::Recycle()
{
  if (cmdPool != VK_NULL_HANDLE) {
    cmdPool = VK_NULL_HANDLE;
  }

  // TODO: we are doing three separate queue submission for each kind of
  // allocator; these should be grouped into one submission
  ClaimResources(&allocator);
  ClaimResources(&arena);

  if (trash.fence != VK_NULL_HANDLE &&
      vkGetFenceStatus(device, trash.fence) == VK_NOT_READY) {
    return;
  }

  if (trash.fence != VK_NULL_HANDLE) {
    ReleaseFence(&allocator, trash.fence);
    trash.fence = VK_NULL_HANDLE;

    for (uint64_t i = trash.start; i < trash.start + trash.fencedResCnt; ++i) {
      auto const& res = trash.resources[i % Trash::RING_BUFFER_SIZE];
      switch (res.type) {
        case ResourceType::BUFFER: {
          auto bufferInfo = (BufferInfo*)res.resource;
          vkDestroyBuffer(device, bufferInfo->buffer, nullptr);

          if (bufferInfo->event) {
            ReleaseEvent(&allocator, bufferInfo->event);
          }

          vmaFreeMemory(vmaAllocator, bufferInfo->allocation);

          for (auto it = buffers.begin(); it != buffers.end(); ++it) {
            if (*it == bufferInfo) {
              buffers.erase(it);
              break;
            }
          }

          delete bufferInfo;
          break;
        }
        case ResourceType::TEXTURE: {
          break;
        }
        case ResourceType::SWAPCHAIN: {
          auto info = (SwapchainInfo*)res.resource;

          for (auto texture : info->textures) {
            auto textureInfo = (TextureInfo*)texture;
            vkDestroyImageView(device, textureInfo->view, nullptr);
            delete textureInfo;
          }

          vkDestroySwapchainKHR(device, info->swapchain, nullptr);
          vkDestroySurfaceKHR(instance, info->surface, nullptr);
          delete info;
          break;
        }
        default:
          break;
      }
    }

    trash.start += trash.fencedResCnt;
    trash.cnt -= trash.fencedResCnt;
    trash.fencedResCnt = 0;
  }

  if (trash.cnt > 0) {
    trash.fence = AllocateFence(&allocator);
    trash.fencedResCnt = trash.cnt;

    vkQueueSubmit(queue, 0, nullptr, trash.fence);
  }
}

CmdBuffer*
VulkanDevice::AllocateCmdBuffer()
{
  if (!cmdPool) {
    cmdPool = AllocateCommandPool(&arena, props.GetGrahicsQueueFamiliyIdx());
  }

  auto allocInfo =
    vkiCommandBufferAllocateInfo(cmdPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1);

  // TODO: not reusing command buffers is slow (but convenient)
  VkCommandBuffer cmdBuffer = VK_NULL_HANDLE;
  vkAllocateCommandBuffers(device, &allocInfo, &cmdBuffer);

  auto beginInfo = vkiCommandBufferBeginInfo(nullptr);
  vkBeginCommandBuffer(cmdBuffer, &beginInfo);

  return new VulkanCmdBuffer(this, cmdBuffer);
}

CmdBuffer*
VulkanDevice::GetCmdBuffer()
{
  return AllocateCmdBuffer();
}

void
VulkanDevice::Submit(CmdBuffer* cmdBuffer_)
{
  VulkanCmdBuffer* cmdBuffer = (VulkanCmdBuffer*)cmdBuffer_;

  std::vector<VkSemaphore> waitSemaphores = {};
  std::vector<VkPipelineStageFlags> waitStages = {};
  std::vector<VkSemaphore> signalSemaphores = {};

  vkEndCommandBuffer(cmdBuffer->cmdBuffer);

  auto submitInfo =
    vkiSubmitInfo(static_cast<uint32_t>(waitSemaphores.size()),
                  waitSemaphores.data(),
                  waitStages.data(),
                  1,
                  &cmdBuffer->cmdBuffer,
                  static_cast<uint32_t>(signalSemaphores.size()),
                  signalSemaphores.data());

  vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
  delete cmdBuffer;
}

VulkanDevice::VulkanDevice()
{
  CreateResources();
  allocator = {};
  allocator.device = device;
  allocator.queue = queue;

  staticResources = {};
  staticResources.device = device;

  arena = {};
  arena.device = device;
  arena.queue = queue;
  arena.staticResources = &staticResources;
  arena.resourceAllocator = &allocator;
}

VulkanDevice::~VulkanDevice()
{
  DestroyResources();
}

VulkanDevice::Properties::Properties(VkPhysicalDevice physicalDevice)
{
  vkGetPhysicalDeviceProperties(physicalDevice, &device);
  vkGetPhysicalDeviceFeatures(physicalDevice, &features);
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memory);

  uint32_t count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
  queueFamilies.resize(count);
  vkGetPhysicalDeviceQueueFamilyProperties(
    physicalDevice, &count, queueFamilies.data());
}

uint32_t
VulkanDevice::Properties::GetGrahicsQueueFamiliyIdx()
{
  for (uint32_t idx = 0; idx < queueFamilies.size(); ++idx) {
    if (queueFamilies[idx].queueCount == 0)
      continue;
    if (queueFamilies[idx].queueFlags & VK_QUEUE_GRAPHICS_BIT)
      return idx;
  }
  return -1;
}

bool
VulkanDevice::Properties::HasGraphicsSupport()
{
  return GetGrahicsQueueFamiliyIdx() != (uint32_t)-1;
}

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

void
VulkanDevice::CreateResources()
{
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

  vkCreateInstance(&instInfo, nullptr, &instance);

  assert(instance != VK_NULL_HANDLE);

  volkLoadInstance(instance);

#ifdef _DEBUG
  auto createInfo =
    vkiDebugReportCallbackCreateInfoEXT(debugReportCallback, nullptr);
  createInfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT |
                     VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
                     VK_DEBUG_REPORT_ERROR_BIT_EXT;
  vkCreateDebugReportCallbackEXT(instance, &createInfo, 0, &callback);
#endif // DEBUG

  // device
  char const* deviceExtensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

  uint32_t physicalDeviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
  std::vector<VkPhysicalDevice> physicalsDevices(physicalDeviceCount);
  vkEnumeratePhysicalDevices(
    instance, &physicalDeviceCount, physicalsDevices.data());

  for (const auto& dev : physicalsDevices) {
    physicalDevice = dev;
    props = Properties(dev);
    if (props.HasGraphicsSupport()) {
      break;
    }
  }

  float queuePriority = 1.0f;
  uint32_t queueFamiliyIdx = props.GetGrahicsQueueFamiliyIdx();

  VkDeviceQueueCreateInfo queueCreateInfo =
    vkiDeviceQueueCreateInfo(queueFamiliyIdx, 1, &queuePriority);

  VkPhysicalDeviceFeatures deviceFeatures = {};
  deviceFeatures.textureCompressionBC = true;
  deviceFeatures.fillModeNonSolid = true;
  deviceFeatures.multiDrawIndirect = true;

  VkDeviceCreateInfo deviceCreateInfo =
    vkiDeviceCreateInfo(1,
                        &queueCreateInfo,
                        0,
                        nullptr,
                        sizeof(deviceExtensions) / sizeof(deviceExtensions[0]),
                        deviceExtensions,
                        &deviceFeatures);

  vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);

  volkLoadDevice(device);

  // queue
  vkGetDeviceQueue(device, queueFamiliyIdx, 0, &queue);

  VmaAllocatorCreateInfo allocatorInfo = {};
  allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_1;
  allocatorInfo.physicalDevice = physicalDevice;
  allocatorInfo.device = device;
  allocatorInfo.instance = instance;

  vmaCreateAllocator(&allocatorInfo, &vmaAllocator);
}

void
VulkanDevice::DestroyResources()
{
  vmaDestroyAllocator(vmaAllocator);
  vkDestroyDevice(device, nullptr);
#ifdef _DEBUG
  vkDestroyDebugReportCallbackEXT(instance, callback, nullptr);
#endif // DEBUG
  vkDestroyInstance(instance, nullptr);
}
