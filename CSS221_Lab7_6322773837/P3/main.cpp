//
//  main.cpp
//  P3
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
    
    //glBegin(GL_POINTS);
    //glBegin(GL_LINES);
    //glBegin(GL_LINE_STRIP);
    //glBegin(GL_LINE_LOOP);
    //glbegin(GL_TRIANGLES);
    //glBegin(GL_TRIANGLE_STRIP);
    glBegin(GL_TRIANGLE_FAN);
    
    // draw points or lines
    glVertex2f(0.0,0.0); // vo
    glVertex2f(3.0,3.0); // v1
    glVertex2f(2.0,2.0); // v2
    glVertex2f(6.0, 2.0); // v3
    glVertex2f(4.0,4.0); // v4
    glVertex2f(4.0,10.0); // v5
    glEnd();
    glFlush();
    
    
}void Init(void)
{ glClearColor(1, 1, 1, 0);//white
    glColor3f(0, 0, 1);//blue
    glPointSize(6.0); //Set up the point size
    glMatrixMode(GL_PROJECTION); //Set matrix mode to projection .
    glLoadIdentity();//Clear current projection matrix to the identity matrix.
    gluOrtho2D(-5.0,15.0,-5.0,15.0); //Define a mathematical coordinate system
}
int main(int argc, char **argv)
{glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Problem 3");
    Init();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;}
