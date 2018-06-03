#include "shapes.h"
#include "errorTools.h"

void shape::setVertices(vector<float> & vertices_)
{
  vertices=vertices_;
  glGenVertexArrays(1,&VAOS);
  glBindVertexArray(VAOS);
  // vertex elements
  VBOS=generateBufferVertex3D(vertices,0);
  
}

void shape::setIndices(vector<unsigned int> & indices_)
{
  indices=indices_;
  EBOS=generateElementArray3D(indices);
  
}

void shape::setColors(vector<float> & colors_)
{
  colors=colors_;
  glBindVertexArray(VAOS);
  VBCS=generateBufferVertex3D(colors,1);
  
}

void shape::setNormals(vector<float> & normals_)
{
  normals=normals_;
  glBindVertexArray(VAOS);
  VBN=generateBufferVertex3D(normals,2);
  
}

void shape::setColor(float rCol,float gCol,float bCol)
{
   
  for(int k=0;k<colors.size()/3;k++)
    {
      colors[3*k]=rCol;
      colors[3*k+1]=gCol;
      colors[3*k+2]=bCol;
	    
    }
  changeDataBufferArray(VBCS,colors);
}

void shape::draw()
{
  
  makeDrawing();
}

void textureShape::setTexture(texture & textureObject_,vector<float> & texCoords_)
{
  texCoords=texCoords_;
  glBindVertexArray(getIndexVertex());
  textureBufferId=generateBufferVertex2D(texCoords,3);
  setTex=true;
  textureObject=&textureObject_;
}

void shape::bind()
{
  
  glBindVertexArray(VAOS);
  
}

void textureShape::bind()
{
  
  shape::bind();
  if (setTex)
    {
      
      glBindBuffer(GL_ARRAY_BUFFER,textureBufferId);
      glActiveTexture(GL_TEXTURE0);
      
      textureObject->bind();
      
    }

  
}

void shape::makeDrawing()
{
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  

 
}

void textureShape::draw()
{
  
  makeDrawing();
  
    
}
