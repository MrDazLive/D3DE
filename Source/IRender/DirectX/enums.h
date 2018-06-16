#pragma once

namespace IRender {

  enum BufferBit {
    COLOUR      = 1 << 0,
    DEPTH       = 1 << 1,
    STENCIL     = 1 << 2
  };

  enum Face {
    FRONT       ,//= GL_FRONT,
    BACK        ,//= GL_BACK,
    BOTH        ,//= GL_FRONT_AND_BACK
  };
  
  enum DrawMode {
    POINTS      ,//= GL_POINTS,
    LINES       ,//= GL_LINES,
    TRIANGLES   ,//= GL_TRIANGLES,
    QUADS       ,//= GL_QUADS
  };

}