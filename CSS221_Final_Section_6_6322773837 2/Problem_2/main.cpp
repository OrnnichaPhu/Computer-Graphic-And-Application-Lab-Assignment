//
//  main.cpp
//  Problem_2
//
//  Created by Ornnicha Phueaksri on 11/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <cstdlib>

//Define value of pi
# define Pi 3.141592

# define reverse 1

//coordinate axes
float ax[3] = {30, 0, 0};
float ay[3] = {0, 30, 0};
float az[3] = {0, 0, 30};

float i[] = {0,120,240};

float t=0, dt=0.1;
float t1=0, dt1=0.3;

bool flag=false;
bool rev = false;

GLfloat posX;
GLfloat posY;

//All initial set up
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}

void plot_Arrow(float v1[3], float v2[3]){
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}//plot arrow
void plot_Vector(float v[3]){
    float zero[3] = {0, 0, 0};
    plot_Arrow(zero, v);
}//plot vector
void plot_Axis(){
    glColor3f(1, 0, 0);
    plot_Vector(ax);
    glColor3f(0, 1, 0);
    plot_Vector(ay);
    glColor3f(0, 0, 1);
    plot_Vector(az);
}//plot axis

void output_Text(float x, float y, char *text){
    int len, i;
    glColor3f(0, 0, 1);
    glRasterPos2f(x, y);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void myInit3d(GLsizei w, GLsizei h){
    glClearColor(1, 1, 1, 0);
    glColor3f(1.0, 0.0, 0.0);     // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); // reset the Current Modelview Matrix //
    //glViewport(0, 0, w, h);
    //glOrtho(-1,1,-1,1,-1,1);//ortho view
    gluPerspective(45, 1.33, .01, 1000);//perspective view
    gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //the coordinate system, the window and glLookAt in your assignment
    //can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}

void Position(GLint i){
    posX = 5.9*cos(2*Pi*i/360);
    posY = 5.9*sin(2*Pi*i/360);
}

void draw_Polygon(GLfloat xc, GLfloat yc,GLint N, GLfloat R){
    glLineStipple(1, 0xFFFF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(0,0,1);
    for(int i=0;i<=N;i++){
        glVertex2f(xc + R*cos(2*Pi*i/N), yc + R*sin(2*Pi*i/N));
    }
    glEnd();
    glFlush();
}

void draw_Traiangle(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    for(int n=0; n<4;n++){
        Position(i[n]);
        glVertex2f(posX, posY);
    }
    glEnd();
    glFlush();
}

void drawPoint(float x,float y,float z){
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3d(0, 0, 1);
    glVertex3f(x,y,z);
    glEnd();
}

void Move_Circle(){
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(t, 0, 0, 1);
    draw_Polygon(0, 0, 100, 5.9);
    glPopMatrix();
}

void Move_trianglr(){
    glPushMatrix();
    glRotatef(t1, 0, 1, 0);
    draw_Traiangle();
    glPopMatrix();
}
void draw_Something(){
    //plot_Axis();
    Move_Circle();
    Move_trianglr();
    if(!flag){
        if(rev){
            t -= dt;
            t1 += dt1;
        }
        else{
            t += dt;
            t1 -= dt1;
        }
    }
    drawPoint(0, 0, 0);
    output_Text(-3.5,-7,"Right click for menu...");
}


void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    draw_Something();
    glutSwapBuffers(); // for swap draw animation
}

void Do_Nothing(){}

void rotate_change(int option){
    switch (option) {
        case reverse: rev = !rev; break;
    }
    
}

void processMenuStatus(int status, int x, int y){
    if (status == GLUT_MENU_IN_USE)
        flag = true; else flag = false;
    
}//check whether the menu is in use

void createGLUTMenus(){
    int menu = glutCreateMenu(rotate_change);
    glutAddMenuEntry("Reverse ",reverse);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}





int main(int argc, char **argv){
    glutInit(&argc, argv);                       //should be called before any other GLUT routine.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500);           //Set the window size.
    glutInitWindowPosition(580, 500);                //position of the OpenGL window
    glutCreateWindow("Final-exam | Problem 2");                   // Create an OpenGL window with a title.
    //myInit3d();                                     //Initialize
    glutReshapeFunc(myInit3d);                      //Initialize
    glutDisplayFunc(myDisplay);                  //callback drawing routine
    glutIdleFunc(myDisplay);                        //run animation
    glutMenuStatusFunc(processMenuStatus);
    createGLUTMenus();
    glutMainLoop();                              //infinite loop
    return 0;
}
