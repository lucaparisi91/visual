#ifndef TOOLSERROR_H
#define TOOLSERROR_H

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
#ifdef DEBUG
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#else
#define glCheckError()
#endif

GLenum glCheckError_(const char *file, int line);


#endif
