#include "allocators.h"

#include "vk_init.h"


FNVHash
hash(void const* data, uint32_t size, FNVHash prev = {})
{
	uint8_t const* ptr = static_cast<uint8_t const*>(data);
	uint8_t const* end = ptr + size;

	while (ptr < end) {
		prev.value ^= *ptr;
		prev.value *= 0x100000001b3;
		++ptr;
	}

	return prev;
}

FNVHash
hash(RenderPassInternal const* renderpass, FNVHash prev = {})
{
	prev = hash(renderpass->attachments,
		sizeof(renderpass->attachments[0]) * renderpass->attachmentCnt,
		prev);
	prev = hash(renderpass->dependencies,
		sizeof(renderpass->dependencies[0]) * renderpass->dependencyCnt,
		prev);

	for (uint32_t i = 0; i < renderpass->subpassCnt; ++i) {
		prev = hash(renderpass->attachmentRefs[i].inputAttachments,
			sizeof(renderpass->attachmentRefs[i].inputAttachments[0]) *
			renderpass->attachmentRefs[i].inputAttachmentCnt,
			prev);
		prev = hash(renderpass->attachmentRefs[i].colorAttachments,
			sizeof(renderpass->attachmentRefs[i].colorAttachments[0]) *
			renderpass->attachmentRefs[i].colorAttachmentCnt,
			prev);
		prev =
			hash(renderpass->attachmentRefs[i].depthStencilAttachments,
				sizeof(renderpass->attachmentRefs[i].depthStencilAttachments[0]) *
				renderpass->attachmentRefs[i].depthStencilAttachmentCnt,
				prev);
	}

	return prev;
}

FNVHash
hash(Framebuffer const* framebuffer, FNVHash prev = {})
{
	prev = hash(&framebuffer->renderPass, sizeof(framebuffer->renderPass), prev);
	prev = hash(&framebuffer->width, sizeof(framebuffer->width), prev);
	prev = hash(&framebuffer->height, sizeof(framebuffer->height), prev);
	prev = hash(&framebuffer->layers, sizeof(framebuffer->layers), prev);
	return hash(&framebuffer->attachments,
		sizeof(framebuffer->attachments[0]) * framebuffer->attachmentCnt,
		prev);
}

FNVHash
hash(PipelineLayout const* pipelineLayout, FNVHash prev = {})
{
	return hash(pipelineLayout->layouts,
		sizeof(pipelineLayout->layouts[0]) * pipelineLayout->layoutCnt,
		prev);
}

FNVHash
hash(DescriptorSetLayout const* layout, FNVHash prev = {})
{
	return hash(
		&layout->bindings, sizeof(layout->bindings[0]) * layout->bindingCnt, prev);
}

bool Shared::getRenderPass(RenderPassInternal const * in, VkRenderPass *out)
{
	auto h = hash(in);
	auto findIter = renderPasses.find(h);
	if (findIter != renderPasses.end()) {
		*out = findIter->second;
		return true;
	}
	auto handle = createRenderPass(device, in);
	renderPasses[h] = handle;
	*out = handle;
	return true;
}

bool Shared::getFramebuffer(Framebuffer const * in, VkFramebuffer * out)
{
	auto h = hash(in);
	auto findIter = framebuffers.find(h);
	if (findIter != framebuffers.end()) {
		*out = findIter->second;
		return true;
	}
	auto handle = createFramebuffer(device, in);
	framebuffers[h] = handle;
	*out = handle;
	return true;
}

bool Shared::getPipelineLayout(PipelineLayout const * in, VkPipelineLayout * out)
{
	auto h = hash(in);
	auto findIter = vkPipelineLayouts.find(h);
	if (findIter != vkPipelineLayouts.end()) {
		*out = findIter->second;
		return true;
	}
	auto handle = createPipelineLayout(device, in);
	vkPipelineLayouts[h] = handle;
	*out = handle;
	return true;
}

bool Shared::getShaderModule(char const * filepath, VkShaderModule * out0, ShaderLayout *out1)
{
	auto h = hash(&filepath, sizeof(filepath));

	// TODO: avoid loading code twice

	{
		auto findIter = shaderModules.find(h);
		if (findIter != shaderModules.end()) {
			*out0 = findIter->second;
		}
		else {
			auto handle = createShaderModule(device, filepath);
			shaderModules[h] = handle;
			*out0 = handle;
		}
	}

	{
		auto findIter = shaderLayouts.find(h);
		if (findIter != shaderLayouts.end()) {
			*out1 = findIter->second;
		}
		else {
			auto handle = createShaderLayout(filepath);
			shaderLayouts[h] = handle;
			*out1 = handle;
		}
	}

	return true;
}

bool Shared::getDescriptorSetLayout(DescriptorSetLayout const * in, VkDescriptorSetLayout * out)
{
	auto h = hash(in);
	auto findIter = desriptorSetLayouts.find(h);
	if (findIter != desriptorSetLayouts.end()) {
		*out = findIter->second;
		return true;
	}
	auto handle = createDescriptorSetLayout(device, in);
	desriptorSetLayouts[h] = handle;
	*out = handle;
	return true;
}

