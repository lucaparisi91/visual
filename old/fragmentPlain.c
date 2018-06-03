#version 330 core

out vec4 FragColor;
in vec3 colorPos;

void main()
{
  FragColor=vec4(colorPos,1);
}
