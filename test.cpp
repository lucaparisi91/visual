#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "shader.h"
#include "stb_image.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include "camera.h"

using namespace std;

//-----------------------------PROGRAM STATES---------------
unsigned int triangleVAO;
shader triangleProgram;
shader sphereProgram;
unsigned int texture1;
unsigned int texture2;

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 identity;

int widthScreen=800;
int heightScreen=600;

float timeLastFrame;
float timeFrame;

camera cam1(glm::vec3(0,1.9,-3),glm::vec3(0,-1.3,3),glm::vec3(0,1,0));

//---------------------------------------------------
void processInput(GLFWwindow *window)
{
  timeFrame=glfwGetTime();
  
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
    }
  
  cam1.processInput(window,timeFrame-timeLastFrame);
  timeLastFrame=timeFrame;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  widthScreen=800;
  heightScreen=600;
  glViewport(0, 0, width, height);
  
  triangleProgram.setMatrix4fv("projection",glm::value_ptr(projection));
}  

int makeTexture(string filename)
{
  // load image
  int width,height,nrChannels;
  unsigned char* data=stbi_load(filename.c_str(),&width,&height,&nrChannels,0);
  unsigned int texture;

  if (not data)
    {
      std::cout << "Could not load the texture "<<filename << std::endl;
      return 0;
    }
  
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  stbi_image_free(data);
  return texture;
  
}

void render()
{
  glEnable(GL_DEPTH_TEST);  
  
  glClearColor(0.,0.,0.,1.);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
}


void drawBox()
{
  
  glm::mat4 face1=glm::rotate(model,glm::radians(-90.0f),glm::vec3(1.f,0.f,0.f));

  glm::mat4 face2=glm::translate(model,glm::vec3(-0.5,0.5,0));
  face2=glm::rotate(face2,glm::radians(-90.0f),glm::vec3(0.f,1.f,0.f));

  glm::mat4 face3=glm::translate(model,glm::vec3(0.5,0.5,0));
  face3=glm::rotate(face3,glm::radians(-90.0f),glm::vec3(0.f,1.f,0.f));

  glm::mat4 face4=glm::translate(model,glm::vec3(0,0.5,-0.5));

  glm::mat4 face5=glm::translate(model,glm::vec3(0,1,0));
  face5=glm::rotate(face5,glm::radians(-90.0f),glm::vec3(1.f,0.f,0.f));
  
  triangleProgram.setMatrix4fv("model",glm::value_ptr(face1));
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  triangleProgram.setMatrix4fv("model",glm::value_ptr(face2));
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  triangleProgram.setMatrix4fv("model",glm::value_ptr(face3));
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  triangleProgram.setMatrix4fv("model",glm::value_ptr(face4));
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  triangleProgram.setMatrix4fv("model",glm::value_ptr(face5));
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  
}


class object
{
public:
  
  
  
};

class sphere : public object
{
 public:
  
  unsigned int VAOS;
  unsigned int VBOS;
  unsigned int VBCS;
  unsigned int EBOS;
  unsigned int radialSubDivisions;
  unsigned int zSubDivisions;
  unsigned int d;
  vector<float> vertices;
  vector<unsigned int> indices; // indices that define the quadrilaters
  vector<float> colors;
  sphere(){};

  
  sphere(unsigned int radialSubDivisions_,unsigned int zSubDivisions_)
  {
    int nVertices;
    int k;
    float phi;
    float teta;
    // create vertices
    radialSubDivisions=radialSubDivisions_;
    zSubDivisions=zSubDivisions_;
    nVertices=radialSubDivisions*zSubDivisions;
    vertices.resize(radialSubDivisions*zSubDivisions*3);
    indices.resize(radialSubDivisions*(zSubDivisions-1)*6);
    colors.resize(nVertices*3);
    
    
    for(int j=1;j<=zSubDivisions;j++)
      {
	for(int i=0;i<radialSubDivisions;i++)
	  {
	    k=(j-1)*radialSubDivisions+i;
	    teta=i*2.*M_PI/radialSubDivisions;
	    phi=j*M_PI/(zSubDivisions+1.);
	    vertices[3*k]=cos(teta)*sin(phi);
	    vertices[3*k+1]=sin(teta)*sin(phi);
	    vertices[3*k+2]=cos(phi);
	    //colors[3*k]=232/255.;
	    //colors[3*k+1]=130/255.;
	    //colors[3*k+2]=48/255.;

	    colors[3*k]=1.f;
	    colors[3*k+1]=1.f;
	    colors[3*k+2]=1.f;
	    
	    k++;
	  }
      }
    // defines the ordered quadrilaters to draw
    k=0;
    for(int j=2;j<=zSubDivisions;j++)
      {
	for(int i=1;i<radialSubDivisions;i++)
	  {
	    // first half
	    indices[6*k]=(j-2)*radialSubDivisions+i-1;
	    indices[6*k+1]=(j-2)*radialSubDivisions+i;
	    indices[6*k+2]=(j-1)*radialSubDivisions+i-1;
	    //second half
	    indices[6*k+3]=(j-1)*radialSubDivisions+i-1;
	    indices[6*k+4]=(j-2)*radialSubDivisions+i;
	    indices[6*k+5]=(j-1)*radialSubDivisions+i;
	    k++;
	  }
	// last quad to close the circle strip
	indices[6*k]=(j-2)*radialSubDivisions+radialSubDivisions-1;
	indices[6*k+1]=(j-2)*radialSubDivisions;
	indices[6*k+2]=(j-1)*radialSubDivisions+radialSubDivisions-1;
	indices[6*k+3]=(j-1)*radialSubDivisions+radialSubDivisions-1;
	indices[6*k+4]=(j-2)*radialSubDivisions;
	indices[6*k+5]=(j-1)*radialSubDivisions;
	k++;
      }
    
    // ------------------------------generate buffers
    glGenVertexArrays(1,&VAOS);
    glBindVertexArray(VAOS);

    // vertex elements
    glGenBuffers(1,&VBOS);
    glBindBuffer(GL_ARRAY_BUFFER,VBOS);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    // ------------------------------------------quads
    
    glGenBuffers(1,&EBOS);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBOS);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(float),&indices[0],GL_STATIC_DRAW);

    //------------------colors
    
    glGenBuffers(1,&VBCS);
    glBindBuffer(GL_ARRAY_BUFFER,VBCS);
    glBufferData(GL_ARRAY_BUFFER,colors.size()*sizeof(float),&colors[0],GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(1);
  }

  void draw()
  {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAOS);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
  }
  
};

