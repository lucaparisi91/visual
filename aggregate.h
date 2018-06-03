#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "texture.h"
#include "shapes.h"

class aggregate
{
  aggregate(shape &shape_,texture& texture_):shapeO(shape_),textureO(textureO_){};
  addShape( shapeO * shape){shapeO=&shape;}
  addTexture( textureO * shape){shapeO=&shape;}
  void bind(){shapeO->bind();textureO->bind();}
  void draw(){shapeO.draw();}
private:
  shape shapeO;
  texture textureO;
}
  
#endif
