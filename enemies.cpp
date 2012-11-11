#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "enemies.h"

int alive[4][8];
int direction = 1;

void Enemies::generate(){
  for(int i = 0;i<4;i++){
    for(int j = 0;j<8;j++){
      alive[i][j] = 4;
    }
  }
  direction = 1;
}

void Enemies::draw_one(){
  glColor4f(1.0,0.0,0.0,1.0);
  glLineWidth(1);
  glBegin(GL_QUADS); 
  glVertex2f(0,0);
  glVertex2f(0,height);
  glVertex2f(width, height);
  glVertex2f(width,0);
  glEnd();
}

void Enemies::draw(){
  glPushMatrix();
  glTranslatef(x,y,0);
  for(int i = 0;i<4;i++){
    glTranslatef(0,-(this->height)-3,0);
    glPushMatrix();
    for(int j = 0;j<8;j++){
      glTranslatef(this->width+3,0,0);
      if(alive[i][j] > 0)
        draw_one();
    }
    glPopMatrix();
  }
  glPopMatrix();
}

void Enemies::update(){

  if(
      this->x <= 80 - (8*(this->width+3)) &&
      this->x >= -97 
    ){
    this->translateX(this->direction);
  }else{
    direction = -1 * direction;
    this->translateX(this->direction);
    this->translateY(-1);
  }
}

bool Enemies::collided(double fX, double fY){
  if(
      (this->x + 8*(this->width+3)+7 >= fX) && (this->x+7 < fX)
      && 
      ((this->y - 4*(this->height+3) <= fY) && (this->y-3 > fY))
    )
  {
    bool c = false;

    for(int i = 3 ; !c && i>=0 ; i--){
      int *r = alive[i];
      int xd = fX-this->x;
      int infx = xd - 10;
      int supx = xd + 10;
      int ix = xd/10;
      int iix = ix - 1;
      int six = ix - 1;

      if(r[ix] > 0){
        //Verifica colision
        if(
            fX > (this->x + (this->width+3)*ix)
            &&
            fX < (this->x + (this->width+3)*ix+7)
          )
        {
          r[ix-1] = 0;
          c = true;
          printf("%d %d -> %d\n",i,ix-1,alive[i][ix-1]);
          return true;
        }
      }else
        continue;
    }
    return false;
  }else 
    return false;
}

