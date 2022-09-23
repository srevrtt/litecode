#include <iostream>
#include <string>

#include <Windows.h>
#include "include/win_opengl.hpp"

#include <glad/glad.h>
#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/wglext.h>

HDC hdc;

// OpenGL context type
typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int* attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;

// OpenGL pixel format type
typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int* piAttribList, const FLOAT *pfAttribList,
  UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
wglChoosePixelFormatARB_type* wglChoosePixelFormatARB;

// Initializes the OpenGL context creation before the window has been created
void Windows_OpenGL::init()
{
  // create a fake window class
  WNDCLASSA fakeWc{};
  fakeWc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  fakeWc.lpfnWndProc = DefWindowProcA;
  fakeWc.hInstance = GetModuleHandleA(nullptr);
  fakeWc.lpszClassName = "qwerty123";

  // register it
  RegisterClassA(&fakeWc);

  // create a dummy window
  HWND dummyWindow = CreateWindowExA(
    0,
    fakeWc.lpszClassName,
    "Dummy OpenGL Window",
    0,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    0,
    0,
    fakeWc.hInstance,
    0
  );

  // error handling
  if (!dummyWindow)
  {
    std::cout << "Failed to initialize fake OpenGL window." << '\n';
    exit(1);
  }

  // create a dummy device context
  HDC dummyHdc = GetDC(dummyWindow);

  // pixel format configuration
  PIXELFORMATDESCRIPTOR pfd;
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.cColorBits = 32;
  pfd.cAlphaBits = 8;
  pfd.iLayerType = PFD_MAIN_PLANE;
  pfd.cDepthBits = 24;
  pfd.cStencilBits = 8;

  // applying the pixel format configuration
  int pixelFormat = ChoosePixelFormat(dummyHdc, &pfd);
  SetPixelFormat(dummyHdc, pixelFormat, &pfd);

  // create the dummy OpenGL context
  HGLRC dummyContext = wglCreateContext(dummyHdc);
  wglMakeCurrent(dummyHdc, dummyContext);

  // set the two OpenGL loader functions
  wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress("wglCreateContextAttribsARB");
  wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)wglGetProcAddress("wglChoosePixelFormatARB");

  // destroy everything
  wglMakeCurrent(dummyHdc, 0);
  wglDeleteContext(dummyContext);
  ReleaseDC(dummyWindow, dummyHdc);
  DestroyWindow(dummyWindow);
}

void Windows_OpenGL::createContext(HWND hwnd)
{
  // get the real graphics driver
  hdc = GetDC(hwnd);

  // modern pixel format configuration
  int pixelFormatAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
    WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
    WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB,         32,
    WGL_DEPTH_BITS_ARB,         24,
    WGL_STENCIL_BITS_ARB,       8,
    0
  };

  int pixelFormat;
  UINT numFormats;
  wglChoosePixelFormatARB(hdc, pixelFormatAttribs, 0, 1, &pixelFormat, &numFormats);

  // apply the modern pixel format
  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
  SetPixelFormat(hdc, pixelFormat, &pfd);

  // specify the context attributes (we want 3.3 core)
  int glAttribs[] =
  {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0
  };

  // create the context and make it current
  HGLRC glContext = wglCreateContextAttribsARB(hdc, 0, glAttribs);
  wglMakeCurrent(hdc, glContext);

  // load Glad
  gladLoadGL();
}

// Renders everything from the window's renderer to the screen
void Windows_OpenGL::render()
{
  SwapBuffers(hdc);
}
