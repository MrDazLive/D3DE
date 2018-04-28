#include "../State.h"

namespace IRender {

  void EnableDepthTest() {
    glEnable(GL_DEPTH_TEST);
  }

  void EnableCullFace() {
    glEnable(GL_CULL_FACE);
  }

  void ClearBuffer(const unsigned int bits) {
    glClear(bits);
  }

  void SetViewport(const int x, const int y, const unsigned int width, const unsigned int height) {
    glViewport(x, y, (GLsizei)width, (GLsizei)height);
  }

  void SetClearColour(const float& red, const float& green, const float& blue, const float& alpha) {
    glClearColor(red, green, blue, alpha);
  }

}