// creates the shader object

sphere sphere1;

void draw()
{
  triangleProgram.use();
  
  view=cam1.getViewMatrix();
  
  triangleProgram.setMatrix4fv("view",glm::value_ptr(view));
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glBindVertexArray(triangleVAO);
  //glDrawArrays(GL_TRIANGLES,0,3);
  
  model=glm::rotate(identity,(float)glfwGetTime() * glm::radians(50.0f),glm::vec3(0.f,1.f,0.f));
  
  drawBox();
  model=glm::translate(identity,glm::vec3(0.0f,0.3f,0.0f));
  model=glm::scale(model,glm::vec3(0.2f,0.2f,0.2f));
  sphereProgram.use();
  sphereProgram.setMatrix4fv("view",glm::value_ptr(view));
  sphereProgram.setMatrix4fv("model",glm::value_ptr(model));
  sphere1.draw();
}


unsigned int makeTriangle()
{
  // Linking vertex attributes
  
  float vertices[] = {-0.5,-0.5,0,0.5,-0.5,0,-0.5,0.5,0,0.5,0.5,0};
  
  float colors[]={1,0.5,0.2,1,0.5,0.2,1,0.5,0.2,1,0.5,0.2};
  
  unsigned int indices[]={0,1,2,1,3,2};

  float textCoords[]={0,0,1,0,0,1,1,1};
  
  unsigned int VBO;
  unsigned int VAO;
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  // vertex elements
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  
  // buffer elements
  unsigned int EBO;
  glGenBuffers(1,&EBO);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

  // color elements

  unsigned int VBC;
  glGenBuffers(1,&VBC);
  glBindBuffer(GL_ARRAY_BUFFER,VBC);
  glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(1);

  
  // texture coordinates
  unsigned int VBT;
  glGenBuffers(1,&VBT);
  glBindBuffer(GL_ARRAY_BUFFER,VBT);
  glBufferData(GL_ARRAY_BUFFER,sizeof(textCoords),textCoords,GL_STATIC_DRAW);
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
  glEnableVertexAttribArray(2);
  
  return VAO;
}

unsigned int makeTriangle2()
{
  // Linking vertex attributes
  
  float vertices[] = {0.5,-0.5,0,0,0.5,0,0.8,0.5,0};
  
  unsigned int indices[]={0,1,2};
  
  unsigned int VBO;
  unsigned int VAO;
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);
  
  // vertex elements
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

  // buffer elements
  unsigned int EBO;
  glGenBuffers(1,&EBO);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
   
  
  return VAO;
}


void init()
{
  
  triangleProgram=shader("vertex.c","fragment.c");
  sphereProgram=shader("sphereVertex.c","fragmentSphere.c");
  triangleProgram.use();
  triangleVAO=makeTriangle();
  texture1=makeTexture("container.jpg");
  texture2=makeTexture("awesomeface.png");
  triangleProgram.setInt("texture1",0);
  triangleProgram.setInt("texture2",1);
  
  
  //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  projection=glm::perspective(glm::radians(45.0f),(float)widthScreen/(float)heightScreen,0.1f,100.0f);
  
  //view = glm::translate(view, glm::vec3(-0.2f, -0.8f, -3.0f));
  view = cam1.getViewMatrix();
  triangleProgram.setMatrix4fv("model",glm::value_ptr(model));
  triangleProgram.setMatrix4fv("view",glm::value_ptr(view));
  triangleProgram.setMatrix4fv("projection",glm::value_ptr(projection));
  
  sphereProgram.use();
  sphereProgram.setMatrix4fv("model",glm::value_ptr(model));
  sphereProgram.setMatrix4fv("view",glm::value_ptr(view));
  sphereProgram.setMatrix4fv("projection",glm::value_ptr(projection));
  sphere1=sphere(100,100);
  
  
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
}

// init a new main session
int main(int argc,char** argv)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(widthScreen, heightScreen, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }
  glfwMakeContextCurrent(window);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
    }
  
  glViewport(0, 0, widthScreen, heightScreen);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  init();
  
  while(!glfwWindowShouldClose(window))
    {
      processInput(window);
      render();
      draw();
      glfwSwapBuffers(window);
      glfwPollEvents();    
    }

  glfwTerminate();
  return 0;
}
