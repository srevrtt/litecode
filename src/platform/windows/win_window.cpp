#ifdef _WIN32

#include <string>
#include <Windows.h>

#include "include/win_window.hpp"

// Window main event loop
LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
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
    wc.hbrBackground = CreateSolidBrush(RGB(26, 26, 26)); // light gray for now
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
      nullptr
    );

    // error handling
    if (!hwnd)
    {
      MessageBoxA(nullptr, "Failed to create a window.", "Fatal Error", MB_ICONERROR);
      exit(1);
    }

    // show & update the window
    ShowWindow(hwnd, SW_NORMAL);
    UpdateWindow(hwnd);
  }
}

// Updates the window
void Windows_Window::update()
{
  TranslateMessage(&msg);
  DispatchMessageA(&msg);
}

// Returns a boolean value determining if the window should close
bool Windows_Window::isCloseRequested()
{
  return GetMessageA(&msg, nullptr, 0, 0) == 0;
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

#endif
