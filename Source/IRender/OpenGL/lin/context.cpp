#include "../../IRender.h"

#include <GL/glx.h>

namespace IRender {
  void CreateContext(const int idx, void* const ctx) {
    Window    window  = (XID)idx;
    Display*  display = *(Display**)ctx;
    
    GLint attl[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
    XVisualInfo info = *glXChooseVisual(display, 0, attl);

    auto glc = glXCreateContext(display, &info, nullptr, GL_TRUE);
    glXMakeCurrent(display, window, glc);
  }

  void SwapBuffer(const int idx, void* const ctx) {
    Window    window  = (XID)idx;
    Display*  display = *(Display**)ctx;

    glXSwapBuffers(display, window);
  }
}