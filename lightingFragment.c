#version 330 core

out vec4 FragColor;
in vec3 colorPos;
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform sampler2D textureSampler;

void main()
{
  float specularStrength=0.5;
  vec3 ambient=ambientStrength*lightColor;
  //vec3 lightDir = normalize(lightPosition - fragPos);
  vec3 lightDir = normalize(vec3(-0.1,0.1,0.2));
  float diff = max(dot(normal, lightDir), 0.0);
  
  //vec3 diffuse = lightColor*diff*vec3(texture(textureSampler,texCoord));
  vec3 diffuse = lightColor*diff;
  
  vec3 viewDir=normalize(viewPosition - fragPos);
  vec3 reflectDir=reflect(-lightDir,normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 42);
  vec3 specular = specularStrength * spec * lightColor;  
  
  FragColor=vec4(colorPos*(ambient+diffuse+specular),1);
  //FragColor=vec4(colorPos*(ambient+diffuse+specular),1)*texture(textureSampler,texCoord);
  
}
