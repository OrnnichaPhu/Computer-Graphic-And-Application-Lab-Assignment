//
//  main.cpp
//  P1
//
//  Created by Ornnicha Phueaksri on 29/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>


GLfloat rotangle1=0.0, dt1=0.1;
GLfloat rotangle2=0.0, dt2=0.1;


float ax[3]={45,0,0}; float ay[3]={0,45,0}; float az[3]={0,0,45};//axes


float V1[3] ={0,0,0}; float V2[3] ={0,0,15};
GLfloat direction1[]={0,0,1};//the first teapot rotates around this direction
bool Rotate = true;

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
void plot_line(){
    glPushMatrix();
    glColor3f(0, 1, 0);
    plot_Arrow(V1, V2);
    glLineWidth(2);
    glPopMatrix();
}

void MoveRect(){
    glPushMatrix();
    glRotatef(rotangle1, 0, 1, 0);
    plot_line();
    rotangle1 = rotangle1 + dt1;
    
    glTranslatef(0, 0, 15);
    glRotatef(rotangle2, 0, 0, 1);
    rotangle2 = rotangle2 + dt2;
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
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
    gluLookAt(50.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);// position and aim the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();// reset the current Modelview Matrix
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}

void doNothing(void){}

void myDisplay(void)
{//clear the screen, increment the rotation angle, plot the teapot
    glClear(GL_COLOR_BUFFER_BIT);
    MoveRect();
    plot_Axis();
    output_Text(-15,11,7.5,"F1 - Start / Stop the rotations");
    glutSwapBuffers();
}

void SpecialKeys(int c, int x, int y)
{
    if (c == GLUT_KEY_F1)
        Rotate = !Rotate;
    if(Rotate)
        glutIdleFunc(myDisplay);
    else
        glutIdleFunc(doNothing);
}
    
    
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(480,480);
    glutCreateWindow("Pre-exam | Problem 1");
    /* Use myInit2d() or myInit3d() for initialization */
    myInit3d();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
}
