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

  this->padding = 10;

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
      this->x <= (95 - this->full_width) &&
      this->x >= -95 
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
      (this->x + this->full_width >= fX) && (this->x <= fX)
      && 
      ((this->y - this->full_height <= fY) && (this->y >= fY))
     )
  {
    int _x = (fX - this->x)/(this->width+this->padding);
    if(fX >= _x * (this->width+this->padding)+ this->x &&
        fX <= _x * (this->width+this->padding)+ this->x + this->width
      ){
      int _y = (fY - (this->y - this->full_height))/(this->height+this->padding);
        _y = 3 - _y;
      if(
          fY >= (this->y - _y*(this->height+this->padding))
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

Bullet* Enemies::generateBullet(int i, int j){
    int x = this->x + (j* (this->width+this->padding));
    int y = this->y - (i* (this->height+this->padding));
    return new Bullet(x,y,1,3);
}

Bullet* Enemies::shoot(){
  srand((unsigned)time(0));

  for(int k=0;k<32;k++){
    int i = rand()%4;
    int j = rand()%8;
    if(alive[i][j] != 0)
      return generateBullet(i,j);
  }

  if (rand()%2 == 0){
    for(int i = 1;i<4;i++)
      for(int j = 1;j<8;j++)
        if(alive[i][j] != 0) 
          return generateBullet(i,j);
  }else{
    for(int i = 3;i>1;i--)
      for(int j = 7;j>1;j--)
        if(alive[i][j] != 0) 
          return generateBullet(i,j);
  }
  return NULL;
}

