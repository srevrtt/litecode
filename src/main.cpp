#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/image.hpp"

int main(int argc, char* argv[])
{
  OSWindow* window = new OSWindow(1280, 720, "Litecode v0.1.0");

  Image *img = new Image(20, 20, 200, 200, "../src/resources/images/test.png");

  window->run();
  
  return 0;
}
