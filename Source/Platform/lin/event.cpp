#ifdef __linux__

#include "context.h"

namespace Platform {

  static unsigned int convertModMask(const unsigned int mask) {
    unsigned int mask_ = 0;
    mask_ |= (mask & ShiftMask)   ? System::ModMask::SHIFT      : 0;
    mask_ |= (mask & ControlMask) ? System::ModMask::CTRL       : 0;
    mask_ |= (mask & AltMask)     ? System::ModMask::ALT        : 0;
    mask_ |= (mask & WinMask)     ? System::ModMask::WIN        : 0;
    mask_ |= (mask & LockMask)    ? System::ModMask::CAPS_LOCK  : 0;
    mask_ |= (mask & NumMask)     ? System::ModMask::NUM_LOCK   : 0;
    return mask_;
  }

  void SignalCharacterEvent(XKeyEvent& xkey) {
    if(xkey.state & (AltMask | ControlMask | WinMask))
      return;

    bool shift = (bool)(xkey.state & ShiftMask) ^ (bool)(xkey.state & LockMask);
    auto key = XLookupKeysym(&xkey, shift);
    if(XK_space <= key && key <= XK_asciitilde)
      SignalEvent(&Event::Listener::CharacterPressed, (char)key);
  }

  void Event::Check() {
    XEvent event;
    for(auto ctx : ContextMap()) {
      auto display = ctx.second.display;
      while(ValidateWindow(ctx.first) && XPending(display)) {
        XNextEvent(display, &event);
        switch(event.type) {
        case ConfigureNotify:
          SignalEvent(&Event::Listener::WindowResized, ctx.first, event.xconfigure.x, event.xconfigure.y, event.xconfigure.width, event.xconfigure.height);
          break;
        case FocusIn:
          SignalEvent(&Event::Listener::WindowFocusChange, ctx.first, true);
          break;
        case FocusOut:
          SignalEvent(&Event::Listener::WindowFocusChange, ctx.first, false);
          break;
        case KeyRelease:
          if (XEventsQueued(display, QueuedAfterReading)) {
            XEvent next;
            XPeekEvent(display, &next);
            if (next.type == KeyPress && next.xkey.time == event.xkey.time && next.xkey.keycode == event.xkey.keycode) {
              XNextEvent(display, &next);
              SignalCharacterEvent(event.xkey);
              break;
            }
          }
          SignalEvent(&Event::Listener::KeyboardReleased, (System::KeyCode)XLookupKeysym(&(event.xkey), 0), convertModMask(event.xkey.state));
          break;
        case KeyPress:
          SignalCharacterEvent(event.xkey);
          SignalEvent(&Event::Listener::KeyboardPressed, (System::KeyCode)XLookupKeysym(&(event.xkey), 0), convertModMask(event.xkey.state));
          break;
        case ButtonPress:
          SignalEvent(&Event::Listener::ButtonPressed, (System::ButtonCode)event.xbutton.button, convertModMask(event.xbutton.state));
          break;
        case ButtonRelease:
          SignalEvent(&Event::Listener::ButtonReleased, (System::ButtonCode)event.xbutton.button, convertModMask(event.xbutton.state));
          break;
        case MotionNotify:
          SignalEvent(&Event::Listener::CursorMove, event.xmotion.x, event.xmotion.y);
          break;
        case ClientMessage:
          if(event.xclient.data.l[0] == XInternAtom(display, WM_DELETE_WINDOW, true)) {
            SignalEvent(&Event::Listener::WindowClosed, ctx.first);
          }
          break;
        }
      }
    }
  }

}

#endif