#include <iostream>
#include <string>

#include "include/text.hpp"
#include "include/font.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::vector<Text*> textComponents{};

// Creates a new text object with the specified font, text to display, color, and position
Text::Text(FontComponent *font, std::string text, int x, int y, unsigned int r, unsigned int g, unsigned int b)
{
  // set member variables
  this->font = font;
  this->text = text;

  this->r = r;
  this->g = g;
  this->b = b;

  this->x = (float)x;
  this->y = (float)y;
  initialX = x;

  this->size = 1.0f;

  // indices
  unsigned int indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };

  // generate & bind buffers
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, nullptr, GL_DYNAMIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // add to the count
  textComponents.push_back(this);
}

// Draws the text onto the window's renderer
void Text::render()
{
  FontComponent::render();
  float newY = 720 - y;
  
  for (auto &i : text)
  {
    FontChar chr = font->getCharList()[i];
    
    float xpos = x + chr.bearing.x * size;
    float ypos = newY - (chr.size.y - chr.bearing.y) * size;

    float w = chr.size.x * size;
    float h = chr.size.y * size;

    // update VBO for each character
    float vertices[] = {
      xpos + w, ypos,       1.0f, 1.0f,
      xpos + w, ypos + h,   1.0f, 0.0f,
      xpos,     ypos + h,   0.0f, 0.0f,
      xpos,     ypos,       0.0f, 1.0f,
    };

    glBindTexture(GL_TEXTURE_2D, chr.texture);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    x += (chr.advance >> 6) * size;
  }

  x = initialX;
}

// Returns the number of text components created
std::vector<Text*> Text::getNumText()
{
  return textComponents;
}
