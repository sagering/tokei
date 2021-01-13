#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <cmd_buffer.h>
#include <device.h>

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

  auto device = Device::Create();

  void* data;
  Buffer stagingBuffer;
  BufferCreateInfo bufferCreateInfo;
  bufferCreateInfo.size = vertices.size() * sizeof(float);
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_SRC;
  std::tie(stagingBuffer, data) = device->CreateBuffer(bufferCreateInfo);
  memcpy(data, vertices.data(), vertices.size() * sizeof(float));

  Buffer vertexBuffer;
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                BufferUsageFlagBits::BUF_VERTEX_BUFFER;
  bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
  bufferCreateInfo.name = nullptr;
  std::tie(vertexBuffer, std::ignore) = device->CreateBuffer(bufferCreateInfo);

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

  TextureCreateInfo textureDesc0 = {};
  textureDesc0.width = 10;
  textureDesc0.height = 10;
  textureDesc0.depth = 1;
  textureDesc0.format = PixelFormat::RGBA8_UNORM;
  textureDesc0.layers = 1;
  textureDesc0.mipLevels = 1;
  textureDesc0.usageFlags =
    TextureUsageFlagBits::TEX_SAMPLED | TextureUsageFlagBits::TEX_TRANSFER_DST;
  textureDesc0.name = "sampledTexture";

  auto sampledTexture = device->CreateTexture(textureDesc0);

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
    bufferCreateInfo.name = nullptr;

    std::tie(uniformBuffer, data) = device->CreateBuffer(bufferCreateInfo);
    memcpy(data, &color, sizeof(color));

    Texture swapchainTexture;

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

    for (auto i = 0; i < 2; ++i) {
      CmdBuffer* cmdBuffer = device->GetCmdBuffer();

      cmdBuffer->Copy(vertexBuffer, stagingBuffer);

      cmdBuffer->TextureBarrier({ TextureBarrierScope::None,
                                  TextureBarrierScope::TransferDst,
                                  sampledTexture });

      cmdBuffer->CopyBufferToTexture(sampledTexture, uniformBuffer);

      cmdBuffer->BufferBarrier({ BufferBarrierScope::TransferDst,
                                 BufferBarrierScope::VertexBuffer,
                                 vertexBuffer });

      cmdBuffer->TextureBarrier({ TextureBarrierScope::TransferDst,
                                  TextureBarrierScope::SampledTexture,
                                  sampledTexture });

      cmdBuffer->TextureBarrier({ TextureBarrierScope::None,
                                  TextureBarrierScope::ColorAttachment,
                                  swapchainTexture });

      RenderPassBeginInfo beginInfo = {};
      beginInfo.attachmentCnt = 1;
      beginInfo.attachmentInfos[0].clearValue = { 1., 0., 0., 1 };
      beginInfo.attachmentInfos[0].texture = swapchainTexture;
      beginInfo.attachmentInfos[0].type = AttachmentType::COLOR;
      beginInfo.attachmentInfos[0].loadOp = LoadOp::CLEAR;
      beginInfo.attachmentInfos[0].storeOp = StoreOp::STORE;
      cmdBuffer->BeginRenderPass(beginInfo);

      cmdBuffer->SetPipelineState(state);
      cmdBuffer->BindVertexBuffer(vertexBuffer, 0);
      cmdBuffer->BindUniformBuffer(uniformBuffer, 0, 0);
      cmdBuffer->BindSampledTexture(sampledTexture, 0, 1);
      cmdBuffer->BindSampler(0, 2);
      cmdBuffer->Draw(3);
      cmdBuffer->BindVertexBuffer(vertexBuffer, 9 * sizeof(float));
      cmdBuffer->Draw(3);
      cmdBuffer->EndRenderPass();

      cmdBuffer->TextureBarrier({ TextureBarrierScope::ColorAttachment,
                                  TextureBarrierScope::PresentSrc,
                                  swapchainTexture });

      device->Submit(cmdBuffer);
    }

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

    device->Release(uniformBuffer);
    device->Recycle();

    fps_update(&fps);

    glfwPollEvents();
  }
}
