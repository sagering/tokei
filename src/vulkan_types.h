#pragma once

#include <cmd_buffer.h>

inline VkBlendFactor GetVkBlendFactor(BlendFactor blendFactor) {
  switch (blendFactor) {
    case BlendFactor::ZERO:
      return VK_BLEND_FACTOR_ZERO;
      break;
    case BlendFactor::ONE:
      return VK_BLEND_FACTOR_ONE;
      break;
    case BlendFactor::SRC0_COLOR:
      return VK_BLEND_FACTOR_SRC_COLOR;
      break;
    case BlendFactor::ONE_MINUS_SRC0_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
      break;
    case BlendFactor::DST_COLOR:
      return VK_BLEND_FACTOR_DST_COLOR;
      break;
    case BlendFactor::ONE_MINUS_DST_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
      break;
    case BlendFactor::SRC0_ALPHA:
      return VK_BLEND_FACTOR_SRC_ALPHA;
      break;
    case BlendFactor::ONE_MINUS_SRC0_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
      break;
    case BlendFactor::DST_ALPHA:
      return VK_BLEND_FACTOR_DST_ALPHA;
      break;
    case BlendFactor::ONE_MINUS_DST_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
      break;
    case BlendFactor::CONSTANT_COLOR:
      return VK_BLEND_FACTOR_CONSTANT_COLOR;
      break;
    case BlendFactor::ONE_MINUS_CONSTANT_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
      break;
    case BlendFactor::CONSTANT_ALPHA:
      return VK_BLEND_FACTOR_CONSTANT_ALPHA;
      break;
    case BlendFactor::ONE_MINUS_CONSTANT_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
      break;
    case BlendFactor::SRC0_ALPHA_SATURATE:
      return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
      break;
    case BlendFactor::SRC1_COLOR:
      return VK_BLEND_FACTOR_SRC1_COLOR;
      break;
    case BlendFactor::ONE_MINUS_SRC1_COLOR:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
      break;
    case BlendFactor::SRC1_ALPHA:
      return VK_BLEND_FACTOR_SRC1_ALPHA;
      break;
    case BlendFactor::ONE_MINUS_SRC1_ALPHA:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
      break;
    default:
      return VK_BLEND_FACTOR_ONE;
      break;
  }
}

inline VkVertexInputRate GetVkVertexInputRate(VertexInputRate inputRate) {
  switch (inputRate) {
    case VertexInputRate::VERTEX:
      return VK_VERTEX_INPUT_RATE_VERTEX;
      break;
    case VertexInputRate::INSTANCE:
      return VK_VERTEX_INPUT_RATE_INSTANCE;
      break;
    default:
      return VK_VERTEX_INPUT_RATE_VERTEX;
      break;
  }
}

