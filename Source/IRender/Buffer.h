#pragma once

#include "defines.h"

namespace IRender {

  IRENDER_API int   CreateArrayBuffer       ();

  IRENDER_API void  DeleteArrayBuffer       (const int);

  IRENDER_API void  SetActiveArrayBuffer    (const int);

  IRENDER_API void  SetArrayBufferData      (const void*, const size_t);

  IRENDER_API int   CreateElementBuffer     ();

  IRENDER_API void  DeleteElementBuffer     (const int);

  IRENDER_API void  SetActiveElementBuffer  (const int);

  IRENDER_API void  SetElementBufferData    (const void*, const size_t);

  IRENDER_API int   CreateUniformBuffer     ();

  IRENDER_API void  DeleteUniformBuffer     (const int);

  IRENDER_API void  SetActiveUniformBuffer  (const int);

  IRENDER_API void  SetUniformBufferData    (const void*, const size_t);

}