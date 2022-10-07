#pragma once

#ifdef _WIN32
#include "../../platform/windows/include/win_window.hpp"
#include "../../platform/windows/include/win_opengl.hpp"
#elif __linux__
#include "../../platform/linux/include/linux_window.hpp"
#include "../../platform/linux/include/linux_opengl.hpp"
#endif

#include <glm/glm.hpp>

class OSWindow
{
private:
#ifdef _WIN32
  Windows_Window *window;
#endif
public:
  OSWindow(unsigned int width, unsigned int height, std::string title);

#ifdef __linux__
  static gboolean updateGtk(GtkWidget *window, GdkFrameClock *clock, gpointer data);
#endif

  static void update();
  void close();
  void run();
};
