#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>

namespace IRender {

  enum BufferBit {
    COLOUR  = GL_COLOR_BUFFER_BIT,
    DEPTH   = GL_DEPTH_BUFFER_BIT,
    STENCIL = GL_STENCIL_BUFFER_BIT
  };

}