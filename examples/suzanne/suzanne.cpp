#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <cmd_buffer.h>
#include <device.h>

#include <chrono>
#include <iostream>
#include <vector>

#define FAST_OBJ_IMPLEMENTATION
#include "../third_party/fast_obj/fast_obj.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

struct Mesh
{
  Buffer vbuf;
  Buffer ibuf;
  uint32_t triCnt;
};

struct MVP
{
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};

Mesh
uploadSuzanne(Device* device, CmdBuffer* cmdBuffer)
{
  fastObjMesh* mesh = fast_obj_read("resources/meshes/suzanne.obj");
  uint32_t vbuf_size = sizeof(float) * 3 * mesh->position_count;
  uint32_t ibuf_size = 3 * mesh->face_count * sizeof(uint32_t);

  Mesh result = { 0, 0, mesh->face_count };

  {
    // asserting that all facse are triangles
    auto idxCnt = 0;

    for (unsigned int i = 0; i < mesh->face_count; ++i) {
      idxCnt += 3 * (mesh->face_vertices[i] - 2);
    }

    assert(idxCnt == mesh->face_count * 3);
  }

  { // vertices
    void* data;
    Buffer stagingBuffer;
    BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = vbuf_size;
    bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_SRC;
    std::tie(stagingBuffer, data) = device->CreateBuffer(bufferCreateInfo);

    memcpy(data, mesh->positions, vbuf_size);

    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                  BufferUsageFlagBits::BUF_VERTEX_BUFFER;
    bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
    std::tie(result.vbuf, std::ignore) = device->CreateBuffer(bufferCreateInfo);

    cmdBuffer->Copy(result.vbuf, stagingBuffer);

    device->Release(stagingBuffer);
  }

  { // indices
    std::vector<uint32_t> positionIndices;
    positionIndices.reserve(mesh->face_count * 3);

    for (uint32_t i = 0; i < mesh->face_count * 3; ++i) {
      positionIndices.push_back(mesh->indices[i].p);
    }

    void* data;
    Buffer stagingBuffer;
    BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = ibuf_size;
    bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_SRC;
    std::tie(stagingBuffer, data) = device->CreateBuffer(bufferCreateInfo);

    memcpy(data, positionIndices.data(), ibuf_size);

    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                  BufferUsageFlagBits::BUF_INDEX_BUFFER;
    bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
    std::tie(result.ibuf, std::ignore) = device->CreateBuffer(bufferCreateInfo);

    cmdBuffer->Copy(result.ibuf, stagingBuffer);
    device->Release(stagingBuffer);
  }

  cmdBuffer->BufferBarrier({ BufferBarrierScope::None,
                             BufferBarrierScope::VertexBuffer,
                             result.vbuf });
  cmdBuffer->BufferBarrier(
    { BufferBarrierScope::None, BufferBarrierScope::IndexBuffer, result.ibuf });

  fast_obj_destroy(mesh);

  return result;
}

