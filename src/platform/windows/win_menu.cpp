#include <iostream>
#include <string>

#include "include/win_menu.hpp"
#include <Windows.h>

// menu globals
bool menuCreated = false; // test to see if we want to create a menubar
HMENU menu;               // the menu

std::vector<Windows_MenuItem *> menuItems; // for event handling

// Creates a new menu item with the specified ID and label
Windows_MenuItem::Windows_MenuItem(int id, std::string label)
{
  // set member variables & append to the menu items
  this->id = id;
  this->label = label;
  menuItems.push_back(this);
}

// Adds an event handler to the specified callable function
void Windows_MenuItem::addEventHandler(void (*handler)())
{
  this->eventHandler = handler;
}

// Gets the menu item's label as a C string
const char *Windows_MenuItem::getLabel()
{
  return label.c_str();
}

// Gets the ID of the menu item
int Windows_MenuItem::getId()
{
  return id;
}

// Calls the menu item's event handler
void Windows_MenuItem::callEventHandler()
{
  eventHandler();
}

// Returns a boolean determining if there is an event handler attached to the menu item
bool Windows_MenuItem::eventHandlerActive()
{
  return eventHandler != nullptr;
}

// Creates a Win32 menubar
Windows_Menubar::Windows_Menubar()
{
  menu = CreateMenu();
  menuCreated = true;
}

// Adds a menu item to the menubar
void Windows_Menubar::addMenu(Windows_MenuItem *menuitem)
{
  AppendMenuA(menu, MF_STRING, menuitem->getId(), menuitem->getLabel());
}

// Adds a submenu to the menubar
void Windows_Menubar::addSubmenu(std::string label, int id, std::vector<Windows_MenuItem *> items)
{
  // create it
  HMENU submenu = CreatePopupMenu();

  // for each item, add a new menu label to the submenu
  for (auto &item : items)
  {
    AppendMenuA(submenu, MF_STRING, item->getId(), item->getLabel());
  }

  // append the submenu to the main menubar
  AppendMenuA(menu, MF_STRING | MF_POPUP, (UINT)submenu, label.c_str());
}

// Applies all of these changes to the window
void Windows_Menubar::draw(HWND hwnd)
{
  SetMenu(hwnd, menu);
}

// Gets all of the children of the menubar
std::vector<Windows_MenuItem *> Windows_Menubar::getItems()
{
  return menuItems;
}

// Returns a boolean determining if a menubar has been created
bool Windows_Menubar::menuActive()
{
  return menuCreated;
}
