#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");
  window->run();

  return 0;
}
