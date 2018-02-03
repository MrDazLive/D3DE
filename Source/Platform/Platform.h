namespace Platform {
  bool              ValidateWindow    (int);

  void              CreateWindow      (int* const, unsigned int, unsigned int, unsigned int, unsigned int);
  void              CloseWindow       (int);

  void              PositionWindow    (int, int, int);
  void              ResizeWindow      (int, unsigned int, unsigned int);

  void              RaiseWindow       (int);
  void              LowerWindow       (int);

  void              SimulateCursor    (int, const int, const int);
  void              SimulateButton    (int, const unsigned int, const unsigned int, bool = false);
  void              SimulateKeyboard  (int, const unsigned int, const unsigned int, bool = false);

  namespace Event {
    void            Check             ();

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