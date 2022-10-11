#include <iostream>
#include <string>

#include <glad/glad.h>

#ifdef __linux__
#include <gtk/gtk.h>
#endif

#include "include/frame.hpp"
#include "include/window.hpp"
#include "include/image.hpp"
#include "include/text.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utilities/include/fs.hpp"

// OpenGL renderer variables
unsigned int shaderProgram;
unsigned int vao;
glm::mat4 projection;

#ifdef __linux__
Linux_Window *win;
#endif

bool attrib = false;

// Creates a window for the current platform
OSWindow::OSWindow(unsigned int width, unsigned int height, std::string title)
{
#ifdef _WIN32
  window = new Windows_Window(width, height, title);
  Windows_OpenGL::init();
  Windows_OpenGL::createContext(window->getWindowHandle());
#elif __linux__
  win = new Linux_Window(width, height, title);
#endif
  glViewport(0, 0, 0, 0);

  // // shader sources
  // std::string vertexShaderString = Filesystem::readShaderFile("../src/resources/shaders/frame.vert");
  // std::string fragmentShaderString = Filesystem::readShaderFile("../src/resources/shaders/frame.frag");

  // const char* vertexShaderSource = vertexShaderString.c_str();
  // const char* fragmentShaderSource = fragmentShaderString.c_str();

  // // shaders
  // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  // glCompileShader(vertexShader);

  // unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  // glCompileShader(fragmentShader);

  // // shader program
  // shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, vertexShader);
  // glAttachShader(shaderProgram, fragmentShader);

  // glLinkProgram(shaderProgram);

  // // delete shaders to save memory
  // glDeleteShader(vertexShader);
  // glDeleteShader(fragmentShader);

  // // vertex array object
  // glGenVertexArrays(1, &vao);
  // glBindVertexArray(vao);

  // // apply orthographic projection matrix for transformations
  // projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

  // initialize text rendering
  FontComponent::init();
}

void OSWindow::update()
{
  // if we previously configured the vertex attrib pointers, start rendering
  if (attrib)
  {
    // clear the renderer
    glClearColor(26.0f / 255.0f, 26.0f / 255.0f, 26.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // prepare for rendering
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    // rendering objects
    for (auto &frame : FrameComponent::getAllFrames())
    {
      frame->render(shaderProgram, projection);
    }

    for (auto &image : Image::getTextures())
    {
      image->render();
    }

    for (auto &text : Text::getNumText())
    {
      text->render();
    }

// swap buffers
#ifdef __linux__
    Linux_Opengl::render();
#elif _WIN32
    Windows_OpenGL::render();
#endif
  }
}

#ifdef __linux__
// GTK tick callback
gboolean OSWindow::updateGtk(GtkWidget *window, GdkFrameClock *clock, gpointer data)
{
  update();
  return 1;
}
#endif

// Runs the main loop for the created window
void OSWindow::run()
{
  if (Image::getTextures().size() > 0 || Text::getNumText().size() > 0)
  {
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
  }
  else
  {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
  }

  attrib = true;

#ifdef __linux__
  win->run();
#elif _WIN32
  while (window->active())
  {
    window->update();
    update();
  }
#endif
}

void OSWindow::close()
{
#ifdef _WIN32
  window->close();
#endif
}
