#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include "include/frame.hpp"

std::vector<FrameComponent*> frames;
bool first = false;

// Creates a new frame with the specified size, position, and color
FrameComponent::FrameComponent(int x, int y, unsigned int width, unsigned int height, unsigned int r, unsigned int g, unsigned int b)
{
  // vertices
  float vertices[] =
  {
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };

  // indices
  unsigned int indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };

  // set member variables
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->r = r;
  this->g = g;
  this->b = b;

  // vertex buffer object
  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // element array buffer object
  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // check color parameters
  if (r > 255 && g > 255 && b > 255)
  {
    std::cout << "Error: Invalid color parameter for frame.\n";
    exit(1);
  }
  
  frames.push_back(this);
}

// Draws the frame onto the renderer
void FrameComponent::render(unsigned int shaderProgram, glm::mat4 projection)
{
  glm::mat4 model = glm::mat4(1.0f);
  glm::vec3 color;

  // apply translation to x, y position and corner allignment
  model = glm::translate(model, glm::vec3(x + (width / 2), (y + (height / 2)), 0.0f));
  model = glm::scale(model, glm::vec3(width, height, 0.0f)); // scale to the width and height

  // get the color
  color = glm::vec3(r, g, b);

  // get locations of uniform variables inside the shaders
  int modelLocation = glGetUniformLocation(shaderProgram, "model");
  int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
  int colorLocation = glGetUniformLocation(shaderProgram, "color");

  // apply the transformations
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

  // apply the color
  glUniform3fv(colorLocation, 1, glm::value_ptr(color));

  // draw it!
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


// Deletes the frame
void FrameComponent::destroy()
{
  int idx = 0;

  // get the index of the current frame
  for (int i = 0; i < frames.size(); i++)
  {
    if (frames[i] == this)
    {
      idx = i;
      break;
    }
  }

  // delete it
  frames.erase(frames.begin() + idx);

  // remove color
  r = 0;
  g = 0;
  b = 0;

  // remove size and position
  x = 0;
  y = 0;
  width = 0;
  height = 0;
}

// Gets the color of the frame and returns a vector of integers respresenting the r, g, b color
std::vector<int> FrameComponent::getColor()
{
  return {r, g, b};
}

// Returns a vector of integers representing the size and position of the frame
std::vector<int> FrameComponent::getSizeAndPosition()
{
  return {x, y, (int)width, (int)height};
}

// Gets all of the current created frames
std::vector<FrameComponent*> FrameComponent::getAllFrames()
{
  return frames;
}
