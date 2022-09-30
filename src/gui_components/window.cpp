#include <iostream>
#include <string>

#include <glad/glad.h>

#include "include/frame.hpp"
#include "include/window.hpp"

#include "../utilities/include/fs.hpp"

// Creates a window for the current platform
Window::Window(unsigned int width, unsigned int height, std::string title)
{
#ifdef _WIN32
  window = new Windows_Window(width, height, title);
  Windows_OpenGL::init();
  Windows_OpenGL::createContext(window->getWindowHandle());
#elif __linux__
  window = new Linux_Window(width, height, title);
#endif

  // initalize OpenGL rendering
  ////glViewport(0, 0, width, height);

  // shader sources
  //std::string vertexShaderString = Filesystem::readShaderFile("src/resources/shaders/frame.vert");
  //std::string fragmentShaderString = Filesystem::readShaderFile("src/resources/shaders/frame.frag");
  //
  //const char* vertexShaderSource = vertexShaderString.c_str();
  //const char* fragmentShaderSource = fragmentShaderString.c_str();
  //
  //// shaders
  //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  //glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  //glCompileShader(vertexShader);
  //
  //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  //glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  //glCompileShader(fragmentShader);
  //
  //// shader program
  //shaderProgram = glCreateProgram();
  //glAttachShader(shaderProgram, vertexShader);
  //glAttachShader(shaderProgram, fragmentShader);
  //
  //glLinkProgram(shaderProgram);
  //
  //// delete shaders to save memory
  //glDeleteShader(vertexShader);
  //glDeleteShader(fragmentShader);
  //
  //// vertex array object
  //glGenVertexArrays(1, &vao);
  //glBindVertexArray(vao);
  //
  //// apply orthographic projection matrix for transformations
  //projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
}

// Runs the main loop for the created window
void Window::run()
{
  #ifdef _WIN32
  if (Image::getTextures().size() > 0)
  {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }
  else
  {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  }

  while (window->active())
  {
    glClearColor(26.0f / 255.0f, 26.0f / 255.0f, 26.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    // rendering objects
    for (auto& frame : FrameComponent::getAllFrames())
    {
      frame->render(shaderProgram, projection);
    }

    for (auto& image : Image::getTextures())
    {
      image->render();
    }

    Windows_OpenGL::render();
    window->update();
  }

  window->close();
  
  #endif
}
