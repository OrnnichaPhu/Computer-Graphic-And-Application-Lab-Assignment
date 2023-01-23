//
//  main.cpp
//  P4
//
//  Created by Ornnicha Phueaksri on 22/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <time.h>

GLfloat angle1=0,dangle1=1;
GLfloat angle2=0,dangle2=2.5;


void Draw_Origin()
{ glColor3f(0.0, 0.0, 1.0); // set the drawing color blue
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2i(0,0);
    glEnd();
}
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-450.0,450.0,-360.0,360.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Time_Delay(GLint dur) //time delay
{clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    {
        
    }
}
void Rotate_Rect1()
{
    angle1 = angle1+dangle1;
    glPushMatrix();

    glTranslatef(100,100,0);
    glRotatef(angle1,0.0,0.0,1.0);
    Draw_Origin();
    glTranslatef(120,0,0);
    glColor3f(1.0,0.0,0.0);
    glRecti(-50,-50,50,50);
    //Draw_Origin();
    glPopMatrix();
    Draw_Origin();
    //glutSwapBuffers();
    //Time_Delay(100);
}
void Rotate_Rect2()
{
    angle2 = angle2+dangle2;
    glPushMatrix();
    //Draw_Origin();
    glTranslatef(-100,-100,0);
    glRotatef(-angle2,0.0,0.0,1.0);
    Draw_Origin();
    glTranslatef(170,0,0);
    glColor3f(1.0,1.0,0.0);
    glRecti(-50,-50,50,50);
    //Draw_Origin();
    glPopMatrix();
    glutSwapBuffers();
    Time_Delay(100);
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Rotate_Rect1();
    Rotate_Rect2();
   
}

void Do_Nothing(void) {
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) glutIdleFunc(myDisplay);
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) glutIdleFunc(Do_Nothing);
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("problem 4");
    glutDisplayFunc(myDisplay);
    //glutIdleFunc(myDisplay);
    glutMouseFunc(mouse);
    myInit();
    glutMainLoop();
  
}
