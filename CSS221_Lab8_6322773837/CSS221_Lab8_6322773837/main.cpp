//
//  main.cpp
//  CSS221_Lab8_6322773837
//
//  Created by Ornnicha Phueaksri on 22/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

bool roz = false, rox = false;

float t1=0, dt1=0.1;
float t2=0, dt2=0.1;
float trajectoryx1(float t)
{
    return t;
}
float trajectoryy1(float t)
{
    return t;
}
float trajectoryx2(float t)
{
    return 0;
}
float trajectoryy2(float t)
{
    return t;
}

GLfloat x,y,z;
GLfloat Pi=M_PI;
GLfloat shiftx,shifty,shiftz,shift;
GLfloat t=0, dt=0.01;
GLfloat angle1=0;
GLfloat angle2=0;
bool rotate=false;
bool move=true;

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

GLfloat angle=0,dangle=1;
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}


void myInit2d(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.33, .01, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void draw_Origin()
{
    glColor3f(1,0,1);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
}

void Draw_Rectangle()
{
    glBegin(GL_QUADS);
    glVertex3d(10,10,0);
    glVertex3d(20,10,0);
    glVertex3d(20,20,0);
    glVertex3d(10,20,0);
    glEnd();
}

void Draw_Blade()
{
    glColor3f(0.9,0.9,0.9);
    glRecti(2,-1,7,1);
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex3d(0,1,0);
    glVertex3d(7,1,0);
    glVertex3d(7,-1,0);
    glVertex3d(2,-1,0);
    glVertex3d(2,1,0);
    glEnd();
}
void DrawTrajectory()
{
GLfloat t,dt;
glColor3d(0,0,1);
dt=0.01;
glBegin(GL_POINTS);
for (t=0;t<=12*Pi;t+=dt)
{x=sin(t);
y=cos(t);
z=t/5;
glVertex3d(x,y,z);}
glEnd();
}

void Draw_allBlades()
{

    shiftx=sin(t);
    shifty=cos(t);
    shiftz=t/5;

    glPushMatrix();
   
    glTranslated(shiftx,shifty,shiftz);
    if (rotate) {
        if((rox)){glRotated(angle1,1,0,0); angle1++;} else glRotated(angle,1,0,0);
        if((roz)){glRotated(angle2,0,0,1); angle2++;} else glRotated(angle,0,0,1);
      
    }
    glRecti(-1,-1,1,1);
    
    glPopMatrix();
    
    
}




void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_Axis();
    DrawTrajectory();
    glColor3f(1.0, 0.0, 0.0);
    Draw_allBlades();
    t+=dt;
    if ((t>=12*Pi)||(t<0)) dt=-dt;
    glutSwapBuffers();
    Time_Delay(50);
}


void Do_Nothing(void)
{
}

void mouse(int button, int state, int x, int y)
{
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (rotate) {rotate=false; if(rox) rotate=true;} else rotate=true;
        if(roz)  roz =false; else {roz =true; rotate = true;}
        if (move) glutIdleFunc(myDisplay); else glutIdleFunc(Do_Nothing);
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        {
            if (rotate) {rotate=false; if(roz) rotate=true;} else rotate=true;
            if(rox) rox =false; else {rox =true; rotate =true;}
        if (move) glutIdleFunc(myDisplay); else glutIdleFunc(Do_Nothing);
        }
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Problem 7");
    /* Use myInit2d() or myInit3d() for initialization */
    //myInit2d();
    myInit3d();
    glutDisplayFunc(myDisplay);
    //glutIdleFunc(myDisplay);
    glutMouseFunc(mouse);
    glutMainLoop();
}

