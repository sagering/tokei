#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

#include <tuple>

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

typedef struct Buffer_T* Buffer;
typedef struct Texture_T* Texture;
typedef struct Swapchain_T* Swapchain;
typedef struct Ticket_T* Ticket;

// Pixel components are abreviated using the following letters:
//
// A = Alpha
// R = Red
// G = Green
// B = Blue
// D = Depth
// S = Stencil
//

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
  char const* name = nullptr;
};

struct BufferCreateInfo
{
  uint64_t size;
  BufferUsageFlags usageFlags;
  MemoryUsage memoryUsage;
  char const* name = nullptr;
};

struct SwapchainCreateInfo
{
  uint32_t width;
  uint32_t height;
  uint32_t depth;
  PixelFormat format;
  TextureUsageFlags usageFlags;
  uint32_t textureCnt;
  void* platformHandle;
  Swapchain oldSwapchain;
  char const* name = nullptr;
};

class CmdBuffer;

class Device
{
public:
  static Device* Create();

  virtual CmdBuffer* GetCmdBuffer() = 0;
  virtual Ticket Submit(CmdBuffer* cmdBuffer) = 0;
  virtual void Wait(Ticket ticket) = 0;

  virtual std::pair<Buffer, void*> CreateBuffer(
    BufferCreateInfo const& createInfo) = 0;

  virtual Texture CreateTexture(TextureCreateInfo const& createInfo) = 0;
  virtual Swapchain CreateSwapchain(SwapchainCreateInfo const& createInfo) = 0;

  virtual bool AquireNext(Swapchain swapchain, Texture* texture) = 0;
  virtual bool Present(Swapchain swapchain) = 0;

  virtual void Release(Buffer buffer) = 0;
  virtual void Release(Texture texture) = 0;
  virtual void Release(Swapchain swapchain) = 0;
  virtual void Recycle() = 0;
};

// typedef struct Dev_T* Dev;
// typedef struct CmdBuf_T* CmdBuf;
//
// typedef struct BufferInfo {
//  Buffer buffer;
//  void* data;
//} BufferInfo;
//
// void CreateDevice(Dev* pDev);
// void CreateBuffer(Dev dev, BufferCreateInfo* pCreateInfo, BufferInfo* pInfo);
// void CreateTexture(Dev dev, TextureCreateInfo* pCreateInfo, Texture*
// pTexture); void CreateSwapchain(Dev dev, SwapchainCreateInfo* pCreateInfo,
//                     Swapchain* pSwapchain);
//
// void CreateCmdBuffer(Dev dev, CmdBuf* pCmdBuf);
// void Submit(Dev dev, CmdBuf cmdBuf);
//
// int AquireNext(Swapchain swapchain, Texture* pTexture);
// int Present(Swapchain swapchain);
//
// void Toss(Dev dev, Buffer buffer);
// void Toss(Dev dev, Swapchain swapchain);
// void Recycle(Dev dev);

#endif // !DEVICE_H
