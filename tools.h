#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <glad/glad.h>
#include <vector>
using namespace std;

unsigned int generateBufferVertex3D(vector<float> &vertices,int i);

unsigned int generateElementArray3D(vector<unsigned int> &vertices);

void changeDataBufferArray(unsigned int i,vector<float> & colors);
unsigned int generateBufferVertex2D(vector<float> &vertices,int i);
#endif
