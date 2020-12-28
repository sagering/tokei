#include "vulkan_device.h"

#include "vulkan_resources.h"
#include "vulkan_types.h"

#include <algorithm>
#include <assert.h>

//#define PRINT_SYNC_CMD

char* const
getImageLayoutName(VkImageLayout layout)
{
  if (layout == VK_IMAGE_LAYOUT_UNDEFINED)
    return "VK_IMAGE_LAYOUT_UNDEFINED";
  if (layout == VK_IMAGE_LAYOUT_GENERAL)
    return "VK_IMAGE_LAYOUT_GENERAL";
  if (layout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
    return "VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
    return "VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL)
    return "VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    return "VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
    return "VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    return "VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_PREINITIALIZED)
    return "VK_IMAGE_LAYOUT_PREINITIALIZED";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL)
    return "VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL)
    return "VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL)
    return "VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL)
    return "VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL)
    return "VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL)
    return "VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL";
  if (layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
    return "VK_IMAGE_LAYOUT_PRESENT_SRC_KHR";
  if (layout == VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR)
    return "VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR";
  if (layout == VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV)
    return "VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV";
  if (layout == VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT)
    return "VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR)
    return "VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR)
    return "VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR)
    return "VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR";
  if (layout == VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR)
    return "VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR";
  if (layout == VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR)
    return "VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR";
  if (layout == VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR)
    return "VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR";
  return "";
};

void
SynchronizationInfo::Coalesce(void* res, ResourceType resType, AccessScope prev)
{
  struct OperationRange
  {
    Operation op;
    uint32_t start; // inclusive
    uint32_t end;   // exclusive
  };

  if (ops.size() == 0) {
    return;
  }

  std::vector<OperationRange> ranges;
  ranges.reserve(ops.size());
  ranges.push_back({ ops[0], 0u, static_cast<uint32_t>(ops.size()) });

  for (uint32_t j = 1; j < ops.size(); ++j) {
    auto& currRange = ranges.back();
    if (!ops[j].scope.ReadOnly() || !currRange.op.scope.ReadOnly() ||
        ops[j].scope.initialLayout != currRange.op.scope.finalLayout) {
      currRange.end = j;
      ranges.push_back({ ops[j], j, static_cast<uint32_t>(ops.size()) });
    } else {
      currRange.op.scope.stageFlags |= ops[j].scope.stageFlags;
      currRange.op.scope.accessFlags |= ops[j].scope.accessFlags;
    }
  }

  firstScope = ranges.front().op.scope;
  firstCmd = ops[ranges.front().start].cmd;

  lastScope = ranges.back().op.scope;
  lastCmd = ops[ranges.back().end - 1].cmd;

  for (uint32_t i = 1; i < ranges.size(); ++i) {
    AccessScope waitSrc = ranges[i - 1].op.scope;
    AccessScope waitDst = ranges[i].op.scope;

    { // Wait event
      auto waitCmd = ops[ranges[i].start].cmd;
      auto syncCmd = &waitCmd->syncCmds[waitCmd->syncCmdCnt];

      syncCmd->pars.first = waitSrc;
      syncCmd->pars.second = waitDst;
      syncCmd->code = SyncCmdCode::WAIT_EVENT;
      syncCmd->pars.res = res;
      syncCmd->pars.resType = resType;

      waitCmd->syncCmdCnt++;
    }

    { // set event
      auto setCmd = ops[ranges[i - 1].end - 1].cmd;
      auto syncCmd = &setCmd->syncCmds[setCmd->syncCmdCnt];

      syncCmd->pars.first = waitSrc;
      syncCmd->code = SyncCmdCode::SET_EVENT;
      syncCmd->pars.res = res;
      syncCmd->pars.resType = resType;

      setCmd->syncCmdCnt++;
    }
  }
}

void
VulkanCmdBuffer::PushOp(AccessScope scope, SynchronizationInfo& syncInfo)
{
  Operation op = { scope, &data.cmds.back(), data.passes.back().id };
  syncInfo.ops.push_back(op);
}

