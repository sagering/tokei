

# Renderpasses

## Attachment

`VkAttachmentDescription` describes an attached image (format and number of samles), how
it should loaded at the beginning of a renderpass and stored at the end of a renderpass.

`VkAttachmentReference` describes the layout with which an attachment is used in a subpass.
Do we have to explicitly transition the layout?

## Framebuffer

A framebuffer is a concrete realization of attachments of a renderpass.

## Beginning a Renderpass

`VkClearValues` have to be passed for each attachment of a renderpass in `VkRenderPassBeginInfo`.
As for framebuffers, `VkClearValues` are a concrete realization of the load operations.

Render area `VkRect2D` (?)

# Descriptors

Piece of memory on the GPU that links a shader resource binding slot to an actual resource.

## Descriptor set layout

A `VkDescriptorSetLayout` describes a set of resource binding slots.

## Descriptor set

A set of descriptors with a particular descriptor set layout.

## Writing descriptor sets

Descriptor sets can be written by `vkUpdateDescriptorSets`. Not allowed to be updated while still in use.

# Vulkan Synchronization

## Barriers

Barriers can be used to for GPU to GPU synchronization of buffer and image memory accesses, use cases
are:

- image layout transitions for images
- queue transfer
- write after read synchronization
- write after write synchronization 
- read after write synchronization

### Buffer Memory Barriers

Create a `VkBufferMemoryBarrier` by specifying source and destination `VkAccessFlags`,
source and destination queue family index, a buffer and buffer region (offset and size).

Record the barrier by calling `vkCmdPipelineBarrier` and additionally proving source and destination
`VkPipelineStageFlags`.

The changes to the buffer memory in the source pipeline stage will be made available (flushed) and
made visible (loaded) to access in the destination stage.

### Image Memory Barriers

Image memory barriers work similar to buffer memory barriers. Instead of specifying a buffer 
region, a `VkImageSubresourceRange` needs to be provided.

The initial and final `VkImageLayout` further define a potential image layout transition from
the initial to the final `VkImageLayout` that the image should have after made available (missing reference).

## Events
## Semaphores
## Fences