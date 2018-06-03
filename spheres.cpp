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
  
  lightingScene(string shaderVertexSource,string shaderFragmentSource) : scene::scene(shaderVertexSource,shaderFragmentSource),mainSphere(100,100)
  {
    mainSphere.setColor(1.f,0.2f,0.3f);
    
    setProgramDefault();
    
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
    applyModelViewProjection();
    mainSphere.draw();
    
    

    
    //set the light position at the center of the lamp object in world space
    
  }
  
  sphere mainSphere;
  
};

int main(int argc,char** argv)
{
  GLFWwindow * window;
  
  window=initWindow(800,600,"Lighting demo");
  
  lightingScene scene1("vertex.c","fragment.c");
  
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
