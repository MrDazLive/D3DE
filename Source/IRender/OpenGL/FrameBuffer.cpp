#include "../FrameBuffer.h"

namespace IRender {

  int CreateFrameBuffer() {
    GLuint index{ 0 };
    glGenFramebuffers(1, &index);
    return (int)index;
  }

  void DeleteFrameBuffer(const int index) {
    glDeleteFramebuffers(1, (GLuint*)&index);
  }

  void SetActiveFrameBuffer(const int index, const FrameBufferDescription* description) {
    Access access = description ? description->access : Access::READ_WRITE;
    switch (access) {
    case Access::READ:
      glBindFramebuffer(GL_READ_FRAMEBUFFER, (GLuint)index);
      if(description)
        glReadBuffer((GLenum)description->readBuffer);
      break;
    case Access::WRITE:
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, (GLuint)index);
      if (description) {
        if (description->writeCount && description->writeBuffer)
          glDrawBuffers((GLsizei)description->writeCount, (GLenum*)description->writeBuffer);
        else
          glDrawBuffer(GL_NONE);
      }
      break;
    case Access::READ_WRITE:
      glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)index);
      if (description) {
        glReadBuffer((GLenum)description->readBuffer);
        if (description->writeCount && description->writeBuffer)
          glDrawBuffers((GLsizei)description->writeCount, (GLenum*)description->writeBuffer);
        else
          glDrawBuffer(GL_NONE);
      }
      break;
    }
  }

  void BindFrameBufferTexture(const int tIndex, const unsigned int attachment) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)attachment, GL_TEXTURE_RECTANGLE, tIndex, 0);
  }

  void BlitFrameBuffer(const int width, const int height, const unsigned int mask) {
    BlitFrameBuffer(0, 0, width, height, 0, 0, width, height, mask);
  }

  void BlitFrameBuffer(const int sWidth, const int sHeight, const int tWidth, const int tHeight, const unsigned int mask) {
    BlitFrameBuffer(0, 0, sWidth, sHeight, 0, 0, tWidth, tHeight, mask);
  }

  void BlitFrameBuffer(const int sX, const int sY, const int sWidth, const int sHeight, const int tX, const int tY, const int tWidth, const int tHeight, const unsigned int mask) {
    glBlitFramebuffer(sX, sY, sWidth, sHeight, tX, tY, tWidth, tHeight, (GLbitfield)mask, (mask & (BufferBit::DEPTH | BufferBit::STENCIL)) ? GL_NEAREST : GL_LINEAR);
  }

}