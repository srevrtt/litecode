#pragma once
#include <vector>

std::vector<std::vector<int>> getFrames();

class FrameComponent
{
private:
  int x, y;
  int r, g, b;
  unsigned int width, height;
public:
  FrameComponent(int x, int y, unsigned int width, unsigned int height, unsigned int r, unsigned int g, unsigned int b);

  void changePos(int x, int y);
  void changeSize(unsigned int width, unsigned int height);

  std::vector<int> getColor();
  std::vector<int> getSizeAndPosition();
};
