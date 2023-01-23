//
//  main.cpp
//  P3
//
//  Created by Ornnicha Phueaksri on 22/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <time.h>
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
//the rotation angle and increment
float angle=0.0,dt=1;

void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-480, 480.0, -480, 480.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    angle=0.0;
}
//<<<<<<<<<<<<<<<<<<<<<<<< my routines >>>>>>>>>>>>>>>>>
void Draw_Origin()
{
    glPointSize(7.0);
    glColor3f(0.0, 0.0, 0.0); //the origin, big, red point
    glBegin(GL_POINTS);
    glVertex2i(0,0);
    glEnd();
}

void Rotate_Rect( ) {
    glColor3f(0.0, 1.0, 0.0); // rectangle drawing color green
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);// Set angle-deg. rotation about the z axis.
    glRecti(-50, -50, 50, 50); // Display green rectangle.
    angle+=dt;
    glPopMatrix();
    Draw_Origin();
    Time_Delay(50);
    glutSwapBuffers();
}

void Rotate_Rectblue( ) {
    glColor3f(0.0, 0.0, 1.0); // rectangle drawing color green
    glPushMatrix();
    glTranslatef(100,100,0);
    glRotatef(-angle, 0.0, 0.0, 1.0);// Set angle-deg. rotation about the z axis.
    glRecti(-50, -50, 50, 50); // Display green rectangle.
    angle+=dt;
    glPopMatrix();
    Draw_Origin();
    Time_Delay(50);
    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    //Rotate_Rect();
    Rotate_Rectblue();
}
void Do_Nothing(void) {
}
void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) glutIdleFunc(myDisplay);
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) glutIdleFunc(Do_Nothing);
    
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Problem 3");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);
    myInit();
    glutMainLoop();
}

