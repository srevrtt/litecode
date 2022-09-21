#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <string>

class Windows_Window
{
private:
  WNDCLASSEXA wc;
  HWND hwnd;
  MSG msg;
public:
  Windows_Window(unsigned int width, unsigned int height, std::string title);

  void update();
  bool isCloseRequested();
  void close();
};

#endif
