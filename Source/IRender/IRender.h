#include "defines.h"
#include "Buffer.h"
#include "Shader.h"
#include "State.h"
#include "Vertex.h"

namespace IRender {

  IRENDER_API bool  Initialise              ();

  /// <summary>
  /// Produces a rendering context and connects it to the provided window context.
  /// </summary>
  /// <param name = "idx">The index of the window being validated.</param>
  /// <param name = "ctx">The pointer to the platform's display context.</param>
  IRENDER_API void  CreateContext           (const int, void* const);
  
  IRENDER_API void  SwapBuffer              (const int, void* const);

  IRENDER_API void  DrawElements            (DrawMode, const size_t, const size_t);

  IRENDER_API void  DrawElementsInstanced   (DrawMode, const size_t, const size_t, const size_t);

}