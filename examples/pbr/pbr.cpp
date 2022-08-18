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
#include <glm/gtc/matrix_transform.hpp>

using u32 = uint32_t;

struct Mesh
{
  Buffer vertexBuffer;
  u32 vertexCnt;
};

struct UBO
{
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
  glm::vec3 cameraPos;
};

Mesh uploadMesh(Device device, CmdBuffer cmdBuffer)
{
  fastObjMesh *mesh = fast_obj_read("resources/meshes/dragon.obj");
  Mesh result = {};

  result.vertexCnt = mesh->face_count * 3;
  uint32_t const size = sizeof(float) * 3 * 2 * result.vertexCnt;

  {
    // asserting that all faces are triangles
    auto idxCnt = 0;

    for (unsigned int i = 0; i < mesh->face_count; ++i)
    {
      idxCnt += 3 * (mesh->face_vertices[i] - 2);
    }

    assert(idxCnt == mesh->face_count * 3);
  }

  std::vector<float> vertices = {};

  for (uint32_t i = 0; i < result.vertexCnt; ++i)
  {
    vertices.push_back(mesh->positions[mesh->indices[i].p * 3 + 0]);
    vertices.push_back(mesh->positions[mesh->indices[i].p * 3 + 1]);
    vertices.push_back(mesh->positions[mesh->indices[i].p * 3 + 2]);
    vertices.push_back(mesh->normals[mesh->indices[i].n * 3 + 0]);
    vertices.push_back(mesh->normals[mesh->indices[i].n * 3 + 1]);
    vertices.push_back(mesh->normals[mesh->indices[i].n * 3 + 2]);
  }

  fast_obj_destroy(mesh);

  { // vertices
    void *data;
    Buffer stagingBuffer;
    BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = size;
    bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_SRC;
    pkCreateBuffer(device, &bufferCreateInfo, &stagingBuffer, &data);

    memcpy(data, vertices.data(), size);

    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                  BufferUsageFlagBits::BUF_VERTEX_BUFFER;
    bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
    pkCreateBuffer(device, &bufferCreateInfo, &result.vertexBuffer, &data);

    pkCopy(cmdBuffer, result.vertexBuffer, stagingBuffer);

    pkDestroyBuffer(device, stagingBuffer);
  }
  auto barrier = BufferBarrier{
      SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
                           AccessFlagBits::TRANSFER_WRITE_BIT,
                           QueueType::Transfer},
      SynchronizationScope{PipelineStageFlagBits::GRAPHICS_VERTEX_INPUT_BIT |
                               PipelineStageFlagBits::GRAPHICS_VERTEX_SHADER_BIT,
                           AccessFlagBits::VERTEX_ATTRIBUTE_READ_BIT,
                           QueueType::Graphics},
      result.vertexBuffer};

  insertBarrier(cmdBuffer, &barrier);

  return result;
}

