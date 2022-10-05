#pragma once

#include <ft2build.h>
#include <freetype/freetype.h>

#include <string>
#include <vector>

#include <glm/glm.hpp>

struct FontChar
{
  unsigned int texture;
  glm::ivec2 size;
  glm::ivec2 bearing;
  unsigned int advance;
};

class FontComponent
{
private:
  FT_Face font;

  static std::vector<FontChar> characters;
  static unsigned int shaderProgram;
  static unsigned int vao;
public:
  FontComponent(std::string fontPath);

  static void init();
  static void render();
  static void useProgram();

  static std::vector<FontChar> getCharList();
  unsigned int getProgram();
};
