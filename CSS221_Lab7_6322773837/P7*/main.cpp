//
//  main.cpp
//  P7*
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
int set = 0;

void myInit(void)
{ glClearColor(1.0,1.0,1.0,0.0); // background color is white
    glColor3f(1.0, 0.0, 0.0); // drawing color is black
    glPointSize(2.0); // a 'dot' is 2 by 2 pixels
    glMatrixMode(GL_PROJECTION); // set some other parameters
    glLoadIdentity(); // set some other parameters
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);//clear the screen
    glClearColor(r,g,b,0.0); //set up an RGB background color
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void){ //change this function
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glBegin(GL_LINE_STRIP);

    for(double t = 0; t < 10.0 ; t += 0.005){ //x changes from 0 to1 with step 0.005
        double x = sin(2*t);
        double y = sin(3*t);
        glVertex2d(x,y);
    }
        glEnd();
        glFlush(); // send all output to display
}


void s2(){
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glLineStipple(1, 0xFFFF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);

    for(double t = 0; t < 10.0 ; t += 0.005){ //x changes from 0 to1 with step 0.005
        double x = sin(2*t);
        double y = sin(3*t);
        glVertex2d(x,y);
    }
        glEnd();
        glFlush(); // send all output to display
}
void s3(){
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glPointSize(2.0);
    glLineStipple(1, 0xFFFF);
    glBegin(GL_POINTS);

    for(double t = 0; t < 10.0 ; t += 0.005){ //x changes from 0 to1 with step 0.005
        double x = sin(2*t);
        double y = sin(3*t);
        glVertex2d(x,y);
    }
        glEnd();
        glFlush(); // send all output to display
}

void s4(){
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glPointSize(4.0);
    glLineStipple(1, 0xFFFF);
    glBegin(GL_POINTS);

    for(double t = 0; t < 10.0 ; t += 0.01){ //x changes from 0 to1 with step 0.005
        double x = sin(2*t);
        double y = sin(3*t);
        glVertex2d(x,y);
    }
        glEnd();
        glFlush(); // send all output to display
}

void s5(){
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glPointSize(6.0);
    glLineStipple(1, 0xFFFF);
    glBegin(GL_POINTS);

    for(double t = 0; t < 10.0 ; t += 0.02){ //x changes from 0 to1 with step 0.005
        double x = sin(2*t);
        double y = sin(3*t);
        glVertex2d(x,y);
    }
        glEnd();
        glFlush(); // send all output to display
}


void mouse(GLint button, GLint state, GLint x, GLint y) {
    if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN){
        glClear(GL_COLOR_BUFFER_BIT);
        set = (set + 1)%5;
        switch (set) {
            case 1:myDisplay();
                break;
            case 2:s2();
                break;
            case 3:s3();
                break;
            case 4:s4();
                break;
            case 5:s5();
                break;
        }
    }
    glFlush();
        }

int main(int argc, char** argv){
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Dot Plot of a Function"); // open the screen window
    glutDisplayFunc(myDisplay); // register the redraw function
    glutMouseFunc(mouse);
    myInit();
    glutMainLoop();
    return 0;
}
