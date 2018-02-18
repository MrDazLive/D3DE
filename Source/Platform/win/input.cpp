#ifdef _WIN32

#include "context.h"

namespace Platform {

  static unsigned int convertModMask(const unsigned int mask) {
    unsigned int mask_ = 0;

    return mask_;
  }

  void SimulateCursor(int idx, const int x, const int y) {
    SendMessage(*GetContext(idx), WM_MOUSEMOVE, 0, MAKELPARAM(x, y));
  }

  void SimulateButton(int idx, const unsigned int button, const unsigned int mask, bool release) {

  }

  void SimulateKeyboard(int idx, const unsigned int key, const unsigned int mask, bool release) {
    keybd_event(key, 0, release ? KEYEVENTF_KEYUP : 0, 0);
  }

}

#endif