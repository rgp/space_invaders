#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "enemies.h"

#include <assert.h>
#include <fstream>

#include "imageloader.cpp"

using namespace std;


void Enemies::generate(){
  for(int i = 0;i<4;i++){
    for(int j = 0;j<8;j++){
      this->alive[i][j] = i+1;
    }
  }
  this->direction = 0.7;

  this->padding = 10;

  this->full_width = 8*this->width + 7*this->padding;
  this->full_height = 4*this->height + 3*this->padding;

  glGenTextures(6, this->texName); //Make room for our texture
  Image* image = loadBMP("images/aliens1.bmp");
  loadTexture(image,0,this->texName);
  image = loadBMP("images/aliens2.bmp");
  loadTexture(image,1,this->texName);
  image = loadBMP("images/aliens3.bmp");
  loadTexture(image,2,this->texName);
  image = loadBMP("images/aliens4.bmp");
  loadTexture(image,3,this->texName);
  image = loadBMP("images/aliens5.bmp");
  loadTexture(image,4,this->texName);
  image = loadBMP("images/aliens6.bmp");
  loadTexture(image,5,this->texName);

  delete image;
  
}

void Enemies::draw_one(int a){
  //glColor4f(1.0,0.0,0.0,1.0);
  //glLineWidth(1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texName[a]);

  glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,0);
    glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0,this->height);
    glTexCoord2f(1.0f, 1.0f);
  glVertex2f(this->width, this->height);
    glTexCoord2f(1.0f, 0.0f);
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
        draw_one(this->alive[i][j]);
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
