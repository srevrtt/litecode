#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/frame.hpp"
#include "gui_components/include/image.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");

  // create two test frames
  Image* image = new Image(10, 60, 50, 50, "src/resources/images/test.png");
  Image* image2 = new Image(70, 60, 50, 50, "src/resources/images/test-2.png");

  window->run();
  return 0;
}
