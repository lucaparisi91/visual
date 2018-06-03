#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "square.h"
#include "toolsGL.h"
#include "tools.h"
#include <iostream>
#include "shader.h"
#include <string>
#include "scene.h"
using namespace std;


class demoScene : public scene
{
public:
  demoScene(string vertexShader,string fragmentShader) : scene(vertexShader,fragmentShader){}
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
    s1.draw();
  }
private:
  square s1;
  
};

int main()
{
  GLFWwindow* window =initWindow(800,600,"square");
    
  demoScene scene("vertex.c","fragment.c");
  
  square s1;
  while (!glfwWindowShouldClose(window))
    {
        
      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      
        
	
      s1.draw();
      
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    closeWindow();
    
    return 0;
}

