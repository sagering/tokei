#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <pokei.h>

#include <chrono>
#include <iostream>
#include <vector>

double
nowd()
{
  return std::chrono::duration_cast<std::chrono::duration<double>>(
           std::chrono::steady_clock::now().time_since_epoch())
    .count();
}

struct Time
{
  double start;
};

double
elapsed(Time* t)
{
  return nowd() - t->start;
}

void
reset(Time* t)
{
  t->start = nowd();
}

struct Fps
{
  double start;
  uint32_t fps = 0;
};

void
fps_update(Fps* fps)
{
  auto now = nowd();

  if (now - fps->start >= 1.0) {
    std::cout << "FPS: " << fps->fps << std::endl;
    fps->fps = 0;
    fps->start = now;
  } else {
    fps->fps += 1;
  }
}

std::vector<float> const vertices = { 1.0f, 0.0f,  0.0f, 0.0f,  1.0f, 0.0f,
                                      0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
                                      0.0f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f };

int
main()
{
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  int width = 512;
  int height = 512;

  auto window = glfwCreateWindow(width, height, "basic", 0, 0);
  auto hwnd = glfwGetWin32Window(window);

  Device device;
  pkCreateDevice(&device);

  void* data;
  Buffer stagingBuffer;
  BufferCreateInfo bufferCreateInfo;
  bufferCreateInfo.size = vertices.size() * sizeof(float);
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_SRC;
  pkCreateBuffer(device, &bufferCreateInfo, &stagingBuffer, &data);
  memcpy(data, vertices.data(), vertices.size() * sizeof(float));

  Buffer vertexBuffer;
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                BufferUsageFlagBits::BUF_VERTEX_BUFFER;
  bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
  void* dummy;
  pkCreateBuffer(device, &bufferCreateInfo, &vertexBuffer, &dummy);

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
  state.shader.vertexShader = "resources/shaders/basic.vert.spv";
  state.shader.fragmentShader = "resources/shaders/basic.frag.spv";

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

  TextureCreateInfo textureCreateInfo = {};
  textureCreateInfo.width = 10;
  textureCreateInfo.height = 10;
  textureCreateInfo.depth = 1;
  textureCreateInfo.format = PixelFormat::RGBA8_UNORM;
  textureCreateInfo.layers = 1;
  textureCreateInfo.mipLevels = 1;
  textureCreateInfo.usageFlags =
    TextureUsageFlagBits::TEX_SAMPLED | TextureUsageFlagBits::TEX_TRANSFER_DST;

  Texture sampledTexture;
  pkCreateTexture(device, &textureCreateInfo, &sampledTexture);

  uint8_t const dr = 1;
  uint8_t const dg = 2;
  uint8_t const db = 3;

  struct Color
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  } color = {};

  Time t;
  reset(&t);

  Fps fps;

  while (true) {
    auto dt = elapsed(&t);
    if (dt > 0.1) {
      color.g += dg;
      color.b += db;
      color.a = 255;
      reset(&t);
    }

    Buffer uniformBuffer;
    void* data;
    bufferCreateInfo.size = 10 * 10 * 4;
    bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER |
                                  BufferUsageFlagBits::BUF_TRANSFER_SRC;
    bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;

    pkCreateBuffer(device, &bufferCreateInfo, &uniformBuffer, &data);
    memcpy(data, &color, sizeof(color));

    Texture swapchainTexture;
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

    auto bufferBarrier = BufferBarrier{
      SynchronizationScope{ PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0 },
      SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                            AccessFlagBits::TRANSFER_WRITE_BIT },
      vertexBuffer
    };

    insertBarrier(cmdBuffer, &bufferBarrier);

    pkCopy(cmdBuffer, vertexBuffer, stagingBuffer);

    auto textureBarrier = TextureBarrier{
      SynchronizationScope{ PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0 },
      SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                            AccessFlagBits::TRANSFER_WRITE_BIT },
      TextureLayout::UNDEFINED,
      TextureLayout::TRANSFER_DST_OPTIMAL,
      sampledTexture
    };

    insertBarrier(cmdBuffer, &textureBarrier);

    pkCopyBufferToTexture(cmdBuffer, sampledTexture, uniformBuffer);

    bufferBarrier = BufferBarrier{
      SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                            AccessFlagBits::TRANSFER_WRITE_BIT },
      SynchronizationScope{ PipelineStageFlagBits::GRAPHICS_VERTEX_SHADER_BIT |
                              PipelineStageFlagBits::GRAPHICS_VERTEX_INPUT_BIT,
                            AccessFlagBits::VERTEX_ATTRIBUTE_READ_BIT },
      vertexBuffer
    };

    insertBarrier(cmdBuffer, &bufferBarrier);

    textureBarrier = TextureBarrier{
      SynchronizationScope{ PipelineStageFlagBits::TRANSFER_BIT,
                            AccessFlagBits::TRANSFER_WRITE_BIT },
      SynchronizationScope{ PipelineStageFlagBits::GRAPHICS_FRAGMENT_SHADER_BIT,
                            AccessFlagBits::SHADER_READ_BIT },
      TextureLayout::TRANSFER_DST_OPTIMAL,
      TextureLayout::SHADER_READ_ONLY_OPTIMAL,
      sampledTexture
    };

    insertBarrier(cmdBuffer, &textureBarrier);

    textureBarrier = TextureBarrier{
      SynchronizationScope{ PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0 },
      SynchronizationScope{
        PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
        AccessFlagBits::COLOR_ATTACHMENT_READ_BIT |
          AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT },
      TextureLayout::UNDEFINED,
      TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
      swapchainTexture
    };

    insertBarrier(cmdBuffer, &textureBarrier);

    RenderPass renderPass = {};
    renderPass.attachmentCnt = 1;
    renderPass.attachmentInfos[0].clearValue = { 1., 0., 0., 1 };
    renderPass.attachmentInfos[0].texture = swapchainTexture;
    renderPass.attachmentInfos[0].type = AttachmentType::COLOR;
    renderPass.attachmentInfos[0].loadOp = LoadOp::CLEAR;
    renderPass.attachmentInfos[0].storeOp = StoreOp::STORE;
    beginRenderPass(cmdBuffer, &renderPass);

    setPipelineState(cmdBuffer, &state);
    bindVertexBuffer(cmdBuffer, vertexBuffer, 0);
    bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 0, 0, 10 * 10 * 4);
    bindSampledTexture(cmdBuffer, sampledTexture, 0, 1);
    bindSampler(cmdBuffer, 0, 2);
    draw(cmdBuffer, 3);
    bindVertexBuffer(cmdBuffer, vertexBuffer, 9 * sizeof(float));
    draw(cmdBuffer, 3);
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

    pkDestroyBuffer(device, uniformBuffer);
    frame(device);

    fps_update(&fps);

    glfwPollEvents();
  }
}
