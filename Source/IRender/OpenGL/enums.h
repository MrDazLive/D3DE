#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

namespace IRender {

  enum BufferBit {
    COLOUR  = GL_COLOR_BUFFER_BIT,
    DEPTH   = GL_DEPTH_BUFFER_BIT,
    STENCIL = GL_STENCIL_BUFFER_BIT
  };

}