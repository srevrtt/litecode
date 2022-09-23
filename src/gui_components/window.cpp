#include <iostream>
#include <string>

#include "include/frame.hpp"
#include <glad/glad.h>

#include "include/window.hpp"
#include "../utilities/include/fs.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Creates a window for the current platform
Window::Window(unsigned int width, unsigned int height, std::string title)
{
#ifdef _WIN32
  window = new Windows_Window(width, height, title);
  Windows_OpenGL::init();
  Windows_OpenGL::createContext(window->getWindowHandle());
#endif

  // initalize OpenGL rendering
  glViewport(0, 0, width, height);

  // shader sources
  std::string vertexShaderString = Filesystem::readShaderFile("src/resources/shaders/frame.vert");
  std::string fragmentShaderString = Filesystem::readShaderFile("src/resources/shaders/frame.frag");

  const char* vertexShaderSource = vertexShaderString.c_str();
  const char* fragmentShaderSource = fragmentShaderString.c_str();

  // shaders
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  // shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  // delete shaders to save memory
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // vertex array object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // apply orthographic projection matrix for transformations
  projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
}

// Runs the main loop for the created window
void Window::run()
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while (!window->isCloseRequested())
  {
    glClearColor(26.0f/255.0f, 26.0f/255.0f, 26.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    // rendering objects
    for (auto &frame : getFrames())
    {
      glm::mat4 model = glm::mat4(1.0f);

      // apply translation to x, y position, corner allignment, and offset to the height to exclude the titlebar
      model = glm::translate(model, glm::vec3(frame[0] + (frame[2] / 2), frame[1] + (frame[3] * 1.25), 0.0f));
      model = glm::scale(model, glm::vec3(frame[2], frame[3], 0.0f)); // scale to the width and height

      // get locations of uniform variables inside the shaders
      int modelLocation = glGetUniformLocation(shaderProgram, "model");
      int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

      // apply the transformations
      glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

      // draw it!
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    Windows_OpenGL::render();
    window->update();
  }

  window->close();
}
