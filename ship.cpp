#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "ship.h"

#include <assert.h>

#include <fstream>

using namespace std;


void Ship::generate(){

  glGenTextures(6, this->texName); //Make room for our texture
  Image* image = loadBMP("images/ship.bmp");
  loadTexture(image,0,this->texName);
  delete image;

}
void Ship::draw(){
  glPushMatrix();
  glTranslatef(x,y+15,0);
  glColor4f(1.0,0.0,0.0,1.0);
  GLfloat ambientLight[] = {1.2f, 1.2f, 1.2f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

  GLfloat directedLight[] = {1.9f, 1.9f, 1.9f, 1.0f};
  GLfloat directedLightPos[] = {0.0f, 0.0f, 20.0f, 0.0f};
  glLightfv(GL_LIGHT1, GL_DIFFUSE, directedLight);
  glLightfv(GL_LIGHT1, GL_POSITION, directedLightPos);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE); 


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texName[0]);

  glPushMatrix();
  glBegin(GL_QUADS); 
    glTexCoord2f(0,1.0f);
  glVertex2f(0,0);
    glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,-this->height);
    glTexCoord2f(1.0f, 0.0f);
  glVertex2f(this->width,-this->height);
    glTexCoord2f(1.0f, 1.0f);
  glVertex2f(this->width,0);
  glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT1);
  glDisable(GL_NORMALIZE); 
  glPopMatrix();
}

Bullet* Ship::shoot(){
  return new Bullet(this->centerX(), this->centerY(), 2, 4);
}



