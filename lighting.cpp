#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "shader.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include "camera.h"
#include "scene.h"
#include "toolsGL.h"
#include "sphere.h"
#include "circle.h"
#include "cylinder.h"
#include "square.h"

class lightingScene : public scene
{
  
public:
  
  lightingScene(string shaderVertexSource,string shaderFragmentSource) : scene::scene(shaderVertexSource,shaderFragmentSource),mainSphere(100,100),lamp(100,100),lampProgram("lightingLampVertex.c","lightingLampFragment.c"),circle1(100,100),cylinder1(100,100)
  {
    mainSphere.setColor(1.f,0.2f,0.3f);
    cylinder1.setColor(1.f,194/255.,45/255.);
    square1.setColor(48/255.,97./255.,21/255.);
    circle1.setColor(1,194/255.,45/255.);
    setProgram(lampProgram);
    lamp.setColor(1.f,1.0f,1.f);
    setProgramDefault();
    getBaseProgram().setVec3("lightColor",1.f,1.f,0.f);
    getBaseProgram().setFloat("ambientStrength",0.6);
    getBaseProgram().setVec3fv("viewPosition",glm::value_ptr(getCameraPos()));
    //mainSphere.setTexture(*new texture("sand.jpg"));
    
  }
  
  void render()
  {
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2,0.3,0.3,1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  }
  
  void processInput(GLFWwindow *window)
  {
    
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
	glfwSetWindowShouldClose(window, true);
      }
    
    scene::processInput(window);
    
  }
  
  void draw()
  {
    
    view = getViewMatrixCamera();
    
    // draw lamp

    model=glm::translate(identity,glm::vec3(0.0f,0.8*sin(getTime()),1.+0.6*cos(getTime()  )));
    model=glm::scale(model,glm::vec3(0.1f,0.1f,0.1f));
    setProgram(lampProgram);
    applyModelViewProjection();
    lamp.draw();
    
    setProgramDefault();
    // set the lighting
    getBaseProgram().setVec3fv("lightPosition",glm::value_ptr(model*glm::vec4(0.,0.,0.,1.)));
    
    model=glm::translate(identity,glm::vec3(0.0f,0.3f,1.f));
    model=glm::scale(model,glm::vec3(0.3f,0.3f,0.3f));
    applyModelViewProjection();
    mainSphere.draw();

    
    model=glm::translate(identity,glm::vec3(0.0f,0.3f,1.f));
    
    model=glm::rotate(model,(float)(M_PI/2.),glm::vec3(1.f,0.f,0.0f));
    model=glm::scale(model,glm::vec3(0.1f,0.1f,1.f));
    applyModelViewProjection();
    cylinder1.draw();
    // square

    model=glm::translate(identity,glm::vec3(0.0f,-0.5,0.f));
    model=glm::rotate(model,(float)(-M_PI/2.),glm::vec3(1.f,0.f,0.0f));
    model=glm::scale(model,glm::vec3(20.f,20.f,20.f));
    applyModelViewProjection();
    square1.draw();

    

    
    //set the light position at the center of the lamp object in world space
    
  }
  square square1;
  sphere mainSphere;
  sphere lamp;
  circle circle1;
  cylinder cylinder1;
  shader lampProgram;
};


int main(int argc,char** argv)
{
  GLFWwindow * window;
  
  window=initWindow(800,600,"Lighting demo");
  
  lightingScene scene1("lightingVertex.c","lightingFragment.c");
  
  while(!glfwWindowShouldClose(window))
    {
      scene1.processInput(window);
      scene1.render();
      scene1.draw();
      
      glfwSwapBuffers(window);
      glfwPollEvents();
      
    }
  
  closeWindow();
  
}
