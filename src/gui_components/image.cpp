#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/image.hpp"
#include "../utilities/include/fs.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <stb/stb_image.h>

// OpenGL stuff
unsigned int imageProgram;
unsigned int imageVao{};

bool initialized = false;
std::vector<Image*> images;

// math
glm::mat4 imageProjection;

// Creates a new image component
Image::Image(int x, int y, unsigned int width, unsigned int height, std::string filepath)
{
  // vertices and texture coordinates
  float vertices[] =
  {
    0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,       1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f
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

  // if this is the first time creating an image, initalize the creation
  if (!initialized)
  {
    initialized = true;

    // shader sources
    std::string vertexShaderString = Filesystem::readShaderFile("src/resources/shaders/image.vert");
    std::string fragmentShaderString = Filesystem::readShaderFile("src/resources/shaders/image.frag");

    // convert into OpenGL-readable C strings
    const char* vertexShaderSource = vertexShaderString.c_str();
    const char* fragmentShaderSource = fragmentShaderString.c_str();

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // shader program
    imageProgram = glCreateProgram();
    glAttachShader(imageProgram, vertexShader);
    glAttachShader(imageProgram, fragmentShader);

    glLinkProgram(imageProgram);

    // delete shaders to save memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // vao
    glGenVertexArrays(1, &imageVao);
    glBindVertexArray(imageVao);
  }

  // vbo
  unsigned int vbo{};
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // ebo
  unsigned int ebo{};
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // create a texture object in OpenGL
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // texture configuration
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // load the image
  int texWidth, texHeight, channels;
  unsigned char* data = stbi_load(filepath.c_str(), &texWidth, &texHeight, &channels, 0);

  // make sure the image was correctly loaded
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }
  else
  {
    std::cout << "Error: Failed to load texture with filepath \"" << filepath << "\".\n";
    exit(0);
  }

  // free stb image memory
  stbi_image_free(data);

  // set projection matrix
  imageProjection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

  // push back this object
  images.push_back(this);
}

// Draws the image onto the renderer
void Image::render()
{
  glUseProgram(imageProgram);

  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(imageVao);

  // calculate transformations
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(x + (width / 2), y + (height / 2), 0.0f));
  model = glm::scale(model, glm::vec3(width, height, 0.0f));

  // apply matrices
  int modelLocation = glGetUniformLocation(imageProgram, "model");
  int projectionLocation = glGetUniformLocation(imageProgram, "projection");

  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(imageProjection));

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

std::vector<Image*> Image::getTextures()
{
  return images;
}