inline VkFormat GetVkFormat(VertexFormat format) {
  switch (format) {
    case VertexFormat::UCHAR:
      return VK_FORMAT_R8_UINT;
      break;
    case VertexFormat::UCHAR2:
      return VK_FORMAT_R8G8_UINT;
      break;
    case VertexFormat::UCHAR3:
      return VK_FORMAT_R8G8B8_UINT;
      break;
    case VertexFormat::UCHAR4:
      return VK_FORMAT_R8G8B8A8_UINT;
      break;
    case VertexFormat::CHAR:
      return VK_FORMAT_R8_SINT;
      break;
    case VertexFormat::CHAR2:
      return VK_FORMAT_R8G8_SINT;
      break;
    case VertexFormat::CHAR3:
      return VK_FORMAT_R8G8B8_SINT;
      break;
    case VertexFormat::CHAR4:
      return VK_FORMAT_R8G8B8A8_SINT;
      break;
    case VertexFormat::UCHAR_N:
      return VK_FORMAT_R8_UNORM;
      break;
    case VertexFormat::UCHAR2_N:
      return VK_FORMAT_R8G8_UNORM;
      break;
    case VertexFormat::UCHAR3_N:
      return VK_FORMAT_R8G8B8_UNORM;
      break;
    case VertexFormat::UCHAR4_N:
      return VK_FORMAT_R8G8B8A8_UNORM;
      break;
    case VertexFormat::CHAR_N:
      return VK_FORMAT_R8_SNORM;
      break;
    case VertexFormat::CHAR2_N:
      return VK_FORMAT_R8G8_SNORM;
      break;
    case VertexFormat::CHAR3_N:
      return VK_FORMAT_R8G8B8_SNORM;
      break;
    case VertexFormat::CHAR4_N:
      return VK_FORMAT_R8G8B8A8_SNORM;
      break;
    case VertexFormat::USHORT:
      return VK_FORMAT_R16_UINT;
      break;
    case VertexFormat::USHORT2:
      return VK_FORMAT_R16G16_UINT;
      break;
    case VertexFormat::USHORT3:
      return VK_FORMAT_R16G16B16_UINT;
      break;
    case VertexFormat::USHORT4:
      return VK_FORMAT_R16G16B16A16_UINT;
      break;
    case VertexFormat::SHORT:
      return VK_FORMAT_R16_SINT;
      break;
    case VertexFormat::SHORT2:
      return VK_FORMAT_R16G16_SINT;
      break;
    case VertexFormat::SHORT3:
      return VK_FORMAT_R16G16B16_SINT;
      break;
    case VertexFormat::SHORT4:
      return VK_FORMAT_R16G16B16A16_SINT;
      break;
    case VertexFormat::USHORT_N:
      return VK_FORMAT_R16_UNORM;
      break;
    case VertexFormat::USHORT2_N:
      return VK_FORMAT_R16G16_UNORM;
      break;
    case VertexFormat::USHORT3_N:
      return VK_FORMAT_R16G16B16_UNORM;
      break;
    case VertexFormat::USHORT4_N:
      return VK_FORMAT_R16G16B16A16_UNORM;
      break;
    case VertexFormat::SHORT_N:
      return VK_FORMAT_R16_SNORM;
      break;
    case VertexFormat::SHORT2_N:
      return VK_FORMAT_R16G16_SNORM;
      break;
    case VertexFormat::SHORT3_N:
      return VK_FORMAT_R16G16B16_SNORM;
      break;
    case VertexFormat::SHORT4_N:
      return VK_FORMAT_R16G16B16A16_SNORM;
      break;
    case VertexFormat::UINT:
      return VK_FORMAT_R32_UINT;
      break;
    case VertexFormat::UINT2:
      return VK_FORMAT_R32G32_UINT;
      break;
    case VertexFormat::UINT3:
      return VK_FORMAT_R32G32B32_UINT;
      break;
    case VertexFormat::UINT4:
      return VK_FORMAT_R32G32B32A32_UINT;
      break;
    case VertexFormat::INT:
      return VK_FORMAT_R32_SINT;
      break;
    case VertexFormat::INT2:
      return VK_FORMAT_R32G32_SINT;
      break;
    case VertexFormat::INT3:
      return VK_FORMAT_R32G32B32_SINT;
      break;
    case VertexFormat::INT4:
      return VK_FORMAT_R32G32B32A32_SINT;
      break;
    case VertexFormat::HALF:
      return VK_FORMAT_R16_SFLOAT;
      break;
    case VertexFormat::HALF2:
      return VK_FORMAT_R16G16_SFLOAT;
      break;
    case VertexFormat::HALF3:
      return VK_FORMAT_R16G16B16_SFLOAT;
      break;
    case VertexFormat::HALF4:
      return VK_FORMAT_R16G16B16A16_SFLOAT;
      break;
    case VertexFormat::FLOAT:
      return VK_FORMAT_R32_SFLOAT;
      break;
    case VertexFormat::FLOAT2:
      return VK_FORMAT_R32G32_SFLOAT;
      break;
    case VertexFormat::FLOAT3:
      return VK_FORMAT_R32G32B32_SFLOAT;
      break;
    case VertexFormat::FLOAT4:
      return VK_FORMAT_R32G32B32A32_SFLOAT;
      break;
    default:
      return VK_FORMAT_R32G32B32A32_SFLOAT;
      break;
  }
}

