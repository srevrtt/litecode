#ifdef __linux__

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <X11/Xlib.h>

#include "include/linux_opengl.hpp"
#include "include/linux_window.hpp"

#include <GL/gl.h>
#include <GL/glx.h>

Display *display;
Window handle;

// GLX context creation proc address type
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);

// Creates a Linux specific OpenGL context
void Linux_Opengl::createContext()
{
  // configure the OpenGL renderer
  int glxAttribs[] =
      {
          GLX_X_RENDERABLE, True,
          GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
          GLX_RENDER_TYPE, GLX_RGBA_BIT,
          GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
          GLX_RED_SIZE, 8,
          GLX_GREEN_SIZE, 8,
          GLX_BLUE_SIZE, 8,
          GLX_ALPHA_SIZE, 8,
          GLX_DEPTH_SIZE, 24,
          GLX_STENCIL_SIZE, 8,
          GLX_DOUBLEBUFFER, True,
          0};

  // get the X11 handles
  display = Linux_Window::getDisplay();
  int screen = DefaultScreen(display);

  // getting the best FB visual with the most samples per pixel
  int fbCount{};
  GLXFBConfig *fbc = glXChooseFBConfig(display, screen, glxAttribs, &fbCount);

  int bestFbc = -1, worstFbc = -1, bestNumSamp = -1, worstNumSamp = 999;
  for (int i = 0; i < fbCount; i++)
  {
    XVisualInfo *visualInfo = glXGetVisualFromFBConfig(display, fbc[i]);

    if (visualInfo != 0)
    {
      int sampBuffer{}, samples{};

      glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS, &sampBuffer);
      glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

      if (bestFbc < 0 || (sampBuffer && samples > bestNumSamp))
      {
        bestFbc = i;
        bestNumSamp = samples;
      }

      if (worstFbc < 0 || !sampBuffer || samples < worstNumSamp)
      {
        worstFbc = i;
      }

      worstNumSamp = samples;
    }
  }

  // choosing the visual info from that best FB visual
  GLXFBConfig bestFBC = fbc[bestFbc];
  XVisualInfo *visual = glXGetVisualFromFBConfig(display, bestFBC);

  // error handling
  if (visual == 0)
  {
    std::cout << "Error: Could not create visual window.\n";
    exit(1);
  }

  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

  // configure the OpenGL context
  int contextAttribs[] =
      {
          GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
          GLX_CONTEXT_MINOR_VERSION_ARB, 3,
          GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
          None};

  // get the X11 window handle from the GTK window
  handle = Linux_Window::getWindow();

  // create the context
  GLXContext context = 0;
  context = glXCreateContextAttribsARB(display, bestFBC, 0, true, contextAttribs);

  // make it current & load glad :)
  glXMakeCurrent(display, handle, context);
  gladLoadGL();
}

// Swaps both buffers of the OpenGL renderer
void Linux_Opengl::render()
{
  glXSwapBuffers(Linux_Window::getDisplay(), Linux_Window::getWindow());
}

#endif
