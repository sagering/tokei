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

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	int width = 512;
	int height = 512;

	auto window = glfwCreateWindow(width, height, "slime", 0, 0);
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

	PipelineState computeState = {};
	computeState.shader.computeShader = "resources/shaders/particles.comp.spv";

	PipelineState evap = {};
	evap.shader.computeShader = "resources/shaders/post.comp.spv";

	PipelineState fullscreenPipeline = {};
	fullscreenPipeline.shader.vertexShader =
		"resources/shaders/fullscreen.vert.spv";
	fullscreenPipeline.shader.fragmentShader =
		"resources/shaders/fullscreen.frag.spv";

	fullscreenPipeline.inputAssembly.topology = PrimitiveTopology::TRIANGLE_STRIP;

	fullscreenPipeline.rasterization.polygonMode = PolygonMode::FILL;
	fullscreenPipeline.rasterization.cullMode = CullMode::NONE;
	fullscreenPipeline.rasterization.frontFace = FrontFace::COUNTER_CLOCKWISE;

	fullscreenPipeline.viewport.viewport.x = 0;
	fullscreenPipeline.viewport.viewport.y = 0;
	fullscreenPipeline.viewport.viewport.width =
		static_cast<float>(swapchainCreateInfo.width);
	fullscreenPipeline.viewport.viewport.height =
		static_cast<float>(swapchainCreateInfo.height);
	fullscreenPipeline.viewport.viewport.minDepth = 0.f;
	fullscreenPipeline.viewport.viewport.maxDepth = 1.f;
	fullscreenPipeline.viewport.scissors.x = 0;
	fullscreenPipeline.viewport.scissors.y = 0;
	fullscreenPipeline.viewport.scissors.width = swapchainCreateInfo.width;
	fullscreenPipeline.viewport.scissors.height = swapchainCreateInfo.height;

	TextureCreateInfo textureCreateInfo = {};
	textureCreateInfo.width = width;
	textureCreateInfo.height = height;
	textureCreateInfo.depth = 1;
	textureCreateInfo.format = PixelFormat::RGBA8_UNORM;
	textureCreateInfo.layers = 1;
	textureCreateInfo.mipLevels = 1;
	textureCreateInfo.usageFlags = TextureUsageFlagBits::TEX_STORAGE |
								   TextureUsageFlagBits::TEX_SAMPLED |
								   TextureUsageFlagBits::TEX_TRANSFER_SRC |
								   TextureUsageFlagBits::TEX_TRANSFER_DST;
	textureCreateInfo.samples = 1;

	Texture in;
	pkCreateTexture(device, &textureCreateInfo, &in);

	Texture out;
	pkCreateTexture(device, &textureCreateInfo, &out);

	auto const numParticlesX = 512;
	auto const numParticlesY = 512;

	struct UBO
	{
		int32_t numParticles;
		int32_t init;
		float dt;
		float moveSpeed;
		float evaporateSpeed;
		float diffuseSpeed;
		float turnSpeed;
		float padding;
	};

	auto offset = offsetof(UBO, dt);

	UBO *ubo;

	Buffer uniformBuffer;
	BufferCreateInfo bufferCreateInfo;
	bufferCreateInfo.size = sizeof(UBO);
	bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_UNIFORM_BUFFER;
	bufferCreateInfo.memoryUsage = MemoryUsage::CPU_TO_GPU;

	pkCreateBuffer(device, &bufferCreateInfo, &uniformBuffer, (void **)&ubo);

	struct Particle
	{
		glm::vec2 pos;
		float angle;
		int32_t init;
	};

	Buffer storageBuffer;
	void *dummy;
	bufferCreateInfo = {};
	bufferCreateInfo.size = sizeof(Particle) * numParticlesX * numParticlesY;
	bufferCreateInfo.usageFlags = BufferUsageFlagBits::BUF_STORAGE_BUFFER;
	bufferCreateInfo.memoryUsage = MemoryUsage::GPU_ONLY;

	pkCreateBuffer(device, &bufferCreateInfo, &storageBuffer, &dummy);

	{
		Queue queue;
		CmdBuffer cmdBuffer;

		pkGetQueue(device, QueueType::Graphics, &queue);
		pkCreateCmdBuffer(queue, &cmdBuffer);

		auto textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0},
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_READ_BIT |
									 AccessFlagBits::SHADER_WRITE_BIT},
			TextureLayout::UNDEFINED,
			TextureLayout::TRANSFER_DST_OPTIMAL,
			in};

		insertBarrier(cmdBuffer, &textureBarrier);

		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0},
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_READ_BIT |
									 AccessFlagBits::SHADER_WRITE_BIT},
			TextureLayout::UNDEFINED,
			TextureLayout::SHADER_READ_ONLY_OPTIMAL,
			out};

		insertBarrier(cmdBuffer, &textureBarrier);

		submit(queue, &cmdBuffer, 1, nullptr, nullptr, 0, nullptr, 0, nullptr);
	}

	ubo->numParticles = numParticlesX * numParticlesY;
	ubo->dt = 0.015f;
	ubo->moveSpeed = 20.0f;
	ubo->evaporateSpeed = 0.2f;
	ubo->diffuseSpeed = 3.0f;
	ubo->turnSpeed = 2.f;
	ubo->init = 1;

	// TODO: ping pong instead of blitting

	// particles compute shader:
	// - write to storage buffer
	// - read from in, write to out(in=GENERAL/out=GENERAL)

	// blit:
	// - read from out write to in (in=TRANSFER_DST/out=TRANSFER_SRC)

	// post compute shader:
	// - read from in write to out  (in=GENERAL/out=GENERAL)

	// blit:
	// - read from out write to in (in=TRANSFER_DST/out=TRANSFER_SRC)

	// render:
	// - read from out (out=SHADER_READ_ONLY)

	while (true)
	{
		Texture swapchainTexture;

		Semaphore available;
		while (!acquireNext(device, swapchain, &swapchainTexture, &available))
		{
			glfwGetWindowSize(window, &width, &height);

			fullscreenPipeline.viewport.scissors.width = width;
			fullscreenPipeline.viewport.scissors.height = height;
			fullscreenPipeline.viewport.viewport.width = static_cast<float>(width);
			fullscreenPipeline.viewport.viewport.height = static_cast<float>(height);

			swapchainCreateInfo.width = width;
			swapchainCreateInfo.height = height;

			pkRecreateSwapchain(device, &swapchainCreateInfo, swapchain);
		}

		Queue queue;
		CmdBuffer cmdBuffer;

		pkGetQueue(device, QueueType::Graphics, &queue);
		pkCreateCmdBuffer(queue, &cmdBuffer);

		auto bufferBarrier =
			BufferBarrier{SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
											   AccessFlagBits::SHADER_WRITE_BIT |
												   AccessFlagBits::SHADER_READ_BIT},
						  SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
											   AccessFlagBits::SHADER_WRITE_BIT |
												   AccessFlagBits::SHADER_READ_BIT},
						  storageBuffer};

		insertBarrier(cmdBuffer, &bufferBarrier);

		auto textureBarrier = TextureBarrier{};

		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
								 AccessFlagBits::TRANSFER_WRITE_BIT},
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_READ_BIT},
			TextureLayout::TRANSFER_DST_OPTIMAL,
			TextureLayout::GENERAL,
			in};

		insertBarrier(cmdBuffer, &textureBarrier);

		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::GRAPHICS_FRAGMENT_SHADER_BIT,
								 AccessFlagBits::SHADER_READ_BIT},
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_WRITE_BIT},
			TextureLayout::SHADER_READ_ONLY_OPTIMAL,
			TextureLayout::GENERAL,
			out};

		insertBarrier(cmdBuffer, &textureBarrier);

		// particles (read in, write out)
		setPipelineState(cmdBuffer, &computeState);
		bindStorageTexture(cmdBuffer, in, 0, 0);
		bindStorageTexture(cmdBuffer, out, 0, 1);
		bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 2, 0, sizeof(UBO));
		bindStorageBuffer(cmdBuffer,
						  storageBuffer,
						  0,
						  3,
						  0,
						  sizeof(Particle) * numParticlesX * numParticlesY);
		dispatch(cmdBuffer, numParticlesX, numParticlesY, 1);

		// blit out -> in
		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_READ_BIT},
			SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
								 AccessFlagBits::TRANSFER_WRITE_BIT},
			TextureLayout::GENERAL,
			TextureLayout::TRANSFER_DST_OPTIMAL,
			in};

		insertBarrier(cmdBuffer, &textureBarrier);

		textureBarrier =
			TextureBarrier{SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
												AccessFlagBits::SHADER_WRITE_BIT},
						   SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
												AccessFlagBits::TRANSFER_READ_BIT},
						   TextureLayout::GENERAL,
						   TextureLayout::TRANSFER_SRC_OPTIMAL,
						   out};

		insertBarrier(cmdBuffer, &textureBarrier);

		pkBlit(cmdBuffer,
			   in,
			   TextureLayout::TRANSFER_DST_OPTIMAL,
			   out,
			   TextureLayout::TRANSFER_SRC_OPTIMAL);

		// post
		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
								 AccessFlagBits::TRANSFER_WRITE_BIT},
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_READ_BIT},
			TextureLayout::TRANSFER_DST_OPTIMAL,
			TextureLayout::GENERAL,
			in};

		insertBarrier(cmdBuffer, &textureBarrier);

		textureBarrier =
			TextureBarrier{SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
												AccessFlagBits::TRANSFER_READ_BIT},
						   SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
												AccessFlagBits::SHADER_WRITE_BIT},
						   TextureLayout::TRANSFER_SRC_OPTIMAL,
						   TextureLayout::GENERAL,
						   out};

		insertBarrier(cmdBuffer, &textureBarrier);

		setPipelineState(cmdBuffer, &evap);
		bindStorageTexture(cmdBuffer, in, 0, 0);
		bindStorageTexture(cmdBuffer, out, 0, 1);
		bindUniformBuffer(cmdBuffer, uniformBuffer, 0, 2, 0, sizeof(UBO));
		dispatch(cmdBuffer, 512, 512, 1);

		// blit out -> in
		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
								 AccessFlagBits::SHADER_READ_BIT},
			SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
								 AccessFlagBits::TRANSFER_WRITE_BIT},
			TextureLayout::GENERAL,
			TextureLayout::TRANSFER_DST_OPTIMAL,
			in};

		insertBarrier(cmdBuffer, &textureBarrier);

		textureBarrier =
			TextureBarrier{SynchronizationScope{PipelineStageFlagBits::COMPUTE_BIT,
												AccessFlagBits::SHADER_WRITE_BIT},
						   SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
												AccessFlagBits::TRANSFER_READ_BIT},
						   TextureLayout::GENERAL,
						   TextureLayout::TRANSFER_SRC_OPTIMAL,
						   out};

		insertBarrier(cmdBuffer, &textureBarrier);

		pkBlit(cmdBuffer,
			   in,
			   TextureLayout::TRANSFER_DST_OPTIMAL,
			   out,
			   TextureLayout::TRANSFER_SRC_OPTIMAL);

		// sample

		textureBarrier =
			TextureBarrier{SynchronizationScope{PipelineStageFlagBits::TRANSFER_BIT,
												AccessFlagBits::TRANSFER_READ_BIT},
						   SynchronizationScope{PipelineStageFlagBits::GRAPHICS_FRAGMENT_SHADER_BIT,
												AccessFlagBits::SHADER_READ_BIT},
						   TextureLayout::TRANSFER_SRC_OPTIMAL,
						   TextureLayout::SHADER_READ_ONLY_OPTIMAL,
						   out};

		insertBarrier(cmdBuffer, &textureBarrier);

		textureBarrier = TextureBarrier{
			SynchronizationScope{PipelineStageFlagBits::TOP_OF_PIPE_BIT, 0},
			SynchronizationScope{
				PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
				AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT |
					AccessFlagBits::COLOR_ATTACHMENT_READ_BIT},
			TextureLayout::UNDEFINED,
			TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
			swapchainTexture};

		insertBarrier(cmdBuffer, &textureBarrier);

		RenderPass renderPass;
		renderPass.attachmentInfos[0].clearValue = {0.0, 0.0, 0.0, 1.0};
		renderPass.attachmentInfos[0].loadOp = LoadOp::CLEAR;
		renderPass.attachmentInfos[0].storeOp = StoreOp::STORE;
		renderPass.attachmentInfos[0].texture = swapchainTexture;
		renderPass.attachmentInfos[0].type = AttachmentType::COLOR;
		++renderPass.attachmentCnt;

		beginRenderPass(cmdBuffer, &renderPass);
		setPipelineState(cmdBuffer, &fullscreenPipeline);
		bindSampledTexture(cmdBuffer, out, 0, 0);
		bindSampler(cmdBuffer, 0, 1);
		draw(cmdBuffer, 6);
		endRenderPass(cmdBuffer);

		textureBarrier = TextureBarrier{
			SynchronizationScope{
				PipelineStageFlagBits::GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT,
				AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT |
					AccessFlagBits::COLOR_ATTACHMENT_READ_BIT},
			SynchronizationScope{PipelineStageFlagBits::BOTTOM_OF_PIPE_BIT, 0},
			TextureLayout::COLOR_ATTACHMENT_OPTIMAL,
			TextureLayout::PRESENT_SRC_KHR,
			swapchainTexture};

		insertBarrier(cmdBuffer, &textureBarrier);
		Semaphore waitSemaphores[1];
		waitSemaphores[0] = available;

		PipelineStageFlags waitStages[1];
		waitStages[0] = PipelineStageFlagBits::COMPUTE_BIT;

		Semaphore renderDone;
		Fence fence;
		submit(queue,
			   &cmdBuffer,
			   1,
			   waitSemaphores,
			   waitStages,
			   1,
			   &renderDone,
			   1,
			   &fence);

		if (!present(queue, swapchain, &renderDone))
		{
			glfwGetWindowSize(window, &width, &height);
			fullscreenPipeline.viewport.scissors.width = width;
			fullscreenPipeline.viewport.scissors.height = height;
			fullscreenPipeline.viewport.viewport.width = static_cast<float>(width);
			fullscreenPipeline.viewport.viewport.height = static_cast<float>(height);

			swapchainCreateInfo.width = width;
			swapchainCreateInfo.height = height;

			pkRecreateSwapchain(device, &swapchainCreateInfo, swapchain);
		}

		frame(device);
		glfwPollEvents();

		ubo->init = 0;
	}
}
