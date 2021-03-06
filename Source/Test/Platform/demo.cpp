#include "declerations.h"

#include <Core/Log.h>

#ifdef _WIN32
#include <Windows.h>
#define wait Sleep(200)
#undef CreateWindow
#else
#include <unistd.h>
#define wait usleep(200000)
#endif


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

  void  ButtonPressed     (const System::ButtonCode b, const unsigned int f) override {
    LOG->PrintMessage(String("Button Press: %i", (int)b));
  }

  void  ButtonReleased    (const System::ButtonCode b, const unsigned int f) override {
    LOG->PrintMessage(String("Button Release: %i", (int)b));
  }

  void  CharacterPressed   (const char c) override {
    LOG->PrintMessage(String("Character Press: '%c'", c));
  }

  void  KeyboardPressed   (const System::KeyCode k, const unsigned int f) override {
    LOG->PrintMessage(String("Key Press: '%c'(%i), Mask: %i", (char)k, (int)k, f));
  }

  void  KeyboardReleased  (const System::KeyCode k, const unsigned int f) override {
    LOG->PrintMessage(String("Key Release: '%c'(%i), Mask: %i", (char)k, (int)k, f));
  }
};


namespace Platform_Test {
  int DemoMode() {
    Listener listener;
    Platform::CreateWindow(&displayIndex, 0, 0, 100, 100, "Test-Platform (Demo Mode)");
    while(Platform::ValidateWindow(displayIndex)) {
      Platform::Event::Check();
    }
    return 0;
  }

   void Flush() {
     wait;
     Platform::Event::Check();
  }
}