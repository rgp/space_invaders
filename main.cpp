#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

/* GLUT callback Handlers */
int speed = 50;

double shipPosition=0.0;

double racketWidthTolerance=0.01;

GLfloat vertices [ ][3] =
{{-1.0, -1.0, -1.0},  { 1.0, -1.0, -1.0},
  { 1.0,  1.0, -1.0},  {-1.0,  1.0, -1.0},
  {-1.0, -1.0,  1.0},  { 1.0, -1.0,  1.0},
  { 1.0,  1.0,  1.0},  {-1.0,  1.0,  1.0}
};

GLfloat colores [ ][3] =
{{0.0, 0.0, 0.0},   {1.0, 0.0, 0.0},
  {1.0, 1.0, 0.0},   {0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0},   {1.0, 0.0, 1.0},
  {1.0, 1.0, 1.0},   {0.0, 1.0, 1.0}
};

GLubyte indicesCubo[24] = {0,3,2,1,
                         2,3,7,6,
                         0,4,7,3,
                         1,2,6,5,
                         4,5,6,7,
                         0,1,5,4
                        };

static void displayShip(){
    glColor4f(1,0.0,0.0,1.0);
    glPushMatrix();
      glScalef(0.05,0.05,0.05);
      glTranslatef( shipPosition/0.2, -18, 0);
      glDrawElements( GL_QUADS,24, GL_UNSIGNED_BYTE, indicesCubo );
    glPopMatrix();

}

static void displayFrame(){
    glColor4f(0.0,0.0,0.5,1.0);
    glLineWidth(10);
    glBegin(GL_LINE_STRIP); 
    glVertex2f(-1,-1);
    glVertex2f(-1,1);
    glVertex2f(1,1);
    glVertex2f(1,-1);
    glVertex2f(-1,-1);
    glEnd();

}
static void display(void)
{
    glClearColor(0.44,0.51,0.34,1);//DEFINE EL COLOR DEL FONDO DE TU PANTALLA
    glClear(GL_COLOR_BUFFER_BIT);
    displayFrame();
    displayShip();
    glutSwapBuffers();//por defaul invoca al glFlush();
}
void myTimer( int valor)
{
  glutTimerFunc(speed,myTimer,1);
  glutPostRedisplay(); 
}

void updateShip(int dir){
  shipPosition += dir*0.05;
}

void specialKeyboard(int key, int mouseX, int mouseY){
  switch(key){
    case GLUT_KEY_RIGHT:
      updateShip(1);
      break;
    case GLUT_KEY_LEFT: 
      updateShip(-1);
      break;
  }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800); 
    glutInitWindowPosition(10,10); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Space Invaders"); 
    glutDisplayFunc(display); 
    glutTimerFunc(speed,myTimer,1);
    glutSpecialFunc(specialKeyboard);

    // Declarar el arreglo de vértices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Declarar el arreglo de colores
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colores);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutMainLoop();
    return EXIT_SUCCESS;
}
