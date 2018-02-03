#include "declerations.h"

class InputEvent_Dumby : public Platform::Event::Listener {
public:      
  void  CursorMove        (const int x, const int y) override {
    this->x = x; this->y = y;
  }

  void  ButtonPressed     (const unsigned int b, const unsigned int f) override {
    button = b; pressed = true;
  }

  void  ButtonReleased    (const unsigned int b, const unsigned int f) override {
    button = b; released = true;
  }

  void  KeyboardPressed   (const unsigned int k, const unsigned int f) override {
    key = (char)k; pressed = true;
  }

  void  KeyboardReleased  (const unsigned int k, const unsigned int f) override {
    key = (char)k; released = true;
  }

  int   index             { -1 };
  int   x                 { -1 };
  int   y                 { -1 };
  int   button            { -1 };
  char  key               { ' ' };
  bool  pressed           { false };
  bool  released          { false };
} input_dumby;

namespace Platform_Test {
  void Input::Reset() {
    Platform::CloseWindow(input_dumby.index);
    input_dumby = InputEvent_Dumby();
    Platform::CreateWindow(&input_dumby.index, 0, 0, 100, 100);
    Flush();
  }

  void Input::Examine() {
    TestCase([]() {
      Platform::SimulateCursor(input_dumby.index, 200, 300);
      Flush();
      return input_dumby.x == 200 && input_dumby.y == 300;
    }, "Event::Listener::CursorMove()");

    TestCase([]() {
      Platform::SimulateKeyboard(input_dumby.index, 'a', 0);
      Flush();
      return input_dumby.pressed && input_dumby.key == 'a';
    }, "Event::Listener::KeyboardPressed()");

    TestCase([]() {
      Platform::SimulateKeyboard(input_dumby.index, 'b', 0, true);
      Flush();
      return input_dumby.released && input_dumby.key == 'b';
    }, "Event::Listener::KeyboardReleased()");

    TestCase([]() {
      Platform::SimulateButton(input_dumby.index, 1, 0);
      Flush();
      return input_dumby.pressed && input_dumby.button == 1;
    }, "Event::Listener::ButtonPressed()");

    TestCase([]() {
      Platform::SimulateButton(input_dumby.index, 2, 0, true);
      Flush();
      return input_dumby.released && input_dumby.button == 2;
    }, "Event::Listener::ButtonReleased()");
  }
}