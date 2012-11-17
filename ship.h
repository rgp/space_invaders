#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

class Ship : public Element{
  public:
    Ship(double xx, double xy, double xwidth, double xheight):Element(xx,xy,xwidth,xheight) {}
    GLuint texName[6];
    Bullet* shoot();
    void generate();
    void draw();
};
