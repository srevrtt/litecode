#include <iostream>
#include <string>
#include <vector>

#include "include/flexbox.hpp"
#include "include/frame.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

std::vector<Flexbox> flexboxes;

void FlexboxComponent::increaseCapacity()
{
  numFrames++;
}

void FlexboxComponent::addFrame(FrameComponent* frame)
{
  int newWidth = 1280 / numFrames;
  int newHeight = 720;

  int newX = newX = (currentFrame * newWidth);
  int newY = 0;

  std::cout << newX << ',' << newY << ',' << newWidth << ',' << newHeight << '\n';

  std::vector<int> frameColor = frame->getColor();
  FrameComponent* newFrame = new FrameComponent(newX, newY, newWidth, newHeight, frameColor[0], frameColor[1], frameColor[2]);

  frames.push_back(newFrame);

  Flexbox clone{};
  clone.frames = frames;
  clone.numFrames = numFrames;
  flexboxes.push_back(clone);

  currentFrame++;
  delete frame;
}

void Flexbox::render(unsigned int shaderProgram, glm::mat4 projection)
{
  for (auto& frame : frames)
  {
    std::vector<int> transformations = frame->getSizeAndPosition();
    std::vector<int> colorArr = frame->getColor();

    int x = transformations[0];
    int y = transformations[1];
    int width = transformations[2];
    int height = transformations[3];

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 color;

    // apply translation to x, y position, corner allignment, and offset to the height to exclude the titlebar
    model = glm::translate(model, glm::vec3(x + (width / 2), y + (height / 2), 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 0.0f)); // scale to the width and height

    // get the color
    color = glm::vec3(colorArr[0], colorArr[1], colorArr[2]);

    // get locations of uniform variables inside the shaders
    int modelLocation = glGetUniformLocation(shaderProgram, "model");
    int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
    int colorLocation = glGetUniformLocation(shaderProgram, "color");

    // apply the transformations
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    // apply the color
    glUniform3fv(colorLocation, 1, glm::value_ptr(color));

    // draw it!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

std::vector<Flexbox> FlexboxComponent::getAllFlexboxes()
{
  return flexboxes;
}
