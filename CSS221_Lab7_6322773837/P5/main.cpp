//
//  main.cpp
//  P5
//
//  Created by Ornnicha Phueaksri on 18/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <cstdlib> //this is for randomization "rand"
#include <math.h> // math functions

const float Pi=3.14159265358979323846;
GLint wx = 800, wy = 800;//initial size of the window
GLfloat r, g, b;


void MyInit(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,wx,0.0,wy); // math coordinate system matches the window
    glPointSize(4.0);
}

//***************************Replace this procedure***************************
void draw_Triangle(GLfloat cornerX, GLfloat cornerY, GLfloat size){//draw the triangle
    glBegin(GL_POLYGON);
    glColor3f(1,0,0); // Set the drawing color
    glVertex2f(cornerX, cornerY);
    glVertex2f(cornerX+size, cornerY);
    glVertex2f(cornerX+size/2, cornerY+size);
    glEnd();
    glFlush(); // Process all OpenGL routines as quickly as possible.
}
//***********************************************************

void draw_Polygon(GLfloat xc, GLfloat yc,GLint N, GLfloat R){
    glBegin(GL_POLYGON);
    glColor3f(0,0,1);
    for (int i=0;i<=N;i++){
        glVertex2f(xc + R*cos(2*Pi*i/N), yc + R*sin(2*Pi*i/N));
    }
    glEnd();
    glFlush();
    
}

void myDrawing(){
    //draw_Triangle(100,100,80);
    draw_Polygon(100.0,100.0,5,40);
    glFlush();
}
void winReshapeFcn (GLint w, GLint h){
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h); //viewport matches the new window
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0*w, 0.0, 1.0*h); //math coordinates matches the new window
    wx=w; wy=h; //new window dimensions are sent to the main
    r=rand()%1000/1000.;
    g=rand()%1000/1000.;
    b=rand()%1000/1000.; //change r,g,b randomly
    glClearColor(r,g,b,0.0); //set up an RGB background color
    glClear (GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{ glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize (800, 800);
    glutCreateWindow("problem 5");
    MyInit();
    glutDisplayFunc(myDrawing); //call the display function
    glutReshapeFunc(winReshapeFcn); // call the reshape window function
    glutMainLoop();
    return 0;
}
