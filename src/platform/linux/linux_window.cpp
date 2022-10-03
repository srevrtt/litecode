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

int windowWidth = 0;
int windowHeight = 0;
std::string windowTitle = "";

GtkWidget *window;
GtkApplication *app;

bool Linux_Window::ran = false;
bool running = true;

static void onClose(GtkApplication *app, gpointer data)
{
  exit(1);
}

static void onActivate(GtkApplication *app, gpointer data)
{
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_default_size(GTK_WINDOW(window), windowWidth, windowHeight);
  gtk_window_set_title(GTK_WINDOW(window), windowTitle.c_str());

  gtk_window_present(GTK_WINDOW(window));

  Linux_Opengl::createContext();
  gtk_widget_add_tick_callback(window, OSWindow::update, nullptr, nullptr);
  
  Linux_Window::ran = true;
  g_signal_connect(window, "destroy", gtk_main_quit, nullptr);
}

Linux_Window::Linux_Window(unsigned int width, unsigned int height, std::string title)
{
  app = gtk_application_new("com.srevrtt.litecode", G_APPLICATION_FLAGS_NONE);

  windowWidth = width;
  windowHeight = height;
  windowTitle = title;

  g_signal_connect(app, "activate", G_CALLBACK(onActivate), nullptr);
}

void Linux_Window::run()
{
  const char *argv[] = { windowTitle.c_str() };
  g_application_run(G_APPLICATION(app), 0, (char**)argv);
}

void Linux_Window::actualRun()
{
  gtk_main();
}

Display *Linux_Window::getDisplay()
{
  return gdk_x11_display_get_xdisplay(gdk_display_get_default());
}

Window Linux_Window::getWindow()
{
  return gdk_x11_window_get_xid(gtk_widget_get_window(window));
}

std::vector<int> Linux_Window::getSize()
{
  return { windowWidth, windowHeight };
}

#endif