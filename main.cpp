/*
 * Space Inavers
 *
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "element.cpp"
#include "bullet.cpp"
#include "ship.cpp"
#include "enemies.cpp"
#include "bullet_node.cpp"
#include "bullet_observer.cpp"
#include "collider.cpp"
#include "collider_ship.cpp"
#include <assert.h>
#include <fstream>
#include "Imageloader.cpp"

using namespace std;

GLuint bg[1];
int score = 0;
int speed = 50;
int level = 0;
int lives = 3;
Enemies *enemies = new Enemies(-80,25,7,7);
Ship *ship = new Ship(0,-90,10,10);
BulletObserver *bulletObserver = new BulletObserver();
Collider *collider = new Collider(bulletObserver, enemies);
BulletObserver *enemiesBulletObserver = new BulletObserver();
ColliderShip *colliderShip = new ColliderShip(enemiesBulletObserver, ship);
int bulletYield = 0;
bool paused = false;

/*
 * Game Inicializer
 */
void initGame(){
  srand((unsigned)time(0));
  enemies->generate();

  glGenTextures(1, bg); //Make room for our texture
  Image* image = loadBMP("images/fondo.bmp");
  loadTexture(image,0,bg);
  delete image;
}

/*
 * Game Frame 
 *
 */
static void displayFrame(){

  GLfloat ambientLight[] = {1.2f, 1.2f, 1.2f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

  GLfloat directedLight[] = {1.9f, 1.9f, 1.9f, 1.0f};
  GLfloat directedLightPos[] = {0.0f, 0.0f, 20.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
  glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
  //glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE); 
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, bg[0]);

  glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-100,-100);
    glTexCoord2f(1.0f, 0.0f);
  glVertex2f(100,-100);
    glTexCoord2f(1.0f, 1.0f);
  glVertex2f(100,100);
    glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-100,100);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  //glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_NORMALIZE); 
  /*
  glColor4f(0.1,1.0,0.1,1.0);
  glLineWidth(10);
  glBegin(GL_LINE_STRIP); 
  glVertex2f(-100,-100);
  glVertex2f(-100,100);
  glVertex2f(100,100);
  glVertex2f(100,-100);
  glVertex2f(-100,-100);
  glEnd();

  */
}

/*
 * Timer Function
 *
 */
void myTimer( int valor)
{
  if(!paused){
    bulletObserver->update(10);
    enemiesBulletObserver->update(-1);
    if( lives >= 0 && !enemies->update()){
      glutTimerFunc(speed,myTimer,1);
      score += collider->checkForCollisions();
      //RESET
      if(score > 1 && score%20 == 0){
        //enemies = new Enemies(-80,25,7,7);
        //enemies->generate();
      }
      if(bulletYield == 0){
        enemiesBulletObserver->addBullet(enemies->shoot(ship->x));
        bulletYield = 20;
      }else
        bulletYield--;

      glutPostRedisplay(); 
      if(colliderShip->checkForCollisions() > 0)
        lives--;
    } 
  }else{ 
    //TODO
    //render pause
      glutPostRedisplay(); 
  }
}

/* 
 * Keyboar managment
 */
void specialKeyboard(int key, int mouseX, int mouseY){
  switch(key){
    case GLUT_KEY_RIGHT:
      ship->translateX(4);
      break;
    case GLUT_KEY_LEFT: 
      ship->translateX(-4);
      break;
  }
}
void key_shoot(unsigned char key, int mouseX, int mouseY){

  switch(key){
    case ' ':
      if(bulletObserver->isEmpty()){
        Bullet *bullet = ship->shoot();
        bulletObserver->setBullet(bullet);
      }
      break;
  }
}

void displayCoordinates(){
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  if (bulletObserver->bulletList != NULL){ 
    Bullet *bullet = bulletObserver->bulletList->bullet;
    glRasterPos2f(75,-75);
    stringstream ss;
    ss << "x:" << bullet->x;
    string label = ss.str();
    for(int i =0; i< label.length(); i++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);

    glRasterPos2f(75,-80);
    stringstream sss;
    sss << "y: " << bullet->y;
    string label2 = sss.str();
    for(int i =0; i< label2.length(); i++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label2[i]);
  }
}

void displayLives(){
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glRasterPos2f(34.5, 34);
  stringstream ss;
  ss <<(lives >= 0 ? lives : 0);
  string label = ss.str();

  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, label[i]);
}
void displayScore(){
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glRasterPos2f(-25, 34);
  stringstream ss;
  ss << score;
  string label = ss.str();

  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, label[i]);
}

/*
 *
 * Bob Ross
 *
 */
void display(){
  glClearColor(44,51,34,1);
  glClearColor(0,0,0,1);
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  displayFrame();
  enemies->draw();
  ship->draw();
  bulletObserver->draw();
  enemiesBulletObserver->draw();
  displayScore();
  displayCoordinates();
  displayLives();
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(600,600); 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Space Invaders"); 
  glOrtho(-100, 100, -100, 100, -100, 100);
  initGame();
  glutDisplayFunc(display); 
  glutKeyboardUpFunc(key_shoot);
  glutTimerFunc(speed,myTimer,1);
  glutSpecialFunc(specialKeyboard);

  glutMainLoop();
  return EXIT_SUCCESS;
}
