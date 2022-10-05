#version 330 core
layout (location = 0) in vec4 stuff;

uniform mat4 projection;
out vec2 texCoords;

void main()
{
  gl_Position = projection * vec4(stuff.xy, 0.0, 1.0);
  texCoords = stuff.zw;
}
