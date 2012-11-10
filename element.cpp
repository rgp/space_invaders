#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "element.h"

Element::Element(double xx, double xy, double xwidth, double xheight) {
  x = xx;
  y = xy;
  width = xwidth;
  height = xheight;
}

bool Element::collided(double fX, double fY){
  if ((this->x + this->width > fX) && (this->x < fX)
      && ((this->y + this->height > fY) && (this->y < fY)))
  {
    return true;
  }else 
    return false;
}

void Element::translateX(double deltaX){
  x += deltaX;
}

void Element::translateY(double deltaY){
  y += deltaY;
}

void Element::draw(){
  glColor4f(0.0,0.0,0.5,1.0);
  glLineWidth(1);
  glBegin(GL_QUADS); 
    glVertex2f(x,y);
    glVertex2f(x,y+height);
    glVertex2f(x+width, y+height);
    glVertex2f(x+width,y);
  glEnd();
}

double Element::centerX(){
  return this->x + (this->width)/2;
}

double Element::centerY(){
  return this->y + (this->height)/2;
}
