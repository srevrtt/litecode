#pragma once

#ifdef _WIN32
#include <Windows.h>

namespace Windows_OpenGL
{
  void init();
  void createContext(HWND hwnd);
  void render();
}

#endif
