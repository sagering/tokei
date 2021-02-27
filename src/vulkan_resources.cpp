#include "vulkan_resources.h"

#include <assert.h>
#include <spirv_cross/spirv_cross.hpp>

#include "vulkan_types.h"

FNVHash
hash(void const* data, uint32_t size, FNVHash prev)
{
  uint8_t const* ptr = static_cast<uint8_t const*>(data);
  uint8_t const* end = ptr + size;

  while (ptr < end) {
    prev.value ^= *ptr;
    prev.value *= 0x100000001b3;
    ++ptr;
  }

  return prev;
}

FNVHash
hash(DescriptorSetLayout const* layout, FNVHash prev)
{
  return hash(
    &layout->bindings, sizeof(layout->bindings[0]) * layout->bindingCnt, prev);
}

FNVHash
hash(RenderPass const* renderpass, FNVHash prev)
{
  prev = hash(renderpass->attachments,
              sizeof(renderpass->attachments[0]) * renderpass->attachmentCnt,
              prev);
  prev = hash(renderpass->dependencies,
              sizeof(renderpass->dependencies[0]) * renderpass->dependencyCnt,
              prev);

  for (uint32_t i = 0; i < renderpass->subpassCnt; ++i) {
    prev = hash(renderpass->attachmentRefs[i].inputAttachments,
                sizeof(renderpass->attachmentRefs[i].inputAttachments[0]) *
                  renderpass->attachmentRefs[i].inputAttachmentCnt,
                prev);
    prev = hash(renderpass->attachmentRefs[i].colorAttachments,
                sizeof(renderpass->attachmentRefs[i].colorAttachments[0]) *
                  renderpass->attachmentRefs[i].colorAttachmentCnt,
                prev);
    prev =
      hash(renderpass->attachmentRefs[i].depthStencilAttachments,
           sizeof(renderpass->attachmentRefs[i].depthStencilAttachments[0]) *
             renderpass->attachmentRefs[i].depthStencilAttachmentCnt,
           prev);
  }

  return prev;
}

FNVHash
hash(Framebuffer const* framebuffer, FNVHash prev)
{
  prev = hash(&framebuffer->renderPass, sizeof(framebuffer->renderPass), prev);
  prev = hash(&framebuffer->width, sizeof(framebuffer->width), prev);
  prev = hash(&framebuffer->height, sizeof(framebuffer->height), prev);
  prev = hash(&framebuffer->layers, sizeof(framebuffer->layers), prev);
  return hash(&framebuffer->attachments,
              sizeof(framebuffer->attachments[0]) * framebuffer->attachmentCnt,
              prev);
}

FNVHash
hash(PipelineLayout const* pipelineLayout, FNVHash prev)
{
  return hash(pipelineLayout->layouts,
              sizeof(pipelineLayout->layouts[0]) * pipelineLayout->layoutCnt,
              prev);
}

FNVHash
hash(Pipeline1 const* pipeline, FNVHash prev)
{
  prev = hash(pipeline, sizeof(*pipeline), prev);
  return hash(pipeline->state, sizeof(*pipeline->state), prev);
}

VkRenderPass
GetRenderPass(StaticResources* res, RenderPass* renderPass_)
{
  auto h = hash(renderPass_);
  auto it = res->renderPasses.find(h);
  if (it != res->renderPasses.end()) {
    return it->second;
  }

  auto createInfo = vkiRenderPassCreateInfo(renderPass_->attachmentCnt,
                                            renderPass_->attachments,
                                            renderPass_->subpassCnt,
                                            renderPass_->subpassess,
                                            renderPass_->dependencyCnt,
                                            renderPass_->dependencies);

  VkRenderPass renderPass = VK_NULL_HANDLE;
  vkCreateRenderPass(res->device, &createInfo, nullptr, &renderPass);

  res->renderPasses.insert({ h, renderPass });

  return renderPass;
}

VkFramebuffer
GetFramebuffer(StaticResources* res, Framebuffer* framebuffer_)
{
  auto h = hash(framebuffer_);
  auto it = res->framebuffers.find(h);
  if (it != res->framebuffers.end()) {
    return it->second;
  }

  VkFramebuffer framebuffer = VK_NULL_HANDLE;
  auto createInfo = vkiFramebufferCreateInfo(framebuffer_->renderPass,
                                             framebuffer_->attachmentCnt,
                                             framebuffer_->attachments,
                                             framebuffer_->width,
                                             framebuffer_->height,
                                             framebuffer_->layers);
  vkCreateFramebuffer(res->device, &createInfo, nullptr, &framebuffer);

  res->framebuffers.insert({ h, framebuffer });

  return framebuffer;
}

