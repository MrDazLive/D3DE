#pragma once

#include "defines.h"

namespace IRender {

  struct TextureFormatDescription {
    bool          normalised      { false };
    BufferBit     targetBuffer    { BufferBit::COLOUR };
    unsigned int  componentCount  { 4 };
  };

  IRENDER_API int   CreateTextureBuffer       (bool = false);

  IRENDER_API void  DeleteTextureBuffer       (const int);

  IRENDER_API void  SetActiveTextureBuffer    (const int);

  IRENDER_API void  FormatTextureBuffer       (const size_t, const size_t, const TextureFormatDescription&, const void* = nullptr);

}