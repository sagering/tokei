#pragma once

#include <stdint.h>

typedef struct Device_T *Device;
typedef struct Queue_T *Queue;
typedef struct CmdBuffer_T *CmdBuffer;
typedef struct Texture_T *Texture;
typedef struct Buffer_T *Buffer;
typedef struct Swapchain_T *Swapchain;
typedef uint64_t Semaphore;
typedef uint64_t Fence;

typedef uint32_t Flags;

typedef enum BufferUsageFlagBits
{
  BUF_TRANSFER_SRC = 0x00000001,
  BUF_TRANSFER_DST = 0x00000002,
  BUF_UNIFORM_TEXEL_BUFFER = 0x00000004,
  BUF_STORAGE_TEXEL_BUFFER = 0x00000008,
  BUF_UNIFORM_BUFFER = 0x00000010,
  BUF_STORAGE_BUFFER = 0x00000020,
  BUF_INDEX_BUFFER = 0x00000040,
  BUF_VERTEX_BUFFER = 0x00000080,
  BUF_INDIRECT_BUFFER = 0x00000100,
} BufferUsageFlagBits;
typedef Flags BufferUsageFlags;

typedef enum TextureUsageFlagBits
{
  TEX_TRANSFER_SRC = 0x00000001,
  TEX_TRANSFER_DST = 0x00000002,
  TEX_SAMPLED = 0x00000004,
  TEX_STORAGE = 0x00000008,
  TEX_COLOR_ATTACHMENT = 0x00000010,
  TEX_DEPTH_STENCIL_ATTACHMENT = 0x00000020,
} TextureUsageFlagBits;
typedef Flags TextureUsageFlags;

enum class MemoryUsage : uint8_t
{
  GPU_ONLY = 1,
  CPU_ONLY = 2,
  CPU_TO_GPU = 3,
  GPU_TO_CPU = 4,
};

typedef enum PipelineStageFlagBits
{
  TOP_OF_PIPE_BIT = 0x00000001,
  GRAPHICS_DRAW_INDIRECT_BIT = 0x00000002,
  GRAPHICS_VERTEX_INPUT_BIT = 0x00000004,
  GRAPHICS_VERTEX_SHADER_BIT = 0x00000008,
  GRAPHICS_TESSELLATION_CONTROL_SHADER_BIT = 0x00000010,
  GRAPHICS_TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020,
  GRAPHICS_GEOMETRY_SHADER_BIT = 0x00000040,
  GRAPHICS_FRAGMENT_SHADER_BIT = 0x00000080,
  GRAPHICS_EARLY_FRAGMENT_TESTS_BIT = 0x00000100,
  GRAPHICS_LATE_FRAGMENT_TESTS_BIT = 0x00000200,
  GRAPHICS_COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400,
  COMPUTE_BIT = 0x00000800,
  TRANSFER_BIT = 0x00001000,
  BOTTOM_OF_PIPE_BIT = 0x00002000,
  HOST_BIT = 0x00004000,
} PipelineStageFlagBits;
typedef Flags PipelineStageFlags;

typedef enum AccessFlagBits
{
  INDIRECT_COMMAND_READ_BIT = 0x00000001,
  INDEX_READ_BIT = 0x00000002,
  VERTEX_ATTRIBUTE_READ_BIT = 0x00000004,
  UNIFORM_READ_BIT = 0x00000008,
  INPUT_ATTACHMENT_READ_BIT = 0x00000010,
  SHADER_READ_BIT = 0x00000020,
  SHADER_WRITE_BIT = 0x00000040,
  COLOR_ATTACHMENT_READ_BIT = 0x00000080,
  COLOR_ATTACHMENT_WRITE_BIT = 0x00000100,
  DEPTH_STENCIL_ATTACHMENT_READ_BIT = 0x00000200,
  DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 0x00000400,
  TRANSFER_READ_BIT = 0x00000800,
  TRANSFER_WRITE_BIT = 0x00001000,
  HOST_READ_BIT = 0x00002000,
  HOST_WRITE_BIT = 0x00004000,
  MEMORY_READ_BIT = 0x00008000,
  MEMORY_WRITE_BIT = 0x00010000,
} AccessFlagBits;
typedef Flags AccessFlags;

