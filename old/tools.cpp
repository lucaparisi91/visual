#include "tools.h"

unsigned int generateBufferVertex3D(vector<float> &vertices,int i)
{
  unsigned int VBN;
  glGenBuffers(1,&VBN);
  glBindBuffer(GL_ARRAY_BUFFER,VBN);
  glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),&vertices[0],GL_STATIC_DRAW);
  glVertexAttribPointer(i,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(i);
  return VBN;
}

unsigned int generateBufferVertex2D(vector<float> &vertices,int i)
{
  unsigned int VBN;
  glGenBuffers(1,&VBN);
  glBindBuffer(GL_ARRAY_BUFFER,VBN);
  glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),&vertices[0],GL_STATIC_DRAW);
  glVertexAttribPointer(i,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
  glEnableVertexAttribArray(i);
  return VBN;
}



unsigned int generateElementArray3D(vector<unsigned int> &vertices)
{
  unsigned int VBN;
  glGenBuffers(1,&VBN);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VBN);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,vertices.size()*sizeof(unsigned int),&vertices[0],GL_STATIC_DRAW);
  
  return VBN;
}

void changeDataBufferArray(unsigned int VBCS,vector<float> & colors)
{
    glBindBuffer(GL_ARRAY_BUFFER,VBCS);
    glBufferData(GL_ARRAY_BUFFER,colors.size()*sizeof(float),&colors[0],GL_STATIC_DRAW);
}


