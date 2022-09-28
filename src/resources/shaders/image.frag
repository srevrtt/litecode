#version 330 core

in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D texture0;

void main()
{
  vec4 tex = texture(texture0, textureCoords);
  
  if (tex.a < 0.1)
    discard;

  fragColor = tex;
}
