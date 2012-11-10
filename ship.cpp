#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "ship.h"

Bullet* Ship::shoot(){
  return new Bullet(this->centerX(), this->centerY());
}