inline VkFormat GetVkFormat(PixelFormat pixelFormat) {
  switch (pixelFormat) {
    case A8_UNORM:  // fallthrough
    case R8_UNORM:
      return VK_FORMAT_R8_UNORM;
    case R8_UNORM_SRGB:
      return VK_FORMAT_R8_SRGB;
    case R8_SNORM:
      return VK_FORMAT_R8_SNORM;
    case R8_UINT:
      return VK_FORMAT_R8_UINT;
    case R8_SINT:
      return VK_FORMAT_R8_SINT;
    case R16_UNORM:
      return VK_FORMAT_R16_UNORM;
    case R16_SNORM:
      return VK_FORMAT_R16_SNORM;
    case R16_UINT:
      return VK_FORMAT_R16_UINT;
    case R16_SINT:
      return VK_FORMAT_R16_SINT;
    case R16_FLOAT:
      return VK_FORMAT_R16_SFLOAT;
    case RG8_UNORM:
      return VK_FORMAT_R8G8_UNORM;
    case RG8_UNORM_SRGB:
      return VK_FORMAT_R8G8_SRGB;
    case RG8_SNORM:
      return VK_FORMAT_R8G8_SNORM;
    case RG8_UINT:
      return VK_FORMAT_R8G8_UINT;
    case RG8_SINT:
      return VK_FORMAT_R8G8_SINT;
    case B5G6R5_UNORM:
      return VK_FORMAT_B5G6R5_UNORM_PACK16;
    case A1BGR5_UNORM:
      return VK_FORMAT_A1R5G5B5_UNORM_PACK16;
    // case ABGR4_UNORM:
    //	break;
    case BGR5A1_UNORM:
      return VK_FORMAT_B5G5R5A1_UNORM_PACK16;
    case R32_UINT:
      return VK_FORMAT_R32_UINT;
    case R32_SINT:
      return VK_FORMAT_R32_SINT;
    case R32_FLOAT:
      return VK_FORMAT_R32_SFLOAT;
    case RG16_UNORM:
      return VK_FORMAT_R16G16_UNORM;
    case RG16_SNORM:
      return VK_FORMAT_R16G16_SNORM;
    case RG16_UINT:
      return VK_FORMAT_R16G16_UINT;
    case RG16_SINT:
      return VK_FORMAT_R16G16_SINT;
    case RG16_FLOAT:
      return VK_FORMAT_R16G16_SFLOAT;
    case RGBA8_UNORM:
      return VK_FORMAT_R8G8B8A8_UNORM;
    case RGBA8_UNORM_SRGB:
      return VK_FORMAT_R8G8B8A8_SRGB;
    case RGBA8_SNORM:
      return VK_FORMAT_R8G8B8A8_SNORM;
    case RGBA8_UINT:
      return VK_FORMAT_R8G8B8A8_UINT;
    case RGBA8_SINT:
      return VK_FORMAT_R8G8B8A8_SINT;
    case BGRA8_UNORM:
      return VK_FORMAT_B8G8R8A8_UNORM;
    case BGRA8_UNORM_SRGB:
      return VK_FORMAT_B8G8R8A8_SRGB;
    default:
      return VK_FORMAT_R8G8B8A8_SRGB;
  }
}
inline VkPrimitiveTopology GetVkPrimitiveTopology(PrimitiveTopology topo) {
  switch (topo) {
    case PrimitiveTopology::POINT_LIST:
      return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
      break;
    case PrimitiveTopology::LINE_LIST:
      return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
      break;
    case PrimitiveTopology::LINE_STRIP:
      return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
      break;
    case PrimitiveTopology::TRIANGLE_LIST:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
      break;
    case PrimitiveTopology::TRIANGLE_STRIP:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
      break;
    case PrimitiveTopology::TRIANGLE_FAN:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
      break;
    case PrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
      break;
    case PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
      break;
    case PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
      break;
    case PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
      break;
    case PrimitiveTopology::PATCH_LIST:
      return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
      break;
    default:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
      break;
  }
}

inline VkPolygonMode GetVkPolygonMode(PolygonMode mode) {
  switch (mode) {
    case PolygonMode::FILL:
      return VK_POLYGON_MODE_FILL;
      break;
    case PolygonMode::LINE:
      return VK_POLYGON_MODE_LINE;
      break;
    case PolygonMode::POINT:
      return VK_POLYGON_MODE_POINT;
      break;
    default:
      return VK_POLYGON_MODE_FILL;
      break;
  }
}

