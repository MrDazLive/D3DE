#ifdef _WIN32

#include "context.win.h"

namespace Platform {

  static void simulateModMask(const unsigned int mask, bool release) {
    unsigned int mask_ = mask & ~GetModMask();
    auto flags = release ? KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP : KEYEVENTF_EXTENDEDKEY;

    if (mask & System::ModMask::SHIFT)      keybd_event(VK_SHIFT,   0, flags, 0);
    if (mask & System::ModMask::CTRL)       keybd_event(VK_CONTROL, 0, flags, 0);
    if (mask & System::ModMask::ALT)        keybd_event(VK_MENU,    0, flags, 0);
    if (mask & System::ModMask::WIN)        keybd_event(VK_LWIN,    0, flags, 0);

    if (mask & System::ModMask::CAPS_LOCK)  keybd_event(VK_CAPITAL, 0, flags, 0);
    if (mask & System::ModMask::SCRL_LOCK)  keybd_event(VK_SCROLL,  0, flags, 0);
    if (mask & System::ModMask::NUM_LOCK)   keybd_event(VK_NUMLOCK, 0, flags, 0);
  }

  void SimulateCursor(int idx, const int x, const int y) {
    POINT p{ x, y };
    ClientToScreen(*GetContext(idx), &p);
    SetCursorPos(p.x, p.y);
  }

  void SimulateButton(int idx, const System::ButtonCode button, const unsigned int mask, bool release) {
    DWORD dwFlags = 0;
    switch (button) {
    case System::ButtonCode::LEFT_MOUSE:
      dwFlags = release ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_LEFTDOWN;
      break;
    case System::ButtonCode::MIDDLE_MOUSE:
      dwFlags = release ? MOUSEEVENTF_MIDDLEUP : MOUSEEVENTF_MIDDLEDOWN;
      break;
    case System::ButtonCode::RIGHT_MOUSE:
      dwFlags = release ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_RIGHTDOWN;
      break;
    }
    simulateModMask(mask, false);
    mouse_event(dwFlags, 0, 0, XBUTTON1, 0);
    simulateModMask(mask, true);
  }

  void SimulateKeyboard(int idx, const System::KeyCode key, const unsigned int mask, bool release) {
    simulateModMask(mask, false);
    keybd_event(key, 0, release ? KEYEVENTF_KEYUP : 0, 0);
    simulateModMask(mask, true);
  }

}

#endif