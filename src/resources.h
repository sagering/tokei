#pragma once

#include "common.h"

struct DescriptorSetLayout
{
  enum
  {
    MAX_NUM_DESCRIPTOR_SET_BINDINGS = 16
  };

  VkDescriptorSetLayoutBinding bindings[MAX_NUM_DESCRIPTOR_SET_BINDINGS];
  uint32_t bindingCnt;
};

struct RenderPassInternal
{
  enum
  {
    MAX_NUM_ATTACHMENTS = 8,
    MAX_NUM_SUBPASSES = 8,
    MAX_NUM_SUBPASS_DEPENDENCIES = 16,
    MAX_NUM_SUBPASS_INPUT_ATTACHMENTS = 2,
    MAX_NUM_SUBPASS_COLOR_ATTACHMENTS = 2,
    MAX_NUM_SUBPASS_RESOLVE_ATTACHMENTS = 2,
    MAX_NUM_SUBPASS_DEPTH_STENCIL_ATTACHMENTS = 1,
  };

  VkAttachmentDescription attachments[MAX_NUM_ATTACHMENTS];
  uint32_t attachmentCnt;

  VkSubpassDependency dependencies[MAX_NUM_SUBPASS_DEPENDENCIES];
  uint32_t dependencyCnt;

  struct AttachmentRefs
  {
    VkAttachmentReference inputAttachments[MAX_NUM_SUBPASS_INPUT_ATTACHMENTS];
    uint32_t inputAttachmentCnt;
    VkAttachmentReference colorAttachments[MAX_NUM_SUBPASS_COLOR_ATTACHMENTS];
    uint32_t colorAttachmentCnt;
    VkAttachmentReference
        resolveAttachments[MAX_NUM_SUBPASS_RESOLVE_ATTACHMENTS];
    uint32_t resolveAttachmentCnt;
    VkAttachmentReference
        depthStencilAttachments[MAX_NUM_SUBPASS_DEPTH_STENCIL_ATTACHMENTS];
    uint32_t depthStencilAttachmentCnt;
  };

  AttachmentRefs attachmentRefs[MAX_NUM_SUBPASSES];
  VkSubpassDescription subpassess[MAX_NUM_SUBPASSES];
  uint32_t subpassCnt;
};

struct Framebuffer
{
  enum
  {
    MAX_NUM_ATTACHMENTS = 8
  };

  VkRenderPass renderPass;                      // deps
  VkImageView attachments[MAX_NUM_ATTACHMENTS]; // deps
  uint32_t attachmentCnt;

  uint32_t width;
  uint32_t height;
  uint32_t layers;
};

struct ShaderLayout
{
  enum
  {
    MAX_NUM_DESCRIPTOR_SET_LAYOUT_BINDINGS = 16,
    MAX_NUM_PUSH_CONSTANT_RANGES = 1
  };

  struct DescriptorSetLayoutBinding
  {
    uint32_t set = 0;
    VkDescriptorSetLayoutBinding binding = {};
  };

  DescriptorSetLayoutBinding bindings[MAX_NUM_DESCRIPTOR_SET_LAYOUT_BINDINGS] =
      {};
  uint32_t bindingCnt = 0;

  VkPushConstantRange pushConstantRanges[MAX_NUM_PUSH_CONSTANT_RANGES] = {};
  uint32_t pushConstantRangeCount = 0;

  uint32_t inputLocationMask = 0;
  uint32_t outputLocationMask = 0;
  uint32_t inputAttachmentMask = 0;
};

struct PipelineLayout
{
  enum
  {
    MAX_NUM_DESCRIPTOR_SETS = 16
  };

  DescriptorSetLayout layouts[MAX_NUM_DESCRIPTOR_SETS];
  uint32_t layoutCnt;
};

struct GraphicsPipelineState
{
  struct BlendState
  {
    bool enable;
    VkBlendOp colorOp;
    VkBlendFactor srcColorFactor;
    VkBlendFactor dstColorFactor;
    VkBlendOp alphaOp;
    VkBlendFactor srcAlphaFactor;
    VkBlendFactor dstAlphaFactor;
  } blend;

  struct DepthStencilState
  {
    bool depthTestenable;
    bool depthWriteEnable;
    VkCompareOp depthCompareOp;

    bool stencilTestEnable;
    VkStencilOpState front;
    VkStencilOpState back;
  } depthStencil;

  struct InputAssemblyState
  {
    VkPrimitiveTopology topology;
    bool primitiveRestartEnable;
  } inputAssembly;

  struct RasterizationState
  {
    VkPolygonMode polygonMode;
    VkCullModeFlags cullMode;
    VkFrontFace frontFace;
  } rasterization;

  struct VertexInputState
  {
    enum
    {
      MAX_NUM_VERTEX_BINDINGS = 2,
      MAX_NUM_VERTEX_ATTRIBUTES = 8
    };

    struct BindingDescription
    {
      uint32_t binding;
      uint32_t stride;
      VkVertexInputRate inputRate;
    };

    BindingDescription bindingDescriptions[MAX_NUM_VERTEX_BINDINGS];
    uint32_t bindingDescriptionCnt;

    struct AttributeDescription
    {
      uint32_t location;
      uint32_t binding;
      VkFormat format;
      uint32_t offset;
    };

    AttributeDescription attributeDescriptions[MAX_NUM_VERTEX_BINDINGS];
    uint32_t attributeDescriptionCnt;
  } vertexInput;

  struct ViewportState
  {
    VkViewport viewport;
    VkRect2D scissors;
  } viewport;

  struct MultisampleState
  {
    VkSampleCountFlagBits rasterizationSamples;
  } multisample;
};

VkRenderPass createRenderPass(VkDevice, RenderPassInternal const *);

VkFramebuffer createFramebuffer(VkDevice, Framebuffer const *);

VkDescriptorSetLayout createDescriptorSetLayout(VkDevice,
                                                DescriptorSetLayout const *);

ShaderLayout createShaderLayout(char const *filepath);

PipelineLayout createPipelineLayout(ShaderLayout *,
                                    VkShaderStageFlagBits const *,
                                    uint32_t cnt);

VkPipelineLayout createPipelineLayout(VkDevice, PipelineLayout const *);

VkShaderModule createShaderModule(VkDevice, char const *filepath);

VkPipeline createComputePipeline(VkDevice, VkShaderModule, VkPipelineLayout);

VkPipeline createGraphicsPipeline(VkDevice, VkShaderModule *,
                                  VkShaderStageFlagBits *,
                                  uint32_t shaderModuleCnt, VkPipelineLayout,
                                  GraphicsPipelineState const *, VkRenderPass,
                                  uint32_t subpass);

VkSampler createSampler(VkDevice);

VkRenderPass createRenderPass(VkDevice, RenderPassInternal const *);

VkEvent createEvent(VkDevice);

VkSemaphore createSemaphore(VkDevice);

VkFence createFence(VkDevice);
