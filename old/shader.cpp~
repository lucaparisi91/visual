#include "shader.h"

string readFile(string filename)
{
  ifstream file(filename.c_str());
  stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  string tmp=buffer.str();
  return tmp;
}
