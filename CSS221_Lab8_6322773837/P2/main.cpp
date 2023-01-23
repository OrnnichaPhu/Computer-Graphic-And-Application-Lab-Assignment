//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 22/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>

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
/**************************
* Add your code here for trajectory 2
**************************/
void DrawCircle1()
{
    float xtrans, ytrans;
    glPushMatrix();
    xtrans=trajectoryx1(t1);
    ytrans=trajectoryy1(t1);
    glTranslatef(xtrans,ytrans,0);
    t1=t1+dt1;
    if ((t1>60) || (t1<0)) dt1=-dt1;
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(4.0,15,15);
    glPopMatrix();
}
void DrawCircle2()
{
    float xtrans, ytrans;
    glPushMatrix();
    xtrans=trajectoryx2(t2);
    ytrans=trajectoryy2(t2);
    glTranslatef(xtrans,ytrans,0);
    t2=t2+dt2;
    if ((t2>60) || (t2<0)) dt2=-dt2;
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(4.0,15,15);
    glPopMatrix();
}
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void myInit2d(void)
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-60,60,-60,60,-10,10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 1.0);
    glRectf(-30,30,30,-30);
    glTranslatef(-30,-30,0);
    DrawCircle1();
    DrawCircle2();
    /**************************
    * Add your code here DrawCircle2 *
    **************************/
    glutSwapBuffers();

    Time_Delay(10);
}

void doNothing(void)
{

}
void myMouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) glutIdleFunc(myDisplay);
    break;
    case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) glutIdleFunc(doNothing);
    break;
    default:
    break;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("problem 2");
    myInit2d();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
}
