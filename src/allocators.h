#pragma once

#include "resources.h"
#include "common.h"

#include <unordered_map>
#include <deque>

struct FNVHash
{
	uint64_t value = 0xcbf29ce484222325;
};

struct FNVHashIdentityHasher
{
	std::size_t operator()(FNVHash const& hash) const noexcept
	{
		return static_cast<size_t>(hash.value);
	}
};

struct FNVHashComparator
{
	bool operator()(FNVHash const& first, FNVHash const& second) const noexcept
	{
		return first.value == second.value;
	}
};

template<typename Value>
using HashMap =
std::unordered_map<FNVHash, Value, FNVHashIdentityHasher, FNVHashComparator>;

struct Shared {
	struct Pipeline {
		VkPipeline vkPipeline;
		VkPipelineLayout vkPipelineLayout;
		PipelineLayout pipelineLayout;
	};

	bool getRenderPass(RenderPassInternal const*, VkRenderPass*);
	bool getFramebuffer(Framebuffer const*, VkFramebuffer*);
	bool getPipelineLayout(PipelineLayout const*, VkPipelineLayout*);
	bool getShaderModule(char const* filepath, VkShaderModule*, ShaderLayout*);
	bool getDescriptorSetLayout(DescriptorSetLayout const*, VkDescriptorSetLayout*);
	bool getSampler(VkSampler*);
	bool getComputePipeline(const char* compute, Pipeline*);
	bool getGraphicsPipeline(const char* vert, const char* frag, GraphicsPipelineState const*, VkRenderPass, uint32_t subpass, Pipeline*);

	HashMap<VkDescriptorSetLayout> desriptorSetLayouts;
	HashMap<VkRenderPass> renderPasses;
	HashMap<VkFramebuffer> framebuffers;
	HashMap<VkPipelineLayout> vkPipelineLayouts;
	HashMap<std::vector<uint32_t>> shaderCode;
	HashMap<VkShaderModule> shaderModules;
	HashMap<ShaderLayout> shaderLayouts;
	HashMap<Pipeline> computePipelines;
	HashMap<Pipeline> graphicsPipelines;
	HashMap<PipelineLayout> computePipelineLayouts;
	HashMap<PipelineLayout> graphicsPipelineLayouts;
	HashMap<VkSampler> samplers;

	VkDevice device;
};

struct DescriptorSetAllocator {
	bool getDescriptorSet(VkDescriptorSetLayout, DescriptorSetLayout const*, uint64_t frame, VkDescriptorSet*);
	void freeResources(uint64_t frame);

	struct DescriptorSetPool
	{
		VkDescriptorPool pool = VK_NULL_HANDLE;
		enum
		{
			MAX_NUM_SETS = 8
		};
		VkDescriptorSet sets[MAX_NUM_SETS];
		uint8_t allocCnt = 0;
		uint64_t frame = 0;
	};

	using PoolMap = std::unordered_map<VkDescriptorSetLayout, std::deque<DescriptorSetPool>>;

	PoolMap free = {};
	PoolMap working = {};

	VkDevice device = VK_NULL_HANDLE;
};

// - allocator not threadsafe
// - command buffers can only be used on a single thread 
struct CommandBufferAllocator {
	VkCommandBuffer getCommandBuffer(uint32_t queueFamiliyIdx, uint64_t frame);
	void freeResources(uint64_t frame);

	struct CommandPool
	{
		VkCommandPool pool = VK_NULL_HANDLE;
		enum
		{
			MAX_NUM_BUFFERS = 8
		};
		VkCommandBuffer buffers[MAX_NUM_BUFFERS];
		uint8_t allocCnt = 0;
		uint64_t frame = 0;
	};

	using PoolMap = std::unordered_map<uint32_t, std::deque<CommandPool>>;

	PoolMap free = {};
	PoolMap working = {};

	VkDevice device = VK_NULL_HANDLE;
};

struct FenceAllocator {
	VkFence getFence(uint64_t frame);
	void freeResources(uint64_t frame);

	std::deque<VkFence> free;
	std::deque<std::pair<VkFence, uint64_t>> working;

	VkDevice device = VK_NULL_HANDLE;
};

struct SemaphoreAllocator {
	VkSemaphore getSemaphore(uint64_t frame);
	void freeResources(uint64_t frame);

	std::deque<VkSemaphore> free;
	std::deque<std::pair<VkSemaphore, uint64_t>> working;

	VkDevice device = VK_NULL_HANDLE;
};
