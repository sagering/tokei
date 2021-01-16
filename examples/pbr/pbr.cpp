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

Mesh
uploadMesh(Device* device, CmdBuffer* cmdBuffer)
{
  fastObjMesh* mesh = fast_obj_read("resources/meshes/dragon.obj");
  Mesh result = {};

  result.vertexCnt = mesh->face_count * 3;
  uint32_t const size = sizeof(float) * 3 * 2 * result.vertexCnt;

  {
    // asserting that all faces are triangles
    auto idxCnt = 0;

    for (unsigned int i = 0; i < mesh->face_count; ++i) {
      idxCnt += 3 * (mesh->face_vertices[i] - 2);
    }

    assert(idxCnt == mesh->face_count * 3);
  }

  std::vector<float> vertices = {};

  for (uint32_t i = 0; i < result.vertexCnt; ++i) {
    vertices.push_back(mesh->positions[mesh->indices[i].p * 3 + 0]);
    vertices.push_back(mesh->positions[mesh->indices[i].p * 3 + 1]);
    vertices.push_back(mesh->positions[mesh->indices[i].p * 3 + 2]);
    vertices.push_back(mesh->normals[mesh->indices[i].n * 3 + 0]);
    vertices.push_back(mesh->normals[mesh->indices[i].n * 3 + 1]);
    vertices.push_back(mesh->normals[mesh->indices[i].n * 3 + 2]);
  }

  fast_obj_destroy(mesh);

  { // vertices
    void* data;
    Buffer stagingBuffer;
    BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = size;
    bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_SRC;
    std::tie(stagingBuffer, data) = device->CreateBuffer(bufferCreateInfo);

    memcpy(data, vertices.data(), size);

    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                  BufferUsageFlagBits::BUF_VERTEX_BUFFER;
    bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
    std::tie(result.vertexBuffer, std::ignore) =
      device->CreateBuffer(bufferCreateInfo);

    cmdBuffer->Copy(result.vertexBuffer, stagingBuffer);

    device->Release(stagingBuffer);
  }

  cmdBuffer->BufferBarrier({ BufferBarrierScope::None,
                             BufferBarrierScope::VertexBuffer,
                             result.vertexBuffer });

  return result;
}

Texture
CreateDepthTexture(Device* device, int width, int height)
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

  return device->CreateTexture(textureCreateInfo);
}

int
main()
{
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  int width = 512;
  int height = 512;

  auto window = glfwCreateWindow(width, height, "pbr", 0, 0);
  auto hwnd = glfwGetWin32Window(window);

  auto device = Device::Create();

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

  Texture depthTexture = CreateDepthTexture(device, width, height);

  Mesh mesh = {};
  UBO ubo = {};

  Buffer uniformBuffer;
  void* data;
  BufferCreateInfo bufferCreateInfo;
  bufferCreateInfo.size = sizeof(ubo);
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER |
                                BufferUsageFlagBits::BUF_TRANSFER_SRC;
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;
  std::tie(uniformBuffer, data) = device->CreateBuffer(bufferCreateInfo);

  ubo.cameraPos = { 0.f, -18.f, 13.f };
  ubo.model = glm::scale(glm::identity<glm::mat4>(), { 1.f, -1.f, 1.f });
  ubo.view =
    glm::lookAt(ubo.cameraPos, glm::vec3{}, glm::vec3{ 0.f, 1.f, 0.f });
  ubo.proj =
    glm::perspective(50.f / 180.f * glm::pi<float>(), 1.f, 0.1f, 1000.f);

  while (true) {
    Texture swapchainTexture;

    ubo.model = glm::rotate(ubo.model, 0.0002f, glm::vec3{ 0, 1, 0 });
    memcpy(data, &ubo, sizeof(ubo));

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
      device->Release(depthTexture);
      depthTexture = CreateDepthTexture(device, width, height);
    }

    CmdBuffer* cmdBuffer = device->GetCmdBuffer();

    if (!mesh.vertexBuffer) {
      mesh = uploadMesh(device, cmdBuffer);
    }

    cmdBuffer->TextureBarrier({ TextureBarrierScope::None,
                                TextureBarrierScope::ColorAttachment,
                                swapchainTexture });

    cmdBuffer->TextureBarrier({ TextureBarrierScope::None,
                                TextureBarrierScope::DepthStencilAttachment,
                                depthTexture });

    RenderPassBeginInfo beginInfo = {};
    beginInfo.attachmentCnt = 2;
    beginInfo.attachmentInfos[0].clearValue = { 0., 0., 0., 1 };
    beginInfo.attachmentInfos[0].texture = swapchainTexture;
    beginInfo.attachmentInfos[0].type = AttachmentType::COLOR;
    beginInfo.attachmentInfos[0].loadOp = LoadOp::CLEAR;
    beginInfo.attachmentInfos[0].storeOp = StoreOp::STORE;

    beginInfo.attachmentInfos[1].clearValue = { 1.f };
    beginInfo.attachmentInfos[1].texture = depthTexture;
    beginInfo.attachmentInfos[1].type = AttachmentType::DEPTH;
    beginInfo.attachmentInfos[1].loadOp = LoadOp::CLEAR;
    beginInfo.attachmentInfos[1].storeOp = StoreOp::DONT_CARE;

    cmdBuffer->BeginRenderPass(beginInfo);

    cmdBuffer->SetPipelineState(state);
    cmdBuffer->BindVertexBuffer(mesh.vertexBuffer, 0);
    cmdBuffer->BindUniformBuffer(uniformBuffer, 0, 0);
    cmdBuffer->Draw(mesh.vertexCnt);
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

      device->Release(depthTexture);
      depthTexture = CreateDepthTexture(device, width, height);
    }

    device->Recycle();
    glfwPollEvents();
  }
}
