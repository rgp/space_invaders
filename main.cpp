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
int bulletYieldIndex = 0;
bool paused = true;
bool init = true;
bool levelUpeado = true;

/*
 * Game Inicializer
 */
void initGame(){
  srand((unsigned)time(0));
  enemies->generate();
  ship->generate();

  glGenTextures(1, bg); //Make room for our texture
  Image* image = loadBMP("images/fondo.bmp");
  loadTexture(image,0,bg);
  delete image;
}

void resetElements(){ 
  enemies = new Enemies(-80,25,7,7);
  collider = new Collider(bulletObserver, enemies);
  colliderShip = new ColliderShip(enemiesBulletObserver, ship);
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
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_NORMALIZE); 
}

bool dead(){
  return (lives < 0);
}
void levelUp(){
  level++;
  if(speed > 20) 
    speed-=10; 

  if(bulletYieldIndex < 19) 
    bulletYieldIndex--;
  resetElements();
  enemies->generate();
}
/*
 * Timer Function
 *
 */
void myTimer( int valor)
{
  if(!paused && !init){
    bulletObserver->update(10);
    enemiesBulletObserver->update(-1);
    if( !dead() && !enemies->update()){
      glutTimerFunc(speed,myTimer,1);
      int scum = score;
      score += collider->checkForCollisions();
      if(score > scum)
        levelUpeado = false;
      //RESET
      if(score > 1 && score%320 == 0 && !levelUpeado){
        levelUp();
        levelUpeado = true;
      }
      if(bulletYield == 0){
        enemiesBulletObserver->addBullet(enemies->shoot(ship->x));
        bulletYield = 20 - bulletYieldIndex;
      }else
        bulletYield--;

      if(colliderShip->checkForCollisions() > 0)
        lives--;
    }
  }else{ 
    //TODO
    //render pause
    glutTimerFunc(speed,myTimer,1);
  }
  glutPostRedisplay(); 
}

/* 
 * Keyboar managment
 */
void specialKeyboard(int key, int mouseX, int mouseY){
  if(!paused){
    switch(key){
      case GLUT_KEY_RIGHT:
        ship->translateX(4);
        break;
      case GLUT_KEY_LEFT: 
        ship->translateX(-4);
        break;
    }
  }
}
void key_shoot(unsigned char key, int mouseX, int mouseY){

  switch(key){
    case ' ':
      if(!paused){
        if(bulletObserver->isEmpty()){
          Bullet *bullet = ship->shoot();
          bulletObserver->setBullet(bullet);
        }
      }
      break;
    case 's':
      if(init)
        init = false;
      else
        break;
    case 'p':
    case 'P':
      paused = !paused;
      break;
  }
}

void displayGameOver(){
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glRasterPos2f(-20, -30);
  string label = "GAME OVER!!!";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
}

void displayPause(){
  glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
  glBegin(GL_QUADS); 
  glVertex2f(-100,-100);
  glVertex2f(100,-100);
  glVertex2f(100,100);
  glVertex2f(-100,100);
  glEnd();

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glRasterPos2f(-5, -20);
  string label = "PAUSE";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
}

void displayWelcome(){
  glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
  glBegin(GL_QUADS); 
  glVertex2f(-100,-100);
  glVertex2f(100,-100);
  glVertex2f(100,100);
  glVertex2f(-100,100);
  glEnd();

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glRasterPos2f(-30, 0);
  string label = "PRESS s to START!";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
  glRasterPos2f(-35, -15);
  label = "<- Moves LEFT";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
  glRasterPos2f(-35, -25);
  label = "-> Moves RIGHT";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
  glRasterPos2f(-35, -35);
  label = "SPACE shoots bullets into space";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
  glRasterPos2f(-35, -45);
  label = "P pauses the game";
  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
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
  ss <<(!dead() ? lives : 0);
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
  if ( dead()){
    displayGameOver();
  } else {
    enemies->draw();
    ship->draw();
    bulletObserver->draw();
    enemiesBulletObserver->draw();
    displayCoordinates();
  }
  displayScore();
  displayLives();
  if(paused && !init)
    displayPause();
  if(init)
    displayWelcome();
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
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glutDisplayFunc(display); 
  glutKeyboardUpFunc(key_shoot);
  glutTimerFunc(speed,myTimer,1);
  glutSpecialFunc(specialKeyboard);

  glutMainLoop();
  return EXIT_SUCCESS;
}
