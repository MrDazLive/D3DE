#include "declerations.h"

class WindowEvent_Dumby : public Platform::Event::Listener {
public:      
  void  WindowClosed      (const int idx) override {
    if(index == idx) { closed = true; }
  }
  void  WindowResized     (const int idx, const int x, const int y, const unsigned int w, const unsigned int h) override {
    if(index == idx) { this->x = x; this->y = y; this->width = w; this->height = h; }
  }
  void  WindowFocusChange (const int idx, const bool f) override {
    if(index == idx) { inFocus = f; outFocus = !f; }
  }

  int   index             { -1 };
  bool  closed            { false };
  bool  inFocus           { false };
  bool  outFocus          { false };
  int   x                 { 0 };
  int   y                 { 0 };
  int   width             { 0 };
  int   height            { 0 };
} window_dumby;

namespace Platform_Test {
  void Window::Reset() {
    Platform::CloseWindow(window_dumby.index);
    Flush();
    window_dumby = WindowEvent_Dumby();
    Platform::CreateWindow(&window_dumby.index, 0, 0, 100, 100, "Test-Platform (Windows)");
    Flush();
  }

  void Window::Examine() {
    TestCase([]() {
      return window_dumby.index != -1 && Platform::ValidateWindow(window_dumby.index);
    }, "Platform::CreateWindow()");

    TestCase([]() {
      Platform::ResizeWindow(window_dumby.index, 200, 300);
      Flush();
      return window_dumby.width == 200 && window_dumby.height == 300;
    }, "Event::Listener::WindowResized()");

    TestCase([]() {
      Platform::ResizeWindow(window_dumby.index, 200, 300);
      Flush();
      return window_dumby.width == 200 && window_dumby.height == 300;
    }, "Event::Listener::WindowResized()");

    TestCase([]() {
      Platform::RaiseWindow(window_dumby.index);
      Flush();
      return window_dumby.inFocus;
    }, "Event::Listener::WindowGainFocus()");

    TestCase([]() {
      Platform::LowerWindow(window_dumby.index);
      Flush();
      return window_dumby.outFocus;
    }, "Event::Listener::WindowLoseFocus()");
  }
}