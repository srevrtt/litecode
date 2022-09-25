#include <iostream>
#include <string>
#include <vector>

#include "include/flexbox.hpp"
#include "include/frame.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

std::vector<FlexboxComponent*> flexboxes;

// Creates a new flexbox component
FlexboxComponent::FlexboxComponent(FlexboxAlignment alignment)
{
  this->alignment = alignment;
}

// Increases the maximum number of frames
void FlexboxComponent::increaseCapacity(int capacity)
{
  numFrames += capacity;
}

// Appends a frame to the flexbox
void FlexboxComponent::addFrame(FrameComponent* frame)
{
  // calculate width & height
  int newWidth = 1280;
  int newHeight = 720 / numFrames;

  // calculate position
  int newX = 0;
  int newY = (currentFrame * newHeight);

  switch (alignment)
  {
  case FB_ALIGNMENT_VERTICAL:
    newWidth = 1280 / numFrames;
    newHeight = 720;
    newX = (currentFrame * newWidth);
    newY = 0;

    break;
  }

  // get the previous frame's color
  std::vector<int> frameColor = frame->getColor();

  // create a copy of the frame and append it to the frames list
  FrameComponent* newFrame = new FrameComponent(newX, newY, newWidth, newHeight, frameColor[0], frameColor[1], frameColor[2]);
  newFrame->isChild = true;
  frames.push_back(newFrame);

  frame->isChild = true;

  // create a clone of this component for rendering
  flexboxes.push_back(this);
  currentFrame++;
}

// Draws the flexbox's components onto the renderer
void FlexboxComponent::render(unsigned int shaderProgram, glm::mat4 projection)
{
  // get each frame
  for (auto& frame : frames)
  {
    // get information of the frame
    std::vector<int> transformations = frame->getSizeAndPosition();
    std::vector<int> colorArr = frame->getColor();
    
    // shorten the process of getting the position & size
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

// Gets all of the flexboxes
std::vector<FlexboxComponent*> FlexboxComponent::getAllFlexboxes()
{
  return flexboxes;
}
