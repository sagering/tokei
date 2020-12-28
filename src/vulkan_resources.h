#ifndef RESOURCES_H
#define RESOURCES_H

#include <unordered_map>
#include <vector>

#include "cmd_buffer.h"
#include "common.h"

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

struct DescriptorSetLayout
{
  enum
  {
    MAX_NUM_DESCRIPTOR_SET_BINDINGS = 16
  };

  VkDescriptorSetLayoutBinding bindings[MAX_NUM_DESCRIPTOR_SET_BINDINGS];
  uint32_t bindingCnt;
};

struct RenderPass
{
  enum
  {
    MAX_NUM_ATTACHMENTS = 8,
    MAX_NUM_SUBPASSES = 8,
    MAX_NUM_SUBPASS_DEPENDENCIES = 16,
    MAX_NUM_SUBPASS_INPUT_ATTACHMENTS = 2,
    MAX_NUM_SUBPASS_COLOR_ATTACHMENTS = 2,
    MAX_NUM_SUBPASS_DEPTH_STENCIL_ATTACHMENTS = 1,
  };

  VkAttachmentDescription attachments[MAX_NUM_ATTACHMENTS];
  uint32_t attachmentCnt;

  VkSubpassDependency dependencies[MAX_NUM_SUBPASS_DEPENDENCIES];
  uint32_t dependencyCnt;

  struct AttachmentRefs
  {
    VkAttachmentReference inputAttachments[MAX_NUM_SUBPASS_INPUT_ATTACHMENTS];
    uint32_t inputAttachmentCnt;
    VkAttachmentReference colorAttachments[MAX_NUM_SUBPASS_COLOR_ATTACHMENTS];
    uint32_t colorAttachmentCnt;
    VkAttachmentReference
      depthStencilAttachments[MAX_NUM_SUBPASS_DEPTH_STENCIL_ATTACHMENTS];
    uint32_t depthStencilAttachmentCnt;
  };

  AttachmentRefs attachmentRefs[MAX_NUM_SUBPASSES];
  VkSubpassDescription subpassess[MAX_NUM_SUBPASSES];
  uint32_t subpassCnt;
};

struct Framebuffer
{
  enum
  {
    MAX_NUM_ATTACHMENTS = 8
  };

  VkRenderPass renderPass;                      // deps
  VkImageView attachments[MAX_NUM_ATTACHMENTS]; // deps
  uint32_t attachmentCnt;

  uint32_t width;
  uint32_t height;
  uint32_t layers;
};

struct ShaderLayout1
{
  enum
  {
    MAX_NUM_DESCRIPTOR_SET_LAYOUT_BINDINGS = 16,
    MAX_NUM_PUSH_CONSTANT_RANGES = 1
  };

  struct DescriptorSetLayoutBinding
  {
    uint32_t set = 0;
    VkDescriptorSetLayoutBinding binding = {};
  };

  DescriptorSetLayoutBinding
    bindings[MAX_NUM_DESCRIPTOR_SET_LAYOUT_BINDINGS] = {};
  uint32_t bindingCnt = 0;

  VkPushConstantRange pushConstantRanges[MAX_NUM_PUSH_CONSTANT_RANGES] = {};
  uint32_t pushConstantRangeCount = 0;

  uint32_t inputLocationMask = 0;
  uint32_t outputLocationMask = 0;
  uint32_t inputAttachmentMask = 0;
};

struct PipelineLayout
{
  enum
  {
    MAX_NUM_DESCRIPTOR_SETS = 16
  };

  DescriptorSetLayout layouts[MAX_NUM_DESCRIPTOR_SETS];
  uint32_t layoutCnt;
};

struct Pipeline1
{
  VkRenderPass renderPass;
  uint32_t subpass;
  PipelineState* state;
};

struct PipelineWithLayout
{
  VkPipeline pipeline;
  PipelineLayout layout;
};

FNVHash
hash(void const* data, uint32_t size, FNVHash prev = {});

FNVHash
hash(DescriptorSetLayout const* layout, FNVHash prev = {});

FNVHash
hash(RenderPass const* renderPass, FNVHash prev = {});

