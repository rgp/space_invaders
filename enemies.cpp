#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "enemies.h"


void Enemies::generate(){
  for(int i = 0;i<4;i++){
    for(int j = 0;j<8;j++){
      this->alive[i][j] = 4;
    }
  }
  this->direction = 0.7;

  this->padding = 7;

  this->full_width = 8*this->width + 7*this->padding;
  this->full_height = 4*this->height + 3*this->padding;
}

void Enemies::draw_one(){
  glColor4f(1.0,0.0,0.0,1.0);
  glLineWidth(1);
  glBegin(GL_QUADS); 
  glVertex2f(0,0);
  glVertex2f(0,this->height);
  glVertex2f(width, this->height);
  glVertex2f(this->width,0);
  glEnd();
}

void Enemies::draw(){
  glPushMatrix();
  glTranslatef(x,y,0);
  for(int i = 0;i<4;i++){
    glPushMatrix();
    glTranslatef(0,-i*(this->height+this->padding),0);
    for(int j = 0;j<8;j++){
      glPushMatrix();
      glTranslatef(j*(this->width+this->padding),0,0);
      if(this->alive[i][j] > 0)
        draw_one();
      glPopMatrix();
    }
    glPopMatrix();
  }
  glPopMatrix();
}

void Enemies::update(){

  if(
      this->x <= (90 - this->full_width) &&
      this->x >= -90 
    ){
    this->translateX(this->direction);
  }else{
    this->direction = -1 * this->direction;
    this->translateX(this->direction);
    this->translateY(-1);
  }
}

int Enemies::getIndexX(double fX){
  int ind = (fX - this->x)/(this->width+this->padding);
  int a = ind*(this->width+this->padding)+this->x;
  if(fX > a && fX < + this->width){
    return ind;
  }else{
    return -1;
  }
}

int Enemies::getIndexY(double fY){
  return (this->y-fY)/(this->width+this->padding);
}

bool Enemies::collided(double fX, double fY){
  if (
      (this->x + this->full_width > fX) && (this->x < fX)
      && 
      ((this->y - this->full_height < fY) && (this->y > fY))
     )
  {
    int _x = (fX - this->x)/(this->width+this->padding);
    if(fX > _x * (this->width+this->padding)+ this->x &&
        fX < _x * (this->width+this->padding)+ this->x + this->width
      ){
      int _y = (fY - (this->y - this->full_height))/(this->height+this->padding);
        _y = 3 - _y;
      if(
          fY > this->y - _y*(this->height+this->padding) - this->height
        ){
        if(this->alive[_y][_x] > 0){
          this->alive[_y][_x] = 0;
          return true;
        }
      }
    }
  }
  return false;
}
