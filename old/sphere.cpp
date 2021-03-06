#include "sphere.h"
#include <cmath>
#include <glad/glad.h>
#include "tools.h"

sphere::sphere(unsigned int radialSubDivisions_,unsigned int zSubDivisions_)
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
    normals.resize(nVertices*3);
    
    float normalization;
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
	    
	    
	    normals[3*k]=vertices[3*k];
	    normals[3*k+1]=vertices[3*k+1];
	    normals[3*k+2]=vertices[3*k+2];
	    
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
	// last quad close the circle strip
	indices[6*k]=(j-2)*radialSubDivisions+radialSubDivisions-1;
	indices[6*k+1]=(j-2)*radialSubDivisions;
	indices[6*k+2]=(j-1)*radialSubDivisions+radialSubDivisions-1;
	indices[6*k+3]=(j-1)*radialSubDivisions+radialSubDivisions-1;
	indices[6*k+4]=(j-2)*radialSubDivisions;
	indices[6*k+5]=(j-1)*radialSubDivisions;
	k++;
      }
    
    // ------------------------------generate buffers
    
    setVertices(vertices);
    setIndices(indices);
    setColors(colors);
    setNormals(normals);
  }

/*
void sphere::setColor(float rCol,float gCol,float bCol)
{
  
  for(int k=0;k<colors.size()/3;k++)
    {
      colors[3*k]=rCol;
      colors[3*k+1]=gCol;
      colors[3*k+2]=bCol;
	    
    }
  
  glBindBuffer(GL_ARRAY_BUFFER,VBCS);
  glBufferData(GL_ARRAY_BUFFER,colors.size()*sizeof(float),&colors[0],GL_STATIC_DRAW);
  
}


void sphere::draw()
  {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (isTexture())
      {
	glBindBuffer(GL_ARRAY_BUFFER,textureBufferId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureObject->getId());
      }
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
  }
*/




void sphere::setTexture(texture& textureObject_)
{
 
  textureObject=&textureObject_;
  vector<float> & normals=getNormals();
  texCoords.resize(normals.size()/3*2);
  // set tex coords based on normals
  for(int i=0;i<normals.size()/3;i++)
    {
      texCoords[2*i]=asin(normals[3*i])/M_PI + 0.5;
      texCoords[2*i+1]=asin(normals[3*i+1])/M_PI + 0.5;
    }
  
  textureShape::setTexture(textureObject_,texCoords);
  
}
