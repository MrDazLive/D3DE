#include "../Shader.h"

#include <vector>
#include <iostream>
#include <functional>

namespace IRender {

  // Temporary error handling.
  void PrintShaderError(GLuint index) {
    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(index, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(index, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
      std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(index, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      printf("%s\n", &VertexShaderErrorMessage[0]);
    }
  }

#define GL_SHADER_FUNCTIONS(NAME, TYPE)                                           \
  int Create##NAME##Shader(const char** sourceArray, const size_t sourceCount) {  \
    auto index = glCreateShader(TYPE);                                            \
    glShaderSource(index, (GLsizei)sourceCount, sourceArray, NULL);               \
    glCompileShader(index);                                                       \
    PrintShaderError(index);                                                      \
    return (int)index;                                                            \
  }                                                                               \
                                                                                  \
  void Delete##NAME##Shader(const int index) {                                    \
    glDeleteShader((GLuint)index);                                                \
  }                                                                               \

  GL_SHADER_FUNCTIONS(Vertex,   GL_VERTEX_SHADER);
  GL_SHADER_FUNCTIONS(Fragment, GL_FRAGMENT_SHADER);

#undef GL_SHADER_FUNCTIONS

  int CreateShaderProgram(const int* shaderArray, size_t shaderCount) {
    auto index = glCreateProgram();

    auto loop = [&] (std::function<void(GLuint)> func) {
      for(size_t i = 0; i < shaderCount; ++i)
        func((GLuint)shaderArray[i]);
    };

    loop([&](GLuint i){ glAttachShader(index, i); });
    glLinkProgram(index);
    loop([&](GLuint i){ glDetachShader(index, i); });

    return (int)index;
  }

  void DeleteShaderProgram(const int index) {
    glDeleteProgram((GLuint)index);
  }

  void SetActiveShaderProgram(const int index) {
    glUseProgram((GLuint)index);
  }

  int GetUniformIndex(const int program, const char* uniform) {
    return (int)glGetUniformLocation((GLuint)program, uniform);
  }

#define GL_UNIFORM_FUNCTIONS(TYPE, Y, X, FUNC)                      \
  template <>                                                       \
  void SetUniformValue<TYPE, Y, X>(const int index, TYPE* value) {  \
    [](const int index, TYPE* value) { FUNC; }(index, value);       \
  }                                                                 \

#define GL_TYPE_UNIFORM_FUNCTIONS(TYPE, EXT)                                                          \
  GL_UNIFORM_FUNCTIONS(TYPE, 1, 1, glUniform1##EXT(index, value[0]));                                 \
  GL_UNIFORM_FUNCTIONS(TYPE, 1, 2, glUniform2##EXT(index, value[0], value[1]));                       \
  GL_UNIFORM_FUNCTIONS(TYPE, 1, 3, glUniform3##EXT(index, value[0], value[1], value[2]));             \
  GL_UNIFORM_FUNCTIONS(TYPE, 1, 4, glUniform4##EXT(index, value[0], value[1], value[2], value[3]));   \

  GL_TYPE_UNIFORM_FUNCTIONS(float,    f);
  GL_TYPE_UNIFORM_FUNCTIONS(int,      i);
  GL_TYPE_UNIFORM_FUNCTIONS(unsigned, ui);

  GL_UNIFORM_FUNCTIONS(float, 2, 2, glUniformMatrix2fv(index, 1, GL_FALSE, value));
  GL_UNIFORM_FUNCTIONS(float, 2, 3, glUniformMatrix2x3fv(index, 1, GL_FALSE, value));
  GL_UNIFORM_FUNCTIONS(float, 2, 4, glUniformMatrix2x4fv(index, 1, GL_FALSE, value));

  GL_UNIFORM_FUNCTIONS(float, 3, 2, glUniformMatrix3x2fv(index, 1, GL_FALSE, value));
  GL_UNIFORM_FUNCTIONS(float, 3, 3, glUniformMatrix3fv(index, 1, GL_FALSE, value));
  GL_UNIFORM_FUNCTIONS(float, 3, 4, glUniformMatrix3x4fv(index, 1, GL_FALSE, value));

  GL_UNIFORM_FUNCTIONS(float, 4, 2, glUniformMatrix4x2fv(index, 1, GL_FALSE, value));
  GL_UNIFORM_FUNCTIONS(float, 4, 3, glUniformMatrix4x3fv(index, 1, GL_FALSE, value));
  GL_UNIFORM_FUNCTIONS(float, 4, 4, glUniformMatrix4fv(index, 1, GL_FALSE, value));

#undef GL_TYPE_UNIFORM_FUNCTIONS
#undef GL_UNIFORM_FUNCTIONS

}