#pragma once

#ifdef _WIN32
#define IRENDER_API __declspec(dllexport)
#else
#define IRENDER_API
#endif

#include "OpenGL/enums.h"