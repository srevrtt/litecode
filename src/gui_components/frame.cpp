#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include "include/frame.hpp"

std::vector<std::vector<int>> frames;

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

  frames.push_back({ x, y, (int)width, (int)height, (int)r, (int)g, (int)b});
}

std::vector<std::vector<int>> getFrames()
{
  return frames;
}