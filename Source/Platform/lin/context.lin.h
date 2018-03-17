#ifdef __linux__

#include "../misc.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <map>

#define AltMask Mod1Mask
#define NumMask Mod2Mask
#define WinMask Mod4Mask
#define WM_DELETE_WINDOW "WM_DELETE_WINDOW"

struct DisplayContext {
  Display* const display;
  Window window;
};

std::map<int, DisplayContext>& ContextMap();
DisplayContext* const GetContext(int);

#endif