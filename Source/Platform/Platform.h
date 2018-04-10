#ifdef _WIN32
#define PLATFORM_API __declspec(dllexport)
#else
#define PLATFORM_API 
#endif

#include "enums.h"

namespace Platform {

  /// <summary>
  /// Checks for the existance of a window.
  /// </summary>
  /// <param name = "idx">The index of the window being validated.</param>
  PLATFORM_API  bool              ValidateWindow    (const int);

  /// <summary>
  /// Gets the raw pointer to the platform's window context.
  /// </summary>
  /// <param name = "idx">The index of the window to collect.</param>
  PLATFORM_API  void* const       WindowContext     (const int);

  /// <summary>
  /// Creates a new window to be displayed, positioned using the provided parameters.
  /// </summary>
  /// <param name = "idx">The pointer to an integer that will hold the index of the generated window.</param>
  /// <param name = "left">The inital left position of the window.</param>
  /// <param name = "top">The inital top position of the window.</param>
  /// <param name = "width">The initial width of the window.</param>
  /// <param name = "height">The initial height of the window.</param>
  /// <param name = "name">The displayed name of the window.</param>
  PLATFORM_API  void              CreateWindow      (int* const, unsigned int, unsigned int, unsigned int, unsigned int, const char* = "New Window");

  /// <summary>
  /// Closes the specified window.
  /// </summary>
  /// <param name = "idx">The index of the window to be closed.</param>
  PLATFORM_API  void              CloseWindow       (int);

  /// <summary>
  /// Repositions the specified window to the provided coordinates.
  /// </summary>
  /// <param name = "idx">The index of the window being repositioned.</param>
  /// <param name = "left">The new left coordinate of the window.</param>
  /// <param name = "top">The new top coordinate of the window.</param>
  PLATFORM_API  void              PositionWindow    (int, int, int);

  /// <summary>
  /// Resizes the specified window to the provided size.
  /// </summary>
  /// <param name = "idx">The index of the window being resized.</param>
  /// <param name = "width">The new width of the window.</param>
  /// <param name = "height">The new height of the window.</param>
  PLATFORM_API  void              ResizeWindow      (int, unsigned int, unsigned int);

  /// <summary>
  /// Brings the specified window to the top of the stack.
  /// </summary>
  /// <param name = "idx">The index of the window being brought forward.</param>
  PLATFORM_API  void              RaiseWindow       (int);

  /// <summary>
  /// Send the specified window to the bottom of the stack.
  /// </summary>
  /// <param name = "idx">The index of the window being sent backward.</param>
  PLATFORM_API  void              LowerWindow       (int);

  /// <summary>
  /// </summary>
  /// <param name = "idx"></param>
  /// <param name = "x"></param>
  /// <param name = "y"></param>
  PLATFORM_API  void              SimulateCursor    (int, const int, const int);

  /// <summary>
  /// Simulates a button press event.
  /// </summary>
  /// <param name = "idx">The index of the window to simulate the event on.</param>
  /// <param name = "button">The index of the button being simulated.</param>
  /// <param name = "mask">The desired modifier mask to accompany the simlation.</param>
  /// <param name = "release">Simulates a release event.</param>
  PLATFORM_API  void              SimulateButton    (int, const System::ButtonCode, const unsigned int = 0, bool = false);

  /// <summary>
  /// Simulates a key press event.
  /// </summary>
  /// <param name = "idx">The index of the window to simulate the event on.</param>
  /// <param name = "key">The index of the key being simulated.</param>
  /// <param name = "mask">The desired modifier mask to accompan the simulation.</param>
  /// <param name = "release">Simulates a release event.</param>
  PLATFORM_API  void              SimulateKeyboard  (int, const System::KeyCode, const unsigned int = 0, bool = false);

  /// <summary>
  /// A namespace used for managing platform related events.
  /// </summary>
  namespace Event {

    /// <summary>
    /// Checks for pending platform event messages that are yet to be processed.
    /// </summary>
    PLATFORM_API  void            Check             ();

    /// <summary>
    /// Base class used for receiving platform related events.
    /// </summary>
    struct Listener {
      PLATFORM_API                Listener          ();
      PLATFORM_API  virtual       ~Listener         ();

      PLATFORM_API  virtual void  WindowClosed      (const int) {}
      PLATFORM_API  virtual void  WindowResized     (const int, const int, const int, const unsigned int, const unsigned int) {}
      PLATFORM_API  virtual void  WindowFocusChange (const int, const bool) {}

      PLATFORM_API  virtual void  CursorMove        (const int, const int) {}
      PLATFORM_API  virtual void  ButtonPressed     (const System::ButtonCode, const unsigned int) {}
      PLATFORM_API  virtual void  ButtonReleased    (const System::ButtonCode, const unsigned int) {}

      PLATFORM_API  virtual void  CharacterPressed  (const char) {}
      PLATFORM_API  virtual void  KeyboardPressed   (const System::KeyCode, const unsigned int) {}
      PLATFORM_API  virtual void  KeyboardReleased  (const System::KeyCode, const unsigned int) {}
    };
  };
}