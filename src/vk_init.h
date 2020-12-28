#ifndef VK_INIT_H_
#define VK_INIT_H_

#include <vulkan/vulkan_core.h>

inline VkApplicationInfo vkiApplicationInfo(const char* pApplicationName,
                                            uint32_t applicationVersion,
                                            const char* pEngineName,
                                            uint32_t engineVersion,
                                            uint32_t apiVersion) {
  VkApplicationInfo ApplicationInfo = {};
  ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  ApplicationInfo.pNext = nullptr;
  ApplicationInfo.pApplicationName = pApplicationName;
  ApplicationInfo.applicationVersion = applicationVersion;
  ApplicationInfo.pEngineName = pEngineName;
  ApplicationInfo.engineVersion = engineVersion;
  ApplicationInfo.apiVersion = apiVersion;
  return ApplicationInfo;
}

inline VkInstanceCreateInfo vkiInstanceCreateInfo(
    const VkApplicationInfo* pApplicationInfo, uint32_t enabledLayerCount,
    const char* const* ppEnabledLayerNames, uint32_t enabledExtensionCount,
    const char* const* ppEnabledExtensionNames) {
  VkInstanceCreateInfo InstanceCreateInfo = {};
  InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  InstanceCreateInfo.pNext = nullptr;
  InstanceCreateInfo.flags = 0;
  InstanceCreateInfo.pApplicationInfo = pApplicationInfo;
  InstanceCreateInfo.enabledLayerCount = enabledLayerCount;
  InstanceCreateInfo.ppEnabledLayerNames = ppEnabledLayerNames;
  InstanceCreateInfo.enabledExtensionCount = enabledExtensionCount;
  InstanceCreateInfo.ppEnabledExtensionNames = ppEnabledExtensionNames;
  return InstanceCreateInfo;
}

inline VkAllocationCallbacks vkiAllocationCallbacks(
    void* pUserData, PFN_vkAllocationFunction pfnAllocation,
    PFN_vkReallocationFunction pfnReallocation, PFN_vkFreeFunction pfnFree,
    PFN_vkInternalAllocationNotification pfnInternalAllocation,
    PFN_vkInternalFreeNotification pfnInternalFree) {
  VkAllocationCallbacks AllocationCallbacks = {};
  AllocationCallbacks.pUserData = pUserData;
  AllocationCallbacks.pfnAllocation = pfnAllocation;
  AllocationCallbacks.pfnReallocation = pfnReallocation;
  AllocationCallbacks.pfnFree = pfnFree;
  AllocationCallbacks.pfnInternalAllocation = pfnInternalAllocation;
  AllocationCallbacks.pfnInternalFree = pfnInternalFree;
  return AllocationCallbacks;
}

inline VkPhysicalDeviceFeatures vkiPhysicalDeviceFeatures(
    VkBool32 robustBufferAccess, VkBool32 fullDrawIndexUint32,
    VkBool32 imageCubeArray, VkBool32 independentBlend, VkBool32 geometryShader,
    VkBool32 tessellationShader, VkBool32 sampleRateShading,
    VkBool32 dualSrcBlend, VkBool32 logicOp, VkBool32 multiDrawIndirect,
    VkBool32 drawIndirectFirstInstance, VkBool32 depthClamp,
    VkBool32 depthBiasClamp, VkBool32 fillModeNonSolid, VkBool32 depthBounds,
    VkBool32 wideLines, VkBool32 largePoints, VkBool32 alphaToOne,
    VkBool32 multiViewport, VkBool32 samplerAnisotropy,
    VkBool32 textureCompressionETC2, VkBool32 textureCompressionASTC_LDR,
    VkBool32 textureCompressionBC, VkBool32 occlusionQueryPrecise,
    VkBool32 pipelineStatisticsQuery, VkBool32 vertexPipelineStoresAndAtomics,
    VkBool32 fragmentStoresAndAtomics,
    VkBool32 shaderTessellationAndGeometryPointSize,
    VkBool32 shaderImageGatherExtended,
    VkBool32 shaderStorageImageExtendedFormats,
    VkBool32 shaderStorageImageMultisample,
    VkBool32 shaderStorageImageReadWithoutFormat,
    VkBool32 shaderStorageImageWriteWithoutFormat,
    VkBool32 shaderUniformBufferArrayDynamicIndexing,
    VkBool32 shaderSampledImageArrayDynamicIndexing,
    VkBool32 shaderStorageBufferArrayDynamicIndexing,
    VkBool32 shaderStorageImageArrayDynamicIndexing,
    VkBool32 shaderClipDistance, VkBool32 shaderCullDistance,
    VkBool32 shaderFloat64, VkBool32 shaderInt64, VkBool32 shaderInt16,
    VkBool32 shaderResourceResidency, VkBool32 shaderResourceMinLod,
    VkBool32 sparseBinding, VkBool32 sparseResidencyBuffer,
    VkBool32 sparseResidencyImage2D, VkBool32 sparseResidencyImage3D,
    VkBool32 sparseResidency2Samples, VkBool32 sparseResidency4Samples,
    VkBool32 sparseResidency8Samples, VkBool32 sparseResidency16Samples,
    VkBool32 sparseResidencyAliased, VkBool32 variableMultisampleRate,
    VkBool32 inheritedQueries) {
  VkPhysicalDeviceFeatures PhysicalDeviceFeatures = {};
  PhysicalDeviceFeatures.robustBufferAccess = robustBufferAccess;
  PhysicalDeviceFeatures.fullDrawIndexUint32 = fullDrawIndexUint32;
  PhysicalDeviceFeatures.imageCubeArray = imageCubeArray;
  PhysicalDeviceFeatures.independentBlend = independentBlend;
  PhysicalDeviceFeatures.geometryShader = geometryShader;
  PhysicalDeviceFeatures.tessellationShader = tessellationShader;
  PhysicalDeviceFeatures.sampleRateShading = sampleRateShading;
  PhysicalDeviceFeatures.dualSrcBlend = dualSrcBlend;
  PhysicalDeviceFeatures.logicOp = logicOp;
  PhysicalDeviceFeatures.multiDrawIndirect = multiDrawIndirect;
  PhysicalDeviceFeatures.drawIndirectFirstInstance = drawIndirectFirstInstance;
  PhysicalDeviceFeatures.depthClamp = depthClamp;
  PhysicalDeviceFeatures.depthBiasClamp = depthBiasClamp;
  PhysicalDeviceFeatures.fillModeNonSolid = fillModeNonSolid;
  PhysicalDeviceFeatures.depthBounds = depthBounds;
  PhysicalDeviceFeatures.wideLines = wideLines;
  PhysicalDeviceFeatures.largePoints = largePoints;
  PhysicalDeviceFeatures.alphaToOne = alphaToOne;
  PhysicalDeviceFeatures.multiViewport = multiViewport;
  PhysicalDeviceFeatures.samplerAnisotropy = samplerAnisotropy;
  PhysicalDeviceFeatures.textureCompressionETC2 = textureCompressionETC2;
  PhysicalDeviceFeatures.textureCompressionASTC_LDR =
      textureCompressionASTC_LDR;
  PhysicalDeviceFeatures.textureCompressionBC = textureCompressionBC;
  PhysicalDeviceFeatures.occlusionQueryPrecise = occlusionQueryPrecise;
  PhysicalDeviceFeatures.pipelineStatisticsQuery = pipelineStatisticsQuery;
  PhysicalDeviceFeatures.vertexPipelineStoresAndAtomics =
      vertexPipelineStoresAndAtomics;
  PhysicalDeviceFeatures.fragmentStoresAndAtomics = fragmentStoresAndAtomics;
  PhysicalDeviceFeatures.shaderTessellationAndGeometryPointSize =
      shaderTessellationAndGeometryPointSize;
  PhysicalDeviceFeatures.shaderImageGatherExtended = shaderImageGatherExtended;
  PhysicalDeviceFeatures.shaderStorageImageExtendedFormats =
      shaderStorageImageExtendedFormats;
  PhysicalDeviceFeatures.shaderStorageImageMultisample =
      shaderStorageImageMultisample;
  PhysicalDeviceFeatures.shaderStorageImageReadWithoutFormat =
      shaderStorageImageReadWithoutFormat;
  PhysicalDeviceFeatures.shaderStorageImageWriteWithoutFormat =
      shaderStorageImageWriteWithoutFormat;
  PhysicalDeviceFeatures.shaderUniformBufferArrayDynamicIndexing =
      shaderUniformBufferArrayDynamicIndexing;
  PhysicalDeviceFeatures.shaderSampledImageArrayDynamicIndexing =
      shaderSampledImageArrayDynamicIndexing;
  PhysicalDeviceFeatures.shaderStorageBufferArrayDynamicIndexing =
      shaderStorageBufferArrayDynamicIndexing;
  PhysicalDeviceFeatures.shaderStorageImageArrayDynamicIndexing =
      shaderStorageImageArrayDynamicIndexing;
  PhysicalDeviceFeatures.shaderClipDistance = shaderClipDistance;
  PhysicalDeviceFeatures.shaderCullDistance = shaderCullDistance;
  PhysicalDeviceFeatures.shaderFloat64 = shaderFloat64;
  PhysicalDeviceFeatures.shaderInt64 = shaderInt64;
  PhysicalDeviceFeatures.shaderInt16 = shaderInt16;
  PhysicalDeviceFeatures.shaderResourceResidency = shaderResourceResidency;
  PhysicalDeviceFeatures.shaderResourceMinLod = shaderResourceMinLod;
  PhysicalDeviceFeatures.sparseBinding = sparseBinding;
  PhysicalDeviceFeatures.sparseResidencyBuffer = sparseResidencyBuffer;
  PhysicalDeviceFeatures.sparseResidencyImage2D = sparseResidencyImage2D;
  PhysicalDeviceFeatures.sparseResidencyImage3D = sparseResidencyImage3D;
  PhysicalDeviceFeatures.sparseResidency2Samples = sparseResidency2Samples;
  PhysicalDeviceFeatures.sparseResidency4Samples = sparseResidency4Samples;
  PhysicalDeviceFeatures.sparseResidency8Samples = sparseResidency8Samples;
  PhysicalDeviceFeatures.sparseResidency16Samples = sparseResidency16Samples;
  PhysicalDeviceFeatures.sparseResidencyAliased = sparseResidencyAliased;
  PhysicalDeviceFeatures.variableMultisampleRate = variableMultisampleRate;
  PhysicalDeviceFeatures.inheritedQueries = inheritedQueries;
  return PhysicalDeviceFeatures;
}

inline VkFormatProperties vkiFormatProperties(
    VkFormatFeatureFlags linearTilingFeatures,
    VkFormatFeatureFlags optimalTilingFeatures,
    VkFormatFeatureFlags bufferFeatures) {
  VkFormatProperties FormatProperties = {};
  FormatProperties.linearTilingFeatures = linearTilingFeatures;
  FormatProperties.optimalTilingFeatures = optimalTilingFeatures;
  FormatProperties.bufferFeatures = bufferFeatures;
  return FormatProperties;
}

inline VkExtent3D vkiExtent3D(uint32_t width, uint32_t height, uint32_t depth) {
  VkExtent3D Extent3D = {};
  Extent3D.width = width;
  Extent3D.height = height;
  Extent3D.depth = depth;
  return Extent3D;
}

inline VkImageFormatProperties vkiImageFormatProperties(
    VkExtent3D maxExtent, uint32_t maxMipLevels, uint32_t maxArrayLayers,
    VkSampleCountFlags sampleCounts, VkDeviceSize maxResourceSize) {
  VkImageFormatProperties ImageFormatProperties = {};
  ImageFormatProperties.maxExtent = maxExtent;
  ImageFormatProperties.maxMipLevels = maxMipLevels;
  ImageFormatProperties.maxArrayLayers = maxArrayLayers;
  ImageFormatProperties.sampleCounts = sampleCounts;
  ImageFormatProperties.maxResourceSize = maxResourceSize;
  return ImageFormatProperties;
}

// inline VkPhysicalDeviceLimits vkiPhysicalDeviceLimits(uint32_t
// maxImageDimension1D, uint32_t maxImageDimension2D, uint32_t
// maxImageDimension3D, uint32_t maxImageDimensionCube, uint32_t
// maxImageArrayLayers, uint32_t maxTexelBufferElements, uint32_t
// maxUniformBufferRange, uint32_t maxStorageBufferRange, uint32_t
// maxPushConstantsSize, uint32_t maxMemoryAllocationCount, uint32_t
// maxSamplerAllocationCount, VkDeviceSize bufferImageGranularity, VkDeviceSize
// sparseAddressSpaceSize, uint32_t maxBoundDescriptorSets, uint32_t
// maxPerStageDescriptorSamplers, uint32_t maxPerStageDescriptorUniformBuffers,
// uint32_t maxPerStageDescriptorStorageBuffers, uint32_t
// maxPerStageDescriptorSampledImages, uint32_t
// maxPerStageDescriptorStorageImages, uint32_t
// maxPerStageDescriptorInputAttachments, uint32_t maxPerStageResources,
// uint32_t maxDescriptorSetSamplers, uint32_t maxDescriptorSetUniformBuffers,
// uint32_t maxDescriptorSetUniformBuffersDynamic, uint32_t
// maxDescriptorSetStorageBuffers, uint32_t
// maxDescriptorSetStorageBuffersDynamic, uint32_t
// maxDescriptorSetSampledImages, uint32_t maxDescriptorSetStorageImages,
// uint32_t maxDescriptorSetInputAttachments, uint32_t maxVertexInputAttributes,
// uint32_t maxVertexInputBindings, uint32_t maxVertexInputAttributeOffset,
// uint32_t maxVertexInputBindingStride, uint32_t maxVertexOutputComponents,
// uint32_t maxTessellationGenerationLevel, uint32_t maxTessellationPatchSize,
// uint32_t maxTessellationControlPerVertexInputComponents, uint32_t
// maxTessellationControlPerVertexOutputComponents, uint32_t
// maxTessellationControlPerPatchOutputComponents, uint32_t
// maxTessellationControlTotalOutputComponents, uint32_t
// maxTessellationEvaluationInputComponents, uint32_t
// maxTessellationEvaluationOutputComponents, uint32_t
// maxGeometryShaderInvocations, uint32_t maxGeometryInputComponents, uint32_t
// maxGeometryOutputComponents, uint32_t maxGeometryOutputVertices, uint32_t
// maxGeometryTotalOutputComponents, uint32_t maxFragmentInputComponents,
// uint32_t maxFragmentOutputAttachments, uint32_t
// maxFragmentDualSrcAttachments, uint32_t maxFragmentCombinedOutputResources,
// uint32_t maxComputeSharedMemorySize, uint32_t maxComputeWorkGroupCount[3],
// uint32_t maxComputeWorkGroupInvocations, uint32_t maxComputeWorkGroupSize[3],
// uint32_t subPixelPrecisionBits, uint32_t subTexelPrecisionBits, uint32_t
// mipmapPrecisionBits, uint32_t maxDrawIndexedIndexValue, uint32_t
// maxDrawIndirectCount, float maxSamplerLodBias, float maxSamplerAnisotropy,
// uint32_t maxViewports, uint32_t maxViewportDimensions[2], float
// viewportBoundsRange[2], uint32_t viewportSubPixelBits, size_t
// minMemoryMapAlignment, VkDeviceSize minTexelBufferOffsetAlignment,
// VkDeviceSize minUniformBufferOffsetAlignment, VkDeviceSize
// minStorageBufferOffsetAlignment, int32_t minTexelOffset, uint32_t
// maxTexelOffset, int32_t minTexelGatherOffset, uint32_t maxTexelGatherOffset,
// float minInterpolationOffset, float maxInterpolationOffset, uint32_t
// subPixelInterpolationOffsetBits, uint32_t maxFramebufferWidth, uint32_t
// maxFramebufferHeight, uint32_t maxFramebufferLayers, VkSampleCountFlags
// framebufferColorSampleCounts, VkSampleCountFlags
// framebufferDepthSampleCounts, VkSampleCountFlags
// framebufferStencilSampleCounts, VkSampleCountFlags
// framebufferNoAttachmentsSampleCounts, uint32_t maxColorAttachments,
// VkSampleCountFlags sampledImageColorSampleCounts, VkSampleCountFlags
// sampledImageIntegerSampleCounts, VkSampleCountFlags
// sampledImageDepthSampleCounts, VkSampleCountFlags
// sampledImageStencilSampleCounts, VkSampleCountFlags storageImageSampleCounts,
// uint32_t maxSampleMaskWords, VkBool32 timestampComputeAndGraphics, float
// timestampPeriod, uint32_t maxClipDistances, uint32_t maxCullDistances,
// uint32_t maxCombinedClipAndCullDistances, uint32_t discreteQueuePriorities,
// float pointSizeRange[2], float lineWidthRange[2], float pointSizeGranularity,
// float lineWidthGranularity, VkBool32 strictLines, VkBool32
// standardSampleLocations, VkDeviceSize optimalBufferCopyOffsetAlignment,
// VkDeviceSize optimalBufferCopyRowPitchAlignment, VkDeviceSize
// nonCoherentAtomSize) {
//     VkPhysicalDeviceLimits PhysicalDeviceLimits = {};
//     PhysicalDeviceLimits.maxImageDimension1D = maxImageDimension1D;
//     PhysicalDeviceLimits.maxImageDimension2D = maxImageDimension2D;
//     PhysicalDeviceLimits.maxImageDimension3D = maxImageDimension3D;
//     PhysicalDeviceLimits.maxImageDimensionCube = maxImageDimensionCube;
//     PhysicalDeviceLimits.maxImageArrayLayers = maxImageArrayLayers;
//     PhysicalDeviceLimits.maxTexelBufferElements = maxTexelBufferElements;
//     PhysicalDeviceLimits.maxUniformBufferRange = maxUniformBufferRange;
//     PhysicalDeviceLimits.maxStorageBufferRange = maxStorageBufferRange;
//     PhysicalDeviceLimits.maxPushConstantsSize = maxPushConstantsSize;
//     PhysicalDeviceLimits.maxMemoryAllocationCount = maxMemoryAllocationCount;
//     PhysicalDeviceLimits.maxSamplerAllocationCount =
//     maxSamplerAllocationCount; PhysicalDeviceLimits.bufferImageGranularity =
//     bufferImageGranularity; PhysicalDeviceLimits.sparseAddressSpaceSize =
//     sparseAddressSpaceSize; PhysicalDeviceLimits.maxBoundDescriptorSets =
//     maxBoundDescriptorSets;
//     PhysicalDeviceLimits.maxPerStageDescriptorSamplers =
//     maxPerStageDescriptorSamplers;
//     PhysicalDeviceLimits.maxPerStageDescriptorUniformBuffers =
//     maxPerStageDescriptorUniformBuffers;
//     PhysicalDeviceLimits.maxPerStageDescriptorStorageBuffers =
//     maxPerStageDescriptorStorageBuffers;
//     PhysicalDeviceLimits.maxPerStageDescriptorSampledImages =
//     maxPerStageDescriptorSampledImages;
//     PhysicalDeviceLimits.maxPerStageDescriptorStorageImages =
//     maxPerStageDescriptorStorageImages;
//     PhysicalDeviceLimits.maxPerStageDescriptorInputAttachments =
//     maxPerStageDescriptorInputAttachments;
//     PhysicalDeviceLimits.maxPerStageResources = maxPerStageResources;
//     PhysicalDeviceLimits.maxDescriptorSetSamplers = maxDescriptorSetSamplers;
//     PhysicalDeviceLimits.maxDescriptorSetUniformBuffers =
//     maxDescriptorSetUniformBuffers;
//     PhysicalDeviceLimits.maxDescriptorSetUniformBuffersDynamic =
//     maxDescriptorSetUniformBuffersDynamic;
//     PhysicalDeviceLimits.maxDescriptorSetStorageBuffers =
//     maxDescriptorSetStorageBuffers;
//     PhysicalDeviceLimits.maxDescriptorSetStorageBuffersDynamic =
//     maxDescriptorSetStorageBuffersDynamic;
//     PhysicalDeviceLimits.maxDescriptorSetSampledImages =
//     maxDescriptorSetSampledImages;
//     PhysicalDeviceLimits.maxDescriptorSetStorageImages =
//     maxDescriptorSetStorageImages;
//     PhysicalDeviceLimits.maxDescriptorSetInputAttachments =
//     maxDescriptorSetInputAttachments;
//     PhysicalDeviceLimits.maxVertexInputAttributes = maxVertexInputAttributes;
//     PhysicalDeviceLimits.maxVertexInputBindings = maxVertexInputBindings;
//     PhysicalDeviceLimits.maxVertexInputAttributeOffset =
//     maxVertexInputAttributeOffset;
//     PhysicalDeviceLimits.maxVertexInputBindingStride =
//     maxVertexInputBindingStride;
//     PhysicalDeviceLimits.maxVertexOutputComponents =
//     maxVertexOutputComponents;
//     PhysicalDeviceLimits.maxTessellationGenerationLevel =
//     maxTessellationGenerationLevel;
//     PhysicalDeviceLimits.maxTessellationPatchSize = maxTessellationPatchSize;
//     PhysicalDeviceLimits.maxTessellationControlPerVertexInputComponents =
//     maxTessellationControlPerVertexInputComponents;
//     PhysicalDeviceLimits.maxTessellationControlPerVertexOutputComponents =
//     maxTessellationControlPerVertexOutputComponents;
//     PhysicalDeviceLimits.maxTessellationControlPerPatchOutputComponents =
//     maxTessellationControlPerPatchOutputComponents;
//     PhysicalDeviceLimits.maxTessellationControlTotalOutputComponents =
//     maxTessellationControlTotalOutputComponents;
//     PhysicalDeviceLimits.maxTessellationEvaluationInputComponents =
//     maxTessellationEvaluationInputComponents;
//     PhysicalDeviceLimits.maxTessellationEvaluationOutputComponents =
//     maxTessellationEvaluationOutputComponents;
//     PhysicalDeviceLimits.maxGeometryShaderInvocations =
//     maxGeometryShaderInvocations;
//     PhysicalDeviceLimits.maxGeometryInputComponents =
//     maxGeometryInputComponents;
//     PhysicalDeviceLimits.maxGeometryOutputComponents =
//     maxGeometryOutputComponents;
//     PhysicalDeviceLimits.maxGeometryOutputVertices =
//     maxGeometryOutputVertices;
//     PhysicalDeviceLimits.maxGeometryTotalOutputComponents =
//     maxGeometryTotalOutputComponents;
//     PhysicalDeviceLimits.maxFragmentInputComponents =
//     maxFragmentInputComponents;
//     PhysicalDeviceLimits.maxFragmentOutputAttachments =
//     maxFragmentOutputAttachments;
//     PhysicalDeviceLimits.maxFragmentDualSrcAttachments =
//     maxFragmentDualSrcAttachments;
//     PhysicalDeviceLimits.maxFragmentCombinedOutputResources =
//     maxFragmentCombinedOutputResources;
//     PhysicalDeviceLimits.maxComputeSharedMemorySize =
//     maxComputeSharedMemorySize;
//     PhysicalDeviceLimits.maxComputeWorkGroupCount[3] =
//     maxComputeWorkGroupCount[3];
//     PhysicalDeviceLimits.maxComputeWorkGroupInvocations =
//     maxComputeWorkGroupInvocations;
//     PhysicalDeviceLimits.maxComputeWorkGroupSize[3] =
//     maxComputeWorkGroupSize[3]; PhysicalDeviceLimits.subPixelPrecisionBits =
//     subPixelPrecisionBits; PhysicalDeviceLimits.subTexelPrecisionBits =
//     subTexelPrecisionBits; PhysicalDeviceLimits.mipmapPrecisionBits =
//     mipmapPrecisionBits; PhysicalDeviceLimits.maxDrawIndexedIndexValue =
//     maxDrawIndexedIndexValue; PhysicalDeviceLimits.maxDrawIndirectCount =
//     maxDrawIndirectCount; PhysicalDeviceLimits.maxSamplerLodBias =
//     maxSamplerLodBias; PhysicalDeviceLimits.maxSamplerAnisotropy =
//     maxSamplerAnisotropy; PhysicalDeviceLimits.maxViewports = maxViewports;
//     PhysicalDeviceLimits.maxViewportDimensions[2] = maxViewportDimensions[2];
//     PhysicalDeviceLimits.viewportBoundsRange[2] = viewportBoundsRange[2];
//     PhysicalDeviceLimits.viewportSubPixelBits = viewportSubPixelBits;
//     PhysicalDeviceLimits.minMemoryMapAlignment = minMemoryMapAlignment;
//     PhysicalDeviceLimits.minTexelBufferOffsetAlignment =
//     minTexelBufferOffsetAlignment;
//     PhysicalDeviceLimits.minUniformBufferOffsetAlignment =
//     minUniformBufferOffsetAlignment;
//     PhysicalDeviceLimits.minStorageBufferOffsetAlignment =
//     minStorageBufferOffsetAlignment; PhysicalDeviceLimits.minTexelOffset =
//     minTexelOffset; PhysicalDeviceLimits.maxTexelOffset = maxTexelOffset;
//     PhysicalDeviceLimits.minTexelGatherOffset = minTexelGatherOffset;
//     PhysicalDeviceLimits.maxTexelGatherOffset = maxTexelGatherOffset;
//     PhysicalDeviceLimits.minInterpolationOffset = minInterpolationOffset;
//     PhysicalDeviceLimits.maxInterpolationOffset = maxInterpolationOffset;
//     PhysicalDeviceLimits.subPixelInterpolationOffsetBits =
//     subPixelInterpolationOffsetBits; PhysicalDeviceLimits.maxFramebufferWidth
//     = maxFramebufferWidth; PhysicalDeviceLimits.maxFramebufferHeight =
//     maxFramebufferHeight; PhysicalDeviceLimits.maxFramebufferLayers =
//     maxFramebufferLayers; PhysicalDeviceLimits.framebufferColorSampleCounts =
//     framebufferColorSampleCounts;
//     PhysicalDeviceLimits.framebufferDepthSampleCounts =
//     framebufferDepthSampleCounts;
//     PhysicalDeviceLimits.framebufferStencilSampleCounts =
//     framebufferStencilSampleCounts;
//     PhysicalDeviceLimits.framebufferNoAttachmentsSampleCounts =
//     framebufferNoAttachmentsSampleCounts;
//     PhysicalDeviceLimits.maxColorAttachments = maxColorAttachments;
//     PhysicalDeviceLimits.sampledImageColorSampleCounts =
//     sampledImageColorSampleCounts;
//     PhysicalDeviceLimits.sampledImageIntegerSampleCounts =
//     sampledImageIntegerSampleCounts;
//     PhysicalDeviceLimits.sampledImageDepthSampleCounts =
//     sampledImageDepthSampleCounts;
//     PhysicalDeviceLimits.sampledImageStencilSampleCounts =
//     sampledImageStencilSampleCounts;
//     PhysicalDeviceLimits.storageImageSampleCounts = storageImageSampleCounts;
//     PhysicalDeviceLimits.maxSampleMaskWords = maxSampleMaskWords;
//     PhysicalDeviceLimits.timestampComputeAndGraphics =
//     timestampComputeAndGraphics; PhysicalDeviceLimits.timestampPeriod =
//     timestampPeriod; PhysicalDeviceLimits.maxClipDistances =
//     maxClipDistances; PhysicalDeviceLimits.maxCullDistances =
//     maxCullDistances; PhysicalDeviceLimits.maxCombinedClipAndCullDistances =
//     maxCombinedClipAndCullDistances;
//     PhysicalDeviceLimits.discreteQueuePriorities = discreteQueuePriorities;
//     PhysicalDeviceLimits.pointSizeRange[2] = pointSizeRange[2];
//     PhysicalDeviceLimits.lineWidthRange[2] = lineWidthRange[2];
//     PhysicalDeviceLimits.pointSizeGranularity = pointSizeGranularity;
//     PhysicalDeviceLimits.lineWidthGranularity = lineWidthGranularity;
//     PhysicalDeviceLimits.strictLines = strictLines;
//     PhysicalDeviceLimits.standardSampleLocations = standardSampleLocations;
//     PhysicalDeviceLimits.optimalBufferCopyOffsetAlignment =
//     optimalBufferCopyOffsetAlignment;
//     PhysicalDeviceLimits.optimalBufferCopyRowPitchAlignment =
//     optimalBufferCopyRowPitchAlignment;
//     PhysicalDeviceLimits.nonCoherentAtomSize = nonCoherentAtomSize;
//     return PhysicalDeviceLimits;
// }

inline VkPhysicalDeviceSparseProperties vkiPhysicalDeviceSparseProperties(
    VkBool32 residencyStandard2DBlockShape,
    VkBool32 residencyStandard2DMultisampleBlockShape,
    VkBool32 residencyStandard3DBlockShape, VkBool32 residencyAlignedMipSize,
    VkBool32 residencyNonResidentStrict) {
  VkPhysicalDeviceSparseProperties PhysicalDeviceSparseProperties = {};
  PhysicalDeviceSparseProperties.residencyStandard2DBlockShape =
      residencyStandard2DBlockShape;
  PhysicalDeviceSparseProperties.residencyStandard2DMultisampleBlockShape =
      residencyStandard2DMultisampleBlockShape;
  PhysicalDeviceSparseProperties.residencyStandard3DBlockShape =
      residencyStandard3DBlockShape;
  PhysicalDeviceSparseProperties.residencyAlignedMipSize =
      residencyAlignedMipSize;
  PhysicalDeviceSparseProperties.residencyNonResidentStrict =
      residencyNonResidentStrict;
  return PhysicalDeviceSparseProperties;
}

// inline VkPhysicalDeviceProperties vkiPhysicalDeviceProperties(uint32_t
// apiVersion, uint32_t driverVersion, uint32_t vendorID, uint32_t deviceID,
// VkPhysicalDeviceType deviceType, char
// deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE], uint8_t
// pipelineCacheUUID[VK_UUID_SIZE], VkPhysicalDeviceLimits limits,
// VkPhysicalDeviceSparseProperties sparseProperties) {
//     VkPhysicalDeviceProperties PhysicalDeviceProperties = {};
//     PhysicalDeviceProperties.apiVersion = apiVersion;
//     PhysicalDeviceProperties.driverVersion = driverVersion;
//     PhysicalDeviceProperties.vendorID = vendorID;
//     PhysicalDeviceProperties.deviceID = deviceID;
//     PhysicalDeviceProperties.deviceType = deviceType;
//     PhysicalDeviceProperties.deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE] =
//     deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
//     PhysicalDeviceProperties.pipelineCacheUUID[VK_UUID_SIZE] =
//     pipelineCacheUUID[VK_UUID_SIZE]; PhysicalDeviceProperties.limits =
//     limits; PhysicalDeviceProperties.sparseProperties = sparseProperties;
//     return PhysicalDeviceProperties;
// }

inline VkQueueFamilyProperties vkiQueueFamilyProperties(
    VkQueueFlags queueFlags, uint32_t queueCount, uint32_t timestampValidBits,
    VkExtent3D minImageTransferGranularity) {
  VkQueueFamilyProperties QueueFamilyProperties = {};
  QueueFamilyProperties.queueFlags = queueFlags;
  QueueFamilyProperties.queueCount = queueCount;
  QueueFamilyProperties.timestampValidBits = timestampValidBits;
  QueueFamilyProperties.minImageTransferGranularity =
      minImageTransferGranularity;
  return QueueFamilyProperties;
}

inline VkMemoryType vkiMemoryType(VkMemoryPropertyFlags propertyFlags,
                                  uint32_t heapIndex) {
  VkMemoryType MemoryType = {};
  MemoryType.propertyFlags = propertyFlags;
  MemoryType.heapIndex = heapIndex;
  return MemoryType;
}

inline VkMemoryHeap vkiMemoryHeap(VkDeviceSize size) {
  VkMemoryHeap MemoryHeap = {};
  MemoryHeap.flags = 0;
  MemoryHeap.size = size;
  return MemoryHeap;
}

// inline VkPhysicalDeviceMemoryProperties
// vkiPhysicalDeviceMemoryProperties(uint32_t memoryTypeCount, VkMemoryType
// memoryTypes[VK_MAX_MEMORY_TYPES], uint32_t memoryHeapCount, VkMemoryHeap
// memoryHeaps[VK_MAX_MEMORY_HEAPS]) {
//     VkPhysicalDeviceMemoryProperties PhysicalDeviceMemoryProperties = {};
//     PhysicalDeviceMemoryProperties.memoryTypeCount = memoryTypeCount;
//     PhysicalDeviceMemoryProperties.memoryTypes[VK_MAX_MEMORY_TYPES] =
//     memoryTypes[VK_MAX_MEMORY_TYPES];
//     PhysicalDeviceMemoryProperties.memoryHeapCount = memoryHeapCount;
//     PhysicalDeviceMemoryProperties.memoryHeaps[VK_MAX_MEMORY_HEAPS] =
//     memoryHeaps[VK_MAX_MEMORY_HEAPS]; return PhysicalDeviceMemoryProperties;
// }

inline VkDeviceQueueCreateInfo vkiDeviceQueueCreateInfo(
    uint32_t queueFamilyIndex, uint32_t queueCount,
    const float* pQueuePriorities) {
  VkDeviceQueueCreateInfo DeviceQueueCreateInfo = {};
  DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  DeviceQueueCreateInfo.pNext = nullptr;
  DeviceQueueCreateInfo.flags = 0;
  DeviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
  DeviceQueueCreateInfo.queueCount = queueCount;
  DeviceQueueCreateInfo.pQueuePriorities = pQueuePriorities;
  return DeviceQueueCreateInfo;
}

inline VkDeviceCreateInfo vkiDeviceCreateInfo(
    uint32_t queueCreateInfoCount,
    const VkDeviceQueueCreateInfo* pQueueCreateInfos,
    uint32_t enabledLayerCount, const char* const* ppEnabledLayerNames,
    uint32_t enabledExtensionCount, const char* const* ppEnabledExtensionNames,
    const VkPhysicalDeviceFeatures* pEnabledFeatures) {
  VkDeviceCreateInfo DeviceCreateInfo = {};
  DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  DeviceCreateInfo.pNext = nullptr;
  DeviceCreateInfo.flags = 0;
  DeviceCreateInfo.queueCreateInfoCount = queueCreateInfoCount;
  DeviceCreateInfo.pQueueCreateInfos = pQueueCreateInfos;
  DeviceCreateInfo.enabledLayerCount = enabledLayerCount;
  DeviceCreateInfo.ppEnabledLayerNames = ppEnabledLayerNames;
  DeviceCreateInfo.enabledExtensionCount = enabledExtensionCount;
  DeviceCreateInfo.ppEnabledExtensionNames = ppEnabledExtensionNames;
  DeviceCreateInfo.pEnabledFeatures = pEnabledFeatures;
  return DeviceCreateInfo;
}

// inline VkExtensionProperties vkiExtensionProperties(char
// extensionName[VK_MAX_EXTENSION_NAME_SIZE], uint32_t specVersion) {
//     VkExtensionProperties ExtensionProperties = {};
//     ExtensionProperties.extensionName[VK_MAX_EXTENSION_NAME_SIZE] =
//     extensionName[VK_MAX_EXTENSION_NAME_SIZE];
//     ExtensionProperties.specVersion = specVersion;
//     return ExtensionProperties;
// }

// inline VkLayerProperties vkiLayerProperties(char
// layerName[VK_MAX_EXTENSION_NAME_SIZE], uint32_t specVersion, uint32_t
// implementationVersion, char description[VK_MAX_DESCRIPTION_SIZE]) {
//     VkLayerProperties LayerProperties = {};
//     LayerProperties.layerName[VK_MAX_EXTENSION_NAME_SIZE] =
//     layerName[VK_MAX_EXTENSION_NAME_SIZE]; LayerProperties.specVersion =
//     specVersion; LayerProperties.implementationVersion =
//     implementationVersion;
//     LayerProperties.description[VK_MAX_DESCRIPTION_SIZE] =
//     description[VK_MAX_DESCRIPTION_SIZE]; return LayerProperties;
// }

inline VkSubmitInfo vkiSubmitInfo(uint32_t waitSemaphoreCount,
                                  const VkSemaphore* pWaitSemaphores,
                                  const VkPipelineStageFlags* pWaitDstStageMask,
                                  uint32_t commandBufferCount,
                                  const VkCommandBuffer* pCommandBuffers,
                                  uint32_t signalSemaphoreCount,
                                  const VkSemaphore* pSignalSemaphores) {
  VkSubmitInfo SubmitInfo = {};
  SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  SubmitInfo.pNext = nullptr;
  SubmitInfo.waitSemaphoreCount = waitSemaphoreCount;
  SubmitInfo.pWaitSemaphores = pWaitSemaphores;
  SubmitInfo.pWaitDstStageMask = pWaitDstStageMask;
  SubmitInfo.commandBufferCount = commandBufferCount;
  SubmitInfo.pCommandBuffers = pCommandBuffers;
  SubmitInfo.signalSemaphoreCount = signalSemaphoreCount;
  SubmitInfo.pSignalSemaphores = pSignalSemaphores;
  return SubmitInfo;
}

inline VkMemoryAllocateInfo vkiMemoryAllocateInfo(VkDeviceSize allocationSize,
                                                  uint32_t memoryTypeIndex) {
  VkMemoryAllocateInfo MemoryAllocateInfo = {};
  MemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  MemoryAllocateInfo.pNext = nullptr;
  MemoryAllocateInfo.allocationSize = allocationSize;
  MemoryAllocateInfo.memoryTypeIndex = memoryTypeIndex;
  return MemoryAllocateInfo;
}

inline VkMappedMemoryRange vkiMappedMemoryRange(VkDeviceMemory memory,
                                                VkDeviceSize offset,
                                                VkDeviceSize size) {
  VkMappedMemoryRange MappedMemoryRange = {};
  MappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
  MappedMemoryRange.pNext = nullptr;
  MappedMemoryRange.memory = memory;
  MappedMemoryRange.offset = offset;
  MappedMemoryRange.size = size;
  return MappedMemoryRange;
}

inline VkMemoryRequirements vkiMemoryRequirements(VkDeviceSize size,
                                                  VkDeviceSize alignment,
                                                  uint32_t memoryTypeBits) {
  VkMemoryRequirements MemoryRequirements = {};
  MemoryRequirements.size = size;
  MemoryRequirements.alignment = alignment;
  MemoryRequirements.memoryTypeBits = memoryTypeBits;
  return MemoryRequirements;
}

inline VkSparseImageFormatProperties vkiSparseImageFormatProperties(
    VkImageAspectFlags aspectMask, VkExtent3D imageGranularity) {
  VkSparseImageFormatProperties SparseImageFormatProperties = {};
  SparseImageFormatProperties.flags = 0;
  SparseImageFormatProperties.aspectMask = aspectMask;
  SparseImageFormatProperties.imageGranularity = imageGranularity;
  return SparseImageFormatProperties;
}

inline VkSparseImageMemoryRequirements vkiSparseImageMemoryRequirements(
    VkSparseImageFormatProperties formatProperties,
    uint32_t imageMipTailFirstLod, VkDeviceSize imageMipTailSize,
    VkDeviceSize imageMipTailOffset, VkDeviceSize imageMipTailStride) {
  VkSparseImageMemoryRequirements SparseImageMemoryRequirements = {};
  SparseImageMemoryRequirements.formatProperties = formatProperties;
  SparseImageMemoryRequirements.imageMipTailFirstLod = imageMipTailFirstLod;
  SparseImageMemoryRequirements.imageMipTailSize = imageMipTailSize;
  SparseImageMemoryRequirements.imageMipTailOffset = imageMipTailOffset;
  SparseImageMemoryRequirements.imageMipTailStride = imageMipTailStride;
  return SparseImageMemoryRequirements;
}

inline VkSparseMemoryBind vkiSparseMemoryBind(VkDeviceSize resourceOffset,
                                              VkDeviceSize size,
                                              VkDeviceMemory memory,
                                              VkDeviceSize memoryOffset) {
  VkSparseMemoryBind SparseMemoryBind = {};
  SparseMemoryBind.flags = 0;
  SparseMemoryBind.resourceOffset = resourceOffset;
  SparseMemoryBind.size = size;
  SparseMemoryBind.memory = memory;
  SparseMemoryBind.memoryOffset = memoryOffset;
  return SparseMemoryBind;
}

inline VkSparseBufferMemoryBindInfo vkiSparseBufferMemoryBindInfo(
    VkBuffer buffer, uint32_t bindCount, const VkSparseMemoryBind* pBinds) {
  VkSparseBufferMemoryBindInfo SparseBufferMemoryBindInfo = {};
  SparseBufferMemoryBindInfo.buffer = buffer;
  SparseBufferMemoryBindInfo.bindCount = bindCount;
  SparseBufferMemoryBindInfo.pBinds = pBinds;
  return SparseBufferMemoryBindInfo;
}

inline VkSparseImageOpaqueMemoryBindInfo vkiSparseImageOpaqueMemoryBindInfo(
    VkImage image, uint32_t bindCount, const VkSparseMemoryBind* pBinds) {
  VkSparseImageOpaqueMemoryBindInfo SparseImageOpaqueMemoryBindInfo = {};
  SparseImageOpaqueMemoryBindInfo.image = image;
  SparseImageOpaqueMemoryBindInfo.bindCount = bindCount;
  SparseImageOpaqueMemoryBindInfo.pBinds = pBinds;
  return SparseImageOpaqueMemoryBindInfo;
}

inline VkImageSubresource vkiImageSubresource(VkImageAspectFlags aspectMask,
                                              uint32_t mipLevel,
                                              uint32_t arrayLayer) {
  VkImageSubresource ImageSubresource = {};
  ImageSubresource.aspectMask = aspectMask;
  ImageSubresource.mipLevel = mipLevel;
  ImageSubresource.arrayLayer = arrayLayer;
  return ImageSubresource;
}

inline VkOffset3D vkiOffset3D(int32_t x, int32_t y, int32_t z) {
  VkOffset3D Offset3D = {};
  Offset3D.x = x;
  Offset3D.y = y;
  Offset3D.z = z;
  return Offset3D;
}

inline VkSparseImageMemoryBind vkiSparseImageMemoryBind(
    VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent,
    VkDeviceMemory memory, VkDeviceSize memoryOffset) {
  VkSparseImageMemoryBind SparseImageMemoryBind = {};
  SparseImageMemoryBind.flags = 0;
  SparseImageMemoryBind.subresource = subresource;
  SparseImageMemoryBind.offset = offset;
  SparseImageMemoryBind.extent = extent;
  SparseImageMemoryBind.memory = memory;
  SparseImageMemoryBind.memoryOffset = memoryOffset;
  return SparseImageMemoryBind;
}

inline VkSparseImageMemoryBindInfo vkiSparseImageMemoryBindInfo(
    VkImage image, uint32_t bindCount, const VkSparseImageMemoryBind* pBinds) {
  VkSparseImageMemoryBindInfo SparseImageMemoryBindInfo = {};
  SparseImageMemoryBindInfo.image = image;
  SparseImageMemoryBindInfo.bindCount = bindCount;
  SparseImageMemoryBindInfo.pBinds = pBinds;
  return SparseImageMemoryBindInfo;
}

inline VkBindSparseInfo vkiBindSparseInfo(
    uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores,
    uint32_t bufferBindCount, const VkSparseBufferMemoryBindInfo* pBufferBinds,
    uint32_t imageOpaqueBindCount,
    const VkSparseImageOpaqueMemoryBindInfo* pImageOpaqueBinds,
    uint32_t imageBindCount, const VkSparseImageMemoryBindInfo* pImageBinds,
    uint32_t signalSemaphoreCount, const VkSemaphore* pSignalSemaphores) {
  VkBindSparseInfo BindSparseInfo = {};
  BindSparseInfo.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
  BindSparseInfo.pNext = nullptr;
  BindSparseInfo.waitSemaphoreCount = waitSemaphoreCount;
  BindSparseInfo.pWaitSemaphores = pWaitSemaphores;
  BindSparseInfo.bufferBindCount = bufferBindCount;
  BindSparseInfo.pBufferBinds = pBufferBinds;
  BindSparseInfo.imageOpaqueBindCount = imageOpaqueBindCount;
  BindSparseInfo.pImageOpaqueBinds = pImageOpaqueBinds;
  BindSparseInfo.imageBindCount = imageBindCount;
  BindSparseInfo.pImageBinds = pImageBinds;
  BindSparseInfo.signalSemaphoreCount = signalSemaphoreCount;
  BindSparseInfo.pSignalSemaphores = pSignalSemaphores;
  return BindSparseInfo;
}

inline VkFenceCreateInfo vkiFenceCreateInfo() {
  VkFenceCreateInfo FenceCreateInfo = {};
  FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  FenceCreateInfo.pNext = nullptr;
  FenceCreateInfo.flags = 0;
  return FenceCreateInfo;
}

inline VkSemaphoreCreateInfo vkiSemaphoreCreateInfo() {
  VkSemaphoreCreateInfo SemaphoreCreateInfo = {};
  SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  SemaphoreCreateInfo.pNext = nullptr;
  SemaphoreCreateInfo.flags = 0;
  return SemaphoreCreateInfo;
}

inline VkEventCreateInfo vkiEventCreateInfo() {
  VkEventCreateInfo EventCreateInfo = {};
  EventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
  EventCreateInfo.pNext = nullptr;
  EventCreateInfo.flags = 0;
  return EventCreateInfo;
}

inline VkQueryPoolCreateInfo vkiQueryPoolCreateInfo(
    VkQueryType queryType, uint32_t queryCount,
    VkQueryPipelineStatisticFlags pipelineStatistics) {
  VkQueryPoolCreateInfo QueryPoolCreateInfo = {};
  QueryPoolCreateInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
  QueryPoolCreateInfo.pNext = nullptr;
  QueryPoolCreateInfo.flags = 0;
  QueryPoolCreateInfo.queryType = queryType;
  QueryPoolCreateInfo.queryCount = queryCount;
  QueryPoolCreateInfo.pipelineStatistics = pipelineStatistics;
  return QueryPoolCreateInfo;
}

inline VkBufferCreateInfo vkiBufferCreateInfo(
    VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharingMode,
    uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices) {
  VkBufferCreateInfo BufferCreateInfo = {};
  BufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  BufferCreateInfo.pNext = nullptr;
  BufferCreateInfo.flags = 0;
  BufferCreateInfo.size = size;
  BufferCreateInfo.usage = usage;
  BufferCreateInfo.sharingMode = sharingMode;
  BufferCreateInfo.queueFamilyIndexCount = queueFamilyIndexCount;
  BufferCreateInfo.pQueueFamilyIndices = pQueueFamilyIndices;
  return BufferCreateInfo;
}

inline VkBufferViewCreateInfo vkiBufferViewCreateInfo(VkBuffer buffer,
                                                      VkFormat format,
                                                      VkDeviceSize offset,
                                                      VkDeviceSize range) {
  VkBufferViewCreateInfo BufferViewCreateInfo = {};
  BufferViewCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
  BufferViewCreateInfo.pNext = nullptr;
  BufferViewCreateInfo.flags = 0;
  BufferViewCreateInfo.buffer = buffer;
  BufferViewCreateInfo.format = format;
  BufferViewCreateInfo.offset = offset;
  BufferViewCreateInfo.range = range;
  return BufferViewCreateInfo;
}

inline VkImageCreateInfo vkiImageCreateInfo(
    VkImageType imageType, VkFormat format, VkExtent3D extent,
    uint32_t mipLevels, uint32_t arrayLayers, VkSampleCountFlagBits samples,
    VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharingMode,
    uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices,
    VkImageLayout initialLayout) {
  VkImageCreateInfo ImageCreateInfo = {};
  ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  ImageCreateInfo.pNext = nullptr;
  ImageCreateInfo.flags = 0;
  ImageCreateInfo.imageType = imageType;
  ImageCreateInfo.format = format;
  ImageCreateInfo.extent = extent;
  ImageCreateInfo.mipLevels = mipLevels;
  ImageCreateInfo.arrayLayers = arrayLayers;
  ImageCreateInfo.samples = samples;
  ImageCreateInfo.tiling = tiling;
  ImageCreateInfo.usage = usage;
  ImageCreateInfo.sharingMode = sharingMode;
  ImageCreateInfo.queueFamilyIndexCount = queueFamilyIndexCount;
  ImageCreateInfo.pQueueFamilyIndices = pQueueFamilyIndices;
  ImageCreateInfo.initialLayout = initialLayout;
  return ImageCreateInfo;
}

inline VkSubresourceLayout vkiSubresourceLayout(VkDeviceSize offset,
                                                VkDeviceSize size,
                                                VkDeviceSize rowPitch,
                                                VkDeviceSize arrayPitch,
                                                VkDeviceSize depthPitch) {
  VkSubresourceLayout SubresourceLayout = {};
  SubresourceLayout.offset = offset;
  SubresourceLayout.size = size;
  SubresourceLayout.rowPitch = rowPitch;
  SubresourceLayout.arrayPitch = arrayPitch;
  SubresourceLayout.depthPitch = depthPitch;
  return SubresourceLayout;
}

inline VkComponentMapping vkiComponentMapping(VkComponentSwizzle r,
                                              VkComponentSwizzle g,
                                              VkComponentSwizzle b,
                                              VkComponentSwizzle a) {
  VkComponentMapping ComponentMapping = {};
  ComponentMapping.r = r;
  ComponentMapping.g = g;
  ComponentMapping.b = b;
  ComponentMapping.a = a;
  return ComponentMapping;
}

inline VkImageSubresourceRange vkiImageSubresourceRange(
    VkImageAspectFlags aspectMask, uint32_t baseMipLevel, uint32_t levelCount,
    uint32_t baseArrayLayer, uint32_t layerCount) {
  VkImageSubresourceRange ImageSubresourceRange = {};
  ImageSubresourceRange.aspectMask = aspectMask;
  ImageSubresourceRange.baseMipLevel = baseMipLevel;
  ImageSubresourceRange.levelCount = levelCount;
  ImageSubresourceRange.baseArrayLayer = baseArrayLayer;
  ImageSubresourceRange.layerCount = layerCount;
  return ImageSubresourceRange;
}

inline VkImageViewCreateInfo vkiImageViewCreateInfo(
    VkImage image, VkImageViewType viewType, VkFormat format,
    VkComponentMapping components, VkImageSubresourceRange subresourceRange) {
  VkImageViewCreateInfo ImageViewCreateInfo = {};
  ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  ImageViewCreateInfo.pNext = nullptr;
  ImageViewCreateInfo.flags = 0;
  ImageViewCreateInfo.image = image;
  ImageViewCreateInfo.viewType = viewType;
  ImageViewCreateInfo.format = format;
  ImageViewCreateInfo.components = components;
  ImageViewCreateInfo.subresourceRange = subresourceRange;
  return ImageViewCreateInfo;
}

inline VkShaderModuleCreateInfo vkiShaderModuleCreateInfo(
    size_t codeSize, const uint32_t* pCode) {
  VkShaderModuleCreateInfo ShaderModuleCreateInfo = {};
  ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  ShaderModuleCreateInfo.pNext = nullptr;
  ShaderModuleCreateInfo.flags = 0;
  ShaderModuleCreateInfo.codeSize = codeSize;
  ShaderModuleCreateInfo.pCode = pCode;
  return ShaderModuleCreateInfo;
}

inline VkPipelineCacheCreateInfo vkiPipelineCacheCreateInfo(
    size_t initialDataSize, const void* pInitialData) {
  VkPipelineCacheCreateInfo PipelineCacheCreateInfo = {};
  PipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
  PipelineCacheCreateInfo.pNext = nullptr;
  PipelineCacheCreateInfo.flags = 0;
  PipelineCacheCreateInfo.initialDataSize = initialDataSize;
  PipelineCacheCreateInfo.pInitialData = pInitialData;
  return PipelineCacheCreateInfo;
}

inline VkSpecializationMapEntry vkiSpecializationMapEntry(uint32_t constantID,
                                                          uint32_t offset,
                                                          size_t size) {
  VkSpecializationMapEntry SpecializationMapEntry = {};
  SpecializationMapEntry.constantID = constantID;
  SpecializationMapEntry.offset = offset;
  SpecializationMapEntry.size = size;
  return SpecializationMapEntry;
}

inline VkSpecializationInfo vkiSpecializationInfo(
    uint32_t mapEntryCount, const VkSpecializationMapEntry* pMapEntries,
    size_t dataSize, const void* pData) {
  VkSpecializationInfo SpecializationInfo = {};
  SpecializationInfo.mapEntryCount = mapEntryCount;
  SpecializationInfo.pMapEntries = pMapEntries;
  SpecializationInfo.dataSize = dataSize;
  SpecializationInfo.pData = pData;
  return SpecializationInfo;
}

inline VkPipelineShaderStageCreateInfo vkiPipelineShaderStageCreateInfo(
    VkShaderStageFlagBits stage, VkShaderModule module, const char* pName,
    const VkSpecializationInfo* pSpecializationInfo) {
  VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo = {};
  PipelineShaderStageCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  PipelineShaderStageCreateInfo.pNext = nullptr;
  PipelineShaderStageCreateInfo.flags = 0;
  PipelineShaderStageCreateInfo.stage = stage;
  PipelineShaderStageCreateInfo.module = module;
  PipelineShaderStageCreateInfo.pName = pName;
  PipelineShaderStageCreateInfo.pSpecializationInfo = pSpecializationInfo;
  return PipelineShaderStageCreateInfo;
}

inline VkVertexInputBindingDescription vkiVertexInputBindingDescription(
    uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) {
  VkVertexInputBindingDescription VertexInputBindingDescription = {};
  VertexInputBindingDescription.binding = binding;
  VertexInputBindingDescription.stride = stride;
  VertexInputBindingDescription.inputRate = inputRate;
  return VertexInputBindingDescription;
}

inline VkVertexInputAttributeDescription vkiVertexInputAttributeDescription(
    uint32_t location, uint32_t binding, VkFormat format, uint32_t offset) {
  VkVertexInputAttributeDescription VertexInputAttributeDescription = {};
  VertexInputAttributeDescription.location = location;
  VertexInputAttributeDescription.binding = binding;
  VertexInputAttributeDescription.format = format;
  VertexInputAttributeDescription.offset = offset;
  return VertexInputAttributeDescription;
}

inline VkPipelineVertexInputStateCreateInfo
vkiPipelineVertexInputStateCreateInfo(
    uint32_t vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription* pVertexAttributeDescriptions) {
  VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo = {};
  PipelineVertexInputStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  PipelineVertexInputStateCreateInfo.pNext = nullptr;
  PipelineVertexInputStateCreateInfo.flags = 0;
  PipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount =
      vertexBindingDescriptionCount;
  PipelineVertexInputStateCreateInfo.pVertexBindingDescriptions =
      pVertexBindingDescriptions;
  PipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount =
      vertexAttributeDescriptionCount;
  PipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions =
      pVertexAttributeDescriptions;
  return PipelineVertexInputStateCreateInfo;
}

inline VkPipelineInputAssemblyStateCreateInfo
vkiPipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology,
                                        VkBool32 primitiveRestartEnable) {
  VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo =
      {};
  PipelineInputAssemblyStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  PipelineInputAssemblyStateCreateInfo.pNext = nullptr;
  PipelineInputAssemblyStateCreateInfo.flags = 0;
  PipelineInputAssemblyStateCreateInfo.topology = topology;
  PipelineInputAssemblyStateCreateInfo.primitiveRestartEnable =
      primitiveRestartEnable;
  return PipelineInputAssemblyStateCreateInfo;
}

inline VkPipelineTessellationStateCreateInfo
vkiPipelineTessellationStateCreateInfo(uint32_t patchControlPoints) {
  VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo =
      {};
  PipelineTessellationStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
  PipelineTessellationStateCreateInfo.pNext = nullptr;
  PipelineTessellationStateCreateInfo.flags = 0;
  PipelineTessellationStateCreateInfo.patchControlPoints = patchControlPoints;
  return PipelineTessellationStateCreateInfo;
}

inline VkViewport vkiViewport(float x, float y, float width, float height,
                              float minDepth, float maxDepth) {
  VkViewport Viewport = {};
  Viewport.x = x;
  Viewport.y = y;
  Viewport.width = width;
  Viewport.height = height;
  Viewport.minDepth = minDepth;
  Viewport.maxDepth = maxDepth;
  return Viewport;
}

inline VkOffset2D vkiOffset2D(int32_t x, int32_t y) {
  VkOffset2D Offset2D = {};
  Offset2D.x = x;
  Offset2D.y = y;
  return Offset2D;
}

inline VkExtent2D vkiExtent2D(uint32_t width, uint32_t height) {
  VkExtent2D Extent2D = {};
  Extent2D.width = width;
  Extent2D.height = height;
  return Extent2D;
}

inline VkRect2D vkiRect2D(VkOffset2D offset, VkExtent2D extent) {
  VkRect2D Rect2D = {};
  Rect2D.offset = offset;
  Rect2D.extent = extent;
  return Rect2D;
}

inline VkPipelineViewportStateCreateInfo vkiPipelineViewportStateCreateInfo(
    uint32_t viewportCount, const VkViewport* pViewports, uint32_t scissorCount,
    const VkRect2D* pScissors) {
  VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo = {};
  PipelineViewportStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  PipelineViewportStateCreateInfo.pNext = nullptr;
  PipelineViewportStateCreateInfo.flags = 0;
  PipelineViewportStateCreateInfo.viewportCount = viewportCount;
  PipelineViewportStateCreateInfo.pViewports = pViewports;
  PipelineViewportStateCreateInfo.scissorCount = scissorCount;
  PipelineViewportStateCreateInfo.pScissors = pScissors;
  return PipelineViewportStateCreateInfo;
}

inline VkPipelineRasterizationStateCreateInfo
vkiPipelineRasterizationStateCreateInfo(
    VkBool32 depthClampEnable, VkBool32 rasterizerDiscardEnable,
    VkPolygonMode polygonMode, VkCullModeFlags cullMode, VkFrontFace frontFace,
    VkBool32 depthBiasEnable, float depthBiasConstantFactor,
    float depthBiasClamp, float depthBiasSlopeFactor, float lineWidth) {
  VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo =
      {};
  PipelineRasterizationStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  PipelineRasterizationStateCreateInfo.pNext = nullptr;
  PipelineRasterizationStateCreateInfo.flags = 0;
  PipelineRasterizationStateCreateInfo.depthClampEnable = depthClampEnable;
  PipelineRasterizationStateCreateInfo.rasterizerDiscardEnable =
      rasterizerDiscardEnable;
  PipelineRasterizationStateCreateInfo.polygonMode = polygonMode;
  PipelineRasterizationStateCreateInfo.cullMode = cullMode;
  PipelineRasterizationStateCreateInfo.frontFace = frontFace;
  PipelineRasterizationStateCreateInfo.depthBiasEnable = depthBiasEnable;
  PipelineRasterizationStateCreateInfo.depthBiasConstantFactor =
      depthBiasConstantFactor;
  PipelineRasterizationStateCreateInfo.depthBiasClamp = depthBiasClamp;
  PipelineRasterizationStateCreateInfo.depthBiasSlopeFactor =
      depthBiasSlopeFactor;
  PipelineRasterizationStateCreateInfo.lineWidth = lineWidth;
  return PipelineRasterizationStateCreateInfo;
}

inline VkPipelineMultisampleStateCreateInfo
vkiPipelineMultisampleStateCreateInfo(
    VkSampleCountFlagBits rasterizationSamples, VkBool32 sampleShadingEnable,
    float minSampleShading, const VkSampleMask* pSampleMask,
    VkBool32 alphaToCoverageEnable, VkBool32 alphaToOneEnable) {
  VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo = {};
  PipelineMultisampleStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  PipelineMultisampleStateCreateInfo.pNext = nullptr;
  PipelineMultisampleStateCreateInfo.flags = 0;
  PipelineMultisampleStateCreateInfo.rasterizationSamples =
      rasterizationSamples;
  PipelineMultisampleStateCreateInfo.sampleShadingEnable = sampleShadingEnable;
  PipelineMultisampleStateCreateInfo.minSampleShading = minSampleShading;
  PipelineMultisampleStateCreateInfo.pSampleMask = pSampleMask;
  PipelineMultisampleStateCreateInfo.alphaToCoverageEnable =
      alphaToCoverageEnable;
  PipelineMultisampleStateCreateInfo.alphaToOneEnable = alphaToOneEnable;
  return PipelineMultisampleStateCreateInfo;
}

inline VkStencilOpState vkiStencilOpState(
    VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp,
    VkCompareOp compareOp, uint32_t compareMask, uint32_t writeMask,
    uint32_t reference) {
  VkStencilOpState StencilOpState = {};
  StencilOpState.failOp = failOp;
  StencilOpState.passOp = passOp;
  StencilOpState.depthFailOp = depthFailOp;
  StencilOpState.compareOp = compareOp;
  StencilOpState.compareMask = compareMask;
  StencilOpState.writeMask = writeMask;
  StencilOpState.reference = reference;
  return StencilOpState;
}

inline VkPipelineDepthStencilStateCreateInfo
vkiPipelineDepthStencilStateCreateInfo(
    VkBool32 depthTestEnable, VkBool32 depthWriteEnable,
    VkCompareOp depthCompareOp, VkBool32 depthBoundsTestEnable,
    VkBool32 stencilTestEnable, VkStencilOpState front, VkStencilOpState back,
    float minDepthBounds, float maxDepthBounds) {
  VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo =
      {};
  PipelineDepthStencilStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  PipelineDepthStencilStateCreateInfo.pNext = nullptr;
  PipelineDepthStencilStateCreateInfo.flags = 0;
  PipelineDepthStencilStateCreateInfo.depthTestEnable = depthTestEnable;
  PipelineDepthStencilStateCreateInfo.depthWriteEnable = depthWriteEnable;
  PipelineDepthStencilStateCreateInfo.depthCompareOp = depthCompareOp;
  PipelineDepthStencilStateCreateInfo.depthBoundsTestEnable =
      depthBoundsTestEnable;
  PipelineDepthStencilStateCreateInfo.stencilTestEnable = stencilTestEnable;
  PipelineDepthStencilStateCreateInfo.front = front;
  PipelineDepthStencilStateCreateInfo.back = back;
  PipelineDepthStencilStateCreateInfo.minDepthBounds = minDepthBounds;
  PipelineDepthStencilStateCreateInfo.maxDepthBounds = maxDepthBounds;
  return PipelineDepthStencilStateCreateInfo;
}

inline VkPipelineColorBlendAttachmentState vkiPipelineColorBlendAttachmentState(
    VkBool32 blendEnable, VkBlendFactor srcColorBlendFactor,
    VkBlendFactor dstColorBlendFactor, VkBlendOp colorBlendOp,
    VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor,
    VkBlendOp alphaBlendOp, VkColorComponentFlags colorWriteMask) {
  VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState = {};
  PipelineColorBlendAttachmentState.blendEnable = blendEnable;
  PipelineColorBlendAttachmentState.srcColorBlendFactor = srcColorBlendFactor;
  PipelineColorBlendAttachmentState.dstColorBlendFactor = dstColorBlendFactor;
  PipelineColorBlendAttachmentState.colorBlendOp = colorBlendOp;
  PipelineColorBlendAttachmentState.srcAlphaBlendFactor = srcAlphaBlendFactor;
  PipelineColorBlendAttachmentState.dstAlphaBlendFactor = dstAlphaBlendFactor;
  PipelineColorBlendAttachmentState.alphaBlendOp = alphaBlendOp;
  PipelineColorBlendAttachmentState.colorWriteMask = colorWriteMask;
  return PipelineColorBlendAttachmentState;
}

// inline VkPipelineColorBlendStateCreateInfo
// vkiPipelineColorBlendStateCreateInfo(VkBool32 logicOpEnable, VkLogicOp
// logicOp, uint32_t attachmentCount, const VkPipelineColorBlendAttachmentState*
// pAttachments, float blendConstants[4]) {
//     VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo =
//     {}; PipelineColorBlendStateCreateInfo.sType =
//     VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
//     PipelineColorBlendStateCreateInfo.pNext = nullptr;
//     PipelineColorBlendStateCreateInfo.flags = 0;
//     PipelineColorBlendStateCreateInfo.logicOpEnable = logicOpEnable;
//     PipelineColorBlendStateCreateInfo.logicOp = logicOp;
//     PipelineColorBlendStateCreateInfo.attachmentCount = attachmentCount;
//     PipelineColorBlendStateCreateInfo.pAttachments = pAttachments;
//     PipelineColorBlendStateCreateInfo.blendConstants[4] = blendConstants[4];
//     return PipelineColorBlendStateCreateInfo;
// }

inline VkPipelineDynamicStateCreateInfo vkiPipelineDynamicStateCreateInfo(
    uint32_t dynamicStateCount, const VkDynamicState* pDynamicStates) {
  VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo = {};
  PipelineDynamicStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  PipelineDynamicStateCreateInfo.pNext = nullptr;
  PipelineDynamicStateCreateInfo.flags = 0;
  PipelineDynamicStateCreateInfo.dynamicStateCount = dynamicStateCount;
  PipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates;
  return PipelineDynamicStateCreateInfo;
}

inline VkGraphicsPipelineCreateInfo vkiGraphicsPipelineCreateInfo(
    uint32_t stageCount, const VkPipelineShaderStageCreateInfo* pStages,
    const VkPipelineVertexInputStateCreateInfo* pVertexInputState,
    const VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState,
    const VkPipelineTessellationStateCreateInfo* pTessellationState,
    const VkPipelineViewportStateCreateInfo* pViewportState,
    const VkPipelineRasterizationStateCreateInfo* pRasterizationState,
    const VkPipelineMultisampleStateCreateInfo* pMultisampleState,
    const VkPipelineDepthStencilStateCreateInfo* pDepthStencilState,
    const VkPipelineColorBlendStateCreateInfo* pColorBlendState,
    const VkPipelineDynamicStateCreateInfo* pDynamicState,
    VkPipelineLayout layout, VkRenderPass renderPass, uint32_t subpass,
    VkPipeline basePipelineHandle, int32_t basePipelineIndex) {
  VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo = {};
  GraphicsPipelineCreateInfo.sType =
      VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  GraphicsPipelineCreateInfo.pNext = nullptr;
  GraphicsPipelineCreateInfo.flags = 0;
  GraphicsPipelineCreateInfo.stageCount = stageCount;
  GraphicsPipelineCreateInfo.pStages = pStages;
  GraphicsPipelineCreateInfo.pVertexInputState = pVertexInputState;
  GraphicsPipelineCreateInfo.pInputAssemblyState = pInputAssemblyState;
  GraphicsPipelineCreateInfo.pTessellationState = pTessellationState;
  GraphicsPipelineCreateInfo.pViewportState = pViewportState;
  GraphicsPipelineCreateInfo.pRasterizationState = pRasterizationState;
  GraphicsPipelineCreateInfo.pMultisampleState = pMultisampleState;
  GraphicsPipelineCreateInfo.pDepthStencilState = pDepthStencilState;
  GraphicsPipelineCreateInfo.pColorBlendState = pColorBlendState;
  GraphicsPipelineCreateInfo.pDynamicState = pDynamicState;
  GraphicsPipelineCreateInfo.layout = layout;
  GraphicsPipelineCreateInfo.renderPass = renderPass;
  GraphicsPipelineCreateInfo.subpass = subpass;
  GraphicsPipelineCreateInfo.basePipelineHandle = basePipelineHandle;
  GraphicsPipelineCreateInfo.basePipelineIndex = basePipelineIndex;
  return GraphicsPipelineCreateInfo;
}

inline VkComputePipelineCreateInfo vkiComputePipelineCreateInfo(
    VkPipelineShaderStageCreateInfo stage, VkPipelineLayout layout,
    VkPipeline basePipelineHandle, int32_t basePipelineIndex) {
  VkComputePipelineCreateInfo ComputePipelineCreateInfo = {};
  ComputePipelineCreateInfo.sType =
      VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
  ComputePipelineCreateInfo.pNext = nullptr;
  ComputePipelineCreateInfo.flags = 0;
  ComputePipelineCreateInfo.stage = stage;
  ComputePipelineCreateInfo.layout = layout;
  ComputePipelineCreateInfo.basePipelineHandle = basePipelineHandle;
  ComputePipelineCreateInfo.basePipelineIndex = basePipelineIndex;
  return ComputePipelineCreateInfo;
}

inline VkPushConstantRange vkiPushConstantRange(VkShaderStageFlags stageFlags,
                                                uint32_t offset,
                                                uint32_t size) {
  VkPushConstantRange PushConstantRange = {};
  PushConstantRange.stageFlags = stageFlags;
  PushConstantRange.offset = offset;
  PushConstantRange.size = size;
  return PushConstantRange;
}

inline VkPipelineLayoutCreateInfo vkiPipelineLayoutCreateInfo(
    uint32_t setLayoutCount, const VkDescriptorSetLayout* pSetLayouts,
    uint32_t pushConstantRangeCount,
    const VkPushConstantRange* pPushConstantRanges) {
  VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo = {};
  PipelineLayoutCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  PipelineLayoutCreateInfo.pNext = nullptr;
  PipelineLayoutCreateInfo.flags = 0;
  PipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
  PipelineLayoutCreateInfo.pSetLayouts = pSetLayouts;
  PipelineLayoutCreateInfo.pushConstantRangeCount = pushConstantRangeCount;
  PipelineLayoutCreateInfo.pPushConstantRanges = pPushConstantRanges;
  return PipelineLayoutCreateInfo;
}

inline VkSamplerCreateInfo vkiSamplerCreateInfo(
    VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode,
    VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV,
    VkSamplerAddressMode addressModeW, float mipLodBias,
    VkBool32 anisotropyEnable, float maxAnisotropy, VkBool32 compareEnable,
    VkCompareOp compareOp, float minLod, float maxLod,
    VkBorderColor borderColor, VkBool32 unnormalizedCoordinates) {
  VkSamplerCreateInfo SamplerCreateInfo = {};
  SamplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  SamplerCreateInfo.pNext = nullptr;
  SamplerCreateInfo.flags = 0;
  SamplerCreateInfo.magFilter = magFilter;
  SamplerCreateInfo.minFilter = minFilter;
  SamplerCreateInfo.mipmapMode = mipmapMode;
  SamplerCreateInfo.addressModeU = addressModeU;
  SamplerCreateInfo.addressModeV = addressModeV;
  SamplerCreateInfo.addressModeW = addressModeW;
  SamplerCreateInfo.mipLodBias = mipLodBias;
  SamplerCreateInfo.anisotropyEnable = anisotropyEnable;
  SamplerCreateInfo.maxAnisotropy = maxAnisotropy;
  SamplerCreateInfo.compareEnable = compareEnable;
  SamplerCreateInfo.compareOp = compareOp;
  SamplerCreateInfo.minLod = minLod;
  SamplerCreateInfo.maxLod = maxLod;
  SamplerCreateInfo.borderColor = borderColor;
  SamplerCreateInfo.unnormalizedCoordinates = unnormalizedCoordinates;
  return SamplerCreateInfo;
}

inline VkDescriptorSetLayoutBinding vkiDescriptorSetLayoutBinding(
    uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount,
    VkShaderStageFlags stageFlags, const VkSampler* pImmutableSamplers) {
  VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding = {};
  DescriptorSetLayoutBinding.binding = binding;
  DescriptorSetLayoutBinding.descriptorType = descriptorType;
  DescriptorSetLayoutBinding.descriptorCount = descriptorCount;
  DescriptorSetLayoutBinding.stageFlags = stageFlags;
  DescriptorSetLayoutBinding.pImmutableSamplers = pImmutableSamplers;
  return DescriptorSetLayoutBinding;
}

inline VkDescriptorSetLayoutCreateInfo vkiDescriptorSetLayoutCreateInfo(
    uint32_t bindingCount, const VkDescriptorSetLayoutBinding* pBindings) {
  VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo = {};
  DescriptorSetLayoutCreateInfo.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  DescriptorSetLayoutCreateInfo.pNext = nullptr;
  DescriptorSetLayoutCreateInfo.flags = 0;
  DescriptorSetLayoutCreateInfo.bindingCount = bindingCount;
  DescriptorSetLayoutCreateInfo.pBindings = pBindings;
  return DescriptorSetLayoutCreateInfo;
}

inline VkDescriptorPoolSize vkiDescriptorPoolSize(VkDescriptorType type,
                                                  uint32_t descriptorCount) {
  VkDescriptorPoolSize DescriptorPoolSize = {};
  DescriptorPoolSize.type = type;
  DescriptorPoolSize.descriptorCount = descriptorCount;
  return DescriptorPoolSize;
}

inline VkDescriptorPoolCreateInfo vkiDescriptorPoolCreateInfo(
    uint32_t maxSets, uint32_t poolSizeCount,
    const VkDescriptorPoolSize* pPoolSizes) {
  VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo = {};
  DescriptorPoolCreateInfo.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  DescriptorPoolCreateInfo.pNext = nullptr;
  DescriptorPoolCreateInfo.flags = 0;
  DescriptorPoolCreateInfo.maxSets = maxSets;
  DescriptorPoolCreateInfo.poolSizeCount = poolSizeCount;
  DescriptorPoolCreateInfo.pPoolSizes = pPoolSizes;
  return DescriptorPoolCreateInfo;
}

inline VkDescriptorSetAllocateInfo vkiDescriptorSetAllocateInfo(
    VkDescriptorPool descriptorPool, uint32_t descriptorSetCount,
    const VkDescriptorSetLayout* pSetLayouts) {
  VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo = {};
  DescriptorSetAllocateInfo.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  DescriptorSetAllocateInfo.pNext = nullptr;
  DescriptorSetAllocateInfo.descriptorPool = descriptorPool;
  DescriptorSetAllocateInfo.descriptorSetCount = descriptorSetCount;
  DescriptorSetAllocateInfo.pSetLayouts = pSetLayouts;
  return DescriptorSetAllocateInfo;
}

inline VkDescriptorImageInfo vkiDescriptorImageInfo(VkSampler sampler,
                                                    VkImageView imageView,
                                                    VkImageLayout imageLayout) {
  VkDescriptorImageInfo DescriptorImageInfo = {};
  DescriptorImageInfo.sampler = sampler;
  DescriptorImageInfo.imageView = imageView;
  DescriptorImageInfo.imageLayout = imageLayout;
  return DescriptorImageInfo;
}

inline VkDescriptorBufferInfo vkiDescriptorBufferInfo(VkBuffer buffer,
                                                      VkDeviceSize offset,
                                                      VkDeviceSize range) {
  VkDescriptorBufferInfo DescriptorBufferInfo = {};
  DescriptorBufferInfo.buffer = buffer;
  DescriptorBufferInfo.offset = offset;
  DescriptorBufferInfo.range = range;
  return DescriptorBufferInfo;
}

inline VkWriteDescriptorSet vkiWriteDescriptorSet(
    VkDescriptorSet dstSet, uint32_t dstBinding, uint32_t dstArrayElement,
    uint32_t descriptorCount, VkDescriptorType descriptorType,
    const VkDescriptorImageInfo* pImageInfo,
    const VkDescriptorBufferInfo* pBufferInfo,
    const VkBufferView* pTexelBufferView) {
  VkWriteDescriptorSet WriteDescriptorSet = {};
  WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  WriteDescriptorSet.pNext = nullptr;
  WriteDescriptorSet.dstSet = dstSet;
  WriteDescriptorSet.dstBinding = dstBinding;
  WriteDescriptorSet.dstArrayElement = dstArrayElement;
  WriteDescriptorSet.descriptorCount = descriptorCount;
  WriteDescriptorSet.descriptorType = descriptorType;
  WriteDescriptorSet.pImageInfo = pImageInfo;
  WriteDescriptorSet.pBufferInfo = pBufferInfo;
  WriteDescriptorSet.pTexelBufferView = pTexelBufferView;
  return WriteDescriptorSet;
}

inline VkCopyDescriptorSet vkiCopyDescriptorSet(
    VkDescriptorSet srcSet, uint32_t srcBinding, uint32_t srcArrayElement,
    VkDescriptorSet dstSet, uint32_t dstBinding, uint32_t dstArrayElement,
    uint32_t descriptorCount) {
  VkCopyDescriptorSet CopyDescriptorSet = {};
  CopyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
  CopyDescriptorSet.pNext = nullptr;
  CopyDescriptorSet.srcSet = srcSet;
  CopyDescriptorSet.srcBinding = srcBinding;
  CopyDescriptorSet.srcArrayElement = srcArrayElement;
  CopyDescriptorSet.dstSet = dstSet;
  CopyDescriptorSet.dstBinding = dstBinding;
  CopyDescriptorSet.dstArrayElement = dstArrayElement;
  CopyDescriptorSet.descriptorCount = descriptorCount;
  return CopyDescriptorSet;
}

inline VkFramebufferCreateInfo vkiFramebufferCreateInfo(
    VkRenderPass renderPass, uint32_t attachmentCount,
    const VkImageView* pAttachments, uint32_t width, uint32_t height,
    uint32_t layers) {
  VkFramebufferCreateInfo FramebufferCreateInfo = {};
  FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  FramebufferCreateInfo.pNext = nullptr;
  FramebufferCreateInfo.flags = 0;
  FramebufferCreateInfo.renderPass = renderPass;
  FramebufferCreateInfo.attachmentCount = attachmentCount;
  FramebufferCreateInfo.pAttachments = pAttachments;
  FramebufferCreateInfo.width = width;
  FramebufferCreateInfo.height = height;
  FramebufferCreateInfo.layers = layers;
  return FramebufferCreateInfo;
}

inline VkAttachmentDescription vkiAttachmentDescription(
    VkFormat format, VkSampleCountFlagBits samples, VkAttachmentLoadOp loadOp,
    VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp,
    VkAttachmentStoreOp stencilStoreOp, VkImageLayout initialLayout,
    VkImageLayout finalLayout) {
  VkAttachmentDescription AttachmentDescription = {};
  AttachmentDescription.flags = 0;
  AttachmentDescription.format = format;
  AttachmentDescription.samples = samples;
  AttachmentDescription.loadOp = loadOp;
  AttachmentDescription.storeOp = storeOp;
  AttachmentDescription.stencilLoadOp = stencilLoadOp;
  AttachmentDescription.stencilStoreOp = stencilStoreOp;
  AttachmentDescription.initialLayout = initialLayout;
  AttachmentDescription.finalLayout = finalLayout;
  return AttachmentDescription;
}

inline VkAttachmentReference vkiAttachmentReference(uint32_t attachment,
                                                    VkImageLayout layout) {
  VkAttachmentReference AttachmentReference = {};
  AttachmentReference.attachment = attachment;
  AttachmentReference.layout = layout;
  return AttachmentReference;
}

inline VkSubpassDescription vkiSubpassDescription(
    VkPipelineBindPoint pipelineBindPoint, uint32_t inputAttachmentCount,
    const VkAttachmentReference* pInputAttachments,
    uint32_t colorAttachmentCount,
    const VkAttachmentReference* pColorAttachments,
    const VkAttachmentReference* pResolveAttachments,
    const VkAttachmentReference* pDepthStencilAttachment,
    uint32_t preserveAttachmentCount, const uint32_t* pPreserveAttachments) {
  VkSubpassDescription SubpassDescription = {};
  SubpassDescription.flags = 0;
  SubpassDescription.pipelineBindPoint = pipelineBindPoint;
  SubpassDescription.inputAttachmentCount = inputAttachmentCount;
  SubpassDescription.pInputAttachments = pInputAttachments;
  SubpassDescription.colorAttachmentCount = colorAttachmentCount;
  SubpassDescription.pColorAttachments = pColorAttachments;
  SubpassDescription.pResolveAttachments = pResolveAttachments;
  SubpassDescription.pDepthStencilAttachment = pDepthStencilAttachment;
  SubpassDescription.preserveAttachmentCount = preserveAttachmentCount;
  SubpassDescription.pPreserveAttachments = pPreserveAttachments;
  return SubpassDescription;
}

inline VkSubpassDependency vkiSubpassDependency(
    uint32_t srcSubpass, uint32_t dstSubpass, VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask, VkAccessFlags srcAccessMask,
    VkAccessFlags dstAccessMask, VkDependencyFlags dependencyFlags) {
  VkSubpassDependency SubpassDependency = {};
  SubpassDependency.srcSubpass = srcSubpass;
  SubpassDependency.dstSubpass = dstSubpass;
  SubpassDependency.srcStageMask = srcStageMask;
  SubpassDependency.dstStageMask = dstStageMask;
  SubpassDependency.srcAccessMask = srcAccessMask;
  SubpassDependency.dstAccessMask = dstAccessMask;
  SubpassDependency.dependencyFlags = dependencyFlags;
  return SubpassDependency;
}

inline VkRenderPassCreateInfo vkiRenderPassCreateInfo(
    uint32_t attachmentCount, const VkAttachmentDescription* pAttachments,
    uint32_t subpassCount, const VkSubpassDescription* pSubpasses,
    uint32_t dependencyCount, const VkSubpassDependency* pDependencies) {
  VkRenderPassCreateInfo RenderPassCreateInfo = {};
  RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  RenderPassCreateInfo.pNext = nullptr;
  RenderPassCreateInfo.flags = 0;
  RenderPassCreateInfo.attachmentCount = attachmentCount;
  RenderPassCreateInfo.pAttachments = pAttachments;
  RenderPassCreateInfo.subpassCount = subpassCount;
  RenderPassCreateInfo.pSubpasses = pSubpasses;
  RenderPassCreateInfo.dependencyCount = dependencyCount;
  RenderPassCreateInfo.pDependencies = pDependencies;
  return RenderPassCreateInfo;
}

inline VkCommandPoolCreateInfo vkiCommandPoolCreateInfo(
    uint32_t queueFamilyIndex) {
  VkCommandPoolCreateInfo CommandPoolCreateInfo = {};
  CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  CommandPoolCreateInfo.pNext = nullptr;
  CommandPoolCreateInfo.flags = 0;
  CommandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
  return CommandPoolCreateInfo;
}

inline VkCommandBufferAllocateInfo vkiCommandBufferAllocateInfo(
    VkCommandPool commandPool, VkCommandBufferLevel level,
    uint32_t commandBufferCount) {
  VkCommandBufferAllocateInfo CommandBufferAllocateInfo = {};
  CommandBufferAllocateInfo.sType =
      VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  CommandBufferAllocateInfo.pNext = nullptr;
  CommandBufferAllocateInfo.commandPool = commandPool;
  CommandBufferAllocateInfo.level = level;
  CommandBufferAllocateInfo.commandBufferCount = commandBufferCount;
  return CommandBufferAllocateInfo;
}

inline VkCommandBufferInheritanceInfo vkiCommandBufferInheritanceInfo(
    VkRenderPass renderPass, uint32_t subpass, VkFramebuffer framebuffer,
    VkBool32 occlusionQueryEnable, VkQueryControlFlags queryFlags,
    VkQueryPipelineStatisticFlags pipelineStatistics) {
  VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo = {};
  CommandBufferInheritanceInfo.sType =
      VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  CommandBufferInheritanceInfo.pNext = nullptr;
  CommandBufferInheritanceInfo.renderPass = renderPass;
  CommandBufferInheritanceInfo.subpass = subpass;
  CommandBufferInheritanceInfo.framebuffer = framebuffer;
  CommandBufferInheritanceInfo.occlusionQueryEnable = occlusionQueryEnable;
  CommandBufferInheritanceInfo.queryFlags = queryFlags;
  CommandBufferInheritanceInfo.pipelineStatistics = pipelineStatistics;
  return CommandBufferInheritanceInfo;
}

inline VkCommandBufferBeginInfo vkiCommandBufferBeginInfo(
    const VkCommandBufferInheritanceInfo* pInheritanceInfo) {
  VkCommandBufferBeginInfo CommandBufferBeginInfo = {};
  CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  CommandBufferBeginInfo.pNext = nullptr;
  CommandBufferBeginInfo.flags = 0;
  CommandBufferBeginInfo.pInheritanceInfo = pInheritanceInfo;
  return CommandBufferBeginInfo;
}

inline VkBufferCopy vkiBufferCopy(VkDeviceSize srcOffset,
                                  VkDeviceSize dstOffset, VkDeviceSize size) {
  VkBufferCopy BufferCopy = {};
  BufferCopy.srcOffset = srcOffset;
  BufferCopy.dstOffset = dstOffset;
  BufferCopy.size = size;
  return BufferCopy;
}

inline VkImageSubresourceLayers vkiImageSubresourceLayers(
    VkImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t baseArrayLayer,
    uint32_t layerCount) {
  VkImageSubresourceLayers ImageSubresourceLayers = {};
  ImageSubresourceLayers.aspectMask = aspectMask;
  ImageSubresourceLayers.mipLevel = mipLevel;
  ImageSubresourceLayers.baseArrayLayer = baseArrayLayer;
  ImageSubresourceLayers.layerCount = layerCount;
  return ImageSubresourceLayers;
}

inline VkImageCopy vkiImageCopy(VkImageSubresourceLayers srcSubresource,
                                VkOffset3D srcOffset,
                                VkImageSubresourceLayers dstSubresource,
                                VkOffset3D dstOffset, VkExtent3D extent) {
  VkImageCopy ImageCopy = {};
  ImageCopy.srcSubresource = srcSubresource;
  ImageCopy.srcOffset = srcOffset;
  ImageCopy.dstSubresource = dstSubresource;
  ImageCopy.dstOffset = dstOffset;
  ImageCopy.extent = extent;
  return ImageCopy;
}

// inline VkImageBlit vkiImageBlit(VkImageSubresourceLayers srcSubresource,
// VkOffset3D srcOffsets[2], VkImageSubresourceLayers dstSubresource, VkOffset3D
// dstOffsets[2]) {
//     VkImageBlit ImageBlit = {};
//     ImageBlit.srcSubresource = srcSubresource;
//     ImageBlit.srcOffsets[2] = srcOffsets[2];
//     ImageBlit.dstSubresource = dstSubresource;
//     ImageBlit.dstOffsets[2] = dstOffsets[2];
//     return ImageBlit;
// }

inline VkBufferImageCopy vkiBufferImageCopy(
    VkDeviceSize bufferOffset, uint32_t bufferRowLength,
    uint32_t bufferImageHeight, VkImageSubresourceLayers imageSubresource,
    VkOffset3D imageOffset, VkExtent3D imageExtent) {
  VkBufferImageCopy BufferImageCopy = {};
  BufferImageCopy.bufferOffset = bufferOffset;
  BufferImageCopy.bufferRowLength = bufferRowLength;
  BufferImageCopy.bufferImageHeight = bufferImageHeight;
  BufferImageCopy.imageSubresource = imageSubresource;
  BufferImageCopy.imageOffset = imageOffset;
  BufferImageCopy.imageExtent = imageExtent;
  return BufferImageCopy;
}

inline VkClearDepthStencilValue vkiClearDepthStencilValue(float depth,
                                                          uint32_t stencil) {
  VkClearDepthStencilValue ClearDepthStencilValue = {};
  ClearDepthStencilValue.depth = depth;
  ClearDepthStencilValue.stencil = stencil;
  return ClearDepthStencilValue;
}

inline VkClearAttachment vkiClearAttachment(VkImageAspectFlags aspectMask,
                                            uint32_t colorAttachment,
                                            VkClearValue clearValue) {
  VkClearAttachment ClearAttachment = {};
  ClearAttachment.aspectMask = aspectMask;
  ClearAttachment.colorAttachment = colorAttachment;
  ClearAttachment.clearValue = clearValue;
  return ClearAttachment;
}

inline VkClearRect vkiClearRect(VkRect2D rect, uint32_t baseArrayLayer,
                                uint32_t layerCount) {
  VkClearRect ClearRect = {};
  ClearRect.rect = rect;
  ClearRect.baseArrayLayer = baseArrayLayer;
  ClearRect.layerCount = layerCount;
  return ClearRect;
}

inline VkImageResolve vkiImageResolve(VkImageSubresourceLayers srcSubresource,
                                      VkOffset3D srcOffset,
                                      VkImageSubresourceLayers dstSubresource,
                                      VkOffset3D dstOffset, VkExtent3D extent) {
  VkImageResolve ImageResolve = {};
  ImageResolve.srcSubresource = srcSubresource;
  ImageResolve.srcOffset = srcOffset;
  ImageResolve.dstSubresource = dstSubresource;
  ImageResolve.dstOffset = dstOffset;
  ImageResolve.extent = extent;
  return ImageResolve;
}

inline VkMemoryBarrier vkiMemoryBarrier(VkAccessFlags srcAccessMask,
                                        VkAccessFlags dstAccessMask) {
  VkMemoryBarrier MemoryBarrier = {};
  MemoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
  MemoryBarrier.pNext = nullptr;
  MemoryBarrier.srcAccessMask = srcAccessMask;
  MemoryBarrier.dstAccessMask = dstAccessMask;
  return MemoryBarrier;
}

inline VkBufferMemoryBarrier vkiBufferMemoryBarrier(
    VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask,
    uint32_t srcQueueFamilyIndex, uint32_t dstQueueFamilyIndex, VkBuffer buffer,
    VkDeviceSize offset, VkDeviceSize size) {
  VkBufferMemoryBarrier BufferMemoryBarrier = {};
  BufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
  BufferMemoryBarrier.pNext = nullptr;
  BufferMemoryBarrier.srcAccessMask = srcAccessMask;
  BufferMemoryBarrier.dstAccessMask = dstAccessMask;
  BufferMemoryBarrier.srcQueueFamilyIndex = srcQueueFamilyIndex;
  BufferMemoryBarrier.dstQueueFamilyIndex = dstQueueFamilyIndex;
  BufferMemoryBarrier.buffer = buffer;
  BufferMemoryBarrier.offset = offset;
  BufferMemoryBarrier.size = size;
  return BufferMemoryBarrier;
}

inline VkImageMemoryBarrier vkiImageMemoryBarrier(
    VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask,
    VkImageLayout oldLayout, VkImageLayout newLayout,
    uint32_t srcQueueFamilyIndex, uint32_t dstQueueFamilyIndex, VkImage image,
    VkImageSubresourceRange subresourceRange) {
  VkImageMemoryBarrier ImageMemoryBarrier = {};
  ImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  ImageMemoryBarrier.pNext = nullptr;
  ImageMemoryBarrier.srcAccessMask = srcAccessMask;
  ImageMemoryBarrier.dstAccessMask = dstAccessMask;
  ImageMemoryBarrier.oldLayout = oldLayout;
  ImageMemoryBarrier.newLayout = newLayout;
  ImageMemoryBarrier.srcQueueFamilyIndex = srcQueueFamilyIndex;
  ImageMemoryBarrier.dstQueueFamilyIndex = dstQueueFamilyIndex;
  ImageMemoryBarrier.image = image;
  ImageMemoryBarrier.subresourceRange = subresourceRange;
  return ImageMemoryBarrier;
}

inline VkRenderPassBeginInfo vkiRenderPassBeginInfo(
    VkRenderPass renderPass, VkFramebuffer framebuffer, VkRect2D renderArea,
    uint32_t clearValueCount, const VkClearValue* pClearValues) {
  VkRenderPassBeginInfo RenderPassBeginInfo = {};
  RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  RenderPassBeginInfo.pNext = nullptr;
  RenderPassBeginInfo.renderPass = renderPass;
  RenderPassBeginInfo.framebuffer = framebuffer;
  RenderPassBeginInfo.renderArea = renderArea;
  RenderPassBeginInfo.clearValueCount = clearValueCount;
  RenderPassBeginInfo.pClearValues = pClearValues;
  return RenderPassBeginInfo;
}

inline VkDispatchIndirectCommand vkiDispatchIndirectCommand(uint32_t x,
                                                            uint32_t y,
                                                            uint32_t z) {
  VkDispatchIndirectCommand DispatchIndirectCommand = {};
  DispatchIndirectCommand.x = x;
  DispatchIndirectCommand.y = y;
  DispatchIndirectCommand.z = z;
  return DispatchIndirectCommand;
}

inline VkDrawIndexedIndirectCommand vkiDrawIndexedIndirectCommand(
    uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex,
    int32_t vertexOffset, uint32_t firstInstance) {
  VkDrawIndexedIndirectCommand DrawIndexedIndirectCommand = {};
  DrawIndexedIndirectCommand.indexCount = indexCount;
  DrawIndexedIndirectCommand.instanceCount = instanceCount;
  DrawIndexedIndirectCommand.firstIndex = firstIndex;
  DrawIndexedIndirectCommand.vertexOffset = vertexOffset;
  DrawIndexedIndirectCommand.firstInstance = firstInstance;
  return DrawIndexedIndirectCommand;
}

inline VkDrawIndirectCommand vkiDrawIndirectCommand(uint32_t vertexCount,
                                                    uint32_t instanceCount,
                                                    uint32_t firstVertex,
                                                    uint32_t firstInstance) {
  VkDrawIndirectCommand DrawIndirectCommand = {};
  DrawIndirectCommand.vertexCount = vertexCount;
  DrawIndirectCommand.instanceCount = instanceCount;
  DrawIndirectCommand.firstVertex = firstVertex;
  DrawIndirectCommand.firstInstance = firstInstance;
  return DrawIndirectCommand;
}

inline VkPhysicalDeviceSubgroupProperties vkiPhysicalDeviceSubgroupProperties(
    uint32_t subgroupSize, VkShaderStageFlags supportedStages,
    VkSubgroupFeatureFlags supportedOperations,
    VkBool32 quadOperationsInAllStages) {
  VkPhysicalDeviceSubgroupProperties PhysicalDeviceSubgroupProperties = {};
  PhysicalDeviceSubgroupProperties.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
  PhysicalDeviceSubgroupProperties.pNext = nullptr;
  PhysicalDeviceSubgroupProperties.subgroupSize = subgroupSize;
  PhysicalDeviceSubgroupProperties.supportedStages = supportedStages;
  PhysicalDeviceSubgroupProperties.supportedOperations = supportedOperations;
  PhysicalDeviceSubgroupProperties.quadOperationsInAllStages =
      quadOperationsInAllStages;
  return PhysicalDeviceSubgroupProperties;
}

inline VkBindBufferMemoryInfo vkiBindBufferMemoryInfo(
    VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
  VkBindBufferMemoryInfo BindBufferMemoryInfo = {};
  BindBufferMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO;
  BindBufferMemoryInfo.pNext = nullptr;
  BindBufferMemoryInfo.buffer = buffer;
  BindBufferMemoryInfo.memory = memory;
  BindBufferMemoryInfo.memoryOffset = memoryOffset;
  return BindBufferMemoryInfo;
}

inline VkBindImageMemoryInfo vkiBindImageMemoryInfo(VkImage image,
                                                    VkDeviceMemory memory,
                                                    VkDeviceSize memoryOffset) {
  VkBindImageMemoryInfo BindImageMemoryInfo = {};
  BindImageMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
  BindImageMemoryInfo.pNext = nullptr;
  BindImageMemoryInfo.image = image;
  BindImageMemoryInfo.memory = memory;
  BindImageMemoryInfo.memoryOffset = memoryOffset;
  return BindImageMemoryInfo;
}

inline VkPhysicalDevice16BitStorageFeatures
vkiPhysicalDevice16BitStorageFeatures(
    VkBool32 storageBuffer16BitAccess,
    VkBool32 uniformAndStorageBuffer16BitAccess, VkBool32 storagePushConstant16,
    VkBool32 storageInputOutput16) {
  VkPhysicalDevice16BitStorageFeatures PhysicalDevice16BitStorageFeatures = {};
  PhysicalDevice16BitStorageFeatures.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
  PhysicalDevice16BitStorageFeatures.pNext = nullptr;
  PhysicalDevice16BitStorageFeatures.storageBuffer16BitAccess =
      storageBuffer16BitAccess;
  PhysicalDevice16BitStorageFeatures.uniformAndStorageBuffer16BitAccess =
      uniformAndStorageBuffer16BitAccess;
  PhysicalDevice16BitStorageFeatures.storagePushConstant16 =
      storagePushConstant16;
  PhysicalDevice16BitStorageFeatures.storageInputOutput16 =
      storageInputOutput16;
  return PhysicalDevice16BitStorageFeatures;
}

inline VkMemoryDedicatedRequirements vkiMemoryDedicatedRequirements(
    VkBool32 prefersDedicatedAllocation, VkBool32 requiresDedicatedAllocation) {
  VkMemoryDedicatedRequirements MemoryDedicatedRequirements = {};
  MemoryDedicatedRequirements.sType =
      VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
  MemoryDedicatedRequirements.pNext = nullptr;
  MemoryDedicatedRequirements.prefersDedicatedAllocation =
      prefersDedicatedAllocation;
  MemoryDedicatedRequirements.requiresDedicatedAllocation =
      requiresDedicatedAllocation;
  return MemoryDedicatedRequirements;
}

inline VkMemoryDedicatedAllocateInfo vkiMemoryDedicatedAllocateInfo(
    VkImage image, VkBuffer buffer) {
  VkMemoryDedicatedAllocateInfo MemoryDedicatedAllocateInfo = {};
  MemoryDedicatedAllocateInfo.sType =
      VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
  MemoryDedicatedAllocateInfo.pNext = nullptr;
  MemoryDedicatedAllocateInfo.image = image;
  MemoryDedicatedAllocateInfo.buffer = buffer;
  return MemoryDedicatedAllocateInfo;
}

inline VkMemoryAllocateFlagsInfo vkiMemoryAllocateFlagsInfo(
    uint32_t deviceMask) {
  VkMemoryAllocateFlagsInfo MemoryAllocateFlagsInfo = {};
  MemoryAllocateFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
  MemoryAllocateFlagsInfo.pNext = nullptr;
  MemoryAllocateFlagsInfo.flags = 0;
  MemoryAllocateFlagsInfo.deviceMask = deviceMask;
  return MemoryAllocateFlagsInfo;
}

inline VkDeviceGroupRenderPassBeginInfo vkiDeviceGroupRenderPassBeginInfo(
    uint32_t deviceMask, uint32_t deviceRenderAreaCount,
    const VkRect2D* pDeviceRenderAreas) {
  VkDeviceGroupRenderPassBeginInfo DeviceGroupRenderPassBeginInfo = {};
  DeviceGroupRenderPassBeginInfo.sType =
      VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO;
  DeviceGroupRenderPassBeginInfo.pNext = nullptr;
  DeviceGroupRenderPassBeginInfo.deviceMask = deviceMask;
  DeviceGroupRenderPassBeginInfo.deviceRenderAreaCount = deviceRenderAreaCount;
  DeviceGroupRenderPassBeginInfo.pDeviceRenderAreas = pDeviceRenderAreas;
  return DeviceGroupRenderPassBeginInfo;
}

inline VkDeviceGroupCommandBufferBeginInfo vkiDeviceGroupCommandBufferBeginInfo(
    uint32_t deviceMask) {
  VkDeviceGroupCommandBufferBeginInfo DeviceGroupCommandBufferBeginInfo = {};
  DeviceGroupCommandBufferBeginInfo.sType =
      VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO;
  DeviceGroupCommandBufferBeginInfo.pNext = nullptr;
  DeviceGroupCommandBufferBeginInfo.deviceMask = deviceMask;
  return DeviceGroupCommandBufferBeginInfo;
}

inline VkDeviceGroupSubmitInfo vkiDeviceGroupSubmitInfo(
    uint32_t waitSemaphoreCount, const uint32_t* pWaitSemaphoreDeviceIndices,
    uint32_t commandBufferCount, const uint32_t* pCommandBufferDeviceMasks,
    uint32_t signalSemaphoreCount,
    const uint32_t* pSignalSemaphoreDeviceIndices) {
  VkDeviceGroupSubmitInfo DeviceGroupSubmitInfo = {};
  DeviceGroupSubmitInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
  DeviceGroupSubmitInfo.pNext = nullptr;
  DeviceGroupSubmitInfo.waitSemaphoreCount = waitSemaphoreCount;
  DeviceGroupSubmitInfo.pWaitSemaphoreDeviceIndices =
      pWaitSemaphoreDeviceIndices;
  DeviceGroupSubmitInfo.commandBufferCount = commandBufferCount;
  DeviceGroupSubmitInfo.pCommandBufferDeviceMasks = pCommandBufferDeviceMasks;
  DeviceGroupSubmitInfo.signalSemaphoreCount = signalSemaphoreCount;
  DeviceGroupSubmitInfo.pSignalSemaphoreDeviceIndices =
      pSignalSemaphoreDeviceIndices;
  return DeviceGroupSubmitInfo;
}

inline VkDeviceGroupBindSparseInfo vkiDeviceGroupBindSparseInfo(
    uint32_t resourceDeviceIndex, uint32_t memoryDeviceIndex) {
  VkDeviceGroupBindSparseInfo DeviceGroupBindSparseInfo = {};
  DeviceGroupBindSparseInfo.sType =
      VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO;
  DeviceGroupBindSparseInfo.pNext = nullptr;
  DeviceGroupBindSparseInfo.resourceDeviceIndex = resourceDeviceIndex;
  DeviceGroupBindSparseInfo.memoryDeviceIndex = memoryDeviceIndex;
  return DeviceGroupBindSparseInfo;
}

inline VkBindBufferMemoryDeviceGroupInfo vkiBindBufferMemoryDeviceGroupInfo(
    uint32_t deviceIndexCount, const uint32_t* pDeviceIndices) {
  VkBindBufferMemoryDeviceGroupInfo BindBufferMemoryDeviceGroupInfo = {};
  BindBufferMemoryDeviceGroupInfo.sType =
      VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO;
  BindBufferMemoryDeviceGroupInfo.pNext = nullptr;
  BindBufferMemoryDeviceGroupInfo.deviceIndexCount = deviceIndexCount;
  BindBufferMemoryDeviceGroupInfo.pDeviceIndices = pDeviceIndices;
  return BindBufferMemoryDeviceGroupInfo;
}

inline VkBindImageMemoryDeviceGroupInfo vkiBindImageMemoryDeviceGroupInfo(
    uint32_t deviceIndexCount, const uint32_t* pDeviceIndices,
    uint32_t splitInstanceBindRegionCount,
    const VkRect2D* pSplitInstanceBindRegions) {
  VkBindImageMemoryDeviceGroupInfo BindImageMemoryDeviceGroupInfo = {};
  BindImageMemoryDeviceGroupInfo.sType =
      VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO;
  BindImageMemoryDeviceGroupInfo.pNext = nullptr;
  BindImageMemoryDeviceGroupInfo.deviceIndexCount = deviceIndexCount;
  BindImageMemoryDeviceGroupInfo.pDeviceIndices = pDeviceIndices;
  BindImageMemoryDeviceGroupInfo.splitInstanceBindRegionCount =
      splitInstanceBindRegionCount;
  BindImageMemoryDeviceGroupInfo.pSplitInstanceBindRegions =
      pSplitInstanceBindRegions;
  return BindImageMemoryDeviceGroupInfo;
}

// inline VkPhysicalDeviceGroupProperties
// vkiPhysicalDeviceGroupProperties(uint32_t physicalDeviceCount,
// VkPhysicalDevice physicalDevices[VK_MAX_DEVICE_GROUP_SIZE], VkBool32
// subsetAllocation) {
//     VkPhysicalDeviceGroupProperties PhysicalDeviceGroupProperties = {};
//     PhysicalDeviceGroupProperties.sType =
//     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
//     PhysicalDeviceGroupProperties.pNext = nullptr;
//     PhysicalDeviceGroupProperties.physicalDeviceCount = physicalDeviceCount;
//     PhysicalDeviceGroupProperties.physicalDevices[VK_MAX_DEVICE_GROUP_SIZE] =
//     physicalDevices[VK_MAX_DEVICE_GROUP_SIZE];
//     PhysicalDeviceGroupProperties.subsetAllocation = subsetAllocation;
//     return PhysicalDeviceGroupProperties;
// }

inline VkDeviceGroupDeviceCreateInfo vkiDeviceGroupDeviceCreateInfo(
    uint32_t physicalDeviceCount, const VkPhysicalDevice* pPhysicalDevices) {
  VkDeviceGroupDeviceCreateInfo DeviceGroupDeviceCreateInfo = {};
  DeviceGroupDeviceCreateInfo.sType =
      VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
  DeviceGroupDeviceCreateInfo.pNext = nullptr;
  DeviceGroupDeviceCreateInfo.physicalDeviceCount = physicalDeviceCount;
  DeviceGroupDeviceCreateInfo.pPhysicalDevices = pPhysicalDevices;
  return DeviceGroupDeviceCreateInfo;
}

inline VkBufferMemoryRequirementsInfo2 vkiBufferMemoryRequirementsInfo2(
    VkBuffer buffer) {
  VkBufferMemoryRequirementsInfo2 BufferMemoryRequirementsInfo2 = {};
  BufferMemoryRequirementsInfo2.sType =
      VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
  BufferMemoryRequirementsInfo2.pNext = nullptr;
  BufferMemoryRequirementsInfo2.buffer = buffer;
  return BufferMemoryRequirementsInfo2;
}

inline VkImageMemoryRequirementsInfo2 vkiImageMemoryRequirementsInfo2(
    VkImage image) {
  VkImageMemoryRequirementsInfo2 ImageMemoryRequirementsInfo2 = {};
  ImageMemoryRequirementsInfo2.sType =
      VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
  ImageMemoryRequirementsInfo2.pNext = nullptr;
  ImageMemoryRequirementsInfo2.image = image;
  return ImageMemoryRequirementsInfo2;
}

inline VkImageSparseMemoryRequirementsInfo2
vkiImageSparseMemoryRequirementsInfo2(VkImage image) {
  VkImageSparseMemoryRequirementsInfo2 ImageSparseMemoryRequirementsInfo2 = {};
  ImageSparseMemoryRequirementsInfo2.sType =
      VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2;
  ImageSparseMemoryRequirementsInfo2.pNext = nullptr;
  ImageSparseMemoryRequirementsInfo2.image = image;
  return ImageSparseMemoryRequirementsInfo2;
}

inline VkMemoryRequirements2 vkiMemoryRequirements2(
    VkMemoryRequirements memoryRequirements) {
  VkMemoryRequirements2 MemoryRequirements2 = {};
  MemoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  MemoryRequirements2.pNext = nullptr;
  MemoryRequirements2.memoryRequirements = memoryRequirements;
  return MemoryRequirements2;
}

inline VkSparseImageMemoryRequirements2 vkiSparseImageMemoryRequirements2(
    VkSparseImageMemoryRequirements memoryRequirements) {
  VkSparseImageMemoryRequirements2 SparseImageMemoryRequirements2 = {};
  SparseImageMemoryRequirements2.sType =
      VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2;
  SparseImageMemoryRequirements2.pNext = nullptr;
  SparseImageMemoryRequirements2.memoryRequirements = memoryRequirements;
  return SparseImageMemoryRequirements2;
}

inline VkPhysicalDeviceFeatures2 vkiPhysicalDeviceFeatures2(
    VkPhysicalDeviceFeatures features) {
  VkPhysicalDeviceFeatures2 PhysicalDeviceFeatures2 = {};
  PhysicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
  PhysicalDeviceFeatures2.pNext = nullptr;
  PhysicalDeviceFeatures2.features = features;
  return PhysicalDeviceFeatures2;
}

inline VkPhysicalDeviceProperties2 vkiPhysicalDeviceProperties2(
    VkPhysicalDeviceProperties properties) {
  VkPhysicalDeviceProperties2 PhysicalDeviceProperties2 = {};
  PhysicalDeviceProperties2.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
  PhysicalDeviceProperties2.pNext = nullptr;
  PhysicalDeviceProperties2.properties = properties;
  return PhysicalDeviceProperties2;
}

inline VkFormatProperties2 vkiFormatProperties2(
    VkFormatProperties formatProperties) {
  VkFormatProperties2 FormatProperties2 = {};
  FormatProperties2.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
  FormatProperties2.pNext = nullptr;
  FormatProperties2.formatProperties = formatProperties;
  return FormatProperties2;
}

inline VkImageFormatProperties2 vkiImageFormatProperties2(
    VkImageFormatProperties imageFormatProperties) {
  VkImageFormatProperties2 ImageFormatProperties2 = {};
  ImageFormatProperties2.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
  ImageFormatProperties2.pNext = nullptr;
  ImageFormatProperties2.imageFormatProperties = imageFormatProperties;
  return ImageFormatProperties2;
}

inline VkPhysicalDeviceImageFormatInfo2 vkiPhysicalDeviceImageFormatInfo2(
    VkFormat format, VkImageType type, VkImageTiling tiling,
    VkImageUsageFlags usage) {
  VkPhysicalDeviceImageFormatInfo2 PhysicalDeviceImageFormatInfo2 = {};
  PhysicalDeviceImageFormatInfo2.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
  PhysicalDeviceImageFormatInfo2.pNext = nullptr;
  PhysicalDeviceImageFormatInfo2.flags = 0;
  PhysicalDeviceImageFormatInfo2.format = format;
  PhysicalDeviceImageFormatInfo2.type = type;
  PhysicalDeviceImageFormatInfo2.tiling = tiling;
  PhysicalDeviceImageFormatInfo2.usage = usage;
  return PhysicalDeviceImageFormatInfo2;
}

inline VkQueueFamilyProperties2 vkiQueueFamilyProperties2(
    VkQueueFamilyProperties queueFamilyProperties) {
  VkQueueFamilyProperties2 QueueFamilyProperties2 = {};
  QueueFamilyProperties2.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
  QueueFamilyProperties2.pNext = nullptr;
  QueueFamilyProperties2.queueFamilyProperties = queueFamilyProperties;
  return QueueFamilyProperties2;
}

inline VkPhysicalDeviceMemoryProperties2 vkiPhysicalDeviceMemoryProperties2(
    VkPhysicalDeviceMemoryProperties memoryProperties) {
  VkPhysicalDeviceMemoryProperties2 PhysicalDeviceMemoryProperties2 = {};
  PhysicalDeviceMemoryProperties2.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
  PhysicalDeviceMemoryProperties2.pNext = nullptr;
  PhysicalDeviceMemoryProperties2.memoryProperties = memoryProperties;
  return PhysicalDeviceMemoryProperties2;
}

inline VkSparseImageFormatProperties2 vkiSparseImageFormatProperties2(
    VkSparseImageFormatProperties properties) {
  VkSparseImageFormatProperties2 SparseImageFormatProperties2 = {};
  SparseImageFormatProperties2.sType =
      VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2;
  SparseImageFormatProperties2.pNext = nullptr;
  SparseImageFormatProperties2.properties = properties;
  return SparseImageFormatProperties2;
}

inline VkPhysicalDeviceSparseImageFormatInfo2
vkiPhysicalDeviceSparseImageFormatInfo2(VkFormat format, VkImageType type,
                                        VkSampleCountFlagBits samples,
                                        VkImageUsageFlags usage,
                                        VkImageTiling tiling) {
  VkPhysicalDeviceSparseImageFormatInfo2 PhysicalDeviceSparseImageFormatInfo2 =
      {};
  PhysicalDeviceSparseImageFormatInfo2.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2;
  PhysicalDeviceSparseImageFormatInfo2.pNext = nullptr;
  PhysicalDeviceSparseImageFormatInfo2.format = format;
  PhysicalDeviceSparseImageFormatInfo2.type = type;
  PhysicalDeviceSparseImageFormatInfo2.samples = samples;
  PhysicalDeviceSparseImageFormatInfo2.usage = usage;
  PhysicalDeviceSparseImageFormatInfo2.tiling = tiling;
  return PhysicalDeviceSparseImageFormatInfo2;
}

inline VkPhysicalDevicePointClippingProperties
vkiPhysicalDevicePointClippingProperties(
    VkPointClippingBehavior pointClippingBehavior) {
  VkPhysicalDevicePointClippingProperties
      PhysicalDevicePointClippingProperties = {};
  PhysicalDevicePointClippingProperties.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
  PhysicalDevicePointClippingProperties.pNext = nullptr;
  PhysicalDevicePointClippingProperties.pointClippingBehavior =
      pointClippingBehavior;
  return PhysicalDevicePointClippingProperties;
}

inline VkInputAttachmentAspectReference vkiInputAttachmentAspectReference(
    uint32_t subpass, uint32_t inputAttachmentIndex,
    VkImageAspectFlags aspectMask) {
  VkInputAttachmentAspectReference InputAttachmentAspectReference = {};
  InputAttachmentAspectReference.subpass = subpass;
  InputAttachmentAspectReference.inputAttachmentIndex = inputAttachmentIndex;
  InputAttachmentAspectReference.aspectMask = aspectMask;
  return InputAttachmentAspectReference;
}

inline VkRenderPassInputAttachmentAspectCreateInfo
vkiRenderPassInputAttachmentAspectCreateInfo(
    uint32_t aspectReferenceCount,
    const VkInputAttachmentAspectReference* pAspectReferences) {
  VkRenderPassInputAttachmentAspectCreateInfo
      RenderPassInputAttachmentAspectCreateInfo = {};
  RenderPassInputAttachmentAspectCreateInfo.sType =
      VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
  RenderPassInputAttachmentAspectCreateInfo.pNext = nullptr;
  RenderPassInputAttachmentAspectCreateInfo.aspectReferenceCount =
      aspectReferenceCount;
  RenderPassInputAttachmentAspectCreateInfo.pAspectReferences =
      pAspectReferences;
  return RenderPassInputAttachmentAspectCreateInfo;
}

inline VkImageViewUsageCreateInfo vkiImageViewUsageCreateInfo(
    VkImageUsageFlags usage) {
  VkImageViewUsageCreateInfo ImageViewUsageCreateInfo = {};
  ImageViewUsageCreateInfo.sType =
      VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
  ImageViewUsageCreateInfo.pNext = nullptr;
  ImageViewUsageCreateInfo.usage = usage;
  return ImageViewUsageCreateInfo;
}

inline VkPipelineTessellationDomainOriginStateCreateInfo
vkiPipelineTessellationDomainOriginStateCreateInfo(
    VkTessellationDomainOrigin domainOrigin) {
  VkPipelineTessellationDomainOriginStateCreateInfo
      PipelineTessellationDomainOriginStateCreateInfo = {};
  PipelineTessellationDomainOriginStateCreateInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO;
  PipelineTessellationDomainOriginStateCreateInfo.pNext = nullptr;
  PipelineTessellationDomainOriginStateCreateInfo.domainOrigin = domainOrigin;
  return PipelineTessellationDomainOriginStateCreateInfo;
}

inline VkRenderPassMultiviewCreateInfo vkiRenderPassMultiviewCreateInfo(
    uint32_t subpassCount, const uint32_t* pViewMasks, uint32_t dependencyCount,
    const int32_t* pViewOffsets, uint32_t correlationMaskCount,
    const uint32_t* pCorrelationMasks) {
  VkRenderPassMultiviewCreateInfo RenderPassMultiviewCreateInfo = {};
  RenderPassMultiviewCreateInfo.sType =
      VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
  RenderPassMultiviewCreateInfo.pNext = nullptr;
  RenderPassMultiviewCreateInfo.subpassCount = subpassCount;
  RenderPassMultiviewCreateInfo.pViewMasks = pViewMasks;
  RenderPassMultiviewCreateInfo.dependencyCount = dependencyCount;
  RenderPassMultiviewCreateInfo.pViewOffsets = pViewOffsets;
  RenderPassMultiviewCreateInfo.correlationMaskCount = correlationMaskCount;
  RenderPassMultiviewCreateInfo.pCorrelationMasks = pCorrelationMasks;
  return RenderPassMultiviewCreateInfo;
}

inline VkPhysicalDeviceMultiviewFeatures vkiPhysicalDeviceMultiviewFeatures(
    VkBool32 multiview, VkBool32 multiviewGeometryShader,
    VkBool32 multiviewTessellationShader) {
  VkPhysicalDeviceMultiviewFeatures PhysicalDeviceMultiviewFeatures = {};
  PhysicalDeviceMultiviewFeatures.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
  PhysicalDeviceMultiviewFeatures.pNext = nullptr;
  PhysicalDeviceMultiviewFeatures.multiview = multiview;
  PhysicalDeviceMultiviewFeatures.multiviewGeometryShader =
      multiviewGeometryShader;
  PhysicalDeviceMultiviewFeatures.multiviewTessellationShader =
      multiviewTessellationShader;
  return PhysicalDeviceMultiviewFeatures;
}

inline VkPhysicalDeviceMultiviewProperties vkiPhysicalDeviceMultiviewProperties(
    uint32_t maxMultiviewViewCount, uint32_t maxMultiviewInstanceIndex) {
  VkPhysicalDeviceMultiviewProperties PhysicalDeviceMultiviewProperties = {};
  PhysicalDeviceMultiviewProperties.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
  PhysicalDeviceMultiviewProperties.pNext = nullptr;
  PhysicalDeviceMultiviewProperties.maxMultiviewViewCount =
      maxMultiviewViewCount;
  PhysicalDeviceMultiviewProperties.maxMultiviewInstanceIndex =
      maxMultiviewInstanceIndex;
  return PhysicalDeviceMultiviewProperties;
}

inline VkPhysicalDeviceVariablePointersFeatures
vkiPhysicalDeviceVariablePointersFeatures(
    VkBool32 variablePointersStorageBuffer, VkBool32 variablePointers) {
  VkPhysicalDeviceVariablePointersFeatures
      PhysicalDeviceVariablePointersFeatures = {};
  PhysicalDeviceVariablePointersFeatures.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES;
  PhysicalDeviceVariablePointersFeatures.pNext = nullptr;
  PhysicalDeviceVariablePointersFeatures.variablePointersStorageBuffer =
      variablePointersStorageBuffer;
  PhysicalDeviceVariablePointersFeatures.variablePointers = variablePointers;
  return PhysicalDeviceVariablePointersFeatures;
}

inline VkPhysicalDeviceProtectedMemoryFeatures
vkiPhysicalDeviceProtectedMemoryFeatures(VkBool32 protectedMemory) {
  VkPhysicalDeviceProtectedMemoryFeatures
      PhysicalDeviceProtectedMemoryFeatures = {};
  PhysicalDeviceProtectedMemoryFeatures.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
  PhysicalDeviceProtectedMemoryFeatures.pNext = nullptr;
  PhysicalDeviceProtectedMemoryFeatures.protectedMemory = protectedMemory;
  return PhysicalDeviceProtectedMemoryFeatures;
}

inline VkPhysicalDeviceProtectedMemoryProperties
vkiPhysicalDeviceProtectedMemoryProperties(VkBool32 protectedNoFault) {
  VkPhysicalDeviceProtectedMemoryProperties
      PhysicalDeviceProtectedMemoryProperties = {};
  PhysicalDeviceProtectedMemoryProperties.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES;
  PhysicalDeviceProtectedMemoryProperties.pNext = nullptr;
  PhysicalDeviceProtectedMemoryProperties.protectedNoFault = protectedNoFault;
  return PhysicalDeviceProtectedMemoryProperties;
}

inline VkDeviceQueueInfo2 vkiDeviceQueueInfo2(uint32_t queueFamilyIndex,
                                              uint32_t queueIndex) {
  VkDeviceQueueInfo2 DeviceQueueInfo2 = {};
  DeviceQueueInfo2.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
  DeviceQueueInfo2.pNext = nullptr;
  DeviceQueueInfo2.flags = 0;
  DeviceQueueInfo2.queueFamilyIndex = queueFamilyIndex;
  DeviceQueueInfo2.queueIndex = queueIndex;
  return DeviceQueueInfo2;
}

inline VkProtectedSubmitInfo vkiProtectedSubmitInfo(VkBool32 protectedSubmit) {
  VkProtectedSubmitInfo ProtectedSubmitInfo = {};
  ProtectedSubmitInfo.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
  ProtectedSubmitInfo.pNext = nullptr;
  ProtectedSubmitInfo.protectedSubmit = protectedSubmit;
  return ProtectedSubmitInfo;
}

inline VkSamplerYcbcrConversionCreateInfo vkiSamplerYcbcrConversionCreateInfo(
    VkFormat format, VkSamplerYcbcrModelConversion ycbcrModel,
    VkSamplerYcbcrRange ycbcrRange, VkComponentMapping components,
    VkChromaLocation xChromaOffset, VkChromaLocation yChromaOffset,
    VkFilter chromaFilter, VkBool32 forceExplicitReconstruction) {
  VkSamplerYcbcrConversionCreateInfo SamplerYcbcrConversionCreateInfo = {};
  SamplerYcbcrConversionCreateInfo.sType =
      VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
  SamplerYcbcrConversionCreateInfo.pNext = nullptr;
  SamplerYcbcrConversionCreateInfo.format = format;
  SamplerYcbcrConversionCreateInfo.ycbcrModel = ycbcrModel;
  SamplerYcbcrConversionCreateInfo.ycbcrRange = ycbcrRange;
  SamplerYcbcrConversionCreateInfo.components = components;
  SamplerYcbcrConversionCreateInfo.xChromaOffset = xChromaOffset;
  SamplerYcbcrConversionCreateInfo.yChromaOffset = yChromaOffset;
  SamplerYcbcrConversionCreateInfo.chromaFilter = chromaFilter;
  SamplerYcbcrConversionCreateInfo.forceExplicitReconstruction =
      forceExplicitReconstruction;
  return SamplerYcbcrConversionCreateInfo;
}

inline VkSamplerYcbcrConversionInfo vkiSamplerYcbcrConversionInfo(
    VkSamplerYcbcrConversion conversion) {
  VkSamplerYcbcrConversionInfo SamplerYcbcrConversionInfo = {};
  SamplerYcbcrConversionInfo.sType =
      VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
  SamplerYcbcrConversionInfo.pNext = nullptr;
  SamplerYcbcrConversionInfo.conversion = conversion;
  return SamplerYcbcrConversionInfo;
}

inline VkBindImagePlaneMemoryInfo vkiBindImagePlaneMemoryInfo(
    VkImageAspectFlagBits planeAspect) {
  VkBindImagePlaneMemoryInfo BindImagePlaneMemoryInfo = {};
  BindImagePlaneMemoryInfo.sType =
      VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
  BindImagePlaneMemoryInfo.pNext = nullptr;
  BindImagePlaneMemoryInfo.planeAspect = planeAspect;
  return BindImagePlaneMemoryInfo;
}

inline VkImagePlaneMemoryRequirementsInfo vkiImagePlaneMemoryRequirementsInfo(
    VkImageAspectFlagBits planeAspect) {
  VkImagePlaneMemoryRequirementsInfo ImagePlaneMemoryRequirementsInfo = {};
  ImagePlaneMemoryRequirementsInfo.sType =
      VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO;
  ImagePlaneMemoryRequirementsInfo.pNext = nullptr;
  ImagePlaneMemoryRequirementsInfo.planeAspect = planeAspect;
  return ImagePlaneMemoryRequirementsInfo;
}

inline VkPhysicalDeviceSamplerYcbcrConversionFeatures
vkiPhysicalDeviceSamplerYcbcrConversionFeatures(
    VkBool32 samplerYcbcrConversion) {
  VkPhysicalDeviceSamplerYcbcrConversionFeatures
      PhysicalDeviceSamplerYcbcrConversionFeatures = {};
  PhysicalDeviceSamplerYcbcrConversionFeatures.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
  PhysicalDeviceSamplerYcbcrConversionFeatures.pNext = nullptr;
  PhysicalDeviceSamplerYcbcrConversionFeatures.samplerYcbcrConversion =
      samplerYcbcrConversion;
  return PhysicalDeviceSamplerYcbcrConversionFeatures;
}

inline VkSamplerYcbcrConversionImageFormatProperties
vkiSamplerYcbcrConversionImageFormatProperties(
    uint32_t combinedImageSamplerDescriptorCount) {
  VkSamplerYcbcrConversionImageFormatProperties
      SamplerYcbcrConversionImageFormatProperties = {};
  SamplerYcbcrConversionImageFormatProperties.sType =
      VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES;
  SamplerYcbcrConversionImageFormatProperties.pNext = nullptr;
  SamplerYcbcrConversionImageFormatProperties
      .combinedImageSamplerDescriptorCount =
      combinedImageSamplerDescriptorCount;
  return SamplerYcbcrConversionImageFormatProperties;
}

inline VkDescriptorUpdateTemplateEntry vkiDescriptorUpdateTemplateEntry(
    uint32_t dstBinding, uint32_t dstArrayElement, uint32_t descriptorCount,
    VkDescriptorType descriptorType, size_t offset, size_t stride) {
  VkDescriptorUpdateTemplateEntry DescriptorUpdateTemplateEntry = {};
  DescriptorUpdateTemplateEntry.dstBinding = dstBinding;
  DescriptorUpdateTemplateEntry.dstArrayElement = dstArrayElement;
  DescriptorUpdateTemplateEntry.descriptorCount = descriptorCount;
  DescriptorUpdateTemplateEntry.descriptorType = descriptorType;
  DescriptorUpdateTemplateEntry.offset = offset;
  DescriptorUpdateTemplateEntry.stride = stride;
  return DescriptorUpdateTemplateEntry;
}

inline VkDescriptorUpdateTemplateCreateInfo
vkiDescriptorUpdateTemplateCreateInfo(
    uint32_t descriptorUpdateEntryCount,
    const VkDescriptorUpdateTemplateEntry* pDescriptorUpdateEntries,
    VkDescriptorUpdateTemplateType templateType,
    VkDescriptorSetLayout descriptorSetLayout,
    VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout pipelineLayout,
    uint32_t set) {
  VkDescriptorUpdateTemplateCreateInfo DescriptorUpdateTemplateCreateInfo = {};
  DescriptorUpdateTemplateCreateInfo.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO;
  DescriptorUpdateTemplateCreateInfo.pNext = nullptr;
  DescriptorUpdateTemplateCreateInfo.flags = 0;
  DescriptorUpdateTemplateCreateInfo.descriptorUpdateEntryCount =
      descriptorUpdateEntryCount;
  DescriptorUpdateTemplateCreateInfo.pDescriptorUpdateEntries =
      pDescriptorUpdateEntries;
  DescriptorUpdateTemplateCreateInfo.templateType = templateType;
  DescriptorUpdateTemplateCreateInfo.descriptorSetLayout = descriptorSetLayout;
  DescriptorUpdateTemplateCreateInfo.pipelineBindPoint = pipelineBindPoint;
  DescriptorUpdateTemplateCreateInfo.pipelineLayout = pipelineLayout;
  DescriptorUpdateTemplateCreateInfo.set = set;
  return DescriptorUpdateTemplateCreateInfo;
}

inline VkExternalMemoryProperties vkiExternalMemoryProperties(
    VkExternalMemoryFeatureFlags externalMemoryFeatures,
    VkExternalMemoryHandleTypeFlags exportFromImportedHandleTypes,
    VkExternalMemoryHandleTypeFlags compatibleHandleTypes) {
  VkExternalMemoryProperties ExternalMemoryProperties = {};
  ExternalMemoryProperties.externalMemoryFeatures = externalMemoryFeatures;
  ExternalMemoryProperties.exportFromImportedHandleTypes =
      exportFromImportedHandleTypes;
  ExternalMemoryProperties.compatibleHandleTypes = compatibleHandleTypes;
  return ExternalMemoryProperties;
}

inline VkPhysicalDeviceExternalImageFormatInfo
vkiPhysicalDeviceExternalImageFormatInfo(
    VkExternalMemoryHandleTypeFlagBits handleType) {
  VkPhysicalDeviceExternalImageFormatInfo
      PhysicalDeviceExternalImageFormatInfo = {};
  PhysicalDeviceExternalImageFormatInfo.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO;
  PhysicalDeviceExternalImageFormatInfo.pNext = nullptr;
  PhysicalDeviceExternalImageFormatInfo.handleType = handleType;
  return PhysicalDeviceExternalImageFormatInfo;
}

inline VkExternalImageFormatProperties vkiExternalImageFormatProperties(
    VkExternalMemoryProperties externalMemoryProperties) {
  VkExternalImageFormatProperties ExternalImageFormatProperties = {};
  ExternalImageFormatProperties.sType =
      VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES;
  ExternalImageFormatProperties.pNext = nullptr;
  ExternalImageFormatProperties.externalMemoryProperties =
      externalMemoryProperties;
  return ExternalImageFormatProperties;
}

inline VkPhysicalDeviceExternalBufferInfo vkiPhysicalDeviceExternalBufferInfo(
    VkBufferUsageFlags usage, VkExternalMemoryHandleTypeFlagBits handleType) {
  VkPhysicalDeviceExternalBufferInfo PhysicalDeviceExternalBufferInfo = {};
  PhysicalDeviceExternalBufferInfo.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO;
  PhysicalDeviceExternalBufferInfo.pNext = nullptr;
  PhysicalDeviceExternalBufferInfo.flags = 0;
  PhysicalDeviceExternalBufferInfo.usage = usage;
  PhysicalDeviceExternalBufferInfo.handleType = handleType;
  return PhysicalDeviceExternalBufferInfo;
}

inline VkExternalBufferProperties vkiExternalBufferProperties(
    VkExternalMemoryProperties externalMemoryProperties) {
  VkExternalBufferProperties ExternalBufferProperties = {};
  ExternalBufferProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES;
  ExternalBufferProperties.pNext = nullptr;
  ExternalBufferProperties.externalMemoryProperties = externalMemoryProperties;
  return ExternalBufferProperties;
}

// inline VkPhysicalDeviceIDProperties vkiPhysicalDeviceIDProperties(uint8_t
// deviceUUID[VK_UUID_SIZE], uint8_t driverUUID[VK_UUID_SIZE], uint8_t
// deviceLUID[VK_LUID_SIZE], uint32_t deviceNodeMask, VkBool32 deviceLUIDValid)
// {
//     VkPhysicalDeviceIDProperties PhysicalDeviceIDProperties = {};
//     PhysicalDeviceIDProperties.sType =
//     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
//     PhysicalDeviceIDProperties.pNext = nullptr;
//     PhysicalDeviceIDProperties.deviceUUID[VK_UUID_SIZE] =
//     deviceUUID[VK_UUID_SIZE];
//     PhysicalDeviceIDProperties.driverUUID[VK_UUID_SIZE] =
//     driverUUID[VK_UUID_SIZE];
//     PhysicalDeviceIDProperties.deviceLUID[VK_LUID_SIZE] =
//     deviceLUID[VK_LUID_SIZE]; PhysicalDeviceIDProperties.deviceNodeMask =
//     deviceNodeMask; PhysicalDeviceIDProperties.deviceLUIDValid =
//     deviceLUIDValid; return PhysicalDeviceIDProperties;
// }

inline VkExternalMemoryImageCreateInfo vkiExternalMemoryImageCreateInfo(
    VkExternalMemoryHandleTypeFlags handleTypes) {
  VkExternalMemoryImageCreateInfo ExternalMemoryImageCreateInfo = {};
  ExternalMemoryImageCreateInfo.sType =
      VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
  ExternalMemoryImageCreateInfo.pNext = nullptr;
  ExternalMemoryImageCreateInfo.handleTypes = handleTypes;
  return ExternalMemoryImageCreateInfo;
}

inline VkExternalMemoryBufferCreateInfo vkiExternalMemoryBufferCreateInfo(
    VkExternalMemoryHandleTypeFlags handleTypes) {
  VkExternalMemoryBufferCreateInfo ExternalMemoryBufferCreateInfo = {};
  ExternalMemoryBufferCreateInfo.sType =
      VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO;
  ExternalMemoryBufferCreateInfo.pNext = nullptr;
  ExternalMemoryBufferCreateInfo.handleTypes = handleTypes;
  return ExternalMemoryBufferCreateInfo;
}

inline VkExportMemoryAllocateInfo vkiExportMemoryAllocateInfo(
    VkExternalMemoryHandleTypeFlags handleTypes) {
  VkExportMemoryAllocateInfo ExportMemoryAllocateInfo = {};
  ExportMemoryAllocateInfo.sType =
      VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
  ExportMemoryAllocateInfo.pNext = nullptr;
  ExportMemoryAllocateInfo.handleTypes = handleTypes;
  return ExportMemoryAllocateInfo;
}

inline VkPhysicalDeviceExternalFenceInfo vkiPhysicalDeviceExternalFenceInfo(
    VkExternalFenceHandleTypeFlagBits handleType) {
  VkPhysicalDeviceExternalFenceInfo PhysicalDeviceExternalFenceInfo = {};
  PhysicalDeviceExternalFenceInfo.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO;
  PhysicalDeviceExternalFenceInfo.pNext = nullptr;
  PhysicalDeviceExternalFenceInfo.handleType = handleType;
  return PhysicalDeviceExternalFenceInfo;
}

inline VkExternalFenceProperties vkiExternalFenceProperties(
    VkExternalFenceHandleTypeFlags exportFromImportedHandleTypes,
    VkExternalFenceHandleTypeFlags compatibleHandleTypes,
    VkExternalFenceFeatureFlags externalFenceFeatures) {
  VkExternalFenceProperties ExternalFenceProperties = {};
  ExternalFenceProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES;
  ExternalFenceProperties.pNext = nullptr;
  ExternalFenceProperties.exportFromImportedHandleTypes =
      exportFromImportedHandleTypes;
  ExternalFenceProperties.compatibleHandleTypes = compatibleHandleTypes;
  ExternalFenceProperties.externalFenceFeatures = externalFenceFeatures;
  return ExternalFenceProperties;
}

inline VkExportFenceCreateInfo vkiExportFenceCreateInfo(
    VkExternalFenceHandleTypeFlags handleTypes) {
  VkExportFenceCreateInfo ExportFenceCreateInfo = {};
  ExportFenceCreateInfo.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO;
  ExportFenceCreateInfo.pNext = nullptr;
  ExportFenceCreateInfo.handleTypes = handleTypes;
  return ExportFenceCreateInfo;
}

inline VkExportSemaphoreCreateInfo vkiExportSemaphoreCreateInfo(
    VkExternalSemaphoreHandleTypeFlags handleTypes) {
  VkExportSemaphoreCreateInfo ExportSemaphoreCreateInfo = {};
  ExportSemaphoreCreateInfo.sType =
      VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
  ExportSemaphoreCreateInfo.pNext = nullptr;
  ExportSemaphoreCreateInfo.handleTypes = handleTypes;
  return ExportSemaphoreCreateInfo;
}

inline VkPhysicalDeviceExternalSemaphoreInfo
vkiPhysicalDeviceExternalSemaphoreInfo(
    VkExternalSemaphoreHandleTypeFlagBits handleType) {
  VkPhysicalDeviceExternalSemaphoreInfo PhysicalDeviceExternalSemaphoreInfo =
      {};
  PhysicalDeviceExternalSemaphoreInfo.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO;
  PhysicalDeviceExternalSemaphoreInfo.pNext = nullptr;
  PhysicalDeviceExternalSemaphoreInfo.handleType = handleType;
  return PhysicalDeviceExternalSemaphoreInfo;
}

inline VkExternalSemaphoreProperties vkiExternalSemaphoreProperties(
    VkExternalSemaphoreHandleTypeFlags exportFromImportedHandleTypes,
    VkExternalSemaphoreHandleTypeFlags compatibleHandleTypes,
    VkExternalSemaphoreFeatureFlags externalSemaphoreFeatures) {
  VkExternalSemaphoreProperties ExternalSemaphoreProperties = {};
  ExternalSemaphoreProperties.sType =
      VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
  ExternalSemaphoreProperties.pNext = nullptr;
  ExternalSemaphoreProperties.exportFromImportedHandleTypes =
      exportFromImportedHandleTypes;
  ExternalSemaphoreProperties.compatibleHandleTypes = compatibleHandleTypes;
  ExternalSemaphoreProperties.externalSemaphoreFeatures =
      externalSemaphoreFeatures;
  return ExternalSemaphoreProperties;
}

inline VkPhysicalDeviceMaintenance3Properties
vkiPhysicalDeviceMaintenance3Properties(uint32_t maxPerSetDescriptors,
                                        VkDeviceSize maxMemoryAllocationSize) {
  VkPhysicalDeviceMaintenance3Properties PhysicalDeviceMaintenance3Properties =
      {};
  PhysicalDeviceMaintenance3Properties.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
  PhysicalDeviceMaintenance3Properties.pNext = nullptr;
  PhysicalDeviceMaintenance3Properties.maxPerSetDescriptors =
      maxPerSetDescriptors;
  PhysicalDeviceMaintenance3Properties.maxMemoryAllocationSize =
      maxMemoryAllocationSize;
  return PhysicalDeviceMaintenance3Properties;
}

inline VkDescriptorSetLayoutSupport vkiDescriptorSetLayoutSupport(
    VkBool32 supported) {
  VkDescriptorSetLayoutSupport DescriptorSetLayoutSupport = {};
  DescriptorSetLayoutSupport.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT;
  DescriptorSetLayoutSupport.pNext = nullptr;
  DescriptorSetLayoutSupport.supported = supported;
  return DescriptorSetLayoutSupport;
}

inline VkPhysicalDeviceShaderDrawParametersFeatures
vkiPhysicalDeviceShaderDrawParametersFeatures(VkBool32 shaderDrawParameters) {
  VkPhysicalDeviceShaderDrawParametersFeatures
      PhysicalDeviceShaderDrawParametersFeatures = {};
  PhysicalDeviceShaderDrawParametersFeatures.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
  PhysicalDeviceShaderDrawParametersFeatures.pNext = nullptr;
  PhysicalDeviceShaderDrawParametersFeatures.shaderDrawParameters =
      shaderDrawParameters;
  return PhysicalDeviceShaderDrawParametersFeatures;
}

inline VkSurfaceCapabilitiesKHR vkiSurfaceCapabilitiesKHR(
    uint32_t minImageCount, uint32_t maxImageCount, VkExtent2D currentExtent,
    VkExtent2D minImageExtent, VkExtent2D maxImageExtent,
    uint32_t maxImageArrayLayers,
    VkSurfaceTransformFlagsKHR supportedTransforms,
    VkSurfaceTransformFlagBitsKHR currentTransform,
    VkCompositeAlphaFlagsKHR supportedCompositeAlpha,
    VkImageUsageFlags supportedUsageFlags) {
  VkSurfaceCapabilitiesKHR SurfaceCapabilitiesKHR = {};
  SurfaceCapabilitiesKHR.minImageCount = minImageCount;
  SurfaceCapabilitiesKHR.maxImageCount = maxImageCount;
  SurfaceCapabilitiesKHR.currentExtent = currentExtent;
  SurfaceCapabilitiesKHR.minImageExtent = minImageExtent;
  SurfaceCapabilitiesKHR.maxImageExtent = maxImageExtent;
  SurfaceCapabilitiesKHR.maxImageArrayLayers = maxImageArrayLayers;
  SurfaceCapabilitiesKHR.supportedTransforms = supportedTransforms;
  SurfaceCapabilitiesKHR.currentTransform = currentTransform;
  SurfaceCapabilitiesKHR.supportedCompositeAlpha = supportedCompositeAlpha;
  SurfaceCapabilitiesKHR.supportedUsageFlags = supportedUsageFlags;
  return SurfaceCapabilitiesKHR;
}

inline VkSurfaceFormatKHR vkiSurfaceFormatKHR(VkFormat format,
                                              VkColorSpaceKHR colorSpace) {
  VkSurfaceFormatKHR SurfaceFormatKHR = {};
  SurfaceFormatKHR.format = format;
  SurfaceFormatKHR.colorSpace = colorSpace;
  return SurfaceFormatKHR;
}

inline VkSwapchainCreateInfoKHR vkiSwapchainCreateInfoKHR(
    VkSurfaceKHR surface, uint32_t minImageCount, VkFormat imageFormat,
    VkColorSpaceKHR imageColorSpace, VkExtent2D imageExtent,
    uint32_t imageArrayLayers, VkImageUsageFlags imageUsage,
    VkSharingMode imageSharingMode, uint32_t queueFamilyIndexCount,
    const uint32_t* pQueueFamilyIndices,
    VkSurfaceTransformFlagBitsKHR preTransform,
    VkCompositeAlphaFlagBitsKHR compositeAlpha, VkPresentModeKHR presentMode,
    VkBool32 clipped, VkSwapchainKHR oldSwapchain) {
  VkSwapchainCreateInfoKHR SwapchainCreateInfoKHR = {};
  SwapchainCreateInfoKHR.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  SwapchainCreateInfoKHR.pNext = nullptr;
  SwapchainCreateInfoKHR.flags = 0;
  SwapchainCreateInfoKHR.surface = surface;
  SwapchainCreateInfoKHR.minImageCount = minImageCount;
  SwapchainCreateInfoKHR.imageFormat = imageFormat;
  SwapchainCreateInfoKHR.imageColorSpace = imageColorSpace;
  SwapchainCreateInfoKHR.imageExtent = imageExtent;
  SwapchainCreateInfoKHR.imageArrayLayers = imageArrayLayers;
  SwapchainCreateInfoKHR.imageUsage = imageUsage;
  SwapchainCreateInfoKHR.imageSharingMode = imageSharingMode;
  SwapchainCreateInfoKHR.queueFamilyIndexCount = queueFamilyIndexCount;
  SwapchainCreateInfoKHR.pQueueFamilyIndices = pQueueFamilyIndices;
  SwapchainCreateInfoKHR.preTransform = preTransform;
  SwapchainCreateInfoKHR.compositeAlpha = compositeAlpha;
  SwapchainCreateInfoKHR.presentMode = presentMode;
  SwapchainCreateInfoKHR.clipped = clipped;
  SwapchainCreateInfoKHR.oldSwapchain = oldSwapchain;
  return SwapchainCreateInfoKHR;
}

inline VkPresentInfoKHR vkiPresentInfoKHR(uint32_t waitSemaphoreCount,
                                          const VkSemaphore* pWaitSemaphores,
                                          uint32_t swapchainCount,
                                          const VkSwapchainKHR* pSwapchains,
                                          const uint32_t* pImageIndices,
                                          VkResult* pResults) {
  VkPresentInfoKHR PresentInfoKHR = {};
  PresentInfoKHR.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  PresentInfoKHR.pNext = nullptr;
  PresentInfoKHR.waitSemaphoreCount = waitSemaphoreCount;
  PresentInfoKHR.pWaitSemaphores = pWaitSemaphores;
  PresentInfoKHR.swapchainCount = swapchainCount;
  PresentInfoKHR.pSwapchains = pSwapchains;
  PresentInfoKHR.pImageIndices = pImageIndices;
  PresentInfoKHR.pResults = pResults;
  return PresentInfoKHR;
}

inline VkImageSwapchainCreateInfoKHR vkiImageSwapchainCreateInfoKHR(
    VkSwapchainKHR swapchain) {
  VkImageSwapchainCreateInfoKHR ImageSwapchainCreateInfoKHR = {};
  ImageSwapchainCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR;
  ImageSwapchainCreateInfoKHR.pNext = nullptr;
  ImageSwapchainCreateInfoKHR.swapchain = swapchain;
  return ImageSwapchainCreateInfoKHR;
}

inline VkBindImageMemorySwapchainInfoKHR vkiBindImageMemorySwapchainInfoKHR(
    VkSwapchainKHR swapchain, uint32_t imageIndex) {
  VkBindImageMemorySwapchainInfoKHR BindImageMemorySwapchainInfoKHR = {};
  BindImageMemorySwapchainInfoKHR.sType =
      VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR;
  BindImageMemorySwapchainInfoKHR.pNext = nullptr;
  BindImageMemorySwapchainInfoKHR.swapchain = swapchain;
  BindImageMemorySwapchainInfoKHR.imageIndex = imageIndex;
  return BindImageMemorySwapchainInfoKHR;
}

inline VkAcquireNextImageInfoKHR vkiAcquireNextImageInfoKHR(
    VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore,
    VkFence fence, uint32_t deviceMask) {
  VkAcquireNextImageInfoKHR AcquireNextImageInfoKHR = {};
  AcquireNextImageInfoKHR.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
  AcquireNextImageInfoKHR.pNext = nullptr;
  AcquireNextImageInfoKHR.swapchain = swapchain;
  AcquireNextImageInfoKHR.timeout = timeout;
  AcquireNextImageInfoKHR.semaphore = semaphore;
  AcquireNextImageInfoKHR.fence = fence;
  AcquireNextImageInfoKHR.deviceMask = deviceMask;
  return AcquireNextImageInfoKHR;
}

// inline VkDeviceGroupPresentCapabilitiesKHR
// vkiDeviceGroupPresentCapabilitiesKHR(uint32_t
// presentMask[VK_MAX_DEVICE_GROUP_SIZE], VkDeviceGroupPresentModeFlagsKHR
// modes) {
//     VkDeviceGroupPresentCapabilitiesKHR DeviceGroupPresentCapabilitiesKHR =
//     {}; DeviceGroupPresentCapabilitiesKHR.sType =
//     VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR;
//     DeviceGroupPresentCapabilitiesKHR.pNext = nullptr;
//     DeviceGroupPresentCapabilitiesKHR.presentMask[VK_MAX_DEVICE_GROUP_SIZE] =
//     presentMask[VK_MAX_DEVICE_GROUP_SIZE];
//     DeviceGroupPresentCapabilitiesKHR.modes = modes;
//     return DeviceGroupPresentCapabilitiesKHR;
// }

inline VkDeviceGroupPresentInfoKHR vkiDeviceGroupPresentInfoKHR(
    uint32_t swapchainCount, const uint32_t* pDeviceMasks,
    VkDeviceGroupPresentModeFlagBitsKHR mode) {
  VkDeviceGroupPresentInfoKHR DeviceGroupPresentInfoKHR = {};
  DeviceGroupPresentInfoKHR.sType =
      VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR;
  DeviceGroupPresentInfoKHR.pNext = nullptr;
  DeviceGroupPresentInfoKHR.swapchainCount = swapchainCount;
  DeviceGroupPresentInfoKHR.pDeviceMasks = pDeviceMasks;
  DeviceGroupPresentInfoKHR.mode = mode;
  return DeviceGroupPresentInfoKHR;
}

inline VkDeviceGroupSwapchainCreateInfoKHR vkiDeviceGroupSwapchainCreateInfoKHR(
    VkDeviceGroupPresentModeFlagsKHR modes) {
  VkDeviceGroupSwapchainCreateInfoKHR DeviceGroupSwapchainCreateInfoKHR = {};
  DeviceGroupSwapchainCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
  DeviceGroupSwapchainCreateInfoKHR.pNext = nullptr;
  DeviceGroupSwapchainCreateInfoKHR.modes = modes;
  return DeviceGroupSwapchainCreateInfoKHR;
}

inline VkDisplayPropertiesKHR vkiDisplayPropertiesKHR(
    VkDisplayKHR display, const char* displayName,
    VkExtent2D physicalDimensions, VkExtent2D physicalResolution,
    VkSurfaceTransformFlagsKHR supportedTransforms,
    VkBool32 planeReorderPossible, VkBool32 persistentContent) {
  VkDisplayPropertiesKHR DisplayPropertiesKHR = {};
  DisplayPropertiesKHR.display = display;
  DisplayPropertiesKHR.displayName = displayName;
  DisplayPropertiesKHR.physicalDimensions = physicalDimensions;
  DisplayPropertiesKHR.physicalResolution = physicalResolution;
  DisplayPropertiesKHR.supportedTransforms = supportedTransforms;
  DisplayPropertiesKHR.planeReorderPossible = planeReorderPossible;
  DisplayPropertiesKHR.persistentContent = persistentContent;
  return DisplayPropertiesKHR;
}

inline VkDisplayModeParametersKHR vkiDisplayModeParametersKHR(
    VkExtent2D visibleRegion, uint32_t refreshRate) {
  VkDisplayModeParametersKHR DisplayModeParametersKHR = {};
  DisplayModeParametersKHR.visibleRegion = visibleRegion;
  DisplayModeParametersKHR.refreshRate = refreshRate;
  return DisplayModeParametersKHR;
}

inline VkDisplayModePropertiesKHR vkiDisplayModePropertiesKHR(
    VkDisplayModeKHR displayMode, VkDisplayModeParametersKHR parameters) {
  VkDisplayModePropertiesKHR DisplayModePropertiesKHR = {};
  DisplayModePropertiesKHR.displayMode = displayMode;
  DisplayModePropertiesKHR.parameters = parameters;
  return DisplayModePropertiesKHR;
}

inline VkDisplayModeCreateInfoKHR vkiDisplayModeCreateInfoKHR(
    VkDisplayModeParametersKHR parameters) {
  VkDisplayModeCreateInfoKHR DisplayModeCreateInfoKHR = {};
  DisplayModeCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
  DisplayModeCreateInfoKHR.pNext = nullptr;
  DisplayModeCreateInfoKHR.flags = 0;
  DisplayModeCreateInfoKHR.parameters = parameters;
  return DisplayModeCreateInfoKHR;
}

inline VkDisplayPlaneCapabilitiesKHR vkiDisplayPlaneCapabilitiesKHR(
    VkDisplayPlaneAlphaFlagsKHR supportedAlpha, VkOffset2D minSrcPosition,
    VkOffset2D maxSrcPosition, VkExtent2D minSrcExtent, VkExtent2D maxSrcExtent,
    VkOffset2D minDstPosition, VkOffset2D maxDstPosition,
    VkExtent2D minDstExtent, VkExtent2D maxDstExtent) {
  VkDisplayPlaneCapabilitiesKHR DisplayPlaneCapabilitiesKHR = {};
  DisplayPlaneCapabilitiesKHR.supportedAlpha = supportedAlpha;
  DisplayPlaneCapabilitiesKHR.minSrcPosition = minSrcPosition;
  DisplayPlaneCapabilitiesKHR.maxSrcPosition = maxSrcPosition;
  DisplayPlaneCapabilitiesKHR.minSrcExtent = minSrcExtent;
  DisplayPlaneCapabilitiesKHR.maxSrcExtent = maxSrcExtent;
  DisplayPlaneCapabilitiesKHR.minDstPosition = minDstPosition;
  DisplayPlaneCapabilitiesKHR.maxDstPosition = maxDstPosition;
  DisplayPlaneCapabilitiesKHR.minDstExtent = minDstExtent;
  DisplayPlaneCapabilitiesKHR.maxDstExtent = maxDstExtent;
  return DisplayPlaneCapabilitiesKHR;
}

inline VkDisplayPlanePropertiesKHR vkiDisplayPlanePropertiesKHR(
    VkDisplayKHR currentDisplay, uint32_t currentStackIndex) {
  VkDisplayPlanePropertiesKHR DisplayPlanePropertiesKHR = {};
  DisplayPlanePropertiesKHR.currentDisplay = currentDisplay;
  DisplayPlanePropertiesKHR.currentStackIndex = currentStackIndex;
  return DisplayPlanePropertiesKHR;
}

inline VkDisplaySurfaceCreateInfoKHR vkiDisplaySurfaceCreateInfoKHR(
    VkDisplayModeKHR displayMode, uint32_t planeIndex, uint32_t planeStackIndex,
    VkSurfaceTransformFlagBitsKHR transform, float globalAlpha,
    VkDisplayPlaneAlphaFlagBitsKHR alphaMode, VkExtent2D imageExtent) {
  VkDisplaySurfaceCreateInfoKHR DisplaySurfaceCreateInfoKHR = {};
  DisplaySurfaceCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
  DisplaySurfaceCreateInfoKHR.pNext = nullptr;
  DisplaySurfaceCreateInfoKHR.flags = 0;
  DisplaySurfaceCreateInfoKHR.displayMode = displayMode;
  DisplaySurfaceCreateInfoKHR.planeIndex = planeIndex;
  DisplaySurfaceCreateInfoKHR.planeStackIndex = planeStackIndex;
  DisplaySurfaceCreateInfoKHR.transform = transform;
  DisplaySurfaceCreateInfoKHR.globalAlpha = globalAlpha;
  DisplaySurfaceCreateInfoKHR.alphaMode = alphaMode;
  DisplaySurfaceCreateInfoKHR.imageExtent = imageExtent;
  return DisplaySurfaceCreateInfoKHR;
}

inline VkDisplayPresentInfoKHR vkiDisplayPresentInfoKHR(VkRect2D srcRect,
                                                        VkRect2D dstRect,
                                                        VkBool32 persistent) {
  VkDisplayPresentInfoKHR DisplayPresentInfoKHR = {};
  DisplayPresentInfoKHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR;
  DisplayPresentInfoKHR.pNext = nullptr;
  DisplayPresentInfoKHR.srcRect = srcRect;
  DisplayPresentInfoKHR.dstRect = dstRect;
  DisplayPresentInfoKHR.persistent = persistent;
  return DisplayPresentInfoKHR;
}

inline VkImportMemoryFdInfoKHR vkiImportMemoryFdInfoKHR(
    VkExternalMemoryHandleTypeFlagBits handleType, int fd) {
  VkImportMemoryFdInfoKHR ImportMemoryFdInfoKHR = {};
  ImportMemoryFdInfoKHR.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
  ImportMemoryFdInfoKHR.pNext = nullptr;
  ImportMemoryFdInfoKHR.handleType = handleType;
  ImportMemoryFdInfoKHR.fd = fd;
  return ImportMemoryFdInfoKHR;
}

inline VkMemoryFdPropertiesKHR vkiMemoryFdPropertiesKHR(
    uint32_t memoryTypeBits) {
  VkMemoryFdPropertiesKHR MemoryFdPropertiesKHR = {};
  MemoryFdPropertiesKHR.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;
  MemoryFdPropertiesKHR.pNext = nullptr;
  MemoryFdPropertiesKHR.memoryTypeBits = memoryTypeBits;
  return MemoryFdPropertiesKHR;
}

inline VkMemoryGetFdInfoKHR vkiMemoryGetFdInfoKHR(
    VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagBits handleType) {
  VkMemoryGetFdInfoKHR MemoryGetFdInfoKHR = {};
  MemoryGetFdInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
  MemoryGetFdInfoKHR.pNext = nullptr;
  MemoryGetFdInfoKHR.memory = memory;
  MemoryGetFdInfoKHR.handleType = handleType;
  return MemoryGetFdInfoKHR;
}

inline VkImportSemaphoreFdInfoKHR vkiImportSemaphoreFdInfoKHR(
    VkSemaphore semaphore, VkExternalSemaphoreHandleTypeFlagBits handleType,
    int fd) {
  VkImportSemaphoreFdInfoKHR ImportSemaphoreFdInfoKHR = {};
  ImportSemaphoreFdInfoKHR.sType =
      VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR;
  ImportSemaphoreFdInfoKHR.pNext = nullptr;
  ImportSemaphoreFdInfoKHR.flags = 0;
  ImportSemaphoreFdInfoKHR.semaphore = semaphore;
  ImportSemaphoreFdInfoKHR.handleType = handleType;
  ImportSemaphoreFdInfoKHR.fd = fd;
  return ImportSemaphoreFdInfoKHR;
}

inline VkSemaphoreGetFdInfoKHR vkiSemaphoreGetFdInfoKHR(
    VkSemaphore semaphore, VkExternalSemaphoreHandleTypeFlagBits handleType) {
  VkSemaphoreGetFdInfoKHR SemaphoreGetFdInfoKHR = {};
  SemaphoreGetFdInfoKHR.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR;
  SemaphoreGetFdInfoKHR.pNext = nullptr;
  SemaphoreGetFdInfoKHR.semaphore = semaphore;
  SemaphoreGetFdInfoKHR.handleType = handleType;
  return SemaphoreGetFdInfoKHR;
}

inline VkPhysicalDevicePushDescriptorPropertiesKHR
vkiPhysicalDevicePushDescriptorPropertiesKHR(uint32_t maxPushDescriptors) {
  VkPhysicalDevicePushDescriptorPropertiesKHR
      PhysicalDevicePushDescriptorPropertiesKHR = {};
  PhysicalDevicePushDescriptorPropertiesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
  PhysicalDevicePushDescriptorPropertiesKHR.pNext = nullptr;
  PhysicalDevicePushDescriptorPropertiesKHR.maxPushDescriptors =
      maxPushDescriptors;
  return PhysicalDevicePushDescriptorPropertiesKHR;
}

inline VkPhysicalDeviceShaderFloat16Int8FeaturesKHR
vkiPhysicalDeviceShaderFloat16Int8FeaturesKHR(VkBool32 shaderFloat16,
                                              VkBool32 shaderInt8) {
  VkPhysicalDeviceShaderFloat16Int8FeaturesKHR
      PhysicalDeviceShaderFloat16Int8FeaturesKHR = {};
  PhysicalDeviceShaderFloat16Int8FeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES_KHR;
  PhysicalDeviceShaderFloat16Int8FeaturesKHR.pNext = nullptr;
  PhysicalDeviceShaderFloat16Int8FeaturesKHR.shaderFloat16 = shaderFloat16;
  PhysicalDeviceShaderFloat16Int8FeaturesKHR.shaderInt8 = shaderInt8;
  return PhysicalDeviceShaderFloat16Int8FeaturesKHR;
}

inline VkRectLayerKHR vkiRectLayerKHR(VkOffset2D offset, VkExtent2D extent,
                                      uint32_t layer) {
  VkRectLayerKHR RectLayerKHR = {};
  RectLayerKHR.offset = offset;
  RectLayerKHR.extent = extent;
  RectLayerKHR.layer = layer;
  return RectLayerKHR;
}

inline VkPresentRegionKHR vkiPresentRegionKHR(
    uint32_t rectangleCount, const VkRectLayerKHR* pRectangles) {
  VkPresentRegionKHR PresentRegionKHR = {};
  PresentRegionKHR.rectangleCount = rectangleCount;
  PresentRegionKHR.pRectangles = pRectangles;
  return PresentRegionKHR;
}

inline VkPresentRegionsKHR vkiPresentRegionsKHR(
    uint32_t swapchainCount, const VkPresentRegionKHR* pRegions) {
  VkPresentRegionsKHR PresentRegionsKHR = {};
  PresentRegionsKHR.sType = VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR;
  PresentRegionsKHR.pNext = nullptr;
  PresentRegionsKHR.swapchainCount = swapchainCount;
  PresentRegionsKHR.pRegions = pRegions;
  return PresentRegionsKHR;
}

inline VkPhysicalDeviceImagelessFramebufferFeaturesKHR
vkiPhysicalDeviceImagelessFramebufferFeaturesKHR(
    VkBool32 imagelessFramebuffer) {
  VkPhysicalDeviceImagelessFramebufferFeaturesKHR
      PhysicalDeviceImagelessFramebufferFeaturesKHR = {};
  PhysicalDeviceImagelessFramebufferFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES_KHR;
  PhysicalDeviceImagelessFramebufferFeaturesKHR.pNext = nullptr;
  PhysicalDeviceImagelessFramebufferFeaturesKHR.imagelessFramebuffer =
      imagelessFramebuffer;
  return PhysicalDeviceImagelessFramebufferFeaturesKHR;
}

inline VkFramebufferAttachmentImageInfoKHR vkiFramebufferAttachmentImageInfoKHR(
    VkImageUsageFlags usage, uint32_t width, uint32_t height,
    uint32_t layerCount, uint32_t viewFormatCount,
    const VkFormat* pViewFormats) {
  VkFramebufferAttachmentImageInfoKHR FramebufferAttachmentImageInfoKHR = {};
  FramebufferAttachmentImageInfoKHR.sType =
      VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO_KHR;
  FramebufferAttachmentImageInfoKHR.pNext = nullptr;
  FramebufferAttachmentImageInfoKHR.flags = 0;
  FramebufferAttachmentImageInfoKHR.usage = usage;
  FramebufferAttachmentImageInfoKHR.width = width;
  FramebufferAttachmentImageInfoKHR.height = height;
  FramebufferAttachmentImageInfoKHR.layerCount = layerCount;
  FramebufferAttachmentImageInfoKHR.viewFormatCount = viewFormatCount;
  FramebufferAttachmentImageInfoKHR.pViewFormats = pViewFormats;
  return FramebufferAttachmentImageInfoKHR;
}

inline VkFramebufferAttachmentsCreateInfoKHR
vkiFramebufferAttachmentsCreateInfoKHR(
    uint32_t attachmentImageInfoCount,
    const VkFramebufferAttachmentImageInfoKHR* pAttachmentImageInfos) {
  VkFramebufferAttachmentsCreateInfoKHR FramebufferAttachmentsCreateInfoKHR =
      {};
  FramebufferAttachmentsCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO_KHR;
  FramebufferAttachmentsCreateInfoKHR.pNext = nullptr;
  FramebufferAttachmentsCreateInfoKHR.attachmentImageInfoCount =
      attachmentImageInfoCount;
  FramebufferAttachmentsCreateInfoKHR.pAttachmentImageInfos =
      pAttachmentImageInfos;
  return FramebufferAttachmentsCreateInfoKHR;
}

inline VkRenderPassAttachmentBeginInfoKHR vkiRenderPassAttachmentBeginInfoKHR(
    uint32_t attachmentCount, const VkImageView* pAttachments) {
  VkRenderPassAttachmentBeginInfoKHR RenderPassAttachmentBeginInfoKHR = {};
  RenderPassAttachmentBeginInfoKHR.sType =
      VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO_KHR;
  RenderPassAttachmentBeginInfoKHR.pNext = nullptr;
  RenderPassAttachmentBeginInfoKHR.attachmentCount = attachmentCount;
  RenderPassAttachmentBeginInfoKHR.pAttachments = pAttachments;
  return RenderPassAttachmentBeginInfoKHR;
}

inline VkAttachmentDescription2KHR vkiAttachmentDescription2KHR(
    VkFormat format, VkSampleCountFlagBits samples, VkAttachmentLoadOp loadOp,
    VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp,
    VkAttachmentStoreOp stencilStoreOp, VkImageLayout initialLayout,
    VkImageLayout finalLayout) {
  VkAttachmentDescription2KHR AttachmentDescription2KHR = {};
  AttachmentDescription2KHR.sType =
      VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2_KHR;
  AttachmentDescription2KHR.pNext = nullptr;
  AttachmentDescription2KHR.flags = 0;
  AttachmentDescription2KHR.format = format;
  AttachmentDescription2KHR.samples = samples;
  AttachmentDescription2KHR.loadOp = loadOp;
  AttachmentDescription2KHR.storeOp = storeOp;
  AttachmentDescription2KHR.stencilLoadOp = stencilLoadOp;
  AttachmentDescription2KHR.stencilStoreOp = stencilStoreOp;
  AttachmentDescription2KHR.initialLayout = initialLayout;
  AttachmentDescription2KHR.finalLayout = finalLayout;
  return AttachmentDescription2KHR;
}

inline VkAttachmentReference2KHR vkiAttachmentReference2KHR(
    uint32_t attachment, VkImageLayout layout, VkImageAspectFlags aspectMask) {
  VkAttachmentReference2KHR AttachmentReference2KHR = {};
  AttachmentReference2KHR.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2_KHR;
  AttachmentReference2KHR.pNext = nullptr;
  AttachmentReference2KHR.attachment = attachment;
  AttachmentReference2KHR.layout = layout;
  AttachmentReference2KHR.aspectMask = aspectMask;
  return AttachmentReference2KHR;
}

inline VkSubpassDescription2KHR vkiSubpassDescription2KHR(
    VkPipelineBindPoint pipelineBindPoint, uint32_t viewMask,
    uint32_t inputAttachmentCount,
    const VkAttachmentReference2KHR* pInputAttachments,
    uint32_t colorAttachmentCount,
    const VkAttachmentReference2KHR* pColorAttachments,
    const VkAttachmentReference2KHR* pResolveAttachments,
    const VkAttachmentReference2KHR* pDepthStencilAttachment,
    uint32_t preserveAttachmentCount, const uint32_t* pPreserveAttachments) {
  VkSubpassDescription2KHR SubpassDescription2KHR = {};
  SubpassDescription2KHR.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2_KHR;
  SubpassDescription2KHR.pNext = nullptr;
  SubpassDescription2KHR.flags = 0;
  SubpassDescription2KHR.pipelineBindPoint = pipelineBindPoint;
  SubpassDescription2KHR.viewMask = viewMask;
  SubpassDescription2KHR.inputAttachmentCount = inputAttachmentCount;
  SubpassDescription2KHR.pInputAttachments = pInputAttachments;
  SubpassDescription2KHR.colorAttachmentCount = colorAttachmentCount;
  SubpassDescription2KHR.pColorAttachments = pColorAttachments;
  SubpassDescription2KHR.pResolveAttachments = pResolveAttachments;
  SubpassDescription2KHR.pDepthStencilAttachment = pDepthStencilAttachment;
  SubpassDescription2KHR.preserveAttachmentCount = preserveAttachmentCount;
  SubpassDescription2KHR.pPreserveAttachments = pPreserveAttachments;
  return SubpassDescription2KHR;
}

inline VkSubpassDependency2KHR vkiSubpassDependency2KHR(
    uint32_t srcSubpass, uint32_t dstSubpass, VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask, VkAccessFlags srcAccessMask,
    VkAccessFlags dstAccessMask, VkDependencyFlags dependencyFlags,
    int32_t viewOffset) {
  VkSubpassDependency2KHR SubpassDependency2KHR = {};
  SubpassDependency2KHR.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2_KHR;
  SubpassDependency2KHR.pNext = nullptr;
  SubpassDependency2KHR.srcSubpass = srcSubpass;
  SubpassDependency2KHR.dstSubpass = dstSubpass;
  SubpassDependency2KHR.srcStageMask = srcStageMask;
  SubpassDependency2KHR.dstStageMask = dstStageMask;
  SubpassDependency2KHR.srcAccessMask = srcAccessMask;
  SubpassDependency2KHR.dstAccessMask = dstAccessMask;
  SubpassDependency2KHR.dependencyFlags = dependencyFlags;
  SubpassDependency2KHR.viewOffset = viewOffset;
  return SubpassDependency2KHR;
}

inline VkRenderPassCreateInfo2KHR vkiRenderPassCreateInfo2KHR(
    uint32_t attachmentCount, const VkAttachmentDescription2KHR* pAttachments,
    uint32_t subpassCount, const VkSubpassDescription2KHR* pSubpasses,
    uint32_t dependencyCount, const VkSubpassDependency2KHR* pDependencies,
    uint32_t correlatedViewMaskCount, const uint32_t* pCorrelatedViewMasks) {
  VkRenderPassCreateInfo2KHR RenderPassCreateInfo2KHR = {};
  RenderPassCreateInfo2KHR.sType =
      VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2_KHR;
  RenderPassCreateInfo2KHR.pNext = nullptr;
  RenderPassCreateInfo2KHR.flags = 0;
  RenderPassCreateInfo2KHR.attachmentCount = attachmentCount;
  RenderPassCreateInfo2KHR.pAttachments = pAttachments;
  RenderPassCreateInfo2KHR.subpassCount = subpassCount;
  RenderPassCreateInfo2KHR.pSubpasses = pSubpasses;
  RenderPassCreateInfo2KHR.dependencyCount = dependencyCount;
  RenderPassCreateInfo2KHR.pDependencies = pDependencies;
  RenderPassCreateInfo2KHR.correlatedViewMaskCount = correlatedViewMaskCount;
  RenderPassCreateInfo2KHR.pCorrelatedViewMasks = pCorrelatedViewMasks;
  return RenderPassCreateInfo2KHR;
}

inline VkSubpassBeginInfoKHR vkiSubpassBeginInfoKHR(
    VkSubpassContents contents) {
  VkSubpassBeginInfoKHR SubpassBeginInfoKHR = {};
  SubpassBeginInfoKHR.sType = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO_KHR;
  SubpassBeginInfoKHR.pNext = nullptr;
  SubpassBeginInfoKHR.contents = contents;
  return SubpassBeginInfoKHR;
}

inline VkSubpassEndInfoKHR vkiSubpassEndInfoKHR() {
  VkSubpassEndInfoKHR SubpassEndInfoKHR = {};
  SubpassEndInfoKHR.sType = VK_STRUCTURE_TYPE_SUBPASS_END_INFO_KHR;
  SubpassEndInfoKHR.pNext = nullptr;
  return SubpassEndInfoKHR;
}

inline VkSharedPresentSurfaceCapabilitiesKHR
vkiSharedPresentSurfaceCapabilitiesKHR(
    VkImageUsageFlags sharedPresentSupportedUsageFlags) {
  VkSharedPresentSurfaceCapabilitiesKHR SharedPresentSurfaceCapabilitiesKHR =
      {};
  SharedPresentSurfaceCapabilitiesKHR.sType =
      VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR;
  SharedPresentSurfaceCapabilitiesKHR.pNext = nullptr;
  SharedPresentSurfaceCapabilitiesKHR.sharedPresentSupportedUsageFlags =
      sharedPresentSupportedUsageFlags;
  return SharedPresentSurfaceCapabilitiesKHR;
}

inline VkImportFenceFdInfoKHR vkiImportFenceFdInfoKHR(
    VkFence fence, VkExternalFenceHandleTypeFlagBits handleType, int fd) {
  VkImportFenceFdInfoKHR ImportFenceFdInfoKHR = {};
  ImportFenceFdInfoKHR.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR;
  ImportFenceFdInfoKHR.pNext = nullptr;
  ImportFenceFdInfoKHR.flags = 0;
  ImportFenceFdInfoKHR.fence = fence;
  ImportFenceFdInfoKHR.handleType = handleType;
  ImportFenceFdInfoKHR.fd = fd;
  return ImportFenceFdInfoKHR;
}

inline VkFenceGetFdInfoKHR vkiFenceGetFdInfoKHR(
    VkFence fence, VkExternalFenceHandleTypeFlagBits handleType) {
  VkFenceGetFdInfoKHR FenceGetFdInfoKHR = {};
  FenceGetFdInfoKHR.sType = VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR;
  FenceGetFdInfoKHR.pNext = nullptr;
  FenceGetFdInfoKHR.fence = fence;
  FenceGetFdInfoKHR.handleType = handleType;
  return FenceGetFdInfoKHR;
}

inline VkPhysicalDeviceSurfaceInfo2KHR vkiPhysicalDeviceSurfaceInfo2KHR(
    VkSurfaceKHR surface) {
  VkPhysicalDeviceSurfaceInfo2KHR PhysicalDeviceSurfaceInfo2KHR = {};
  PhysicalDeviceSurfaceInfo2KHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
  PhysicalDeviceSurfaceInfo2KHR.pNext = nullptr;
  PhysicalDeviceSurfaceInfo2KHR.surface = surface;
  return PhysicalDeviceSurfaceInfo2KHR;
}

inline VkSurfaceCapabilities2KHR vkiSurfaceCapabilities2KHR(
    VkSurfaceCapabilitiesKHR surfaceCapabilities) {
  VkSurfaceCapabilities2KHR SurfaceCapabilities2KHR = {};
  SurfaceCapabilities2KHR.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
  SurfaceCapabilities2KHR.pNext = nullptr;
  SurfaceCapabilities2KHR.surfaceCapabilities = surfaceCapabilities;
  return SurfaceCapabilities2KHR;
}

inline VkSurfaceFormat2KHR vkiSurfaceFormat2KHR(
    VkSurfaceFormatKHR surfaceFormat) {
  VkSurfaceFormat2KHR SurfaceFormat2KHR = {};
  SurfaceFormat2KHR.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
  SurfaceFormat2KHR.pNext = nullptr;
  SurfaceFormat2KHR.surfaceFormat = surfaceFormat;
  return SurfaceFormat2KHR;
}

inline VkDisplayProperties2KHR vkiDisplayProperties2KHR(
    VkDisplayPropertiesKHR displayProperties) {
  VkDisplayProperties2KHR DisplayProperties2KHR = {};
  DisplayProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR;
  DisplayProperties2KHR.pNext = nullptr;
  DisplayProperties2KHR.displayProperties = displayProperties;
  return DisplayProperties2KHR;
}

inline VkDisplayPlaneProperties2KHR vkiDisplayPlaneProperties2KHR(
    VkDisplayPlanePropertiesKHR displayPlaneProperties) {
  VkDisplayPlaneProperties2KHR DisplayPlaneProperties2KHR = {};
  DisplayPlaneProperties2KHR.sType =
      VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR;
  DisplayPlaneProperties2KHR.pNext = nullptr;
  DisplayPlaneProperties2KHR.displayPlaneProperties = displayPlaneProperties;
  return DisplayPlaneProperties2KHR;
}

inline VkDisplayModeProperties2KHR vkiDisplayModeProperties2KHR(
    VkDisplayModePropertiesKHR displayModeProperties) {
  VkDisplayModeProperties2KHR DisplayModeProperties2KHR = {};
  DisplayModeProperties2KHR.sType =
      VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR;
  DisplayModeProperties2KHR.pNext = nullptr;
  DisplayModeProperties2KHR.displayModeProperties = displayModeProperties;
  return DisplayModeProperties2KHR;
}

inline VkDisplayPlaneInfo2KHR vkiDisplayPlaneInfo2KHR(VkDisplayModeKHR mode,
                                                      uint32_t planeIndex) {
  VkDisplayPlaneInfo2KHR DisplayPlaneInfo2KHR = {};
  DisplayPlaneInfo2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR;
  DisplayPlaneInfo2KHR.pNext = nullptr;
  DisplayPlaneInfo2KHR.mode = mode;
  DisplayPlaneInfo2KHR.planeIndex = planeIndex;
  return DisplayPlaneInfo2KHR;
}

inline VkDisplayPlaneCapabilities2KHR vkiDisplayPlaneCapabilities2KHR(
    VkDisplayPlaneCapabilitiesKHR capabilities) {
  VkDisplayPlaneCapabilities2KHR DisplayPlaneCapabilities2KHR = {};
  DisplayPlaneCapabilities2KHR.sType =
      VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR;
  DisplayPlaneCapabilities2KHR.pNext = nullptr;
  DisplayPlaneCapabilities2KHR.capabilities = capabilities;
  return DisplayPlaneCapabilities2KHR;
}

inline VkImageFormatListCreateInfoKHR vkiImageFormatListCreateInfoKHR(
    uint32_t viewFormatCount, const VkFormat* pViewFormats) {
  VkImageFormatListCreateInfoKHR ImageFormatListCreateInfoKHR = {};
  ImageFormatListCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR;
  ImageFormatListCreateInfoKHR.pNext = nullptr;
  ImageFormatListCreateInfoKHR.viewFormatCount = viewFormatCount;
  ImageFormatListCreateInfoKHR.pViewFormats = pViewFormats;
  return ImageFormatListCreateInfoKHR;
}

inline VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR
vkiPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR(
    VkBool32 shaderSubgroupExtendedTypes) {
  VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR
      PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR = {};
  PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES_KHR;
  PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR.pNext = nullptr;
  PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR
      .shaderSubgroupExtendedTypes = shaderSubgroupExtendedTypes;
  return PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR;
}

inline VkPhysicalDevice8BitStorageFeaturesKHR
vkiPhysicalDevice8BitStorageFeaturesKHR(
    VkBool32 storageBuffer8BitAccess,
    VkBool32 uniformAndStorageBuffer8BitAccess, VkBool32 storagePushConstant8) {
  VkPhysicalDevice8BitStorageFeaturesKHR PhysicalDevice8BitStorageFeaturesKHR =
      {};
  PhysicalDevice8BitStorageFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES_KHR;
  PhysicalDevice8BitStorageFeaturesKHR.pNext = nullptr;
  PhysicalDevice8BitStorageFeaturesKHR.storageBuffer8BitAccess =
      storageBuffer8BitAccess;
  PhysicalDevice8BitStorageFeaturesKHR.uniformAndStorageBuffer8BitAccess =
      uniformAndStorageBuffer8BitAccess;
  PhysicalDevice8BitStorageFeaturesKHR.storagePushConstant8 =
      storagePushConstant8;
  return PhysicalDevice8BitStorageFeaturesKHR;
}

inline VkPhysicalDeviceShaderAtomicInt64FeaturesKHR
vkiPhysicalDeviceShaderAtomicInt64FeaturesKHR(
    VkBool32 shaderBufferInt64Atomics, VkBool32 shaderSharedInt64Atomics) {
  VkPhysicalDeviceShaderAtomicInt64FeaturesKHR
      PhysicalDeviceShaderAtomicInt64FeaturesKHR = {};
  PhysicalDeviceShaderAtomicInt64FeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES_KHR;
  PhysicalDeviceShaderAtomicInt64FeaturesKHR.pNext = nullptr;
  PhysicalDeviceShaderAtomicInt64FeaturesKHR.shaderBufferInt64Atomics =
      shaderBufferInt64Atomics;
  PhysicalDeviceShaderAtomicInt64FeaturesKHR.shaderSharedInt64Atomics =
      shaderSharedInt64Atomics;
  return PhysicalDeviceShaderAtomicInt64FeaturesKHR;
}

inline VkPhysicalDeviceShaderClockFeaturesKHR
vkiPhysicalDeviceShaderClockFeaturesKHR(VkBool32 shaderSubgroupClock,
                                        VkBool32 shaderDeviceClock) {
  VkPhysicalDeviceShaderClockFeaturesKHR PhysicalDeviceShaderClockFeaturesKHR =
      {};
  PhysicalDeviceShaderClockFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR;
  PhysicalDeviceShaderClockFeaturesKHR.pNext = nullptr;
  PhysicalDeviceShaderClockFeaturesKHR.shaderSubgroupClock =
      shaderSubgroupClock;
  PhysicalDeviceShaderClockFeaturesKHR.shaderDeviceClock = shaderDeviceClock;
  return PhysicalDeviceShaderClockFeaturesKHR;
}

inline VkConformanceVersionKHR vkiConformanceVersionKHR(uint8_t major,
                                                        uint8_t minor,
                                                        uint8_t subminor,
                                                        uint8_t patch) {
  VkConformanceVersionKHR ConformanceVersionKHR = {};
  ConformanceVersionKHR.major = major;
  ConformanceVersionKHR.minor = minor;
  ConformanceVersionKHR.subminor = subminor;
  ConformanceVersionKHR.patch = patch;
  return ConformanceVersionKHR;
}

// inline VkPhysicalDeviceDriverPropertiesKHR
// vkiPhysicalDeviceDriverPropertiesKHR(VkDriverIdKHR driverID, char
// driverName[VK_MAX_DRIVER_NAME_SIZE_KHR], char
// driverInfo[VK_MAX_DRIVER_INFO_SIZE_KHR], VkConformanceVersionKHR
// conformanceVersion) {
//     VkPhysicalDeviceDriverPropertiesKHR PhysicalDeviceDriverPropertiesKHR =
//     {}; PhysicalDeviceDriverPropertiesKHR.sType =
//     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES_KHR;
//     PhysicalDeviceDriverPropertiesKHR.pNext = nullptr;
//     PhysicalDeviceDriverPropertiesKHR.driverID = driverID;
//     PhysicalDeviceDriverPropertiesKHR.driverName[VK_MAX_DRIVER_NAME_SIZE_KHR]
//     = driverName[VK_MAX_DRIVER_NAME_SIZE_KHR];
//     PhysicalDeviceDriverPropertiesKHR.driverInfo[VK_MAX_DRIVER_INFO_SIZE_KHR]
//     = driverInfo[VK_MAX_DRIVER_INFO_SIZE_KHR];
//     PhysicalDeviceDriverPropertiesKHR.conformanceVersion =
//     conformanceVersion; return PhysicalDeviceDriverPropertiesKHR;
// }

inline VkPhysicalDeviceFloatControlsPropertiesKHR
vkiPhysicalDeviceFloatControlsPropertiesKHR(
    VkShaderFloatControlsIndependenceKHR denormBehaviorIndependence,
    VkShaderFloatControlsIndependenceKHR roundingModeIndependence,
    VkBool32 shaderSignedZeroInfNanPreserveFloat16,
    VkBool32 shaderSignedZeroInfNanPreserveFloat32,
    VkBool32 shaderSignedZeroInfNanPreserveFloat64,
    VkBool32 shaderDenormPreserveFloat16, VkBool32 shaderDenormPreserveFloat32,
    VkBool32 shaderDenormPreserveFloat64,
    VkBool32 shaderDenormFlushToZeroFloat16,
    VkBool32 shaderDenormFlushToZeroFloat32,
    VkBool32 shaderDenormFlushToZeroFloat64,
    VkBool32 shaderRoundingModeRTEFloat16,
    VkBool32 shaderRoundingModeRTEFloat32,
    VkBool32 shaderRoundingModeRTEFloat64,
    VkBool32 shaderRoundingModeRTZFloat16,
    VkBool32 shaderRoundingModeRTZFloat32,
    VkBool32 shaderRoundingModeRTZFloat64) {
  VkPhysicalDeviceFloatControlsPropertiesKHR
      PhysicalDeviceFloatControlsPropertiesKHR = {};
  PhysicalDeviceFloatControlsPropertiesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES_KHR;
  PhysicalDeviceFloatControlsPropertiesKHR.pNext = nullptr;
  PhysicalDeviceFloatControlsPropertiesKHR.denormBehaviorIndependence =
      denormBehaviorIndependence;
  PhysicalDeviceFloatControlsPropertiesKHR.roundingModeIndependence =
      roundingModeIndependence;
  PhysicalDeviceFloatControlsPropertiesKHR
      .shaderSignedZeroInfNanPreserveFloat16 =
      shaderSignedZeroInfNanPreserveFloat16;
  PhysicalDeviceFloatControlsPropertiesKHR
      .shaderSignedZeroInfNanPreserveFloat32 =
      shaderSignedZeroInfNanPreserveFloat32;
  PhysicalDeviceFloatControlsPropertiesKHR
      .shaderSignedZeroInfNanPreserveFloat64 =
      shaderSignedZeroInfNanPreserveFloat64;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderDenormPreserveFloat16 =
      shaderDenormPreserveFloat16;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderDenormPreserveFloat32 =
      shaderDenormPreserveFloat32;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderDenormPreserveFloat64 =
      shaderDenormPreserveFloat64;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderDenormFlushToZeroFloat16 =
      shaderDenormFlushToZeroFloat16;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderDenormFlushToZeroFloat32 =
      shaderDenormFlushToZeroFloat32;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderDenormFlushToZeroFloat64 =
      shaderDenormFlushToZeroFloat64;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderRoundingModeRTEFloat16 =
      shaderRoundingModeRTEFloat16;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderRoundingModeRTEFloat32 =
      shaderRoundingModeRTEFloat32;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderRoundingModeRTEFloat64 =
      shaderRoundingModeRTEFloat64;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderRoundingModeRTZFloat16 =
      shaderRoundingModeRTZFloat16;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderRoundingModeRTZFloat32 =
      shaderRoundingModeRTZFloat32;
  PhysicalDeviceFloatControlsPropertiesKHR.shaderRoundingModeRTZFloat64 =
      shaderRoundingModeRTZFloat64;
  return PhysicalDeviceFloatControlsPropertiesKHR;
}

inline VkSubpassDescriptionDepthStencilResolveKHR
vkiSubpassDescriptionDepthStencilResolveKHR(
    VkResolveModeFlagBitsKHR depthResolveMode,
    VkResolveModeFlagBitsKHR stencilResolveMode,
    const VkAttachmentReference2KHR* pDepthStencilResolveAttachment) {
  VkSubpassDescriptionDepthStencilResolveKHR
      SubpassDescriptionDepthStencilResolveKHR = {};
  SubpassDescriptionDepthStencilResolveKHR.sType =
      VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE_KHR;
  SubpassDescriptionDepthStencilResolveKHR.pNext = nullptr;
  SubpassDescriptionDepthStencilResolveKHR.depthResolveMode = depthResolveMode;
  SubpassDescriptionDepthStencilResolveKHR.stencilResolveMode =
      stencilResolveMode;
  SubpassDescriptionDepthStencilResolveKHR.pDepthStencilResolveAttachment =
      pDepthStencilResolveAttachment;
  return SubpassDescriptionDepthStencilResolveKHR;
}

inline VkPhysicalDeviceDepthStencilResolvePropertiesKHR
vkiPhysicalDeviceDepthStencilResolvePropertiesKHR(
    VkResolveModeFlagsKHR supportedDepthResolveModes,
    VkResolveModeFlagsKHR supportedStencilResolveModes,
    VkBool32 independentResolveNone, VkBool32 independentResolve) {
  VkPhysicalDeviceDepthStencilResolvePropertiesKHR
      PhysicalDeviceDepthStencilResolvePropertiesKHR = {};
  PhysicalDeviceDepthStencilResolvePropertiesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES_KHR;
  PhysicalDeviceDepthStencilResolvePropertiesKHR.pNext = nullptr;
  PhysicalDeviceDepthStencilResolvePropertiesKHR.supportedDepthResolveModes =
      supportedDepthResolveModes;
  PhysicalDeviceDepthStencilResolvePropertiesKHR.supportedStencilResolveModes =
      supportedStencilResolveModes;
  PhysicalDeviceDepthStencilResolvePropertiesKHR.independentResolveNone =
      independentResolveNone;
  PhysicalDeviceDepthStencilResolvePropertiesKHR.independentResolve =
      independentResolve;
  return PhysicalDeviceDepthStencilResolvePropertiesKHR;
}

inline VkPhysicalDeviceTimelineSemaphoreFeaturesKHR
vkiPhysicalDeviceTimelineSemaphoreFeaturesKHR(VkBool32 timelineSemaphore) {
  VkPhysicalDeviceTimelineSemaphoreFeaturesKHR
      PhysicalDeviceTimelineSemaphoreFeaturesKHR = {};
  PhysicalDeviceTimelineSemaphoreFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES_KHR;
  PhysicalDeviceTimelineSemaphoreFeaturesKHR.pNext = nullptr;
  PhysicalDeviceTimelineSemaphoreFeaturesKHR.timelineSemaphore =
      timelineSemaphore;
  return PhysicalDeviceTimelineSemaphoreFeaturesKHR;
}

inline VkPhysicalDeviceTimelineSemaphorePropertiesKHR
vkiPhysicalDeviceTimelineSemaphorePropertiesKHR(
    uint64_t maxTimelineSemaphoreValueDifference) {
  VkPhysicalDeviceTimelineSemaphorePropertiesKHR
      PhysicalDeviceTimelineSemaphorePropertiesKHR = {};
  PhysicalDeviceTimelineSemaphorePropertiesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES_KHR;
  PhysicalDeviceTimelineSemaphorePropertiesKHR.pNext = nullptr;
  PhysicalDeviceTimelineSemaphorePropertiesKHR
      .maxTimelineSemaphoreValueDifference =
      maxTimelineSemaphoreValueDifference;
  return PhysicalDeviceTimelineSemaphorePropertiesKHR;
}

inline VkSemaphoreTypeCreateInfoKHR vkiSemaphoreTypeCreateInfoKHR(
    VkSemaphoreTypeKHR semaphoreType, uint64_t initialValue) {
  VkSemaphoreTypeCreateInfoKHR SemaphoreTypeCreateInfoKHR = {};
  SemaphoreTypeCreateInfoKHR.sType =
      VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO_KHR;
  SemaphoreTypeCreateInfoKHR.pNext = nullptr;
  SemaphoreTypeCreateInfoKHR.semaphoreType = semaphoreType;
  SemaphoreTypeCreateInfoKHR.initialValue = initialValue;
  return SemaphoreTypeCreateInfoKHR;
}

inline VkTimelineSemaphoreSubmitInfoKHR vkiTimelineSemaphoreSubmitInfoKHR(
    uint32_t waitSemaphoreValueCount, const uint64_t* pWaitSemaphoreValues,
    uint32_t signalSemaphoreValueCount,
    const uint64_t* pSignalSemaphoreValues) {
  VkTimelineSemaphoreSubmitInfoKHR TimelineSemaphoreSubmitInfoKHR = {};
  TimelineSemaphoreSubmitInfoKHR.sType =
      VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO_KHR;
  TimelineSemaphoreSubmitInfoKHR.pNext = nullptr;
  TimelineSemaphoreSubmitInfoKHR.waitSemaphoreValueCount =
      waitSemaphoreValueCount;
  TimelineSemaphoreSubmitInfoKHR.pWaitSemaphoreValues = pWaitSemaphoreValues;
  TimelineSemaphoreSubmitInfoKHR.signalSemaphoreValueCount =
      signalSemaphoreValueCount;
  TimelineSemaphoreSubmitInfoKHR.pSignalSemaphoreValues =
      pSignalSemaphoreValues;
  return TimelineSemaphoreSubmitInfoKHR;
}

inline VkSemaphoreWaitInfoKHR vkiSemaphoreWaitInfoKHR(
    uint32_t semaphoreCount, const VkSemaphore* pSemaphores,
    const uint64_t* pValues) {
  VkSemaphoreWaitInfoKHR SemaphoreWaitInfoKHR = {};
  SemaphoreWaitInfoKHR.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO_KHR;
  SemaphoreWaitInfoKHR.pNext = nullptr;
  SemaphoreWaitInfoKHR.flags = 0;
  SemaphoreWaitInfoKHR.semaphoreCount = semaphoreCount;
  SemaphoreWaitInfoKHR.pSemaphores = pSemaphores;
  SemaphoreWaitInfoKHR.pValues = pValues;
  return SemaphoreWaitInfoKHR;
}

inline VkSemaphoreSignalInfoKHR vkiSemaphoreSignalInfoKHR(VkSemaphore semaphore,
                                                          uint64_t value) {
  VkSemaphoreSignalInfoKHR SemaphoreSignalInfoKHR = {};
  SemaphoreSignalInfoKHR.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO_KHR;
  SemaphoreSignalInfoKHR.pNext = nullptr;
  SemaphoreSignalInfoKHR.semaphore = semaphore;
  SemaphoreSignalInfoKHR.value = value;
  return SemaphoreSignalInfoKHR;
}

inline VkPhysicalDeviceVulkanMemoryModelFeaturesKHR
vkiPhysicalDeviceVulkanMemoryModelFeaturesKHR(
    VkBool32 vulkanMemoryModel, VkBool32 vulkanMemoryModelDeviceScope,
    VkBool32 vulkanMemoryModelAvailabilityVisibilityChains) {
  VkPhysicalDeviceVulkanMemoryModelFeaturesKHR
      PhysicalDeviceVulkanMemoryModelFeaturesKHR = {};
  PhysicalDeviceVulkanMemoryModelFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES_KHR;
  PhysicalDeviceVulkanMemoryModelFeaturesKHR.pNext = nullptr;
  PhysicalDeviceVulkanMemoryModelFeaturesKHR.vulkanMemoryModel =
      vulkanMemoryModel;
  PhysicalDeviceVulkanMemoryModelFeaturesKHR.vulkanMemoryModelDeviceScope =
      vulkanMemoryModelDeviceScope;
  PhysicalDeviceVulkanMemoryModelFeaturesKHR
      .vulkanMemoryModelAvailabilityVisibilityChains =
      vulkanMemoryModelAvailabilityVisibilityChains;
  return PhysicalDeviceVulkanMemoryModelFeaturesKHR;
}

inline VkSurfaceProtectedCapabilitiesKHR vkiSurfaceProtectedCapabilitiesKHR(
    VkBool32 supportsProtected) {
  VkSurfaceProtectedCapabilitiesKHR SurfaceProtectedCapabilitiesKHR = {};
  SurfaceProtectedCapabilitiesKHR.sType =
      VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR;
  SurfaceProtectedCapabilitiesKHR.pNext = nullptr;
  SurfaceProtectedCapabilitiesKHR.supportsProtected = supportsProtected;
  return SurfaceProtectedCapabilitiesKHR;
}

inline VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR
vkiPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR(
    VkBool32 uniformBufferStandardLayout) {
  VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR
      PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR = {};
  PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES_KHR;
  PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR.pNext = nullptr;
  PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR
      .uniformBufferStandardLayout = uniformBufferStandardLayout;
  return PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR;
}

inline VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR
vkiPhysicalDevicePipelineExecutablePropertiesFeaturesKHR(
    VkBool32 pipelineExecutableInfo) {
  VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR
      PhysicalDevicePipelineExecutablePropertiesFeaturesKHR = {};
  PhysicalDevicePipelineExecutablePropertiesFeaturesKHR.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR;
  PhysicalDevicePipelineExecutablePropertiesFeaturesKHR.pNext = nullptr;
  PhysicalDevicePipelineExecutablePropertiesFeaturesKHR.pipelineExecutableInfo =
      pipelineExecutableInfo;
  return PhysicalDevicePipelineExecutablePropertiesFeaturesKHR;
}

inline VkPipelineInfoKHR vkiPipelineInfoKHR(VkPipeline pipeline) {
  VkPipelineInfoKHR PipelineInfoKHR = {};
  PipelineInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR;
  PipelineInfoKHR.pNext = nullptr;
  PipelineInfoKHR.pipeline = pipeline;
  return PipelineInfoKHR;
}

// inline VkPipelineExecutablePropertiesKHR
// vkiPipelineExecutablePropertiesKHR(VkShaderStageFlags stages, char
// name[VK_MAX_DESCRIPTION_SIZE], char description[VK_MAX_DESCRIPTION_SIZE],
// uint32_t subgroupSize) {
//     VkPipelineExecutablePropertiesKHR PipelineExecutablePropertiesKHR = {};
//     PipelineExecutablePropertiesKHR.sType =
//     VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR;
//     PipelineExecutablePropertiesKHR.pNext = nullptr;
//     PipelineExecutablePropertiesKHR.stages = stages;
//     PipelineExecutablePropertiesKHR.name[VK_MAX_DESCRIPTION_SIZE] =
//     name[VK_MAX_DESCRIPTION_SIZE];
//     PipelineExecutablePropertiesKHR.description[VK_MAX_DESCRIPTION_SIZE] =
//     description[VK_MAX_DESCRIPTION_SIZE];
//     PipelineExecutablePropertiesKHR.subgroupSize = subgroupSize;
//     return PipelineExecutablePropertiesKHR;
// }

inline VkPipelineExecutableInfoKHR vkiPipelineExecutableInfoKHR(
    VkPipeline pipeline, uint32_t executableIndex) {
  VkPipelineExecutableInfoKHR PipelineExecutableInfoKHR = {};
  PipelineExecutableInfoKHR.sType =
      VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR;
  PipelineExecutableInfoKHR.pNext = nullptr;
  PipelineExecutableInfoKHR.pipeline = pipeline;
  PipelineExecutableInfoKHR.executableIndex = executableIndex;
  return PipelineExecutableInfoKHR;
}

// inline VkPipelineExecutableStatisticKHR
// vkiPipelineExecutableStatisticKHR(char name[VK_MAX_DESCRIPTION_SIZE], char
// description[VK_MAX_DESCRIPTION_SIZE], VkPipelineExecutableStatisticFormatKHR
// format, VkPipelineExecutableStatisticValueKHR value) {
//     VkPipelineExecutableStatisticKHR PipelineExecutableStatisticKHR = {};
//     PipelineExecutableStatisticKHR.sType =
//     VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR;
//     PipelineExecutableStatisticKHR.pNext = nullptr;
//     PipelineExecutableStatisticKHR.name[VK_MAX_DESCRIPTION_SIZE] =
//     name[VK_MAX_DESCRIPTION_SIZE];
//     PipelineExecutableStatisticKHR.description[VK_MAX_DESCRIPTION_SIZE] =
//     description[VK_MAX_DESCRIPTION_SIZE];
//     PipelineExecutableStatisticKHR.format = format;
//     PipelineExecutableStatisticKHR.value = value;
//     return PipelineExecutableStatisticKHR;
// }

// inline VkPipelineExecutableInternalRepresentationKHR
// vkiPipelineExecutableInternalRepresentationKHR(char
// name[VK_MAX_DESCRIPTION_SIZE], char description[VK_MAX_DESCRIPTION_SIZE],
// VkBool32 isText, size_t dataSize, void* pData) {
//     VkPipelineExecutableInternalRepresentationKHR
//     PipelineExecutableInternalRepresentationKHR = {};
//     PipelineExecutableInternalRepresentationKHR.sType =
//     VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR;
//     PipelineExecutableInternalRepresentationKHR.pNext = nullptr;
//     PipelineExecutableInternalRepresentationKHR.name[VK_MAX_DESCRIPTION_SIZE]
//     = name[VK_MAX_DESCRIPTION_SIZE];
//     PipelineExecutableInternalRepresentationKHR.description[VK_MAX_DESCRIPTION_SIZE]
//     = description[VK_MAX_DESCRIPTION_SIZE];
//     PipelineExecutableInternalRepresentationKHR.isText = isText;
//     PipelineExecutableInternalRepresentationKHR.dataSize = dataSize;
//     PipelineExecutableInternalRepresentationKHR.pData = pData;
//     return PipelineExecutableInternalRepresentationKHR;
// }

inline VkDebugReportCallbackCreateInfoEXT vkiDebugReportCallbackCreateInfoEXT(
    PFN_vkDebugReportCallbackEXT pfnCallback, void* pUserData) {
  VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCreateInfoEXT = {};
  DebugReportCallbackCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  DebugReportCallbackCreateInfoEXT.pNext = nullptr;
  DebugReportCallbackCreateInfoEXT.flags = 0;
  DebugReportCallbackCreateInfoEXT.pfnCallback = pfnCallback;
  DebugReportCallbackCreateInfoEXT.pUserData = pUserData;
  return DebugReportCallbackCreateInfoEXT;
}

inline VkPipelineRasterizationStateRasterizationOrderAMD
vkiPipelineRasterizationStateRasterizationOrderAMD(
    VkRasterizationOrderAMD rasterizationOrder) {
  VkPipelineRasterizationStateRasterizationOrderAMD
      PipelineRasterizationStateRasterizationOrderAMD = {};
  PipelineRasterizationStateRasterizationOrderAMD.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD;
  PipelineRasterizationStateRasterizationOrderAMD.pNext = nullptr;
  PipelineRasterizationStateRasterizationOrderAMD.rasterizationOrder =
      rasterizationOrder;
  return PipelineRasterizationStateRasterizationOrderAMD;
}

inline VkDebugMarkerObjectNameInfoEXT vkiDebugMarkerObjectNameInfoEXT(
    VkDebugReportObjectTypeEXT objectType, uint64_t object,
    const char* pObjectName) {
  VkDebugMarkerObjectNameInfoEXT DebugMarkerObjectNameInfoEXT = {};
  DebugMarkerObjectNameInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
  DebugMarkerObjectNameInfoEXT.pNext = nullptr;
  DebugMarkerObjectNameInfoEXT.objectType = objectType;
  DebugMarkerObjectNameInfoEXT.object = object;
  DebugMarkerObjectNameInfoEXT.pObjectName = pObjectName;
  return DebugMarkerObjectNameInfoEXT;
}

inline VkDebugMarkerObjectTagInfoEXT vkiDebugMarkerObjectTagInfoEXT(
    VkDebugReportObjectTypeEXT objectType, uint64_t object, uint64_t tagName,
    size_t tagSize, const void* pTag) {
  VkDebugMarkerObjectTagInfoEXT DebugMarkerObjectTagInfoEXT = {};
  DebugMarkerObjectTagInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
  DebugMarkerObjectTagInfoEXT.pNext = nullptr;
  DebugMarkerObjectTagInfoEXT.objectType = objectType;
  DebugMarkerObjectTagInfoEXT.object = object;
  DebugMarkerObjectTagInfoEXT.tagName = tagName;
  DebugMarkerObjectTagInfoEXT.tagSize = tagSize;
  DebugMarkerObjectTagInfoEXT.pTag = pTag;
  return DebugMarkerObjectTagInfoEXT;
}

// inline VkDebugMarkerMarkerInfoEXT vkiDebugMarkerMarkerInfoEXT(const char*
// pMarkerName, float color[4]) {
//     VkDebugMarkerMarkerInfoEXT DebugMarkerMarkerInfoEXT = {};
//     DebugMarkerMarkerInfoEXT.sType =
//     VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
//     DebugMarkerMarkerInfoEXT.pNext = nullptr;
//     DebugMarkerMarkerInfoEXT.pMarkerName = pMarkerName;
//     DebugMarkerMarkerInfoEXT.color[4] = color[4];
//     return DebugMarkerMarkerInfoEXT;
// }

inline VkDedicatedAllocationImageCreateInfoNV
vkiDedicatedAllocationImageCreateInfoNV(VkBool32 dedicatedAllocation) {
  VkDedicatedAllocationImageCreateInfoNV DedicatedAllocationImageCreateInfoNV =
      {};
  DedicatedAllocationImageCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV;
  DedicatedAllocationImageCreateInfoNV.pNext = nullptr;
  DedicatedAllocationImageCreateInfoNV.dedicatedAllocation =
      dedicatedAllocation;
  return DedicatedAllocationImageCreateInfoNV;
}

inline VkDedicatedAllocationBufferCreateInfoNV
vkiDedicatedAllocationBufferCreateInfoNV(VkBool32 dedicatedAllocation) {
  VkDedicatedAllocationBufferCreateInfoNV
      DedicatedAllocationBufferCreateInfoNV = {};
  DedicatedAllocationBufferCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV;
  DedicatedAllocationBufferCreateInfoNV.pNext = nullptr;
  DedicatedAllocationBufferCreateInfoNV.dedicatedAllocation =
      dedicatedAllocation;
  return DedicatedAllocationBufferCreateInfoNV;
}

inline VkDedicatedAllocationMemoryAllocateInfoNV
vkiDedicatedAllocationMemoryAllocateInfoNV(VkImage image, VkBuffer buffer) {
  VkDedicatedAllocationMemoryAllocateInfoNV
      DedicatedAllocationMemoryAllocateInfoNV = {};
  DedicatedAllocationMemoryAllocateInfoNV.sType =
      VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV;
  DedicatedAllocationMemoryAllocateInfoNV.pNext = nullptr;
  DedicatedAllocationMemoryAllocateInfoNV.image = image;
  DedicatedAllocationMemoryAllocateInfoNV.buffer = buffer;
  return DedicatedAllocationMemoryAllocateInfoNV;
}

inline VkPhysicalDeviceTransformFeedbackFeaturesEXT
vkiPhysicalDeviceTransformFeedbackFeaturesEXT(VkBool32 transformFeedback,
                                              VkBool32 geometryStreams) {
  VkPhysicalDeviceTransformFeedbackFeaturesEXT
      PhysicalDeviceTransformFeedbackFeaturesEXT = {};
  PhysicalDeviceTransformFeedbackFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT;
  PhysicalDeviceTransformFeedbackFeaturesEXT.pNext = nullptr;
  PhysicalDeviceTransformFeedbackFeaturesEXT.transformFeedback =
      transformFeedback;
  PhysicalDeviceTransformFeedbackFeaturesEXT.geometryStreams = geometryStreams;
  return PhysicalDeviceTransformFeedbackFeaturesEXT;
}

inline VkPhysicalDeviceTransformFeedbackPropertiesEXT
vkiPhysicalDeviceTransformFeedbackPropertiesEXT(
    uint32_t maxTransformFeedbackStreams, uint32_t maxTransformFeedbackBuffers,
    VkDeviceSize maxTransformFeedbackBufferSize,
    uint32_t maxTransformFeedbackStreamDataSize,
    uint32_t maxTransformFeedbackBufferDataSize,
    uint32_t maxTransformFeedbackBufferDataStride,
    VkBool32 transformFeedbackQueries,
    VkBool32 transformFeedbackStreamsLinesTriangles,
    VkBool32 transformFeedbackRasterizationStreamSelect,
    VkBool32 transformFeedbackDraw) {
  VkPhysicalDeviceTransformFeedbackPropertiesEXT
      PhysicalDeviceTransformFeedbackPropertiesEXT = {};
  PhysicalDeviceTransformFeedbackPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT;
  PhysicalDeviceTransformFeedbackPropertiesEXT.pNext = nullptr;
  PhysicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackStreams =
      maxTransformFeedbackStreams;
  PhysicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBuffers =
      maxTransformFeedbackBuffers;
  PhysicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferSize =
      maxTransformFeedbackBufferSize;
  PhysicalDeviceTransformFeedbackPropertiesEXT
      .maxTransformFeedbackStreamDataSize = maxTransformFeedbackStreamDataSize;
  PhysicalDeviceTransformFeedbackPropertiesEXT
      .maxTransformFeedbackBufferDataSize = maxTransformFeedbackBufferDataSize;
  PhysicalDeviceTransformFeedbackPropertiesEXT
      .maxTransformFeedbackBufferDataStride =
      maxTransformFeedbackBufferDataStride;
  PhysicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackQueries =
      transformFeedbackQueries;
  PhysicalDeviceTransformFeedbackPropertiesEXT
      .transformFeedbackStreamsLinesTriangles =
      transformFeedbackStreamsLinesTriangles;
  PhysicalDeviceTransformFeedbackPropertiesEXT
      .transformFeedbackRasterizationStreamSelect =
      transformFeedbackRasterizationStreamSelect;
  PhysicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackDraw =
      transformFeedbackDraw;
  return PhysicalDeviceTransformFeedbackPropertiesEXT;
}

inline VkPipelineRasterizationStateStreamCreateInfoEXT
vkiPipelineRasterizationStateStreamCreateInfoEXT(uint32_t rasterizationStream) {
  VkPipelineRasterizationStateStreamCreateInfoEXT
      PipelineRasterizationStateStreamCreateInfoEXT = {};
  PipelineRasterizationStateStreamCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT;
  PipelineRasterizationStateStreamCreateInfoEXT.pNext = nullptr;
  PipelineRasterizationStateStreamCreateInfoEXT.flags = 0;
  PipelineRasterizationStateStreamCreateInfoEXT.rasterizationStream =
      rasterizationStream;
  return PipelineRasterizationStateStreamCreateInfoEXT;
}

inline VkImageViewHandleInfoNVX vkiImageViewHandleInfoNVX(
    VkImageView imageView, VkDescriptorType descriptorType, VkSampler sampler) {
  VkImageViewHandleInfoNVX ImageViewHandleInfoNVX = {};
  ImageViewHandleInfoNVX.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX;
  ImageViewHandleInfoNVX.pNext = nullptr;
  ImageViewHandleInfoNVX.imageView = imageView;
  ImageViewHandleInfoNVX.descriptorType = descriptorType;
  ImageViewHandleInfoNVX.sampler = sampler;
  return ImageViewHandleInfoNVX;
}

inline VkTextureLODGatherFormatPropertiesAMD
vkiTextureLODGatherFormatPropertiesAMD(
    VkBool32 supportsTextureGatherLODBiasAMD) {
  VkTextureLODGatherFormatPropertiesAMD TextureLODGatherFormatPropertiesAMD =
      {};
  TextureLODGatherFormatPropertiesAMD.sType =
      VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD;
  TextureLODGatherFormatPropertiesAMD.pNext = nullptr;
  TextureLODGatherFormatPropertiesAMD.supportsTextureGatherLODBiasAMD =
      supportsTextureGatherLODBiasAMD;
  return TextureLODGatherFormatPropertiesAMD;
}

inline VkShaderResourceUsageAMD vkiShaderResourceUsageAMD(
    uint32_t numUsedVgprs, uint32_t numUsedSgprs,
    uint32_t ldsSizePerLocalWorkGroup, size_t ldsUsageSizeInBytes,
    size_t scratchMemUsageInBytes) {
  VkShaderResourceUsageAMD ShaderResourceUsageAMD = {};
  ShaderResourceUsageAMD.numUsedVgprs = numUsedVgprs;
  ShaderResourceUsageAMD.numUsedSgprs = numUsedSgprs;
  ShaderResourceUsageAMD.ldsSizePerLocalWorkGroup = ldsSizePerLocalWorkGroup;
  ShaderResourceUsageAMD.ldsUsageSizeInBytes = ldsUsageSizeInBytes;
  ShaderResourceUsageAMD.scratchMemUsageInBytes = scratchMemUsageInBytes;
  return ShaderResourceUsageAMD;
}

// inline VkShaderStatisticsInfoAMD
// vkiShaderStatisticsInfoAMD(VkShaderStageFlags shaderStageMask,
// VkShaderResourceUsageAMD resourceUsage, uint32_t numPhysicalVgprs, uint32_t
// numPhysicalSgprs, uint32_t numAvailableVgprs, uint32_t numAvailableSgprs,
// uint32_t computeWorkGroupSize[3]) {
//     VkShaderStatisticsInfoAMD ShaderStatisticsInfoAMD = {};
//     ShaderStatisticsInfoAMD.shaderStageMask = shaderStageMask;
//     ShaderStatisticsInfoAMD.resourceUsage = resourceUsage;
//     ShaderStatisticsInfoAMD.numPhysicalVgprs = numPhysicalVgprs;
//     ShaderStatisticsInfoAMD.numPhysicalSgprs = numPhysicalSgprs;
//     ShaderStatisticsInfoAMD.numAvailableVgprs = numAvailableVgprs;
//     ShaderStatisticsInfoAMD.numAvailableSgprs = numAvailableSgprs;
//     ShaderStatisticsInfoAMD.computeWorkGroupSize[3] =
//     computeWorkGroupSize[3]; return ShaderStatisticsInfoAMD;
// }

inline VkPhysicalDeviceCornerSampledImageFeaturesNV
vkiPhysicalDeviceCornerSampledImageFeaturesNV(VkBool32 cornerSampledImage) {
  VkPhysicalDeviceCornerSampledImageFeaturesNV
      PhysicalDeviceCornerSampledImageFeaturesNV = {};
  PhysicalDeviceCornerSampledImageFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV;
  PhysicalDeviceCornerSampledImageFeaturesNV.pNext = nullptr;
  PhysicalDeviceCornerSampledImageFeaturesNV.cornerSampledImage =
      cornerSampledImage;
  return PhysicalDeviceCornerSampledImageFeaturesNV;
}

inline VkExternalImageFormatPropertiesNV vkiExternalImageFormatPropertiesNV(
    VkImageFormatProperties imageFormatProperties,
    VkExternalMemoryFeatureFlagsNV externalMemoryFeatures,
    VkExternalMemoryHandleTypeFlagsNV exportFromImportedHandleTypes,
    VkExternalMemoryHandleTypeFlagsNV compatibleHandleTypes) {
  VkExternalImageFormatPropertiesNV ExternalImageFormatPropertiesNV = {};
  ExternalImageFormatPropertiesNV.imageFormatProperties = imageFormatProperties;
  ExternalImageFormatPropertiesNV.externalMemoryFeatures =
      externalMemoryFeatures;
  ExternalImageFormatPropertiesNV.exportFromImportedHandleTypes =
      exportFromImportedHandleTypes;
  ExternalImageFormatPropertiesNV.compatibleHandleTypes = compatibleHandleTypes;
  return ExternalImageFormatPropertiesNV;
}

inline VkExternalMemoryImageCreateInfoNV vkiExternalMemoryImageCreateInfoNV(
    VkExternalMemoryHandleTypeFlagsNV handleTypes) {
  VkExternalMemoryImageCreateInfoNV ExternalMemoryImageCreateInfoNV = {};
  ExternalMemoryImageCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV;
  ExternalMemoryImageCreateInfoNV.pNext = nullptr;
  ExternalMemoryImageCreateInfoNV.handleTypes = handleTypes;
  return ExternalMemoryImageCreateInfoNV;
}

inline VkExportMemoryAllocateInfoNV vkiExportMemoryAllocateInfoNV(
    VkExternalMemoryHandleTypeFlagsNV handleTypes) {
  VkExportMemoryAllocateInfoNV ExportMemoryAllocateInfoNV = {};
  ExportMemoryAllocateInfoNV.sType =
      VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV;
  ExportMemoryAllocateInfoNV.pNext = nullptr;
  ExportMemoryAllocateInfoNV.handleTypes = handleTypes;
  return ExportMemoryAllocateInfoNV;
}

inline VkValidationFlagsEXT vkiValidationFlagsEXT(
    uint32_t disabledValidationCheckCount,
    const VkValidationCheckEXT* pDisabledValidationChecks) {
  VkValidationFlagsEXT ValidationFlagsEXT = {};
  ValidationFlagsEXT.sType = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT;
  ValidationFlagsEXT.pNext = nullptr;
  ValidationFlagsEXT.disabledValidationCheckCount =
      disabledValidationCheckCount;
  ValidationFlagsEXT.pDisabledValidationChecks = pDisabledValidationChecks;
  return ValidationFlagsEXT;
}

inline VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT
vkiPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT(
    VkBool32 textureCompressionASTC_HDR) {
  VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT
      PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT = {};
  PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES_EXT;
  PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT.pNext = nullptr;
  PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT
      .textureCompressionASTC_HDR = textureCompressionASTC_HDR;
  return PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT;
}

inline VkImageViewASTCDecodeModeEXT vkiImageViewASTCDecodeModeEXT(
    VkFormat decodeMode) {
  VkImageViewASTCDecodeModeEXT ImageViewASTCDecodeModeEXT = {};
  ImageViewASTCDecodeModeEXT.sType =
      VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT;
  ImageViewASTCDecodeModeEXT.pNext = nullptr;
  ImageViewASTCDecodeModeEXT.decodeMode = decodeMode;
  return ImageViewASTCDecodeModeEXT;
}

inline VkPhysicalDeviceASTCDecodeFeaturesEXT
vkiPhysicalDeviceASTCDecodeFeaturesEXT(VkBool32 decodeModeSharedExponent) {
  VkPhysicalDeviceASTCDecodeFeaturesEXT PhysicalDeviceASTCDecodeFeaturesEXT =
      {};
  PhysicalDeviceASTCDecodeFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT;
  PhysicalDeviceASTCDecodeFeaturesEXT.pNext = nullptr;
  PhysicalDeviceASTCDecodeFeaturesEXT.decodeModeSharedExponent =
      decodeModeSharedExponent;
  return PhysicalDeviceASTCDecodeFeaturesEXT;
}

inline VkConditionalRenderingBeginInfoEXT vkiConditionalRenderingBeginInfoEXT(
    VkBuffer buffer, VkDeviceSize offset) {
  VkConditionalRenderingBeginInfoEXT ConditionalRenderingBeginInfoEXT = {};
  ConditionalRenderingBeginInfoEXT.sType =
      VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT;
  ConditionalRenderingBeginInfoEXT.pNext = nullptr;
  ConditionalRenderingBeginInfoEXT.flags = 0;
  ConditionalRenderingBeginInfoEXT.buffer = buffer;
  ConditionalRenderingBeginInfoEXT.offset = offset;
  return ConditionalRenderingBeginInfoEXT;
}

inline VkPhysicalDeviceConditionalRenderingFeaturesEXT
vkiPhysicalDeviceConditionalRenderingFeaturesEXT(
    VkBool32 conditionalRendering, VkBool32 inheritedConditionalRendering) {
  VkPhysicalDeviceConditionalRenderingFeaturesEXT
      PhysicalDeviceConditionalRenderingFeaturesEXT = {};
  PhysicalDeviceConditionalRenderingFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT;
  PhysicalDeviceConditionalRenderingFeaturesEXT.pNext = nullptr;
  PhysicalDeviceConditionalRenderingFeaturesEXT.conditionalRendering =
      conditionalRendering;
  PhysicalDeviceConditionalRenderingFeaturesEXT.inheritedConditionalRendering =
      inheritedConditionalRendering;
  return PhysicalDeviceConditionalRenderingFeaturesEXT;
}

inline VkCommandBufferInheritanceConditionalRenderingInfoEXT
vkiCommandBufferInheritanceConditionalRenderingInfoEXT(
    VkBool32 conditionalRenderingEnable) {
  VkCommandBufferInheritanceConditionalRenderingInfoEXT
      CommandBufferInheritanceConditionalRenderingInfoEXT = {};
  CommandBufferInheritanceConditionalRenderingInfoEXT.sType =
      VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT;
  CommandBufferInheritanceConditionalRenderingInfoEXT.pNext = nullptr;
  CommandBufferInheritanceConditionalRenderingInfoEXT
      .conditionalRenderingEnable = conditionalRenderingEnable;
  return CommandBufferInheritanceConditionalRenderingInfoEXT;
}

inline VkPipelineViewportWScalingStateCreateInfoNV
vkiPipelineViewportWScalingStateCreateInfoNV(
    VkBool32 viewportWScalingEnable, uint32_t viewportCount,
    const VkViewportWScalingNV* pViewportWScalings) {
  VkPipelineViewportWScalingStateCreateInfoNV
      PipelineViewportWScalingStateCreateInfoNV = {};
  PipelineViewportWScalingStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV;
  PipelineViewportWScalingStateCreateInfoNV.pNext = nullptr;
  PipelineViewportWScalingStateCreateInfoNV.viewportWScalingEnable =
      viewportWScalingEnable;
  PipelineViewportWScalingStateCreateInfoNV.viewportCount = viewportCount;
  PipelineViewportWScalingStateCreateInfoNV.pViewportWScalings =
      pViewportWScalings;
  return PipelineViewportWScalingStateCreateInfoNV;
}

inline VkSurfaceCapabilities2EXT vkiSurfaceCapabilities2EXT(
    uint32_t minImageCount, uint32_t maxImageCount, VkExtent2D currentExtent,
    VkExtent2D minImageExtent, VkExtent2D maxImageExtent,
    uint32_t maxImageArrayLayers,
    VkSurfaceTransformFlagsKHR supportedTransforms,
    VkSurfaceTransformFlagBitsKHR currentTransform,
    VkCompositeAlphaFlagsKHR supportedCompositeAlpha,
    VkImageUsageFlags supportedUsageFlags,
    VkSurfaceCounterFlagsEXT supportedSurfaceCounters) {
  VkSurfaceCapabilities2EXT SurfaceCapabilities2EXT = {};
  SurfaceCapabilities2EXT.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT;
  SurfaceCapabilities2EXT.pNext = nullptr;
  SurfaceCapabilities2EXT.minImageCount = minImageCount;
  SurfaceCapabilities2EXT.maxImageCount = maxImageCount;
  SurfaceCapabilities2EXT.currentExtent = currentExtent;
  SurfaceCapabilities2EXT.minImageExtent = minImageExtent;
  SurfaceCapabilities2EXT.maxImageExtent = maxImageExtent;
  SurfaceCapabilities2EXT.maxImageArrayLayers = maxImageArrayLayers;
  SurfaceCapabilities2EXT.supportedTransforms = supportedTransforms;
  SurfaceCapabilities2EXT.currentTransform = currentTransform;
  SurfaceCapabilities2EXT.supportedCompositeAlpha = supportedCompositeAlpha;
  SurfaceCapabilities2EXT.supportedUsageFlags = supportedUsageFlags;
  SurfaceCapabilities2EXT.supportedSurfaceCounters = supportedSurfaceCounters;
  return SurfaceCapabilities2EXT;
}

inline VkDisplayPowerInfoEXT vkiDisplayPowerInfoEXT(
    VkDisplayPowerStateEXT powerState) {
  VkDisplayPowerInfoEXT DisplayPowerInfoEXT = {};
  DisplayPowerInfoEXT.sType = VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT;
  DisplayPowerInfoEXT.pNext = nullptr;
  DisplayPowerInfoEXT.powerState = powerState;
  return DisplayPowerInfoEXT;
}

inline VkDeviceEventInfoEXT vkiDeviceEventInfoEXT(
    VkDeviceEventTypeEXT deviceEvent) {
  VkDeviceEventInfoEXT DeviceEventInfoEXT = {};
  DeviceEventInfoEXT.sType = VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT;
  DeviceEventInfoEXT.pNext = nullptr;
  DeviceEventInfoEXT.deviceEvent = deviceEvent;
  return DeviceEventInfoEXT;
}

inline VkDisplayEventInfoEXT vkiDisplayEventInfoEXT(
    VkDisplayEventTypeEXT displayEvent) {
  VkDisplayEventInfoEXT DisplayEventInfoEXT = {};
  DisplayEventInfoEXT.sType = VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT;
  DisplayEventInfoEXT.pNext = nullptr;
  DisplayEventInfoEXT.displayEvent = displayEvent;
  return DisplayEventInfoEXT;
}

inline VkSwapchainCounterCreateInfoEXT vkiSwapchainCounterCreateInfoEXT(
    VkSurfaceCounterFlagsEXT surfaceCounters) {
  VkSwapchainCounterCreateInfoEXT SwapchainCounterCreateInfoEXT = {};
  SwapchainCounterCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT;
  SwapchainCounterCreateInfoEXT.pNext = nullptr;
  SwapchainCounterCreateInfoEXT.surfaceCounters = surfaceCounters;
  return SwapchainCounterCreateInfoEXT;
}

inline VkRefreshCycleDurationGOOGLE vkiRefreshCycleDurationGOOGLE(
    uint64_t refreshDuration) {
  VkRefreshCycleDurationGOOGLE RefreshCycleDurationGOOGLE = {};
  RefreshCycleDurationGOOGLE.refreshDuration = refreshDuration;
  return RefreshCycleDurationGOOGLE;
}

inline VkPastPresentationTimingGOOGLE vkiPastPresentationTimingGOOGLE(
    uint32_t presentID, uint64_t desiredPresentTime, uint64_t actualPresentTime,
    uint64_t earliestPresentTime, uint64_t presentMargin) {
  VkPastPresentationTimingGOOGLE PastPresentationTimingGOOGLE = {};
  PastPresentationTimingGOOGLE.presentID = presentID;
  PastPresentationTimingGOOGLE.desiredPresentTime = desiredPresentTime;
  PastPresentationTimingGOOGLE.actualPresentTime = actualPresentTime;
  PastPresentationTimingGOOGLE.earliestPresentTime = earliestPresentTime;
  PastPresentationTimingGOOGLE.presentMargin = presentMargin;
  return PastPresentationTimingGOOGLE;
}

inline VkPresentTimeGOOGLE vkiPresentTimeGOOGLE(uint32_t presentID,
                                                uint64_t desiredPresentTime) {
  VkPresentTimeGOOGLE PresentTimeGOOGLE = {};
  PresentTimeGOOGLE.presentID = presentID;
  PresentTimeGOOGLE.desiredPresentTime = desiredPresentTime;
  return PresentTimeGOOGLE;
}

inline VkPresentTimesInfoGOOGLE vkiPresentTimesInfoGOOGLE(
    uint32_t swapchainCount, const VkPresentTimeGOOGLE* pTimes) {
  VkPresentTimesInfoGOOGLE PresentTimesInfoGOOGLE = {};
  PresentTimesInfoGOOGLE.sType = VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE;
  PresentTimesInfoGOOGLE.pNext = nullptr;
  PresentTimesInfoGOOGLE.swapchainCount = swapchainCount;
  PresentTimesInfoGOOGLE.pTimes = pTimes;
  return PresentTimesInfoGOOGLE;
}

inline VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX
vkiPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX(
    VkBool32 perViewPositionAllComponents) {
  VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX
      PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX = {};
  PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
  PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX.pNext = nullptr;
  PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX
      .perViewPositionAllComponents = perViewPositionAllComponents;
  return PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX;
}

inline VkViewportSwizzleNV vkiViewportSwizzleNV(
    VkViewportCoordinateSwizzleNV x, VkViewportCoordinateSwizzleNV y,
    VkViewportCoordinateSwizzleNV z, VkViewportCoordinateSwizzleNV w) {
  VkViewportSwizzleNV ViewportSwizzleNV = {};
  ViewportSwizzleNV.x = x;
  ViewportSwizzleNV.y = y;
  ViewportSwizzleNV.z = z;
  ViewportSwizzleNV.w = w;
  return ViewportSwizzleNV;
}

inline VkPipelineViewportSwizzleStateCreateInfoNV
vkiPipelineViewportSwizzleStateCreateInfoNV(
    uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) {
  VkPipelineViewportSwizzleStateCreateInfoNV
      PipelineViewportSwizzleStateCreateInfoNV = {};
  PipelineViewportSwizzleStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV;
  PipelineViewportSwizzleStateCreateInfoNV.pNext = nullptr;
  PipelineViewportSwizzleStateCreateInfoNV.flags = 0;
  PipelineViewportSwizzleStateCreateInfoNV.viewportCount = viewportCount;
  PipelineViewportSwizzleStateCreateInfoNV.pViewportSwizzles =
      pViewportSwizzles;
  return PipelineViewportSwizzleStateCreateInfoNV;
}

inline VkPhysicalDeviceDiscardRectanglePropertiesEXT
vkiPhysicalDeviceDiscardRectanglePropertiesEXT(uint32_t maxDiscardRectangles) {
  VkPhysicalDeviceDiscardRectanglePropertiesEXT
      PhysicalDeviceDiscardRectanglePropertiesEXT = {};
  PhysicalDeviceDiscardRectanglePropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
  PhysicalDeviceDiscardRectanglePropertiesEXT.pNext = nullptr;
  PhysicalDeviceDiscardRectanglePropertiesEXT.maxDiscardRectangles =
      maxDiscardRectangles;
  return PhysicalDeviceDiscardRectanglePropertiesEXT;
}

inline VkPipelineDiscardRectangleStateCreateInfoEXT
vkiPipelineDiscardRectangleStateCreateInfoEXT(
    VkDiscardRectangleModeEXT discardRectangleMode,
    uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) {
  VkPipelineDiscardRectangleStateCreateInfoEXT
      PipelineDiscardRectangleStateCreateInfoEXT = {};
  PipelineDiscardRectangleStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT;
  PipelineDiscardRectangleStateCreateInfoEXT.pNext = nullptr;
  PipelineDiscardRectangleStateCreateInfoEXT.flags = 0;
  PipelineDiscardRectangleStateCreateInfoEXT.discardRectangleMode =
      discardRectangleMode;
  PipelineDiscardRectangleStateCreateInfoEXT.discardRectangleCount =
      discardRectangleCount;
  PipelineDiscardRectangleStateCreateInfoEXT.pDiscardRectangles =
      pDiscardRectangles;
  return PipelineDiscardRectangleStateCreateInfoEXT;
}

inline VkPhysicalDeviceConservativeRasterizationPropertiesEXT
vkiPhysicalDeviceConservativeRasterizationPropertiesEXT(
    float primitiveOverestimationSize,
    float maxExtraPrimitiveOverestimationSize,
    float extraPrimitiveOverestimationSizeGranularity,
    VkBool32 primitiveUnderestimation,
    VkBool32 conservativePointAndLineRasterization,
    VkBool32 degenerateTrianglesRasterized, VkBool32 degenerateLinesRasterized,
    VkBool32 fullyCoveredFragmentShaderInputVariable,
    VkBool32 conservativeRasterizationPostDepthCoverage) {
  VkPhysicalDeviceConservativeRasterizationPropertiesEXT
      PhysicalDeviceConservativeRasterizationPropertiesEXT = {};
  PhysicalDeviceConservativeRasterizationPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
  PhysicalDeviceConservativeRasterizationPropertiesEXT.pNext = nullptr;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .primitiveOverestimationSize = primitiveOverestimationSize;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .maxExtraPrimitiveOverestimationSize =
      maxExtraPrimitiveOverestimationSize;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .extraPrimitiveOverestimationSizeGranularity =
      extraPrimitiveOverestimationSizeGranularity;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .primitiveUnderestimation = primitiveUnderestimation;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .conservativePointAndLineRasterization =
      conservativePointAndLineRasterization;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .degenerateTrianglesRasterized = degenerateTrianglesRasterized;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .degenerateLinesRasterized = degenerateLinesRasterized;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .fullyCoveredFragmentShaderInputVariable =
      fullyCoveredFragmentShaderInputVariable;
  PhysicalDeviceConservativeRasterizationPropertiesEXT
      .conservativeRasterizationPostDepthCoverage =
      conservativeRasterizationPostDepthCoverage;
  return PhysicalDeviceConservativeRasterizationPropertiesEXT;
}

inline VkPipelineRasterizationConservativeStateCreateInfoEXT
vkiPipelineRasterizationConservativeStateCreateInfoEXT(
    VkConservativeRasterizationModeEXT conservativeRasterizationMode,
    float extraPrimitiveOverestimationSize) {
  VkPipelineRasterizationConservativeStateCreateInfoEXT
      PipelineRasterizationConservativeStateCreateInfoEXT = {};
  PipelineRasterizationConservativeStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT;
  PipelineRasterizationConservativeStateCreateInfoEXT.pNext = nullptr;
  PipelineRasterizationConservativeStateCreateInfoEXT.flags = 0;
  PipelineRasterizationConservativeStateCreateInfoEXT
      .conservativeRasterizationMode = conservativeRasterizationMode;
  PipelineRasterizationConservativeStateCreateInfoEXT
      .extraPrimitiveOverestimationSize = extraPrimitiveOverestimationSize;
  return PipelineRasterizationConservativeStateCreateInfoEXT;
}

inline VkPhysicalDeviceDepthClipEnableFeaturesEXT
vkiPhysicalDeviceDepthClipEnableFeaturesEXT(VkBool32 depthClipEnable) {
  VkPhysicalDeviceDepthClipEnableFeaturesEXT
      PhysicalDeviceDepthClipEnableFeaturesEXT = {};
  PhysicalDeviceDepthClipEnableFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT;
  PhysicalDeviceDepthClipEnableFeaturesEXT.pNext = nullptr;
  PhysicalDeviceDepthClipEnableFeaturesEXT.depthClipEnable = depthClipEnable;
  return PhysicalDeviceDepthClipEnableFeaturesEXT;
}

inline VkPipelineRasterizationDepthClipStateCreateInfoEXT
vkiPipelineRasterizationDepthClipStateCreateInfoEXT(VkBool32 depthClipEnable) {
  VkPipelineRasterizationDepthClipStateCreateInfoEXT
      PipelineRasterizationDepthClipStateCreateInfoEXT = {};
  PipelineRasterizationDepthClipStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT;
  PipelineRasterizationDepthClipStateCreateInfoEXT.pNext = nullptr;
  PipelineRasterizationDepthClipStateCreateInfoEXT.flags = 0;
  PipelineRasterizationDepthClipStateCreateInfoEXT.depthClipEnable =
      depthClipEnable;
  return PipelineRasterizationDepthClipStateCreateInfoEXT;
}

inline VkXYColorEXT vkiXYColorEXT(float x, float y) {
  VkXYColorEXT XYColorEXT = {};
  XYColorEXT.x = x;
  XYColorEXT.y = y;
  return XYColorEXT;
}

inline VkHdrMetadataEXT vkiHdrMetadataEXT(
    VkXYColorEXT displayPrimaryRed, VkXYColorEXT displayPrimaryGreen,
    VkXYColorEXT displayPrimaryBlue, VkXYColorEXT whitePoint,
    float maxLuminance, float minLuminance, float maxContentLightLevel,
    float maxFrameAverageLightLevel) {
  VkHdrMetadataEXT HdrMetadataEXT = {};
  HdrMetadataEXT.sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
  HdrMetadataEXT.pNext = nullptr;
  HdrMetadataEXT.displayPrimaryRed = displayPrimaryRed;
  HdrMetadataEXT.displayPrimaryGreen = displayPrimaryGreen;
  HdrMetadataEXT.displayPrimaryBlue = displayPrimaryBlue;
  HdrMetadataEXT.whitePoint = whitePoint;
  HdrMetadataEXT.maxLuminance = maxLuminance;
  HdrMetadataEXT.minLuminance = minLuminance;
  HdrMetadataEXT.maxContentLightLevel = maxContentLightLevel;
  HdrMetadataEXT.maxFrameAverageLightLevel = maxFrameAverageLightLevel;
  return HdrMetadataEXT;
}

inline VkDebugUtilsObjectNameInfoEXT vkiDebugUtilsObjectNameInfoEXT(
    VkObjectType objectType, uint64_t objectHandle, const char* pObjectName) {
  VkDebugUtilsObjectNameInfoEXT DebugUtilsObjectNameInfoEXT = {};
  DebugUtilsObjectNameInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
  DebugUtilsObjectNameInfoEXT.pNext = nullptr;
  DebugUtilsObjectNameInfoEXT.objectType = objectType;
  DebugUtilsObjectNameInfoEXT.objectHandle = objectHandle;
  DebugUtilsObjectNameInfoEXT.pObjectName = pObjectName;
  return DebugUtilsObjectNameInfoEXT;
}

inline VkDebugUtilsObjectTagInfoEXT vkiDebugUtilsObjectTagInfoEXT(
    VkObjectType objectType, uint64_t objectHandle, uint64_t tagName,
    size_t tagSize, const void* pTag) {
  VkDebugUtilsObjectTagInfoEXT DebugUtilsObjectTagInfoEXT = {};
  DebugUtilsObjectTagInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
  DebugUtilsObjectTagInfoEXT.pNext = nullptr;
  DebugUtilsObjectTagInfoEXT.objectType = objectType;
  DebugUtilsObjectTagInfoEXT.objectHandle = objectHandle;
  DebugUtilsObjectTagInfoEXT.tagName = tagName;
  DebugUtilsObjectTagInfoEXT.tagSize = tagSize;
  DebugUtilsObjectTagInfoEXT.pTag = pTag;
  return DebugUtilsObjectTagInfoEXT;
}

// inline VkDebugUtilsLabelEXT vkiDebugUtilsLabelEXT(const char* pLabelName,
// float color[4]) {
//     VkDebugUtilsLabelEXT DebugUtilsLabelEXT = {};
//     DebugUtilsLabelEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
//     DebugUtilsLabelEXT.pNext = nullptr;
//     DebugUtilsLabelEXT.pLabelName = pLabelName;
//     DebugUtilsLabelEXT.color[4] = color[4];
//     return DebugUtilsLabelEXT;
// }

inline VkDebugUtilsMessengerCallbackDataEXT
vkiDebugUtilsMessengerCallbackDataEXT(
    const char* pMessageIdName, int32_t messageIdNumber, const char* pMessage,
    uint32_t queueLabelCount, const VkDebugUtilsLabelEXT* pQueueLabels,
    uint32_t cmdBufLabelCount, const VkDebugUtilsLabelEXT* pCmdBufLabels,
    uint32_t objectCount, const VkDebugUtilsObjectNameInfoEXT* pObjects) {
  VkDebugUtilsMessengerCallbackDataEXT DebugUtilsMessengerCallbackDataEXT = {};
  DebugUtilsMessengerCallbackDataEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
  DebugUtilsMessengerCallbackDataEXT.pNext = nullptr;
  DebugUtilsMessengerCallbackDataEXT.flags = 0;
  DebugUtilsMessengerCallbackDataEXT.pMessageIdName = pMessageIdName;
  DebugUtilsMessengerCallbackDataEXT.messageIdNumber = messageIdNumber;
  DebugUtilsMessengerCallbackDataEXT.pMessage = pMessage;
  DebugUtilsMessengerCallbackDataEXT.queueLabelCount = queueLabelCount;
  DebugUtilsMessengerCallbackDataEXT.pQueueLabels = pQueueLabels;
  DebugUtilsMessengerCallbackDataEXT.cmdBufLabelCount = cmdBufLabelCount;
  DebugUtilsMessengerCallbackDataEXT.pCmdBufLabels = pCmdBufLabels;
  DebugUtilsMessengerCallbackDataEXT.objectCount = objectCount;
  DebugUtilsMessengerCallbackDataEXT.pObjects = pObjects;
  return DebugUtilsMessengerCallbackDataEXT;
}

inline VkDebugUtilsMessengerCreateInfoEXT vkiDebugUtilsMessengerCreateInfoEXT(
    VkDebugUtilsMessageSeverityFlagsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    PFN_vkDebugUtilsMessengerCallbackEXT pfnUserCallback, void* pUserData) {
  VkDebugUtilsMessengerCreateInfoEXT DebugUtilsMessengerCreateInfoEXT = {};
  DebugUtilsMessengerCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  DebugUtilsMessengerCreateInfoEXT.pNext = nullptr;
  DebugUtilsMessengerCreateInfoEXT.flags = 0;
  DebugUtilsMessengerCreateInfoEXT.messageSeverity = messageSeverity;
  DebugUtilsMessengerCreateInfoEXT.messageType = messageType;
  DebugUtilsMessengerCreateInfoEXT.pfnUserCallback = pfnUserCallback;
  DebugUtilsMessengerCreateInfoEXT.pUserData = pUserData;
  return DebugUtilsMessengerCreateInfoEXT;
}

inline VkSamplerReductionModeCreateInfoEXT vkiSamplerReductionModeCreateInfoEXT(
    VkSamplerReductionModeEXT reductionMode) {
  VkSamplerReductionModeCreateInfoEXT SamplerReductionModeCreateInfoEXT = {};
  SamplerReductionModeCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT;
  SamplerReductionModeCreateInfoEXT.pNext = nullptr;
  SamplerReductionModeCreateInfoEXT.reductionMode = reductionMode;
  return SamplerReductionModeCreateInfoEXT;
}

inline VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT
vkiPhysicalDeviceSamplerFilterMinmaxPropertiesEXT(
    VkBool32 filterMinmaxSingleComponentFormats,
    VkBool32 filterMinmaxImageComponentMapping) {
  VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT
      PhysicalDeviceSamplerFilterMinmaxPropertiesEXT = {};
  PhysicalDeviceSamplerFilterMinmaxPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES_EXT;
  PhysicalDeviceSamplerFilterMinmaxPropertiesEXT.pNext = nullptr;
  PhysicalDeviceSamplerFilterMinmaxPropertiesEXT
      .filterMinmaxSingleComponentFormats = filterMinmaxSingleComponentFormats;
  PhysicalDeviceSamplerFilterMinmaxPropertiesEXT
      .filterMinmaxImageComponentMapping = filterMinmaxImageComponentMapping;
  return PhysicalDeviceSamplerFilterMinmaxPropertiesEXT;
}

inline VkPhysicalDeviceInlineUniformBlockFeaturesEXT
vkiPhysicalDeviceInlineUniformBlockFeaturesEXT(
    VkBool32 inlineUniformBlock,
    VkBool32 descriptorBindingInlineUniformBlockUpdateAfterBind) {
  VkPhysicalDeviceInlineUniformBlockFeaturesEXT
      PhysicalDeviceInlineUniformBlockFeaturesEXT = {};
  PhysicalDeviceInlineUniformBlockFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT;
  PhysicalDeviceInlineUniformBlockFeaturesEXT.pNext = nullptr;
  PhysicalDeviceInlineUniformBlockFeaturesEXT.inlineUniformBlock =
      inlineUniformBlock;
  PhysicalDeviceInlineUniformBlockFeaturesEXT
      .descriptorBindingInlineUniformBlockUpdateAfterBind =
      descriptorBindingInlineUniformBlockUpdateAfterBind;
  return PhysicalDeviceInlineUniformBlockFeaturesEXT;
}

inline VkPhysicalDeviceInlineUniformBlockPropertiesEXT
vkiPhysicalDeviceInlineUniformBlockPropertiesEXT(
    uint32_t maxInlineUniformBlockSize,
    uint32_t maxPerStageDescriptorInlineUniformBlocks,
    uint32_t maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks,
    uint32_t maxDescriptorSetInlineUniformBlocks,
    uint32_t maxDescriptorSetUpdateAfterBindInlineUniformBlocks) {
  VkPhysicalDeviceInlineUniformBlockPropertiesEXT
      PhysicalDeviceInlineUniformBlockPropertiesEXT = {};
  PhysicalDeviceInlineUniformBlockPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES_EXT;
  PhysicalDeviceInlineUniformBlockPropertiesEXT.pNext = nullptr;
  PhysicalDeviceInlineUniformBlockPropertiesEXT.maxInlineUniformBlockSize =
      maxInlineUniformBlockSize;
  PhysicalDeviceInlineUniformBlockPropertiesEXT
      .maxPerStageDescriptorInlineUniformBlocks =
      maxPerStageDescriptorInlineUniformBlocks;
  PhysicalDeviceInlineUniformBlockPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks =
      maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
  PhysicalDeviceInlineUniformBlockPropertiesEXT
      .maxDescriptorSetInlineUniformBlocks =
      maxDescriptorSetInlineUniformBlocks;
  PhysicalDeviceInlineUniformBlockPropertiesEXT
      .maxDescriptorSetUpdateAfterBindInlineUniformBlocks =
      maxDescriptorSetUpdateAfterBindInlineUniformBlocks;
  return PhysicalDeviceInlineUniformBlockPropertiesEXT;
}

inline VkWriteDescriptorSetInlineUniformBlockEXT
vkiWriteDescriptorSetInlineUniformBlockEXT(uint32_t dataSize,
                                           const void* pData) {
  VkWriteDescriptorSetInlineUniformBlockEXT
      WriteDescriptorSetInlineUniformBlockEXT = {};
  WriteDescriptorSetInlineUniformBlockEXT.sType =
      VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT;
  WriteDescriptorSetInlineUniformBlockEXT.pNext = nullptr;
  WriteDescriptorSetInlineUniformBlockEXT.dataSize = dataSize;
  WriteDescriptorSetInlineUniformBlockEXT.pData = pData;
  return WriteDescriptorSetInlineUniformBlockEXT;
}

inline VkDescriptorPoolInlineUniformBlockCreateInfoEXT
vkiDescriptorPoolInlineUniformBlockCreateInfoEXT(
    uint32_t maxInlineUniformBlockBindings) {
  VkDescriptorPoolInlineUniformBlockCreateInfoEXT
      DescriptorPoolInlineUniformBlockCreateInfoEXT = {};
  DescriptorPoolInlineUniformBlockCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT;
  DescriptorPoolInlineUniformBlockCreateInfoEXT.pNext = nullptr;
  DescriptorPoolInlineUniformBlockCreateInfoEXT.maxInlineUniformBlockBindings =
      maxInlineUniformBlockBindings;
  return DescriptorPoolInlineUniformBlockCreateInfoEXT;
}

inline VkSampleLocationEXT vkiSampleLocationEXT(float x, float y) {
  VkSampleLocationEXT SampleLocationEXT = {};
  SampleLocationEXT.x = x;
  SampleLocationEXT.y = y;
  return SampleLocationEXT;
}

inline VkSampleLocationsInfoEXT vkiSampleLocationsInfoEXT(
    VkSampleCountFlagBits sampleLocationsPerPixel,
    VkExtent2D sampleLocationGridSize, uint32_t sampleLocationsCount,
    const VkSampleLocationEXT* pSampleLocations) {
  VkSampleLocationsInfoEXT SampleLocationsInfoEXT = {};
  SampleLocationsInfoEXT.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
  SampleLocationsInfoEXT.pNext = nullptr;
  SampleLocationsInfoEXT.sampleLocationsPerPixel = sampleLocationsPerPixel;
  SampleLocationsInfoEXT.sampleLocationGridSize = sampleLocationGridSize;
  SampleLocationsInfoEXT.sampleLocationsCount = sampleLocationsCount;
  SampleLocationsInfoEXT.pSampleLocations = pSampleLocations;
  return SampleLocationsInfoEXT;
}

inline VkAttachmentSampleLocationsEXT vkiAttachmentSampleLocationsEXT(
    uint32_t attachmentIndex, VkSampleLocationsInfoEXT sampleLocationsInfo) {
  VkAttachmentSampleLocationsEXT AttachmentSampleLocationsEXT = {};
  AttachmentSampleLocationsEXT.attachmentIndex = attachmentIndex;
  AttachmentSampleLocationsEXT.sampleLocationsInfo = sampleLocationsInfo;
  return AttachmentSampleLocationsEXT;
}

inline VkSubpassSampleLocationsEXT vkiSubpassSampleLocationsEXT(
    uint32_t subpassIndex, VkSampleLocationsInfoEXT sampleLocationsInfo) {
  VkSubpassSampleLocationsEXT SubpassSampleLocationsEXT = {};
  SubpassSampleLocationsEXT.subpassIndex = subpassIndex;
  SubpassSampleLocationsEXT.sampleLocationsInfo = sampleLocationsInfo;
  return SubpassSampleLocationsEXT;
}

inline VkRenderPassSampleLocationsBeginInfoEXT
vkiRenderPassSampleLocationsBeginInfoEXT(
    uint32_t attachmentInitialSampleLocationsCount,
    const VkAttachmentSampleLocationsEXT* pAttachmentInitialSampleLocations,
    uint32_t postSubpassSampleLocationsCount,
    const VkSubpassSampleLocationsEXT* pPostSubpassSampleLocations) {
  VkRenderPassSampleLocationsBeginInfoEXT
      RenderPassSampleLocationsBeginInfoEXT = {};
  RenderPassSampleLocationsBeginInfoEXT.sType =
      VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT;
  RenderPassSampleLocationsBeginInfoEXT.pNext = nullptr;
  RenderPassSampleLocationsBeginInfoEXT.attachmentInitialSampleLocationsCount =
      attachmentInitialSampleLocationsCount;
  RenderPassSampleLocationsBeginInfoEXT.pAttachmentInitialSampleLocations =
      pAttachmentInitialSampleLocations;
  RenderPassSampleLocationsBeginInfoEXT.postSubpassSampleLocationsCount =
      postSubpassSampleLocationsCount;
  RenderPassSampleLocationsBeginInfoEXT.pPostSubpassSampleLocations =
      pPostSubpassSampleLocations;
  return RenderPassSampleLocationsBeginInfoEXT;
}

inline VkPipelineSampleLocationsStateCreateInfoEXT
vkiPipelineSampleLocationsStateCreateInfoEXT(
    VkBool32 sampleLocationsEnable,
    VkSampleLocationsInfoEXT sampleLocationsInfo) {
  VkPipelineSampleLocationsStateCreateInfoEXT
      PipelineSampleLocationsStateCreateInfoEXT = {};
  PipelineSampleLocationsStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT;
  PipelineSampleLocationsStateCreateInfoEXT.pNext = nullptr;
  PipelineSampleLocationsStateCreateInfoEXT.sampleLocationsEnable =
      sampleLocationsEnable;
  PipelineSampleLocationsStateCreateInfoEXT.sampleLocationsInfo =
      sampleLocationsInfo;
  return PipelineSampleLocationsStateCreateInfoEXT;
}

// inline VkPhysicalDeviceSampleLocationsPropertiesEXT
// vkiPhysicalDeviceSampleLocationsPropertiesEXT(VkSampleCountFlags
// sampleLocationSampleCounts, VkExtent2D maxSampleLocationGridSize, float
// sampleLocationCoordinateRange[2], uint32_t sampleLocationSubPixelBits,
// VkBool32 variableSampleLocations) {
//     VkPhysicalDeviceSampleLocationsPropertiesEXT
//     PhysicalDeviceSampleLocationsPropertiesEXT = {};
//     PhysicalDeviceSampleLocationsPropertiesEXT.sType =
//     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
//     PhysicalDeviceSampleLocationsPropertiesEXT.pNext = nullptr;
//     PhysicalDeviceSampleLocationsPropertiesEXT.sampleLocationSampleCounts =
//     sampleLocationSampleCounts;
//     PhysicalDeviceSampleLocationsPropertiesEXT.maxSampleLocationGridSize =
//     maxSampleLocationGridSize;
//     PhysicalDeviceSampleLocationsPropertiesEXT.sampleLocationCoordinateRange[2]
//     = sampleLocationCoordinateRange[2];
//     PhysicalDeviceSampleLocationsPropertiesEXT.sampleLocationSubPixelBits =
//     sampleLocationSubPixelBits;
//     PhysicalDeviceSampleLocationsPropertiesEXT.variableSampleLocations =
//     variableSampleLocations; return
//     PhysicalDeviceSampleLocationsPropertiesEXT;
// }

inline VkMultisamplePropertiesEXT vkiMultisamplePropertiesEXT(
    VkExtent2D maxSampleLocationGridSize) {
  VkMultisamplePropertiesEXT MultisamplePropertiesEXT = {};
  MultisamplePropertiesEXT.sType = VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT;
  MultisamplePropertiesEXT.pNext = nullptr;
  MultisamplePropertiesEXT.maxSampleLocationGridSize =
      maxSampleLocationGridSize;
  return MultisamplePropertiesEXT;
}

inline VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT
vkiPhysicalDeviceBlendOperationAdvancedFeaturesEXT(
    VkBool32 advancedBlendCoherentOperations) {
  VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT
      PhysicalDeviceBlendOperationAdvancedFeaturesEXT = {};
  PhysicalDeviceBlendOperationAdvancedFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
  PhysicalDeviceBlendOperationAdvancedFeaturesEXT.pNext = nullptr;
  PhysicalDeviceBlendOperationAdvancedFeaturesEXT
      .advancedBlendCoherentOperations = advancedBlendCoherentOperations;
  return PhysicalDeviceBlendOperationAdvancedFeaturesEXT;
}

inline VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT
vkiPhysicalDeviceBlendOperationAdvancedPropertiesEXT(
    uint32_t advancedBlendMaxColorAttachments,
    VkBool32 advancedBlendIndependentBlend,
    VkBool32 advancedBlendNonPremultipliedSrcColor,
    VkBool32 advancedBlendNonPremultipliedDstColor,
    VkBool32 advancedBlendCorrelatedOverlap,
    VkBool32 advancedBlendAllOperations) {
  VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT
      PhysicalDeviceBlendOperationAdvancedPropertiesEXT = {};
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT.pNext = nullptr;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT
      .advancedBlendMaxColorAttachments = advancedBlendMaxColorAttachments;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT
      .advancedBlendIndependentBlend = advancedBlendIndependentBlend;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT
      .advancedBlendNonPremultipliedSrcColor =
      advancedBlendNonPremultipliedSrcColor;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT
      .advancedBlendNonPremultipliedDstColor =
      advancedBlendNonPremultipliedDstColor;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT
      .advancedBlendCorrelatedOverlap = advancedBlendCorrelatedOverlap;
  PhysicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendAllOperations =
      advancedBlendAllOperations;
  return PhysicalDeviceBlendOperationAdvancedPropertiesEXT;
}

inline VkPipelineColorBlendAdvancedStateCreateInfoEXT
vkiPipelineColorBlendAdvancedStateCreateInfoEXT(
    VkBool32 srcPremultiplied, VkBool32 dstPremultiplied,
    VkBlendOverlapEXT blendOverlap) {
  VkPipelineColorBlendAdvancedStateCreateInfoEXT
      PipelineColorBlendAdvancedStateCreateInfoEXT = {};
  PipelineColorBlendAdvancedStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT;
  PipelineColorBlendAdvancedStateCreateInfoEXT.pNext = nullptr;
  PipelineColorBlendAdvancedStateCreateInfoEXT.srcPremultiplied =
      srcPremultiplied;
  PipelineColorBlendAdvancedStateCreateInfoEXT.dstPremultiplied =
      dstPremultiplied;
  PipelineColorBlendAdvancedStateCreateInfoEXT.blendOverlap = blendOverlap;
  return PipelineColorBlendAdvancedStateCreateInfoEXT;
}

inline VkPipelineCoverageToColorStateCreateInfoNV
vkiPipelineCoverageToColorStateCreateInfoNV(VkBool32 coverageToColorEnable,
                                            uint32_t coverageToColorLocation) {
  VkPipelineCoverageToColorStateCreateInfoNV
      PipelineCoverageToColorStateCreateInfoNV = {};
  PipelineCoverageToColorStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV;
  PipelineCoverageToColorStateCreateInfoNV.pNext = nullptr;
  PipelineCoverageToColorStateCreateInfoNV.flags = 0;
  PipelineCoverageToColorStateCreateInfoNV.coverageToColorEnable =
      coverageToColorEnable;
  PipelineCoverageToColorStateCreateInfoNV.coverageToColorLocation =
      coverageToColorLocation;
  return PipelineCoverageToColorStateCreateInfoNV;
}

inline VkPipelineCoverageModulationStateCreateInfoNV
vkiPipelineCoverageModulationStateCreateInfoNV(
    VkCoverageModulationModeNV coverageModulationMode,
    VkBool32 coverageModulationTableEnable,
    uint32_t coverageModulationTableCount,
    const float* pCoverageModulationTable) {
  VkPipelineCoverageModulationStateCreateInfoNV
      PipelineCoverageModulationStateCreateInfoNV = {};
  PipelineCoverageModulationStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV;
  PipelineCoverageModulationStateCreateInfoNV.pNext = nullptr;
  PipelineCoverageModulationStateCreateInfoNV.flags = 0;
  PipelineCoverageModulationStateCreateInfoNV.coverageModulationMode =
      coverageModulationMode;
  PipelineCoverageModulationStateCreateInfoNV.coverageModulationTableEnable =
      coverageModulationTableEnable;
  PipelineCoverageModulationStateCreateInfoNV.coverageModulationTableCount =
      coverageModulationTableCount;
  PipelineCoverageModulationStateCreateInfoNV.pCoverageModulationTable =
      pCoverageModulationTable;
  return PipelineCoverageModulationStateCreateInfoNV;
}

inline VkPhysicalDeviceShaderSMBuiltinsPropertiesNV
vkiPhysicalDeviceShaderSMBuiltinsPropertiesNV(uint32_t shaderSMCount,
                                              uint32_t shaderWarpsPerSM) {
  VkPhysicalDeviceShaderSMBuiltinsPropertiesNV
      PhysicalDeviceShaderSMBuiltinsPropertiesNV = {};
  PhysicalDeviceShaderSMBuiltinsPropertiesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV;
  PhysicalDeviceShaderSMBuiltinsPropertiesNV.pNext = nullptr;
  PhysicalDeviceShaderSMBuiltinsPropertiesNV.shaderSMCount = shaderSMCount;
  PhysicalDeviceShaderSMBuiltinsPropertiesNV.shaderWarpsPerSM =
      shaderWarpsPerSM;
  return PhysicalDeviceShaderSMBuiltinsPropertiesNV;
}

inline VkPhysicalDeviceShaderSMBuiltinsFeaturesNV
vkiPhysicalDeviceShaderSMBuiltinsFeaturesNV(VkBool32 shaderSMBuiltins) {
  VkPhysicalDeviceShaderSMBuiltinsFeaturesNV
      PhysicalDeviceShaderSMBuiltinsFeaturesNV = {};
  PhysicalDeviceShaderSMBuiltinsFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
  PhysicalDeviceShaderSMBuiltinsFeaturesNV.pNext = nullptr;
  PhysicalDeviceShaderSMBuiltinsFeaturesNV.shaderSMBuiltins = shaderSMBuiltins;
  return PhysicalDeviceShaderSMBuiltinsFeaturesNV;
}

inline VkDrmFormatModifierPropertiesEXT vkiDrmFormatModifierPropertiesEXT(
    uint64_t drmFormatModifier, uint32_t drmFormatModifierPlaneCount,
    VkFormatFeatureFlags drmFormatModifierTilingFeatures) {
  VkDrmFormatModifierPropertiesEXT DrmFormatModifierPropertiesEXT = {};
  DrmFormatModifierPropertiesEXT.drmFormatModifier = drmFormatModifier;
  DrmFormatModifierPropertiesEXT.drmFormatModifierPlaneCount =
      drmFormatModifierPlaneCount;
  DrmFormatModifierPropertiesEXT.drmFormatModifierTilingFeatures =
      drmFormatModifierTilingFeatures;
  return DrmFormatModifierPropertiesEXT;
}

inline VkDrmFormatModifierPropertiesListEXT
vkiDrmFormatModifierPropertiesListEXT(
    uint32_t drmFormatModifierCount,
    VkDrmFormatModifierPropertiesEXT* pDrmFormatModifierProperties) {
  VkDrmFormatModifierPropertiesListEXT DrmFormatModifierPropertiesListEXT = {};
  DrmFormatModifierPropertiesListEXT.sType =
      VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT;
  DrmFormatModifierPropertiesListEXT.pNext = nullptr;
  DrmFormatModifierPropertiesListEXT.drmFormatModifierCount =
      drmFormatModifierCount;
  DrmFormatModifierPropertiesListEXT.pDrmFormatModifierProperties =
      pDrmFormatModifierProperties;
  return DrmFormatModifierPropertiesListEXT;
}

inline VkPhysicalDeviceImageDrmFormatModifierInfoEXT
vkiPhysicalDeviceImageDrmFormatModifierInfoEXT(
    uint64_t drmFormatModifier, VkSharingMode sharingMode,
    uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices) {
  VkPhysicalDeviceImageDrmFormatModifierInfoEXT
      PhysicalDeviceImageDrmFormatModifierInfoEXT = {};
  PhysicalDeviceImageDrmFormatModifierInfoEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT;
  PhysicalDeviceImageDrmFormatModifierInfoEXT.pNext = nullptr;
  PhysicalDeviceImageDrmFormatModifierInfoEXT.drmFormatModifier =
      drmFormatModifier;
  PhysicalDeviceImageDrmFormatModifierInfoEXT.sharingMode = sharingMode;
  PhysicalDeviceImageDrmFormatModifierInfoEXT.queueFamilyIndexCount =
      queueFamilyIndexCount;
  PhysicalDeviceImageDrmFormatModifierInfoEXT.pQueueFamilyIndices =
      pQueueFamilyIndices;
  return PhysicalDeviceImageDrmFormatModifierInfoEXT;
}

inline VkImageDrmFormatModifierListCreateInfoEXT
vkiImageDrmFormatModifierListCreateInfoEXT(
    uint32_t drmFormatModifierCount, const uint64_t* pDrmFormatModifiers) {
  VkImageDrmFormatModifierListCreateInfoEXT
      ImageDrmFormatModifierListCreateInfoEXT = {};
  ImageDrmFormatModifierListCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT;
  ImageDrmFormatModifierListCreateInfoEXT.pNext = nullptr;
  ImageDrmFormatModifierListCreateInfoEXT.drmFormatModifierCount =
      drmFormatModifierCount;
  ImageDrmFormatModifierListCreateInfoEXT.pDrmFormatModifiers =
      pDrmFormatModifiers;
  return ImageDrmFormatModifierListCreateInfoEXT;
}

inline VkImageDrmFormatModifierExplicitCreateInfoEXT
vkiImageDrmFormatModifierExplicitCreateInfoEXT(
    uint64_t drmFormatModifier, uint32_t drmFormatModifierPlaneCount,
    const VkSubresourceLayout* pPlaneLayouts) {
  VkImageDrmFormatModifierExplicitCreateInfoEXT
      ImageDrmFormatModifierExplicitCreateInfoEXT = {};
  ImageDrmFormatModifierExplicitCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT;
  ImageDrmFormatModifierExplicitCreateInfoEXT.pNext = nullptr;
  ImageDrmFormatModifierExplicitCreateInfoEXT.drmFormatModifier =
      drmFormatModifier;
  ImageDrmFormatModifierExplicitCreateInfoEXT.drmFormatModifierPlaneCount =
      drmFormatModifierPlaneCount;
  ImageDrmFormatModifierExplicitCreateInfoEXT.pPlaneLayouts = pPlaneLayouts;
  return ImageDrmFormatModifierExplicitCreateInfoEXT;
}

inline VkImageDrmFormatModifierPropertiesEXT
vkiImageDrmFormatModifierPropertiesEXT(uint64_t drmFormatModifier) {
  VkImageDrmFormatModifierPropertiesEXT ImageDrmFormatModifierPropertiesEXT =
      {};
  ImageDrmFormatModifierPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT;
  ImageDrmFormatModifierPropertiesEXT.pNext = nullptr;
  ImageDrmFormatModifierPropertiesEXT.drmFormatModifier = drmFormatModifier;
  return ImageDrmFormatModifierPropertiesEXT;
}

inline VkValidationCacheCreateInfoEXT vkiValidationCacheCreateInfoEXT(
    size_t initialDataSize, const void* pInitialData) {
  VkValidationCacheCreateInfoEXT ValidationCacheCreateInfoEXT = {};
  ValidationCacheCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT;
  ValidationCacheCreateInfoEXT.pNext = nullptr;
  ValidationCacheCreateInfoEXT.flags = 0;
  ValidationCacheCreateInfoEXT.initialDataSize = initialDataSize;
  ValidationCacheCreateInfoEXT.pInitialData = pInitialData;
  return ValidationCacheCreateInfoEXT;
}

inline VkShaderModuleValidationCacheCreateInfoEXT
vkiShaderModuleValidationCacheCreateInfoEXT(
    VkValidationCacheEXT validationCache) {
  VkShaderModuleValidationCacheCreateInfoEXT
      ShaderModuleValidationCacheCreateInfoEXT = {};
  ShaderModuleValidationCacheCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
  ShaderModuleValidationCacheCreateInfoEXT.pNext = nullptr;
  ShaderModuleValidationCacheCreateInfoEXT.validationCache = validationCache;
  return ShaderModuleValidationCacheCreateInfoEXT;
}

inline VkDescriptorSetLayoutBindingFlagsCreateInfoEXT
vkiDescriptorSetLayoutBindingFlagsCreateInfoEXT(
    uint32_t bindingCount, const VkDescriptorBindingFlagsEXT* pBindingFlags) {
  VkDescriptorSetLayoutBindingFlagsCreateInfoEXT
      DescriptorSetLayoutBindingFlagsCreateInfoEXT = {};
  DescriptorSetLayoutBindingFlagsCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
  DescriptorSetLayoutBindingFlagsCreateInfoEXT.pNext = nullptr;
  DescriptorSetLayoutBindingFlagsCreateInfoEXT.bindingCount = bindingCount;
  DescriptorSetLayoutBindingFlagsCreateInfoEXT.pBindingFlags = pBindingFlags;
  return DescriptorSetLayoutBindingFlagsCreateInfoEXT;
}

inline VkPhysicalDeviceDescriptorIndexingFeaturesEXT
vkiPhysicalDeviceDescriptorIndexingFeaturesEXT(
    VkBool32 shaderInputAttachmentArrayDynamicIndexing,
    VkBool32 shaderUniformTexelBufferArrayDynamicIndexing,
    VkBool32 shaderStorageTexelBufferArrayDynamicIndexing,
    VkBool32 shaderUniformBufferArrayNonUniformIndexing,
    VkBool32 shaderSampledImageArrayNonUniformIndexing,
    VkBool32 shaderStorageBufferArrayNonUniformIndexing,
    VkBool32 shaderStorageImageArrayNonUniformIndexing,
    VkBool32 shaderInputAttachmentArrayNonUniformIndexing,
    VkBool32 shaderUniformTexelBufferArrayNonUniformIndexing,
    VkBool32 shaderStorageTexelBufferArrayNonUniformIndexing,
    VkBool32 descriptorBindingUniformBufferUpdateAfterBind,
    VkBool32 descriptorBindingSampledImageUpdateAfterBind,
    VkBool32 descriptorBindingStorageImageUpdateAfterBind,
    VkBool32 descriptorBindingStorageBufferUpdateAfterBind,
    VkBool32 descriptorBindingUniformTexelBufferUpdateAfterBind,
    VkBool32 descriptorBindingStorageTexelBufferUpdateAfterBind,
    VkBool32 descriptorBindingUpdateUnusedWhilePending,
    VkBool32 descriptorBindingPartiallyBound,
    VkBool32 descriptorBindingVariableDescriptorCount,
    VkBool32 runtimeDescriptorArray) {
  VkPhysicalDeviceDescriptorIndexingFeaturesEXT
      PhysicalDeviceDescriptorIndexingFeaturesEXT = {};
  PhysicalDeviceDescriptorIndexingFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
  PhysicalDeviceDescriptorIndexingFeaturesEXT.pNext = nullptr;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderInputAttachmentArrayDynamicIndexing =
      shaderInputAttachmentArrayDynamicIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderUniformTexelBufferArrayDynamicIndexing =
      shaderUniformTexelBufferArrayDynamicIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderStorageTexelBufferArrayDynamicIndexing =
      shaderStorageTexelBufferArrayDynamicIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderUniformBufferArrayNonUniformIndexing =
      shaderUniformBufferArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderSampledImageArrayNonUniformIndexing =
      shaderSampledImageArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderStorageBufferArrayNonUniformIndexing =
      shaderStorageBufferArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderStorageImageArrayNonUniformIndexing =
      shaderStorageImageArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderInputAttachmentArrayNonUniformIndexing =
      shaderInputAttachmentArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderUniformTexelBufferArrayNonUniformIndexing =
      shaderUniformTexelBufferArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .shaderStorageTexelBufferArrayNonUniformIndexing =
      shaderStorageTexelBufferArrayNonUniformIndexing;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingUniformBufferUpdateAfterBind =
      descriptorBindingUniformBufferUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingSampledImageUpdateAfterBind =
      descriptorBindingSampledImageUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingStorageImageUpdateAfterBind =
      descriptorBindingStorageImageUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingStorageBufferUpdateAfterBind =
      descriptorBindingStorageBufferUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingUniformTexelBufferUpdateAfterBind =
      descriptorBindingUniformTexelBufferUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingStorageTexelBufferUpdateAfterBind =
      descriptorBindingStorageTexelBufferUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingUpdateUnusedWhilePending =
      descriptorBindingUpdateUnusedWhilePending;
  PhysicalDeviceDescriptorIndexingFeaturesEXT.descriptorBindingPartiallyBound =
      descriptorBindingPartiallyBound;
  PhysicalDeviceDescriptorIndexingFeaturesEXT
      .descriptorBindingVariableDescriptorCount =
      descriptorBindingVariableDescriptorCount;
  PhysicalDeviceDescriptorIndexingFeaturesEXT.runtimeDescriptorArray =
      runtimeDescriptorArray;
  return PhysicalDeviceDescriptorIndexingFeaturesEXT;
}

inline VkPhysicalDeviceDescriptorIndexingPropertiesEXT
vkiPhysicalDeviceDescriptorIndexingPropertiesEXT(
    uint32_t maxUpdateAfterBindDescriptorsInAllPools,
    VkBool32 shaderUniformBufferArrayNonUniformIndexingNative,
    VkBool32 shaderSampledImageArrayNonUniformIndexingNative,
    VkBool32 shaderStorageBufferArrayNonUniformIndexingNative,
    VkBool32 shaderStorageImageArrayNonUniformIndexingNative,
    VkBool32 shaderInputAttachmentArrayNonUniformIndexingNative,
    VkBool32 robustBufferAccessUpdateAfterBind,
    VkBool32 quadDivergentImplicitLod,
    uint32_t maxPerStageDescriptorUpdateAfterBindSamplers,
    uint32_t maxPerStageDescriptorUpdateAfterBindUniformBuffers,
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageBuffers,
    uint32_t maxPerStageDescriptorUpdateAfterBindSampledImages,
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageImages,
    uint32_t maxPerStageDescriptorUpdateAfterBindInputAttachments,
    uint32_t maxPerStageUpdateAfterBindResources,
    uint32_t maxDescriptorSetUpdateAfterBindSamplers,
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffers,
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffersDynamic,
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffers,
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffersDynamic,
    uint32_t maxDescriptorSetUpdateAfterBindSampledImages,
    uint32_t maxDescriptorSetUpdateAfterBindStorageImages,
    uint32_t maxDescriptorSetUpdateAfterBindInputAttachments) {
  VkPhysicalDeviceDescriptorIndexingPropertiesEXT
      PhysicalDeviceDescriptorIndexingPropertiesEXT = {};
  PhysicalDeviceDescriptorIndexingPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES_EXT;
  PhysicalDeviceDescriptorIndexingPropertiesEXT.pNext = nullptr;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxUpdateAfterBindDescriptorsInAllPools =
      maxUpdateAfterBindDescriptorsInAllPools;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .shaderUniformBufferArrayNonUniformIndexingNative =
      shaderUniformBufferArrayNonUniformIndexingNative;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .shaderSampledImageArrayNonUniformIndexingNative =
      shaderSampledImageArrayNonUniformIndexingNative;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .shaderStorageBufferArrayNonUniformIndexingNative =
      shaderStorageBufferArrayNonUniformIndexingNative;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .shaderStorageImageArrayNonUniformIndexingNative =
      shaderStorageImageArrayNonUniformIndexingNative;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .shaderInputAttachmentArrayNonUniformIndexingNative =
      shaderInputAttachmentArrayNonUniformIndexingNative;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .robustBufferAccessUpdateAfterBind = robustBufferAccessUpdateAfterBind;
  PhysicalDeviceDescriptorIndexingPropertiesEXT.quadDivergentImplicitLod =
      quadDivergentImplicitLod;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindSamplers =
      maxPerStageDescriptorUpdateAfterBindSamplers;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindUniformBuffers =
      maxPerStageDescriptorUpdateAfterBindUniformBuffers;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindStorageBuffers =
      maxPerStageDescriptorUpdateAfterBindStorageBuffers;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindSampledImages =
      maxPerStageDescriptorUpdateAfterBindSampledImages;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindStorageImages =
      maxPerStageDescriptorUpdateAfterBindStorageImages;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageDescriptorUpdateAfterBindInputAttachments =
      maxPerStageDescriptorUpdateAfterBindInputAttachments;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxPerStageUpdateAfterBindResources =
      maxPerStageUpdateAfterBindResources;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindSamplers =
      maxDescriptorSetUpdateAfterBindSamplers;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindUniformBuffers =
      maxDescriptorSetUpdateAfterBindUniformBuffers;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindUniformBuffersDynamic =
      maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindStorageBuffers =
      maxDescriptorSetUpdateAfterBindStorageBuffers;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindStorageBuffersDynamic =
      maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindSampledImages =
      maxDescriptorSetUpdateAfterBindSampledImages;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindStorageImages =
      maxDescriptorSetUpdateAfterBindStorageImages;
  PhysicalDeviceDescriptorIndexingPropertiesEXT
      .maxDescriptorSetUpdateAfterBindInputAttachments =
      maxDescriptorSetUpdateAfterBindInputAttachments;
  return PhysicalDeviceDescriptorIndexingPropertiesEXT;
}

inline VkDescriptorSetVariableDescriptorCountAllocateInfoEXT
vkiDescriptorSetVariableDescriptorCountAllocateInfoEXT(
    uint32_t descriptorSetCount, const uint32_t* pDescriptorCounts) {
  VkDescriptorSetVariableDescriptorCountAllocateInfoEXT
      DescriptorSetVariableDescriptorCountAllocateInfoEXT = {};
  DescriptorSetVariableDescriptorCountAllocateInfoEXT.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
  DescriptorSetVariableDescriptorCountAllocateInfoEXT.pNext = nullptr;
  DescriptorSetVariableDescriptorCountAllocateInfoEXT.descriptorSetCount =
      descriptorSetCount;
  DescriptorSetVariableDescriptorCountAllocateInfoEXT.pDescriptorCounts =
      pDescriptorCounts;
  return DescriptorSetVariableDescriptorCountAllocateInfoEXT;
}

inline VkDescriptorSetVariableDescriptorCountLayoutSupportEXT
vkiDescriptorSetVariableDescriptorCountLayoutSupportEXT(
    uint32_t maxVariableDescriptorCount) {
  VkDescriptorSetVariableDescriptorCountLayoutSupportEXT
      DescriptorSetVariableDescriptorCountLayoutSupportEXT = {};
  DescriptorSetVariableDescriptorCountLayoutSupportEXT.sType =
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT_EXT;
  DescriptorSetVariableDescriptorCountLayoutSupportEXT.pNext = nullptr;
  DescriptorSetVariableDescriptorCountLayoutSupportEXT
      .maxVariableDescriptorCount = maxVariableDescriptorCount;
  return DescriptorSetVariableDescriptorCountLayoutSupportEXT;
}

inline VkShadingRatePaletteNV vkiShadingRatePaletteNV(
    uint32_t shadingRatePaletteEntryCount,
    const VkShadingRatePaletteEntryNV* pShadingRatePaletteEntries) {
  VkShadingRatePaletteNV ShadingRatePaletteNV = {};
  ShadingRatePaletteNV.shadingRatePaletteEntryCount =
      shadingRatePaletteEntryCount;
  ShadingRatePaletteNV.pShadingRatePaletteEntries = pShadingRatePaletteEntries;
  return ShadingRatePaletteNV;
}

inline VkPipelineViewportShadingRateImageStateCreateInfoNV
vkiPipelineViewportShadingRateImageStateCreateInfoNV(
    VkBool32 shadingRateImageEnable, uint32_t viewportCount,
    const VkShadingRatePaletteNV* pShadingRatePalettes) {
  VkPipelineViewportShadingRateImageStateCreateInfoNV
      PipelineViewportShadingRateImageStateCreateInfoNV = {};
  PipelineViewportShadingRateImageStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV;
  PipelineViewportShadingRateImageStateCreateInfoNV.pNext = nullptr;
  PipelineViewportShadingRateImageStateCreateInfoNV.shadingRateImageEnable =
      shadingRateImageEnable;
  PipelineViewportShadingRateImageStateCreateInfoNV.viewportCount =
      viewportCount;
  PipelineViewportShadingRateImageStateCreateInfoNV.pShadingRatePalettes =
      pShadingRatePalettes;
  return PipelineViewportShadingRateImageStateCreateInfoNV;
}

inline VkPhysicalDeviceShadingRateImageFeaturesNV
vkiPhysicalDeviceShadingRateImageFeaturesNV(
    VkBool32 shadingRateImage, VkBool32 shadingRateCoarseSampleOrder) {
  VkPhysicalDeviceShadingRateImageFeaturesNV
      PhysicalDeviceShadingRateImageFeaturesNV = {};
  PhysicalDeviceShadingRateImageFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
  PhysicalDeviceShadingRateImageFeaturesNV.pNext = nullptr;
  PhysicalDeviceShadingRateImageFeaturesNV.shadingRateImage = shadingRateImage;
  PhysicalDeviceShadingRateImageFeaturesNV.shadingRateCoarseSampleOrder =
      shadingRateCoarseSampleOrder;
  return PhysicalDeviceShadingRateImageFeaturesNV;
}

inline VkPhysicalDeviceShadingRateImagePropertiesNV
vkiPhysicalDeviceShadingRateImagePropertiesNV(
    VkExtent2D shadingRateTexelSize, uint32_t shadingRatePaletteSize,
    uint32_t shadingRateMaxCoarseSamples) {
  VkPhysicalDeviceShadingRateImagePropertiesNV
      PhysicalDeviceShadingRateImagePropertiesNV = {};
  PhysicalDeviceShadingRateImagePropertiesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV;
  PhysicalDeviceShadingRateImagePropertiesNV.pNext = nullptr;
  PhysicalDeviceShadingRateImagePropertiesNV.shadingRateTexelSize =
      shadingRateTexelSize;
  PhysicalDeviceShadingRateImagePropertiesNV.shadingRatePaletteSize =
      shadingRatePaletteSize;
  PhysicalDeviceShadingRateImagePropertiesNV.shadingRateMaxCoarseSamples =
      shadingRateMaxCoarseSamples;
  return PhysicalDeviceShadingRateImagePropertiesNV;
}

inline VkCoarseSampleLocationNV vkiCoarseSampleLocationNV(uint32_t pixelX,
                                                          uint32_t pixelY,
                                                          uint32_t sample) {
  VkCoarseSampleLocationNV CoarseSampleLocationNV = {};
  CoarseSampleLocationNV.pixelX = pixelX;
  CoarseSampleLocationNV.pixelY = pixelY;
  CoarseSampleLocationNV.sample = sample;
  return CoarseSampleLocationNV;
}

inline VkCoarseSampleOrderCustomNV vkiCoarseSampleOrderCustomNV(
    VkShadingRatePaletteEntryNV shadingRate, uint32_t sampleCount,
    uint32_t sampleLocationCount,
    const VkCoarseSampleLocationNV* pSampleLocations) {
  VkCoarseSampleOrderCustomNV CoarseSampleOrderCustomNV = {};
  CoarseSampleOrderCustomNV.shadingRate = shadingRate;
  CoarseSampleOrderCustomNV.sampleCount = sampleCount;
  CoarseSampleOrderCustomNV.sampleLocationCount = sampleLocationCount;
  CoarseSampleOrderCustomNV.pSampleLocations = pSampleLocations;
  return CoarseSampleOrderCustomNV;
}

inline VkPipelineViewportCoarseSampleOrderStateCreateInfoNV
vkiPipelineViewportCoarseSampleOrderStateCreateInfoNV(
    VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount,
    const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) {
  VkPipelineViewportCoarseSampleOrderStateCreateInfoNV
      PipelineViewportCoarseSampleOrderStateCreateInfoNV = {};
  PipelineViewportCoarseSampleOrderStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV;
  PipelineViewportCoarseSampleOrderStateCreateInfoNV.pNext = nullptr;
  PipelineViewportCoarseSampleOrderStateCreateInfoNV.sampleOrderType =
      sampleOrderType;
  PipelineViewportCoarseSampleOrderStateCreateInfoNV.customSampleOrderCount =
      customSampleOrderCount;
  PipelineViewportCoarseSampleOrderStateCreateInfoNV.pCustomSampleOrders =
      pCustomSampleOrders;
  return PipelineViewportCoarseSampleOrderStateCreateInfoNV;
}

inline VkRayTracingShaderGroupCreateInfoNV vkiRayTracingShaderGroupCreateInfoNV(
    VkRayTracingShaderGroupTypeNV type, uint32_t generalShader,
    uint32_t closestHitShader, uint32_t anyHitShader,
    uint32_t intersectionShader) {
  VkRayTracingShaderGroupCreateInfoNV RayTracingShaderGroupCreateInfoNV = {};
  RayTracingShaderGroupCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV;
  RayTracingShaderGroupCreateInfoNV.pNext = nullptr;
  RayTracingShaderGroupCreateInfoNV.type = type;
  RayTracingShaderGroupCreateInfoNV.generalShader = generalShader;
  RayTracingShaderGroupCreateInfoNV.closestHitShader = closestHitShader;
  RayTracingShaderGroupCreateInfoNV.anyHitShader = anyHitShader;
  RayTracingShaderGroupCreateInfoNV.intersectionShader = intersectionShader;
  return RayTracingShaderGroupCreateInfoNV;
}

inline VkRayTracingPipelineCreateInfoNV vkiRayTracingPipelineCreateInfoNV(
    uint32_t stageCount, const VkPipelineShaderStageCreateInfo* pStages,
    uint32_t groupCount, const VkRayTracingShaderGroupCreateInfoNV* pGroups,
    uint32_t maxRecursionDepth, VkPipelineLayout layout,
    VkPipeline basePipelineHandle, int32_t basePipelineIndex) {
  VkRayTracingPipelineCreateInfoNV RayTracingPipelineCreateInfoNV = {};
  RayTracingPipelineCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
  RayTracingPipelineCreateInfoNV.pNext = nullptr;
  RayTracingPipelineCreateInfoNV.flags = 0;
  RayTracingPipelineCreateInfoNV.stageCount = stageCount;
  RayTracingPipelineCreateInfoNV.pStages = pStages;
  RayTracingPipelineCreateInfoNV.groupCount = groupCount;
  RayTracingPipelineCreateInfoNV.pGroups = pGroups;
  RayTracingPipelineCreateInfoNV.maxRecursionDepth = maxRecursionDepth;
  RayTracingPipelineCreateInfoNV.layout = layout;
  RayTracingPipelineCreateInfoNV.basePipelineHandle = basePipelineHandle;
  RayTracingPipelineCreateInfoNV.basePipelineIndex = basePipelineIndex;
  return RayTracingPipelineCreateInfoNV;
}

inline VkGeometryTrianglesNV vkiGeometryTrianglesNV(
    VkBuffer vertexData, VkDeviceSize vertexOffset, uint32_t vertexCount,
    VkDeviceSize vertexStride, VkFormat vertexFormat, VkBuffer indexData,
    VkDeviceSize indexOffset, uint32_t indexCount, VkIndexType indexType,
    VkBuffer transformData, VkDeviceSize transformOffset) {
  VkGeometryTrianglesNV GeometryTrianglesNV = {};
  GeometryTrianglesNV.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
  GeometryTrianglesNV.pNext = nullptr;
  GeometryTrianglesNV.vertexData = vertexData;
  GeometryTrianglesNV.vertexOffset = vertexOffset;
  GeometryTrianglesNV.vertexCount = vertexCount;
  GeometryTrianglesNV.vertexStride = vertexStride;
  GeometryTrianglesNV.vertexFormat = vertexFormat;
  GeometryTrianglesNV.indexData = indexData;
  GeometryTrianglesNV.indexOffset = indexOffset;
  GeometryTrianglesNV.indexCount = indexCount;
  GeometryTrianglesNV.indexType = indexType;
  GeometryTrianglesNV.transformData = transformData;
  GeometryTrianglesNV.transformOffset = transformOffset;
  return GeometryTrianglesNV;
}

inline VkGeometryAABBNV vkiGeometryAABBNV(VkBuffer aabbData, uint32_t numAABBs,
                                          uint32_t stride,
                                          VkDeviceSize offset) {
  VkGeometryAABBNV GeometryAABBNV = {};
  GeometryAABBNV.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
  GeometryAABBNV.pNext = nullptr;
  GeometryAABBNV.aabbData = aabbData;
  GeometryAABBNV.numAABBs = numAABBs;
  GeometryAABBNV.stride = stride;
  GeometryAABBNV.offset = offset;
  return GeometryAABBNV;
}

inline VkGeometryDataNV vkiGeometryDataNV(VkGeometryTrianglesNV triangles,
                                          VkGeometryAABBNV aabbs) {
  VkGeometryDataNV GeometryDataNV = {};
  GeometryDataNV.triangles = triangles;
  GeometryDataNV.aabbs = aabbs;
  return GeometryDataNV;
}

inline VkGeometryNV vkiGeometryNV(VkGeometryTypeNV geometryType,
                                  VkGeometryDataNV geometry) {
  VkGeometryNV GeometryNV = {};
  GeometryNV.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
  GeometryNV.pNext = nullptr;
  GeometryNV.flags = 0;
  GeometryNV.geometryType = geometryType;
  GeometryNV.geometry = geometry;
  return GeometryNV;
}

inline VkAccelerationStructureInfoNV vkiAccelerationStructureInfoNV(
    VkAccelerationStructureTypeNV type, uint32_t instanceCount,
    uint32_t geometryCount, const VkGeometryNV* pGeometries) {
  VkAccelerationStructureInfoNV AccelerationStructureInfoNV = {};
  AccelerationStructureInfoNV.sType =
      VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
  AccelerationStructureInfoNV.pNext = nullptr;
  AccelerationStructureInfoNV.flags = 0;
  AccelerationStructureInfoNV.type = type;
  AccelerationStructureInfoNV.instanceCount = instanceCount;
  AccelerationStructureInfoNV.geometryCount = geometryCount;
  AccelerationStructureInfoNV.pGeometries = pGeometries;
  return AccelerationStructureInfoNV;
}

inline VkAccelerationStructureCreateInfoNV vkiAccelerationStructureCreateInfoNV(
    VkDeviceSize compactedSize, VkAccelerationStructureInfoNV info) {
  VkAccelerationStructureCreateInfoNV AccelerationStructureCreateInfoNV = {};
  AccelerationStructureCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
  AccelerationStructureCreateInfoNV.pNext = nullptr;
  AccelerationStructureCreateInfoNV.compactedSize = compactedSize;
  AccelerationStructureCreateInfoNV.info = info;
  return AccelerationStructureCreateInfoNV;
}

inline VkBindAccelerationStructureMemoryInfoNV
vkiBindAccelerationStructureMemoryInfoNV(
    VkAccelerationStructureNV accelerationStructure, VkDeviceMemory memory,
    VkDeviceSize memoryOffset, uint32_t deviceIndexCount,
    const uint32_t* pDeviceIndices) {
  VkBindAccelerationStructureMemoryInfoNV
      BindAccelerationStructureMemoryInfoNV = {};
  BindAccelerationStructureMemoryInfoNV.sType =
      VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
  BindAccelerationStructureMemoryInfoNV.pNext = nullptr;
  BindAccelerationStructureMemoryInfoNV.accelerationStructure =
      accelerationStructure;
  BindAccelerationStructureMemoryInfoNV.memory = memory;
  BindAccelerationStructureMemoryInfoNV.memoryOffset = memoryOffset;
  BindAccelerationStructureMemoryInfoNV.deviceIndexCount = deviceIndexCount;
  BindAccelerationStructureMemoryInfoNV.pDeviceIndices = pDeviceIndices;
  return BindAccelerationStructureMemoryInfoNV;
}

inline VkWriteDescriptorSetAccelerationStructureNV
vkiWriteDescriptorSetAccelerationStructureNV(
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureNV* pAccelerationStructures) {
  VkWriteDescriptorSetAccelerationStructureNV
      WriteDescriptorSetAccelerationStructureNV = {};
  WriteDescriptorSetAccelerationStructureNV.sType =
      VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV;
  WriteDescriptorSetAccelerationStructureNV.pNext = nullptr;
  WriteDescriptorSetAccelerationStructureNV.accelerationStructureCount =
      accelerationStructureCount;
  WriteDescriptorSetAccelerationStructureNV.pAccelerationStructures =
      pAccelerationStructures;
  return WriteDescriptorSetAccelerationStructureNV;
}

inline VkAccelerationStructureMemoryRequirementsInfoNV
vkiAccelerationStructureMemoryRequirementsInfoNV(
    VkAccelerationStructureMemoryRequirementsTypeNV type,
    VkAccelerationStructureNV accelerationStructure) {
  VkAccelerationStructureMemoryRequirementsInfoNV
      AccelerationStructureMemoryRequirementsInfoNV = {};
  AccelerationStructureMemoryRequirementsInfoNV.sType =
      VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
  AccelerationStructureMemoryRequirementsInfoNV.pNext = nullptr;
  AccelerationStructureMemoryRequirementsInfoNV.type = type;
  AccelerationStructureMemoryRequirementsInfoNV.accelerationStructure =
      accelerationStructure;
  return AccelerationStructureMemoryRequirementsInfoNV;
}

inline VkPhysicalDeviceRayTracingPropertiesNV
vkiPhysicalDeviceRayTracingPropertiesNV(
    uint32_t shaderGroupHandleSize, uint32_t maxRecursionDepth,
    uint32_t maxShaderGroupStride, uint32_t shaderGroupBaseAlignment,
    uint64_t maxGeometryCount, uint64_t maxInstanceCount,
    uint64_t maxTriangleCount,
    uint32_t maxDescriptorSetAccelerationStructures) {
  VkPhysicalDeviceRayTracingPropertiesNV PhysicalDeviceRayTracingPropertiesNV =
      {};
  PhysicalDeviceRayTracingPropertiesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
  PhysicalDeviceRayTracingPropertiesNV.pNext = nullptr;
  PhysicalDeviceRayTracingPropertiesNV.shaderGroupHandleSize =
      shaderGroupHandleSize;
  PhysicalDeviceRayTracingPropertiesNV.maxRecursionDepth = maxRecursionDepth;
  PhysicalDeviceRayTracingPropertiesNV.maxShaderGroupStride =
      maxShaderGroupStride;
  PhysicalDeviceRayTracingPropertiesNV.shaderGroupBaseAlignment =
      shaderGroupBaseAlignment;
  PhysicalDeviceRayTracingPropertiesNV.maxGeometryCount = maxGeometryCount;
  PhysicalDeviceRayTracingPropertiesNV.maxInstanceCount = maxInstanceCount;
  PhysicalDeviceRayTracingPropertiesNV.maxTriangleCount = maxTriangleCount;
  PhysicalDeviceRayTracingPropertiesNV.maxDescriptorSetAccelerationStructures =
      maxDescriptorSetAccelerationStructures;
  return PhysicalDeviceRayTracingPropertiesNV;
}

inline VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV
vkiPhysicalDeviceRepresentativeFragmentTestFeaturesNV(
    VkBool32 representativeFragmentTest) {
  VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV
      PhysicalDeviceRepresentativeFragmentTestFeaturesNV = {};
  PhysicalDeviceRepresentativeFragmentTestFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV;
  PhysicalDeviceRepresentativeFragmentTestFeaturesNV.pNext = nullptr;
  PhysicalDeviceRepresentativeFragmentTestFeaturesNV
      .representativeFragmentTest = representativeFragmentTest;
  return PhysicalDeviceRepresentativeFragmentTestFeaturesNV;
}

inline VkPipelineRepresentativeFragmentTestStateCreateInfoNV
vkiPipelineRepresentativeFragmentTestStateCreateInfoNV(
    VkBool32 representativeFragmentTestEnable) {
  VkPipelineRepresentativeFragmentTestStateCreateInfoNV
      PipelineRepresentativeFragmentTestStateCreateInfoNV = {};
  PipelineRepresentativeFragmentTestStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV;
  PipelineRepresentativeFragmentTestStateCreateInfoNV.pNext = nullptr;
  PipelineRepresentativeFragmentTestStateCreateInfoNV
      .representativeFragmentTestEnable = representativeFragmentTestEnable;
  return PipelineRepresentativeFragmentTestStateCreateInfoNV;
}

inline VkPhysicalDeviceImageViewImageFormatInfoEXT
vkiPhysicalDeviceImageViewImageFormatInfoEXT(VkImageViewType imageViewType) {
  VkPhysicalDeviceImageViewImageFormatInfoEXT
      PhysicalDeviceImageViewImageFormatInfoEXT = {};
  PhysicalDeviceImageViewImageFormatInfoEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT;
  PhysicalDeviceImageViewImageFormatInfoEXT.pNext = nullptr;
  PhysicalDeviceImageViewImageFormatInfoEXT.imageViewType = imageViewType;
  return PhysicalDeviceImageViewImageFormatInfoEXT;
}

inline VkFilterCubicImageViewImageFormatPropertiesEXT
vkiFilterCubicImageViewImageFormatPropertiesEXT(VkBool32 filterCubic,
                                                VkBool32 filterCubicMinmax) {
  VkFilterCubicImageViewImageFormatPropertiesEXT
      FilterCubicImageViewImageFormatPropertiesEXT = {};
  FilterCubicImageViewImageFormatPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT;
  FilterCubicImageViewImageFormatPropertiesEXT.pNext = nullptr;
  FilterCubicImageViewImageFormatPropertiesEXT.filterCubic = filterCubic;
  FilterCubicImageViewImageFormatPropertiesEXT.filterCubicMinmax =
      filterCubicMinmax;
  return FilterCubicImageViewImageFormatPropertiesEXT;
}

inline VkDeviceQueueGlobalPriorityCreateInfoEXT
vkiDeviceQueueGlobalPriorityCreateInfoEXT(
    VkQueueGlobalPriorityEXT globalPriority) {
  VkDeviceQueueGlobalPriorityCreateInfoEXT
      DeviceQueueGlobalPriorityCreateInfoEXT = {};
  DeviceQueueGlobalPriorityCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT;
  DeviceQueueGlobalPriorityCreateInfoEXT.pNext = nullptr;
  DeviceQueueGlobalPriorityCreateInfoEXT.globalPriority = globalPriority;
  return DeviceQueueGlobalPriorityCreateInfoEXT;
}

inline VkImportMemoryHostPointerInfoEXT vkiImportMemoryHostPointerInfoEXT(
    VkExternalMemoryHandleTypeFlagBits handleType, void* pHostPointer) {
  VkImportMemoryHostPointerInfoEXT ImportMemoryHostPointerInfoEXT = {};
  ImportMemoryHostPointerInfoEXT.sType =
      VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT;
  ImportMemoryHostPointerInfoEXT.pNext = nullptr;
  ImportMemoryHostPointerInfoEXT.handleType = handleType;
  ImportMemoryHostPointerInfoEXT.pHostPointer = pHostPointer;
  return ImportMemoryHostPointerInfoEXT;
}

inline VkMemoryHostPointerPropertiesEXT vkiMemoryHostPointerPropertiesEXT(
    uint32_t memoryTypeBits) {
  VkMemoryHostPointerPropertiesEXT MemoryHostPointerPropertiesEXT = {};
  MemoryHostPointerPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT;
  MemoryHostPointerPropertiesEXT.pNext = nullptr;
  MemoryHostPointerPropertiesEXT.memoryTypeBits = memoryTypeBits;
  return MemoryHostPointerPropertiesEXT;
}

inline VkPhysicalDeviceExternalMemoryHostPropertiesEXT
vkiPhysicalDeviceExternalMemoryHostPropertiesEXT(
    VkDeviceSize minImportedHostPointerAlignment) {
  VkPhysicalDeviceExternalMemoryHostPropertiesEXT
      PhysicalDeviceExternalMemoryHostPropertiesEXT = {};
  PhysicalDeviceExternalMemoryHostPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
  PhysicalDeviceExternalMemoryHostPropertiesEXT.pNext = nullptr;
  PhysicalDeviceExternalMemoryHostPropertiesEXT
      .minImportedHostPointerAlignment = minImportedHostPointerAlignment;
  return PhysicalDeviceExternalMemoryHostPropertiesEXT;
}

inline VkPipelineCompilerControlCreateInfoAMD
vkiPipelineCompilerControlCreateInfoAMD(
    VkPipelineCompilerControlFlagsAMD compilerControlFlags) {
  VkPipelineCompilerControlCreateInfoAMD PipelineCompilerControlCreateInfoAMD =
      {};
  PipelineCompilerControlCreateInfoAMD.sType =
      VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
  PipelineCompilerControlCreateInfoAMD.pNext = nullptr;
  PipelineCompilerControlCreateInfoAMD.compilerControlFlags =
      compilerControlFlags;
  return PipelineCompilerControlCreateInfoAMD;
}

inline VkCalibratedTimestampInfoEXT vkiCalibratedTimestampInfoEXT(
    VkTimeDomainEXT timeDomain) {
  VkCalibratedTimestampInfoEXT CalibratedTimestampInfoEXT = {};
  CalibratedTimestampInfoEXT.sType =
      VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_EXT;
  CalibratedTimestampInfoEXT.pNext = nullptr;
  CalibratedTimestampInfoEXT.timeDomain = timeDomain;
  return CalibratedTimestampInfoEXT;
}

inline VkPhysicalDeviceShaderCorePropertiesAMD
vkiPhysicalDeviceShaderCorePropertiesAMD(
    uint32_t shaderEngineCount, uint32_t shaderArraysPerEngineCount,
    uint32_t computeUnitsPerShaderArray, uint32_t simdPerComputeUnit,
    uint32_t wavefrontsPerSimd, uint32_t wavefrontSize, uint32_t sgprsPerSimd,
    uint32_t minSgprAllocation, uint32_t maxSgprAllocation,
    uint32_t sgprAllocationGranularity, uint32_t vgprsPerSimd,
    uint32_t minVgprAllocation, uint32_t maxVgprAllocation,
    uint32_t vgprAllocationGranularity) {
  VkPhysicalDeviceShaderCorePropertiesAMD
      PhysicalDeviceShaderCorePropertiesAMD = {};
  PhysicalDeviceShaderCorePropertiesAMD.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
  PhysicalDeviceShaderCorePropertiesAMD.pNext = nullptr;
  PhysicalDeviceShaderCorePropertiesAMD.shaderEngineCount = shaderEngineCount;
  PhysicalDeviceShaderCorePropertiesAMD.shaderArraysPerEngineCount =
      shaderArraysPerEngineCount;
  PhysicalDeviceShaderCorePropertiesAMD.computeUnitsPerShaderArray =
      computeUnitsPerShaderArray;
  PhysicalDeviceShaderCorePropertiesAMD.simdPerComputeUnit = simdPerComputeUnit;
  PhysicalDeviceShaderCorePropertiesAMD.wavefrontsPerSimd = wavefrontsPerSimd;
  PhysicalDeviceShaderCorePropertiesAMD.wavefrontSize = wavefrontSize;
  PhysicalDeviceShaderCorePropertiesAMD.sgprsPerSimd = sgprsPerSimd;
  PhysicalDeviceShaderCorePropertiesAMD.minSgprAllocation = minSgprAllocation;
  PhysicalDeviceShaderCorePropertiesAMD.maxSgprAllocation = maxSgprAllocation;
  PhysicalDeviceShaderCorePropertiesAMD.sgprAllocationGranularity =
      sgprAllocationGranularity;
  PhysicalDeviceShaderCorePropertiesAMD.vgprsPerSimd = vgprsPerSimd;
  PhysicalDeviceShaderCorePropertiesAMD.minVgprAllocation = minVgprAllocation;
  PhysicalDeviceShaderCorePropertiesAMD.maxVgprAllocation = maxVgprAllocation;
  PhysicalDeviceShaderCorePropertiesAMD.vgprAllocationGranularity =
      vgprAllocationGranularity;
  return PhysicalDeviceShaderCorePropertiesAMD;
}

inline VkDeviceMemoryOverallocationCreateInfoAMD
vkiDeviceMemoryOverallocationCreateInfoAMD(
    VkMemoryOverallocationBehaviorAMD overallocationBehavior) {
  VkDeviceMemoryOverallocationCreateInfoAMD
      DeviceMemoryOverallocationCreateInfoAMD = {};
  DeviceMemoryOverallocationCreateInfoAMD.sType =
      VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD;
  DeviceMemoryOverallocationCreateInfoAMD.pNext = nullptr;
  DeviceMemoryOverallocationCreateInfoAMD.overallocationBehavior =
      overallocationBehavior;
  return DeviceMemoryOverallocationCreateInfoAMD;
}

inline VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT
vkiPhysicalDeviceVertexAttributeDivisorPropertiesEXT(
    uint32_t maxVertexAttribDivisor) {
  VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT
      PhysicalDeviceVertexAttributeDivisorPropertiesEXT = {};
  PhysicalDeviceVertexAttributeDivisorPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
  PhysicalDeviceVertexAttributeDivisorPropertiesEXT.pNext = nullptr;
  PhysicalDeviceVertexAttributeDivisorPropertiesEXT.maxVertexAttribDivisor =
      maxVertexAttribDivisor;
  return PhysicalDeviceVertexAttributeDivisorPropertiesEXT;
}

inline VkVertexInputBindingDivisorDescriptionEXT
vkiVertexInputBindingDivisorDescriptionEXT(uint32_t binding, uint32_t divisor) {
  VkVertexInputBindingDivisorDescriptionEXT
      VertexInputBindingDivisorDescriptionEXT = {};
  VertexInputBindingDivisorDescriptionEXT.binding = binding;
  VertexInputBindingDivisorDescriptionEXT.divisor = divisor;
  return VertexInputBindingDivisorDescriptionEXT;
}

inline VkPipelineVertexInputDivisorStateCreateInfoEXT
vkiPipelineVertexInputDivisorStateCreateInfoEXT(
    uint32_t vertexBindingDivisorCount,
    const VkVertexInputBindingDivisorDescriptionEXT* pVertexBindingDivisors) {
  VkPipelineVertexInputDivisorStateCreateInfoEXT
      PipelineVertexInputDivisorStateCreateInfoEXT = {};
  PipelineVertexInputDivisorStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
  PipelineVertexInputDivisorStateCreateInfoEXT.pNext = nullptr;
  PipelineVertexInputDivisorStateCreateInfoEXT.vertexBindingDivisorCount =
      vertexBindingDivisorCount;
  PipelineVertexInputDivisorStateCreateInfoEXT.pVertexBindingDivisors =
      pVertexBindingDivisors;
  return PipelineVertexInputDivisorStateCreateInfoEXT;
}

inline VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT
vkiPhysicalDeviceVertexAttributeDivisorFeaturesEXT(
    VkBool32 vertexAttributeInstanceRateDivisor,
    VkBool32 vertexAttributeInstanceRateZeroDivisor) {
  VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT
      PhysicalDeviceVertexAttributeDivisorFeaturesEXT = {};
  PhysicalDeviceVertexAttributeDivisorFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT;
  PhysicalDeviceVertexAttributeDivisorFeaturesEXT.pNext = nullptr;
  PhysicalDeviceVertexAttributeDivisorFeaturesEXT
      .vertexAttributeInstanceRateDivisor = vertexAttributeInstanceRateDivisor;
  PhysicalDeviceVertexAttributeDivisorFeaturesEXT
      .vertexAttributeInstanceRateZeroDivisor =
      vertexAttributeInstanceRateZeroDivisor;
  return PhysicalDeviceVertexAttributeDivisorFeaturesEXT;
}

inline VkPipelineCreationFeedbackEXT vkiPipelineCreationFeedbackEXT(
    uint64_t duration) {
  VkPipelineCreationFeedbackEXT PipelineCreationFeedbackEXT = {};
  PipelineCreationFeedbackEXT.flags = 0;
  PipelineCreationFeedbackEXT.duration = duration;
  return PipelineCreationFeedbackEXT;
}

inline VkPipelineCreationFeedbackCreateInfoEXT
vkiPipelineCreationFeedbackCreateInfoEXT(
    VkPipelineCreationFeedbackEXT* pPipelineCreationFeedback,
    uint32_t pipelineStageCreationFeedbackCount,
    VkPipelineCreationFeedbackEXT* pPipelineStageCreationFeedbacks) {
  VkPipelineCreationFeedbackCreateInfoEXT
      PipelineCreationFeedbackCreateInfoEXT = {};
  PipelineCreationFeedbackCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO_EXT;
  PipelineCreationFeedbackCreateInfoEXT.pNext = nullptr;
  PipelineCreationFeedbackCreateInfoEXT.pPipelineCreationFeedback =
      pPipelineCreationFeedback;
  PipelineCreationFeedbackCreateInfoEXT.pipelineStageCreationFeedbackCount =
      pipelineStageCreationFeedbackCount;
  PipelineCreationFeedbackCreateInfoEXT.pPipelineStageCreationFeedbacks =
      pPipelineStageCreationFeedbacks;
  return PipelineCreationFeedbackCreateInfoEXT;
}

inline VkPhysicalDeviceComputeShaderDerivativesFeaturesNV
vkiPhysicalDeviceComputeShaderDerivativesFeaturesNV(
    VkBool32 computeDerivativeGroupQuads,
    VkBool32 computeDerivativeGroupLinear) {
  VkPhysicalDeviceComputeShaderDerivativesFeaturesNV
      PhysicalDeviceComputeShaderDerivativesFeaturesNV = {};
  PhysicalDeviceComputeShaderDerivativesFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV;
  PhysicalDeviceComputeShaderDerivativesFeaturesNV.pNext = nullptr;
  PhysicalDeviceComputeShaderDerivativesFeaturesNV.computeDerivativeGroupQuads =
      computeDerivativeGroupQuads;
  PhysicalDeviceComputeShaderDerivativesFeaturesNV
      .computeDerivativeGroupLinear = computeDerivativeGroupLinear;
  return PhysicalDeviceComputeShaderDerivativesFeaturesNV;
}

inline VkPhysicalDeviceMeshShaderFeaturesNV
vkiPhysicalDeviceMeshShaderFeaturesNV(VkBool32 taskShader,
                                      VkBool32 meshShader) {
  VkPhysicalDeviceMeshShaderFeaturesNV PhysicalDeviceMeshShaderFeaturesNV = {};
  PhysicalDeviceMeshShaderFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV;
  PhysicalDeviceMeshShaderFeaturesNV.pNext = nullptr;
  PhysicalDeviceMeshShaderFeaturesNV.taskShader = taskShader;
  PhysicalDeviceMeshShaderFeaturesNV.meshShader = meshShader;
  return PhysicalDeviceMeshShaderFeaturesNV;
}

// inline VkPhysicalDeviceMeshShaderPropertiesNV
// vkiPhysicalDeviceMeshShaderPropertiesNV(uint32_t maxDrawMeshTasksCount,
// uint32_t maxTaskWorkGroupInvocations, uint32_t maxTaskWorkGroupSize[3],
// uint32_t maxTaskTotalMemorySize, uint32_t maxTaskOutputCount, uint32_t
// maxMeshWorkGroupInvocations, uint32_t maxMeshWorkGroupSize[3], uint32_t
// maxMeshTotalMemorySize, uint32_t maxMeshOutputVertices, uint32_t
// maxMeshOutputPrimitives, uint32_t maxMeshMultiviewViewCount, uint32_t
// meshOutputPerVertexGranularity, uint32_t meshOutputPerPrimitiveGranularity) {
//     VkPhysicalDeviceMeshShaderPropertiesNV
//     PhysicalDeviceMeshShaderPropertiesNV = {};
//     PhysicalDeviceMeshShaderPropertiesNV.sType =
//     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;
//     PhysicalDeviceMeshShaderPropertiesNV.pNext = nullptr;
//     PhysicalDeviceMeshShaderPropertiesNV.maxDrawMeshTasksCount =
//     maxDrawMeshTasksCount;
//     PhysicalDeviceMeshShaderPropertiesNV.maxTaskWorkGroupInvocations =
//     maxTaskWorkGroupInvocations;
//     PhysicalDeviceMeshShaderPropertiesNV.maxTaskWorkGroupSize[3] =
//     maxTaskWorkGroupSize[3];
//     PhysicalDeviceMeshShaderPropertiesNV.maxTaskTotalMemorySize =
//     maxTaskTotalMemorySize;
//     PhysicalDeviceMeshShaderPropertiesNV.maxTaskOutputCount =
//     maxTaskOutputCount;
//     PhysicalDeviceMeshShaderPropertiesNV.maxMeshWorkGroupInvocations =
//     maxMeshWorkGroupInvocations;
//     PhysicalDeviceMeshShaderPropertiesNV.maxMeshWorkGroupSize[3] =
//     maxMeshWorkGroupSize[3];
//     PhysicalDeviceMeshShaderPropertiesNV.maxMeshTotalMemorySize =
//     maxMeshTotalMemorySize;
//     PhysicalDeviceMeshShaderPropertiesNV.maxMeshOutputVertices =
//     maxMeshOutputVertices;
//     PhysicalDeviceMeshShaderPropertiesNV.maxMeshOutputPrimitives =
//     maxMeshOutputPrimitives;
//     PhysicalDeviceMeshShaderPropertiesNV.maxMeshMultiviewViewCount =
//     maxMeshMultiviewViewCount;
//     PhysicalDeviceMeshShaderPropertiesNV.meshOutputPerVertexGranularity =
//     meshOutputPerVertexGranularity;
//     PhysicalDeviceMeshShaderPropertiesNV.meshOutputPerPrimitiveGranularity =
//     meshOutputPerPrimitiveGranularity; return
//     PhysicalDeviceMeshShaderPropertiesNV;
// }

inline VkDrawMeshTasksIndirectCommandNV vkiDrawMeshTasksIndirectCommandNV(
    uint32_t taskCount, uint32_t firstTask) {
  VkDrawMeshTasksIndirectCommandNV DrawMeshTasksIndirectCommandNV = {};
  DrawMeshTasksIndirectCommandNV.taskCount = taskCount;
  DrawMeshTasksIndirectCommandNV.firstTask = firstTask;
  return DrawMeshTasksIndirectCommandNV;
}

inline VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV
vkiPhysicalDeviceFragmentShaderBarycentricFeaturesNV(
    VkBool32 fragmentShaderBarycentric) {
  VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV
      PhysicalDeviceFragmentShaderBarycentricFeaturesNV = {};
  PhysicalDeviceFragmentShaderBarycentricFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV;
  PhysicalDeviceFragmentShaderBarycentricFeaturesNV.pNext = nullptr;
  PhysicalDeviceFragmentShaderBarycentricFeaturesNV.fragmentShaderBarycentric =
      fragmentShaderBarycentric;
  return PhysicalDeviceFragmentShaderBarycentricFeaturesNV;
}

inline VkPhysicalDeviceShaderImageFootprintFeaturesNV
vkiPhysicalDeviceShaderImageFootprintFeaturesNV(VkBool32 imageFootprint) {
  VkPhysicalDeviceShaderImageFootprintFeaturesNV
      PhysicalDeviceShaderImageFootprintFeaturesNV = {};
  PhysicalDeviceShaderImageFootprintFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV;
  PhysicalDeviceShaderImageFootprintFeaturesNV.pNext = nullptr;
  PhysicalDeviceShaderImageFootprintFeaturesNV.imageFootprint = imageFootprint;
  return PhysicalDeviceShaderImageFootprintFeaturesNV;
}

inline VkPipelineViewportExclusiveScissorStateCreateInfoNV
vkiPipelineViewportExclusiveScissorStateCreateInfoNV(
    uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) {
  VkPipelineViewportExclusiveScissorStateCreateInfoNV
      PipelineViewportExclusiveScissorStateCreateInfoNV = {};
  PipelineViewportExclusiveScissorStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV;
  PipelineViewportExclusiveScissorStateCreateInfoNV.pNext = nullptr;
  PipelineViewportExclusiveScissorStateCreateInfoNV.exclusiveScissorCount =
      exclusiveScissorCount;
  PipelineViewportExclusiveScissorStateCreateInfoNV.pExclusiveScissors =
      pExclusiveScissors;
  return PipelineViewportExclusiveScissorStateCreateInfoNV;
}

inline VkPhysicalDeviceExclusiveScissorFeaturesNV
vkiPhysicalDeviceExclusiveScissorFeaturesNV(VkBool32 exclusiveScissor) {
  VkPhysicalDeviceExclusiveScissorFeaturesNV
      PhysicalDeviceExclusiveScissorFeaturesNV = {};
  PhysicalDeviceExclusiveScissorFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV;
  PhysicalDeviceExclusiveScissorFeaturesNV.pNext = nullptr;
  PhysicalDeviceExclusiveScissorFeaturesNV.exclusiveScissor = exclusiveScissor;
  return PhysicalDeviceExclusiveScissorFeaturesNV;
}

inline VkQueueFamilyCheckpointPropertiesNV vkiQueueFamilyCheckpointPropertiesNV(
    VkPipelineStageFlags checkpointExecutionStageMask) {
  VkQueueFamilyCheckpointPropertiesNV QueueFamilyCheckpointPropertiesNV = {};
  QueueFamilyCheckpointPropertiesNV.sType =
      VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV;
  QueueFamilyCheckpointPropertiesNV.pNext = nullptr;
  QueueFamilyCheckpointPropertiesNV.checkpointExecutionStageMask =
      checkpointExecutionStageMask;
  return QueueFamilyCheckpointPropertiesNV;
}

inline VkCheckpointDataNV vkiCheckpointDataNV(VkPipelineStageFlagBits stage,
                                              void* pCheckpointMarker) {
  VkCheckpointDataNV CheckpointDataNV = {};
  CheckpointDataNV.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV;
  CheckpointDataNV.pNext = nullptr;
  CheckpointDataNV.stage = stage;
  CheckpointDataNV.pCheckpointMarker = pCheckpointMarker;
  return CheckpointDataNV;
}

inline VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL
vkiPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL(
    VkBool32 shaderIntegerFunctions2) {
  VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL
      PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL = {};
  PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL;
  PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL.pNext = nullptr;
  PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL.shaderIntegerFunctions2 =
      shaderIntegerFunctions2;
  return PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL;
}

inline VkPerformanceValueINTEL vkiPerformanceValueINTEL(
    VkPerformanceValueTypeINTEL type, VkPerformanceValueDataINTEL data) {
  VkPerformanceValueINTEL PerformanceValueINTEL = {};
  PerformanceValueINTEL.type = type;
  PerformanceValueINTEL.data = data;
  return PerformanceValueINTEL;
}

inline VkInitializePerformanceApiInfoINTEL vkiInitializePerformanceApiInfoINTEL(
    void* pUserData) {
  VkInitializePerformanceApiInfoINTEL InitializePerformanceApiInfoINTEL = {};
  InitializePerformanceApiInfoINTEL.sType =
      VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL;
  InitializePerformanceApiInfoINTEL.pNext = nullptr;
  InitializePerformanceApiInfoINTEL.pUserData = pUserData;
  return InitializePerformanceApiInfoINTEL;
}

inline VkQueryPoolCreateInfoINTEL vkiQueryPoolCreateInfoINTEL(
    VkQueryPoolSamplingModeINTEL performanceCountersSampling) {
  VkQueryPoolCreateInfoINTEL QueryPoolCreateInfoINTEL = {};
  QueryPoolCreateInfoINTEL.sType =
      VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO_INTEL;
  QueryPoolCreateInfoINTEL.pNext = nullptr;
  QueryPoolCreateInfoINTEL.performanceCountersSampling =
      performanceCountersSampling;
  return QueryPoolCreateInfoINTEL;
}

inline VkPerformanceMarkerInfoINTEL vkiPerformanceMarkerInfoINTEL(
    uint64_t marker) {
  VkPerformanceMarkerInfoINTEL PerformanceMarkerInfoINTEL = {};
  PerformanceMarkerInfoINTEL.sType =
      VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL;
  PerformanceMarkerInfoINTEL.pNext = nullptr;
  PerformanceMarkerInfoINTEL.marker = marker;
  return PerformanceMarkerInfoINTEL;
}

inline VkPerformanceStreamMarkerInfoINTEL vkiPerformanceStreamMarkerInfoINTEL(
    uint32_t marker) {
  VkPerformanceStreamMarkerInfoINTEL PerformanceStreamMarkerInfoINTEL = {};
  PerformanceStreamMarkerInfoINTEL.sType =
      VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL;
  PerformanceStreamMarkerInfoINTEL.pNext = nullptr;
  PerformanceStreamMarkerInfoINTEL.marker = marker;
  return PerformanceStreamMarkerInfoINTEL;
}

inline VkPerformanceOverrideInfoINTEL vkiPerformanceOverrideInfoINTEL(
    VkPerformanceOverrideTypeINTEL type, VkBool32 enable, uint64_t parameter) {
  VkPerformanceOverrideInfoINTEL PerformanceOverrideInfoINTEL = {};
  PerformanceOverrideInfoINTEL.sType =
      VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL;
  PerformanceOverrideInfoINTEL.pNext = nullptr;
  PerformanceOverrideInfoINTEL.type = type;
  PerformanceOverrideInfoINTEL.enable = enable;
  PerformanceOverrideInfoINTEL.parameter = parameter;
  return PerformanceOverrideInfoINTEL;
}

inline VkPerformanceConfigurationAcquireInfoINTEL
vkiPerformanceConfigurationAcquireInfoINTEL(
    VkPerformanceConfigurationTypeINTEL type) {
  VkPerformanceConfigurationAcquireInfoINTEL
      PerformanceConfigurationAcquireInfoINTEL = {};
  PerformanceConfigurationAcquireInfoINTEL.sType =
      VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL;
  PerformanceConfigurationAcquireInfoINTEL.pNext = nullptr;
  PerformanceConfigurationAcquireInfoINTEL.type = type;
  return PerformanceConfigurationAcquireInfoINTEL;
}

inline VkPhysicalDevicePCIBusInfoPropertiesEXT
vkiPhysicalDevicePCIBusInfoPropertiesEXT(uint32_t pciDomain, uint32_t pciBus,
                                         uint32_t pciDevice,
                                         uint32_t pciFunction) {
  VkPhysicalDevicePCIBusInfoPropertiesEXT
      PhysicalDevicePCIBusInfoPropertiesEXT = {};
  PhysicalDevicePCIBusInfoPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT;
  PhysicalDevicePCIBusInfoPropertiesEXT.pNext = nullptr;
  PhysicalDevicePCIBusInfoPropertiesEXT.pciDomain = pciDomain;
  PhysicalDevicePCIBusInfoPropertiesEXT.pciBus = pciBus;
  PhysicalDevicePCIBusInfoPropertiesEXT.pciDevice = pciDevice;
  PhysicalDevicePCIBusInfoPropertiesEXT.pciFunction = pciFunction;
  return PhysicalDevicePCIBusInfoPropertiesEXT;
}

inline VkDisplayNativeHdrSurfaceCapabilitiesAMD
vkiDisplayNativeHdrSurfaceCapabilitiesAMD(VkBool32 localDimmingSupport) {
  VkDisplayNativeHdrSurfaceCapabilitiesAMD
      DisplayNativeHdrSurfaceCapabilitiesAMD = {};
  DisplayNativeHdrSurfaceCapabilitiesAMD.sType =
      VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD;
  DisplayNativeHdrSurfaceCapabilitiesAMD.pNext = nullptr;
  DisplayNativeHdrSurfaceCapabilitiesAMD.localDimmingSupport =
      localDimmingSupport;
  return DisplayNativeHdrSurfaceCapabilitiesAMD;
}

inline VkSwapchainDisplayNativeHdrCreateInfoAMD
vkiSwapchainDisplayNativeHdrCreateInfoAMD(VkBool32 localDimmingEnable) {
  VkSwapchainDisplayNativeHdrCreateInfoAMD
      SwapchainDisplayNativeHdrCreateInfoAMD = {};
  SwapchainDisplayNativeHdrCreateInfoAMD.sType =
      VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD;
  SwapchainDisplayNativeHdrCreateInfoAMD.pNext = nullptr;
  SwapchainDisplayNativeHdrCreateInfoAMD.localDimmingEnable =
      localDimmingEnable;
  return SwapchainDisplayNativeHdrCreateInfoAMD;
}

inline VkPhysicalDeviceFragmentDensityMapFeaturesEXT
vkiPhysicalDeviceFragmentDensityMapFeaturesEXT(
    VkBool32 fragmentDensityMap, VkBool32 fragmentDensityMapDynamic,
    VkBool32 fragmentDensityMapNonSubsampledImages) {
  VkPhysicalDeviceFragmentDensityMapFeaturesEXT
      PhysicalDeviceFragmentDensityMapFeaturesEXT = {};
  PhysicalDeviceFragmentDensityMapFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT;
  PhysicalDeviceFragmentDensityMapFeaturesEXT.pNext = nullptr;
  PhysicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMap =
      fragmentDensityMap;
  PhysicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMapDynamic =
      fragmentDensityMapDynamic;
  PhysicalDeviceFragmentDensityMapFeaturesEXT
      .fragmentDensityMapNonSubsampledImages =
      fragmentDensityMapNonSubsampledImages;
  return PhysicalDeviceFragmentDensityMapFeaturesEXT;
}

inline VkPhysicalDeviceFragmentDensityMapPropertiesEXT
vkiPhysicalDeviceFragmentDensityMapPropertiesEXT(
    VkExtent2D minFragmentDensityTexelSize,
    VkExtent2D maxFragmentDensityTexelSize,
    VkBool32 fragmentDensityInvocations) {
  VkPhysicalDeviceFragmentDensityMapPropertiesEXT
      PhysicalDeviceFragmentDensityMapPropertiesEXT = {};
  PhysicalDeviceFragmentDensityMapPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT;
  PhysicalDeviceFragmentDensityMapPropertiesEXT.pNext = nullptr;
  PhysicalDeviceFragmentDensityMapPropertiesEXT.minFragmentDensityTexelSize =
      minFragmentDensityTexelSize;
  PhysicalDeviceFragmentDensityMapPropertiesEXT.maxFragmentDensityTexelSize =
      maxFragmentDensityTexelSize;
  PhysicalDeviceFragmentDensityMapPropertiesEXT.fragmentDensityInvocations =
      fragmentDensityInvocations;
  return PhysicalDeviceFragmentDensityMapPropertiesEXT;
}

inline VkRenderPassFragmentDensityMapCreateInfoEXT
vkiRenderPassFragmentDensityMapCreateInfoEXT(
    VkAttachmentReference fragmentDensityMapAttachment) {
  VkRenderPassFragmentDensityMapCreateInfoEXT
      RenderPassFragmentDensityMapCreateInfoEXT = {};
  RenderPassFragmentDensityMapCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT;
  RenderPassFragmentDensityMapCreateInfoEXT.pNext = nullptr;
  RenderPassFragmentDensityMapCreateInfoEXT.fragmentDensityMapAttachment =
      fragmentDensityMapAttachment;
  return RenderPassFragmentDensityMapCreateInfoEXT;
}

inline VkPhysicalDeviceScalarBlockLayoutFeaturesEXT
vkiPhysicalDeviceScalarBlockLayoutFeaturesEXT(VkBool32 scalarBlockLayout) {
  VkPhysicalDeviceScalarBlockLayoutFeaturesEXT
      PhysicalDeviceScalarBlockLayoutFeaturesEXT = {};
  PhysicalDeviceScalarBlockLayoutFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES_EXT;
  PhysicalDeviceScalarBlockLayoutFeaturesEXT.pNext = nullptr;
  PhysicalDeviceScalarBlockLayoutFeaturesEXT.scalarBlockLayout =
      scalarBlockLayout;
  return PhysicalDeviceScalarBlockLayoutFeaturesEXT;
}

inline VkPhysicalDeviceSubgroupSizeControlFeaturesEXT
vkiPhysicalDeviceSubgroupSizeControlFeaturesEXT(VkBool32 subgroupSizeControl,
                                                VkBool32 computeFullSubgroups) {
  VkPhysicalDeviceSubgroupSizeControlFeaturesEXT
      PhysicalDeviceSubgroupSizeControlFeaturesEXT = {};
  PhysicalDeviceSubgroupSizeControlFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES_EXT;
  PhysicalDeviceSubgroupSizeControlFeaturesEXT.pNext = nullptr;
  PhysicalDeviceSubgroupSizeControlFeaturesEXT.subgroupSizeControl =
      subgroupSizeControl;
  PhysicalDeviceSubgroupSizeControlFeaturesEXT.computeFullSubgroups =
      computeFullSubgroups;
  return PhysicalDeviceSubgroupSizeControlFeaturesEXT;
}

inline VkPhysicalDeviceSubgroupSizeControlPropertiesEXT
vkiPhysicalDeviceSubgroupSizeControlPropertiesEXT(
    uint32_t minSubgroupSize, uint32_t maxSubgroupSize,
    uint32_t maxComputeWorkgroupSubgroups,
    VkShaderStageFlags requiredSubgroupSizeStages) {
  VkPhysicalDeviceSubgroupSizeControlPropertiesEXT
      PhysicalDeviceSubgroupSizeControlPropertiesEXT = {};
  PhysicalDeviceSubgroupSizeControlPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES_EXT;
  PhysicalDeviceSubgroupSizeControlPropertiesEXT.pNext = nullptr;
  PhysicalDeviceSubgroupSizeControlPropertiesEXT.minSubgroupSize =
      minSubgroupSize;
  PhysicalDeviceSubgroupSizeControlPropertiesEXT.maxSubgroupSize =
      maxSubgroupSize;
  PhysicalDeviceSubgroupSizeControlPropertiesEXT.maxComputeWorkgroupSubgroups =
      maxComputeWorkgroupSubgroups;
  PhysicalDeviceSubgroupSizeControlPropertiesEXT.requiredSubgroupSizeStages =
      requiredSubgroupSizeStages;
  return PhysicalDeviceSubgroupSizeControlPropertiesEXT;
}

inline VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT
vkiPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT(
    uint32_t requiredSubgroupSize) {
  VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT
      PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT = {};
  PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO_EXT;
  PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT.pNext = nullptr;
  PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT.requiredSubgroupSize =
      requiredSubgroupSize;
  return PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;
}

inline VkPhysicalDeviceShaderCoreProperties2AMD
vkiPhysicalDeviceShaderCoreProperties2AMD(
    VkShaderCorePropertiesFlagsAMD shaderCoreFeatures,
    uint32_t activeComputeUnitCount) {
  VkPhysicalDeviceShaderCoreProperties2AMD
      PhysicalDeviceShaderCoreProperties2AMD = {};
  PhysicalDeviceShaderCoreProperties2AMD.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;
  PhysicalDeviceShaderCoreProperties2AMD.pNext = nullptr;
  PhysicalDeviceShaderCoreProperties2AMD.shaderCoreFeatures =
      shaderCoreFeatures;
  PhysicalDeviceShaderCoreProperties2AMD.activeComputeUnitCount =
      activeComputeUnitCount;
  return PhysicalDeviceShaderCoreProperties2AMD;
}

inline VkPhysicalDeviceCoherentMemoryFeaturesAMD
vkiPhysicalDeviceCoherentMemoryFeaturesAMD(VkBool32 deviceCoherentMemory) {
  VkPhysicalDeviceCoherentMemoryFeaturesAMD
      PhysicalDeviceCoherentMemoryFeaturesAMD = {};
  PhysicalDeviceCoherentMemoryFeaturesAMD.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
  PhysicalDeviceCoherentMemoryFeaturesAMD.pNext = nullptr;
  PhysicalDeviceCoherentMemoryFeaturesAMD.deviceCoherentMemory =
      deviceCoherentMemory;
  return PhysicalDeviceCoherentMemoryFeaturesAMD;
}

// inline VkPhysicalDeviceMemoryBudgetPropertiesEXT
// vkiPhysicalDeviceMemoryBudgetPropertiesEXT(VkDeviceSize
// heapBudget[VK_MAX_MEMORY_HEAPS], VkDeviceSize heapUsage[VK_MAX_MEMORY_HEAPS])
// {
//     VkPhysicalDeviceMemoryBudgetPropertiesEXT
//     PhysicalDeviceMemoryBudgetPropertiesEXT = {};
//     PhysicalDeviceMemoryBudgetPropertiesEXT.sType =
//     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
//     PhysicalDeviceMemoryBudgetPropertiesEXT.pNext = nullptr;
//     PhysicalDeviceMemoryBudgetPropertiesEXT.heapBudget[VK_MAX_MEMORY_HEAPS] =
//     heapBudget[VK_MAX_MEMORY_HEAPS];
//     PhysicalDeviceMemoryBudgetPropertiesEXT.heapUsage[VK_MAX_MEMORY_HEAPS] =
//     heapUsage[VK_MAX_MEMORY_HEAPS]; return
//     PhysicalDeviceMemoryBudgetPropertiesEXT;
// }

inline VkPhysicalDeviceMemoryPriorityFeaturesEXT
vkiPhysicalDeviceMemoryPriorityFeaturesEXT(VkBool32 memoryPriority) {
  VkPhysicalDeviceMemoryPriorityFeaturesEXT
      PhysicalDeviceMemoryPriorityFeaturesEXT = {};
  PhysicalDeviceMemoryPriorityFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
  PhysicalDeviceMemoryPriorityFeaturesEXT.pNext = nullptr;
  PhysicalDeviceMemoryPriorityFeaturesEXT.memoryPriority = memoryPriority;
  return PhysicalDeviceMemoryPriorityFeaturesEXT;
}

inline VkMemoryPriorityAllocateInfoEXT vkiMemoryPriorityAllocateInfoEXT(
    float priority) {
  VkMemoryPriorityAllocateInfoEXT MemoryPriorityAllocateInfoEXT = {};
  MemoryPriorityAllocateInfoEXT.sType =
      VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT;
  MemoryPriorityAllocateInfoEXT.pNext = nullptr;
  MemoryPriorityAllocateInfoEXT.priority = priority;
  return MemoryPriorityAllocateInfoEXT;
}

inline VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV
vkiPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV(
    VkBool32 dedicatedAllocationImageAliasing) {
  VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV
      PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV = {};
  PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV;
  PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV.pNext = nullptr;
  PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV
      .dedicatedAllocationImageAliasing = dedicatedAllocationImageAliasing;
  return PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV;
}

inline VkPhysicalDeviceBufferDeviceAddressFeaturesEXT
vkiPhysicalDeviceBufferDeviceAddressFeaturesEXT(
    VkBool32 bufferDeviceAddress, VkBool32 bufferDeviceAddressCaptureReplay,
    VkBool32 bufferDeviceAddressMultiDevice) {
  VkPhysicalDeviceBufferDeviceAddressFeaturesEXT
      PhysicalDeviceBufferDeviceAddressFeaturesEXT = {};
  PhysicalDeviceBufferDeviceAddressFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT;
  PhysicalDeviceBufferDeviceAddressFeaturesEXT.pNext = nullptr;
  PhysicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddress =
      bufferDeviceAddress;
  PhysicalDeviceBufferDeviceAddressFeaturesEXT
      .bufferDeviceAddressCaptureReplay = bufferDeviceAddressCaptureReplay;
  PhysicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddressMultiDevice =
      bufferDeviceAddressMultiDevice;
  return PhysicalDeviceBufferDeviceAddressFeaturesEXT;
}

inline VkBufferDeviceAddressInfoEXT vkiBufferDeviceAddressInfoEXT(
    VkBuffer buffer) {
  VkBufferDeviceAddressInfoEXT BufferDeviceAddressInfoEXT = {};
  BufferDeviceAddressInfoEXT.sType =
      VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO_EXT;
  BufferDeviceAddressInfoEXT.pNext = nullptr;
  BufferDeviceAddressInfoEXT.buffer = buffer;
  return BufferDeviceAddressInfoEXT;
}

inline VkBufferDeviceAddressCreateInfoEXT vkiBufferDeviceAddressCreateInfoEXT(
    VkDeviceAddress deviceAddress) {
  VkBufferDeviceAddressCreateInfoEXT BufferDeviceAddressCreateInfoEXT = {};
  BufferDeviceAddressCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT;
  BufferDeviceAddressCreateInfoEXT.pNext = nullptr;
  BufferDeviceAddressCreateInfoEXT.deviceAddress = deviceAddress;
  return BufferDeviceAddressCreateInfoEXT;
}

inline VkImageStencilUsageCreateInfoEXT vkiImageStencilUsageCreateInfoEXT(
    VkImageUsageFlags stencilUsage) {
  VkImageStencilUsageCreateInfoEXT ImageStencilUsageCreateInfoEXT = {};
  ImageStencilUsageCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO_EXT;
  ImageStencilUsageCreateInfoEXT.pNext = nullptr;
  ImageStencilUsageCreateInfoEXT.stencilUsage = stencilUsage;
  return ImageStencilUsageCreateInfoEXT;
}

inline VkValidationFeaturesEXT vkiValidationFeaturesEXT(
    uint32_t enabledValidationFeatureCount,
    const VkValidationFeatureEnableEXT* pEnabledValidationFeatures,
    uint32_t disabledValidationFeatureCount,
    const VkValidationFeatureDisableEXT* pDisabledValidationFeatures) {
  VkValidationFeaturesEXT ValidationFeaturesEXT = {};
  ValidationFeaturesEXT.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
  ValidationFeaturesEXT.pNext = nullptr;
  ValidationFeaturesEXT.enabledValidationFeatureCount =
      enabledValidationFeatureCount;
  ValidationFeaturesEXT.pEnabledValidationFeatures = pEnabledValidationFeatures;
  ValidationFeaturesEXT.disabledValidationFeatureCount =
      disabledValidationFeatureCount;
  ValidationFeaturesEXT.pDisabledValidationFeatures =
      pDisabledValidationFeatures;
  return ValidationFeaturesEXT;
}

inline VkCooperativeMatrixPropertiesNV vkiCooperativeMatrixPropertiesNV(
    uint32_t MSize, uint32_t NSize, uint32_t KSize, VkComponentTypeNV AType,
    VkComponentTypeNV BType, VkComponentTypeNV CType, VkComponentTypeNV DType,
    VkScopeNV scope) {
  VkCooperativeMatrixPropertiesNV CooperativeMatrixPropertiesNV = {};
  CooperativeMatrixPropertiesNV.sType =
      VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV;
  CooperativeMatrixPropertiesNV.pNext = nullptr;
  CooperativeMatrixPropertiesNV.MSize = MSize;
  CooperativeMatrixPropertiesNV.NSize = NSize;
  CooperativeMatrixPropertiesNV.KSize = KSize;
  CooperativeMatrixPropertiesNV.AType = AType;
  CooperativeMatrixPropertiesNV.BType = BType;
  CooperativeMatrixPropertiesNV.CType = CType;
  CooperativeMatrixPropertiesNV.DType = DType;
  CooperativeMatrixPropertiesNV.scope = scope;
  return CooperativeMatrixPropertiesNV;
}

inline VkPhysicalDeviceCooperativeMatrixFeaturesNV
vkiPhysicalDeviceCooperativeMatrixFeaturesNV(
    VkBool32 cooperativeMatrix, VkBool32 cooperativeMatrixRobustBufferAccess) {
  VkPhysicalDeviceCooperativeMatrixFeaturesNV
      PhysicalDeviceCooperativeMatrixFeaturesNV = {};
  PhysicalDeviceCooperativeMatrixFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV;
  PhysicalDeviceCooperativeMatrixFeaturesNV.pNext = nullptr;
  PhysicalDeviceCooperativeMatrixFeaturesNV.cooperativeMatrix =
      cooperativeMatrix;
  PhysicalDeviceCooperativeMatrixFeaturesNV
      .cooperativeMatrixRobustBufferAccess =
      cooperativeMatrixRobustBufferAccess;
  return PhysicalDeviceCooperativeMatrixFeaturesNV;
}

inline VkPhysicalDeviceCooperativeMatrixPropertiesNV
vkiPhysicalDeviceCooperativeMatrixPropertiesNV(
    VkShaderStageFlags cooperativeMatrixSupportedStages) {
  VkPhysicalDeviceCooperativeMatrixPropertiesNV
      PhysicalDeviceCooperativeMatrixPropertiesNV = {};
  PhysicalDeviceCooperativeMatrixPropertiesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
  PhysicalDeviceCooperativeMatrixPropertiesNV.pNext = nullptr;
  PhysicalDeviceCooperativeMatrixPropertiesNV.cooperativeMatrixSupportedStages =
      cooperativeMatrixSupportedStages;
  return PhysicalDeviceCooperativeMatrixPropertiesNV;
}

inline VkPhysicalDeviceCoverageReductionModeFeaturesNV
vkiPhysicalDeviceCoverageReductionModeFeaturesNV(
    VkBool32 coverageReductionMode) {
  VkPhysicalDeviceCoverageReductionModeFeaturesNV
      PhysicalDeviceCoverageReductionModeFeaturesNV = {};
  PhysicalDeviceCoverageReductionModeFeaturesNV.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV;
  PhysicalDeviceCoverageReductionModeFeaturesNV.pNext = nullptr;
  PhysicalDeviceCoverageReductionModeFeaturesNV.coverageReductionMode =
      coverageReductionMode;
  return PhysicalDeviceCoverageReductionModeFeaturesNV;
}

inline VkPipelineCoverageReductionStateCreateInfoNV
vkiPipelineCoverageReductionStateCreateInfoNV(
    VkCoverageReductionModeNV coverageReductionMode) {
  VkPipelineCoverageReductionStateCreateInfoNV
      PipelineCoverageReductionStateCreateInfoNV = {};
  PipelineCoverageReductionStateCreateInfoNV.sType =
      VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV;
  PipelineCoverageReductionStateCreateInfoNV.pNext = nullptr;
  PipelineCoverageReductionStateCreateInfoNV.flags = 0;
  PipelineCoverageReductionStateCreateInfoNV.coverageReductionMode =
      coverageReductionMode;
  return PipelineCoverageReductionStateCreateInfoNV;
}

inline VkFramebufferMixedSamplesCombinationNV
vkiFramebufferMixedSamplesCombinationNV(
    VkCoverageReductionModeNV coverageReductionMode,
    VkSampleCountFlagBits rasterizationSamples,
    VkSampleCountFlags depthStencilSamples, VkSampleCountFlags colorSamples) {
  VkFramebufferMixedSamplesCombinationNV FramebufferMixedSamplesCombinationNV =
      {};
  FramebufferMixedSamplesCombinationNV.sType =
      VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV;
  FramebufferMixedSamplesCombinationNV.pNext = nullptr;
  FramebufferMixedSamplesCombinationNV.coverageReductionMode =
      coverageReductionMode;
  FramebufferMixedSamplesCombinationNV.rasterizationSamples =
      rasterizationSamples;
  FramebufferMixedSamplesCombinationNV.depthStencilSamples =
      depthStencilSamples;
  FramebufferMixedSamplesCombinationNV.colorSamples = colorSamples;
  return FramebufferMixedSamplesCombinationNV;
}

inline VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT
vkiPhysicalDeviceFragmentShaderInterlockFeaturesEXT(
    VkBool32 fragmentShaderSampleInterlock,
    VkBool32 fragmentShaderPixelInterlock,
    VkBool32 fragmentShaderShadingRateInterlock) {
  VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT
      PhysicalDeviceFragmentShaderInterlockFeaturesEXT = {};
  PhysicalDeviceFragmentShaderInterlockFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
  PhysicalDeviceFragmentShaderInterlockFeaturesEXT.pNext = nullptr;
  PhysicalDeviceFragmentShaderInterlockFeaturesEXT
      .fragmentShaderSampleInterlock = fragmentShaderSampleInterlock;
  PhysicalDeviceFragmentShaderInterlockFeaturesEXT
      .fragmentShaderPixelInterlock = fragmentShaderPixelInterlock;
  PhysicalDeviceFragmentShaderInterlockFeaturesEXT
      .fragmentShaderShadingRateInterlock = fragmentShaderShadingRateInterlock;
  return PhysicalDeviceFragmentShaderInterlockFeaturesEXT;
}

inline VkPhysicalDeviceYcbcrImageArraysFeaturesEXT
vkiPhysicalDeviceYcbcrImageArraysFeaturesEXT(VkBool32 ycbcrImageArrays) {
  VkPhysicalDeviceYcbcrImageArraysFeaturesEXT
      PhysicalDeviceYcbcrImageArraysFeaturesEXT = {};
  PhysicalDeviceYcbcrImageArraysFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT;
  PhysicalDeviceYcbcrImageArraysFeaturesEXT.pNext = nullptr;
  PhysicalDeviceYcbcrImageArraysFeaturesEXT.ycbcrImageArrays = ycbcrImageArrays;
  return PhysicalDeviceYcbcrImageArraysFeaturesEXT;
}

inline VkHeadlessSurfaceCreateInfoEXT vkiHeadlessSurfaceCreateInfoEXT() {
  VkHeadlessSurfaceCreateInfoEXT HeadlessSurfaceCreateInfoEXT = {};
  HeadlessSurfaceCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
  HeadlessSurfaceCreateInfoEXT.pNext = nullptr;
  HeadlessSurfaceCreateInfoEXT.flags = 0;
  return HeadlessSurfaceCreateInfoEXT;
}

inline VkPhysicalDeviceLineRasterizationFeaturesEXT
vkiPhysicalDeviceLineRasterizationFeaturesEXT(VkBool32 rectangularLines,
                                              VkBool32 bresenhamLines,
                                              VkBool32 smoothLines,
                                              VkBool32 stippledRectangularLines,
                                              VkBool32 stippledBresenhamLines,
                                              VkBool32 stippledSmoothLines) {
  VkPhysicalDeviceLineRasterizationFeaturesEXT
      PhysicalDeviceLineRasterizationFeaturesEXT = {};
  PhysicalDeviceLineRasterizationFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_EXT;
  PhysicalDeviceLineRasterizationFeaturesEXT.pNext = nullptr;
  PhysicalDeviceLineRasterizationFeaturesEXT.rectangularLines =
      rectangularLines;
  PhysicalDeviceLineRasterizationFeaturesEXT.bresenhamLines = bresenhamLines;
  PhysicalDeviceLineRasterizationFeaturesEXT.smoothLines = smoothLines;
  PhysicalDeviceLineRasterizationFeaturesEXT.stippledRectangularLines =
      stippledRectangularLines;
  PhysicalDeviceLineRasterizationFeaturesEXT.stippledBresenhamLines =
      stippledBresenhamLines;
  PhysicalDeviceLineRasterizationFeaturesEXT.stippledSmoothLines =
      stippledSmoothLines;
  return PhysicalDeviceLineRasterizationFeaturesEXT;
}

inline VkPhysicalDeviceLineRasterizationPropertiesEXT
vkiPhysicalDeviceLineRasterizationPropertiesEXT(
    uint32_t lineSubPixelPrecisionBits) {
  VkPhysicalDeviceLineRasterizationPropertiesEXT
      PhysicalDeviceLineRasterizationPropertiesEXT = {};
  PhysicalDeviceLineRasterizationPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES_EXT;
  PhysicalDeviceLineRasterizationPropertiesEXT.pNext = nullptr;
  PhysicalDeviceLineRasterizationPropertiesEXT.lineSubPixelPrecisionBits =
      lineSubPixelPrecisionBits;
  return PhysicalDeviceLineRasterizationPropertiesEXT;
}

inline VkPipelineRasterizationLineStateCreateInfoEXT
vkiPipelineRasterizationLineStateCreateInfoEXT(
    VkLineRasterizationModeEXT lineRasterizationMode,
    VkBool32 stippledLineEnable, uint32_t lineStippleFactor,
    uint16_t lineStipplePattern) {
  VkPipelineRasterizationLineStateCreateInfoEXT
      PipelineRasterizationLineStateCreateInfoEXT = {};
  PipelineRasterizationLineStateCreateInfoEXT.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT;
  PipelineRasterizationLineStateCreateInfoEXT.pNext = nullptr;
  PipelineRasterizationLineStateCreateInfoEXT.lineRasterizationMode =
      lineRasterizationMode;
  PipelineRasterizationLineStateCreateInfoEXT.stippledLineEnable =
      stippledLineEnable;
  PipelineRasterizationLineStateCreateInfoEXT.lineStippleFactor =
      lineStippleFactor;
  PipelineRasterizationLineStateCreateInfoEXT.lineStipplePattern =
      lineStipplePattern;
  return PipelineRasterizationLineStateCreateInfoEXT;
}

inline VkPhysicalDeviceHostQueryResetFeaturesEXT
vkiPhysicalDeviceHostQueryResetFeaturesEXT(VkBool32 hostQueryReset) {
  VkPhysicalDeviceHostQueryResetFeaturesEXT
      PhysicalDeviceHostQueryResetFeaturesEXT = {};
  PhysicalDeviceHostQueryResetFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES_EXT;
  PhysicalDeviceHostQueryResetFeaturesEXT.pNext = nullptr;
  PhysicalDeviceHostQueryResetFeaturesEXT.hostQueryReset = hostQueryReset;
  return PhysicalDeviceHostQueryResetFeaturesEXT;
}

inline VkPhysicalDeviceIndexTypeUint8FeaturesEXT
vkiPhysicalDeviceIndexTypeUint8FeaturesEXT(VkBool32 indexTypeUint8) {
  VkPhysicalDeviceIndexTypeUint8FeaturesEXT
      PhysicalDeviceIndexTypeUint8FeaturesEXT = {};
  PhysicalDeviceIndexTypeUint8FeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT;
  PhysicalDeviceIndexTypeUint8FeaturesEXT.pNext = nullptr;
  PhysicalDeviceIndexTypeUint8FeaturesEXT.indexTypeUint8 = indexTypeUint8;
  return PhysicalDeviceIndexTypeUint8FeaturesEXT;
}

inline VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT
vkiPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT(
    VkBool32 shaderDemoteToHelperInvocation) {
  VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT
      PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT = {};
  PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES_EXT;
  PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT.pNext = nullptr;
  PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT
      .shaderDemoteToHelperInvocation = shaderDemoteToHelperInvocation;
  return PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
}

inline VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT
vkiPhysicalDeviceTexelBufferAlignmentFeaturesEXT(
    VkBool32 texelBufferAlignment) {
  VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT
      PhysicalDeviceTexelBufferAlignmentFeaturesEXT = {};
  PhysicalDeviceTexelBufferAlignmentFeaturesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
  PhysicalDeviceTexelBufferAlignmentFeaturesEXT.pNext = nullptr;
  PhysicalDeviceTexelBufferAlignmentFeaturesEXT.texelBufferAlignment =
      texelBufferAlignment;
  return PhysicalDeviceTexelBufferAlignmentFeaturesEXT;
}

inline VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT
vkiPhysicalDeviceTexelBufferAlignmentPropertiesEXT(
    VkDeviceSize storageTexelBufferOffsetAlignmentBytes,
    VkBool32 storageTexelBufferOffsetSingleTexelAlignment,
    VkDeviceSize uniformTexelBufferOffsetAlignmentBytes,
    VkBool32 uniformTexelBufferOffsetSingleTexelAlignment) {
  VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT
      PhysicalDeviceTexelBufferAlignmentPropertiesEXT = {};
  PhysicalDeviceTexelBufferAlignmentPropertiesEXT.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES_EXT;
  PhysicalDeviceTexelBufferAlignmentPropertiesEXT.pNext = nullptr;
  PhysicalDeviceTexelBufferAlignmentPropertiesEXT
      .storageTexelBufferOffsetAlignmentBytes =
      storageTexelBufferOffsetAlignmentBytes;
  PhysicalDeviceTexelBufferAlignmentPropertiesEXT
      .storageTexelBufferOffsetSingleTexelAlignment =
      storageTexelBufferOffsetSingleTexelAlignment;
  PhysicalDeviceTexelBufferAlignmentPropertiesEXT
      .uniformTexelBufferOffsetAlignmentBytes =
      uniformTexelBufferOffsetAlignmentBytes;
  PhysicalDeviceTexelBufferAlignmentPropertiesEXT
      .uniformTexelBufferOffsetSingleTexelAlignment =
      uniformTexelBufferOffsetSingleTexelAlignment;
  return PhysicalDeviceTexelBufferAlignmentPropertiesEXT;
}
#endif
