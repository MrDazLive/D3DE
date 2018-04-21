#include "../IRender.h"

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

#include <iostream>
#include <vector>

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

  void EnableCullFace() {
    glEnable(GL_CULL_FACE);
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

  int CreateVertexArray() {
    return glGenBlock(glGenVertexArrays);
  }

  int CreateFragmentShader(const char** sourceArray, const size_t sourceCount) {
    auto index = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(index, sourceCount, sourceArray , NULL);
    glCompileShader(index);
    return (int)index;
  }

  int CreateVertexShader(const char** sourceArray, const size_t sourceCount) {
    auto index = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(index, sourceCount, sourceArray , NULL);
    glCompileShader(index);


	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(index, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(index, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(index, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
    return (int)index;
  }

  int CreateShaderProgram(const int* shaderArray, size_t shaderCount) {
    auto index = glCreateProgram();

    auto loop = [&] (auto func) {
      for(size_t i = 0; i < shaderCount; ++i)
        func(shaderArray[(GLuint)i]);
    };

    loop([&](GLuint i){ glAttachShader(index, i); });
    glLinkProgram(index);
    loop([&](GLuint i){ glDetachShader(index, i); });
    loop([&](GLuint i){ glDeleteShader(       i); });

    return (int)index;
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

  void SetActiveVertexArray(const int index) {
    glBindVertexArray((GLuint)index);
  }

  void SetActiveShaderProgram(const int index) {
    glUseProgram((GLuint)index);
  }

  void SetArrayBufferData(const void* data, const size_t dataSize) {
  glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
  }

  void SetElementBufferData(const void* data, const size_t dataSize) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
  }

  void SetUniformBufferData(const void* data, const size_t dataSize) {
  glBufferData(GL_UNIFORM_BUFFER, dataSize, data, GL_STATIC_DRAW);
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

  void DeleteVertexArray(const int index) {
    glDeleteVertexArrays(1, (GLuint*)&index);
  }

  void DeleteShaderProgram(const int index) {
    glDeleteProgram((GLuint)index);
  }

  void DrawElements(DrawMode mode, const size_t size, const size_t start) {
    glDrawElements(mode, size, GL_UNSIGNED_INT, (void*)start);
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