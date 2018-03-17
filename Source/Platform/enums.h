#ifdef _WIN32
#include "win/enums.win.h"
#else
#include "lin/enums.lin.h"
#endif

namespace System {
  
  /// <summary>
  /// Collection of keys to identify button events.
  /// </summary>
  enum ButtonCode;

  /// <summary>
  /// Collection of keys to identify keyboard events.
  /// </summary>
  enum KeyCode;

  /// <summary>
  /// Mask of indicies to identify toggled modifier states.
  /// </summary>
  enum ModMask {
    SHIFT       = 1 << 0,
    CTRL        = 1 << 1,
    ALT         = 1 << 2,
    WIN         = 1 << 3,

    CAPS_LOCK   = 1 << 4,
    SCRL_LOCK   = 1 << 5,
    NUM_LOCK    = 1 << 6
  };

}