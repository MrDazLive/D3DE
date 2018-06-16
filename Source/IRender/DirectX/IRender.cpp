#include "../IRender.h"

#include "context.h"

#include <iostream>
#include <map>

static float clearColour[4] { 1.0f, 1.0f, 1.0f, 1.0f };

namespace IRender {

  bool Initialise() {
    return DX::Device() != nullptr;
  }

  void CreateContext(const int idx, void* const ctx) {
    HWND hWnd = *(HWND*)ctx;

    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.OutputWindow = hWnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &DX::SwapChain(),
                                  &DX::Device(),
                                  NULL,
                                  &DX::DeviceContext());

    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    DX::SwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    DX::Device()->CreateRenderTargetView(pBackBuffer, NULL, &DX::BackBuffer());
    pBackBuffer->Release();

    // set the render target as the back buffer
    DX::DeviceContext()->OMSetRenderTargets(1, &DX::BackBuffer(), NULL);
  }

  void SwapBuffer(const int idx, void* const ctx) {
    DX::SwapChain()->Present(DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, 0);
  }

  void DrawElements(DrawMode mode, const size_t size, const size_t start) {
    //glDrawElements(mode, (GLsizei)size, GL_UNSIGNED_INT, (void*)start);
  }

  void DrawElementsInstanced(DrawMode mode, const size_t size, const size_t start, const size_t count) {
    //glDrawElementsInstanced(mode, (GLsizei)size, GL_UNSIGNED_INT, (void*)start, (GLsizei)count);
  }

  void EnableDepthTest() {
    //glEnable(GL_DEPTH_TEST);
  }

  void EnableCullFace() {
    //glEnable(GL_CULL_FACE);
  }

  void ClearBuffer(const unsigned int bits) {
    if(bits & BufferBit::COLOUR) DX::DeviceContext()->ClearRenderTargetView(DX::BackBuffer(), clearColour);
  }

  void SetViewport(const int x, const int y, const unsigned int width, const unsigned int height) {
    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = (float)x;
    viewport.TopLeftY = (float)y;
    viewport.Width = (float)width;
    viewport.Height = (float)height;

    DX::DeviceContext()->RSSetViewports(1, &viewport);
  }

  void SetClearColour(const float& red, const float& green, const float& blue, const float& alpha) {
    clearColour[0] = red;
    clearColour[1] = green;
    clearColour[2] = blue;
    clearColour[3] = alpha;
  }

}