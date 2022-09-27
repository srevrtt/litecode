#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/frame.hpp"
#include "gui_components/include/flexbox.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");

  // create two test frames
  FrameComponent* frame1 = new FrameComponent(0, 0, 0, 0, 110, 110, 110);
  FrameComponent* frame2 = new FrameComponent(0, 0, 0, 0, 90, 90, 90);

  FlexboxComponent* flex = new FlexboxComponent(FB_ALIGNMENT_HORIZONTAL);
  
  flex->increaseCapacity(2);

  flex->addFrame(frame1, 1);
  flex->addFrame(frame2, 3);

  frame1->destroy();
  frame2->destroy();

  window->run();
  return 0;
}
