//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 29/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <cstdlib>

#define RED 1
#define BLUE 2
#define GREEN 3
#define BLACK 4

GLfloat angle = 50, r =0;
GLfloat rotangle1=0.0, dt1=0.1;
GLfloat rotangle2=0.0, dt2=0.1;
float ax[3]={18,0,0}; float ay[3]={0,18,0}; float az[3]={0,0,18};//axes
float V1[3] ={0,0,0}; float V2[3] ={0,0,15};
GLfloat direction1[]={0,0,1};//the first teapot rotates around this direction
GLfloat red=0.0,green=0.0,blue=1.0;

void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}

void output_Text(float x, float y, float z, char *text)
{
    int len, i;
    glColor3f(0, 0, 0);
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

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



//
void DrawPoint()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glPointSize(20);
    double angle = 2 * 3.14 * r / 250;
    double xc = 15.9*cos(angle);
    double yc = 15.9*sin(angle);
    if (r!=0) glTranslated(xc,yc,0);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
    glPopMatrix();
}

void DrawDonut(void)
{
    glPushMatrix();
    //glTranslated(-2,0.5,0);
    //glRotated(rotangle1,0,1,0);
    glColor3f(1,1,0);
    glutWireTorus(4,10,20,20);
    glColor3f(red,green,blue);
    glutSolidTorus(4,10,20,20);
    glPopMatrix();
}

void draw_Circle()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i =0; i <= 500; i++)
    {
         double angle = 2 * 3.14 * i / 500;
         double x = 15.9*cos(angle);
         double y = 15.9*sin(angle);
         glVertex2d(x,y);
    }
    glEnd();
    glPopMatrix();
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
}
void myMove()
{
    glPushMatrix();
    glRotated(angle,0,1,0);
    DrawDonut();
    draw_Circle();
    DrawPoint();
    glPopMatrix();
}


void myDisplay(void)
{//clear the screen, increment the rotation angle, plot the teapot
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    myMove();
    r++;
    angle++;
    plot_Axis();
    output_Text(-5,-25,5,"Right click-menu");
    glutSwapBuffers();
}


void doNothing(void){}


void Menu_Color(int option)
{
    switch (option)
    {
        case RED:   red=1.0, green=0.0, blue=0.0; break;
        case BLUE:  red=0.0, green=0.0, blue=1.0; break;
        case GREEN: red=0.0, green=1.0, blue=0.0; break;
        case BLACK: red=0.0, green=0.0, blue=0.0; break;
    }

}

void createGLUTMenus()
{
    int menu = glutCreateMenu(Menu_Color);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


    
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(480,480);
    glutCreateWindow("Pre-exam | Problem 2");
    /* Use myInit2d() or myInit3d() for initialization */
    myInit3d();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    //glutSpecialFunc(SpecialKeys);
    createGLUTMenus();
    glutMainLoop();
}
