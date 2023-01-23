//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 8/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define Red 1
#define Green 2
#define Blue 3
#define Black 4
#define Small 1
#define Medium 2
#define Large 3
#define Stop 1
#define Resume 2

int windowWidth = 500;
int windowHeight = 500;
int windowPosX = 50;
int windowPosY = 50;
GLfloat ballRadius = 0.5;
GLfloat xPos = 0.0;
GLfloat yPos = 0.0;
GLfloat xPosMax, xPosMin, yPosMax, yPosMin;
GLdouble xLeft=-1, xRight=1, yBottom=-1, yTop=1;
GLfloat xSpeed = 0.02;
GLfloat ySpeed = 0.007;
int red=0,green=0, blue=1;
void output_Text(float x, float y, char *text)
{
    int len, i;
    glColor3f(1, 0, 0);
    glRasterPos3f(x, y, 0);
    len = (int)strlen(text);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}
void output_Number(float x, float y, double v)
{
    int len, i;
    char text [20]={'\0'};
    sprintf(text, "%lf", v);
    output_Text(x,y,text);
}

void initGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBottom, yTop);
    xPosMin = xLeft + ballRadius;
    xPosMax = xRight - ballRadius;
    yPosMin = yBottom + ballRadius;
    yPosMax = yTop - ballRadius;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}

void display_Ball()
{
    output_Text(xLeft+0.05,yBottom+0.1,"bouncing ball size=");
    output_Number(xLeft+0.7,yBottom+0.1,ballRadius);
    glTranslatef(xPos, yPos, 0.0);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(red, green, blue);
    glVertex2f(0.0, 0.0);
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) {
        angle = i * 2.0 * M_PI / numSegments;
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
}

void Do_Nothing()
{}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    display_Ball();
    glEnd();
    glutSwapBuffers();


    xPos += xSpeed;
    yPos += ySpeed;

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

    Time_Delay(10);
}

void Menu_Color(int option)
{
    switch (option) {
        case Red : red = 1.0; green = 0.0; blue = 0.0; break;
        case Green : red = 0.0; green = 1.0; blue = 0.0; break;
        case Blue : red = 0.0; green = 0.0; blue = 1.0; break;
        case Black : red = 0.0; green = 0.0; blue = 0.0; break;
        default :break;
        }
}

void Menu_Size(int option)
{
    switch (option)
    {
        case Small: ballRadius=0.1; break;
        case Medium: ballRadius=0.3; break;
        case Large: ballRadius=0.5; break;
        default: break;
    }

    xPosMin = xLeft + ballRadius;
    xPosMax = xRight - ballRadius;
    yPosMin = yBottom + ballRadius;
    yPosMax = yTop - ballRadius;
}

void processMenu(int option)
{
    switch(option)
    {
        case Stop : glutIdleFunc(Do_Nothing); break;
        case Resume : glutIdleFunc(display); break;
        default: break;
    }
}

void createGLUTMenus() {

    // Color Menu
    int submenu1 = glutCreateMenu(Menu_Color);
    glutAddMenuEntry("Red",Red);
    glutAddMenuEntry("Green",Green);
    glutAddMenuEntry("Blue", Blue);
    glutAddMenuEntry("Black", Black);

    //Size Menu
    int submenu2 = glutCreateMenu(Menu_Size);
    glutAddMenuEntry("Small",Small);
    glutAddMenuEntry("Medium",Medium);
    glutAddMenuEntry("Large", Large);

    int menu=glutCreateMenu(processMenu);
    glutAddSubMenu("Color",submenu1);
    glutAddSubMenu("Size",submenu2);
    glutAddMenuEntry("Stop",Stop);
    glutAddMenuEntry("Resume",Resume);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutCreateWindow("Problem 2");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    initGL();
    createGLUTMenus();
    glutMainLoop();
    return 0;
}
