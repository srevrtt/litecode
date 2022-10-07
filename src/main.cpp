#include <iostream>
#include <string>

#include "gui_components/include/window.hpp"
#include "gui_components/include/image.hpp"
#include "gui_components/include/text.hpp"
#include "gui_components/include/menu.hpp"

OSWindow *window;

void onQuit()
{
  std::cout << "You have successfully escaped.\n";
  window->close();
}

int main(int argc, char *argv[])
{
  OSSubmenu *submenu = new OSSubmenu("File");

  OSMenuItem *newBtn = new OSMenuItem("New");
  submenu->addItem(newBtn);

  OSMenuItem *quit = new OSMenuItem("Quit");
  quit->addEventHandler(onQuit);
  submenu->addItem(quit);

  OSMenubar *menu = new OSMenubar();
  menu->addSubmenu(submenu);

  window = new OSWindow(1280, 720, "Litecode v0.1.0");
  window->run();

  return 0;
}