bool Shared::getSampler(VkSampler * out)
{
	auto h = hash(nullptr, 0);
	auto findIter = samplers.find(h);
	if (findIter != samplers.end()) {
		*out = findIter->second;
		return true;
	}
	auto handle = createSampler(device);
	samplers[h] = handle;
	*out = handle;
	return true;
}

bool Shared::getComputePipeline(char const * compute, Pipeline * out)
{
	auto h = hash(&compute, sizeof(compute));
	auto findIter = computePipelines.find(h);
	if (findIter != computePipelines.end()) {
		*out = findIter->second;
		return true;
	}
	VkShaderModule shaderModule;
	ShaderLayout shaderLayout;
	getShaderModule(compute, &shaderModule, &shaderLayout);
	VkShaderStageFlagBits stage = VK_SHADER_STAGE_COMPUTE_BIT;
	auto pipelineLayout = createPipelineLayout(&shaderLayout, &stage, 1);
	VkPipelineLayout vkPipelineLayout;
	getPipelineLayout(&pipelineLayout, &vkPipelineLayout);
	auto pipeline = createComputePipeline(device, shaderModule, vkPipelineLayout);
	computePipelines[h] = { pipeline, vkPipelineLayout, pipelineLayout };
	*out = { pipeline, vkPipelineLayout, pipelineLayout };
	return true;
}

bool Shared::getGraphicsPipeline(char const* vert, char const* frag, GraphicsPipelineState const* state, VkRenderPass renderPass, uint32_t subpass, Pipeline* out)
{
	FNVHash h;
	h = hash(&vert, sizeof(vert), h);
	h = hash(&frag, sizeof(frag), h);
	h = hash(state, sizeof(GraphicsPipelineState), h);
	h = hash(&renderPass, sizeof(VkRenderPass), h);
	h = hash(&subpass, sizeof(uint32_t), h);

	auto findIter = graphicsPipelines.find(h);
	if (findIter != graphicsPipelines.end()) {
		*out = findIter->second;
		return true;
	}

	VkShaderModule modules[2];
	ShaderLayout layouts[2];
	VkShaderStageFlagBits stages[2] = { VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_FRAGMENT_BIT };

	getShaderModule(vert, &modules[0], &layouts[0]);
	getShaderModule(frag, &modules[1], &layouts[1]);

	auto pipelineLayout = createPipelineLayout(layouts, stages, 2);

	VkPipelineLayout vkPipelineLayout;
	getPipelineLayout(&pipelineLayout, &vkPipelineLayout);

	auto pipeline = createGraphicsPipeline(device, modules, stages, 2, vkPipelineLayout, state, renderPass, subpass);
	graphicsPipelines[h] = { pipeline, vkPipelineLayout, pipelineLayout };
	*out = { pipeline, vkPipelineLayout, pipelineLayout };
	return true;
}

bool DescriptorSetAllocator::getDescriptorSet(VkDescriptorSetLayout handle, DescriptorSetLayout const* layout, uint64_t frame, VkDescriptorSet * out)
{
	auto it = working.find(handle);

	// allocate descriptor set from a working pool, if possible
	if (it != working.end()) {
		auto& pool = it->second.back();
		if (pool.allocCnt < DescriptorSetPool::MAX_NUM_SETS) {
			pool.frame = frame;
			*out = pool.sets[pool.allocCnt++];
			return true;
		}
	}

	it = free.find(handle);

	// allocate descriptor set from a free pool, if possible
	if (it != free.end()) {
		auto pool = std::move(it->second.back());
		it->second.pop_back();
		if (it->second.empty()) {
			free.erase(it);
		}
		pool.frame = frame;
		auto set = pool.sets[pool.allocCnt++];
		working[handle].emplace_back(
			std::move(pool));
		*out = set;
		return true;
	}

	// new pool
	enum
	{
		MAX_NUM_DESCRIPTOR_TYPES = 11
	};

	VkDescriptorPoolSize poolSizes[MAX_NUM_DESCRIPTOR_TYPES] = {};
	uint32_t poolSizeCnt = 0;

	for (uint32_t type = 0; type < MAX_NUM_DESCRIPTOR_TYPES; ++type) {
		auto dtype = static_cast<VkDescriptorType>(type);
		bool found = false;

		for (uint32_t binding = 0; binding < layout->bindingCnt; ++binding) {
			if (layout->bindings[binding].descriptorType == dtype) {
				poolSizes[poolSizeCnt].type = dtype;
				poolSizes[poolSizeCnt].descriptorCount +=
					DescriptorSetPool::MAX_NUM_SETS;
				found = true;
			}
		}

		if (found) {
			poolSizeCnt += 1;
		}
	}

	auto createInfo = vkiDescriptorPoolCreateInfo(
		DescriptorSetPool::MAX_NUM_SETS, poolSizeCnt, poolSizes);

	VkDescriptorPool pool = VK_NULL_HANDLE;
	vkCreateDescriptorPool(device, &createInfo, nullptr, &pool);
	DescriptorSetPool setPool = {};
	setPool.pool = pool;
	setPool.allocCnt = 0;

	VkDescriptorSetLayout layouts[DescriptorSetPool::MAX_NUM_SETS];
	for (uint32_t i = 0; i < DescriptorSetPool::MAX_NUM_SETS; ++i) {
		layouts[i] = handle;
	}

	auto allocInfo = vkiDescriptorSetAllocateInfo(
		pool, DescriptorSetPool::MAX_NUM_SETS, layouts);
	vkAllocateDescriptorSets(device, &allocInfo, setPool.sets);

	setPool.frame = frame;
	auto set = setPool.sets[setPool.allocCnt++];

	working[handle].emplace_back(setPool);

	*out = set;

	return true;
}

