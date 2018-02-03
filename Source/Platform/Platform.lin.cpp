#ifdef __linux__

#include "Platform.h"

#include <X11/Xlib.h>
#include <functional>
#include <map>
#include <set>

struct DisplayContext {
  Display* const display;
  Window window;
};

std::map<int, DisplayContext> contextMap;

DisplayContext* const GetContext(int idx) {
  auto it = contextMap.find(idx);
  return it != contextMap.end() ? &(it->second) : nullptr;
}

const char* WM_DELETE_WINDOW = "WM_DELETE_WINDOW";

namespace Platform {

  bool ValidateWindow(const int idx) {
    return idx != -1 && contextMap.find(idx) != contextMap.end();
  }

  void CreateWindow(int* const idx, unsigned int left, unsigned int top, unsigned int width, unsigned int height) {
    // Open a display.
    Display *d = XOpenDisplay(0);
    
    if ( d ) {
      // Create the window
      DisplayContext ctx {
        d,
        XCreateWindow(d, DefaultRootWindow(d),
          left, top, width, height,
          0, 0, 0, 
          nullptr, StructureNotifyMask, nullptr)
      };

      *idx = contextMap.empty() ? 0 : contextMap.rbegin()->first + 1;
      contextMap.emplace(*idx, ctx);
      
      auto atom = XInternAtom(d, WM_DELETE_WINDOW, false);
      XSetWMProtocols(d, ctx.window, &atom, 1);
      XSelectInput(d, ctx.window, PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | FocusChangeMask | StructureNotifyMask);

      // Show the window
      XMapWindow(ctx.display, ctx.window);
      XFlush(ctx.display);
    }
    else {
      *idx = -1;
    }
  }

  void CloseWindow(int idx) {
    if(auto ctx = GetContext(idx)) {
      XDestroyWindow(ctx->display, ctx->window);
      XCloseDisplay(ctx->display);
      contextMap.erase(idx);
    }
  }

  void PositionWindow(int idx, int left, int top) {
    if(auto ctx = GetContext(idx)) {
      XMoveWindow(ctx->display, ctx->window, left, top);
      XFlush(ctx->display);
    }
  }

  void ResizeWindow(int idx, unsigned int width, unsigned int height) {
    if(auto ctx = GetContext(idx)) {
      XResizeWindow(ctx->display, ctx->window, width, height);
      XFlush(ctx->display);
    }
  }

  void RaiseWindow(const int idx) {
    if(auto ctx = GetContext(idx)) {
      XRaiseWindow(ctx->display, ctx->window);
      XFlush(ctx->display);
    }
  }

  void LowerWindow(const int idx) {
    if(auto ctx = GetContext(idx)) {
      XLowerWindow(ctx->display, ctx->window);
      XFlush(ctx->display);
    }
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
      event.state       = mask;
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
      event.state       = mask;
      event.type        = release ? KeyRelease : KeyPress;

      XSendEvent(ctx->display, ctx->window, True, KeyPressMask | KeyReleaseMask, (XEvent*)&event);
      XFlush(ctx->display);
    }
  }

  std::set<Event::Listener*>& EventSet() {
    static std::set<Event::Listener*> set;
    return set;
  }

  Event::Listener::Listener() {
    EventSet().insert(this);
  }

  Event::Listener::~Listener() {
    EventSet().erase(this);
  }

  template <typename F, typename ... V>
  void SignalEvent(F function, V... args) {
    auto func = std::bind(function, std::placeholders::_1, args...);
    for(auto ptr : EventSet()) {
      func(ptr);
    }
  }

  void Event::Check() {
    XEvent event;
    for(auto ctx : contextMap) {
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
              break;
            }
          }
          SignalEvent(&Event::Listener::KeyboardReleased, (unsigned int)XLookupKeysym(&(event.xkey), 0), event.xkey.state);
          break;
        case KeyPress:
          SignalEvent(&Event::Listener::KeyboardPressed, (unsigned int)XLookupKeysym(&(event.xkey), 0), event.xkey.state);
          break;
        case ButtonPress:
          SignalEvent(&Event::Listener::ButtonPressed, event.xbutton.button, event.xkey.state);
          break;
        case ButtonRelease:
          SignalEvent(&Event::Listener::ButtonReleased, event.xbutton.button, event.xkey.state);
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