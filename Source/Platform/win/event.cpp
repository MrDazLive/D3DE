#ifdef _WIN32

#include "context.h"

using namespace Platform;

void Event::Check() {
  MSG msg = {};
  while(!ContextMap().empty() && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

LRESULT CALLBACK WindowProc(HWND ctx, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_CLOSE:
    Platform::SignalEvent(&Platform::Event::Listener::WindowClosed, GetContext(ctx));
    return 0;
  case WM_MOVE:
  case WM_SIZE: {
    RECT rect;
    if (GetWindowRect(ctx, &rect)) {
      int left = rect.left;
      int top = rect.top;
      int width = rect.right - left;
      int height = rect.bottom - top;
      SignalEvent(&Event::Listener::WindowResized, GetContext(ctx), left, top, width, height);
    }
    return 0;
  }
  case WM_SETFOCUS:
    SignalEvent(&Event::Listener::WindowFocusChange, GetContext(ctx), true);
    return 0;
  case WM_KILLFOCUS:
    SignalEvent(&Event::Listener::WindowFocusChange, GetContext(ctx), false);
    return 0;
  case WM_MOUSEMOVE:
    SignalEvent(&Event::Listener::CursorMove, (int)LOWORD(lParam), (int)HIWORD(lParam));
    return 0;
  case WM_CHAR:
    SignalEvent(&Event::Listener::CharacterPressed, (char)wParam);
    return 0;
  case WM_SYSKEYDOWN:
  case WM_KEYDOWN:
    if(!(lParam & (1 << 30)))
      SignalEvent(&Event::Listener::KeyboardPressed, (unsigned int)wParam, 0);
    return 0;
  case WM_SYSKEYUP:
  case WM_KEYUP:
    SignalEvent(&Event::Listener::KeyboardReleased, (unsigned int)wParam, 0);
    return 0;
  case WM_LBUTTONDOWN:
    SignalEvent(&Event::Listener::ButtonPressed, 0, 0);
    return 0;
  case WM_MBUTTONDOWN:
    SignalEvent(&Event::Listener::ButtonPressed, 0, 0);
    return 0;
  case WM_RBUTTONDOWN:
    SignalEvent(&Event::Listener::ButtonPressed, 0, 0);
    return 0;

  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(ctx, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(ctx, &ps);
  }
  return 0;

  }
  return DefWindowProc(ctx, msg, wParam, lParam);
}

#endif