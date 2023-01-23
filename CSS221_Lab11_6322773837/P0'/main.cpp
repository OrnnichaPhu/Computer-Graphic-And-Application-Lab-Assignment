//
//  main.cpp
//  P0'
//
//  Created by Ornnicha Phueaksri on 22/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define nmax 4
GLfloat ang=0,dang=1; //the rotation angle and the increment
float r[nmax];float g[nmax];float b[nmax]; //nmax colors for nmax vertices.
void output_Text(float x, float y, float z, char *text) //output a text at x,y
{  int len, i;
  glColor3f(0, 0, 0); //black
  glRasterPos3f(x, y, z);
  len = (int)strlen(text);
  for (i = 0; i < len; i++) {
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
  }
}
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //reset the current Projection Matrix
    gluPerspective(45, 1.33, .01, 1000);//perspective view
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);// position and aim the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();// reset the current Modelview Matrix
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
    glShadeModel(GL_SMOOTH);//smooth shades (mix colors)
}
void draw_Polygon(GLfloat R, GLint N)
{ GLfloat x, y; GLint i;
   glPushMatrix();
   glRotatef(ang,0,0,1);
   glBegin(GL_POLYGON);
for (i=0;i<=N-1;i++)
{
    x=R*cos(2*M_PI*i/N);
    y=R*sin(2*M_PI*i/N);
    glColor3f(r[i],g[i],b[i]);
    glVertex3f(x,y,0);
}
    glEnd();
glPopMatrix();
}
void myDisplay(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   output_Text(5,0,20,"Left click to change the colors");
   ang=ang+dang;
   draw_Polygon(15,4);
   glutSwapBuffers();
   Time_Delay(10);
}

void myMouse(int button, int state, int x, int y){
    int i;
    if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN){
        for (i=0;i<=nmax-1;i++){//change r,g,b randomly for each vertex  if the left-mouse has been clicked
            r[i]=rand()%1000/1000.;
            g[i]=rand()%1000/1000.;
            b[i]=rand()%1000/1000.;
        }
    }  
    }
int main(int argc, char **argv)
{
   srand(time(0));//necessary to initialize rand()
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Problem 0':Square Smooth shades. Random colors");
   myInit3d();
   glutDisplayFunc(myDisplay);
   glutIdleFunc(myDisplay);
  glutMouseFunc(myMouse);
   glutMainLoop();
}
