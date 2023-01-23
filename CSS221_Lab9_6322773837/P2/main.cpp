//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 1/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLfloat inc1=1;
GLfloat angle1;
GLfloat inc2=1;
GLfloat angle2;
GLint xprev,yprev=0;
GLfloat vx1=0,vy1=0,vz1=1;
GLfloat vx2=0,vy2=1,vz2=0;
int d;//indicator of the rotation vertical or horizontal
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void Rot_Teapot()
{ glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glPushMatrix();
    glRotatef(angle1,vx1,vy1,vz1);
    glRotatef(angle2,vx2,vy2,vz2);
    glColor3f(1.0,0.0,0.0);
    glutSolidTeapot(3.0);
    glColor3f(0.0,0.0,0.0);
    glutWireTeapot(3.0);
    glPopMatrix();
}
void Init(void)
// All Setup For OpenGL Goes Here
{ glClearColor(1.0, 1.0, 1.0,0.0); // background is white
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1.33, .01, 10000);
    gluLookAt(15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
}

void mydisplay(void)
{
    if (d ==1) angle1=angle1+inc1;
    else angle2 = angle2+inc2;
    Rot_Teapot();
    glutSwapBuffers();
    Time_Delay(5);
}
void Do_Nothing(){}

void motion(int x, int y)//modify
{
    if (x<xprev) inc2=0.1; else inc2=-0.1;
    if (y<yprev) inc1=0.1; else inc1=-0.1;
    if (labs(x-xprev)>labs(y-yprev)) d=0; else d=1;
    glutIdleFunc(mydisplay);
    xprev=x;
    yprev=y;
}

void mouse(int button, int state, int x, int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) glutIdleFunc(mydisplay);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) glutIdleFunc(Do_Nothing);
            break;
        default:
            break;
    }
}

void processNormalKeys(unsigned char key, int x, int y)
{ switch (key) {
    case 's': case 'S': glutIdleFunc(mydisplay);break;
    case 'e':case 'E': glutIdleFunc(Do_Nothing);break;
        break;
    default: break;
}
}

void inputKey(int key, int x, int y) {//special key callback function
    switch (key)
    {
        case GLUT_KEY_LEFT: ; break; //arrows keys
        case GLUT_KEY_RIGHT: ;break;
        case GLUT_KEY_UP : ;break;
        case GLUT_KEY_DOWN: ;break;
    }
    glutIdleFunc(mydisplay);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 2");
    glutDisplayFunc(mydisplay);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(processNormalKeys);
    Init();
    glutMainLoop();
}
