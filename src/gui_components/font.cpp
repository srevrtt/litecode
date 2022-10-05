#include <iostream>
#include <string>

#include "include/font.hpp"
#include "../utilities/include/fs.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

FT_Library lib;
glm::mat4 fontProjection;

// declare static variables
unsigned int FontComponent::shaderProgram{};
unsigned int FontComponent::vao{};
std::vector<FontChar> FontComponent::characters{};

// Initializes font rendering
void FontComponent::init()
{
  if (FT_Init_FreeType(&lib))
  {
    std::cout << "Error: Failed to initialize Freetype.\n";
    exit(1);
  }

  // initialize OpenGL rendering
  // shader sources
  std::string vertexShaderString = Filesystem::readShaderFile("../src/resources/shaders/text/text.vert");
  std::string fragmentShaderString = Filesystem::readShaderFile("../src/resources/shaders/text/text.frag");
  
  // convert into OpenGL-readable C string
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
  fontProjection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Creates a new font object with the provided size and font file path
FontComponent::FontComponent(std::string fontPath)
{
  // create the font face
  if (FT_New_Face(lib, fontPath.c_str(), 0, &font))
  {
    std::cout << "Error: Failed to create a font with filepath \"" << fontPath << "\n.\n";
    exit(1);
  }

  // set pixel font size
  FT_Set_Pixel_Sizes(font, 0, 48);
  
  // disable OpenGL byte allignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // load all characters of the first 128 characters of the ASCII chart
  for (unsigned char chr = 0; chr < 128; chr++)
  {
    // load the character
    if (FT_Load_Char(font, chr, FT_LOAD_RENDER))
    {
      std::cout << "Error: Failed to load glyph \"" << chr << "\".\n";
      exit(1);
    }

    // create an OpenGL texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // apply the font texture
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      font->glyph->bitmap.width,
      font->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      font->glyph->bitmap.buffer
    );

    // set OpenGL texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // create the instance of the character
    FontChar character;

    character.texture = texture;
    character.size = glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows);
    character.bearing = glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top);
    character.advance = font->glyph->advance.x;

    // and append it
    characters.push_back(character);
  }

  FT_Done_Face(font);
}

// Renders the font
void FontComponent::render()
{
  glUseProgram(shaderProgram);
  glBindVertexArray(vao);

  int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(fontProjection));
}

// Returns the loaded character list
std::vector<FontChar> FontComponent::getCharList()
{
  return characters;
}

// Retrieves the shader program handle
unsigned int FontComponent::getProgram()
{
  return shaderProgram;
}
