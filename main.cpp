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

using namespace std;

int score = 0;
int speed = 50;
Enemies *enemies = new Enemies(-90,80,7,7);
Ship *ship = new Ship(0,-90,10,10);
BulletObserver *bulletObserver = new BulletObserver();
Collider *collider = new Collider(bulletObserver, enemies);

/*
 * Game Inicializer
 */
void initGame(){
  enemies->generate();
}

/*
 * Game Frame 
 *
 */
static void displayFrame(){
  glColor4f(0.0,0.0,0.5,1.0);
  glLineWidth(10);
  glBegin(GL_LINE_STRIP); 
  glVertex2f(-100,-100);
  glVertex2f(-100,100);
  glVertex2f(100,100);
  glVertex2f(100,-100);
  glVertex2f(-100,-100);
  glEnd();

}

/*
 * Timer Function
 *
 */
void myTimer( int valor)
{
  glutTimerFunc(speed,myTimer,1);
  enemies->update();
  bulletObserver->update();
  score += collider->checkForCollisions();
  glutPostRedisplay(); 
}

/* 
 * Keyboar managment
 */
void specialKeyboard(int key, int mouseX, int mouseY){
  switch(key){
    case GLUT_KEY_RIGHT:
      ship->translateX(7);
      break;
    case GLUT_KEY_LEFT: 
      ship->translateX(-7);
      break;
  }
}
void key_shoot(unsigned char key, int mouseX, int mouseY){

  switch(key){
    case ' ':
      Bullet *bullet = ship->shoot();
      bulletObserver->addBullet(bullet);
      break;
  }
}

void displayScore(){
  stringstream ss;
  ss << "Score: " <<score;
  string label = ss.str();

  for(int i =0; i< label.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
}

/*
 *
 * Bob Ross
 *
 */
void display(){
  glClearColor(44,51,34,1);
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);
  displayFrame();
  ship->draw();
  enemies->draw();
  bulletObserver->draw();
  glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  glRasterPos2f(-90, 90);
  displayScore();
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
