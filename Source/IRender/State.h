#pragma once

#include "defines.h"

namespace IRender {

  IRENDER_API void  EnableDepthTest();

  IRENDER_API void  EnableCullFace();

  IRENDER_API void  ClearBuffer(const unsigned int);

  IRENDER_API void  SetViewport(const int, const int, const unsigned int, const unsigned int);

  IRENDER_API void  SetClearColour(const float&, const float&, const float&, const float&);

}