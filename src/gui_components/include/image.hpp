#pragma once

#include <string>
#include <vector>

class Image
{
private:
  unsigned int texture{};
  glm::mat4 model = glm::mat4(1.0f);
public:
  int x{}, y{};
  unsigned int width{}, height{};

  Image(int x, int y, unsigned int width, unsigned int height, std::string filepath);
  void render();

  static std::vector<Image*> getTextures();
};
