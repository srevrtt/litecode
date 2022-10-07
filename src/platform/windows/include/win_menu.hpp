#pragma once

#include <string>
#include <vector>

#include <Windows.h>

class Windows_MenuItem
{
private:
  int id;
  std::string label;
  void (*eventHandler)() = nullptr;

public:
  Windows_MenuItem(int id, std::string label);
  void addEventHandler(void (*handler)());

  const char *getLabel();
  int getId();

  void callEventHandler();
  bool eventHandlerActive();
};

class Windows_Menubar
{
private:
  int id; // the unique ID template that is given to each menu item

public:
  Windows_Menubar();

  void addMenu(Windows_MenuItem *menuitem);
  void addSubmenu(std::string label, int id, std::vector<Windows_MenuItem *> items);

  static void draw(HWND hwnd);
  static std::vector<Windows_MenuItem *> getItems();
  static bool menuActive();
};
