#pragma once

#include <string>
#include <vector>
#include "frame.hpp"
#include <glm/glm.hpp>

class FlexboxComponent
{
private:
  std::vector<FrameComponent*> frames{};
  int numFrames = 0;
  int currentFrame = 0;
public:
  void addFrame(FrameComponent* frame);
  void increaseCapacity(int capacity);

  static std::vector<FlexboxComponent*> getAllFlexboxes();
  void render(unsigned int shaderProgram, glm::mat4 projection);
};