FNVHash
hash(Framebuffer const* framebuffer, FNVHash prev = {});

FNVHash
hash(PipelineLayout const* pipelineLayout, FNVHash prev = {});

FNVHash
hash(Pipeline1 const* Pipeline, FNVHash prev = {});

struct StaticResources
{
  HashMap<VkDescriptorSetLayout> desriptorsSetLayouts;
  HashMap<VkRenderPass> renderPasses;
  HashMap<VkFramebuffer> framebuffers;
  HashMap<VkPipelineLayout> pipelineLayouts;
  HashMap<std::vector<uint32_t>> shaderCode;
  HashMap<VkShaderModule> shaderModules;
  HashMap<ShaderLayout1> shaderLayouts;
  HashMap<PipelineWithLayout> pipelines;
  HashMap<VkSampler> samplers;

  VkDevice device;
};

VkRenderPass
GetRenderPass(StaticResources* res, RenderPass* renderPass_);

VkFramebuffer
GetFramebuffer(StaticResources* res, Framebuffer* framebuffer_);

VkPipelineLayout
GetPipelineLayout(StaticResources* res, PipelineLayout* layout_);

std::vector<uint32_t>*
GetShaderCode(StaticResources* res, char const* filepath);

VkShaderModule
GetShaderModule(StaticResources* res, char const* filepath);

ShaderLayout1
GetShaderLayout(StaticResources* res, char const* filepath);

VkDescriptorSetLayout
GetDescriptorSetLayout(StaticResources* res,
                       DescriptorSetLayout const* layout_);

VkPipeline
GetPipeline(StaticResources* res,
            Pipeline1* pipeline_,
            PipelineLayout* layout_);

VkSampler
GetSampler(StaticResources* res);

VkRenderPass
GetRenderPass(StaticResources* res, RenderPass* renderPass);

struct Resources
{
  std::vector<VkEvent> events;
  std::vector<VkSemaphore> semaphores;
  std::vector<VkFence> fences;

  uint32_t resourceCnt = 0;
};

struct ResourceAllocator
{
  Resources free;
  Resources released;
  Resources pending;

  VkDevice device;
  VkQueue queue;
  VkFence fence = VK_NULL_HANDLE;

  uint32_t totalResourceCnt = 0;
};

VkEvent
AllocateEvent(ResourceAllocator* al);
void
ReleaseEvent(ResourceAllocator* al, VkEvent event);

VkSemaphore
AllocateSemaphore(ResourceAllocator* al);
void
ReleaseSemaphore(ResourceAllocator* al, VkSemaphore sem);

VkFence
AllocateFence(ResourceAllocator* al);
void
ReleaseFence(ResourceAllocator* al, VkFence fence);

void
ClaimResources(ResourceAllocator* al);

void
PrintStats(ResourceAllocator* al);

struct DescriptorSetPool
{
  VkDescriptorPool pool;
  enum
  {
    MAX_NUM_SETS = 8
  };
  VkDescriptorSet sets[MAX_NUM_SETS];
  uint8_t allocCnt = 0;
};

struct DescriptorSetPoolList
{
  std::vector<DescriptorSetPool> pools;
};

struct CommandPoolList
{
  std::vector<VkCommandPool> pools;
};

struct ArenaResources
{
  std::unordered_map<VkDescriptorSetLayout, DescriptorSetPoolList>
    descriptorPools;
  std::unordered_map<uint32_t, CommandPoolList> cmdPools;

  uint32_t resourceCnt = 0;
};

struct ResourceArenaAllocator
{
  ArenaResources free;
  ArenaResources allocated;
  ArenaResources pending;

  VkDevice device;
  VkQueue queue;

  StaticResources* staticResources;
  ResourceAllocator* resourceAllocator;
  VkFence fence = VK_NULL_HANDLE;
};

VkDescriptorSet
AllocateDescriptorSet(ResourceArenaAllocator* arena,
                      DescriptorSetLayout const* layout);

VkCommandPool
AllocateCommandPool(ResourceArenaAllocator* al, uint32_t queueFamiliyIdx);

void
ClaimResources(ResourceArenaAllocator* arena);

#endif // !RESOURCES_H
