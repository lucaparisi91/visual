#include "circle.h"

circle::circle(unsigned int tetasubdivisions_,unsigned int rsubdivisions_)
{
  tetasubdivisions=tetasubdivisions_;
  rsubdivisions=rsubdivisions_;
  vector<float> vertices;
  vector<float> normals;
  vector<float> colors;
  vector<unsigned int> indices;
  int nVertices=tetasubdivisions*rsubdivisions;
  int k=0;
  float teta,r;
  
  vertices.resize(3*nVertices);
  colors.resize(3*nVertices);
  normals.resize(3*nVertices);
  
  for(int j=1;j<=rsubdivisions;j++)
    {
      r=(float)j/rsubdivisions;
      for(int i=0;i<tetasubdivisions;i++)
	{
	  k=(j-1)*tetasubdivisions + i;
	  teta=i*2*M_PI/tetasubdivisions;
	  vertices[3*k]=cos(teta)*r;
	  vertices[3*k+1]=sin(teta)*r;
	  vertices[3*k+2]=0;
	  
	  normals[3*k+0]=0;
	  normals[3*k+1]=0;
	  normals[3*k+2]=1;

	  colors[3*k]=1.f;
	  colors[3*k+1]=1.f;
	  colors[3*k+2]=1.f;
	  
	 
	}

    } 
  
  indices.resize((rsubdivisions-1)*(tetasubdivisions)*6);
  k=0;
  int k1,k2,k3,k4;
  for(int j=1;j<rsubdivisions;j++)
    {
      for(int i=0;i<tetasubdivisions;i++)
	{
	  k1=(j-1)*tetasubdivisions + i;
	  k2=(j+1-1)*tetasubdivisions + i;
	  k3=(j-1)*tetasubdivisions + (i+1)%tetasubdivisions;
	  k4=(j+1-1)*tetasubdivisions + (i+1)%tetasubdivisions;
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


