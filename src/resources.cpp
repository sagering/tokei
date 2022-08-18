#include "resources.h"

#include <assert.h>
#include <spirv_cross/spirv_cross.hpp>

#include "vk_init.h"

VkRenderPass createRenderPass(VkDevice device,
                              RenderPassInternal const *renderPass)
{
  auto createInfo = vkiRenderPassCreateInfo(
      renderPass->attachmentCnt, renderPass->attachments,
      renderPass->subpassCnt, renderPass->subpassess, renderPass->dependencyCnt,
      renderPass->dependencies);

  VkRenderPass ret = VK_NULL_HANDLE;
  vkCreateRenderPass(device, &createInfo, nullptr, &ret);

  return ret;
}

VkFramebuffer createFramebuffer(VkDevice device,
                                Framebuffer const *framebuffer)
{
  auto createInfo = vkiFramebufferCreateInfo(
      framebuffer->renderPass, framebuffer->attachmentCnt,
      framebuffer->attachments, framebuffer->width, framebuffer->height,
      framebuffer->layers);

  VkFramebuffer ret = VK_NULL_HANDLE;
  vkCreateFramebuffer(device, &createInfo, nullptr, &ret);

  return ret;
}

VkDescriptorSetLayout
createDescriptorSetLayout(VkDevice device, DescriptorSetLayout const *layout)
{
  auto createInfo =
      vkiDescriptorSetLayoutCreateInfo(layout->bindingCnt, layout->bindings);

  VkDescriptorSetLayout ret = VK_NULL_HANDLE;
  vkCreateDescriptorSetLayout(device, &createInfo, nullptr, &ret);

  return ret;
}

VkPipelineLayout createPipelineLayout(VkDevice device,
                                      PipelineLayout const *layout)
{
  VkDescriptorSetLayout dlayouts[PipelineLayout::MAX_NUM_DESCRIPTOR_SETS];

  for (uint32_t set = 0; set < layout->layoutCnt; ++set)
  {
    dlayouts[set] = createDescriptorSetLayout(device, &layout->layouts[set]);
  }

  auto createInfo =
      vkiPipelineLayoutCreateInfo(layout->layoutCnt, dlayouts, 0, nullptr);

  VkPipelineLayout ret = VK_NULL_HANDLE;
  vkCreatePipelineLayout(device, &createInfo, nullptr, &ret);

  return ret;
}

uint32_t *load(char const *filepath, uint32_t *size)
{
  uint32_t *code;

  FILE *file = 0;
  fopen_s(&file, filepath, "rb");

  if (!file)
  {
    return nullptr;
  }

  fseek(file, 0, SEEK_END);
  size_t bytes = ftell(file);

  code = new uint32_t[bytes / 4];

  fseek(file, 0, SEEK_SET);
  fread(code, 1, bytes, file);
  fclose(file);

  *size = bytes / 4;

  return code;
}

VkShaderModule createShaderModule(VkDevice device, char const *filepath)
{
  uint32_t size = 0;
  auto code = load(filepath, &size);

  auto createInfo = vkiShaderModuleCreateInfo(size * 4, code);

  VkShaderModule ret = VK_NULL_HANDLE;
  vkCreateShaderModule(device, &createInfo, nullptr, &ret);

  return ret;
}

bool readDescriptorCount(const spirv_cross::SPIRType &type, uint32_t &cnt)
{
  if (type.array.size() == 0)
  {
    cnt = 1;
    return true;
  }

  if (type.array.size() > 1)
  {
    return false; // vulkan only supports single array level for descriptors.
  }

  if (!type.array_size_literal.back())
  {
    return false; // size cannot be statically resolved
  }

  if (type.array.back() == 0)
  {
    return false; // avoid bindless complexity
  }

  cnt = type.array.back();
  return true;
}

bool reflectDescriptor(const spirv_cross::Compiler &comp,
                       const spirv_cross::Resource &res, ShaderLayout &layout)
{
  uint32_t set = comp.get_decoration(res.id, spv::DecorationDescriptorSet);
  uint32_t binding = comp.get_decoration(res.id, spv::DecorationBinding);
  uint32_t count = 0;

  if (!readDescriptorCount(comp.get_type(res.type_id), count))
  {
    return false;
  }

  if (binding >= ShaderLayout::MAX_NUM_DESCRIPTOR_SET_LAYOUT_BINDINGS)
  {
    return false;
  }

  layout.bindings[layout.bindingCnt].set = set;
  layout.bindings[layout.bindingCnt].binding =
      VkDescriptorSetLayoutBinding{binding, {}, count, 0, nullptr};

  return true;
}

