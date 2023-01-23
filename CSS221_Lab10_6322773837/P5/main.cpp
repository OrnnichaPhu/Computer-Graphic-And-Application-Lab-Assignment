//
//  main.cpp
//  P5
//
//  Created by Ornnicha Phueaksri on 8/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Main
#define Accerelation 1
#define Start_Stop 2

//Sub1
#define SPEED_BALL 1
#define SLOW_BALL 2

//Sub2
#define STOP_BALL 2
#define START_BALL 1

int Main_Option = 2;

GLfloat angle=0, inc_angle=0.1, ro_Angle =0, ro_df=0.1 ;

GLfloat xPos = 0.0;
GLfloat yPos = 0.0;
GLfloat zPos = 0.0;

GLfloat xSpeed = 0.007;
GLfloat ySpeed = 0.004;
GLfloat zSpeed = 0.003;
GLfloat ballRadius=0.3;

GLfloat xPosMax, xPosMin, yPosMax, yPosMin,zPosMax, zPosMin;
GLdouble xLeft=-1, xRight=1, yBottom=-1, yTop=1,zNear=-1,zFar=1;

bool rotate=false;



void init3D()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
    glMatrixMode(GL_PROJECTION); // Select the Projection matrix
    glLoadIdentity();
    gluPerspective(20,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -10,0,0,0,0.0,1.0,0.0);

    xPosMin = xLeft + ballRadius;
    xPosMax = xRight - ballRadius;
    yPosMin = yBottom + ballRadius;
    yPosMax = yTop - ballRadius;
    zPosMin = zNear + ballRadius;
    zPosMax = zFar - ballRadius;
}

void Unit_Cube(void)
{
    // Front face
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(-1.0,1.0,1.0);
    glEnd();
    //Back Face
    glColor3f(0.1, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,1.0,-1.0);
    glEnd();
    // Top Face
    glColor3f(0.9, 0.1, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,1.0,-1.0);
    glEnd();
    // Bottom Face
    glColor3f(0.1, 0.1, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glEnd();
    // Left face
    glColor3f(0.1, 0.9, 0.1);
    glBegin(GL_QUADS);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(1.0,-1.0,1.0);
    glEnd();
    glColor3f(0.9, 0.9, 0.1);
    // Right face
    glBegin(GL_QUADS);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glEnd();
}

void draw_shpere()
{
    glPushMatrix();
        glTranslated(xPos,yPos,zPos);
        glColor3f(1,0,1);
        glRotated(ro_Angle, 0, 1, 1);
        glutSolidSphere(ballRadius,10,10);
        glColor3f(1, 1, 1);
        glutWireSphere(ballRadius,10,10);
    glPopMatrix();


}


void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotated(angle,0,1,0);
    Unit_Cube();
    draw_shpere();
    glPopMatrix();

    angle=angle+inc_angle;
    
    if(rotate) ro_Angle = ro_Angle + ro_df;
    
    xPos += xSpeed;
    yPos += ySpeed;
    zPos += zSpeed;

    if (xPos > xPosMax) {
        xPos = xPosMax;
        xSpeed = -xSpeed;
    } else if (xPos < xPosMin) {
        xPos = xPosMin;
        xSpeed = -xSpeed;
    }
    if (yPos > yPosMax) {
        yPos = yPosMax;
        ySpeed = -ySpeed;
    } else if (yPos < yPosMin) {
        yPos = yPosMin;
        ySpeed = -ySpeed;
    }
    if (zPos > zPosMax) {
        zPos = zPosMax;
        zSpeed = -zSpeed;
    } else if (zPos < zPosMin) {
        zPos = zPosMin;
        zSpeed = -zSpeed;
    }


    glutSwapBuffers();
}

void processMenu(int option){
    Main_Option = option;
}


void AccelationMenu(int option){
    switch (option) {
        case SPEED_BALL: ro_df = ro_df + 2.0; break;
        case SLOW_BALL : if(ro_df >= 0) ro_df = ro_df - 1.0; break;
        default: break;
    }
}


void ratation_Menu(int option){
    switch (option) {
        case STOP_BALL : if(rotate == true) rotate = false; break;
        case START_BALL: rotate = true; break;
        default: break;
    }
}



void createGLUTMenu(){
    
    //Accerelation Menu
    int Acce_Manu = glutCreateMenu(AccelationMenu);
    glutAddMenuEntry("Accelerate", SPEED_BALL);
    glutAddMenuEntry("Decelerate",SLOW_BALL);

    
    //
    int start_stop_Menu = glutCreateMenu(ratation_Menu);
    glutAddMenuEntry("Stop",STOP_BALL);
    glutAddMenuEntry("Resume",START_BALL);
    
    //Maain Menu
    int Main_menu = glutCreateMenu(processMenu);
    glutAddSubMenu("Acceleration", Acce_Manu);
    glutAddSubMenu("Start/Stop", start_stop_Menu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(480,480);
    glutCreateWindow("Problem 4");
    init3D();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    createGLUTMenu();
    glutMainLoop();
    return(0);
}
