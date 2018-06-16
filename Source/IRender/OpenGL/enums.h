#pragma once

#include <glad/glad.h>

#include <cstdint>

namespace IRender {

  enum BufferBit {
    COLOUR      = GL_COLOR_BUFFER_BIT,
    DEPTH       = GL_DEPTH_BUFFER_BIT,
    STENCIL     = GL_STENCIL_BUFFER_BIT
  };

  enum struct Face {
    FRONT       = GL_FRONT,
    BACK        = GL_BACK,
    BOTH        = GL_FRONT_AND_BACK
  };
  
  enum struct DrawMode {
    POINTS      = GL_POINTS,
    LINES       = GL_LINES,
    TRIANGLES   = GL_TRIANGLES,
    QUADS       = GL_QUADS
  };

  enum struct Attachment {
    NONE        = GL_NONE,
    COLOUR      = GL_COLOR_ATTACHMENT0,
    DEPTH       = GL_DEPTH_ATTACHMENT,
    STENCIL     = GL_STENCIL_ATTACHMENT
  };

  enum struct Access : uint8_t {
    NONE        = 0,
    READ        = (1 << 0),
    WRITE       = (1 << 1),
    READ_WRITE  = READ | WRITE
  };

}