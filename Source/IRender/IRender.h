#ifdef _WIN32
#define IRENDER_API __declspec(dllexport)
#else
#define IRENDER_API
#endif

#include "OpenGL/enums.h"

namespace IRender {

  IRENDER_API bool  Initialise              ();

  /// <summary>
  /// Produces a rendering context and connects it to the provided window context.
  /// </summary>
  /// <param name = "idx">The index of the window being validated.</param>
  /// <param name = "ctx">The pointer to the platform's display context.</param>
  IRENDER_API void  CreateContext           (const int, void* const);
  
  IRENDER_API void  SwapBuffer              (const int, void* const);

  IRENDER_API void  ClearBuffer             (const unsigned int);

  IRENDER_API void  SetClearColour          (const float&, const float&, const float&, const float&);

  IRENDER_API void  EnableDepthTest         ();

  IRENDER_API int   CreateArrayBuffer       ();

  IRENDER_API int   CreateElementBuffer     ();

  IRENDER_API int   CreateUniformBuffer     ();

  IRENDER_API int   CreateVertexArray       ();

  IRENDER_API int   CreateFragmentShader    (const char**, const size_t);

  IRENDER_API int   CreateVertexShader      (const char**, const size_t);

  IRENDER_API int   CreateShaderProgram     (const int*, const size_t);

  IRENDER_API void  SetActiveArrayBuffer    (const int);

  IRENDER_API void  SetActiveElementBuffer  (const int);

  IRENDER_API void  SetActiveUniformBuffer  (const int);
  
  IRENDER_API void  SetActiveVertexArray    (const int);

  IRENDER_API void  SetActiveShaderProgram  (const int);

  IRENDER_API void  SetArrayBufferData      (const void*, const size_t);

  IRENDER_API void  SetElementBufferData     (const void*, const size_t);

  IRENDER_API void  SetUniformBufferData     (const void*, const size_t);

  IRENDER_API void  DeleteArrayBuffer       (const int);

  IRENDER_API void  DeleteElementBuffer     (const int);

  IRENDER_API void  DeleteUniformBuffer     (const int);

  IRENDER_API void  DeleteVertexArray       (const int);

  IRENDER_API void  DeleteShaderProgram     (const int);

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