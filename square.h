#include <vector>
#include "shapes.h"
#include "textures.h"
using namespace std;

class square : public textureShape
{
public:
  
  square();
  void setTexture(texture & textureObject);
};
