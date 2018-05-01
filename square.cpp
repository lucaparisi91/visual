#include "square.h"

square::square()
{
  static const float vertices1[] ={-0.5,-0.5,0,0.5,-0.5,0,0.5,0.5,0,-0.5,0.5,0};

  static const float colors1[]={1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};
  static const float normals1[]={0.,0.,1.,0.,0.,1.,0.,0.,1.,0.,0.,1.};
  
  static const int indices1[]={0,1,3,3,1,2};

  vector<float> vertices(vertices1,vertices1 + 12 );
  vector<float> colors(colors1,colors1 + 12 );
  vector<unsigned int> indices(indices1,indices1 + 12 );
  vector<float> normals(normals1,normals1 + 12 );
  setVertices(vertices);
  setColors(colors);
  setIndices(indices);
  setNormals(normals);
}
