#include <iostream>
#include <string>

#include "include/menu.hpp"

// Creates a new cross platform menu item with a label
OSMenuItem::OSMenuItem(std::string label)
{
  name = label;
}

// Adds an event handler to the menu item
void OSMenuItem::addEventHandler(void (*eventHandler)())
{
  this->eventHandler = eventHandler;
}

// Gets the label of the menu item
std::string OSMenuItem::getName()
{
  return name;
}

// Creates a cross platform sub menu
OSSubmenu::OSSubmenu(std::string label)
{
  name = label;
}

// Appends a menu item to the sub menu
void OSSubmenu::addItem(OSMenuItem *item)
{
  elements.push_back(item);
}

// Returns all of the children of the sub menu
std::vector<OSMenuItem *> OSSubmenu::getElementData()
{
  return elements;
}

// Gets the name of the sub menu
std::string OSSubmenu::getName()
{
  return name;
}

// Creates a cross platform menubar (must be created before the window has been created)
OSMenubar::OSMenubar()
{
  // create a new Windows menubar if we're on windows
#ifdef _WIN32
  menubar = new Windows_Menubar();
#endif
}

// Appends a single menu label to the menubar
void OSMenubar::addItem(std::string label)
{
#ifdef _WIN32
  currentId++;

  Windows_MenuItem *menuitem = new Windows_MenuItem(currentId, label);
  menubar->addMenu(menuitem);
#endif
}

// Adds a submenu to the menubar
void OSMenubar::addSubmenu(OSSubmenu *submenu)
{
#ifdef _WIN32
  std::vector<Windows_MenuItem *> items;

  currentId++;
  int currentSubId = currentId + 1;

  // for each element, add a menu item
  for (auto &menu : submenu->getElementData())
  {
    currentSubId++;

    Windows_MenuItem *mi = new Windows_MenuItem(currentSubId, menu->getName());

    if (menu->eventHandler != nullptr)
    {
      mi->addEventHandler(menu->eventHandler);
    }

    items.push_back(mi);
  }

  // add the submenu
  menubar->addSubmenu(submenu->getName(), currentId, items);
  currentId = currentSubId;
#endif
}
