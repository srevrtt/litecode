#pragma once

#ifdef _WIN32
#include "../../platform/windows/include/win_window.hpp"
#endif

class Window
{
private:
#ifdef _WIN32
  Windows_Window* window;
#endif
public:
  Window(unsigned int width, unsigned int height, std::string title);
  void run();
};
