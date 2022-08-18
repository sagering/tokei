#pragma once

#include <pokei.h>

#include <chrono>
#include <iostream>
#include <vector>

#include <glm\glm.hpp>

using u32 = uint32_t;

struct UBO
{
  float dt;
  u32 particleCnt;
};

struct Particle
{
  // vec4 because of alignment requirements
  glm::vec4 position;
  glm::vec4 velocity;
};

u32 const particleCnt = (uint16_t)-1;
Particle particles[particleCnt];

float myRand()
{
  return 2.f * static_cast<float>(rand()) / RAND_MAX - 1.f;
}

void initParticles()
{
  // random x, y in [-1, 1], z = 0
  // random velocities in the xy plane

  for (auto &particle : particles)
  {
    particle.position.x = myRand();
    particle.position.y = myRand();
    particle.position.z = 0.f;
    particle.position.w = 1.f;

    particle.velocity.x = myRand() * 0.001f;
    particle.velocity.y = myRand() * 0.001f;
    particle.velocity.z = 0.f;
    particle.velocity.w = 0.f;
  }
}

struct Timer
{
  void reset() { startTime = now(); }
  float getDt() { return now() - startTime; }

  double now()
  {
    return std::chrono::duration_cast<std::chrono::duration<double>>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
  }

  double startTime = 0.f;
};

int main()
{
  Timer timer;
  timer.reset();

  UBO ubo = {0.f, particleCnt};

  initParticles();

  Device device;
  pkCreateDevice(&device);

  PipelineState state = {};
  state.shader.computeShader = "resources/shaders/compute.comp.spv";

  Buffer uniformBuffer;
  void *uboData;
  BufferCreateInfo bufferCreateInfo;
  bufferCreateInfo.size = sizeof(ubo);
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER;
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;
  pkCreateBuffer(device, &bufferCreateInfo, &uniformBuffer, &uboData);

  void *stagingBufferData;
  Buffer stagingBuffer;
  bufferCreateInfo.size = sizeof(Particle) * particleCnt;
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
                                BufferUsageFlagBits::BUF_TRANSFER_SRC;
  bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
  pkCreateBuffer(device, &bufferCreateInfo, &stagingBuffer, &stagingBufferData);

  memcpy(stagingBufferData, particles, sizeof(Particle) * particleCnt);

  Buffer storageBuffer;
  bufferCreateInfo.size = sizeof(Particle) * particleCnt;
  bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_STORAGE_BUFFER |
                                BufferUsageFlagBits::BUF_TRANSFER_DST |
                                BufferUsageFlagBits::BUF_TRANSFER_SRC;
  bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
  void *dummy;
  pkCreateBuffer(device, &bufferCreateInfo, &storageBuffer, &dummy);

  {
    Queue queue;
    CmdBuffer cmdBuffer;
    pkGetQueue(device, QueueType::Compute, &queue);
    pkCreateCmdBuffer(queue, &cmdBuffer);

    pkCopy(cmdBuffer, storageBuffer, stagingBuffer);

    auto bufferBarrier =
        BufferBarrier{SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
                                           AccessFlagBits::TRANSFER_WRITE_BIT},
                      SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
                                           AccessFlagBits::SHADER_READ_BIT |
                                               AccessFlagBits::SHADER_WRITE_BIT},
                      storageBuffer};

    insertBarrier(cmdBuffer, &bufferBarrier);
    submit(queue, &cmdBuffer, 1, nullptr, nullptr, 0, nullptr, 0, nullptr);
  }

  while (true)
  {
    ubo.dt = timer.getDt();
    memcpy(uboData, &ubo, sizeof(ubo));

    Queue queue;
    CmdBuffer cmdBuffer;
    pkGetQueue(device, QueueType::Compute, &queue);
    pkCreateCmdBuffer(queue, &cmdBuffer);

    setPipelineState(cmdBuffer, &state);
    bindStorageBuffer(
        cmdBuffer, storageBuffer, 0, 0, 0, sizeof(Particle) * particleCnt);
    bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 1, 0, sizeof(UBO));
    dispatch(cmdBuffer, particleCnt, 1, 1);

    auto bufferBarrier =
        BufferBarrier{SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
                                           AccessFlagBits::SHADER_READ_BIT |
                                               AccessFlagBits::SHADER_WRITE_BIT},
                      SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
                                           AccessFlagBits::TRANSFER_READ_BIT},
                      storageBuffer};

    insertBarrier(cmdBuffer, &bufferBarrier);

    pkCopy(cmdBuffer, stagingBuffer, storageBuffer);

    bufferBarrier =
        BufferBarrier{SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
                                           AccessFlagBits::TRANSFER_WRITE_BIT},
                      SynchronizationScope{PipelineStageFlagBits::HOST_BIT,
                                           AccessFlagBits::HOST_READ_BIT},
                      stagingBuffer};

    insertBarrier(cmdBuffer, &bufferBarrier);

    Timer perfTimer;
    perfTimer.reset();

    Fence fence;
    submit(queue, &cmdBuffer, 1, nullptr, nullptr, 0, nullptr, 0, &fence);
    wait(device, fence);

    memcpy(particles, stagingBufferData, sizeof(Particle) * particleCnt);

    std::cout << "elapsed: " << perfTimer.getDt() << " | ";
    std::cout << particles[particleCnt - 1].position.x << ", "
              << particles[particleCnt - 1].position.y << std::endl;

    frame(device);
  }
}
