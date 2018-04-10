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

    A           = XK_a,
    B           = XK_b,
    C           = XK_c,
    D           = XK_d,
    E           = XK_e,

    F           = XK_f,
    G           = XK_g,
    H           = XK_h,
    I           = XK_i,
    J           = XK_j,

    K           = XK_k,
    L           = XK_l,
    M           = XK_m,
    N           = XK_n,
    O           = XK_o,

    P           = XK_p,
    Q           = XK_q,
    R           = XK_r,
    S           = XK_s,
    T           = XK_t,

    U           = XK_u,
    V           = XK_v,
    W           = XK_w,
    X           = XK_x,
    Y           = XK_y,

    Z           = XK_z
  };

};

#endif