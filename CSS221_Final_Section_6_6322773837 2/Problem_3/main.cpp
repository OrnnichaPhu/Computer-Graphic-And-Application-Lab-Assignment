//
//  main.cpp
//  Problem_3
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

#define RED 1
#define BLUE 2
#define GREEN 3
#define GREY 4

//coordinate axes
float ax[3] = {30, 0, 0};
float ay[3] = {0, 30, 0};
float az[3] = {0, 0, 30};

bool flag=false;

GLsizei sw=500, screen_height = 500;
int px, py;
int ipx, ipy;
bool draw = false;

float red=1, green=0, blue=0;

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


void myInit3d(GLsizei w, GLsizei h){
    glClearColor(1, 1, 1, 0);
    glColor3f(1.0, 0.0, 0.0);     // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); // reset the Current Modelview Matrix //
    glViewport(0, 0, w, h);
    glOrtho(-1,1,-1,1,-1,1);//ortho view
    gluPerspective(45, 1.33, .01, 1000);//perspective view
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //the coordinate system, the window and glLookAt in your assignment
    //can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}

void reDraw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glEnd();
    glFlush();
}


void Reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, w, 0.0, h); // set a new math coordinate system which fits the window
    glClearColor(1, 1, 1, 0);//clear the screen
    glMatrixMode(GL_MODELVIEW);
    screen_height = h;
    reDraw();
}



void Draw_Recti(int x1, int y1, int x2, int y2)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(red,green,blue);
    glRectd(x1,y1,x2,y2);
    glutSwapBuffers();
}

void draw_Something(){
    plot_Axis();
    
}

void myMove(int x, int y){
    //draw = true;
    if (draw)
    {
        float p2x=x; //new coordinates
        float p2y=screen_height-y;
        Draw_Recti(ipx,ipy,px,py);
        px = p2x;
        py = p2y;
    }
}
void mouse(int button, int state, int x, int y){
    if (button==GLUT_LEFT_BUTTON && state== GLUT_DOWN) {
        px=x; //new coordinates
        py=screen_height-y;
        ipx = px;
        ipy = py;
        draw=true;
    }
    if (state== GLUT_UP)
    {
        draw=false;
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    draw_Something();
    glutSwapBuffers(); // for swap draw animation
}

void color(int option){
    switch (option)
    {
        case RED : red = 1.0; green = 0.0; blue = 0.0; break;
        case BLUE : red= 0.0; green= 0.0; blue = 1.0; break;
        case GREEN : red = 0.0; green = 1.0; blue = 0.0; break;
        case GREY : red= 0.4; green= 0.4; blue = 0.4; break;
    }
    //Draw_Recti(ipx,ipy,px,py);
}

void createGLUTMenus(){
    int color_menu=glutCreateMenu(color);
    glutAddMenuEntry("RED",RED);
    glutAddMenuEntry("BLUE",BLUE);
    glutAddMenuEntry("GREEN",GREEN);
    glutAddMenuEntry("GREY",GREY);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);                       //should be called before any other GLUT routine.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500);           //Set the window size.
    glutInitWindowSize(sw, screen_height);                //position of the OpenGL window
    glutCreateWindow("Final-exam | Problem 3");                   // Create an OpenGL window with a title.
    //myInit3d();                                     //Initialize
    glutReshapeFunc(Reshape); //Initialize
    glutMouseFunc(mouse);
    glutMotionFunc(myMove);
    glutDisplayFunc(reDraw);                  //callback drawing routine
    //glutIdleFunc(myDisplay);                        //run animation
    createGLUTMenus();
    glutMainLoop();                              //infinite loop
    return 0;
}
