//
//  main.cpp
//  P3
//
//  Created by Ornnicha Phueaksri on 8/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define HIGH 1
#define MEDIUM 2
#define LOW 3
#define Stop 4
#define Resume 5
#define Sur1 1
#define Sur2 2
#define Sur3 3

GLfloat ratio;
GLfloat x=0.0,y=0,z=3.0;//eye coordinates
float ni=25, nj=25;
GLfloat angle=0, inc_angle=0.1; //rotation angle
GLfloat red=1, green=1, blue=1;
bool flag;
int menu1, menu2, menu3, cur_menu;
int cur_sur=1;
void output_Text(float x, float y, char *text)
{
    glColor3f(1, 0, 0);//text color red
    glRasterPos3f(x, y, 0);
    int len, i;
    len = (int)strlen(text);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}
void Output_CurMenu(int menu)
{
    if (menu==menu1) output_Text(-3.0,-1.2,"Color menu");
    if (menu==menu2) output_Text(-3.0,-1.2,"Speed menu");
    if (menu==menu3) output_Text(-3.0,-1.2,"Surface menu");
    output_Text(-3.0,-1.0,"F1- switch menu");
}
void changeSize(GLsizei w, GLsizei h)
{
    if(h == 0)
    h = 1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,x,y,z-1,0.0,1.0,0.0);
}

float sx(float u,float v)
{
    switch(cur_sur) {
        case Sur1 : return u;
        case Sur2 : return sin(2.5*u);
        case Sur3 : return u;
    }
    return 0;
}

float sy(float u,float v)
{
    switch(cur_sur) {
        case Sur1 : return u*u-v*v;
        case Sur2 : return u*u-v*v;
        case Sur3 : return 2*exp(-u*u-v*v);
    }
    return 0;
}

float sz(float u,float v)
{
    return v;
}

void displaySurface()
{
    int i, j;
    float stepi,stepj,ui,vj,uip1,vjp1;
    float xij,yij,zij;
    float xip1j,yip1j,zip1j;
    float xijp1,yijp1,zijp1;
    float xip1jp1,yip1jp1,zip1jp1;
    stepi=float(2/ni);
    stepj=float(2/nj);
    for (j = 0; j <= nj-1; j++)
    {
        for (i = 0; i <= ni-1; i++)
        {
            ui=-1+i*stepi;
            vj=-1+j*stepj;
            uip1=-1+(i+1)*stepi;
            vjp1=-1+(j+1)*stepj;
            xij=sx(ui,vj);
            yij=sy(ui,vj);
            zij=sz(ui,vj);
            xip1j=sx(uip1,vj);
            yip1j=sy(uip1,vj);
            zip1j=sz(uip1,vj);
            xip1jp1=sx(uip1,vjp1);
            yip1jp1=sy(uip1,vjp1);
            zip1jp1=sz(uip1,vjp1);
            xijp1=sx(ui,vjp1);
            yijp1=sy(ui,vjp1);
            zijp1=sz(ui,vjp1);
            glColor3f(0.3, 0.3, 0.3);
            glBegin(GL_QUADS);
            glVertex3f(xij,yij,zij);
            glVertex3f(xip1j,yip1j,zip1j);
            glVertex3f(xip1jp1,yip1jp1,zip1jp1);
            glVertex3f(xijp1,yijp1,zijp1);
            glEnd();
            glColor3f(red, green, blue);
            glBegin(GL_LINE_LOOP);
            glVertex3f(xij,yij,zij);
            glVertex3f(xip1j,yip1j,zip1j);
            glVertex3f(xip1jp1,yip1jp1,zip1jp1);
            glVertex3f(xijp1,yijp1,zijp1);
            glEnd();
        }
    }
}
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotated(angle,0,1,0);
    if(cur_sur==Sur3) glTranslated(0,-1,0);
    displaySurface();
    glPopMatrix();
    angle=angle+inc_angle;
    Output_CurMenu(cur_menu);
    glutSwapBuffers();
}

void Do_Nothing()
{ }

void processSpecialKeys(int c, int x, int y)
{
    if ((c == GLUT_KEY_F1)&&(!flag))
    {
        cur_menu = glutGetMenu();
        if (cur_menu==menu1) {glutSetMenu(menu3); cur_menu=menu3;}
        else if (cur_menu==menu2) {glutSetMenu(menu1); cur_menu=menu1;}
        else if (cur_menu==menu3) {glutSetMenu(menu2); cur_menu=menu2;}
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void process_Menu_Color(int option)
{
    switch (option) {
        case RED : red = 1.0; green = 0.0; blue = 0.0; break;
        case GREEN : red = 0.0; green = 1.0; blue = 0.0; break;
        case BLUE : red = 0.0; green = 0.0; blue = 1.0; break;
        case WHITE : red = 1.0; green = 1.0; blue = 1.0; break;
    }
}
void process_Menu_Speed(int option)
{
    switch (option) {
        case LOW : inc_angle=0.1; break;
        case MEDIUM: inc_angle=1; break;
        case HIGH : inc_angle=3; break;
        case Stop : glutIdleFunc(Do_Nothing); break;
        case Resume :  glutIdleFunc(display); break;
    }
}


void process_Menu_Surface(int option)
{
    switch(option) {
        case Sur1 : cur_sur=1; break;
        case Sur2 : cur_sur=2; break;
        case Sur3 : cur_sur=3; break;
    }
}
void createGLUTMenus() {
    menu1=glutCreateMenu(process_Menu_Color);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("White",WHITE);
    menu2=glutCreateMenu(process_Menu_Speed);
    glutAddMenuEntry("Low",LOW);
    glutAddMenuEntry("Medium",MEDIUM);
    glutAddMenuEntry("High",HIGH);
    glutAddMenuEntry("Stop",Stop);
    glutAddMenuEntry("Resume",Resume);
    menu3=glutCreateMenu(process_Menu_Surface);
    glutAddMenuEntry("Surface 1",Sur1);
    glutAddMenuEntry("Surface 2",Sur2);
    glutAddMenuEntry("Surface 3",Sur3);
    cur_menu=menu3;
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void processMenuStatus(int status, int x, int y) {
    if (status == GLUT_MENU_IN_USE)
    flag = true; else flag = false;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,360);
    glutCreateWindow("Problem 3");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(changeSize);
    glutMenuStatusFunc(processMenuStatus);
    glutSpecialFunc(processSpecialKeys);
    createGLUTMenus();
    glutMainLoop();
    return(0);
}
