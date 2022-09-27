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
int lastFlex = 0;

// Creates a new Flexbox Frame
FlexboxFrame::FlexboxFrame(int x, int y, int r, int g, int b, unsigned int width, unsigned int height, int flex)
{
  // set position
  this->x = x;
  this->y = y;

  // set color
  this->r = r;
  this->g = g;
  this->b = b;

  // set width & height
  this->width = width;
  this->height = height;

  // set flex parameter
  this->flex = flex;
}

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
void FlexboxComponent::addFrame(FrameComponent* frame, int flex)
{
  // calculate width & height
  int newWidth = 1280;
  int newHeight = 720 / numFrames;

  // calculate position
  int newX = 0;
  int newY = currentFrame * newHeight;

  // FLEXBOX
  if (flex > 0)
  {
    if (currentFrame == 1)
    {
      float modifier = (1.0f / (float)flex) * 2;

      frames[0]->height = modifier * newHeight;
      newHeight = 720 - frames[0]->height;
      newY = frames[0]->height;
    }
  }

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
  FlexboxFrame* newFrame = new FlexboxFrame(newX, newY, frameColor[0], frameColor[1], frameColor[2], newWidth, newHeight, 1);
  frames.push_back(newFrame);

  frame->isChild = true;
  lastFlex = flex;

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
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 color;

    // apply translation to x, y position, corner allignment, and offset to the height to exclude the titlebar
    model = glm::translate(model, glm::vec3(frame->x + (frame->width / 2), frame->y + (frame->height / 2), 0.0f));
    model = glm::scale(model, glm::vec3(frame->width, frame->height, 0.0f)); // scale to the width and height

    // get the color
    color = glm::vec3(frame->r, frame->g, frame->b);

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
