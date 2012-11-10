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
#include "element.cpp"
#include "bullet.cpp"
#include "ship.cpp"
#include "bullet_node.cpp"
#include "bullet_observer.cpp"

using namespace std;

int speed = 50;
Ship *ship = new Ship(0,-95,10,10);
BulletObserver *bulletObserver = new BulletObserver();

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
  bulletObserver->update();
  glutPostRedisplay(); 
}

/* 
 * Keyboar managment
 */
void specialKeyboard(int key, int mouseX, int mouseY){
  switch(key){
    case GLUT_KEY_RIGHT:
      ship->translateX(1);
      break;
    case GLUT_KEY_LEFT: 
      ship->translateX(-1);
      break;
  }
}
void keyboard(unsigned char key, int mouseX, int mouseY){
  
  switch(key){
    case ' ':
      Bullet *bullet = ship->shoot();
      bulletObserver->addBullet(bullet);
      break;
  }
}

/*
 *
 * Bob Ross
 *
 */
void display(){
  glClearColor(44,51,34,1);
  glClear(GL_COLOR_BUFFER_BIT);
  displayFrame();
  ship->draw();
  bulletObserver->draw();
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Space Invaders"); 
    glOrtho(-100, 100, -100, 100, -100, 100);
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
    glutTimerFunc(speed,myTimer,1);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();
    return EXIT_SUCCESS;
}
