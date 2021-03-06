#ifdef _WIN32

#include "../../IRender.h"

#include <windows.h>
#include <map>

static HDC getDeviceContext(void* const ctx) {
  static std::map<void*, HDC> contextMap;
  auto it = contextMap.find(ctx);
  if (it != contextMap.end())
    return it->second;

  HWND hwnd = *(HWND*)ctx;
  HDC  hdc = GetDC(hwnd);
  contextMap.emplace(ctx, hdc);
  return hdc;
}

namespace IRender {
  void CreateContext(const int idx, void* const ctx) {
    PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      32,
      0, 0, 0, 0, 0, 0,
      0,
      0,
      0,
      0, 0, 0, 0,
      24,
      8,
      0,
      PFD_MAIN_PLANE,
      0,
      0, 0, 0
    };

    HDC  hdc  = getDeviceContext(ctx);
    GLint ipf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, ipf, &pfd);

    HGLRC hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);
  }

  void SwapBuffer(const int idx, void* const ctx) {
    SwapBuffers(getDeviceContext(ctx));
  }
}

#endif