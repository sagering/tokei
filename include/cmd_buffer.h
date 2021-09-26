#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H

#include <stdint.h>

#include "device.h"

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
    bool enable;
    BlendOp colorOp;
    BlendFactor srcColorFactor;
    BlendFactor dstColorFactor;
    BlendOp alphaOp;
    BlendFactor srcAlphaFactor;
    BlendFactor dstAlphaFactor;
  } blend;

  struct DepthStencilState
  {
    bool depthTestenable;
    bool depthWriteEnable;
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

    bool stencilTestEnable;
    FaceState front;
    FaceState back;
  } depthStencil;

  struct InputAssemblyState
  {
    PrimitiveTopology topology;
    bool primitiveRestartEnable;
  } inputAssembly;

  struct RasterizationState
  {
    PolygonMode polygonMode;
    CullMode cullMode;
    FrontFace frontFace;
  } rasterization;

  struct ShaderState
  {
    char const* vertexShader;
    char const* fragmentShader;
    char const* computeShader;
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
    uint32_t bindingDescriptionCnt;

    struct AttributeDescription
    {
      uint32_t location;
      uint32_t binding;
      VertexFormat format;
      uint32_t offset;
    };

    AttributeDescription attributeDescriptions[MAX_NUM_VERTEX_BINDINGS];
    uint32_t attributeDescriptionCnt;
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

struct RenderPassBeginInfo
{
  enum
  {
    MAX_NUM_ATTACHMENTS = 8
  };
  AttachmentInfo attachmentInfos[MAX_NUM_ATTACHMENTS];
  uint32_t attachmentCnt;
};

enum class TextureBarrierScope
{
  None,
  ColorAttachment,
  DepthStencilAttachment,
  SampledTexture,
  PresentSrc,
  TransferSrc,
  TransferDst
};

struct TextureBarrierInfo
{
  UsageScope src;
  UsageScope dst;
  Texture texture;
};

struct BufferBarrierInfo
{
  UsageScope src;
  UsageScope dst;
  Buffer buffer;
};

class CmdBuffer
{
public:
  virtual void Copy(Buffer dst, Buffer src) = 0;
  virtual void CopyBufferToTexture(Texture dst, Buffer src) = 0;

  virtual void BufferBarrier(BufferBarrierInfo const& info) = 0;
  virtual void TextureBarrier(TextureBarrierInfo const& info) = 0;

  virtual void BeginRenderPass(RenderPassBeginInfo const& beginInfo) = 0;
  virtual void BindVertexBuffer(Buffer buffer, uint64_t offset) = 0;
  virtual void BindIndexBuffer(Buffer buffer) = 0;
  virtual void SetPipelineState(PipelineState pipelineState) = 0;
  virtual void BindUniformBuffer(Buffer buffer,
                                 uint32_t set,
                                 uint32_t binding,
                                 uint32_t offset,
                                 uint32_t range) = 0;
  virtual void BindStorageBuffer(Buffer buffer,
                                 uint32_t set,
                                 uint32_t binding,
                                 uint32_t offset,
                                 uint32_t range) = 0;
  virtual void BindSampler(uint32_t set, uint32_t binding) = 0;
  virtual void BindSampledTexture(Texture texture,
                                  uint32_t set,
                                  uint32_t binding) = 0;
  virtual void Draw(uint32_t cnt) = 0;
  virtual void DrawIndexed(uint32_t cnt) = 0;
  virtual void Dispatch(uint32_t x, uint32_t y, uint32_t z) = 0;
  virtual void EndRenderPass() = 0;
};

#endif // !COMMAND_BUFFER_H
