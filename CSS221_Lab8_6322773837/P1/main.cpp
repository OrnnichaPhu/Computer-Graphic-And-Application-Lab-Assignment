//
//  main.cpp
//  P1
//
//  Created by Ornnicha Phueaksri on 22/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


float angle=0, dangle=1.0;
bool click=false;
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
float ax[3]={25,0,0}; float ay[3]={0,25,0}; float az[3]={0,0,25};//axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
     glVertex3fv(v1);
     glVertex3fv(v2);
     glEnd();
    }
void plot_Vector(float v[3]) //plot vector
{
float zero[3]={0,0,0};
plot_Arrow(zero,v);
}
void plot_Axis()
{
glColor3f(0,0,0);
plot_Vector(ax);
plot_Vector(ay);
plot_Vector(az);
}
void myInit2d(void)
{
    glClearColor(1.0,1.0,1.0,0.0);     // set white background color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluOrtho2D(-50.0, 50.0, -60.0, 60.0);//set your coordinate system
    //the coordinate system and window in your assigment can be different
    glMatrixMode(GL_MODELVIEW);       //set some additional parameters
    glLoadIdentity();
    }

void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluPerspective(45, 1.33, .01, 1000);
        //the coordinate system, the window and glLookAt in your assigment
        //can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void myTeaPot()
{
glPushMatrix();
glRotated(angle,0,1,0);
glutWireTeapot(10.0);  //draw the teapot again as the wireframe
glPopMatrix();
angle+=dangle;
}


void Draw_Triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3d(0,22,15);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3d(0,12,0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3d(18,22,0);
    glEnd();
}

void myDisplay(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // implement this part to draw objects...for example...
   glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
   glRecti(10,10,20,20);//draw a red rectangle
   glColor3f(0.0, 0.0, 1.0);          // set the drawing color blue
   myTeaPot();
    Draw_Triangle();
   plot_Axis();
   glutSwapBuffers();
   Time_Delay(50);
}
void doNothing(void)
{
}
// implement this reshape callback if needed...
void myReshape (int w, int h)
{
}
// implement this mouse callback if needed...
void myMouse(int button, int state, int x, int y)
{
if ((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)) click=!click;
if (click) glutIdleFunc(myDisplay); else glutIdleFunc(doNothing);
}
// implement this keyboard callback if needed...
void myKeyboard(unsigned char key, int x, int y)
{
}
// implement this motion callback if needed...
void myMotion(int x, int y)
{
}
int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("OpenGL program");
   /* Use myInit2d() or myInit3d() for initialization */
   //myInit2d();
   myInit3d();
   glutDisplayFunc(myDisplay);
   glutReshapeFunc(myReshape);
   glutIdleFunc(myDisplay);
   glutMouseFunc(myMouse);
   glutKeyboardFunc(myKeyboard);
   glutMotionFunc(myMotion);
   glutMainLoop();
}
