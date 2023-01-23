//
//  main.cpp
//  P6
//
//  Created by Ornnicha Phueaksri on 18/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <cstdlib> //this is for randomization "rand"
#include <math.h> // math functions
const float Pi=3.14159265358979323846;
bool start = true;
GLint wx=500;
GLint wy=500;
GLfloat r, g, b;


void draw_Triangle(GLfloat cornerX, GLfloat cornerY, GLfloat size) {
    glBegin(GL_POLYGON);
    glColor3f(1,0,0); // Set the drawing color to red.
    glVertex2f(cornerX, cornerY);
    glVertex2f(cornerX+size, cornerY);
    glVertex2f(cornerX+size/2, cornerY+size);
    glEnd();
    glFlush(); // Process all OpenGL routines as quickly as possible.
}

//******************replace by a function to draw a Heptagon with a random color here***
void draw_Polygon(GLfloat xc, GLfloat yc,GLint N, GLfloat R){
    glBegin(GL_POLYGON);
    r=rand()%1000/1000.;
    g=rand()%1000/1000.;
    b=rand()%1000/1000.;
    glColor3f(r,b,g);
    for (int i=0;i<=N;i++){
        glVertex2f(xc + R*cos(2*Pi*i/N), yc + R*sin(2*Pi*i/N));
    }
    glEnd();
    glFlush();
    
}

void doNothing(void) {
    if (start) {
        start = false;
        glClear(GL_COLOR_BUFFER_BIT); // Clear display window for the first time
    }
    glFlush();
}
void mouse(GLint button, GLint state, GLint x, GLint y) {
    if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN)
        draw_Triangle(x, wy-y,30);// understand wy-y!
    //********draw the Heptagon on the right mouse click here
    if (button ==GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
        draw_Polygon(x, wy-y,6,30);// understand wy-y!
}
// *******reshape function to adjust the view port and math coordinates here
void Reshape(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0*w, 0.0, 1.0*h);
    wx=w;
    wy=h;
}

void myInit(void) {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, wx, 0.0, wy); // set the word coordinate system
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize (wx, wy);
    glutCreateWindow("Ex_6");
    myInit();
    glutDisplayFunc(doNothing);
    //**************callback Reshape
    glutMouseFunc(mouse);
    glutMainLoop();
}
