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

BufferBarrier
indexBufferTransferToGraphics(Buffer buffer)
{
  return BufferBarrier{
    SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                          AccessFlagBits::TRANSFER_WRITE_BIT,
                          QueueType::Transfer },
    SynchronizationScope{ PipelineStageFlagBits::GRAPHICS_VERTEX_INPUT_BIT |
                            PipelineStageFlagBits::GRAPHICS_VERTEX_SHADER_BIT,
                          AccessFlagBits::INDEX_READ_BIT,
                          QueueType::Graphics },
    buffer
  };
}

BufferBarrier
vertexBufferTransferToGraphics(Buffer buffer)
{
  return BufferBarrier{
    SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                          AccessFlagBits::TRANSFER_WRITE_BIT,
                          QueueType::Transfer },
    SynchronizationScope{ PipelineStageFlagBits::GRAPHICS_VERTEX_INPUT_BIT |
                            PipelineStageFlagBits::GRAPHICS_VERTEX_SHADER_BIT,
                          AccessFlagBits::VERTEX_ATTRIBUTE_READ_BIT,
                          QueueType::Graphics },
    buffer
  };
}

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

    pkCreateBuffer(device, &bufferCreateInfo, &result.vbuf, &data);
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
    pkCreateBuffer(device, &bufferCreateInfo, &result.ibuf, &data);

    pkCopy(cmdBuffer, result.ibuf, stagingBuffer);
    pkDestroyBuffer(device, stagingBuffer);
  }

  auto barrier = vertexBufferTransferToGraphics(result.vbuf);
  insertBarrier(cmdBuffer, &barrier);
  barrier = indexBufferTransferToGraphics(result.vbuf);
  insertBarrier(cmdBuffer, &barrier);

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
addRandomObject(Device device,
                CmdBuffer cmdBuffer,
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

  Device device;
  pkCreateDevice(&device);

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

  TextureCreateInfo textureCreateInfo = {};
  textureCreateInfo.width = width;
  textureCreateInfo.height = height;
  textureCreateInfo.depth = 1;
  textureCreateInfo.format = PixelFormat::D32_FLOAT;
  textureCreateInfo.mipLevels = 1;
  textureCreateInfo.layers = 1;
  textureCreateInfo.usageFlags =
    TextureUsageFlagBits::TEX_DEPTH_STENCIL_ATTACHMENT;

  Texture depthTexture;
  pkCreateTexture(device, &textureCreateInfo, &depthTexture);

  struct Uniforms
  {
    uint32_t const UBO_BUFFER_SIZE = 1024 * 100;
    uint32_t const NUM_UBOS = 3;

    Buffer buffer;
    void* data;

    uint32_t cur = 0;
    Fence fences[3] = {};

    void Init(Device device)
    {
      BufferCreateInfo bufferCreateInfo = {
        UBO_BUFFER_SIZE * NUM_UBOS,
        BufferUsageFlagBits::BUF_UNIFORM_BUFFER |
          BufferUsageFlagBits::BUF_TRANSFER_SRC,
        MemoryUsage::CPU_TO_GPU
      };

      pkCreateBuffer(device, &bufferCreateInfo, &buffer, &data);
    }

    uint32_t GetNextOfset(Device device)
    {
      uint32_t offset = cur * UBO_BUFFER_SIZE;
      if (fences[cur])
        wait(device, fences[cur]);
      return offset;
    }

    void Inc(Fence fence)
    {
      fences[cur] = fence;
      cur = (cur + 1) % NUM_UBOS;
    }

  } uniforms;

  uniforms.Init(device);

  bool uploadDone = false;
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
    Semaphore available;

    acquireNext(device, swapchain, &swapchainTexture, &available);

    Semaphore transferDone = 0;
    if (!uploadDone) {
      // uploadDone = true;

      for (auto& obj : objects) {
        pkDestroyBuffer(device, obj.mesh.ibuf);
        pkDestroyBuffer(device, obj.mesh.vbuf);
      }

      objects.clear();

      Queue transferQueue;
      pkGetQueue(device, QueueType::Transfer, &transferQueue);
      CmdBuffer cmdBuffer;
      pkCreateCmdBuffer(transferQueue, &cmdBuffer);

      for (int i = 0; i < 100; ++i) {
        addRandomObject(device, cmdBuffer, width, height, samples);
      }
      submit(transferQueue,
             &cmdBuffer,
             1,
             nullptr,
             nullptr,
             0,
             &transferDone,
             1,
             nullptr);
    }

    {
      Queue graphicsQueue;
      CmdBuffer cmdBuffer;

      pkGetQueue(device, QueueType::Graphics, &graphicsQueue);
      pkCreateCmdBuffer(graphicsQueue, &cmdBuffer);

      // transfer buffer ownership to graphics queue
      if (!initDone) {
        // initDone = true;

        for (auto& obj : objects) {
          auto barrier = indexBufferTransferToGraphics(obj.mesh.ibuf);
          insertBarrier(cmdBuffer, &barrier);
          barrier = vertexBufferTransferToGraphics(obj.mesh.vbuf);
          insertBarrier(cmdBuffer, &barrier);
        }
      }

      auto tbarrier = TextureBarrier{
        { PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0, QueueType::Graphics },
        { PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
          AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT |
            AccessFlagBits::COLOR_ATTACHMENT_READ_BIT,
          QueueType::Graphics },
        TextureLayout::UNDEFINED,
        TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
        swapchainTexture
      };

      insertBarrier(cmdBuffer, &tbarrier);

      tbarrier.dst = {
        PipelineStageFlagBits::GRAPHICS_EARLY_FRAGMENT_TESTS_BIT |
          PipelineStageFlagBits::GRAPHICS_LATE_FRAGMENT_TESTS_BIT,
        AccessFlagBits::DEPTH_STENCIL_ATTACHMENT_READ_BIT |
          AccessFlagBits::DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        QueueType::Graphics
      };
      tbarrier.finalLayout = TextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
      tbarrier.texture = depthTexture;

      insertBarrier(cmdBuffer, &tbarrier);

      RenderPass renderPass = {};
      renderPass.attachmentCnt = 2;
      renderPass.attachmentInfos[0].clearValue = { 0., 0., 0., 1 };
      renderPass.attachmentInfos[0].texture = swapchainTexture;
      renderPass.attachmentInfos[0].type = AttachmentType::COLOR;
      renderPass.attachmentInfos[0].loadOp = LoadOp::CLEAR;
      renderPass.attachmentInfos[0].storeOp = StoreOp::STORE;
      renderPass.attachmentInfos[0].makePresentable = false;

      renderPass.attachmentInfos[1].clearValue = { 1.f };
      renderPass.attachmentInfos[1].texture = depthTexture;
      renderPass.attachmentInfos[1].type = AttachmentType::DEPTH;
      renderPass.attachmentInfos[1].loadOp = LoadOp::CLEAR;
      renderPass.attachmentInfos[1].storeOp = StoreOp::STORE;
      renderPass.attachmentInfos[1].makePresentable = false;

      beginRenderPass(cmdBuffer, &renderPass);

      // draw all objects

      objIdx = 0;
      for (auto const& obj : objects) {
        bindVertexBuffer(cmdBuffer, obj.mesh.vbuf, 0);
        bindIndexBuffer(cmdBuffer, obj.mesh.ibuf);
        bindUniformBuffer(
          cmdBuffer,
          uniforms.buffer,
          0,
          0,
          offset +
            objIdx *
              sizeof(obj.mvp), // has to be aligned to required device aligned
          sizeof(obj.mvp));

        setPipelineState(cmdBuffer, &obj.material.pipeline);
        drawIndexed(cmdBuffer, obj.mesh.triCnt * 3);
        ++objIdx;
      }

      endRenderPass(cmdBuffer);

      tbarrier.src = {
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
        AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT |
          AccessFlagBits::COLOR_ATTACHMENT_READ_BIT,
        QueueType::Graphics
      };
      tbarrier.dst = { PipelineStageFlagBits::BOTTOM_OF_PIPE_BIT,
                       0,
                       QueueType::Graphics };
      tbarrier.initialLayout = TextureLayout::COLOR_ATTACHMENT_OPTIMAL;
      tbarrier.finalLayout = TextureLayout::PRESENT_SRC_KHR;
      tbarrier.texture = swapchainTexture;

      insertBarrier(cmdBuffer, &tbarrier);

      Semaphore renderDone;
      Fence fence;

      Semaphore waitSemaphores[2];
      waitSemaphores[0] = available;
      waitSemaphores[1] = transferDone;

      PipelineStageFlags waitStages[2];
      waitStages[0] = PipelineStageFlagBits::GRAPHICS_VERTEX_INPUT_BIT |
                      PipelineStageFlagBits::GRAPHICS_VERTEX_SHADER_BIT;
      waitStages[1] =
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT;

      submit(graphicsQueue,
             &cmdBuffer,
             1,
             waitSemaphores,
             waitStages,
             transferDone ? 2 : 1,
             &renderDone,
             1,
             &fence);
      uniforms.Inc(fence);

      present(graphicsQueue, swapchain, &renderDone);
    }

    frame(device);

    glfwPollEvents();
  }
}
