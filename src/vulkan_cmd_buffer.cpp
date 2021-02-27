#include "vulkan_device.h"

#include "vulkan_resources.h"
#include "vulkan_types.h"

AccessScope
getAccessScope(BufferBarrierScope scope)
{
  switch (scope) {
    case BufferBarrierScope::None:
      return AccessScope::None();
    case BufferBarrierScope::IndexBuffer:
      return AccessScope::IndexBuffer();
    case BufferBarrierScope::VertexBuffer:
      return AccessScope::VertexBuffer();
    case BufferBarrierScope::IndirectBuffer:
      return AccessScope::IndirectBuffer();
    case BufferBarrierScope::UniformBuffer:
      return AccessScope::UniformBuffer(VK_PIPELINE_STAGE_VERTEX_SHADER_BIT |
                                        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT |
                                        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
    case BufferBarrierScope::StorageBuffer:
      return AccessScope::StorageBuffer(VK_PIPELINE_STAGE_VERTEX_SHADER_BIT |
                                        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT |
                                        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
    case BufferBarrierScope::UniformTexelBuffer:
      return AccessScope::UniformTexelBuffer(
        VK_PIPELINE_STAGE_VERTEX_SHADER_BIT |
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT |
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
    case BufferBarrierScope::StorageTexelBuffer:
      return AccessScope::StorageTexelBuffer(
        VK_PIPELINE_STAGE_VERTEX_SHADER_BIT |
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT |
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
    case BufferBarrierScope::TransferSrc:
      return AccessScope::BufferTransferSrc();
    case BufferBarrierScope::TransferDst:
      return AccessScope::BufferTransferDst();
    default:
      return {};
  }
}

AccessScope
getAccessScope(TextureBarrierScope scope)
{
  switch (scope) {
    case TextureBarrierScope::None:
      return AccessScope::None();
    case TextureBarrierScope::ColorAttachment:
      return AccessScope::ColorOutputAttachment();
    case TextureBarrierScope::DepthStencilAttachment:
      return AccessScope::DepthStencilAttachment();
    case TextureBarrierScope::SampledTexture:
      return AccessScope::Sampled(VK_PIPELINE_STAGE_VERTEX_SHADER_BIT |
                                  VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
    case TextureBarrierScope::PresentSrc:
      return AccessScope::PresentSrc();
    case TextureBarrierScope::TransferSrc:
      return AccessScope::TextureTransferSrc();
    case TextureBarrierScope::TransferDst:
      return AccessScope::TextureTransferDst();
    default:
      return {};
  }
}

void
VulkanCmdBuffer::BufferBarrier(BufferBarrierInfo const& info)
{
  auto src = getAccessScope(info.src);
  auto dst = getAccessScope(info.dst);
  auto bufferInfo = ((VulkanDevice::BufferInfo*)info.buffer);

  auto barrier = vkiBufferMemoryBarrier(src.accessFlags,
                                        dst.accessFlags,
                                        -1,
                                        -1,
                                        bufferInfo->buffer,
                                        0,
                                        bufferInfo->size);

  vkCmdPipelineBarrier(cmdBuffer,
                       src.stageFlags,
                       dst.stageFlags,
                       VK_DEPENDENCY_BY_REGION_BIT,
                       0,
                       nullptr,
                       1,
                       &barrier,
                       0,
                       nullptr);
}

void
VulkanCmdBuffer::TextureBarrier(TextureBarrierInfo const& info)
{
  auto src = getAccessScope(info.src);
  auto dst = getAccessScope(info.dst);
  auto textureInfo = ((VulkanDevice::TextureInfo*)info.texture);

  auto barrier = vkiImageMemoryBarrier(src.accessFlags,
                                       dst.accessFlags,
                                       src.initialLayout,
                                       dst.initialLayout,
                                       -1,
                                       -1,
                                       textureInfo->image,
                                       textureInfo->subresource);

  vkCmdPipelineBarrier(cmdBuffer,
                       src.stageFlags,
                       dst.stageFlags,
                       VK_DEPENDENCY_BY_REGION_BIT,
                       0,
                       nullptr,
                       0,
                       nullptr,
                       1,
                       &barrier);
}

void
VulkanCmdBuffer::Copy(Buffer dst, Buffer src)
{
  auto dstBufferInfo = (VulkanDevice::BufferInfo*)dst;
  auto srcBufferInfo = (VulkanDevice::BufferInfo*)src;

  VkBufferCopy copy =
    vkiBufferCopy(0, 0, std::min(srcBufferInfo->size, dstBufferInfo->size));

  vkCmdCopyBuffer(
    cmdBuffer, srcBufferInfo->buffer, dstBufferInfo->buffer, 1, &copy);
}

void
VulkanCmdBuffer::CopyBufferToTexture(Texture dst, Buffer src)
{
  auto dstTextureInfo = (VulkanDevice::TextureInfo*)dst;
  auto srcBufferInfo = (VulkanDevice::BufferInfo*)src;

  VkImageSubresourceLayers subresouce = {};
  subresouce.aspectMask = dstTextureInfo->subresource.aspectMask;
  subresouce.baseArrayLayer = dstTextureInfo->subresource.baseArrayLayer;
  subresouce.layerCount = dstTextureInfo->subresource.layerCount;
  subresouce.mipLevel = dstTextureInfo->subresource.baseMipLevel;

  VkBufferImageCopy copy = vkiBufferImageCopy(0,
                                              0,
                                              0,
                                              subresouce,
                                              { 0, 0, 0 },
                                              { dstTextureInfo->desc.width,
                                                dstTextureInfo->desc.height,
                                                dstTextureInfo->desc.depth });

  vkCmdCopyBufferToImage(cmdBuffer,
                         srcBufferInfo->buffer,
                         dstTextureInfo->image,
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                         1,
                         &copy);
}

void
VulkanCmdBuffer::BeginRenderPass(RenderPassBeginInfo const& beginInfo)
{
  cmdBufferState = {};

  cmdBufferState.bufferInfos.reserve(8);
  cmdBufferState.imageInfos.reserve(8);
  cmdBufferState.descriptorWrites.reserve(8);
  cmdBufferState.descriptorSets.reserve(8);

  RenderPass rp = {};
  rp.subpassCnt = 1;

  Framebuffer fb = {};
  VkClearValue clearValues[Framebuffer::MAX_NUM_ATTACHMENTS];

  // TODO: explicitly set external subpass dependency if initial -> final
  // layout transition happend, to avoid an implicitly inserted, probably
  // costly external subpass dependency.
  for (uint32_t i = 0; i < beginInfo.attachmentCnt; ++i) {
    auto const& info = beginInfo.attachmentInfos[i];
    auto textureInfo = (VulkanDevice::TextureInfo*)info.texture;

    switch (info.type) {
      case AttachmentType::COLOR: {
        // attachments
        rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
          GetVkFormat(textureInfo->desc.format),
          GetVkSampleCountFlagBits(textureInfo->desc.samples),
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
        fb.width = textureInfo->desc.width;
        fb.height = textureInfo->desc.height;
        fb.layers = textureInfo->desc.layers;
        fb.attachments[fb.attachmentCnt] = textureInfo->view;
        ++fb.attachmentCnt;

        break;
      }
      case AttachmentType::DEPTH: {
        // TODO: depth stencil attachmentss and depth only attachments need
        // different layouts
        rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
          GetVkFormat(textureInfo->desc.format),
          GetVkSampleCountFlagBits(textureInfo->desc.samples),
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
        fb.width = textureInfo->desc.width;
        fb.height = textureInfo->desc.height;
        fb.layers = textureInfo->desc.layers;
        fb.attachments[fb.attachmentCnt] = textureInfo->view;
        ++fb.attachmentCnt;

        break;
      }
      case AttachmentType::RESOLVE: {
        // COLOR resolve attachment
        rp.attachments[rp.attachmentCnt] = vkiAttachmentDescription(
          GetVkFormat(textureInfo->desc.format),
          GetVkSampleCountFlagBits(textureInfo->desc.samples),
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
        fb.width = textureInfo->desc.width;
        fb.height = textureInfo->desc.height;
        fb.layers = textureInfo->desc.layers;
        fb.attachments[fb.attachmentCnt] = textureInfo->view;
        ++fb.attachmentCnt;

        break;
      }
      default:
        break;
    }
  }

  cmdBufferState.renderPass = GetRenderPass(&device->staticResources, &rp);
  cmdBufferState.subpass = 0;

  fb.renderPass = cmdBufferState.renderPass;
  auto framebuffer = GetFramebuffer(&device->staticResources, &fb);

  VkRect2D renderArea = { {}, { fb.width, fb.height } };

  VkRenderPassBeginInfo renderPassBeginInfo =
    vkiRenderPassBeginInfo(cmdBufferState.renderPass,
                           framebuffer,
                           renderArea,
                           rp.attachmentCnt,
                           clearValues);
  vkCmdBeginRenderPass(
    cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void
VulkanCmdBuffer::BindVertexBuffer(Buffer buffer, uint64_t offset)
{
  auto bufferInfo = (VulkanDevice::BufferInfo*)buffer;
  vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &bufferInfo->buffer, &offset);
}

void
VulkanCmdBuffer::BindIndexBuffer(Buffer buffer)
{
  auto bufferInfo = (VulkanDevice::BufferInfo*)buffer;
  vkCmdBindIndexBuffer(
    cmdBuffer, bufferInfo->buffer, 0, VkIndexType::VK_INDEX_TYPE_UINT32);
}

void
VulkanCmdBuffer::BindUniformBuffer(Buffer buffer,
                                   uint32_t set,
                                   uint32_t binding)
{
  auto bufferInfo = (VulkanDevice::BufferInfo*)buffer;

  cmdBufferState.descriptorSets.push_back(set);
  cmdBufferState.bufferInfos.push_back(
    vkiDescriptorBufferInfo(bufferInfo->buffer, 0, bufferInfo->size));
  cmdBufferState.descriptorWrites.push_back(
    vkiWriteDescriptorSet(VK_NULL_HANDLE,
                          binding,
                          0,
                          1,
                          VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                          nullptr,
                          &cmdBufferState.bufferInfos.back(),
                          nullptr));
}

void
VulkanCmdBuffer::BindStorageBuffer(Buffer buffer,
                                   uint32_t set,
                                   uint32_t binding)
{
  auto bufferInfo = (VulkanDevice::BufferInfo*)buffer;

  cmdBufferState.descriptorSets.push_back(set);
  cmdBufferState.bufferInfos.push_back(
    vkiDescriptorBufferInfo(bufferInfo->buffer, 0, bufferInfo->size));
  cmdBufferState.descriptorWrites.push_back(
    vkiWriteDescriptorSet(VK_NULL_HANDLE,
                          binding,
                          0,
                          1,
                          VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                          nullptr,
                          &cmdBufferState.bufferInfos.back(),
                          nullptr));
}

void
VulkanCmdBuffer::BindSampler(uint32_t set, uint32_t binding)
{
  auto sampler = GetSampler(&device->staticResources);
  cmdBufferState.descriptorSets.push_back(set);
  cmdBufferState.imageInfos.push_back(
    vkiDescriptorImageInfo(sampler, VK_NULL_HANDLE, VK_IMAGE_LAYOUT_UNDEFINED));
  cmdBufferState.descriptorWrites.push_back(
    vkiWriteDescriptorSet(VK_NULL_HANDLE,
                          binding,
                          0,
                          1,
                          VK_DESCRIPTOR_TYPE_SAMPLER,
                          &cmdBufferState.imageInfos.back(),
                          nullptr,
                          nullptr));
}

void
VulkanCmdBuffer::BindSampledTexture(Texture texture,
                                    uint32_t set,
                                    uint32_t binding)
{
  auto textureInfo = (VulkanDevice::TextureInfo*)texture;

  cmdBufferState.descriptorSets.push_back(set);
  cmdBufferState.imageInfos.push_back(
    vkiDescriptorImageInfo(VK_NULL_HANDLE,
                           textureInfo->view,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
  cmdBufferState.descriptorWrites.push_back(
    vkiWriteDescriptorSet(VK_NULL_HANDLE,
                          binding,
                          0,
                          1,
                          VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
                          &cmdBufferState.imageInfos.back(),
                          nullptr,
                          nullptr));
}

void
VulkanCmdBuffer::SetPipelineState(PipelineState pipelineState)
{
  Pipeline1 pipe = { cmdBufferState.renderPass,
                     cmdBufferState.subpass,
                     &pipelineState };
  auto pipeline = GetPipeline(
    &device->staticResources, &pipe, &cmdBufferState.pipelineLayout);

  if (pipelineState.shader.computeShader) {
    vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
  } else {
    vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
  }
}

void
VulkanCmdBuffer::Draw(uint32_t cnt)
{
  uint32_t const writeCnt =
    static_cast<uint32_t>(cmdBufferState.descriptorSets.size());

  if (writeCnt > 0) {
    auto set = AllocateDescriptorSet(&device->arena,
                                     &cmdBufferState.pipelineLayout.layouts[0]);

    for (uint32_t i = 0; i < writeCnt; ++i) {
      cmdBufferState.descriptorWrites[i].dstSet = set;
    }

    vkUpdateDescriptorSets(device->device,
                           writeCnt,
                           cmdBufferState.descriptorWrites.data(),
                           0,
                           nullptr);

    auto layout = GetPipelineLayout(&device->staticResources,
                                    &cmdBufferState.pipelineLayout);
    vkCmdBindDescriptorSets(cmdBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            layout,
                            0,
                            1,
                            &set,
                            0,
                            nullptr);

    cmdBufferState.descriptorSets.clear();
    cmdBufferState.bufferInfos.clear();
    cmdBufferState.imageInfos.clear();
  }

  vkCmdDraw(cmdBuffer, cnt, 1, 0, 0);
}

void
VulkanCmdBuffer::DrawIndexed(uint32_t cnt)
{
  uint32_t const writeCnt =
    static_cast<uint32_t>(cmdBufferState.descriptorSets.size());

  if (writeCnt > 0) {
    auto set = AllocateDescriptorSet(&device->arena,
                                     &cmdBufferState.pipelineLayout.layouts[0]);

    for (uint32_t i = 0; i < writeCnt; ++i) {
      cmdBufferState.descriptorWrites[i].dstSet = set;
    }

    vkUpdateDescriptorSets(device->device,
                           writeCnt,
                           cmdBufferState.descriptorWrites.data(),
                           0,
                           nullptr);

    auto layout = GetPipelineLayout(&device->staticResources,
                                    &cmdBufferState.pipelineLayout);
    vkCmdBindDescriptorSets(cmdBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            layout,
                            0,
                            1,
                            &set,
                            0,
                            nullptr);

    cmdBufferState.descriptorSets.clear();
    cmdBufferState.bufferInfos.clear();
    cmdBufferState.imageInfos.clear();
  }

  vkCmdDrawIndexed(cmdBuffer, cnt, 1, 0, 0, 0);
}

void
VulkanCmdBuffer::EndRenderPass()
{
  vkCmdEndRenderPass(cmdBuffer);
}

void
VulkanCmdBuffer::Dispatch(uint32_t x, uint32_t y, uint32_t z)
{
  uint32_t const writeCnt =
    static_cast<uint32_t>(cmdBufferState.descriptorSets.size());

  if (writeCnt > 0) {
    auto set = AllocateDescriptorSet(&device->arena,
                                     &cmdBufferState.pipelineLayout.layouts[0]);

    for (uint32_t i = 0; i < writeCnt; ++i) {
      cmdBufferState.descriptorWrites[i].dstSet = set;
    }

    vkUpdateDescriptorSets(device->device,
                           writeCnt,
                           cmdBufferState.descriptorWrites.data(),
                           0,
                           nullptr);

    auto layout = GetPipelineLayout(&device->staticResources,
                                    &cmdBufferState.pipelineLayout);
    vkCmdBindDescriptorSets(cmdBuffer,
                            VK_PIPELINE_BIND_POINT_COMPUTE,
                            layout,
                            0,
                            1,
                            &set,
                            0,
                            nullptr);

    cmdBufferState.descriptorSets.clear();
    cmdBufferState.bufferInfos.clear();
    cmdBufferState.imageInfos.clear();
  }

  vkCmdDispatch(cmdBuffer, x, y, z);
}
