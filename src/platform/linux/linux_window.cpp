#ifdef __linux__

#include <iostream>
#include <string>

#include <glad/glad.h>

#include "include/linux_window.hpp"
#include "include/linux_opengl.hpp"

#include <gtk/gtk.h>
#include <gtk/gtkmain.h>
#include <gtk/gtkx.h>

int windowWidth = 0;
int windowHeight = 0;
std::string windowTitle = "";

GtkWidget *window;
bool initialized = false;
int count = 0;

gboolean mainLoop (GtkWidget *widget, GdkFrameClock *clock, gpointer data)
{
  if (initialized)
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Linux_Opengl::render();
  }

  return 1;
}

static void onActivate(GtkApplication *app)
{
  window = gtk_application_window_new(app);

  gtk_window_set_default_size(GTK_WINDOW(window), windowWidth, windowHeight);
  gtk_window_set_title(GTK_WINDOW(window), windowTitle.c_str());

  gtk_window_present(GTK_WINDOW(window));

  Linux_Opengl::createContext(initialized);
  gtk_widget_add_tick_callback(window, mainLoop, nullptr, nullptr);
}

Linux_Window::Linux_Window(unsigned int width, unsigned int height, std::string title)
{
  GtkApplication *app = gtk_application_new("com.srevrtt.litecode", G_APPLICATION_FLAGS_NONE);

  windowWidth = width;
  windowHeight = height;
  windowTitle = title;

  g_signal_connect(app, "activate", G_CALLBACK(onActivate), nullptr);

  const char *argv[] = { title.c_str() };
  g_application_run(G_APPLICATION(app), 0, (char **)argv);
}

Display *Linux_Window::getDisplay()
{
  return gdk_x11_display_get_xdisplay(gdk_display_get_default());
}

Window Linux_Window::getWindow()
{
  return gdk_x11_window_get_xid(gtk_widget_get_window(window));
}

#endif