void
VulkanCmdBuffer::BeginCopyPass()
{
  Cmd cmd = { CmdCode::BEGIN_COPY_PASS };
  data.cmds.push_back(cmd);
  data.passes.push_back({ data.passes.size() - 1,
                           PassType::COPY,
                           static_cast<int>(data.cmds.size() - 1),
                           0 });
}

void
VulkanCmdBuffer::Copy(Buffer dst, Buffer src)
{
  Cmd cmd = { CmdCode::COPY };
  cmd.pars.copy = { dst, src };
  data.cmds.push_back(cmd);
  PushOp(AccessScope::BufferTransferDst(), data.buffers[dst]);
  PushOp(AccessScope::BufferTransferSrc(), data.buffers[src]);
}

void
VulkanCmdBuffer::CopyBufferToTexture(Texture dst, Buffer src)
{
  Cmd cmd = { CmdCode::COPY_BUFFER_TO_TEXTURE };
  cmd.pars.copyBufferToTexture = { dst, src };
  data.cmds.push_back(cmd);
  PushOp(AccessScope::TextureTransferDst(), data.textures[dst]);
  PushOp(AccessScope::BufferTransferSrc(), data.buffers[src]);
}

void
VulkanCmdBuffer::EndCopyPass()
{
  Cmd cmd = { CmdCode::END_COPY_PASS };
  data.cmds.push_back(cmd);
  data.passes.back().endIdx = static_cast<int>(data.cmds.size()) - 1;
}

void
VulkanCmdBuffer::BeginRenderPass(RenderPassBeginInfo const& beginInfo)
{
  Cmd cmd = { CmdCode::BEGIN_RENDER_PASS };
  cmd.pars.beginRenderPassPars = beginInfo;
  data.cmds.push_back(cmd);

  data.passes.push_back({ data.passes.size() - 1,
                           PassType::RENDER,
                           static_cast<int>(data.cmds.size()) - 1,
                           0 });

  for (uint32_t i = 0; i < beginInfo.attachmentCnt; ++i) {
    auto const& info = beginInfo.attachmentInfos[i];
    switch (info.type) {
      case AttachmentType::COLOR: {
        auto scope = AccessScope::ColorOutputAttachment();
        if (info.makePresentable) {
          scope.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        }
        PushOp(scope, data.textures[info.texture]);
        break;
      }
      case AttachmentType::DEPTH: {
        PushOp(AccessScope::DepthStencilAttachment(),
               data.textures[info.texture]);
        break;
      }
      default:
        break;
    }
  }
}

void
VulkanCmdBuffer::BindVertexBuffer(Buffer vertexBuffer, uint64_t offset)
{
  Cmd cmd = { CmdCode::BIND_VERTEX_BUFFER };
  cmd.pars.bindVertexBuffer = { vertexBuffer, offset };
  data.cmds.push_back(cmd);
  PushOp(AccessScope::VertexBuffer(), data.buffers[vertexBuffer]);
}

void
VulkanCmdBuffer::BindIndexBuffer(Buffer indexBuffer)
{
  Cmd cmd = { CmdCode::BIND_INDEX_BUFFER };
  cmd.pars.bindIndexBuffer = { indexBuffer };
  data.cmds.push_back(cmd);
  PushOp(AccessScope::IndexBuffer(), data.buffers[indexBuffer]);
}

