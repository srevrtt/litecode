#ifdef _WIN32

#include <iostream>
#include <string>

#include <Windows.h>
#include <glad/glad.h>

#include "include/win_window.hpp"
#include "include/win_menu.hpp"

// global HDC
HDC driver;

// FPS limiting
double frameStart, frameTime;
const double frameDelay = 1000 / 60;

// Window main event loop
LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  // switch event message
  switch (msg)
  {
  // if a menu item has been created, then append it to the window
  case WM_CREATE:
    if (Windows_Menubar::menuActive())
    {
      Windows_Menubar::draw(hwnd);
    }

    break;
  // menubar event handlers
  case WM_COMMAND:
    for (auto &item : Windows_Menubar::getItems())
    {
      // call the event handler only if it exists
      if (LOWORD(wparam) == item->getId() && item->eventHandlerActive())
      {
        item->callEventHandler();
      }
    }

    break;
  // closing the window
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  // if the window is being moved
  case WM_MOVING:
    frameTime = GetTickCount64() - frameStart;
    if (frameDelay > frameTime)
    {
      Sleep((frameDelay - frameTime) / 2);
    }

    frameStart = GetTickCount64();
    break;
  // setting minimum window size
  case WM_GETMINMAXINFO:
  {
    LPMINMAXINFO info = (LPMINMAXINFO)lparam;
    info->ptMinTrackSize.x = 800;
    info->ptMinTrackSize.y = 600;
  }
  break;
  default:
    return DefWindowProcA(hwnd, msg, wparam, lparam);
  }

  return 0;
}

// Creates a window with the specified size and title
Windows_Window::Windows_Window(unsigned int width, unsigned int height, std::string title)
{
  // safety
  if (width < 3000 && height < 3000)
  {
    // configure the window class
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "window";
    wc.lpszMenuName = nullptr;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    // apply the configuration
    RegisterClassExA(&wc);

    // create the window
    hwnd = CreateWindowExA(
        WS_EX_CLIENTEDGE,
        "window",
        title.c_str(),
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr);

    // error handling
    if (!hwnd)
    {
      MessageBoxA(nullptr, "Failed to create a window.", "Fatal Error", MB_ICONERROR);
      exit(1);
    }

    // show & update the window
    ShowWindow(hwnd, SW_NORMAL);
    UpdateWindow(hwnd);

    // set the graphics driver
    driver = GetDC(hwnd);
  }
}

// Updates the window
void Windows_Window::update()
{
  // set the viewport in case the window size changed
  RECT rect;
  if (GetWindowRect(hwnd, &rect))
  {
    glViewport(0, 0, rect.right - rect.left, rect.bottom - rect.top);
  }

  TranslateMessage(&msg);
  DispatchMessageA(&msg);
}

// Returns a boolean value determining if the window is active
bool Windows_Window::active()
{
  frameTime = GetTickCount64() - frameStart;
  if (frameDelay > frameTime)
  {
    Sleep(frameDelay - frameTime);
  }

  frameStart = GetTickCount64();
  return GetMessage(&msg, nullptr, 0, 0) > 0;
}

// Closes the window
void Windows_Window::close()
{
  DestroyWindow(hwnd);
}

// Returns the Win32 window handle for OpenGL context creation
HWND Windows_Window::getWindowHandle()
{
  return hwnd;
}

// Returns the Win32 graphics driver for OpenGL
HDC Windows_Window::getDriver()
{
  return driver;
}

#endif
