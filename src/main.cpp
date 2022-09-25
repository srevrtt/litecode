#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/frame.hpp"
#include "gui_components/include/flexbox.hpp"

int main(int argc, char* argv[])
{
  Window* window = new Window(1280, 720, "Litecode v0.1.0");

  // create two test frames
  FrameComponent* frame1 = new FrameComponent(0, 0, 0, 0, 255, 132, 48);
  FrameComponent* frame2 = new FrameComponent(0, 0, 0, 0, 0, 0, 0);
  FrameComponent* frame3 = new FrameComponent(0, 0, 0, 0, 206, 17, 38);

  FlexboxComponent* flex = new FlexboxComponent();
  
  flex->increaseCapacity(3);

  flex->addFrame(frame1);
  flex->addFrame(frame2);
  flex->addFrame(frame3);

  frame1->destroy();
  frame2->destroy();
  frame3->destroy();

  window->run();
  return 0;
}
