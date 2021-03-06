#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <cstdlib>
#include "stb_image.h"
#include <string>

using namespace std;

class texture
{
public:
  
  texture(string name)
  {
    data = stbi_load(name.c_str(), &width, &height, &nChannels, 0);
    if (not data)
      {
	printf("Error in loading data");
	exit(1);
      }
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  };
  
  int const getId(){return id;} ;
  
  ~texture(){stbi_image_free(data);}
  
public:
  unsigned int id;
  int width,height,nChannels;
  unsigned char* data;
};

#endif
