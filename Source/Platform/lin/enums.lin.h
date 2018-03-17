#ifdef __linux__

#include <X11/keysym.h>

namespace System {

  enum ButtonCode {
    LEFT_MOUSE      = 1,
    MIDDLE_MOUSE    = 2,
    RIGHT_MOUSE     = 3
  };

  enum KeyCode {
    NUM_0       = XK_0,
    NUM_1       = XK_1,
    NUM_2       = XK_2,
    NUM_3       = XK_3,
    NUM_4       = XK_4,
    
    NUM_5       = XK_5,
    NUM_6       = XK_6,
    NUM_7       = XK_7,
    NUM_8       = XK_8,
    NUM_9       = XK_9,

    A           = XK_A,
    B           = XK_B,
    C           = XK_C,
    D           = XK_D,
    E           = XK_E,

    F           = XK_F,
    G           = XK_G,
    H           = XK_H,
    I           = XK_I,
    J           = XK_J,

    K           = XK_K,
    L           = XK_L,
    M           = XK_M,
    N           = XK_N,
    O           = XK_O,

    P           = XK_P,
    Q           = XK_Q,
    R           = XK_R,
    S           = XK_S,
    T           = XK_T,

    U           = XK_U,
    V           = XK_V,
    W           = XK_W,
    X           = XK_X,
    Y           = XK_Y,

    Z           = XK_Z
  };

};

#endif