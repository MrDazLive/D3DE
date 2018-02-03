namespace Platform {

  /// <summary>
  /// Checks for the existance of a window.
  /// </summary>
  /// <param name = "idx">The index of the window being validated.</param>
  bool              ValidateWindow    (int);

  /// <summary>
  /// Creates a new window to be displayed, positioned using the provided parameters.
  /// </summary>
  /// <param name = "idx">The pointer to an integer that will hold the index of the generated window.</param>
  /// <param name = "left">The inital left position of the window.</param>
  /// <param name = "top">The inital top position of the window.</param>
  /// <param name = "width">The initial width of the window.</param>
  /// <param name = "height">The initial height of the window.</param>
  void              CreateWindow      (int* const, unsigned int, unsigned int, unsigned int, unsigned int);

  /// <summary>
  /// Closes the specified window.
  /// </summary>
  /// <param name = "idx">The index of the window to be closed.</param>
  void              CloseWindow       (int);

  /// <summary>
  /// Repositions the specified window to the provided coordinates.
  /// </summary>
  /// <param name = "idx">The index of the window being repositioned.</param>
  /// <param name = "left">The new left coordinate of the window.</param>
  /// <param name = "top">The new top coordinate of the window.</param>
  void              PositionWindow    (int, int, int);

  /// <summary>
  /// Resizes the specified window to the provided size.
  /// </summary>
  /// <param name = "idx">The index of the window being resized.</param>
  /// <param name = "width">The new width of the window.</param>
  /// <param name = "height">The new height of the window.</param>
  void              ResizeWindow      (int, unsigned int, unsigned int);

  /// <summary>
  /// Brings the specified window to the top of the stack.
  /// </summary>
  /// <param name = "idx">The index of the window being brought forward.</param>
  void              RaiseWindow       (int);

  /// <summary>
  /// Send the specified window to the bottom of the stack.
  /// </summary>
  /// <param name = "idx">The index of the window being sent backward.</param>
  void              LowerWindow       (int);

  /// <summary>
  /// </summary>
  /// <param name = "idx"></param>
  /// <param name = "x"></param>
  /// <param name = "y"></param>
  void              SimulateCursor    (int, const int, const int);

  /// <summary>
  /// Simulates a button press event.
  /// </summary>
  /// <param name = "idx">The index of the window to simulate the event on.</param>
  /// <param name = "button">The index of the button being simulated.</param>
  /// <param name = "mask">The desired modifier mask to accompany the simlation.</param>
  /// <param name = "release">Simulates a release event.</param>
  void              SimulateButton    (int, const unsigned int, const unsigned int = 0, bool = false);

  /// <summary>
  /// Simulates a key press event.
  /// </summary>
  /// <param name = "idx">The index of the window to simulate the event on.</param>
  /// <param name = "key">The index of the key being simulated.</param>
  /// <param name = "mask">The desired modifier mask to accompan the simulation.</param>
  /// <param name = "release">Simulates a release event.</param>
  void              SimulateKeyboard  (int, const unsigned int, const unsigned int = 0, bool = false);

  /// <summary>
  /// A namespace used for managing platform related events.
  /// </summary>
  namespace Event {

    /// <summary>
    /// Checks for pending platform event messages that are yet to be processed.
    /// </summary>
    void            Check             ();

    /// <summary>
    /// Base class used for receiving platform related events.
    /// </summary>
    struct Listener {
                    Listener          ();
      virtual       ~Listener         ();

      virtual void  WindowClosed      (const int) {}
      virtual void  WindowResized     (const int, const int, const int, const unsigned int, const unsigned int) {}
      virtual void  WindowFocusChange (const int, const bool) {}

      virtual void  CursorMove        (const int, const int) {}
      virtual void  ButtonPressed     (const unsigned int, const unsigned int) {}
      virtual void  ButtonReleased    (const unsigned int, const unsigned int) {}

      virtual void  KeyboardPressed   (const unsigned int, const unsigned int) {}
      virtual void  KeyboardReleased  (const unsigned int, const unsigned int) {}
    };
  };
}