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

struct Material
{
  PipelineState pipeline;
};

struct Object
{
  Mesh mesh;
  MVP mvp;
  Material material;
  float rotationSpeed;
};

std::vector<Object> objects;

float
getRand()
{
  return rand() / (float)RAND_MAX;
}

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

Material
getMaterial(uint32_t viewportWidth, uint32_t viewportHeight, uint32_t samples)
{
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
  state.viewport.viewport.width = static_cast<float>(viewportWidth);
  state.viewport.viewport.height = static_cast<float>(viewportHeight);
  state.viewport.viewport.minDepth = 0.f;
  state.viewport.viewport.maxDepth = 1.f;
  state.viewport.scissors.x = 0;
  state.viewport.scissors.y = 0;
  state.viewport.scissors.width = viewportWidth;
  state.viewport.scissors.height = viewportHeight;

  state.multisample.rasterizationSamples = samples;

  state.depthStencil.depthWriteEnable = true;
  state.depthStencil.depthTestenable = true;
  state.depthStencil.depthCompareOp = CompareOp::LESS;

  return { state };
}

void
addRandomObject(Device* device,
                CmdBuffer* cmdBuffer,
                uint32_t viewportWidth,
                uint32_t viewportHeight,
                uint32_t samples)
{
  Object object = {};
  object.mesh = uploadSuzanne(device, cmdBuffer);
  object.material = getMaterial(viewportWidth, viewportHeight, samples);

  float scale = 0.2 * getRand() + 0.1;
  float x = 1.f - 2.f * getRand();
  float y = 1.f - 2.f * getRand();

  object.mvp.proj = glm::identity<glm::mat4>();
  object.mvp.view = glm::identity<glm::mat4>();
  object.mvp.model = glm::identity<glm::mat4>();

  object.mvp.model =
    glm::translate(object.mvp.model, glm::vec3{ x, y, 0.5f }); // move closer
  object.mvp.model = glm::scale(
    object.mvp.model, glm::vec3{ scale, -scale, 0.5 }); // scale down, flip y

  object.rotationSpeed = getRand();
  objects.push_back(object);
}

int
main()
{
  srand(time(NULL));

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  uint32_t samples = 1;

  int width = 512 * 2;
  int height = 512 * 2;

  auto window = glfwCreateWindow(width, height, "multiple objects", 0, 0);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

  TextureCreateInfo textureCreateInfo = {};
  textureCreateInfo.width = width;
  textureCreateInfo.height = height;
  textureCreateInfo.depth = 1;
  textureCreateInfo.format = PixelFormat::D32_FLOAT;
  textureCreateInfo.mipLevels = 1;
  textureCreateInfo.layers = 1;
  textureCreateInfo.usageFlags =
    TextureUsageFlagBits::TEX_DEPTH_STENCIL_ATTACHMENT;

  Texture depthTexture = device->CreateTexture(textureCreateInfo);

  struct Uniforms
  {
    uint32_t const UBO_BUFFER_SIZE = 1024 * 10;
    uint32_t const NUM_UBOS = 3;

    Buffer buffer;
    void* data;

    uint32_t next = 0;
    Ticket tickets[3] = {};

    void Init(Device* device)
    {
      BufferCreateInfo bufferCreateInfo = {
        UBO_BUFFER_SIZE * NUM_UBOS,
        BufferUsageFlagBits::BUF_UNIFORM_BUFFER |
          BufferUsageFlagBits::BUF_TRANSFER_SRC,
        MemoryUsage::CPU_TO_GPU
      };

      std::tie(buffer, data) = device->CreateBuffer(bufferCreateInfo);
    }

    uint32_t GetNextOfset(Device* device)
    {
      uint32_t offset = next * UBO_BUFFER_SIZE;
      device->Wait(tickets[next]);
      next = (next + 1) % NUM_UBOS;
      return offset;
    }
  } uniforms;

  uniforms.Init(device);

  bool initDone = false;

  while (true) {
    auto offset = uniforms.GetNextOfset(device);

    uint32_t objIdx = 0;
    for (auto& obj : objects) {
      obj.mvp.model = glm::rotate(
        obj.mvp.model, obj.rotationSpeed * 0.02f, glm::vec3{ 0, 1, 0 });
      memcpy(static_cast<uint8_t*>(uniforms.data) + offset +
               objIdx * sizeof(obj.mvp),
             &obj.mvp,
             sizeof(obj.mvp));
      ++objIdx;
    }

    Texture swapchainTexture;
    device->AquireNext(swapchain, &swapchainTexture);

    CmdBuffer* cmdBuffer = device->GetCmdBuffer();

    if (!initDone) {
      initDone = true;
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
      addRandomObject(device, cmdBuffer, width, height, samples);
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
    beginInfo.attachmentInfos[0].makePresentable = false;

    beginInfo.attachmentInfos[1].clearValue = { 1.f };
    beginInfo.attachmentInfos[1].texture = depthTexture;
    beginInfo.attachmentInfos[1].type = AttachmentType::DEPTH;
    beginInfo.attachmentInfos[1].loadOp = LoadOp::CLEAR;
    beginInfo.attachmentInfos[1].storeOp = StoreOp::STORE;
    beginInfo.attachmentInfos[1].makePresentable = false;

    cmdBuffer->BeginRenderPass(beginInfo);

    // draw all objects

    objIdx = 0;
    for (auto const& obj : objects) {
      cmdBuffer->BindVertexBuffer(obj.mesh.vbuf, 0);
      cmdBuffer->BindIndexBuffer(obj.mesh.ibuf);
      cmdBuffer->BindUniformBuffer(
        uniforms.buffer,
        0,
        0,
        offset +
          objIdx *
            sizeof(obj.mvp), // has to be aligned to required device aligned
        sizeof(obj.mvp));

      cmdBuffer->SetPipelineState(obj.material.pipeline);
      cmdBuffer->DrawIndexed(obj.mesh.triCnt * 3);
      ++objIdx;
    }

    cmdBuffer->EndRenderPass();

    cmdBuffer->TextureBarrier({ TextureBarrierScope::ColorAttachment,
                                TextureBarrierScope::PresentSrc,
                                swapchainTexture });

    device->Submit(cmdBuffer);
    device->Present(swapchain);

    device->Recycle();
    glfwPollEvents();
  }
}
