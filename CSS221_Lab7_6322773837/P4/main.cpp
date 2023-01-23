//
//  main.cpp
//  P4
//
//  Created by Ornnicha Phueaksri on 18/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

GLint w=400; GLint h=400; //the window width and height
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POINTS);
    glColor3f(1, 0, 1);
    glVertex2f(-0.8,0.8);
    glColor3f(1, 1, 0);
    glVertex2f(-0.7,0.8);
    glColor3f(0, 0, 1);
    glVertex2f(-0.6,0.8);
    glColor3f(1, 0, 0);
    glVertex2f(-0.7, 0.75);
    glColor3f(0, 1, 0);
    glVertex2f(-0.6,0.75);
    glColor3f(0, 0, 0);
    glVertex2f(-0.5,0.75);
    glEnd();
    glPointSize(250.0);
    
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);
    glVertex2f(-0.8,0.8);
    glVertex2f(-0.7,0.8);
    glVertex2f(-0.6,0.8);
    glVertex2f(-0.7, 0.75);
    glVertex2f(-0.6,0.75);
    glVertex2f(-0.5,0.75);
    glEnd();
    
    glFlush();
    
}
void Init(void){
    glClearColor(1, 1, 1, 0);//white
    glColor3f(0, 0, 1);//blue
    glPointSize(6.0); //Set up the point size
    glMatrixMode(GL_PROJECTION); //Set matrix mode to projection .
    glLoadIdentity();//Clear current projection matrix to the identity matrix.
    gluOrtho2D(-0.9,-0.4,0.6,0.9);//Define a mathematical coordinate system
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Problem 3");
    Init();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;}
