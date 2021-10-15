#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <pokei.h>

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
uploadSuzanne(Device device, CmdBuffer cmdBuffer)
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
    pkCreateBuffer(device, &bufferCreateInfo, &stagingBuffer, &data);

    memcpy(data, mesh->positions, vbuf_size);

    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                  BufferUsageFlagBits::BUF_VERTEX_BUFFER;
    bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
    void* dummy;
    pkCreateBuffer(device, &bufferCreateInfo, &result.vbuf, &dummy);

    pkCopy(cmdBuffer, result.vbuf, stagingBuffer);
    pkDestroyBuffer(device, stagingBuffer);
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
    pkCreateBuffer(device, &bufferCreateInfo, &stagingBuffer, &data);

    memcpy(data, positionIndices.data(), ibuf_size);

    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                  BufferUsageFlagBits::BUF_INDEX_BUFFER;
    bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
    void* dummy;
    pkCreateBuffer(device, &bufferCreateInfo, &result.ibuf, &dummy);
    pkCopy(cmdBuffer, result.ibuf, stagingBuffer);
    pkDestroyBuffer(device, stagingBuffer);
  }

  auto barrier = BufferBarrier{
    SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                          AccessFlagBits::TRANSFER_WRITE_BIT,
                          QueueType::Transfer },
    SynchronizationScope{ PipelineStageFlagBits::GRAPHICS_VERTEX_INPUT_BIT |
                            PipelineStageFlagBits::GRAPHICS_VERTEX_SHADER_BIT,
                          AccessFlagBits::VERTEX_ATTRIBUTE_READ_BIT,
                          QueueType::Graphics },
    result.vbuf
  };

  insertBarrier(cmdBuffer, &barrier);

  barrier.dst.access = AccessFlagBits::INDEX_READ_BIT;
  barrier.buffer = result.ibuf;

  insertBarrier(cmdBuffer, &barrier);

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

  Device device;
  pkCreateDevice(&device);

  TextureCreateInfo textureCreateInfo = {};
  textureCreateInfo.width = width;
  textureCreateInfo.height = height;
  textureCreateInfo.depth = 1;
  textureCreateInfo.format = PixelFormat::RGBA8_UNORM_SRGB;
  textureCreateInfo.layers = 1;
  textureCreateInfo.mipLevels = 1;
  textureCreateInfo.usageFlags = TextureUsageFlagBits::TEX_COLOR_ATTACHMENT;
  textureCreateInfo.samples = samples;

  Texture multiSampleTexture;
  pkCreateTexture(device, &textureCreateInfo, &multiSampleTexture);

  SwapchainCreateInfo swapchainCreateInfo = {};
  swapchainCreateInfo.width = width;
  swapchainCreateInfo.height = height;
  swapchainCreateInfo.depth = 1;
  swapchainCreateInfo.format = PixelFormat::RGBA8_UNORM_SRGB;
  swapchainCreateInfo.usageFlags = TextureUsageFlagBits::TEX_COLOR_ATTACHMENT;
  swapchainCreateInfo.textureCnt = 3;
  swapchainCreateInfo.platformHandle = (void*)hwnd;
  swapchainCreateInfo.oldSwapchain = nullptr;

  Swapchain swapchain;
  pkCreateSwapchain(device, &swapchainCreateInfo, &swapchain);

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

  pkCreateBuffer(device, &bufferCreateInfo, &uniformBuffer, &data);

  while (true) {
    Texture swapchainTexture;

    // mvp.model = glm::rotate(mvp.model, 0.02f, glm::vec3{ 0, 1, 0 });

    memcpy(data, &mvp, sizeof(mvp));

    Semaphore available;
    if (!acquireNext(device, swapchain, &swapchainTexture, &available)) {
      pkDestroySwapchain(device, swapchain);

      glfwGetWindowSize(window, &width, &height);
      state.viewport.scissors.width = width;
      state.viewport.scissors.height = height;
      state.viewport.viewport.width = static_cast<float>(width);
      state.viewport.viewport.height = static_cast<float>(height);

      swapchainCreateInfo.width = width;
      swapchainCreateInfo.height = height;
      swapchainCreateInfo.oldSwapchain = swapchain;

      pkCreateSwapchain(device, &swapchainCreateInfo, &swapchain);
    }

    Queue queue;
    CmdBuffer cmdBuffer;

    pkGetQueue(device, QueueType::Graphics, &queue);
    pkCreateCmdBuffer(queue, &cmdBuffer);

    if (!mesh.vbuf) {
      mesh = uploadSuzanne(device, cmdBuffer);
    }

    auto textureBarrier = TextureBarrier{
      SynchronizationScope{ PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0 },
      SynchronizationScope{
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
        AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
          AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT },
      TextureLayout::UNDEFINED,
      TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
      multiSampleTexture
    };

    insertBarrier(cmdBuffer, &textureBarrier);
	textureBarrier.texture = swapchainTexture;
    insertBarrier(cmdBuffer, &textureBarrier);

    RenderPass renderPass = {};
    renderPass.attachmentCnt = 2;

    renderPass.attachmentInfos[0].clearValue = { 0., 0., 0., 1 };
    renderPass.attachmentInfos[0].texture = swapchainTexture;
    renderPass.attachmentInfos[0].type = AttachmentType::RESOLVE;
    renderPass.attachmentInfos[0].loadOp = LoadOp::CLEAR;
    renderPass.attachmentInfos[0].storeOp = StoreOp::STORE;
    renderPass.attachmentInfos[0].makePresentable = false;

    renderPass.attachmentInfos[1].clearValue = { 0., 0., 0., 1 };
    renderPass.attachmentInfos[1].texture = multiSampleTexture;
    renderPass.attachmentInfos[1].type = AttachmentType::COLOR;
    renderPass.attachmentInfos[1].loadOp = LoadOp::CLEAR;
    renderPass.attachmentInfos[1].storeOp = StoreOp::STORE;
    renderPass.attachmentInfos[1].makePresentable = false;

    beginRenderPass(cmdBuffer, &renderPass);

    bindVertexBuffer(cmdBuffer, mesh.vbuf, 0);
    bindIndexBuffer(cmdBuffer, mesh.ibuf);
    bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 0, 0, sizeof(glm::mat4x4));

    state.viewport.scissors.x = 0;
    state.multisample.rasterizationSamples = samples;
    setPipelineState(cmdBuffer, &state);
    drawIndexed(cmdBuffer, mesh.triCnt * 3);

    endRenderPass(cmdBuffer);

    textureBarrier = TextureBarrier{
      SynchronizationScope{
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
        AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
          AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT },
      SynchronizationScope{
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
        AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
          AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT },
      TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
      TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
      multiSampleTexture
    };

	// render again and overwrite the left side of the anti aliased image
    renderPass.attachmentCnt = 1;
    renderPass.attachmentInfos[0].type = AttachmentType::COLOR;
    renderPass.attachmentInfos[0].loadOp = LoadOp::LOAD;
    renderPass.attachmentInfos[0].storeOp = StoreOp::STORE;
    beginRenderPass(cmdBuffer, &renderPass);

    bindVertexBuffer(cmdBuffer, mesh.vbuf, 0);
    bindIndexBuffer(cmdBuffer, mesh.ibuf);
    bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 0, 0, sizeof(glm::mat4x4));

    state.viewport.scissors.x = width / 2;
    state.multisample.rasterizationSamples = 1;
    setPipelineState(cmdBuffer, &state);
    drawIndexed(cmdBuffer, mesh.triCnt * 3);

    endRenderPass(cmdBuffer);

    textureBarrier = TextureBarrier{
      SynchronizationScope{
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
        AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
          AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT },
      SynchronizationScope{ PipelineStageFlagBits::BOTTOM_OF_PIPE_BIT, 0 },
      TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
      TextureLayout::PRESENT_SRC_KHR,
      swapchainTexture
    };

    insertBarrier(cmdBuffer, &textureBarrier);

    Semaphore waitSemaphores[1];
    waitSemaphores[0] = available;

    PipelineStageFlags waitStages[1];
    waitStages[0] = PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT;

    Semaphore renderDone;
    submit(queue,
           &cmdBuffer,
           1,
           waitSemaphores,
           waitStages,
           1,
           &renderDone,
           1,
           nullptr);

    if (!present(queue, swapchain, &renderDone)) {
      pkDestroySwapchain(device, swapchain);

      glfwGetWindowSize(window, &width, &height);
      state.viewport.scissors.width = width;
      state.viewport.scissors.height = height;
      state.viewport.viewport.width = static_cast<float>(width);
      state.viewport.viewport.height = static_cast<float>(height);

      swapchainCreateInfo.width = width;
      swapchainCreateInfo.height = height;
      swapchainCreateInfo.oldSwapchain = swapchain;

      pkCreateSwapchain(device, &swapchainCreateInfo, &swapchain);
    }

    frame(device);
    glfwPollEvents();
  }
}
