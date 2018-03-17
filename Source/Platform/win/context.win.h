#ifdef _WIN32

#include "../misc.h"

#include <Windows.h>
#include <map>

#define CREATE_WINDOW CreateWindow
#undef CreateWindow

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

using DisplayContext = HWND;

std::map<int, DisplayContext>& ContextMap();
DisplayContext* const GetContext(int);
int GetContext(const DisplayContext&);
int GetModMask();

#endif