void
VulkanCmdBuffer::BindUniformBuffer(Buffer buffer,
                                   uint32_t set,
                                   uint32_t binding)
{
  Cmd cmd = { CmdCode::BIND_UNIFORM_BUFFER };
  cmd.pars.bindUniformBuffer = { buffer, set, binding };

  VkPipelineStageFlags stageFlags = 0;
  auto pipeline = &data.pipelineStates.back();

  if (pipeline->shader.vertexShader) {
    auto layout = GetShaderLayout(&data.device->staticResources,
                                  pipeline->shader.vertexShader);
    for (uint32_t bindingIdx = 0; bindingIdx < layout.bindingCnt;
         ++bindingIdx) {
      if (layout.bindings[bindingIdx].set == set &&
          layout.bindings[bindingIdx].binding.binding == binding) {
        stageFlags |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
        break;
      }
    }
  }
  if (pipeline->shader.fragmentShader) {
    auto layout = GetShaderLayout(&data.device->staticResources,
                                  pipeline->shader.fragmentShader);
    for (uint32_t bindingIdx = 0; bindingIdx < layout.bindingCnt;
         ++bindingIdx) {
      if (layout.bindings[bindingIdx].set == set &&
          layout.bindings[bindingIdx].binding.binding == binding) {
        stageFlags |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        break;
      }
    }
  }

  data.cmds.push_back(cmd);
  PushOp(AccessScope::UniformBuffer(stageFlags), data.buffers[buffer]);
}

void
VulkanCmdBuffer::BindSampler(uint32_t set, uint32_t binding)
{
  Cmd cmd = { CmdCode::BIND_SAMPLER };
  cmd.pars.bindSampler = { set, binding };
  data.cmds.push_back(cmd);
}

void
VulkanCmdBuffer::BindSampledTexture(Texture texture,
                                    uint32_t set,
                                    uint32_t binding)
{
  Cmd cmd = { CmdCode::BIND_SAMPLED_TEXTURE };
  cmd.pars.bindSampledTexture = { texture, set, binding };

  VkPipelineStageFlags stageFlags = 0;
  auto pipeline = &data.pipelineStates.back();

  if (pipeline->shader.vertexShader) {
    auto layout = GetShaderLayout(&data.device->staticResources,
                                  pipeline->shader.vertexShader);
    for (uint32_t bindingIdx = 0; bindingIdx < layout.bindingCnt;
         ++bindingIdx) {
      if (layout.bindings[bindingIdx].set == set &&
          layout.bindings[bindingIdx].binding.binding == binding) {
        stageFlags |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
        break;
      }
    }
  }

  if (pipeline->shader.fragmentShader) {
    auto layout = GetShaderLayout(&data.device->staticResources,
                                  pipeline->shader.fragmentShader);
    for (uint32_t bindingIdx = 0; bindingIdx < layout.bindingCnt;
         ++bindingIdx) {
      if (layout.bindings[bindingIdx].set == set &&
          layout.bindings[bindingIdx].binding.binding == binding) {
        stageFlags |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        break;
      }
    }
  }

  data.cmds.push_back(cmd);
  PushOp(AccessScope::Sampled(stageFlags), data.textures[texture]);
}

void
VulkanCmdBuffer::SetPipelineState(PipelineState pipelineState)
{
  Cmd cmd = { CmdCode::BIND_PIPELINE };
  data.pipelineStates.push_back(pipelineState);
  cmd.pars.pipelineState = &data.pipelineStates.back();
  data.cmds.push_back(cmd);
}

void
VulkanCmdBuffer::Draw(uint32_t cnt)
{
  Cmd cmd = { CmdCode::DRAW };
  cmd.pars.draw = { cnt };
  data.cmds.push_back(cmd);
}

void
VulkanCmdBuffer::DrawIndexed(uint32_t cnt)
{
  Cmd cmd = { CmdCode::DRAW_INDEXED };
  cmd.pars.drawIndexed = { cnt };
  data.cmds.push_back(cmd);
}

void
VulkanCmdBuffer::EndRenderPass()
{
  Cmd cmd = { CmdCode::END_RENDER_PASS };
  data.cmds.push_back(cmd);
  data.passes.back().endIdx = static_cast<int>(data.cmds.size()) - 1;
}

