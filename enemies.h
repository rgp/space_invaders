#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

class Enemies : public Element{
  public:
    Enemies(double xx, double xy, double xwidth, double xheight):Element(xx,xy,xwidth,xheight) {}

    int alive[4][8];
    double direction;
    int padding;
    void generate();
    void draw_one(int);
    void draw();
    bool update();
    int getIndexX(double);
    int getIndexY(double);
    bool collided(double,double);
    GLuint texName[6];
    Bullet* shoot(double x);
  private:
    Bullet* generateBullet(int,int);
};