void DescriptorSetAllocator::freeResources(uint64_t frame)
{
	for (auto it = working.begin(); it != working.end();) {
		auto layout = it->first;
		auto& pools = it->second;

		while (!pools.empty() && pools.front().frame <= frame) {
			auto pool = pools.front();
			pool.allocCnt = 0;
			pool.frame = 0;
			free[layout].emplace_back(std::move(pool));
			pools.pop_front();
		}

		if (pools.empty()) {
			it = working.erase(it);
			continue;
		}

		++it;
	}
}

VkCommandBuffer CommandBufferAllocator::getCommandBuffer(uint32_t queueFamilyIdx, uint64_t frame)
{
	auto it = working.find(queueFamilyIdx);

	// allocate command buffer from a working pool, if possible
	if (it != working.end()) {
		auto& pool = it->second.back();
		if (pool.allocCnt < CommandPool::MAX_NUM_BUFFERS) {
			pool.frame = frame;
			return pool.buffers[pool.allocCnt++];
		}
	}

	it = free.find(queueFamilyIdx);

	// allocate command buffer from a free pool, if possible
	if (it != free.end()) {
		auto pool = std::move(it->second.back());
		it->second.pop_back();
		if (it->second.empty()) {
			free.erase(it);
		}
		pool.frame = frame;
		auto set = pool.buffers[pool.allocCnt++];
		working[queueFamilyIdx].emplace_back(
			std::move(pool));
		return set;
	}

	// new pool
	auto createInfo = vkiCommandPoolCreateInfo(queueFamilyIdx);
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	VkCommandPool pool = VK_NULL_HANDLE;
	vkCreateCommandPool(device, &createInfo, nullptr, &pool);

	auto allocateInfo = vkiCommandBufferAllocateInfo(pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, CommandPool::MAX_NUM_BUFFERS);
	auto cmdPool = CommandPool{};
	cmdPool.pool = pool;
	cmdPool.frame = frame;
	vkAllocateCommandBuffers(device, &allocateInfo, cmdPool.buffers);
	auto cmdBuffer = cmdPool.buffers[cmdPool.allocCnt++];
	working[queueFamilyIdx].push_back(cmdPool);

	return cmdBuffer;
}

void CommandBufferAllocator::freeResources(uint64_t frame)
{
	for (auto it = working.begin(); it != working.end();) {
		auto queueFamilyIdx = it->first;
		auto& pools = it->second;

		while (!pools.empty() && pools.front().frame <= frame) {
			auto pool = pools.front();
			for (uint32_t i = 0; i < pool.allocCnt; ++i) {
				vkResetCommandBuffer(pool.buffers[i], 0);
			}
			pool.allocCnt = 0;
			pool.frame = 0;
			free[queueFamilyIdx].emplace_back(std::move(pool));

			pools.pop_front();
		}

		if (pools.empty()) {
			it = working.erase(it);
			continue;
		}

		++it;
	}
}

VkFence FenceAllocator::getFence(uint64_t frame)
{
	if (!free.empty()) {
		auto fence = free.back();
		free.pop_back();
		return fence;
	}

	auto createInfo = vkiFenceCreateInfo();
	VkFence fence = VK_NULL_HANDLE;
	vkCreateFence(device, &createInfo, nullptr, &fence);

	working.push_back({ fence, frame });

	return fence;
}

void FenceAllocator::freeResources(uint64_t frame)
{
	std::vector<VkFence> reset;

	while (!working.empty() && working.front().second <= frame) {
		auto fence = working.front().first;
		reset.push_back(fence);
		free.push_back(fence);
		working.pop_front();
	}

	if (reset.empty()) return;

	vkResetFences(device, static_cast<uint32_t>(reset.size()), reset.data());
}

VkSemaphore SemaphoreAllocator::getSemaphore(uint64_t frame)
{
	if (!free.empty()) {
		auto sem = free.back();
		free.pop_back();
		return sem;
	}

	auto createInfo = vkiSemaphoreCreateInfo();
	VkSemaphore sem = VK_NULL_HANDLE;
	vkCreateSemaphore(device, &createInfo, nullptr, &sem);

	working.push_back({ sem, frame });

	return sem;
}

void SemaphoreAllocator::freeResources(uint64_t frame)
{
	while (!working.empty() && working.front().second <= frame) {
		auto sem = working.front().first;
		free.push_back(sem);
		working.pop_front();
	}
}