VkPipelineLayout
GetPipelineLayout(StaticResources* res, PipelineLayout* layout_)
{
  auto h = hash(layout_);

  auto it = res->pipelineLayouts.find(h);

  if (it != res->pipelineLayouts.end()) {
    return it->second;
  }

  VkDescriptorSetLayout dlayouts[PipelineLayout::MAX_NUM_DESCRIPTOR_SETS];
  for (uint32_t set = 0; set < layout_->layoutCnt; ++set) {
    dlayouts[set] = GetDescriptorSetLayout(res, &layout_->layouts[set]);
  }

  VkPipelineLayout layout = VK_NULL_HANDLE;
  auto createInfo =
    vkiPipelineLayoutCreateInfo(layout_->layoutCnt, dlayouts, 0, nullptr);
  vkCreatePipelineLayout(res->device, &createInfo, nullptr, &layout);

  res->pipelineLayouts.insert({ h, layout });
  return layout;
}

std::vector<uint32_t>*
GetShaderCode(StaticResources* res, char const* filepath)
{
  auto h = hash(&filepath, sizeof(filepath));

  auto it = res->shaderCode.find(h);

  if (it != res->shaderCode.end()) {
    return &it->second;
  }

  std::vector<uint32_t> code;

  FILE* file = 0;
  fopen_s(&file, filepath, "rb");

  if (!file) {
    return nullptr;
  }

  fseek(file, 0, SEEK_END);
  size_t bytes = ftell(file);

  code.resize(bytes / 4);

  fseek(file, 0, SEEK_SET);
  fread(&(*code.begin()), 1, bytes, file);
  fclose(file);

  auto result = res->shaderCode.emplace(h, std::move(code));
  return &result.first->second;
}

VkShaderModule
GetShaderModule(StaticResources* res, char const* filepath)
{
  auto h = hash(&filepath, sizeof(filepath));

  auto it = res->shaderModules.find(h);

  if (it != res->shaderModules.end()) {
    return it->second;
  }

  auto code = GetShaderCode(res, filepath);

  auto createInfo = vkiShaderModuleCreateInfo(
    static_cast<uint32_t>(code->size()) * 4, code->data());

  VkShaderModule shaderModule = VK_NULL_HANDLE;
  vkCreateShaderModule(res->device, &createInfo, nullptr, &shaderModule);

  res->shaderModules.insert({ h, shaderModule });

  return shaderModule;
}

static bool
ReadDescriptorCount(const spirv_cross::SPIRType& type, uint32_t& cnt)
{
  if (type.array.size() == 0) {
    cnt = 1;
    return true;
  }

  if (type.array.size() > 1) {
    return false; // vulkan only supports single array level for descriptors.
  }

  if (!type.array_size_literal.back()) {
    return false; // size cannot be statically resolved
  }

  if (type.array.back() == 0) {
    return false; // avoid bindless complexity
  }

  cnt = type.array.back();
  return true;
}

static bool
ReflectDescriptor(const spirv_cross::Compiler& comp,
                  const spirv_cross::Resource& res,
                  ShaderLayout1& layout)
{
  uint32_t set = comp.get_decoration(res.id, spv::DecorationDescriptorSet);
  uint32_t binding = comp.get_decoration(res.id, spv::DecorationBinding);
  uint32_t count = 0;

  if (!ReadDescriptorCount(comp.get_type(res.type_id), count)) {
    return false;
  }

  if (binding >= ShaderLayout1::MAX_NUM_DESCRIPTOR_SET_LAYOUT_BINDINGS) {
    return false;
  }

  layout.bindings[layout.bindingCnt].set = set;
  layout.bindings[layout.bindingCnt].binding =
    VkDescriptorSetLayoutBinding{ binding, {}, count, 0, nullptr };

  return true;
}

