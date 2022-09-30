#ifdef __linux__

#include <iostream>
#include <string>

#include "include/linux_window.hpp"

#include <gtk/gtk.h>
#include <gtk/gtkmain.h>

int windowWidth = 0;
int windowHeight = 0;
std::string windowTitle = "";

static gpointer test(gpointer data)
{
  while (true)
  {
    // TODO:
  }

  return 0;
}

static void onActivate(GtkApplication *app)
{
  GtkWidget *window = gtk_application_window_new(app);

  gtk_window_set_default_size(GTK_WINDOW(window), windowWidth, windowHeight);
  gtk_window_set_title(GTK_WINDOW(window), windowTitle.c_str());

  gtk_window_present(GTK_WINDOW(window));

  GThread *thread = g_thread_new("testthread", test, nullptr);
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

#endif