#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

string readFile(string filename);

class shader
{
public:
  unsigned int id;
  shader(){id=0;}
  shader(string vertexShaderFile,string fragmentShaderFile)
     {
       // compile vertex shader
       string tmpText;
       const char * vertexShaderSource;
       unsigned int vertexShader;
       tmpText=readFile(vertexShaderFile);
       vertexShaderSource=tmpText.c_str();
       //cout<< vertexShaderSource <<endl;
       
       vertexShader=glCreateShader(GL_VERTEX_SHADER);
       glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
       glCompileShader(vertexShader);
       
       int succes;
       char infoLog[512];
       glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&succes);
       
       if(!succes)
	 {
	   glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
	   std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	   exit(1);
	 }

       
       // compile fragment shader
       unsigned int fragmentShader;
       const char * fragmentShaderSource;
       tmpText=readFile(fragmentShaderFile);
       fragmentShaderSource=tmpText.c_str();
       fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
       glCompileShader(fragmentShader);
       
       glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&succes);
  
       if(!succes)
	 {
	   glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
	   std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	   exit(1);
	 }
       // Linking program
       unsigned int shaderProgram;
       
       shaderProgram=glCreateProgram();
       glAttachShader(shaderProgram,vertexShader);
       glAttachShader(shaderProgram,fragmentShader);
       glLinkProgram(shaderProgram);
       
       glGetProgramiv(shaderProgram,GL_LINK_STATUS,&succes);
       if(!succes)
	 {
	   glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
	   std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
	   exit(1);
	 }
       
       glDeleteShader(vertexShader);
       glDeleteShader(fragmentShader);
       
       id=shaderProgram;
       
     }
  
  void use()
  {
    glUseProgram(id);
  }
  
  void setInt(string name,int value) const
  {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
  }

  void setFloat(string name,float value) const
  {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
  }
  
  void setVec3(string name,float value1,float value2,float value3) const
  {
    glUniform3f(glGetUniformLocation(id, name.c_str()), value1,value2,value3);
  }
  void setVec3fv(string name,const GLfloat * value) const
  {
    glUniform3fv(glGetUniformLocation(id, name.c_str()),1,value );
  }
  
  void setMatrix4fv(string name,const GLfloat * value) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,value);
  }
  
  void setBool(string name,bool value) const
  {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
  }
  
};

#endif