static bool
ReflectLayout(std::vector<uint32_t> const& code,
              VkShaderStageFlags stage,
              ShaderLayout1& layout)
{
  spirv_cross::Compiler comp(code.data(), code.size());

  auto resources = comp.get_shader_resources();

  // sampler2D
  for (auto& res : resources.sampled_images) {
    if (!ReflectDescriptor(comp, res, layout)) {
      return false;
    }

    layout.bindings[layout.bindingCnt].binding.descriptorType =
      VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    ++layout.bindingCnt;
  }

  // texture2D or samplerBuffer
  for (auto& res : resources.separate_images) {
    auto type = comp.get_type(res.base_type_id);
    if (type.image.dim == spv::DimBuffer) {
      if (!ReflectDescriptor(comp, res, layout)) {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
      ++layout.bindingCnt;
    } else {
      if (!ReflectDescriptor(comp, res, layout)) {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
      ++layout.bindingCnt;
    }
  }

  // image2D or imageBuffer
  for (auto& res : resources.storage_images) {
    auto type = comp.get_type(res.base_type_id);
    if (type.image.dim == spv::DimBuffer) {
      if (!ReflectDescriptor(comp, res, layout)) {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
      ++layout.bindingCnt;
    } else {
      if (!ReflectDescriptor(comp, res, layout)) {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
      ++layout.bindingCnt;
    }
  }

  // sampler
  for (auto& res : resources.separate_samplers) {
    if (!ReflectDescriptor(comp, res, layout)) {
      return false;
    }
    layout.bindings[layout.bindingCnt].binding.descriptorType =
      VK_DESCRIPTOR_TYPE_SAMPLER;
    ++layout.bindingCnt;
  }

  // uniform UBO {}
  for (auto& res : resources.uniform_buffers) {
    if (!ReflectDescriptor(comp, res, layout)) {
      return false;
    }
    layout.bindings[layout.bindingCnt].binding.descriptorType =
      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ++layout.bindingCnt;
  }

  // layout(push_constant) uniform Push
  if (resources.push_constant_buffers.size() > 0) {
    auto& res = resources.push_constant_buffers.back();

    layout.pushConstantRanges[0].offset = 0;
    layout.pushConstantRanges[0].size = static_cast<uint32_t>(
      comp.get_declared_struct_size(comp.get_type(res.type_id)));
    layout.pushConstantRanges[0].stageFlags = stage;
    layout.pushConstantRangeCount += 1;
  }

  for (auto& res : resources.subpass_inputs) {
    layout.inputAttachmentMask |=
      1 << comp.get_decoration(res.id, spv::DecorationInputAttachmentIndex);
  }

  if (stage == VK_SHADER_STAGE_VERTEX_BIT) {
    for (auto& res : resources.stage_inputs) {
      layout.inputLocationMask |=
        1 << comp.get_decoration(res.id, spv::DecorationLocation);
    }
  }

  if (stage == VK_SHADER_STAGE_FRAGMENT_BIT) {
    for (auto& res : resources.stage_outputs) {
      layout.outputLocationMask |=
        1 << comp.get_decoration(res.id, spv::DecorationLocation);
    }
  }

  // buffer SSBO {}
  for (auto& res : resources.storage_buffers) {
    if (!ReflectDescriptor(comp, res, layout)) {
      return false;
    }
    layout.bindings[layout.bindingCnt].binding.descriptorType =
      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    ++layout.bindingCnt;
  }

  return true;
}

bool
MergeShaderLayouts(ShaderLayout1* layouts,
                   uint32_t layoutCnt,
                   PipelineLayout* pipelineLayout)
{
  for (auto i = 0; i < PipelineLayout::MAX_NUM_DESCRIPTOR_SETS; ++i) {
    for (auto j = 0; j < DescriptorSetLayout::MAX_NUM_DESCRIPTOR_SET_BINDINGS;
         ++j) {
      pipelineLayout->layouts[i].bindings[j].binding = j;
    }
  }

  for (uint32_t layoutIdx = 0; layoutIdx < layoutCnt; ++layoutIdx) {
    ShaderLayout1 const& layout = layouts[layoutIdx];
    for (uint32_t bindingIdx = 0; bindingIdx < layout.bindingCnt;
         ++bindingIdx) {
      auto const set = layout.bindings[bindingIdx].set;
      auto const binding = layout.bindings[bindingIdx].binding.binding;

      if (set >= PipelineLayout::MAX_NUM_DESCRIPTOR_SETS) {
        return false;
      }

      if (binding >= DescriptorSetLayout::MAX_NUM_DESCRIPTOR_SET_BINDINGS) {
        return false;
      }

      pipelineLayout->layoutCnt = std::max(pipelineLayout->layoutCnt, set + 1);
      pipelineLayout->layouts[set].bindingCnt =
        std::max(pipelineLayout->layouts[set].bindingCnt, binding + 1);

      if (pipelineLayout->layouts[set].bindings[binding].stageFlags == 0) {
        pipelineLayout->layouts[set].bindings[binding] =
          layout.bindings[bindingIdx].binding;
      } else {
        // make sure thate descriptor bindings of different shader stages are
        // compatible
        if (pipelineLayout->layouts[set].bindings[binding].descriptorCount !=
            layout.bindings[bindingIdx].binding.descriptorCount) {
          return false;
        }

        if (pipelineLayout->layouts[set].bindings[binding].descriptorType !=
            layout.bindings[bindingIdx].binding.descriptorType) {
          return false;
        }

        pipelineLayout->layouts[set].bindings[binding].stageFlags |=
          layout.bindings[bindingIdx].binding.stageFlags;
      }
    }
  }

  return true;
}

ShaderLayout1
GetShaderLayout(StaticResources* res, char const* filepath)
{
  auto h = hash(&filepath, sizeof(filepath));

  auto it = res->shaderLayouts.find(h);

  if (it != res->shaderLayouts.end()) {
    return it->second;
  }

  auto code = GetShaderCode(res, filepath);

  ShaderLayout1 layout;
  ReflectLayout(*code, 0, layout);

  auto result = res->shaderLayouts.emplace(h, layout);
  return result.first->second;
}

VkDescriptorSetLayout
GetDescriptorSetLayout(StaticResources* res, DescriptorSetLayout const* layout_)
{
  auto h = hash(layout_);

  auto it = res->desriptorsSetLayouts.find(h);
  if (it != res->desriptorsSetLayouts.end()) {
    return it->second;
  }

  auto createInfo =
    vkiDescriptorSetLayoutCreateInfo(layout_->bindingCnt, layout_->bindings);

  VkDescriptorSetLayout layout = VK_NULL_HANDLE;
  vkCreateDescriptorSetLayout(res->device, &createInfo, nullptr, &layout);

  res->desriptorsSetLayouts.insert({ h, layout });
  return layout;
}

VkPipeline
GetPipeline(StaticResources* res, Pipeline1* pipeline_, PipelineLayout* layout_)
{
  auto h = hash(pipeline_);

  auto it = res->pipelines.find(h);
  if (it != res->pipelines.end()) {
    *layout_ = it->second.layout;
    return it->second.pipeline;
  }

  bool isCompute = pipeline_->state->shader.computeShader != nullptr;

  // shader
  VkPipelineShaderStageCreateInfo shaderStageCreateInfos[2];
  uint32_t shaderStageCnt = 0;
  ShaderLayout1 shaderLayouts[2];

  if (isCompute) {
    shaderStageCreateInfos[shaderStageCnt] = vkiPipelineShaderStageCreateInfo(
      VK_SHADER_STAGE_COMPUTE_BIT,
      GetShaderModule(res, pipeline_->state->shader.computeShader),
      "main",
      nullptr);
    shaderLayouts[shaderStageCnt] =
      GetShaderLayout(res, pipeline_->state->shader.computeShader);

    for (uint32_t bindingIdx = 0;
         bindingIdx < shaderLayouts[shaderStageCnt].bindingCnt;
         ++bindingIdx) {
      shaderLayouts[shaderStageCnt].bindings[bindingIdx].binding.stageFlags =
        VK_SHADER_STAGE_COMPUTE_BIT;
    }

    ++shaderStageCnt;

    MergeShaderLayouts(shaderLayouts, shaderStageCnt, layout_);

    auto layout = GetPipelineLayout(res, layout_);
    auto createInfo = vkiComputePipelineCreateInfo(
      *shaderStageCreateInfos, layout, VK_NULL_HANDLE, 0);
    VkPipeline pipeline = VK_NULL_HANDLE;
    vkCreateComputePipelines(
      res->device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &pipeline);

    res->pipelines.insert({ h, { pipeline, *layout_ } });

    return pipeline;
  }

  if (pipeline_->state->shader.vertexShader) {
    shaderStageCreateInfos[shaderStageCnt] = vkiPipelineShaderStageCreateInfo(
      VK_SHADER_STAGE_VERTEX_BIT,
      GetShaderModule(res, pipeline_->state->shader.vertexShader),
      "main",
      nullptr);
    shaderLayouts[shaderStageCnt] =
      GetShaderLayout(res, pipeline_->state->shader.vertexShader);

    for (uint32_t bindingIdx = 0;
         bindingIdx < shaderLayouts[shaderStageCnt].bindingCnt;
         ++bindingIdx) {
      shaderLayouts[shaderStageCnt].bindings[bindingIdx].binding.stageFlags =
        VK_SHADER_STAGE_VERTEX_BIT;
    }
    ++shaderStageCnt;
  }

  if (pipeline_->state->shader.fragmentShader) {
    shaderStageCreateInfos[shaderStageCnt] = vkiPipelineShaderStageCreateInfo(
      VK_SHADER_STAGE_FRAGMENT_BIT,
      GetShaderModule(res, pipeline_->state->shader.fragmentShader),
      "main",
      nullptr);
    shaderLayouts[shaderStageCnt] =
      GetShaderLayout(res, pipeline_->state->shader.fragmentShader);

    for (uint32_t bindingIdx = 0;
         bindingIdx < shaderLayouts[shaderStageCnt].bindingCnt;
         ++bindingIdx) {
      shaderLayouts[shaderStageCnt].bindings[bindingIdx].binding.stageFlags =
        VK_SHADER_STAGE_FRAGMENT_BIT;
    }
    ++shaderStageCnt;
  }

  MergeShaderLayouts(shaderLayouts, shaderStageCnt, layout_);

  // vertex input

  VkVertexInputBindingDescription bindingDescriptions
    [PipelineState::VertexInputState::MAX_NUM_VERTEX_BINDINGS];
  VkVertexInputAttributeDescription attributeDescriptions
    [PipelineState::VertexInputState::MAX_NUM_VERTEX_ATTRIBUTES];

  for (uint32_t i = 0; i < pipeline_->state->vertexInput.bindingDescriptionCnt;
       ++i) {
    bindingDescriptions[i].binding =
      pipeline_->state->vertexInput.bindingDescriptions[i].binding;
    bindingDescriptions[i].inputRate = GetVkVertexInputRate(
      pipeline_->state->vertexInput.bindingDescriptions[i].inputRate);
    bindingDescriptions[i].stride =
      pipeline_->state->vertexInput.bindingDescriptions[i].stride;
  }

  for (uint32_t i = 0;
       i < pipeline_->state->vertexInput.attributeDescriptionCnt;
       ++i) {
    attributeDescriptions[i].binding =
      pipeline_->state->vertexInput.attributeDescriptions[i].binding;
    attributeDescriptions[i].format = GetVkFormat(
      pipeline_->state->vertexInput.attributeDescriptions[i].format);
    attributeDescriptions[i].location =
      pipeline_->state->vertexInput.attributeDescriptions[i].location;
    attributeDescriptions[i].offset =
      pipeline_->state->vertexInput.attributeDescriptions[i].offset;
  }

  auto vertexInputState = vkiPipelineVertexInputStateCreateInfo(
    pipeline_->state->vertexInput.bindingDescriptionCnt,
    bindingDescriptions,
    pipeline_->state->vertexInput.attributeDescriptionCnt,
    attributeDescriptions);

  // input assembly

  auto inputAssemblyCreateInfo = vkiPipelineInputAssemblyStateCreateInfo(
    GetVkPrimitiveTopology(pipeline_->state->inputAssembly.topology),
    pipeline_->state->inputAssembly.primitiveRestartEnable);

  // tesselation

  auto tesselationState = vkiPipelineTessellationStateCreateInfo(0);

  // viewport

  VkViewport viewport;
  viewport.x = pipeline_->state->viewport.viewport.x;
  viewport.y = pipeline_->state->viewport.viewport.y;
  viewport.width = pipeline_->state->viewport.viewport.width;
  viewport.height = pipeline_->state->viewport.viewport.height;
  viewport.minDepth = pipeline_->state->viewport.viewport.minDepth;
  viewport.maxDepth = pipeline_->state->viewport.viewport.maxDepth;

  VkRect2D rect;
  rect.offset.x = pipeline_->state->viewport.scissors.x;
  rect.offset.y = pipeline_->state->viewport.scissors.y;
  rect.extent.width = pipeline_->state->viewport.scissors.width;
  rect.extent.height = pipeline_->state->viewport.scissors.height;

  auto viewportState =
    vkiPipelineViewportStateCreateInfo(1, &viewport, 1, &rect);

  // rasterization

  auto rasterizationState = vkiPipelineRasterizationStateCreateInfo(
    false,
    false,
    GetVkPolygonMode(pipeline_->state->rasterization.polygonMode),
    GetVkCullModeFlags(pipeline_->state->rasterization.cullMode),
    GetVkFrontFace(pipeline_->state->rasterization.frontFace),
    false,
    0.0,
    0.0,
    0.0,
    1.0);

  // multisample

  auto multisamleState = vkiPipelineMultisampleStateCreateInfo(
    GetVkSampleCountFlagBits(
      pipeline_->state->multisample.rasterizationSamples),
    false,
    1.0,
    nullptr,
    false,
    false);

  // depth stencil

  auto depthStencilState = vkiPipelineDepthStencilStateCreateInfo(
    pipeline_->state->depthStencil.depthTestenable,
    pipeline_->state->depthStencil.depthWriteEnable,
    GetVkCompareOp(pipeline_->state->depthStencil.depthCompareOp),
    false,
    pipeline_->state->depthStencil.stencilTestEnable,
    GetVkStencilOpState(pipeline_->state->depthStencil.front),
    GetVkStencilOpState(pipeline_->state->depthStencil.back),
    0.0,
    1.0);

  // blend

  VkColorComponentFlags colorComponentFlags =
    VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
    VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

  VkPipelineColorBlendAttachmentState blendAttachments[8];
  blendAttachments[0] = vkiPipelineColorBlendAttachmentState(
    pipeline_->state->blend.enable,
    GetVkBlendFactor(pipeline_->state->blend.srcColorFactor),
    GetVkBlendFactor(pipeline_->state->blend.dstColorFactor),
    static_cast<VkBlendOp>(pipeline_->state->blend.colorOp),
    GetVkBlendFactor(pipeline_->state->blend.srcAlphaFactor),
    GetVkBlendFactor(pipeline_->state->blend.dstAlphaFactor),
    static_cast<VkBlendOp>(pipeline_->state->blend.alphaOp),
    colorComponentFlags);

  VkPipelineColorBlendStateCreateInfo blendState = {};
  blendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  blendState.pNext = nullptr;
  blendState.flags = 0;
  blendState.logicOp = VK_LOGIC_OP_CLEAR;
  blendState.logicOpEnable = false;
  blendState.blendConstants[0] = 0.0;
  blendState.blendConstants[1] = 0.0;
  blendState.blendConstants[2] = 0.0;
  blendState.blendConstants[3] = 0.0;
  blendState.attachmentCount = 1;
  blendState.pAttachments = blendAttachments;

  // dynamic state

  // VkDynamicState dynamicStates[2] = {VK_DYNAMIC_STATE_VIEWPORT,
  //                                   VK_DYNAMIC_STATE_SCISSOR};

  // auto dynamicState = vkiPipelineDynamicStateCreateInfo(2, dynamicStates);

  auto dynamicState = vkiPipelineDynamicStateCreateInfo(0, nullptr);

  //

  auto layout = GetPipelineLayout(res, layout_);

  auto pipelineCreateInfo =
    vkiGraphicsPipelineCreateInfo(shaderStageCnt,
                                  shaderStageCreateInfos,
                                  &vertexInputState,
                                  &inputAssemblyCreateInfo,
                                  &tesselationState,
                                  &viewportState,
                                  &rasterizationState,
                                  &multisamleState,
                                  &depthStencilState,
                                  &blendState,
                                  &dynamicState,
                                  layout,
                                  pipeline_->renderPass,
                                  pipeline_->subpass,
                                  VK_NULL_HANDLE,
                                  0);

  VkPipeline pipeline = VK_NULL_HANDLE;
  vkCreateGraphicsPipelines(
    res->device, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &pipeline);

  res->pipelines.insert({ h, { pipeline, *layout_ } });

  return pipeline;
}

VkSampler
GetSampler(StaticResources* res)
{
  auto h = hash(nullptr, 0);

  auto it = res->samplers.find(h);
  if (it != res->samplers.end()) {
    return it->second;
  }

  VkSampler sampler = VK_NULL_HANDLE;
  auto createInfo = vkiSamplerCreateInfo(VK_FILTER_NEAREST,
                                         VK_FILTER_NEAREST,
                                         VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                         VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                         VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                         VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                         0.f,
                                         VK_FALSE,
                                         0.f,
                                         VK_FALSE,
                                         VK_COMPARE_OP_NEVER,
                                         0.f,
                                         0.f,
                                         VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
                                         VK_FALSE);
  vkCreateSampler(res->device, &createInfo, nullptr, &sampler);

  res->samplers.insert({ h, sampler });
  return sampler;
}

VkDescriptorSet
AllocateDescriptorSet(ResourceArenaAllocator* arena,
                      DescriptorSetLayout const* layout_)
{
  auto layout = GetDescriptorSetLayout(arena->staticResources, layout_);

  auto it = arena->allocated.descriptorPools.find(layout);

  if (it != arena->allocated.descriptorPools.end()) {
    assert(!it->second.pools.empty());
    auto& pool = it->second.pools.back();
    if (pool.allocCnt < DescriptorSetPool::MAX_NUM_SETS) {
      return pool.sets[pool.allocCnt++];
    }
  }

  it = arena->free.descriptorPools.find(layout);

  if (it != arena->free.descriptorPools.end()) {
    assert(!it->second.pools.empty());
    auto pool = std::move(it->second.pools.back());
    it->second.pools.pop_back();
    if (it->second.pools.empty()) {
      arena->free.descriptorPools.erase(it);
    }
    assert(pool.allocCnt == 0);
    auto set = pool.sets[pool.allocCnt++];
    arena->allocated.descriptorPools[layout].pools.emplace_back(
      std::move(pool));
    return set;
  }

  enum
  {
    MAX_NUM_DESCRIPTOR_TYPES = 11
  };

  VkDescriptorPoolSize poolSizes[MAX_NUM_DESCRIPTOR_TYPES] = {};
  uint32_t poolSizeCnt = 0;

  for (uint32_t type = 0; type < MAX_NUM_DESCRIPTOR_TYPES; ++type) {
    auto dtype = static_cast<VkDescriptorType>(type);
    bool found = false;

    for (uint32_t binding = 0; binding < layout_->bindingCnt; ++binding) {
      if (layout_->bindings[binding].descriptorType == dtype) {
        poolSizes[poolSizeCnt].type = dtype;
        poolSizes[poolSizeCnt].descriptorCount +=
          DescriptorSetPool::MAX_NUM_SETS;
        found = true;
      }
    }

    if (found) {
      poolSizeCnt += 1;
    }
  }

  auto createInfo = vkiDescriptorPoolCreateInfo(
    DescriptorSetPool::MAX_NUM_SETS, poolSizeCnt, poolSizes);

  VkDescriptorPool pool = VK_NULL_HANDLE;
  vkCreateDescriptorPool(arena->device, &createInfo, nullptr, &pool);
  DescriptorSetPool setPool = {};
  setPool.pool = pool;
  setPool.allocCnt = 0;

  VkDescriptorSetLayout layouts[DescriptorSetPool::MAX_NUM_SETS];
  for (uint32_t i = 0; i < DescriptorSetPool::MAX_NUM_SETS; ++i) {
    layouts[i] = layout;
  }

  auto allocInfo = vkiDescriptorSetAllocateInfo(
    pool, DescriptorSetPool::MAX_NUM_SETS, layouts);
  vkAllocateDescriptorSets(arena->device, &allocInfo, setPool.sets);

  auto set = setPool.sets[setPool.allocCnt++];

  arena->allocated.descriptorPools[layout].pools.emplace_back(setPool);

  return set;
}

VkCommandPool
AllocateCommandPool(ResourceArenaAllocator* arena, uint32_t queueFamilyIdx)
{
  // TODO: reuse command pools: the problem is, that we cannot free all command
  // buffers allocated from a pool at once, so we also need to keep track of all
  // allocated command buffers; This is not hard, but I don't feel like doing
  // this right now.

  // auto it = arena->free.cmdPools.find(queueFamilyIdx);
  // if (it != arena->free.cmdPools.end()) {
  //  assert(!it->second.pools.empty());
  //  auto pool = it->second.pools.back();
  //  it->second.pools.pop_back();
  //  arena->free.resourceCnt--;
  //  if (it->second.pools.empty()) {
  //    arena->free.cmdPools.erase(it);
  //  }

  //  arena->allocated.cmdPools[queueFamilyIdx].pools.push_back(pool);
  //  return pool;
  //}

  auto createInfo = vkiCommandPoolCreateInfo(queueFamilyIdx);
  VkCommandPool pool = VK_NULL_HANDLE;
  vkCreateCommandPool(arena->device, &createInfo, nullptr, &pool);

  arena->allocated.cmdPools[queueFamilyIdx].pools.push_back(pool);

  return pool;
}

void
ClaimResources(ResourceArenaAllocator* arena)
{
  if (arena->fence != VK_NULL_HANDLE &&
      vkGetFenceStatus(arena->device, arena->fence) == VK_NOT_READY) {
    return;
  }

  if (arena->fence != VK_NULL_HANDLE) {
    ReleaseFence(arena->resourceAllocator, arena->fence);
    arena->fence = VK_NULL_HANDLE;

    for (auto& kv : arena->pending.descriptorPools) {
      auto layout = kv.first;
      auto& poolList = kv.second;
      for (auto& pool : poolList.pools) {
        pool.allocCnt = 0;
        arena->free.descriptorPools[layout].pools.emplace_back(std::move(pool));
      }
    }

    arena->pending.descriptorPools.clear();

    for (auto const& kv : arena->pending.cmdPools) {
      for (auto pool : kv.second.pools) {
        vkDestroyCommandPool(arena->device, pool, nullptr);
        // arena->free.cmdPools[kv.first].pools.push_back(pool);
      }
    }

    arena->pending.cmdPools.clear();
  }

  arena->pending = std::move(arena->allocated);
  arena->fence = AllocateFence(arena->resourceAllocator);

  vkQueueSubmit(arena->queue, 0, nullptr, arena->fence);
}

VkEvent
AllocateEvent(ResourceAllocator* al)
{
  if (!al->free.events.empty()) {
    auto event = al->free.events.back();
    al->free.events.pop_back();
    al->free.resourceCnt--;
    return event;
  }

  auto createInfo = vkiEventCreateInfo();
  VkEvent event = VK_NULL_HANDLE;
  vkCreateEvent(al->device, &createInfo, nullptr, &event);
  al->totalResourceCnt++;
  return event;
}

void
ReleaseEvent(ResourceAllocator* al, VkEvent event)
{
  al->released.events.push_back(event);
  al->released.resourceCnt++;
}

VkSemaphore
AllocateSemaphore(ResourceAllocator* al)
{
  if (!al->free.semaphores.empty()) {
    auto sem = al->free.semaphores.back();
    al->free.semaphores.pop_back();
    al->free.resourceCnt--;
    return sem;
  }

  auto createInfo = vkiSemaphoreCreateInfo();
  VkSemaphore sem = VK_NULL_HANDLE;
  vkCreateSemaphore(al->device, &createInfo, nullptr, &sem);
  al->totalResourceCnt++;
  return sem;
}

void
ReleaseSemaphore(ResourceAllocator* al, VkSemaphore sem)
{
  al->released.semaphores.push_back(sem);
  al->released.resourceCnt++;
}

VkFence
AllocateFence(ResourceAllocator* al)
{
  if (!al->free.fences.empty()) {
    auto sem = al->free.fences.back();
    al->free.fences.pop_back();
    al->free.resourceCnt--;
    return sem;
  }

  auto createInfo = vkiFenceCreateInfo();
  VkFence fence = VK_NULL_HANDLE;
  vkCreateFence(al->device, &createInfo, nullptr, &fence);
  al->totalResourceCnt++;
  return fence;
}

void
ReleaseFence(ResourceAllocator* al, VkFence fence)
{
  al->released.fences.push_back(fence);
  al->released.resourceCnt++;
}

void
ClaimResources(ResourceAllocator* al)
{
  if (al->fence != VK_NULL_HANDLE &&
      vkGetFenceStatus(al->device, al->fence) == VK_NOT_READY) {
    return;
  }

  if (al->fence != VK_NULL_HANDLE) {
    ReleaseFence(al, al->fence);
    al->fence = VK_NULL_HANDLE;

    for (auto event : al->pending.events) {
      vkResetEvent(al->device, event);
      al->free.events.push_back(event);
    }
    al->pending.events.clear();

    for (auto sem : al->pending.semaphores)
      al->free.semaphores.push_back(sem);
    al->pending.semaphores.clear();

    if (!al->pending.fences.empty()) {
      vkResetFences(al->device,
                    static_cast<uint32_t>(al->pending.fences.size()),
                    al->pending.fences.data());
    }

    for (auto fence : al->pending.fences)
      al->free.fences.push_back(fence);
    al->pending.fences.clear();

    al->free.resourceCnt += al->pending.resourceCnt;
    al->pending.resourceCnt = 0;
  }

  if (al->released.resourceCnt > 0) {
    assert(al->fence == VK_NULL_HANDLE);
    al->fence = AllocateFence(al);
    al->pending = std::move(al->released);
    al->released.resourceCnt = 0;
    vkQueueSubmit(al->queue, 0, nullptr, al->fence);
  }
}

void
PrintStats(ResourceAllocator* al)
{
  printf("Allocator: total %u, free %u, returned %u\n",
         al->totalResourceCnt,
         al->free.resourceCnt,
         al->pending.resourceCnt + al->pending.resourceCnt);
}
