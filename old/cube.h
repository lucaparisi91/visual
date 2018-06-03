#include <vector>
using namespace std;

class cube
{
public:
  cube(float lx,float ly,float lz);
  void draw();
  void setColor(float rCol,float gCol,float bCol);
private:
  generateVertices();
  int iVertices;
  int iBufferVertices;
  
}
