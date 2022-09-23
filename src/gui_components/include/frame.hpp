#pragma once
#include <vector>

std::vector<std::vector<int>> getFrames();

class FrameComponent
{
private:
  int x, y;
  unsigned int width, height;
public:
  FrameComponent(int x, int y, unsigned int width, unsigned int height);

  void changePos(int x, int y);
  void changeSize(unsigned int width, unsigned int height);
};
