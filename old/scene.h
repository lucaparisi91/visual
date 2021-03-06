#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "shader.h"

class scene
{
public:
  scene(string shaderVertexSource,string shaderFragmentSource);
  void applyModelViewProjection();
  
  ~scene();
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;
  glm::mat4 identity;
  
  void setProgram(shader& program);
  void setProgramDefault();
  
  void processInput(GLFWwindow* window);
  glm::mat4 getViewMatrixCamera();
  
  shader& getBaseProgram(){return baseProgram;}

  float getTime();
  
  glm::vec3 getCameraPos(){return cam1.getPos();}
  
  
private:
  float timeFrame;
  float timeLastFrame;
  camera cam1;
  
  shader baseProgram;
  shader* currentProgram;
  
};

#endif
