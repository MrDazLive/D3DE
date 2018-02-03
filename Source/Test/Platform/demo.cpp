#include "declerations.h"

#include <Core/Log.h>

int displayIndex { -1 };

using namespace DTU;

class Listener : public Platform::Event::Listener {
  void  WindowClosed      (const int i) override {
    LOG->PrintMessage("Close Window");
    Platform::CloseWindow(i);
  }

  void  WindowResized     (const int i, const int x, const int y, const unsigned int w, const unsigned int h) override {
    LOG->PrintMessage(String("Window Resize: %i, %i, %i, %i", x, y, w, h));
  }

  void  WindowFocusChange (const int i, const bool f) override {
    LOG->PrintMessage(String("Window Focus Change: %s", f ? "true" : "false"));
  }

  void  CursorMove        (const int x, const int y) override {
    LOG->PrintMessage(String("Cursor Move: %i, %i", x, y));
  }

  void  ButtonPressed     (const unsigned int b, const unsigned int f) override {
    LOG->PrintMessage(String("Button Press: %i", b));
  }

  void  ButtonReleased    (const unsigned int b, const unsigned int f) override {
    LOG->PrintMessage(String("Button Release: %i", b));
  }

  void  KeyboardPressed   (const unsigned int k, const unsigned int f) override {
    LOG->PrintMessage(String("Key Press: %c", (char)k));
  }

  void  KeyboardReleased  (const unsigned int k, const unsigned int f) override {
    LOG->PrintMessage(String("Key Release: %c", (char)k));
  }
};


namespace Platform_Test {
  int DemoMode() {
    Listener listener;
    Platform::CreateWindow(&displayIndex, 0, 0, 100, 100);
    while(Platform::ValidateWindow(displayIndex)) {
      Platform::Event::Check();
    }
    return 0;
  }
}