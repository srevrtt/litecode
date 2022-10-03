#ifdef __linux__

#include <iostream>
#include <string>

#include <glad/glad.h>

#include "include/linux_window.hpp"
#include "include/linux_opengl.hpp"
#include "../../gui_components/include/window.hpp"

#include <gtk/gtk.h>
#include <gtk/gtkmain.h>
#include <gtk/gtkx.h>

// Window configuration for GTK
int windowWidth = 0;
int windowHeight = 0;
std::string windowTitle = "";

// Global GTK variables
GtkWidget *window;
GtkApplication *app;

// Callback function for when the GtkApplication activates
static void onActivate(GtkApplication *app, gpointer data)
{
  // create a new window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // configure the window
  gtk_window_set_default_size(GTK_WINDOW(window), windowWidth, windowHeight);
  gtk_window_set_title(GTK_WINDOW(window), windowTitle.c_str());

  // show it
  gtk_window_present(GTK_WINDOW(window));

  // initialize OpenGL
  Linux_Opengl::createContext();

  // add callbacks
  gtk_widget_add_tick_callback(window, OSWindow::updateGtk, nullptr, nullptr);
  g_signal_connect(window, "destroy", gtk_main_quit, nullptr);
}

// Creates a Linux specific window
Linux_Window::Linux_Window(unsigned int width, unsigned int height, std::string title)
{
  // create a new GTK application
  app = gtk_application_new("com.srevrtt.litecode", G_APPLICATION_FLAGS_NONE);

  // set global GTK window configuration variables
  windowWidth = width;
  windowHeight = height;
  windowTitle = title;

  // set the on activate callback function
  g_signal_connect(app, "activate", G_CALLBACK(onActivate), nullptr);

  // run the application without going into the main loop
  const char *argv[] = { windowTitle.c_str() };
  g_application_run(G_APPLICATION(app), 0, (char**)argv);
}

// Sets the Linux window to go into a "main loop state"
void Linux_Window::run()
{
  gtk_main();
}

// Returns the X11 display handle
Display *Linux_Window::getDisplay()
{
  return gdk_x11_display_get_xdisplay(gdk_display_get_default());
}

// Gets the X11 window handle
Window Linux_Window::getWindow()
{
  return gdk_x11_window_get_xid(gtk_widget_get_window(window));
}

// Gets the window size of the Linux window
std::vector<int> Linux_Window::getSize()
{
  return { windowWidth, windowHeight };
}

#endif