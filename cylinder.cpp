#include "cylinder.h"

cylinder::cylinder(unsigned int tetasubdivisions_,unsigned int zsubdivisions_)
{
  tetasubdivisions=tetasubdivisions_;
  zsubdivisions=zsubdivisions_;
  vector<float> vertices;
  vector<float> normals;
  vector<float> colors;
  vector<unsigned int> indices;
  int nVertices=tetasubdivisions*zsubdivisions;
  int k=0;
  float teta,r;
  
  vertices.resize(3*nVertices);
  colors.resize(3*nVertices);
  normals.resize(3*nVertices);
  
  for(int j=0;j<zsubdivisions;j++)
    {
      r=1.;
      for(int i=0;i<tetasubdivisions;i++)
	{
	  k=j*tetasubdivisions + i;
	  teta=i*2*M_PI/tetasubdivisions;
	  vertices[3*k]=cos(teta)*r;
	  vertices[3*k+1]=sin(teta)*r;
	  vertices[3*k+2]=j*1.f/(zsubdivisions-1)-0.5;
	  
	  normals[3*k+0]=r*cos(teta);
	  normals[3*k+1]=r*sin(teta);
	  normals[3*k+2]=0;
	  
	  colors[3*k]=1.f;
	  colors[3*k+1]=1.f;
	  colors[3*k+2]=1.f;
	  
	 
	}

    } 
  
  indices.resize((zsubdivisions-1)*(tetasubdivisions)*6);
  k=0;
  int k1,k2,k3,k4;
  for(int j=0;j<zsubdivisions-1;j++)
    {
      for(int i=0;i<tetasubdivisions;i++)
	{
	  k1=j*tetasubdivisions + i;
	  k2=(j+1)*tetasubdivisions + i;
	  k3=(j)*tetasubdivisions + (i+1)%tetasubdivisions;
	  k4=(j+1)*tetasubdivisions + (i+1)%tetasubdivisions;
	  indices[6*k]=k1;
	  indices[6*k+1]=k3;
	  indices[6*k+2]=k2;
	  indices[6*k+3]=k3;
	  indices[6*k+4]=k4;
	  indices[6*k+5]=k2;
	  k++;
	  
	}
      
    }
  
  setVertices(vertices);
  setIndices(indices);
  setColors(colors);
  setNormals(normals);
  
}


