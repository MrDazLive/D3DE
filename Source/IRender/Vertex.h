#pragma once

#include "defines.h"

namespace IRender {

  IRENDER_API int   CreateVertexArray       ();

  IRENDER_API void  DeleteVertexArray       (const int);
  
  IRENDER_API void  SetActiveVertexArray    (const int);

              template <typename T>
              void  AddVertexAttribute                (const unsigned int, const size_t, const size_t, const size_t) {}
              template <>
  IRENDER_API void  AddVertexAttribute<int>           (const unsigned int, const size_t, const size_t, const size_t);
              template <>
  IRENDER_API void  AddVertexAttribute<unsigned int>  (const unsigned int, const size_t, const size_t, const size_t);
              template <>
  IRENDER_API void  AddVertexAttribute<float>         (const unsigned int, const size_t, const size_t, const size_t);
              template <>
  IRENDER_API void  AddVertexAttribute<double>        (const unsigned int, const size_t, const size_t, const size_t);

}