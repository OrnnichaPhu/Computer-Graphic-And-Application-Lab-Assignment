//
//  main.cpp
//  P5.1
//
//  Created by Ornnicha Phueaksri on 1/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>


GLfloat ratio=1.33;
GLfloat x=-1.0,y=2.0,z=7.0;
GLfloat lx=0.0,ly=0.0,lz=-1.0,angle=0;
GLfloat increment=0.1, angleincrement=0.01;
GLfloat ang=0, sangleincrement=1;
float angleh=0;
float dh=0.005;
float R=2;


void changeSize(GLint w, GLint h)
{
    if(h == 0)
    h = 1;
    ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
    x + lx,y + ly,z + lz,
    0.0,1.0,0.0);
}
void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}

void DrawPoint(GLfloat x, GLfloat y, GLfloat z)
{
    glColor3d(1,0,0);
    glPointSize(16);
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
}
void DrawDonut(void)
{
    glPushMatrix();
    glTranslated(-2,0.5,0);
    glRotated(ang,0,1,0);
    glColor3f(1,0,0);
    glutWireTorus(0.2,0.8,20,20);
    glColor3f(0,0,1);
    glutSolidTorus(0.2,0.8,20,20);
    glPopMatrix();
}
void DrawSnowMan() {
    int c;
    glColor3f(1.0, 1.0, 1.0);
    // Draw Body
    glTranslatef(0.0f ,0.75, 0.0);
    glutSolidSphere(0.75,20,20);
        glPushMatrix();
        // Draw Head
        //the head nodes
        glTranslatef(0.0, 1.0, 0.0);
        glRotatef(angleh,1,0,0); // rotate head
        glutSolidSphere(0.25,20,20);
        c=rand()%100;
            // Draw Eyes
            if(c==1) glColor3f(1,1,1);
            else glColor3f(0,0,0);
            glPushMatrix();
            glTranslatef(0.05, 0.10, 0.18);
            glutSolidSphere(0.05,10,10);
            glTranslatef(-0.1, 0.0, 0.0);
            glutSolidSphere(0.05,10,10);
            glPopMatrix();
        // Draw Nose
        glColor3f(1.0, 0.5 , 0.5);
        glRotatef(0.0,1.0, 0.0, 0.0);
        glutSolidCone(0.08,0.5,10,2);
        glPopMatrix();
    angleh=angleh+dh;
    if(angleh>=20 || angleh<=0) dh=-dh;
}
void Draw36SnowMan(void)
{
    for(int i = -3; i < 3; i++)
    for(int j=-3; j < 3; j++) {
    glPushMatrix();
    glTranslatef(i*10.0,0,j * 10.0);
    DrawSnowMan();
    glPopMatrix();
    }
}

void DrawMagicBall(void)
{
    glPushMatrix();
    glRotated(ang,0,1,0);
    glTranslatef(2,0.5,0);
    glRotated(-ang,1,0,0);
    glColor3f(1,1,0);
    glutWireSphere(0.5,40,40);
    glColor3f(0,1,0);
    glutSolidSphere(0.5,40,40);
    glPopMatrix();
}



void DrawWorld(void) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw ground
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0, 100.0);
    glVertex3f( 100.0, 0.0, 100.0);
    glVertex3f( 100.0, 0.0, -100.0);
    glEnd();
    // Draw objects
    DrawDonut();
    DrawMagicBall();  
    Draw36SnowMan();
    DrawPoint(0,0,0);
    DrawPoint(-R,0.5,0);
    Time_Delay(20);
    ang=ang+sangleincrement;
    glutSwapBuffers();
}

void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z,
    x+lx ,y+ly ,z+lz,
    0.0,1.0,0.0);
}
void moveMeFlat(float increment) {
    x = x + lx*increment;
    z = z + lz*increment;
    glLoadIdentity();
    gluLookAt(x, y, z,
    x + lx,y + ly,z + lz,
    0.0,1.0,0.0);
}
void moveMeUp(float increment) {
    y=y-increment;
    glLoadIdentity();
    gluLookAt(x, y, z,x + lx,y+ly ,z + lz,0.0,1,0.0);
}
void inputKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT : angle -= angleincrement;orientMe(angle);break;
        case GLUT_KEY_RIGHT : angle+= angleincrement;orientMe(angle);break;
        case GLUT_KEY_UP : moveMeFlat(increment);break;
        case GLUT_KEY_DOWN : moveMeFlat(-increment);break;
        case GLUT_KEY_PAGE_UP: moveMeUp(increment);break;
        case GLUT_KEY_PAGE_DOWN: moveMeUp(-increment);break;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Problem 5: Nodding & blinking");
    changeSize(800,800);
    glutSpecialFunc(inputKey);
    glutDisplayFunc(DrawWorld);
    glutIdleFunc(DrawWorld);
    glutReshapeFunc(changeSize);
    glutMainLoop();
    return(0);
}
