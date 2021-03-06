#include "toolsGL.h"
namespace windowSpace
{
  int widthScreen;
  int heightScreen;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
  
  windowSpace::widthScreen=width;
  windowSpace::heightScreen=height;
  glViewport(0, 0, width, height);
  
}

GLFWwindow* initWindow(int widthScreen,int heightScreen,string title)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
  GLFWwindow*  window = glfwCreateWindow(widthScreen, heightScreen, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
      {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return NULL;
      }
    glfwMakeContextCurrent(window);
  
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return NULL;
      }
    
    glViewport(0, 0, widthScreen, heightScreen);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    windowSpace::widthScreen=widthScreen;
    windowSpace::heightScreen=heightScreen;
    
    return window;
    
}

void closeWindow()
{
  glfwTerminate();
}