void
VulkanCmdBuffer::Wait(VkCommandBuffer cmdBuffer, Cmd const& cmd)
{
  assert(cmd.syncCmdCnt <= 4);

  if (cmd.syncCmdCnt == 0) {
    return;
  }

  for (uint32_t i = 0; i < cmd.syncCmdCnt; ++i) {
    auto const& syncCmd = cmd.syncCmds[i];

    if (syncCmd.code != SyncCmdCode::BARRIER &&
        syncCmd.code != SyncCmdCode::WAIT_EVENT) {
      continue;
    }

    switch (syncCmd.pars.resType) {
      case ResourceType::BUFFER: {
        auto info = (VulkanDevice::BufferInfo*)syncCmd.pars.res;
        auto bufferMemoryBarrier =
          vkiBufferMemoryBarrier(syncCmd.pars.first.accessFlags,
                                 syncCmd.pars.second.accessFlags,
                                 VK_QUEUE_FAMILY_IGNORED,
                                 VK_QUEUE_FAMILY_IGNORED,
                                 info->buffer,
                                 0,
                                 info->size);

        if (syncCmd.code == SyncCmdCode::BARRIER) {
          vkCmdPipelineBarrier(cmdBuffer,
                               syncCmd.pars.first.stageFlags,
                               syncCmd.pars.second.stageFlags,
                               VK_DEPENDENCY_BY_REGION_BIT,
                               0,
                               nullptr,
                               1,
                               &bufferMemoryBarrier,
                               0,
                               nullptr);
#ifdef PRINT_SYNC_CMD
          if (info->desc.name) {
            printf("BUFFER %s: BARRIER (%u, %u) -> (%u, %u)\n",
                   info->desc.name,
                   syncCmd.pars.first.stageFlags,
                   syncCmd.pars.first.accessFlags,
                   syncCmd.pars.second.stageFlags,
                   syncCmd.pars.second.accessFlags);
          }
#endif
        } else {
          assert(info->event != VK_NULL_HANDLE);
          vkCmdWaitEvents(cmdBuffer,
                          1,
                          &info->event,
                          syncCmd.pars.first.stageFlags,
                          syncCmd.pars.second.stageFlags,
                          0,
                          nullptr,
                          1,
                          &bufferMemoryBarrier,
                          0,
                          nullptr);
          ReleaseEvent(&data.device->allocator, info->event);
          info->event = VK_NULL_HANDLE;
#ifdef PRINT_SYNC_CMD
          if (info->desc.name) {
            printf("BUFFER %s: WAIT EVENT (%u, %u) -> (%u, %u)\n",
                   info->desc.name,
                   syncCmd.pars.first.stageFlags,
                   syncCmd.pars.first.accessFlags,
                   syncCmd.pars.second.stageFlags,
                   syncCmd.pars.second.accessFlags);
          }
#endif
        }

        break;
      }
      case ResourceType::TEXTURE: {
        auto info = (VulkanDevice::TextureInfo*)syncCmd.pars.res;
        auto imageMemoryBarrier =
          vkiImageMemoryBarrier(syncCmd.pars.first.accessFlags,
                                syncCmd.pars.second.accessFlags,
                                syncCmd.pars.first.finalLayout,
                                syncCmd.pars.second.initialLayout,
                                VK_QUEUE_FAMILY_IGNORED,
                                VK_QUEUE_FAMILY_IGNORED,
                                info->image,
                                info->subresource);

        if (syncCmd.code == SyncCmdCode::BARRIER) {
          vkCmdPipelineBarrier(cmdBuffer,
                               syncCmd.pars.first.stageFlags,
                               syncCmd.pars.second.stageFlags,
                               VK_DEPENDENCY_BY_REGION_BIT,
                               0,
                               nullptr,
                               0,
                               nullptr,
                               1,
                               &imageMemoryBarrier);
#ifdef PRINT_SYNC_CMD
          if (info->desc.name) {
            printf("TEXTURE %s: BARRIER (%u, %u, %s) -> (%u, %u, %s)\n",
                   info->desc.name,
                   syncCmd.pars.first.stageFlags,
                   syncCmd.pars.first.accessFlags,
                   getImageLayoutName(syncCmd.pars.first.finalLayout),
                   syncCmd.pars.second.stageFlags,
                   syncCmd.pars.second.accessFlags,
                   getImageLayoutName(syncCmd.pars.second.initialLayout));
          }
#endif
        } else {
          assert(info->event != VK_NULL_HANDLE);
          vkCmdWaitEvents(cmdBuffer,
                          1,
                          &info->event,
                          syncCmd.pars.first.stageFlags,
                          syncCmd.pars.second.stageFlags,
                          0,
                          nullptr,
                          0,
                          nullptr,
                          1,
                          &imageMemoryBarrier);
          ReleaseEvent(&data.device->allocator, info->event);
          info->event = VK_NULL_HANDLE;
#ifdef PRINT_SYNC_CMD
          if (info->desc.name) {
            printf("TEXTURE %s: WAIT EVENT (%u, %u, %s) -> (%u, %u, %s)\n",
                   info->desc.name,
                   syncCmd.pars.first.stageFlags,
                   syncCmd.pars.first.accessFlags,
                   getImageLayoutName(syncCmd.pars.first.finalLayout),
                   syncCmd.pars.second.stageFlags,
                   syncCmd.pars.second.accessFlags,
                   getImageLayoutName(syncCmd.pars.second.initialLayout));
          }
#endif
        }
        break;
      }
      default:
        break;
    }
  }
}