bool reflectLayout(uint32_t const *code, uint32_t size,
                   VkShaderStageFlags stage, ShaderLayout &layout)
{
  spirv_cross::Compiler comp(code, size);

  auto resources = comp.get_shader_resources();

  // sampler2D
  for (auto &res : resources.sampled_images)
  {
    if (!reflectDescriptor(comp, res, layout))
    {
      return false;
    }

    layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    ++layout.bindingCnt;
  }

  // texture2D or samplerBuffer
  for (auto &res : resources.separate_images)
  {
    auto type = comp.get_type(res.base_type_id);
    if (type.image.dim == spv::DimBuffer)
    {
      if (!reflectDescriptor(comp, res, layout))
      {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
          VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
      ++layout.bindingCnt;
    }
    else
    {
      if (!reflectDescriptor(comp, res, layout))
      {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
          VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
      ++layout.bindingCnt;
    }
  }

  // image2D or imageBuffer
  for (auto &res : resources.storage_images)
  {
    auto type = comp.get_type(res.base_type_id);
    if (type.image.dim == spv::DimBuffer)
    {
      if (!reflectDescriptor(comp, res, layout))
      {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
          VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
      ++layout.bindingCnt;
    }
    else
    {
      if (!reflectDescriptor(comp, res, layout))
      {
        return false;
      }
      layout.bindings[layout.bindingCnt].binding.descriptorType =
          VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
      ++layout.bindingCnt;
    }
  }

  // sampler
  for (auto &res : resources.separate_samplers)
  {
    if (!reflectDescriptor(comp, res, layout))
    {
      return false;
    }
    layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_SAMPLER;
    ++layout.bindingCnt;
  }

  // uniform UBO {}
  for (auto &res : resources.uniform_buffers)
  {
    if (!reflectDescriptor(comp, res, layout))
    {
      return false;
    }
    layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    ++layout.bindingCnt;
  }

  // layout(push_constant) uniform Push
  if (resources.push_constant_buffers.size() > 0)
  {
    auto &res = resources.push_constant_buffers.back();

    layout.pushConstantRanges[0].offset = 0;
    layout.pushConstantRanges[0].size = static_cast<uint32_t>(
        comp.get_declared_struct_size(comp.get_type(res.type_id)));
    layout.pushConstantRanges[0].stageFlags = stage;
    layout.pushConstantRangeCount += 1;
  }

  for (auto &res : resources.subpass_inputs)
  {
    layout.inputAttachmentMask |=
        1 << comp.get_decoration(res.id, spv::DecorationInputAttachmentIndex);
  }

  if (stage == VK_SHADER_STAGE_VERTEX_BIT)
  {
    for (auto &res : resources.stage_inputs)
    {
      layout.inputLocationMask |=
          1 << comp.get_decoration(res.id, spv::DecorationLocation);
    }
  }

  if (stage == VK_SHADER_STAGE_FRAGMENT_BIT)
  {
    for (auto &res : resources.stage_outputs)
    {
      layout.outputLocationMask |=
          1 << comp.get_decoration(res.id, spv::DecorationLocation);
    }
  }

  // buffer SSBO {}
  for (auto &res : resources.storage_buffers)
  {
    if (!reflectDescriptor(comp, res, layout))
    {
      return false;
    }
    layout.bindings[layout.bindingCnt].binding.descriptorType =
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
    ++layout.bindingCnt;
  }

  return true;
}

bool mergeShaderLayouts(ShaderLayout const *layouts, uint32_t layoutCnt,
                        PipelineLayout *pipelineLayout)
{
  for (auto i = 0; i < PipelineLayout::MAX_NUM_DESCRIPTOR_SETS; ++i)
  {
    for (auto j = 0; j < DescriptorSetLayout::MAX_NUM_DESCRIPTOR_SET_BINDINGS;
         ++j)
    {
      pipelineLayout->layouts[i].bindings[j].binding = j;
    }
  }

  for (uint32_t layoutIdx = 0; layoutIdx < layoutCnt; ++layoutIdx)
  {
    ShaderLayout const &layout = layouts[layoutIdx];
    for (uint32_t bindingIdx = 0; bindingIdx < layout.bindingCnt;
         ++bindingIdx)
    {
      auto const set = layout.bindings[bindingIdx].set;
      auto const binding = layout.bindings[bindingIdx].binding.binding;

      if (set >= PipelineLayout::MAX_NUM_DESCRIPTOR_SETS)
      {
        return false;
      }

      if (binding >= DescriptorSetLayout::MAX_NUM_DESCRIPTOR_SET_BINDINGS)
      {
        return false;
      }

      pipelineLayout->layoutCnt = std::max(pipelineLayout->layoutCnt, set + 1);
      pipelineLayout->layouts[set].bindingCnt =
          std::max(pipelineLayout->layouts[set].bindingCnt, binding + 1);

      if (pipelineLayout->layouts[set].bindings[binding].stageFlags == 0)
      {
        pipelineLayout->layouts[set].bindings[binding] =
            layout.bindings[bindingIdx].binding;
      }
      else
      {
        // make sure thate descriptor bindings of different shader stages are
        // compatible
        if (pipelineLayout->layouts[set].bindings[binding].descriptorCount !=
            layout.bindings[bindingIdx].binding.descriptorCount)
        {
          return false;
        }

        if (pipelineLayout->layouts[set].bindings[binding].descriptorType !=
            layout.bindings[bindingIdx].binding.descriptorType)
        {
          return false;
        }

        pipelineLayout->layouts[set].bindings[binding].stageFlags |=
            layout.bindings[bindingIdx].binding.stageFlags;
      }
    }
  }

  return true;
}

ShaderLayout createShaderLayout(char const *filepath)
{
  uint32_t size = 0;
  auto code = load(filepath, &size);

  ShaderLayout layout;
  reflectLayout(code, size, 0, layout);

  return layout;
}

PipelineLayout createPipelineLayout(ShaderLayout *shaderLayouts,
                                    VkShaderStageFlagBits const *stageFlags,
                                    uint32_t cnt)
{
  PipelineLayout ret = {};

  for (uint32_t i = 0; i < cnt; ++i)
  {
    for (uint32_t bindingIdx = 0; bindingIdx < shaderLayouts[i].bindingCnt;
         ++bindingIdx)
    {
      shaderLayouts[i].bindings[bindingIdx].binding.stageFlags = stageFlags[i];
    }
  }

  mergeShaderLayouts(shaderLayouts, cnt, &ret);

  return ret;
}

VkPipeline createComputePipeline(VkDevice device, VkShaderModule shaderModule,
                                 VkPipelineLayout layout)
{
  auto shaderStageCreateInfo = vkiPipelineShaderStageCreateInfo(
      VK_SHADER_STAGE_COMPUTE_BIT, shaderModule, "main", nullptr);

  auto createInfo = vkiComputePipelineCreateInfo(shaderStageCreateInfo, layout,
                                                 VK_NULL_HANDLE, 0);

  VkPipeline pipeline = VK_NULL_HANDLE;
  vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &createInfo, nullptr,
                           &pipeline);

  return pipeline;
}

VkPipeline createGraphicsPipeline(VkDevice device,
                                  VkShaderModule *shaderModules,
                                  VkShaderStageFlagBits *stageFlags,
                                  uint32_t shaderModuleCnt,
                                  VkPipelineLayout layout,
                                  GraphicsPipelineState const *pipeline,
                                  VkRenderPass renderPass, uint32_t subpass)
{
  // shader
  VkPipelineShaderStageCreateInfo shaderStageCreateInfos[2];

  for (uint32_t i = 0; i < shaderModuleCnt; ++i)
  {
    shaderStageCreateInfos[i] = vkiPipelineShaderStageCreateInfo(
        stageFlags[i], shaderModules[i], "main", nullptr);
  }

  // vertex input
  VkVertexInputBindingDescription bindingDescriptions
      [GraphicsPipelineState::VertexInputState::MAX_NUM_VERTEX_BINDINGS];
  VkVertexInputAttributeDescription attributeDescriptions
      [GraphicsPipelineState::VertexInputState::MAX_NUM_VERTEX_ATTRIBUTES];

  for (uint32_t i = 0; i < pipeline->vertexInput.bindingDescriptionCnt; ++i)
  {
    bindingDescriptions[i].binding =
        pipeline->vertexInput.bindingDescriptions[i].binding;
    bindingDescriptions[i].inputRate =
        pipeline->vertexInput.bindingDescriptions[i].inputRate;
    bindingDescriptions[i].stride =
        pipeline->vertexInput.bindingDescriptions[i].stride;
  }

  for (uint32_t i = 0; i < pipeline->vertexInput.attributeDescriptionCnt; ++i)
  {
    attributeDescriptions[i].binding =
        pipeline->vertexInput.attributeDescriptions[i].binding;
    attributeDescriptions[i].format =
        pipeline->vertexInput.attributeDescriptions[i].format;
    attributeDescriptions[i].location =
        pipeline->vertexInput.attributeDescriptions[i].location;
    attributeDescriptions[i].offset =
        pipeline->vertexInput.attributeDescriptions[i].offset;
  }

  auto vertexInputState = vkiPipelineVertexInputStateCreateInfo(
      pipeline->vertexInput.bindingDescriptionCnt, bindingDescriptions,
      pipeline->vertexInput.attributeDescriptionCnt, attributeDescriptions);

  // input assembly
  auto inputAssemblyCreateInfo = vkiPipelineInputAssemblyStateCreateInfo(
      pipeline->inputAssembly.topology,
      pipeline->inputAssembly.primitiveRestartEnable);

  // tesselation
  auto tesselationState = vkiPipelineTessellationStateCreateInfo(0);

  // viewport
  VkViewport viewport;
  viewport.x = pipeline->viewport.viewport.x;
  viewport.y = pipeline->viewport.viewport.y;
  viewport.width = pipeline->viewport.viewport.width;
  viewport.height = pipeline->viewport.viewport.height;
  viewport.minDepth = pipeline->viewport.viewport.minDepth;
  viewport.maxDepth = pipeline->viewport.viewport.maxDepth;

  auto viewportState = vkiPipelineViewportStateCreateInfo(
      1, &viewport, 1, &pipeline->viewport.scissors);

  // rasterization
  auto rasterizationState = vkiPipelineRasterizationStateCreateInfo(
      false, false, pipeline->rasterization.polygonMode,
      pipeline->rasterization.cullMode, pipeline->rasterization.frontFace,
      false, 0.0, 0.0, 0.0, 1.0);

  // multisample
  auto multisamleState = vkiPipelineMultisampleStateCreateInfo(
      pipeline->multisample.rasterizationSamples, false, 1.0, nullptr, false,
      false);

  // depth stencil
  auto depthStencilState = vkiPipelineDepthStencilStateCreateInfo(
      pipeline->depthStencil.depthTestenable,
      pipeline->depthStencil.depthWriteEnable,
      pipeline->depthStencil.depthCompareOp, false,
      pipeline->depthStencil.stencilTestEnable, pipeline->depthStencil.front,
      pipeline->depthStencil.back, 0.0, 1.0);

  // blend
  VkColorComponentFlags colorComponentFlags =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

  VkPipelineColorBlendAttachmentState blendAttachments[8];
  blendAttachments[0] = vkiPipelineColorBlendAttachmentState(
      pipeline->blend.enable, pipeline->blend.srcColorFactor,
      pipeline->blend.dstColorFactor, pipeline->blend.colorOp,
      pipeline->blend.srcAlphaFactor, pipeline->blend.dstAlphaFactor,
      pipeline->blend.alphaOp, colorComponentFlags);

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

  auto pipelineCreateInfo = vkiGraphicsPipelineCreateInfo(
      shaderModuleCnt, shaderStageCreateInfos, &vertexInputState,
      &inputAssemblyCreateInfo, &tesselationState, &viewportState,
      &rasterizationState, &multisamleState, &depthStencilState, &blendState,
      &dynamicState, layout, renderPass, subpass, VK_NULL_HANDLE, 0);

  VkPipeline ret = VK_NULL_HANDLE;
  vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineCreateInfo,
                            nullptr, &ret);

  return ret;
}

VkSampler createSampler(VkDevice device)
{
  VkSampler sampler = VK_NULL_HANDLE;
  auto createInfo = vkiSamplerCreateInfo(
      VK_FILTER_NEAREST, VK_FILTER_NEAREST, VK_SAMPLER_MIPMAP_MODE_LINEAR,
      VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT,
      VK_SAMPLER_ADDRESS_MODE_REPEAT, 0.f, VK_FALSE, 0.f, VK_FALSE,
      VK_COMPARE_OP_NEVER, 0.f, 0.f, VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
      VK_FALSE);

  vkCreateSampler(device, &createInfo, nullptr, &sampler);

  return sampler;
}
