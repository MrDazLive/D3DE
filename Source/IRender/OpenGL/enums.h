#pragma once

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

namespace IRender {

  enum BufferBit {
    COLOUR      = GL_COLOR_BUFFER_BIT,
    DEPTH       = GL_DEPTH_BUFFER_BIT,
    STENCIL     = GL_STENCIL_BUFFER_BIT
  };

  enum Face {
    FRONT       = GL_FRONT,
    BACK        = GL_BACK,
    BOTH        = GL_FRONT_AND_BACK
  };
  
  enum DrawMode {
    POINTS      = GL_POINTS,
    LINES       = GL_LINES,
    TRIANGLES   = GL_TRIANGLES,
    QUADS       = GL_QUADS
  };

}