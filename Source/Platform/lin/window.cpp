#ifdef __linux__

#include "context.h"

namespace Platform {

  bool ValidateWindow(const int idx) {
    return idx != -1 && ContextMap().find(idx) != ContextMap().end();
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

      *idx = ContextMap().empty() ? 0 : ContextMap().rbegin()->first + 1;
      ContextMap().emplace(*idx, ctx);
      
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
      ContextMap().erase(idx);
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

}

#endif