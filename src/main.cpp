#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/image.hpp"
#include "gui_components/include/text.hpp"

int main(int argc, char* argv[])
{
  OSWindow *window = new OSWindow(1280, 720, "Litecode v0.1.0");
  FontComponent *font = new FontComponent("../src/resources/fonts/inter/Inter-Regular.ttf");

  Text *text = new Text(font, "orange banana.", 100, 100, 255, 255, 255);
  Text *text2 = new Text(font, "woooooooooooooooooooo", 100, 200, 255, 255, 255);

  window->run();
  
  return 0;
}
