#include "../Buffer.h"
#include "context.h"

#include <map>

namespace IRender {

  using   BufferMap           = std::map<int, ID3D11Buffer*>;
  static  BufferMap           g_bufferMap;
  static  BufferMap::iterator g_activeBuffer;

  static int genBuffer() {
    static int count = 0;
    g_bufferMap.emplace(++count, nullptr);
    return count;
  }

  static void deleteBuffer(int index) {
    auto it   = g_bufferMap.find(index);
    auto end  = g_bufferMap.end();
    if (it == end)
      return;

    if (it == g_activeBuffer)
      g_activeBuffer = end;

    if(auto buffer = it->second)
      buffer->Release();
  }

  static void bufferData(D3D11_BIND_FLAG type, const size_t size, const void* data) {
    if (g_activeBuffer == g_bufferMap.end())
      return;
    
    auto& buffer = g_activeBuffer->second;
    
    if (buffer) {
      D3D11_BUFFER_DESC desc;
      ZeroMemory(&desc, sizeof(desc));

      buffer->GetDesc(&desc);
      if (desc.ByteWidth != size) {
        buffer->Release();
        buffer = nullptr;
      }
    }

    if (!buffer) {
      D3D11_BUFFER_DESC desc;
      ZeroMemory(&desc, sizeof(desc));

      desc.Usage          = D3D11_USAGE_DYNAMIC;
      desc.ByteWidth      = (UINT)size;
      desc.BindFlags      = type;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

      DX::Device()->CreateBuffer(&desc, nullptr, &buffer);
    }

    D3D11_MAPPED_SUBRESOURCE ms;
    DX::DeviceContext()->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    memcpy(ms.pData, data, size);
    DX::DeviceContext()->Unmap(buffer, NULL);
  }

#define DX_BUFFER_FUNCTIONS(NAME, TYPE)                             \
  int Create##NAME() {                                              \
    return genBuffer();                                             \
  }                                                                 \
                                                                    \
  void Delete##NAME(const int index) {                              \
    deleteBuffer(index);                                            \
  }                                                                 \
                                                                    \
  void SetActive##NAME(const int index) {                           \
    g_activeBuffer = g_bufferMap.find(index);                       \
  }                                                                 \
                                                                    \
  void Set##NAME##Data(const void* data, const size_t dataSize) {   \
    bufferData(TYPE, dataSize, data);                               \
  }                                                                 \

  DX_BUFFER_FUNCTIONS(ArrayBuffer,    D3D11_BIND_VERTEX_BUFFER);
  DX_BUFFER_FUNCTIONS(ElementBuffer,  D3D11_BIND_INDEX_BUFFER);
  DX_BUFFER_FUNCTIONS(UniformBuffer,  D3D11_BIND_CONSTANT_BUFFER);

#undef GL_BUFFER_FUNCTIONS

}