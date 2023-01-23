//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 18/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

GLint w=500;GLint h=500; //the initial window size
void MyDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0); // Set current drawing color to blue.
    glRectf(100.0, 100.0, 200.0, 200); //Draw a rectangle with current color
    glFlush( ); // send the drawing to the screen
}
void Init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // white color to clear the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, w, 0.0, h);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Exercise 2");
    glutDisplayFunc(MyDisplay);
    Init();
    glutMainLoop();
    return 0;
}
