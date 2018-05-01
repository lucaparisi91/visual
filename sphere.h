#include <vector>
#include "textures.h"
#include "shapes.h"
using namespace std;

class sphere : public textureShape
{
 public:
  
  sphere(unsigned int radialSubDivisions_,unsigned int zSubDivisions_);
  
  void setTexture(texture& textureObject_);
  
private:
  bool setTex;
  string textureFile;
  unsigned int textureBufferId;
  ;
  unsigned int radialSubDivisions;
  unsigned int zSubDivisions;
  unsigned int d;
  vector<float> vertices;
  vector<float> normals;
  
  vector<unsigned int> indices; // indices that define the quadrilaters
  vector<float> colors;
  vector<float> texCoords;
  
  texture* textureObject;
  
};
