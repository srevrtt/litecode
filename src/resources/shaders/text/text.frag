#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D texture0;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture0, texCoords).r);
  fragColor = vec4(1.0, 1.0, 1.0, 1.0) * sampled;
}
