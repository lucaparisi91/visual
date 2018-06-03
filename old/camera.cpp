#include "camera.h"

glm::vec3 cartesianDirection(float Yaw,float Pitch)
{
  glm::vec3 v;
  v.x = cos(Yaw) * cos(Pitch);
  v.y = sin(Pitch);
  v.z = sin(Yaw) * cos(Pitch);
  return v;
  
}

void eulerDirection(const glm::vec3 & v,float & Yaw,float & Pitch)
{
  Pitch = asin(v.y);
  if (v.x!=0)
    Yaw =  atan(v.z/v.x);
  else
    Yaw=M_PI/2;
}
