#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include "shapes.h"
using namespace std;

class circle : public shape
{
public:
  circle(unsigned int tetasubdivisions_,unsigned int rsubdivisions_);
  
private:
  unsigned int tetasubdivisions;
  unsigned int rsubdivisions;
  
  
};

#endif
