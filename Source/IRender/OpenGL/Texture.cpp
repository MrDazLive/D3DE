#include "../Texture.h"

#include <map>

namespace IRender {

  static std::map<int, GLenum> s_textureTarget;

  int CreateTextureBuffer(bool normalised) {
    GLuint index{ 0 };
    glGenTextures(1, &index);
    s_textureTarget[index] = normalised ? GL_TEXTURE_RECTANGLE : GL_TEXTURE_2D;
    return (int)index;
  }

  void DeleteTextureBuffer(const int index) {
    glDeleteTextures(1, (GLuint*)&index);
    s_textureTarget.erase(index);
  }

  void SetActiveTextureBuffer(const int index) {
    glBindTexture(s_textureTarget[index], (GLuint)index);
  }

  void FormatTextureBuffer(const size_t width, const size_t height, const TextureFormatDescription& description, const void* data) {
    GLenum  target  = description.normalised ? GL_TEXTURE_RECTANGLE : GL_TEXTURE_2D;
    GLint   iFormat = 0;
    GLenum  format  = 0;
    GLenum  type    = 0;

    switch (description.targetBuffer) {
    case BufferBit::COLOUR:
      switch (description.componentCount) {
      case 1: format = GL_RED;  iFormat = GL_R16F;    break;
      case 2: format = GL_RG;   iFormat = GL_RG16F;   break;
      case 3: format = GL_RGB;  iFormat = GL_RGB16F;  break;
      case 4: format = GL_RGBA; iFormat = GL_RGBA16F; break;
      }
      type = GL_FLOAT;
      break;
    case BufferBit::DEPTH:
      format  = GL_DEPTH_COMPONENT;
      iFormat = GL_DEPTH_COMPONENT;
      type    = GL_UNSIGNED_INT;
      break;
    case BufferBit::STENCIL:
      format  = GL_DEPTH_STENCIL;
      iFormat = GL_DEPTH24_STENCIL8;
      type    = GL_UNSIGNED_INT_24_8;
      break;
    }

    glTexImage2D(target, 0, iFormat, width, height, 0, format, type, data);
  }

}