int
main()
{
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  uint32_t samples = 16;

  int width = 512;
  int height = 512;

  auto window = glfwCreateWindow(width, height, "suzanne", 0, 0);
  auto hwnd = glfwGetWin32Window(window);

  auto device = Device::Create();

  TextureCreateInfo textureCreateInfo = {};
  textureCreateInfo.width = width;
  textureCreateInfo.height = height;
  textureCreateInfo.depth = 1;
  textureCreateInfo.format = PixelFormat::RGBA8_UNORM_SRGB;
  textureCreateInfo.layers = 1;
  textureCreateInfo.mipLevels = 1;
  textureCreateInfo.name = "multisample_texture";
  textureCreateInfo.usageFlags = TextureUsageFlagBits::TEX_COLOR_ATTACHMENT;
  textureCreateInfo.samples = samples;

  auto multiSampleTexture = device->CreateTexture(textureCreateInfo);

  SwapchainCreateInfo swapchainCreateInfo = {};
  swapchainCreateInfo.width = width;
  swapchainCreateInfo.height = height;
  swapchainCreateInfo.depth = 1;
  swapchainCreateInfo.format = PixelFormat::RGBA8_UNORM_SRGB;
  swapchainCreateInfo.usageFlags = TextureUsageFlagBits::TEX_COLOR_ATTACHMENT;
  swapchainCreateInfo.textureCnt = 3;
  swapchainCreateInfo.platformHandle = (void*)hwnd;
  swapchainCreateInfo.oldSwapchain = nullptr;
  swapchainCreateInfo.name = "swapchain";

  Swapchain swapchain = device->CreateSwapchain(swapchainCreateInfo);

  PipelineState state = {};
  state.shader.vertexShader = "resources/shaders/suzanne.vert.spv";
  state.shader.fragmentShader = "resources/shaders/suzanne.frag.spv";

  state.vertexInput.bindingDescriptions[0].binding = 0;
  state.vertexInput.bindingDescriptions[0].inputRate = VertexInputRate::VERTEX;
  state.vertexInput.bindingDescriptions[0].stride = sizeof(float) * 3;
  state.vertexInput.bindingDescriptionCnt = 1;

  state.vertexInput.attributeDescriptions[0].binding = 0;
  state.vertexInput.attributeDescriptions[0].location = 0;
  state.vertexInput.attributeDescriptions[0].offset = 0;
  state.vertexInput.attributeDescriptions[0].format = VertexFormat::FLOAT3;
  state.vertexInput.attributeDescriptionCnt = 1;

  state.inputAssembly.topology = PrimitiveTopology::TRIANGLE_LIST;

  state.rasterization.polygonMode = PolygonMode::FILL;
  state.rasterization.cullMode = CullMode::NONE;
  state.rasterization.frontFace = FrontFace::CLOCKWISE;

  state.viewport.viewport.x = 0;
  state.viewport.viewport.y = 0;
  state.viewport.viewport.width = static_cast<float>(swapchainCreateInfo.width);
  state.viewport.viewport.height =
    static_cast<float>(swapchainCreateInfo.height);
  state.viewport.viewport.minDepth = 0.f;
  state.viewport.viewport.maxDepth = 1.f;
  state.viewport.scissors.x = 0;
  state.viewport.scissors.y = 0;
  state.viewport.scissors.width = swapchainCreateInfo.width / 2;
  state.viewport.scissors.height = swapchainCreateInfo.height;

  state.multisample.rasterizationSamples = samples;

  Mesh mesh = {};
  MVP mvp = {};

  mvp.model = glm::identity<glm::mat4>();
  mvp.view = glm::identity<glm::mat4>();
  mvp.proj = glm::identity<glm::mat4>();

  mvp.model =
    glm::scale(mvp.model, glm::vec3{ 0.7f, -0.7f, 0.1f }); // scale down, flip y
  mvp.model = glm::translate(mvp.model, glm::vec3{ 0, 0, 1.f }); // move closer

  Buffer uniformBuffer;
  void* data;
  BufferCreateInfo bufferCreateInfo;
  bufferCreateInfo.size = sizeof(mvp);
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER |
                                BufferUsageFlagBits::BUF_TRANSFER_SRC;
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;
  std::tie(uniformBuffer, data) = device->CreateBuffer(bufferCreateInfo);

  while (true) {
    Texture swapchainTexture;

    //mvp.model = glm::rotate(mvp.model, 0.02f, glm::vec3{ 0, 1, 0 });

    memcpy(data, &mvp, sizeof(mvp));

    if (!device->AquireNext(swapchain, &swapchainTexture)) {
      device->Release(swapchain);

      glfwGetWindowSize(window, &width, &height);
      state.viewport.scissors.width = width;
      state.viewport.scissors.height = height;
      state.viewport.viewport.width = static_cast<float>(width);
      state.viewport.viewport.height = static_cast<float>(height);

      swapchainCreateInfo.width = width;
      swapchainCreateInfo.height = height;
      swapchainCreateInfo.oldSwapchain = swapchain;

      swapchain = device->CreateSwapchain(swapchainCreateInfo);
    }

    CmdBuffer* cmdBuffer = device->GetCmdBuffer();

    if (!mesh.vbuf) {
      mesh = uploadSuzanne(device, cmdBuffer);
    }

    cmdBuffer->TextureBarrier({ TextureBarrierScope::None,
                                TextureBarrierScope::ColorAttachment,
                                multiSampleTexture });
    cmdBuffer->TextureBarrier({ TextureBarrierScope::None,
                                TextureBarrierScope::ColorAttachment,
                                swapchainTexture });

    RenderPassBeginInfo beginInfo = {};
    beginInfo.attachmentCnt = 2;

    beginInfo.attachmentInfos[0].clearValue = { 0., 0., 0., 1 };
    beginInfo.attachmentInfos[0].texture = swapchainTexture;
    beginInfo.attachmentInfos[0].type = AttachmentType::RESOLVE;
    beginInfo.attachmentInfos[0].loadOp = LoadOp::CLEAR;
    beginInfo.attachmentInfos[0].storeOp = StoreOp::STORE;
    beginInfo.attachmentInfos[0].makePresentable = false;

    beginInfo.attachmentInfos[1].clearValue = { 0., 0., 0., 1 };
    beginInfo.attachmentInfos[1].texture = multiSampleTexture;
    beginInfo.attachmentInfos[1].type = AttachmentType::COLOR;
    beginInfo.attachmentInfos[1].loadOp = LoadOp::CLEAR;
    beginInfo.attachmentInfos[1].storeOp = StoreOp::STORE;
    beginInfo.attachmentInfos[1].makePresentable = false;

    cmdBuffer->BeginRenderPass(beginInfo);

    cmdBuffer->BindVertexBuffer(mesh.vbuf, 0);
    cmdBuffer->BindIndexBuffer(mesh.ibuf);
    cmdBuffer->BindUniformBuffer(uniformBuffer, 0, 0, 0, sizeof(glm::mat4x4));

    state.viewport.scissors.x = 0;
	state.multisample.rasterizationSamples = samples;
    cmdBuffer->SetPipelineState(state);
    cmdBuffer->DrawIndexed(mesh.triCnt * 3);

    cmdBuffer->EndRenderPass();

    cmdBuffer->TextureBarrier(
      { TextureBarrierScope::ColorAttachment, // not sure what the resolve
                                              // attachment synchronization
                                              // scope should be
        TextureBarrierScope::ColorAttachment,
        swapchainTexture });

    beginInfo.attachmentCnt = 1;
    beginInfo.attachmentInfos[0].type = AttachmentType::COLOR;
    beginInfo.attachmentInfos[0].loadOp = LoadOp::LOAD;
    beginInfo.attachmentInfos[0].storeOp = StoreOp::STORE;
    cmdBuffer->BeginRenderPass(beginInfo);

    cmdBuffer->BindVertexBuffer(mesh.vbuf, 0);
    cmdBuffer->BindIndexBuffer(mesh.ibuf);
    cmdBuffer->BindUniformBuffer(uniformBuffer, 0, 0, 0, sizeof(glm::mat4x4));

    state.viewport.scissors.x = width / 2;
	state.multisample.rasterizationSamples = 1;
    cmdBuffer->SetPipelineState(state);
    cmdBuffer->DrawIndexed(mesh.triCnt * 3);

    cmdBuffer->EndRenderPass();

    cmdBuffer->TextureBarrier({ TextureBarrierScope::ColorAttachment,
                                TextureBarrierScope::PresentSrc,
                                swapchainTexture });

    device->Submit(cmdBuffer);

    if (!device->Present(swapchain)) {
      device->Release(swapchain);

      glfwGetWindowSize(window, &width, &height);
      state.viewport.scissors.width = width;
      state.viewport.scissors.height = height;
      state.viewport.viewport.width = static_cast<float>(width);
      state.viewport.viewport.height = static_cast<float>(height);
      swapchainCreateInfo.width = width;
      swapchainCreateInfo.height = height;
      swapchainCreateInfo.oldSwapchain = swapchain;

      swapchain = device->CreateSwapchain(swapchainCreateInfo);
    }

    device->Recycle();
    glfwPollEvents();
  }
}
