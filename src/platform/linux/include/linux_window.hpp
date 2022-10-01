#pragma once

#ifdef __linux__

#include <string>
#include <gtk/gtk.h>
#include <X11/Xlib.h>

class Linux_Window {
public:
  Linux_Window(unsigned int width, unsigned int height, std::string title);

  static Display *getDisplay();
  static Window getWindow();
};

#endif