void
VulkanCmdBuffer::Signal(VkCommandBuffer cmdBuffer, Cmd const& cmd)
{
  assert(cmd.syncCmdCnt <= 4);

  if (cmd.syncCmdCnt == 0) {
    return;
  }

  for (uint32_t i = 0; i < cmd.syncCmdCnt; ++i) {
    auto const& syncCmd = cmd.syncCmds[i];

    if (syncCmd.code != SyncCmdCode::SET_EVENT) {
      continue;
    }

    switch (syncCmd.pars.resType) {
      case ResourceType::BUFFER: {
        auto info = (VulkanDevice::BufferInfo*)syncCmd.pars.res;
        assert(info->event == VK_NULL_HANDLE);
        info->event = AllocateEvent(&data.device->allocator);
        vkCmdSetEvent(cmdBuffer, info->event, syncCmd.pars.first.stageFlags);
#ifdef PRINT_SYNC_CMD
        if (info->desc.name) {
          printf("BUFFER %s: SET EVENT (%u, %u)\n",
                 info->desc.name,
                 syncCmd.pars.first.stageFlags,
                 syncCmd.pars.first.accessFlags);
        }
#endif
        break;
      }
      case ResourceType::TEXTURE: {
        auto info = (VulkanDevice::TextureInfo*)syncCmd.pars.res;
        assert(info->event == VK_NULL_HANDLE);
        info->event = AllocateEvent(&data.device->allocator);
        vkCmdSetEvent(cmdBuffer, info->event, syncCmd.pars.first.stageFlags);
#ifdef PRINT_SYNC_CMD
        if (info->desc.name) {
          printf("TEXTURE %s: SET EVENT (%u, %u, %s)\n",
                 info->desc.name,
                 syncCmd.pars.first.stageFlags,
                 syncCmd.pars.first.accessFlags,
                 getImageLayoutName(syncCmd.pars.first.finalLayout));
        }
#endif
        break;
      }
      default:
        break;
    }
  }
}

