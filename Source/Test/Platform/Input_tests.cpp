#include "declerations.h"

class InputEvent_Dumby : public Platform::Event::Listener {
public:      
  void  CursorMove        (const int x, const int y) override {
    this->x = x; this->y = y;
  }

  void  ButtonPressed     (const System::ButtonCode b, const unsigned int f) override {
    button = (int)b; pressed = true;
  }

  void  ButtonReleased    (const System::ButtonCode b, const unsigned int f) override {
    button = (int)b; released = true;
  }
  
  void  CharacterPressed  (const char c) override {
    character = c;
  }

  void  KeyboardPressed   (const System::KeyCode k, const unsigned int f) override {
    key = (int)k; pressed = true;
  }

  void  KeyboardReleased  (const System::KeyCode k, const unsigned int f) override {
    key = (int)k; released = true;
  }

  int   index             { -1 };
  int   x                 { -1 };
  int   y                 { -1 };
  int   button            { -1 };
  int   key               { -1 };
  char  character         { ' ' };
  bool  pressed           { false };
  bool  released          { false };
} input_dumby;

namespace Platform_Test {
  void Input::Reset() {
    Platform::CloseWindow(input_dumby.index);
    input_dumby = InputEvent_Dumby();
    Platform::CreateWindow(&input_dumby.index, 0, 0, 300, 200, "Test-Platform (Inputs)");
    Platform::RaiseWindow(input_dumby.index);
    Flush();
  }

  void Input::Examine() {
    TestCase([]() {
      Platform::SimulateCursor(input_dumby.index, 160, 120);
      Flush();
      return input_dumby.x == 160 && input_dumby.y == 120;
    }, "Event::Listener::CursorMove()");

    TestCase([]() {
      Platform::SimulateButton(input_dumby.index, System::ButtonCode::LEFT_MOUSE, 0);
      Flush();
      return input_dumby.pressed && input_dumby.button == System::ButtonCode::LEFT_MOUSE;
    }, "Event::Listener::ButtonPressed()");

    TestCase([]() {
      Platform::SimulateButton(input_dumby.index, System::ButtonCode::RIGHT_MOUSE, 0, true);
      Flush();
      return input_dumby.released && input_dumby.button == System::ButtonCode::RIGHT_MOUSE;
    }, "Event::Listener::ButtonReleased()");

    TestCase([]() {
      Platform::SimulateKeyboard(input_dumby.index, System::KeyCode::A, System::ModMask::SHIFT);
      Flush();
      return input_dumby.character == 'A';
    }, "Event::Listener::CharacterPressed()");

    TestCase([]() {
      Platform::SimulateKeyboard(input_dumby.index, System::KeyCode::B, 0);
      Flush();
      return input_dumby.pressed && input_dumby.key == System::KeyCode::B;
    }, "Event::Listener::KeyboardPressed()");

    TestCase([]() {
      Platform::SimulateKeyboard(input_dumby.index, System::KeyCode::C, 0, true);
      Flush();
      return input_dumby.released && input_dumby.key == System::KeyCode::C;
    }, "Event::Listener::KeyboardReleased()");
  }
}