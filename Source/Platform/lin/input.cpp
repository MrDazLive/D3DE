#ifdef __linux__

#include "context.h"

namespace Platform {

  static unsigned int convertModMask(const unsigned int mask) {
    unsigned int mask_ = 0;
    mask_ |= (mask & Event::ModifierMask::SHIFT)      ? ShiftMask   : 0;
    mask_ |= (mask & Event::ModifierMask::CTRL)       ? ControlMask : 0;
    mask_ |= (mask & Event::ModifierMask::ALT)        ? AltMask     : 0;
    mask_ |= (mask & Event::ModifierMask::WIN)        ? WinMask     : 0;
    mask_ |= (mask & Event::ModifierMask::CAPS_LOCK)  ? LockMask    : 0;
    mask_ |= (mask & Event::ModifierMask::NUM_LOCK)   ? NumMask     : 0;
    return mask_;
  }

  void SimulateCursor(int idx, const int x, const int y) {
    if(auto ctx = GetContext(idx)) {
      XMotionEvent event;
      event.display     = ctx->display;
      event.window      = ctx->window;
      event.x           = x;
      event.y           = y;
      event.type        = MotionNotify;

      XSendEvent(ctx->display, ctx->window, True, PointerMotionMask, (XEvent*)&event);
      XFlush(ctx->display);
    }
  }

  void SimulateButton(int idx, const unsigned int button, const unsigned int mask, bool release) {
    if(auto ctx = GetContext(idx)) {
      XButtonEvent event;
      event.display     = ctx->display;
      event.window      = ctx->window;
      event.button      = button;
      event.state       = convertModMask(mask);
      event.type        = release ? ButtonRelease : ButtonPress;

      XSendEvent(ctx->display, ctx->window, True, ButtonPressMask | ButtonReleaseMask, (XEvent*)&event);
      XFlush(ctx->display);
    }
  }

  void SimulateKeyboard (int idx, const unsigned int key, const unsigned int mask, bool release) {
    if(auto ctx = GetContext(idx)) 
    {
      XKeyEvent event;
      event.display     = ctx->display;
      event.window      = ctx->window;
      event.keycode     = XKeysymToKeycode(ctx->display, key);
      event.state       = convertModMask(mask);
      event.type        = release ? KeyRelease : KeyPress;

      XSendEvent(ctx->display, ctx->window, True, KeyPressMask | KeyReleaseMask, (XEvent*)&event);
      XFlush(ctx->display);
    }
  }

}

#endif