void
VulkanCmdBuffer::ReplayCopyPass(Pass const& pass)
{
  for (int idx = pass.startIdx; idx <= pass.endIdx; ++idx) {
    auto const& cmd = data.cmds[idx];

    switch (cmd.code) {
      case CmdCode::COPY: {
        auto const& pars = cmd.pars.copy;
        auto dstBufferInfo = (VulkanDevice::BufferInfo*)pars.dst;
        auto srcBufferInfo = (VulkanDevice::BufferInfo*)pars.src;

        Wait(data.cmdBuffer, cmd);

        VkBufferCopy copy = vkiBufferCopy(
          0, 0, std::min(srcBufferInfo->size, dstBufferInfo->size));

        vkCmdCopyBuffer(data.cmdBuffer,
                        srcBufferInfo->buffer,
                        dstBufferInfo->buffer,
                        1,
                        &copy);

        Signal(data.cmdBuffer, cmd);

        break;
      }

      case CmdCode::COPY_BUFFER_TO_TEXTURE: {
        auto const& pars = cmd.pars.copyBufferToTexture;
        auto dstTextureInfo = (VulkanDevice::TextureInfo*)pars.dst;
        auto srcBufferInfo = (VulkanDevice::BufferInfo*)pars.src;

        Wait(data.cmdBuffer, cmd);

        VkImageSubresourceLayers subresouce = {};
        subresouce.aspectMask = dstTextureInfo->subresource.aspectMask;
        subresouce.baseArrayLayer = dstTextureInfo->subresource.baseArrayLayer;
        subresouce.layerCount = dstTextureInfo->subresource.layerCount;
        subresouce.mipLevel = dstTextureInfo->subresource.baseMipLevel;

        VkBufferImageCopy copy =
          vkiBufferImageCopy(0,
                             0,
                             0,
                             subresouce,
                             { 0, 0, 0 },
                             { dstTextureInfo->desc.width,
                               dstTextureInfo->desc.height,
                               dstTextureInfo->desc.depth });

        vkCmdCopyBufferToImage(data.cmdBuffer,
                               srcBufferInfo->buffer,
                               dstTextureInfo->image,
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                               1,
                               &copy);

        Signal(data.cmdBuffer, cmd);

        break;
      }
      default:
        break;
    }
  }
}

