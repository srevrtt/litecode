#pragma once

#include "font.hpp"
#include <glm/glm.hpp>

class Text
{
private:
  FontComponent *font;
  std::string text{};
  float size{};

  float x{};
  float y{};

  unsigned int r{};
  unsigned int g{};
  unsigned int b{};

  unsigned int vbo;
  unsigned int ebo;

  int initialX{};
  glm::mat4 model;
public:
  Text(FontComponent *font, std::string text, int x, int y, unsigned int r, unsigned int g, unsigned int b);

  void changeText(std::string newText);
  void render();

  static std::vector<Text*> getNumText();
};
