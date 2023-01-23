//
//  main.cpp
//  P1
//
//  Created by Ornnicha Phueaksri on 1/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLfloat rotangle1=0.0;
GLfloat deltarot1=0.2;
GLfloat rotangle2=0.0;
GLfloat deltarot2=0.3;
GLfloat direction1[]={0,0,1};//the first teapot rotates around this direction
GLfloat direction2[]={1,0,0};//the second teapot rotates around this direction
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void Init(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(15, 1.33, .01, 10000);
    gluLookAt(50.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void plot_Rotation_Vector1()
{ float x2,y2,z2;
    float delta=20;//size of the vector
    glColor3f(0,0,1);
    x2=direction1[0]*delta;
    y2=direction1[1]*delta;
    z2=direction1[2]*delta;
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3d(x2,y2,z2);
    glEnd();
}

void plot_Rotation_Vector2()
{ float x2,y2,z2;
    float delta=20;//size of the vector
    glColor3f(0,0,1);
    x2=direction2[0]*delta;
    y2=direction2[1]*delta;
    z2=direction2[2]*delta;
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3d(x2,y2,z2);
    glEnd();
}

void plot_Origin()
{ glPointSize(10);
    glColor3f(0,1,0);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
}
void Rot_Teapot1(){
    GLfloat dx,dy,dz; //working variables
    dx=direction1[0];//split the direction vector into components
    dy=direction1[1];
    dz=direction1[2];
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();//save the original transformation matrix in the stack
    glRotatef(rotangle1,dx,dy,dz); //rotate around the given vector
    glColor3f(1.0,0.0,0.0);//red
    glutSolidTeapot(5.0); //draw solid teapot
    glColor3f(0.0,0.0,0.0);//white wireframe
    glutWireTeapot(5.0); //draw the teapot again as the wireframe
    plot_Rotation_Vector1();//the rotation vector
    plot_Origin();//the origin
    glPopMatrix(); //get the original transformation back
}
void Rot_Teapot2(){
    GLfloat dx,dy,dz; //working variables
    dx=direction2[0];//split the direction vector into components
    dy=direction2[1];
    dz=direction2[2];
    glColor3f(0.0,0.0,1.0);
    glPushMatrix();//save the original transformation matrix in the stack
    glTranslatef(10, 10, 0);
    glRotatef(rotangle2,dx,dy,dz); //rotate around the given vector
    glColor3f(0.0,0.0,1.0);//red
    glutSolidTeapot(3.0); //draw solid teapot
    glColor3f(0.0,0.0,0.0);//white wireframe
    glutWireTeapot(3.0); //draw the teapot again as the wireframe
    plot_Rotation_Vector2();//the rotation vector
    plot_Origin();//the origin
    glPopMatrix(); //get the original transformation back
}
void Do_Nothing(void){}

void mydisplay(void){
    rotangle1 = rotangle1 + deltarot1;
    rotangle2 = rotangle2 + deltarot2;
    Rot_Teapot1();
    Rot_Teapot2();
    glutSwapBuffers();
    Time_Delay(50);
}

void processNormalKeys(unsigned char key, int x, int y)
{ switch (key) {
    case 's': case 'S': glutIdleFunc(mydisplay);break;
    case 'e':case 'E': glutIdleFunc(Do_Nothing);break;
        break;
    default: break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("problem 1");
    glutDisplayFunc(mydisplay);
    glutIdleFunc(mydisplay);
    glutKeyboardFunc(processNormalKeys);
    Init();
    glutMainLoop();
    
}
