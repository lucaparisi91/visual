#ifndef SHAPES_H
#define SHAPES_H


#include <vector>
#include <glad/glad.h>
#include "tools.h"
#include "textures.h"


using namespace std;
class shape
{
public:
  void setVertices(vector<float> & vertices);
  void setIndices(vector<unsigned int> & indices);
  void setColors(vector<float> & colors);
  void setNormals(vector<float> & normals);
  void setColor(float rCol,float gCol,float bCol);
  void draw();
  
  vector<float> & getNormals(){return normals;};
  vector<float> & getVertices(){return vertices;};
  vector<unsigned int > getIndices(){return indices;}
  
  virtual bool isTexture(){return false;}
  virtual void bind();
  unsigned int getIndexVertex(){return VAOS;};
  void makeDrawing();
protected:
  
private:
  vector<float> vertices;
  vector<float> colors;
  vector<unsigned int> indices;
  vector<float> normals;
  
  unsigned int VAOS;
  unsigned int VBOS;
  unsigned int VBCS;
  unsigned int EBOS;
  unsigned int VBN;
  
};

class textureShape : public shape
{
public:
  textureShape() : shape() {setTex=false;}
  virtual bool isTexture(){return true;};
  void setTexture(texture & textureObject,vector<float> & texCoords_);
  bool isTexture() const
  {
    return setTex;
  }
  virtual void draw();
  virtual void bind();
private:
  texture* textureObject;
  bool setTex;
  vector<float> texCoords;
  unsigned int textureBufferId; 
};

#endif
