#include "cube.h"

cube::cube(float lx_,float ly_,float lz_)
{
  lx=lx_;
  ly=ly_;
  lz=lz_;
}

generateCirconferenceVertices(float radius,int subdivisions,vector<float> & vertices)
{
  float teta=2*M_PI/subdivisions;
  for(int i=0;i<subdivisions;i++)
    {
      
      vertices[3*i]=cos(i*teta)*radius;
      vertices[3*i+1]=sin(i*teta)*radius;
      vertices[3*i+2]=0;
      
    }
}
