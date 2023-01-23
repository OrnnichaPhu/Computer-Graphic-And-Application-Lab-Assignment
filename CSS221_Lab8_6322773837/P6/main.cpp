//
//  main.cpp
//  P6
//
//  Created by Ornnicha Phueaksri on 22/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

GLfloat angle=0,dangle=1;

void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
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

void Draw_AllBlade(){
    angle = angle+dangle;
    glPushMatrix();
    glRotatef(angle,0.0,0.0,1.0);
    glColor3f(1,0,0);
    glutSolidSphere(1,10,10);
    for(int i = 0; i<4; i++){
        glPushMatrix();
        glRotatef(i*90,0.0,0.0,1.0);
        Draw_Blade();
        glPopMatrix();
    }
    glPopMatrix();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Draw_AllBlade();
    glutSwapBuffers();
    Time_Delay(50);
}

void Do_Nothing(void){}

void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) glutIdleFunc(myDisplay);
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) glutIdleFunc(Do_Nothing);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Problem 6");
    /* Use myInit2d() or myInit3d() for initialization */
    //myInit2d();
    myInit3d();
    glutDisplayFunc(myDisplay);
    //glutIdleFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
}

