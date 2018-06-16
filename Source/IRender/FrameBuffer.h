#pragma once

#include "defines.h"

namespace IRender {

  struct FrameBufferDescription {
    Access      access        { Access::READ_WRITE };
    Attachment  readBuffer    { Attachment::NONE };
    const void* writeBuffer   { nullptr };
    size_t      writeCount    { 0 };
  };

  IRENDER_API int   CreateFrameBuffer       ();

  IRENDER_API void  DeleteFrameBuffer       (const int);

  IRENDER_API void  SetActiveFrameBuffer    (const int, const FrameBufferDescription*);

  IRENDER_API void  BindFrameBufferTexture  (const int, const unsigned int);

  IRENDER_API void  BlitFrameBuffer         (const int, const int, const unsigned int);

  IRENDER_API void  BlitFrameBuffer         (const int, const int, const int, const int, const unsigned int);

  IRENDER_API void  BlitFrameBuffer         (const int, const int, const int, const int, const int, const int, const int, const int, const unsigned int);

}