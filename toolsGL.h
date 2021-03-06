#ifndef TOOLSGL_H
#define TOOLSGL_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

// window global variables
namespace windowSpace
{
  extern int widthScreen;
  extern int heightScreen;
}

using namespace std;
GLFWwindow* initWindow(int widthScreen,int heightScreen,string title);

void closeWindow();

#endif
