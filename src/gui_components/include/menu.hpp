#pragma once
#include <string>

#ifdef _WIN32
#include "../../platform/windows/include/win_menu.hpp"
#endif

class OSMenuItem
{
private:
  std::string name;

public:
  void (*eventHandler)() = nullptr;
  OSMenuItem(std::string label);

  void addEventHandler(void (*eventHandler)());
  const void *getEventHandler();

  std::string getName();
};

class OSSubmenu
{
private:
  std::string name;
  std::vector<OSMenuItem *> elements;

public:
  OSSubmenu(std::string label);
  void addItem(OSMenuItem *item);

  std::vector<OSMenuItem *> getElementData();
  std::string getName();
};

class OSMenubar
{
private:
#ifdef _WIN32
  Windows_Menubar *menubar;
#endif
  int currentId{};

public:
  OSMenubar();
  void addItem(std::string label);
  void addSubmenu(OSSubmenu *submenu);
};