typedef enum TextureLayout
{
  UNDEFINED = 0,
  GENERAL = 1,
  COLOR_ATTACHMENT_OPTIMAL = 2,
  DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
  DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
  SHADER_READ_ONLY_OPTIMAL = 5,
  TRANSFER_SRC_OPTIMAL = 6,
  TRANSFER_DST_OPTIMAL = 7,
  PREINITIALIZED = 8,
  DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL = 1000117000,
  DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL = 1000117001,
  DEPTH_ATTACHMENT_OPTIMAL = 1000241000,
  DEPTH_READ_ONLY_OPTIMAL = 1000241001,
  STENCIL_ATTACHMENT_OPTIMAL = 1000241002,
  STENCIL_READ_ONLY_OPTIMAL = 1000241003,
  PRESENT_SRC_KHR = 1000001002,
} TextureLayout;

enum QueueType
{
  Graphics,
  Compute,
  Transfer
};

struct SynchronizationScope
{
  PipelineStageFlags stage;
  AccessFlags access;
  QueueType queue;
};

struct TextureBarrier
{
  SynchronizationScope src;
  SynchronizationScope dst;
  TextureLayout initialLayout;
  TextureLayout finalLayout;
  Texture texture;
};

struct BufferBarrier
{
  SynchronizationScope src;
  SynchronizationScope dst;
  Buffer buffer;
};

enum PixelFormat
{
  A8_UNORM,
  R8_UNORM,
  R8_UNORM_SRGB,
  R8_SNORM,
  R8_UINT,
  R8_SINT,
  R16_UNORM,
  R16_SNORM,
  R16_UINT,
  R16_SINT,
  R16_FLOAT,
  RG8_UNORM,
  RG8_UNORM_SRGB,
  RG8_SNORM,
  RG8_UINT,
  RG8_SINT,
  B5G6R5_UNORM,
  A1BGR5_UNORM,
  // ABGR4_UNORM, // not supported by vulkan?
  BGR5A1_UNORM,
  R32_UINT,
  R32_SINT,
  R32_FLOAT,
  RG16_UNORM,
  RG16_SNORM,
  RG16_UINT,
  RG16_SINT,
  RG16_FLOAT,
  RGBA8_UNORM,
  RGBA8_UNORM_SRGB,
  RGBA8_SNORM,
  RGBA8_UINT,
  RGBA8_SINT,
  BGRA8_UNORM,
  BGRA8_UNORM_SRGB,
  D16_UNORM,
  D32_FLOAT,
  S8_UINT,
  D24S8_UNORM_UINT,
};

struct TextureCreateInfo
{
  uint32_t width;
  uint32_t height;
  uint32_t depth;
  uint32_t mipLevels;
  uint32_t layers;
  uint32_t samples = 1;
  PixelFormat format;
  TextureUsageFlags usageFlags;
};

struct BufferCreateInfo
{
  uint64_t size;
  BufferUsageFlags usageFlags;
  MemoryUsage memoryUsage;
};

struct SwapchainCreateInfo
{
  uint32_t width;
  uint32_t height;
  uint32_t depth;
  PixelFormat format;
  TextureUsageFlags usageFlags;
  uint32_t textureCnt;
  void *platformHandle;
};

enum class BlendOp
{
  ADD = 0,
  SUBTRACT = 1,
  REVERSE_SUBTRACT = 2,
  MIN = 3,
  MAX = 4,
};

enum class BlendFactor
{
  ZERO = 0,
  ONE = 1,
  SRC0_COLOR = 2,
  ONE_MINUS_SRC0_COLOR = 3,
  DST_COLOR = 4,
  ONE_MINUS_DST_COLOR = 5,
  SRC0_ALPHA = 6,
  ONE_MINUS_SRC0_ALPHA = 7,
  DST_ALPHA = 8,
  ONE_MINUS_DST_ALPHA = 9,
  CONSTANT_COLOR = 10,
  ONE_MINUS_CONSTANT_COLOR = 11,
  CONSTANT_ALPHA = 12,
  ONE_MINUS_CONSTANT_ALPHA = 13,
  SRC0_ALPHA_SATURATE = 14,
  SRC1_COLOR = 15,
  ONE_MINUS_SRC1_COLOR = 16,
  SRC1_ALPHA = 17,
  ONE_MINUS_SRC1_ALPHA = 18,
};

enum class CompareOp
{
  NEVER = 0,
  LESS = 1,
  EQUAL = 2,
  LESS_OR_EQUAL = 3,
  GREATER = 4,
  NOT_EQUAL = 5,
  GREATER_OR_EQUAL = 6,
  ALWAYS = 7,
};

enum class Face
{
  FRONT = 0,
  BACK = 1,
};

