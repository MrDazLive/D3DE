#ifdef __linux__

#include "context.lin.h"

namespace Platform {

  bool ValidateWindow(const int idx) {
    return idx != -1 && ContextMap().find(idx) != ContextMap().end();
  }

  void* const WindowContext(const int idx) {
    auto it = ContextMap().find(idx);
    return it != ContextMap().end() ? (void*)(&it->second) : nullptr;
  }

  void CreateWindow(int* const idx, unsigned int left, unsigned int top, unsigned int width, unsigned int height, const char* name/* = "New Window"*/) {
    // Open a display.    
    if (DisplayContext ctx = XOpenDisplay(0)) {

      // Create the window
      XID window = XCreateWindow(ctx, DefaultRootWindow(ctx),
        left, top, width, height,
        0, 0, InputOutput, 
        nullptr, StructureNotifyMask, nullptr);

      // Name the window
      XStoreName(ctx, window, name);

      // Store the display context
      *idx = (int)window;
      ContextMap().emplace(*idx, ctx);
      
      // Register event listeners
      auto atom = XInternAtom(ctx, WM_DELETE_WINDOW, false);
      XSetWMProtocols(ctx, window, &atom, 1);
      XSelectInput(ctx, window, PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | FocusChangeMask | StructureNotifyMask);

      // Show the window
      XMapWindow(ctx, window);
      XFlush(ctx);
    }
    else {
      *idx = -1;
    }
  }

  void CloseWindow(int idx) {
    if(auto ctx = GetContext(idx)) {
      XDestroyWindow(*ctx, (XID)idx);
      XCloseDisplay(*ctx);
      ContextMap().erase(idx);
    }
  }

  void PositionWindow(int idx, int left, int top) {
    if(auto ctx = GetContext(idx)) {
      XMoveWindow(*ctx, (XID)idx, left, top);
      XFlush(*ctx);
    }
  }

  void ResizeWindow(int idx, unsigned int width, unsigned int height) {
    if(auto ctx = GetContext(idx)) {
      XResizeWindow(*ctx, (XID)idx, width, height);
      XFlush(*ctx);
    }
  }

  void RaiseWindow(const int idx) {
    if(auto ctx = GetContext(idx)) {
      XRaiseWindow(*ctx, (XID)idx);
      XFlush(*ctx);
    }
  }

  void LowerWindow(const int idx) {
    if(auto ctx = GetContext(idx)) {
      XLowerWindow(*ctx, (XID)idx);
      XFlush(*ctx);
    }
  }

}

#endif