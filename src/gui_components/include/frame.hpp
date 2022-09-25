#pragma once

#include <glm/glm.hpp>
#include <vector>

class FrameComponent
{
private:
  int x, y;
  int r, g, b;
  unsigned int width, height;
public:
  bool isChild = false;
  FrameComponent(int x, int y, unsigned int width, unsigned int height, unsigned int r, unsigned int g, unsigned int b);

  void render(unsigned int shaderProgram, glm::mat4 projection);
  void destroy();

  void changePos(int x, int y);
  void changeSize(unsigned int width, unsigned int height);

  std::vector<int> getColor();
  std::vector<int> getSizeAndPosition();

  static std::vector<FrameComponent*> getAllFrames();
};
