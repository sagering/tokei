#pragma once

#include <cmd_buffer.h>
#include <device.h>

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

float
myRand()
{
	return 2.f * static_cast<float>(rand()) / RAND_MAX - 1.f;
}

void
initParticles()
{
	// random x, y in [-1, 1], z = 0
	// random velocities in the xy plane

	for (auto& particle : particles) {
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

int
main()
{
	Timer timer;
	timer.reset();

	UBO ubo = { 0.f, particleCnt };

	initParticles();

	auto device = Device::Create();

	PipelineState state = {};
	state.shader.computeShader = "resources/shaders/compute.comp.spv";

	Buffer uniformBuffer;
	void* uboData;
	BufferCreateInfo bufferCreateInfo;
	bufferCreateInfo.size = sizeof(ubo);
	bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER;
	bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;
	std::tie(uniformBuffer, uboData) = device->CreateBuffer(bufferCreateInfo);

	void* stagingBufferData;
	Buffer stagingBuffer;
	bufferCreateInfo.size = sizeof(Particle) * particleCnt;
	bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_TRANSFER_DST |
		BufferUsageFlagBits::BUF_TRANSFER_SRC;
	bufferCreateInfo.memoryUsage = MemoryUsage::CPU_ONLY;
	std::tie(stagingBuffer, stagingBufferData) =
		device->CreateBuffer(bufferCreateInfo);

	memcpy(stagingBufferData, particles, sizeof(Particle) * particleCnt);

	Buffer storageBuffer;
	bufferCreateInfo.size = sizeof(Particle) * particleCnt;
	bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_STORAGE_BUFFER |
		BufferUsageFlagBits::BUF_TRANSFER_DST |
		BufferUsageFlagBits::BUF_TRANSFER_SRC;
	bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;
	std::tie(storageBuffer, std::ignore) = device->CreateBuffer(bufferCreateInfo);

	{
		CmdBuffer* cmdBuffer = device->GetCmdBuffer();
		cmdBuffer->Copy(storageBuffer, stagingBuffer);
		cmdBuffer->BufferBarrier({ UsageScope::TransferDst,
								   UsageScope::StorageBuffer,
								   storageBuffer });
		auto ticket = device->Submit(cmdBuffer, nullptr, UsageScope::None, nullptr);

	}

	while (true) {
		ubo.dt = timer.getDt();
		memcpy(uboData, &ubo, sizeof(ubo));

		CmdBuffer* cmdBuffer = device->GetCmdBuffer();

		cmdBuffer->SetPipelineState(state);
		cmdBuffer->BindStorageBuffer(storageBuffer, 0, 0, 0, sizeof(Particle) * particleCnt);
		cmdBuffer->BindUniformBuffer(uniformBuffer, 0, 1, 0, sizeof(UBO));
		cmdBuffer->Dispatch(particleCnt, 1, 1);
		cmdBuffer->BufferBarrier({ UsageScope::StorageBuffer,
								   UsageScope::TransferSrc,
								   storageBuffer });
		cmdBuffer->Copy(stagingBuffer, storageBuffer);
		cmdBuffer->BufferBarrier({ UsageScope::TransferDst, UsageScope::Host, stagingBuffer });

		Timer perfTimer;
		perfTimer.reset();

		Semaphore renderDone;
		auto ticket = device->Submit(cmdBuffer, nullptr, UsageScope::None, nullptr);

		device->Wait(ticket);

		memcpy(particles, stagingBufferData, sizeof(Particle) * particleCnt);

		std::cout << "elapsed: " << perfTimer.getDt() << " | ";
		std::cout << particles[particleCnt - 1].position.x << ", " << particles[particleCnt - 1].position.y
			<< std::endl;

		device->Recycle();
	}
}
