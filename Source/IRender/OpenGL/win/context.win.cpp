#ifdef _WIN32

#include "../../IRender.h"

#include <windows.h>

#include <iostream>

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
      32,
      8,
      0,
      PFD_MAIN_PLANE,
      0,
      0, 0, 0
    };

    HWND hwnd = *(HWND*)ctx;
    HDC  hdc  = GetDC(hwnd);

    GLint ipf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, ipf, &pfd);

    HGLRC hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);
  }

  void SwapBuffer(const int idx, void* const ctx) {
    HWND hwnd = *(HWND*)ctx;
    HDC  hdc  = GetDC(hwnd);
    SwapBuffers(hdc);
  }
}

#endif