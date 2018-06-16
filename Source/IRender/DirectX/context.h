#pragma once
#ifndef IRENDER_DIRECTX_CONTEXT_HEADER
#define IRENDER_DIRECTX_CONTEXT_HEADER

#include <windows.h>
#include <windowsx.h>

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

struct DX {

  DX() = delete;

  static IDXGISwapChain*& SwapChain() {
    static IDXGISwapChain* i;
    return i;
  }

  static ID3D11Device*& Device() {
    static ID3D11Device* i;
    return i;
  }

  static ID3D11DeviceContext*& DeviceContext() {
    static ID3D11DeviceContext* i;
    return i;
  }

  static ID3D11RenderTargetView*& BackBuffer() {
    static ID3D11RenderTargetView* i;
    return i;
  }

};

#endif