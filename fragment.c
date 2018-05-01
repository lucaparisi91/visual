#version 330 core

out vec4 FragColor;

in vec3 colorPos;
in vec2 textCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
  //FragColor = vec4(colorPos,1.);  
  FragColor=texture(texture1,textCoord);
}
