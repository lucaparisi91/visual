#include "toolsGL.h"
#include "scene.h"
#include <iostream>

scene::scene(string shaderVertexSource,string shaderFragmentSource) : cam1(glm::vec3(0,1.9,-3),glm::vec3(0,-1.3,3),glm::vec3(0,1,0)),baseProgram(shaderVertexSource,shaderFragmentSource)
{
  
  if ( windowSpace::widthScreen==0 or windowSpace::heightScreen==0)
    {
      cout << "Error in the screen dimensions." << endl;
      exit(1);
    }
  identity=glm::mat4(1.0f);
  projection=glm::perspective(glm::radians(45.0f),(float)windowSpace::widthScreen/(float)windowSpace::heightScreen,0.1f,100.0f);
  view = cam1.getViewMatrix();
  
  baseProgram.use();
  
  setProgram(baseProgram);
}

void scene::setProgram(shader& program)
{
  currentProgram=&program;
  currentProgram->use();
}

void scene::setProgramDefault()
{
  currentProgram=&baseProgram;
  currentProgram->use();
}

scene::~scene()
{
  
}

glm::mat4 scene::getViewMatrixCamera()
{
  return cam1.getViewMatrix();
}

void scene::processInput(GLFWwindow * window)
{
  timeFrame=glfwGetTime();
  cam1.processInput(window,timeFrame-timeLastFrame);
  timeLastFrame=timeFrame;
}

void scene::applyModelViewProjection()
{
  currentProgram->setMatrix4fv("view",glm::value_ptr(view));
  currentProgram->setMatrix4fv("model",glm::value_ptr(model));
  currentProgram->setMatrix4fv("projection",glm::value_ptr(projection));
}

float scene::getTime()
{
  return timeFrame;
}
