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

class shadowsScene : public scene
{
public:
  shadowsScene() : scene("vertexPlain.c","fragmentPlain.c"),mainSphere(100,100)
  {
    setProgramDefault();
  }
  
 void render()
  {
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2,0.3,0.3,1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  } 

  void draw()
  {
    view = getViewMatrixCamera();
    model=glm::translate(identity,glm::vec3(0.0f,0.3f,1.f));
    model=glm::scale(model,glm::vec3(0.3f,0.3f,0.3f));
    applyModelViewProjection();
    mainSphere.draw();
    
  }
private:
  sphere mainSphere;
};

int main(int argc,char** argv)
{
  GLFWwindow * window;
  
  window=initWindow(800,600,"Lighting demo");
  
  shadowsScene scene1;
  
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
