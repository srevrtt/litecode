#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/frame.hpp"
#include "gui_components/include/flexbox.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");

  // create two test frames
  FrameComponent* frame1 = new FrameComponent(0, 0, 0, 0, 0, 154, 73);
  FrameComponent* frame2 = new FrameComponent(0, 0, 0, 0, 255, 255, 255);
  FrameComponent* frame3 = new FrameComponent(0, 0, 0, 0, 255, 121, 1);

  FlexboxComponent* flex = new FlexboxComponent();
  
  flex->increaseCapacity();
  flex->increaseCapacity();
  flex->increaseCapacity();

  flex->addFrame(frame1);
  flex->addFrame(frame2);
  flex->addFrame(frame3);

  window->run();
  return 0;
}
