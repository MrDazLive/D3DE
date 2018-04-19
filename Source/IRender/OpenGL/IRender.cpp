#include "../IRender.h"

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

namespace IRender {

  int glGenBlock(void(*genFunc)(GLsizei, GLuint*)) {
    GLuint index{ 0 };
    genFunc(1, &index);
    return (int)index;
  }

  bool Initialise() {
    return gladLoadGL() != 0;
  }

  void ClearBuffer(const unsigned int bits) {
    glClear(bits);
  }

  void SetClearColour(const float& red, const float& green, const float& blue, const float& alpha) {
    glClearColor(red, green, blue, alpha);
  }

  void EnableDepthTest() {
    glEnable(GL_DEPTH_TEST);
  }

  int CreateArrayBuffer() {
    return glGenBlock((void(*)(GLsizei, GLuint*))glGenBuffers);
  }

  int CreateElementBuffer() {
    return glGenBlock(glGenBuffers);
  }

  int CreateUniformBuffer() {
    return glGenBlock(glGenBuffers);
  }

  int CreateVertexBuffer() {
    return glGenBlock(glGenBuffers);
  }

  int CreateVertexArray() {
    return glGenBlock(glGenVertexArrays);
  }

  void SetActiveArrayBuffer(const int index) {
    glBindBuffer(GL_ARRAY_BUFFER, (GLuint)index);
  }

  void SetActiveElementBuffer(const int index) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)index);
  }

  void SetActiveUniformBuffer(const int index) {
    glBindBuffer(GL_UNIFORM_BUFFER, (GLuint)index);
  }

  void SetActiveVertexBuffer(const int index) {
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, (GLuint)index);
  }

  void SetActiveVertexArray(const int index) {
    glBindVertexArray((GLuint)index);
  }

  void DeleteArrayBuffer(const int index) {
    glDeleteBuffers(1, (GLuint*)&index);
  }

  void DeleteElementBuffer(const int index) {
    glDeleteBuffers(1, (GLuint*)&index);
  }

  void DeleteUniformBuffer(const int index) {
    glDeleteBuffers(1, (GLuint*)&index);
  }

  void DeleteVertexBuffer(const int index) {
    glDeleteBuffers(1, (GLuint*)&index);
  }

  void DeleteVertexArray(const int index) {
    glDeleteVertexArrays(1, (GLuint*)&index);
  }

  void AddVertexAttribute(const unsigned int index, const size_t attriuteSize, const size_t glenum, const size_t vertexSize, const size_t offset) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, (GLint)attriuteSize, (GLenum)glenum, GL_FALSE, (GLsizei)vertexSize, (void*)offset);
  }

  template <>
  void AddVertexAttribute<int>(const unsigned int index, const size_t attriuteSize, const size_t vertexSize, const size_t offset) {
    AddVertexAttribute(index, attriuteSize, GL_INT, vertexSize, offset);
  }

  template <>
  void AddVertexAttribute<unsigned int>(const unsigned int index, const size_t attriuteSize, const size_t vertexSize, const size_t offset) {
    AddVertexAttribute(index, attriuteSize, GL_INT, vertexSize, offset);
  }

  template <>
  void AddVertexAttribute<float>(const unsigned int index, const size_t attriuteSize, const size_t vertexSize, const size_t offset) {
    AddVertexAttribute(index, attriuteSize, GL_FLOAT, vertexSize, offset);
  }

  template <>
  void AddVertexAttribute<double>(const unsigned int index, const size_t attriuteSize, const size_t vertexSize, const size_t offset) {
    AddVertexAttribute(index, attriuteSize, GL_DOUBLE, vertexSize, offset);
  }

}