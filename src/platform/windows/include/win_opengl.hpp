#pragma once
#include <Windows.h>

#ifdef _WIN32

namespace Windows_OpenGL
{
  void init();
  void createContext(HWND hwnd);
}

#endif
