#include "../IRender.h"
#include <iostream>

namespace IRender {

  bool Initialise() {
    if (gladLoadGL() == 0)
      return false;

    /*if (GLAD_GL_VERSION_3_3 == 0)
      return false;*/

    return true;
  }

  void DrawElements(DrawMode mode, const size_t size, const size_t start) {
    glDrawElements((GLenum)mode, (GLsizei)size, GL_UNSIGNED_INT, (void*)start);
  }

  void DrawElementsInstanced(DrawMode mode, const size_t size, const size_t start, const size_t count) {
    glDrawElementsInstanced((GLenum)mode, (GLsizei)size, GL_UNSIGNED_INT, (void*)start, (GLsizei)count);
  }

}