void
VulkanCmdBuffer::ReplayRenderPass(Pass const& pass)
{
  for (int idx = pass.startIdx; idx <= pass.endIdx; ++idx) {
    auto const& cmd = data.cmds[idx];

    // things that need to happen before the renderpass begins
    switch (cmd.code) {
      case CmdCode::BIND_SAMPLED_TEXTURE: {
        // image memory barriers are not allowed inside a renderpass without an
        // additional subpass dependency
        Wait(data.cmdBuffer, cmd);
        break;
      }
      default:
        break;
    }
  }

  VkRenderPass renderPass = VK_NULL_HANDLE;

  std::vector<VkWriteDescriptorSet> descriptorWrites = {};
  std::vector<uint32_t> descriptorSets = {};
  std::vector<VkDescriptorBufferInfo> bufferInfos = {};
  std::vector<VkDescriptorImageInfo> imageInfos = {};
  PipelineLayout pipelineLayout = {};

  // TODO: replace with fixed size array for stable pointers
  bufferInfos.reserve(8);
  imageInfos.reserve(8);

  for (int idx = pass.startIdx; idx <= pass.endIdx; ++idx) {
    auto const& cmd = data.cmds[idx];

    switch (cmd.code) {
      case CmdCode::BEGIN_RENDER_PASS: {
        Wait(data.cmdBuffer, cmd);

        RenderPass rp = {};
        rp.subpassCnt = 1;

        Framebuffer fb = {};
        VkClearValue clearValues[Framebuffer::MAX_NUM_ATTACHMENTS];

        auto const& pars = cmd.pars.beginRenderPassPars;

        // TODO: explicitly set external subpass dependency if initial -> final
        // layout transition happend, to avoid an implicitly inserted, probably
        // costly external subpass dependency.
        for (uint32_t i = 0; i < pars.attachmentCnt; ++i) {
          auto const& info = pars.attachmentInfos[i];
          auto textureInfo = (VulkanDevice::TextureInfo*)info.texture;

          switch (info.type) {
            case AttachmentType::COLOR: {
              // attachments
              rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
                GetVkFormat(textureInfo->desc.format),
                VK_SAMPLE_COUNT_1_BIT,
                GetVkAttachmentLoadOp(info.loadOp),
                GetVkAttachmentStoreOp(info.storeOp),
                VK_ATTACHMENT_LOAD_OP_CLEAR,
                VK_ATTACHMENT_STORE_OP_STORE,
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                info.makePresentable
                  ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
                  : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

              // attachment refs for subpass 0
              rp.attachmentRefs[0].colorAttachments[rp.attachmentCnt] = {
                0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
              };
              ++rp.attachmentRefs[0].colorAttachmentCnt;

              rp.subpassess[0].pColorAttachments =
                rp.attachmentRefs->colorAttachments;
              rp.subpassess[0].colorAttachmentCount =
                rp.attachmentRefs->colorAttachmentCnt;

              clearValues[rp.attachmentCnt] = {
                info.clearValue.color.float32[0],
                info.clearValue.color.float32[1],
                info.clearValue.color.float32[2],
                info.clearValue.color.float32[3]
              };

              ++rp.attachmentCnt;

              // framebuffer
              fb.width = textureInfo->desc.width;
              fb.height = textureInfo->desc.height;
              fb.layers = textureInfo->desc.layers;
              fb.attachments[fb.attachmentCnt] = textureInfo->view;
              ++fb.attachmentCnt;

              break;
            }
            case AttachmentType::DEPTH: {
              // TODO: implementation
              break;
            }
            default:
              break;
          }
        }

        renderPass = GetRenderPass(&data.device->staticResources, &rp);

        fb.renderPass = renderPass;
        auto framebuffer = GetFramebuffer(&data.device->staticResources, &fb);

        VkRect2D renderArea = { {}, { fb.width, fb.height } };

        VkRenderPassBeginInfo renderPassBeginInfo = vkiRenderPassBeginInfo(
          renderPass, framebuffer, renderArea, rp.attachmentCnt, clearValues);
        vkCmdBeginRenderPass(
          data.cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        break;
      }
      case CmdCode::BIND_VERTEX_BUFFER: {
        auto const& pars = cmd.pars.bindVertexBuffer;
        auto bufferInfo = (VulkanDevice::BufferInfo*)pars.buffer;

        Wait(data.cmdBuffer, cmd);

        VkDeviceSize offset = pars.offset;

        vkCmdBindVertexBuffers(
          data.cmdBuffer, 0, 1, &bufferInfo->buffer, &offset);
        break;
      }
      case CmdCode::BIND_INDEX_BUFFER: {
        auto const& pars = cmd.pars.bindIndexBuffer;
        auto bufferInfo = (VulkanDevice::BufferInfo*)pars.buffer;

        Wait(data.cmdBuffer, cmd);

        vkCmdBindIndexBuffer(data.cmdBuffer,
                             bufferInfo->buffer,
                             0,
                             VkIndexType::VK_INDEX_TYPE_UINT32);
        break;
      }
      case CmdCode::BIND_UNIFORM_BUFFER: {
        auto const& pars = cmd.pars.bindUniformBuffer;
        auto bufferInfo = (VulkanDevice::BufferInfo*)pars.buffer;

        Wait(data.cmdBuffer, cmd);

        descriptorSets.push_back(pars.set);
        bufferInfos.push_back(
          vkiDescriptorBufferInfo(bufferInfo->buffer, 0, bufferInfo->size));
        descriptorWrites.push_back(
          vkiWriteDescriptorSet(VK_NULL_HANDLE,
                                pars.binding,
                                0,
                                1,
                                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                nullptr,
                                &bufferInfos.back(),
                                nullptr));

        break;
      }
      case CmdCode::BIND_SAMPLER: {
        auto const& pars = cmd.pars.bindSampler;

        auto sampler = GetSampler(&data.device->staticResources);
        descriptorSets.push_back(pars.set);
        imageInfos.push_back(vkiDescriptorImageInfo(
          sampler, VK_NULL_HANDLE, VK_IMAGE_LAYOUT_UNDEFINED));
        descriptorWrites.push_back(
          vkiWriteDescriptorSet(VK_NULL_HANDLE,
                                pars.binding,
                                0,
                                1,
                                VK_DESCRIPTOR_TYPE_SAMPLER,
                                &imageInfos.back(),
                                nullptr,
                                nullptr));

        break;
      }
      case CmdCode::BIND_SAMPLED_TEXTURE: {
        auto const& pars = cmd.pars.bindSampledTexture;
        auto textureInfo = (VulkanDevice::TextureInfo*)pars.texture;

        descriptorSets.push_back(pars.set);
        imageInfos.push_back(
          vkiDescriptorImageInfo(VK_NULL_HANDLE,
                                 textureInfo->view,
                                 VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
        descriptorWrites.push_back(
          vkiWriteDescriptorSet(VK_NULL_HANDLE,
                                pars.binding,
                                0,
                                1,
                                VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
                                &imageInfos.back(),
                                nullptr,
                                nullptr));

        break;
      }
      case CmdCode::BIND_PIPELINE: {
        Pipeline1 pipe = { renderPass, 0, cmd.pars.pipelineState };
        auto pipeline =
          GetPipeline(&data.device->staticResources, &pipe, &pipelineLayout);

        vkCmdBindPipeline(
          data.cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        break;
      }
      case CmdCode::DRAW: // fallthrough
      case CmdCode::DRAW_INDEXED: {
        uint32_t const writeCnt = static_cast<uint32_t>(descriptorSets.size());

        if (writeCnt > 0) {
          auto set = AllocateDescriptorSet(&data.device->arena,
                                           &pipelineLayout.layouts[0]);

          for (uint32_t i = 0; i < writeCnt; ++i) {
            descriptorWrites[i].dstSet = set;
          }

          vkUpdateDescriptorSets(data.device->device,
                                 writeCnt,
                                 descriptorWrites.data(),
                                 0,
                                 nullptr);

          auto layout =
            GetPipelineLayout(&data.device->staticResources, &pipelineLayout);
          vkCmdBindDescriptorSets(data.cmdBuffer,
                                  VK_PIPELINE_BIND_POINT_GRAPHICS,
                                  layout,
                                  0,
                                  1,
                                  &set,
                                  0,
                                  nullptr);

          descriptorSets.clear();
          bufferInfos.clear();
          imageInfos.clear();
        }

        if (cmd.code == CmdCode::DRAW_INDEXED) {
          vkCmdDrawIndexed(data.cmdBuffer, cmd.pars.draw.cnt, 1, 0, 0, 0);
        } else {
          vkCmdDraw(data.cmdBuffer, cmd.pars.draw.cnt, 1, 0, 0);
        }
        break;
      }
      case CmdCode::END_RENDER_PASS: {
        vkCmdEndRenderPass(data.cmdBuffer);
        break;
      }
      default:
        break;
    }
  }

  for (int idx = pass.startIdx; idx <= pass.endIdx; ++idx) {
    auto const& cmd = data.cmds[idx];

    switch (cmd.code) {
      case CmdCode::BIND_VERTEX_BUFFER:
      case CmdCode::BIND_INDEX_BUFFER:
      case CmdCode::BEGIN_RENDER_PASS:
      case CmdCode::BIND_SAMPLED_TEXTURE:
      case CmdCode::BIND_UNIFORM_BUFFER: {
        Signal(data.cmdBuffer, cmd);
        break;
      }
      default:
        break;
    }
  }
}

void
VulkanCmdBuffer::Replay()
{
  for (auto const& pass : data.passes) {
    switch (pass.type) {
      case PassType::COPY: {
        ReplayCopyPass(pass);
        break;
      }
      case PassType::RENDER: {
        ReplayRenderPass(pass);
        break;
      }
      default: {
        break;
      }
    }
  }
}