enum class StencilOp
{
  KEEP = 0,
  ZERO = 1,
  REPLACE = 2,
  INCREMENT_AND_CLAMP = 3,
  DECREMENT_AND_CLAMP = 4,
  INVERT = 5,
  INCREMENT_AND_WRAP = 6,
  DECREMENT_AND_WRAP = 7,
};

enum class PrimitiveTopology
{
  POINT_LIST = 0,
  LINE_LIST = 1,
  LINE_STRIP = 2,
  TRIANGLE_LIST = 3,
  TRIANGLE_STRIP = 4,
  TRIANGLE_FAN = 5,
  LINE_LIST_WITH_ADJACENCY = 6,
  LINE_STRIP_WITH_ADJACENCY = 7,
  TRIANGLE_LIST_WITH_ADJACENCY = 8,
  TRIANGLE_STRIP_WITH_ADJACENCY = 9,
  PATCH_LIST = 10,
};

enum class PolygonMode
{
  FILL = 0,
  LINE = 1,
  POINT = 2,
};

enum class CullMode
{
  NONE = 0,
  FRONT = 1,
  BACK = 2,
  FRONT_AND_BACK = 3,
};

enum class FrontFace
{
  COUNTER_CLOCKWISE = 0,
  CLOCKWISE = 1,
};

struct Viewport
{
  float x;
  float y;
  float width;
  float height;
  float minDepth;
  float maxDepth;
};

struct Rect
{
  int x;
  int y;
  uint32_t width;
  uint32_t height;
};

enum class VertexInputRate
{
  VERTEX = 0,
  INSTANCE = 1,
};

enum class VertexFormat
{
  UCHAR = 0,
  UCHAR2 = 1,
  UCHAR3 = 2,
  UCHAR4 = 3,
  CHAR = 4,
  CHAR2 = 5,
  CHAR3 = 6,
  CHAR4 = 7,
  UCHAR_N = 8,
  UCHAR2_N = 9,
  UCHAR3_N = 10,
  UCHAR4_N = 11,
  CHAR_N = 12,
  CHAR2_N = 13,
  CHAR3_N = 14,
  CHAR4_N = 15,
  USHORT = 16,
  USHORT2 = 17,
  USHORT3 = 18,
  USHORT4 = 19,
  SHORT = 20,
  SHORT2 = 21,
  SHORT3 = 22,
  SHORT4 = 23,
  USHORT_N = 24,
  USHORT2_N = 25,
  USHORT3_N = 26,
  USHORT4_N = 27,
  SHORT_N = 28,
  SHORT2_N = 29,
  SHORT3_N = 30,
  SHORT4_N = 31,
  UINT = 32,
  UINT2 = 33,
  UINT3 = 34,
  UINT4 = 35,
  INT = 36,
  INT2 = 37,
  INT3 = 38,
  INT4 = 39,
  HALF = 40,
  HALF2 = 41,
  HALF3 = 42,
  HALF4 = 43,
  FLOAT = 44,
  FLOAT2 = 45,
  FLOAT3 = 46,
  FLOAT4 = 47,
};

struct PipelineState
{
  struct BlendState
  {
    bool enable = false;
    BlendOp colorOp;
    BlendFactor srcColorFactor;
    BlendFactor dstColorFactor;
    BlendOp alphaOp;
    BlendFactor srcAlphaFactor;
    BlendFactor dstAlphaFactor;
  } blend;

  struct DepthStencilState
  {
    bool depthTestenable = false;
    bool depthWriteEnable = false;
    CompareOp depthCompareOp;

    struct FaceState
    {
      CompareOp compareOp;
      uint32_t compareMask;
      uint32_t writeMask;
      uint32_t reference;
      StencilOp passOp;
      StencilOp failOp;
      StencilOp depthFailOp;
    };

    bool stencilTestEnable = false;
    FaceState front;
    FaceState back;
  } depthStencil;

  struct InputAssemblyState
  {
    PrimitiveTopology topology = PrimitiveTopology::TRIANGLE_LIST;
    bool primitiveRestartEnable = false;
    ;
  } inputAssembly;

  struct RasterizationState
  {
    PolygonMode polygonMode;
    CullMode cullMode;
    FrontFace frontFace;
  } rasterization;

  struct ShaderState
  {
    char const *vertexShader = nullptr;
    char const *fragmentShader = nullptr;
    char const *computeShader = nullptr;
  } shader;

  struct VertexInputState
  {
    enum
    {
      MAX_NUM_VERTEX_BINDINGS = 2,
      MAX_NUM_VERTEX_ATTRIBUTES = 8
    };

