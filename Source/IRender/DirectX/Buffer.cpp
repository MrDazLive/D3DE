#include "../Buffer.h"

namespace IRender {

#define GL_BUFFER_FUNCTIONS(NAME, TYPE)                             \
  int Create##NAME() {                                              \
    /*GLuint index{ 0 };                                              \
    glGenBuffers(1, &index);*/                                        \
    return (int)0;                                              \
  }                                                                 \
                                                                    \
  void Delete##NAME(const int index) {                              \
    /*glDeleteBuffers(1, (GLuint*)&index);*/                            \
  }                                                                 \
                                                                    \
  void SetActive##NAME(const int index) {                           \
    /*glBindBuffer(TYPE, (GLuint)index);*/                              \
  }                                                                 \
                                                                    \
  void Set##NAME##Data(const void* data, const size_t dataSize) {   \
    /*glBufferData(TYPE, dataSize, data, GL_STATIC_DRAW);*/             \
  }                                                                 \

  GL_BUFFER_FUNCTIONS(ArrayBuffer,    GL_ARRAY_BUFFER);
  GL_BUFFER_FUNCTIONS(ElementBuffer,  GL_ELEMENT_ARRAY_BUFFER);
  GL_BUFFER_FUNCTIONS(UniformBuffer,  GL_UNIFORM_BUFFER);

#undef GL_BUFFER_FUNCTIONS

}