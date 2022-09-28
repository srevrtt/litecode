#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/frame.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");

  // create two test frames
  FrameComponent* frame1 = new FrameComponent(15, 60, 50, 50, 110, 110, 110);
  FrameComponent* frame2 = new FrameComponent(65, 60, 50, 50, 90, 90, 90);
  FrameComponent* frame3 = new FrameComponent(115, 60, 50, 50, 70, 70, 70);

  window->run();
  return 0;
}
