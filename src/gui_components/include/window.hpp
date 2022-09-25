#pragma once

#include <glm/glm.hpp>
#include "frame.hpp"

#ifdef _WIN32
#include "../../platform/windows/include/win_window.hpp"
#include "../../platform/windows/include/win_opengl.hpp"
#endif

class Window
{
private:
#ifdef _WIN32
  Windows_Window* window;
#endif
  unsigned int shaderProgram;
  unsigned int vao;
  glm::mat4 projection;
public:
  Window(unsigned int width, unsigned int height, std::string title);
  void run();

  void addFrames(std::vector<FrameComponent*> frames);
};