    struct BindingDescription
    {
      uint32_t binding;
      uint32_t stride;
      VertexInputRate inputRate;
    };

    BindingDescription bindingDescriptions[MAX_NUM_VERTEX_BINDINGS];
    uint32_t bindingDescriptionCnt = 0;
    ;

    struct AttributeDescription
    {
      uint32_t location;
      uint32_t binding;
      VertexFormat format;
      uint32_t offset;
    };

    AttributeDescription attributeDescriptions[MAX_NUM_VERTEX_BINDINGS];
    uint32_t attributeDescriptionCnt = 0;
  } vertexInput;

  struct ViewportState
  {
    Viewport viewport;
    Rect scissors;
  } viewport;

  struct MultisampleState
  {
    uint32_t rasterizationSamples = 1;
  } multisample;
};

enum class AttachmentType
{
  COLOR,
  DEPTH,
  RESOLVE
};

enum class LoadOp
{
  CLEAR,
  LOAD
};

enum class StoreOp
{
  DONT_CARE,
  STORE
};

union Color
{
  float float32[4];
  int32_t int32[4];
  uint32_t uint32[4];
};

struct DepthStencil
{
  float depth;
  uint32_t stencil;
};

union ClearValue
{
  Color color;
  DepthStencil depthStencil;
};

struct AttachmentInfo
{
  Texture texture;
  AttachmentType type;
  LoadOp loadOp;
  StoreOp storeOp;
  ClearValue clearValue;
  bool makePresentable;
};

struct RenderPass
{
  enum
  {
    MAX_NUM_ATTACHMENTS = 8
  };
  AttachmentInfo attachmentInfos[MAX_NUM_ATTACHMENTS] = {};
  uint32_t attachmentCnt = 0;
  ;
};

bool pkCreateDevice(Device *);

bool pkCreateSwapchain(Device, SwapchainCreateInfo const *, Swapchain *);
bool pkRecreateSwapchain(Device, SwapchainCreateInfo const *, Swapchain);
bool pkCreateBuffer(Device, BufferCreateInfo const *, Buffer *, void **data);
bool pkCreateTexture(Device, TextureCreateInfo const *, Texture *);

bool pkDestroySwapchain(Device, Swapchain);
bool pkDestroyBuffer(Device, Buffer);
bool pkDestroyTexture(Device, Texture);

bool pkGetQueue(Device, QueueType, Queue *);

bool pkCreateCmdBuffer(Queue, CmdBuffer *);

void pkCopy(CmdBuffer, Buffer dst, Buffer src);
void pkCopyBufferToTexture(CmdBuffer, Texture, Buffer);

void insertBarrier(CmdBuffer, BufferBarrier const *);
void insertBarrier(CmdBuffer, TextureBarrier const *);

void beginRenderPass(CmdBuffer, RenderPass const *);
void bindVertexBuffer(CmdBuffer, Buffer, uint64_t offset);
void bindIndexBuffer(CmdBuffer, Buffer);
void setPipelineState(CmdBuffer, PipelineState const *);
void bindUniformBuffer(CmdBuffer, Buffer, uint32_t set, uint32_t binding,
                       uint32_t offset, uint32_t range);
void bindStorageBuffer(CmdBuffer, Buffer, uint32_t set, uint32_t binding,
                       uint32_t offset, uint32_t range);
void bindStorageTexture(CmdBuffer, Texture, uint32_t set, uint32_t binding);
void bindSampler(CmdBuffer, uint32_t set, uint32_t binding);
void bindSampledTexture(CmdBuffer, Texture, uint32_t set, uint32_t binding);
void draw(CmdBuffer, uint32_t cnt);
// TODO: extend as needed
void pkBlit(CmdBuffer, Texture dst, TextureLayout dstLayout, Texture src,
            TextureLayout srcLayout);
void drawIndexed(CmdBuffer, uint32_t cnt);
void endRenderPass(CmdBuffer);

void dispatch(CmdBuffer, uint32_t x, uint32_t y, uint32_t z);

bool submit(Queue, CmdBuffer *, uint32_t cnt, Semaphore *wait,
            PipelineStageFlags *stage, uint32_t waitCnt, Semaphore *signal,
            uint32_t signalCnt, Fence *);

bool acquireNext(Device, Swapchain, Texture *, Semaphore *signal);
bool present(Queue, Swapchain, Semaphore *wait);

void frame(Device);

bool wait(Device, Fence);

void debugWait(Device);
