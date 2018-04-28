#pragma once

#include "defines.h"

namespace IRender {

  IRENDER_API int   CreateFragmentShader    (const char**, const size_t);

  IRENDER_API void  DeleteFragmentShader    (const int);

  IRENDER_API int   CreateVertexShader      (const char**, const size_t);

  IRENDER_API void  DeleteVertexShader      (const int);

  IRENDER_API int   CreateShaderProgram     (const int*, const size_t);

  IRENDER_API void  DeleteShaderProgram     (const int);

  IRENDER_API void  SetActiveShaderProgram  (const int);

  IRENDER_API int   GetUniformIndex         (const int, const char*);

              template <typename T, size_t Y, size_t X>
              void  SetUniformValue                   (const int, T*) {}
              template <>
  IRENDER_API void  SetUniformValue<float, 1, 1>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 1, 2>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 1, 3>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 1, 4>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 2, 2>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 2, 3>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 2, 4>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 3, 2>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 3, 3>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 3, 4>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 4, 2>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 4, 3>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<float, 4, 4>      (const int, float*);
              template <>
  IRENDER_API void  SetUniformValue<int, 1, 1>        (const int, int*);
              template <>
  IRENDER_API void  SetUniformValue<int, 1, 2>        (const int, int*);
              template <>
  IRENDER_API void  SetUniformValue<int, 1, 3>        (const int, int*);
              template <>
  IRENDER_API void  SetUniformValue<int, 1, 4>        (const int, int*);
              template <>
  IRENDER_API void  SetUniformValue<unsigned, 1, 1>   (const int, unsigned*);
              template <>
  IRENDER_API void  SetUniformValue<unsigned, 1, 2>   (const int, unsigned*);
              template <>
  IRENDER_API void  SetUniformValue<unsigned, 1, 3>   (const int, unsigned*);
              template <>
  IRENDER_API void  SetUniformValue<unsigned, 1, 4>   (const int, unsigned*);


}