Texture
pkCreateDepthTexture(Device device, int width, int height)
{
  TextureCreateInfo textureCreateInfo = {};
  textureCreateInfo.width = width;
  textureCreateInfo.height = height;
  textureCreateInfo.depth = 1;
  textureCreateInfo.format = PixelFormat::D32_FLOAT;
  textureCreateInfo.mipLevels = 1;
  textureCreateInfo.layers = 1;
  textureCreateInfo.usageFlags =
      TextureUsageFlagBits::TEX_DEPTH_STENCIL_ATTACHMENT;

  Texture texture;
  pkCreateTexture(device, &textureCreateInfo, &texture);

  return texture;
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  int width = 512;
  int height = 512;

  auto window = glfwCreateWindow(width, height, "pbr", 0, 0);
  auto hwnd = glfwGetWin32Window(window);

  Device device;
  pkCreateDevice(&device);

  SwapchainCreateInfo swapchainCreateInfo = {};
  swapchainCreateInfo.width = width;
  swapchainCreateInfo.height = height;
  swapchainCreateInfo.depth = 1;
  swapchainCreateInfo.format = PixelFormat::RGBA8_UNORM_SRGB;
  swapchainCreateInfo.usageFlags = TextureUsageFlagBits::TEX_COLOR_ATTACHMENT;
  swapchainCreateInfo.textureCnt = 3;
  swapchainCreateInfo.platformHandle = (void *)hwnd;

  Swapchain swapchain;
  pkCreateSwapchain(device, &swapchainCreateInfo, &swapchain);

  PipelineState state = {};
  state.shader.vertexShader = "resources/shaders/pbr.vert.spv";
  state.shader.fragmentShader = "resources/shaders/pbr.frag.spv";

  state.vertexInput.bindingDescriptions[0].binding = 0;
  state.vertexInput.bindingDescriptions[0].inputRate = VertexInputRate::VERTEX;
  state.vertexInput.bindingDescriptions[0].stride = sizeof(float) * 3 * 2;
  state.vertexInput.bindingDescriptionCnt = 1;

  state.vertexInput.attributeDescriptions[0].binding = 0;
  state.vertexInput.attributeDescriptions[0].location = 0;
  state.vertexInput.attributeDescriptions[0].offset = 0;
  state.vertexInput.attributeDescriptions[0].format = VertexFormat::FLOAT3;

  state.vertexInput.attributeDescriptions[1].binding = 0;
  state.vertexInput.attributeDescriptions[1].location = 1;
  state.vertexInput.attributeDescriptions[1].offset = sizeof(float) * 3;
  state.vertexInput.attributeDescriptions[1].format = VertexFormat::FLOAT3;
  state.vertexInput.attributeDescriptionCnt = 2;

  state.inputAssembly.topology = PrimitiveTopology::TRIANGLE_LIST;

  state.rasterization.polygonMode = PolygonMode::FILL;
  state.rasterization.cullMode = CullMode::BACK;
  state.rasterization.frontFace = FrontFace::COUNTER_CLOCKWISE;

  state.viewport.viewport.x = 0;
  state.viewport.viewport.y = 0;
  state.viewport.viewport.width = static_cast<float>(swapchainCreateInfo.width);
  state.viewport.viewport.height =
      static_cast<float>(swapchainCreateInfo.height);
  state.viewport.viewport.minDepth = 0.f;
  state.viewport.viewport.maxDepth = 1.f;
  state.viewport.scissors.x = 0;
  state.viewport.scissors.y = 0;
  state.viewport.scissors.width = swapchainCreateInfo.width;
  state.viewport.scissors.height = swapchainCreateInfo.height;

  state.depthStencil.depthTestenable = true;
  state.depthStencil.depthWriteEnable = true;
  state.depthStencil.depthCompareOp = CompareOp::LESS;

  Texture depthTexture = pkCreateDepthTexture(device, width, height);

  Mesh mesh = {};
  UBO ubo = {};

  Buffer uniformBuffer;
  void *data;
  BufferCreateInfo bufferCreateInfo;
  bufferCreateInfo.size = sizeof(ubo);
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER |
                                BufferUsageFlagBits::BUF_TRANSFER_SRC;
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;

  pkCreateBuffer(device, &bufferCreateInfo, &uniformBuffer, &data);

  ubo.cameraPos = {0.f, -18.f, 13.f};
  ubo.model = glm::scale(glm::identity<glm::mat4>(), {1.f, -1.f, 1.f});
  ubo.view =
      glm::lookAt(ubo.cameraPos, glm::vec3{}, glm::vec3{0.f, 1.f, 0.f});
  ubo.proj =
      glm::perspective(50.f / 180.f * glm::pi<float>(), 1.f, 0.1f, 1000.f);

  while (true)
  {
    Texture swapchainTexture;

    ubo.model = glm::rotate(ubo.model, 0.0002f, glm::vec3{0, 1, 0});
    memcpy(data, &ubo, sizeof(ubo));

    Semaphore available;
    while (!acquireNext(device, swapchain, &swapchainTexture, &available))
    {
      glfwGetWindowSize(window, &width, &height);
      state.viewport.scissors.width = width;
      state.viewport.scissors.height = height;
      state.viewport.viewport.width = static_cast<float>(width);
      state.viewport.viewport.height = static_cast<float>(height);

      swapchainCreateInfo.width = width;
      swapchainCreateInfo.height = height;

      pkRecreateSwapchain(device, &swapchainCreateInfo, swapchain);
      pkDestroyTexture(device, depthTexture);
      depthTexture = pkCreateDepthTexture(device, width, height);
    }

    Queue queue;
    CmdBuffer cmdBuffer;

    pkGetQueue(device, QueueType::Graphics, &queue);
    pkCreateCmdBuffer(queue, &cmdBuffer);

    if (!mesh.vertexBuffer)
    {
      mesh = uploadMesh(device, cmdBuffer);
    }

    auto textureBarrier = TextureBarrier{
        SynchronizationScope{PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0},
        SynchronizationScope{
            PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
            AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
                AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT},
        TextureLayout::UNDEFINED,
        TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
        swapchainTexture};

    insertBarrier(cmdBuffer, &textureBarrier);

    textureBarrier.dst = SynchronizationScope{
        PipelineStageFlagBits::GRAPHICS_EARLY_FRAGMENT_TESTS_BIT |
            PipelineStageFlagBits::GRAPHICS_LATE_FRAGMENT_TESTS_BIT,
        AccessFlagBits::DEPTH_STENCIL_ATTACHMENT_READ_BIT |
            AccessFlagBits::DEPTH_STENCIL_ATTACHMENT_WRITE_BIT};
    textureBarrier.finalLayout =
        TextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    textureBarrier.texture = depthTexture;

    insertBarrier(cmdBuffer, &textureBarrier);

    RenderPass renderPass = {};
    renderPass.attachmentCnt = 2;
    renderPass.attachmentInfos[0].clearValue = {0., 0., 0., 1};
    renderPass.attachmentInfos[0].texture = swapchainTexture;
    renderPass.attachmentInfos[0].type = AttachmentType::COLOR;
    renderPass.attachmentInfos[0].loadOp = LoadOp::CLEAR;
    renderPass.attachmentInfos[0].storeOp = StoreOp::STORE;

    renderPass.attachmentInfos[1].clearValue = {1.f};
    renderPass.attachmentInfos[1].texture = depthTexture;
    renderPass.attachmentInfos[1].type = AttachmentType::DEPTH;
    renderPass.attachmentInfos[1].loadOp = LoadOp::CLEAR;
    renderPass.attachmentInfos[1].storeOp = StoreOp::DONT_CARE;

    beginRenderPass(cmdBuffer, &renderPass);
    setPipelineState(cmdBuffer, &state);
    bindVertexBuffer(cmdBuffer, mesh.vertexBuffer, 0);
    bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 0, 0, sizeof(UBO));
    draw(cmdBuffer, mesh.vertexCnt);
    endRenderPass(cmdBuffer);

    textureBarrier = TextureBarrier{
        SynchronizationScope{
            PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
            AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
                AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT},
        SynchronizationScope{PipelineStageFlagBits::BOTTOM_OF_PIPE_BIT, 0},
        TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
        TextureLayout::PRESENT_SRC_KHR,
        swapchainTexture};

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

    if (!present(queue, swapchain, &renderDone))
    {
      glfwGetWindowSize(window, &width, &height);
      state.viewport.scissors.width = width;
      state.viewport.scissors.height = height;
      state.viewport.viewport.width = static_cast<float>(width);
      state.viewport.viewport.height = static_cast<float>(height);

      swapchainCreateInfo.width = width;
      swapchainCreateInfo.height = height;

      pkRecreateSwapchain(device, &swapchainCreateInfo, swapchain);

      pkDestroyTexture(device, depthTexture);
      depthTexture = pkCreateDepthTexture(device, width, height);
    }

    frame(device);
    glfwPollEvents();
  }
}
