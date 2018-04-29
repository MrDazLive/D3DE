#include "../IRender.h"

namespace IRender {

  int glGenBlock(void(*genFunc)(GLsizei, GLuint*)) {
    GLuint index{ 0 };
    genFunc(1, &index);
    return (int)index;
  }

  bool Initialise() {
    return gladLoadGL() != 0;
  }

  void DrawElements(DrawMode mode, const size_t size, const size_t start) {
    glDrawElements(mode, (GLsizei)size, GL_UNSIGNED_INT, (void*)start);
  }

  void DrawElementsInstanced(DrawMode mode, const size_t size, const size_t start, const size_t count) {
    glDrawElementsInstanced(mode, (GLsizei)size, GL_UNSIGNED_INT, (void*)start, (GLsizei)count);
  }

}