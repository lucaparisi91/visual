#ifndef CAMERA_H
#define CAMERA_H

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

const unsigned int FORWARD=0;
const unsigned int BACKWARD=1;
const unsigned int RIGHTWARD=2;
const unsigned int LEFTWARD=3;
const unsigned int UPWARD=4;
const unsigned int DOWNARD=5;


glm::vec3 cartesianDirection(float Yaw,float Pitch);

glm::vec3 eulerDirection(const glm::vec3 & v,float & Yaw,float & Pitch);

class camera
{
public:
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  glm::vec3 cameraRight;
  glm::vec3 cameraTarget;
  float Yaw;
  float Pitch;
  
  glm::mat4 viewMatrix;
  
  float cameraSpeed;
  float rotateSpeed;
  glm::mat4 identity;
  
  glm::vec3 getPos(){return cameraPos;}
  
  camera(glm::vec3 cameraPos_,glm::vec3 cameraFront_,glm::vec3 cameraUp_)
  {
    identity=glm::mat4(1.0f);
    cameraPos=cameraPos_;
    cameraFront=glm::normalize(cameraFront_);
    eulerDirection(cameraFront,Yaw,Pitch);
    cameraUp=glm::normalize(cameraUp_);
    cameraSpeed=3;
    rotateSpeed=1;
  }
  
  glm::mat4 getViewMatrix()
  {
    return glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
  }
  
  void rotateDirection(float Yaw2,float Pitch2)
  {
    cameraTarget=cameraPos + cameraFront;
    Yaw+=Yaw2;
    Pitch+=Pitch2;
    cameraFront=cartesianDirection(Yaw,Pitch);
    cameraRight= glm::normalize(glm::cross(cameraFront, cameraUp));
    cameraUp= glm::normalize(glm::cross(cameraRight, cameraFront));
  }

  void rotatez(float amount)
  {
    cameraTarget=cameraPos + cameraFront;
    glm::mat4 rot=glm::rotate(identity,amount,cameraUp);
    cameraFront=rot*glm::vec4(cameraFront,1.);
    cameraPos=cameraTarget-cameraFront;
  }
  void move(unsigned int direction,float amount)
  {
    if (direction==FORWARD)
      cameraPos += amount * cameraFront;
    if (direction==BACKWARD)
      cameraPos -= amount * cameraFront;
    if (direction==RIGHTWARD)
      cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * amount;
    if (direction==LEFTWARD)
      cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * amount;
    
    if (direction==UPWARD)
      cameraPos -= cameraUp * amount;
    if (direction==DOWNARD)
      cameraPos += cameraUp * amount;
    
  }

  float filterPitch(float pitch2)
  {
     if(pitch2 > 89.0f)
       pitch2 = 89.0f;
     if(pitch2 < -89.0f)
       pitch2 = -89.0f;
     return pitch2;
  }
  
  void processInput(GLFWwindow *window,float deltaTime)
  {
    float angle;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
      {
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	  {
	    rotateDirection(0,filterPitch(-rotateSpeed*deltaTime));
	  }
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	  {
	    rotateDirection(0,filterPitch(rotateSpeed*deltaTime));
	  }
	  
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	  {
	    rotateDirection(-rotateSpeed*deltaTime,0);
	  }
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	  {
	  rotateDirection(rotateSpeed*deltaTime,0);
	  }
	
	
      }
    else
      {
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) or (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) ) 
	  {
	    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	      move(FORWARD,cameraSpeed*deltaTime);
	    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	      move(BACKWARD,cameraSpeed*deltaTime);
	  }
	else
	  {
	    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      move(UPWARD,cameraSpeed*deltaTime);
	    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	      move(DOWNARD,cameraSpeed*deltaTime);
	  }
	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	  move(RIGHTWARD,cameraSpeed*deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	  move(LEFTWARD,cameraSpeed*deltaTime);
      }
     
    
    
        
  }
  
};

#endif
