#pragma once

#ifdef __linux__

#include <string>
#include <gtk/gtk.h>

class Linux_Window {
public:
  Linux_Window(unsigned int width, unsigned int height, std::string title);
};

#endif
