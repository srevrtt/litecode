#pragma once

#ifdef _WIN32
#include "../../platform/windows/include/win_window.hpp"
#include "../../platform/windows/include/win_opengl.hpp"
#elif __linux__
#include "../../platform/linux/include/linux_window.hpp"
#endif

class Window
{
private:
#ifdef _WIN32
  Windows_Window* window;
#elif __linux__
  Linux_Window *window;
#endif
  unsigned int shaderProgram;
  unsigned int vao;
public:
  Window(unsigned int width, unsigned int height, std::string title);
  void run();
};
