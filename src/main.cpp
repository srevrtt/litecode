#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/frame.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");

  // create two test frames
  FrameComponent* frame = new FrameComponent(10, 10, 60, 60, 255, 0, 255);
  FrameComponent* frame2 = new FrameComponent(80, 10, 60, 60, 0, 255, 0);

  window->run();
  return 0;
}
