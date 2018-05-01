#include "../Vertex.h"

namespace IRender {

  int CreateVertexArray() {
    GLuint index{ 0 };
    glGenVertexArrays(1, &index);
    return (int)index;
  }

  void SetActiveVertexArray(const int index) {
    glBindVertexArray((GLuint)index);
  }

  void DeleteVertexArray(const int index) {
    glDeleteVertexArrays(1, (GLuint*)&index);
  }

#define GL_VERTEX_ATTRIBUTE_FUNCTIONS(TYPE, ENUM)                                                                                                     \
  template <>                                                                                                                                         \
  void AddVertexAttribute<TYPE>(const unsigned int index, const size_t attriuteSize, const size_t vertexSize, const size_t offset, bool instanced) {  \
    glEnableVertexAttribArray(index);                                                                                                                 \
    glVertexAttribPointer(index, (GLint)attriuteSize, ENUM, GL_FALSE, (GLsizei)vertexSize, (void*)offset);                                            \
    if(instanced) glVertexAttribDivisor(index, 1);                                                                                                    \
  }                                                                                                                                                   \

  GL_VERTEX_ATTRIBUTE_FUNCTIONS(int,            GL_INT);
  GL_VERTEX_ATTRIBUTE_FUNCTIONS(unsigned int,   GL_UNSIGNED_INT);
  GL_VERTEX_ATTRIBUTE_FUNCTIONS(float,          GL_FLOAT);
  GL_VERTEX_ATTRIBUTE_FUNCTIONS(double,         GL_DOUBLE);

#undef GL_VERTEX_ATTRIBUTE_FUNCTIONS

}