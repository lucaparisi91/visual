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
  
  lightingScene(string shaderVertexSource,string shaderFragmentSource) : scene(shaderVertexSource,shaderFragmentSource)
  {
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
    
    model=glm::translate(identity,glm::vec3(0.0f,0.8*sin(getTime()),1.+0.6*cos(getTime()  )));
    model=glm::scale(model,glm::vec3(0.1f,0.1f,0.1f));
    
    applyModelViewProjection();
    
  }
private:
  square s1;
};


int main(int argc,char** argv)
{
  GLFWwindow * window;
  
  window=initWindow(800,600,"Lighting demo");

   // build and compile our shader program
    // ------------------------------------
    // vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
    string vertexProgram=readFile("vertex.c").c_str()
    glShaderSource(vertexShader, 1, , NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,readFile("fragment.c").c_str(), NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

  
  //lightingScene scene1("vertex.c","fragment.c");
  
  float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
  
  unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
  
  while(!glfwWindowShouldClose(window))
    {
      scene1.processInput(window);
      scene1.render();
      //scene1.draw();

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      glfwSwapBuffers(window);
      glfwPollEvents();
      
    }
  
  closeWindow();
  
}
