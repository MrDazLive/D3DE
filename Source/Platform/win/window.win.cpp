#ifdef _WIN32

#include "context.win.h"

namespace Platform {

  bool ValidateWindow(const int idx) {
    return idx != -1 && ContextMap().find(idx) != ContextMap().end();
  }

  void* const WindowContext(const int idx) {
    auto it = ContextMap().find(idx);
    return it != ContextMap().end() ? (void*)(&it->second) : nullptr;
  }

  void CreateWindow(int* const idx, unsigned int left, unsigned int top, unsigned int width, unsigned int height, const char* name/* = "New Window"*/) {
    static auto handle = GetModuleHandle(NULL);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = handle;
    wc.lpszClassName = "D3DE Application";
    RegisterClass(&wc);

    // Create the window.
    DisplayContext ctx = CreateWindowEx(
      0,                              // Optional window styles.
      "D3DE Application",             // Window class
      name,                           // Window text
      WS_OVERLAPPEDWINDOW,            // Window style

      (int)left,  (int)top,           // Window position
      (int)width, (int)height,        // Window size

      NULL,       // Parent window    
      NULL,       // Menu
      handle,     // Instance handle
      NULL        // Additional application data
    );

    if (ctx) {
      *idx = ContextMap().empty() ? 0 : ContextMap().rbegin()->first + 1;
      ContextMap().emplace(*idx, ctx);

      ShowWindow(ctx, SW_SHOW);
    }
    else
      *idx = -1;
  }

  void CloseWindow(int idx) {
    if (auto ctx = GetContext(idx)) {
      DestroyWindow(*ctx);
      ContextMap().erase(idx);
    }
  }

  void PositionWindow(int idx, int left, int top) {
    if (auto ctx = GetContext(idx)) {
      SetWindowPos(*ctx, NULL, left, top, 0, 0, SWP_NOSIZE);
    }
  }

  void ResizeWindow(int idx, unsigned int width, unsigned int height) {
    if (auto ctx = GetContext(idx)) {
      SetWindowPos(*ctx, NULL, 0, 0, width, height, SWP_NOMOVE);
    }
  }

  void RaiseWindow(const int idx) {
    if (auto ctx = GetContext(idx)) {
      SetActiveWindow(*ctx);
      SetFocus(*ctx);
    }
  }

  void LowerWindow(const int idx) {
    if (auto ctx = GetContext(idx)) {
      SendMessage(*ctx, WM_KILLFOCUS, 0, 0);
    }
  }

}

#endif