inline VkCullModeFlags GetVkCullModeFlags(CullMode mode) {
  switch (mode) {
    case CullMode::NONE:
      return 0;
      break;
    case CullMode::FRONT:
      return VK_CULL_MODE_FRONT_BIT;
      break;
    case CullMode::BACK:
      return VK_CULL_MODE_BACK_BIT;
      break;
    case CullMode::FRONT_AND_BACK:
      return VK_CULL_MODE_FRONT_BIT | VK_CULL_MODE_BACK_BIT;
      break;
    default:
      return 0;
      break;
  }
}

inline VkFrontFace GetVkFrontFace(FrontFace face) {
  switch (face) {
    case FrontFace::COUNTER_CLOCKWISE:
      return VK_FRONT_FACE_COUNTER_CLOCKWISE;
      break;
    case FrontFace::CLOCKWISE:
      return VK_FRONT_FACE_CLOCKWISE;
      break;
    default:
      return VK_FRONT_FACE_CLOCKWISE;
      break;
  }
}

inline VkCompareOp GetVkCompareOp(CompareOp op) {
  switch (op) {
    case CompareOp::NEVER:
      return VK_COMPARE_OP_NEVER;
      break;
    case CompareOp::LESS:
      return VK_COMPARE_OP_LESS;
      break;
    case CompareOp::EQUAL:
      return VK_COMPARE_OP_EQUAL;
      break;
    case CompareOp::LESS_OR_EQUAL:
      return VK_COMPARE_OP_LESS_OR_EQUAL;
      break;
    case CompareOp::GREATER:
      return VK_COMPARE_OP_GREATER;
      break;
    case CompareOp::NOT_EQUAL:
      return VK_COMPARE_OP_NOT_EQUAL;
      break;
    case CompareOp::GREATER_OR_EQUAL:
      return VK_COMPARE_OP_LESS_OR_EQUAL;
      break;
    case CompareOp::ALWAYS:
      return VK_COMPARE_OP_ALWAYS;
      break;
    default:
      return VK_COMPARE_OP_NEVER;
      break;
  }
}

inline VkStencilOp GetVkStencilOp(StencilOp op) {
  switch (op) {
    case StencilOp::KEEP:
      return VK_STENCIL_OP_KEEP;
      break;
    case StencilOp::ZERO:
      return VK_STENCIL_OP_ZERO;
      break;
    case StencilOp::REPLACE:
      return VK_STENCIL_OP_REPLACE;
      break;
    case StencilOp::INCREMENT_AND_CLAMP:
      return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
      break;
    case StencilOp::DECREMENT_AND_CLAMP:
      return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
      break;
    case StencilOp::INVERT:
      return VK_STENCIL_OP_INVERT;
      break;
    case StencilOp::INCREMENT_AND_WRAP:
      return VK_STENCIL_OP_INCREMENT_AND_WRAP;
      break;
    case StencilOp::DECREMENT_AND_WRAP:
      return VK_STENCIL_OP_DECREMENT_AND_WRAP;
      break;
    default:
      return VK_STENCIL_OP_KEEP;
      break;
  }
}

inline VkAttachmentLoadOp GetVkAttachmentLoadOp(LoadOp op) {
  switch (op) {
    case LoadOp::CLEAR:
      return VK_ATTACHMENT_LOAD_OP_CLEAR;
      break;
    case LoadOp::LOAD:
      return VK_ATTACHMENT_LOAD_OP_LOAD;
      break;
    default:
      return VK_ATTACHMENT_LOAD_OP_CLEAR;
      break;
  }
}

inline VkAttachmentStoreOp GetVkAttachmentStoreOp(StoreOp op) {
  switch (op) {
    case StoreOp::DONT_CARE:
      return VK_ATTACHMENT_STORE_OP_DONT_CARE;
      break;
    case StoreOp::STORE:
      return VK_ATTACHMENT_STORE_OP_STORE;
      break;
    default:
      return VK_ATTACHMENT_STORE_OP_STORE;
      break;
  }
}

inline VkStencilOpState GetVkStencilOpState(
    PipelineState::DepthStencilState::FaceState in) {
  VkStencilOpState out = {};
  out.compareMask = in.compareMask;
  out.compareOp = GetVkCompareOp(in.compareOp);
  out.depthFailOp = GetVkStencilOp(in.depthFailOp);
  out.failOp = GetVkStencilOp(in.failOp);
  out.passOp = GetVkStencilOp(in.passOp);
  out.reference = in.reference;
  out.writeMask = in.writeMask;

  return out;
}
