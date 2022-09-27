#pragma once

#include <string>
#include <vector>
#include "frame.hpp"
#include <glm/glm.hpp>

class FlexboxFrame
{
public:
  int x, y;
  int r, g, b;
  unsigned int width, height;
  int flex;

  FlexboxFrame(int x, int y, int r, int g, int b, unsigned int width, unsigned int height, int flex);
};

enum FlexboxAlignment
{
  FB_ALIGNMENT_VERTICAL,
  FB_ALIGNMENT_HORIZONTAL
};

class FlexboxComponent
{
private:
  std::vector<FlexboxFrame*> frames{};
  int numFrames = 0;
  int currentFrame = 0;
  FlexboxAlignment alignment;
public:
  FlexboxComponent(FlexboxAlignment alignment);

  void addFrame(FrameComponent* frame, int flex);
  void increaseCapacity(int capacity);

  static std::vector<FlexboxComponent*> getAllFlexboxes();
  void render(unsigned int shaderProgram, glm::mat4 projection);
};
