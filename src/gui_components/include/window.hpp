#pragma once

#ifdef _WIN32
#include "../../platform/windows/include/win_window.hpp"
#include "../../platform/windows/include/win_opengl.hpp"
#elif __linux__
#include "../../platform/linux/include/linux_window.hpp"
#include "../../platform/linux/include/linux_opengl.hpp"
#endif

class OSWindow
{
private:
#ifdef _WIN32
  Windows_Window* window;
#elif __linux__
  Linux_Window *win;
#endif
  unsigned int shaderProgram;
  unsigned int vao;
public:
  OSWindow(unsigned int width, unsigned int height, std::string title);
  void run();
};
