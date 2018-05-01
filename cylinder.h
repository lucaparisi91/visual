#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include "shapes.h"
using namespace std;

class cylinder : public shape
{
public:
  cylinder(unsigned int tetasubdivisions_,unsigned int zsubdivisions_);
  
  
private:
  unsigned int tetasubdivisions;
  unsigned int zsubdivisions;
  
  
};

#endif
