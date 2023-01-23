//
//  main.cpp
//  P7
//
//  Created by Ornnicha Phueaksri on 18/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <cstdlib> //this is for randomization "rand"
#include <math.h> // math functions

GLint screenWidth = 640; GLint screenHeight = 480; // width and height of the window
GLfloat r=1,g=1,b=1;
void myInit(void)
{ glClearColor(1.0,1.0,1.0,0.0); // background color is white
    glColor3f(1.0, 0.0, 0.0); // drawing color is black
    glPointSize(2.0); // a 'dot' is 2 by 2 pixels
    glMatrixMode(GL_PROJECTION); // set some other parameters
    glLoadIdentity(); // set some other parameters
    //gluOrtho2D(0.0,1.0,0.0,1.0); // set the coordinates //change this
    //gluOrtho2D(1.0,8.0,0.0,5.0); // for ln(x*x+1)
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);//clear the screen
    glClearColor(r,g,b,0.0); //set up an RGB background color
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void){ //change this function
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glBegin(GL_LINE_STRIP);
    
    /*for(double x = 0; x < 1.0 ; x += 0.005){ //x changes from 0 to1 with step 0.005
     double func = x * x; //function
     glVertex2d(x,func);
     }*/
    
    /*for(double x = 1; x < 8.0 ; x += 0.005){ //x changes from 0 to1 with step 0.005
        double func = log(x*x +1);
        glVertex2d(x,func);
    }*/
    for(double t = 0; t < 10.0 ; t += 0.005){ //x changes from 0 to1 with step 0.005
        double x = sin(2*t);
        double y = sin(3*t);
        glVertex2d(x,y);
    }
        glEnd();
        glFlush(); // send all output to display
}
int main(int argc, char** argv){
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Dot Plot of a Function"); // open the screen window
    glutDisplayFunc(myDisplay); // register the redraw function
    myInit();
    glutMainLoop();
    return 0;
}
