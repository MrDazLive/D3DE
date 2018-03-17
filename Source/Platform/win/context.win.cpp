#ifdef _WIN32

#include "context.win.h"

std::map<int, DisplayContext>& ContextMap() {
  static std::map<int, DisplayContext> map;
  return map;
}

DisplayContext* const GetContext(int idx) {
  auto it = ContextMap().find(idx);
  return it != ContextMap().end() ? &(it->second) : nullptr;
}

int GetContext(const DisplayContext& ctx) {
  auto map = ContextMap();
  for (auto it : map) {
    if (it.second == ctx)
      return it.first;
  }
  return -1;
}

int GetModMask() {
  int mask = 0;
  mask |= GetKeyState(VK_SHIFT)   & 0x8000 ? System::ModMask::SHIFT      : 0;
  mask |= GetKeyState(VK_CONTROL) & 0x8000 ? System::ModMask::CTRL       : 0;
  mask |= GetKeyState(VK_MENU)    & 0x8000 ? System::ModMask::ALT        : 0;
  mask |= GetKeyState(VK_LWIN)    & 0x8000 ? System::ModMask::WIN        : 0;

  mask |= GetKeyState(VK_CAPITAL) & 0x0001 ? System::ModMask::CAPS_LOCK  : 0;
  mask |= GetKeyState(VK_SCROLL)  & 0x0001 ? System::ModMask::SCRL_LOCK  : 0;
  mask |= GetKeyState(VK_NUMLOCK) & 0x0001 ? System::ModMask::NUM_LOCK   : 0;
  return mask;
}

#endif