#include <iostream>
#include <string>

#include "include/window.hpp"

// Creates a window for the current platform
Window::Window(unsigned int width, unsigned int height, std::string title)
{
#ifdef _WIN32
  window = new Windows_Window(width, height, title);
#endif
}

// Runs the main loop for the created window
void Window::run()
{
  while (!window->isCloseRequested())
  {
    window->update();
  }

  window->close();
}
