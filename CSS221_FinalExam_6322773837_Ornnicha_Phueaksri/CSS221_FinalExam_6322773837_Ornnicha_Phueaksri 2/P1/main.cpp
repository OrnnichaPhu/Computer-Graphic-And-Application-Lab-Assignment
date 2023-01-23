//
//  main.cpp
//  P1
//
//  Created by Ornnicha Phueaksri on 7/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


# define Pi 3.141592

//Shiftx, Shifty position
GLfloat posX;
GLfloat posY;

//rotatation angle
GLfloat angle=0.0, dt=0.5;

//coordinate axes
float ax[3] = {25, 0, 0};
float ay[3] = {0, 20, 0};
float az[3] = {0, 0, 25};


void Time_Delay(int dur){
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur){}
}


void draw_Polygon(GLfloat xc, GLfloat yc,GLint N, GLfloat R){
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    for(int i=0;i<=N;i++){
        glVertex2f(xc + R*cos(2*Pi*i/N), yc + R*sin(2*Pi*i/N));    }
    glEnd();
    glFlush();
}

void draw_Circle(GLfloat R, GLint N, GLint s){
    glPushMatrix();
    glRotatef(angle, 0, 1, 0);
    glColor3f(0, 0, 1);
    glutWireSphere(R, N, s);
    glPopMatrix();
}

void drawPoint(float x,float y,float z){
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3d(1, 0, 0);
    glVertex3f(x,y,z);
    glEnd();
}

void TranSphere(GLint i){
    glPushMatrix();
    posX = 12.9*cos(2*Pi*i/500);
    posY = 12.9*sin(2*Pi*i/500);
    drawPoint(posX, posY, 0);
    glTranslatef(posX, posY, 0);
    draw_Circle(4, 25, 15);
    glPopMatrix();
}

void Mymove(){
    glPushMatrix();
    TranSphere(125);
    TranSphere(250);
    TranSphere(375);
    TranSphere(500);
    glPopMatrix();
}


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


void draw_Something(){
    plot_Axis();
    draw_Polygon(0, 0, 500, 12.9);
    Mymove();
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    draw_Something();
    angle += dt;
    glutSwapBuffers(); // for swap draw animation
}

void keyboardCB( unsigned char key, int x, int y ){
    switch ( key ){
        case 27: exit (0); break; // Escape key
    }
    glutPostRedisplay();
}//Close Window

int main(int argc, char **argv){
    glutInit(&argc, argv);                       //should be called before any other GLUT routine.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500);           //Set the window size.
    glutInitWindowPosition(480, 580);                //position of the OpenGL window
    glutCreateWindow("Practice_Test1");                   // Create an OpenGL window with a title.
    //myInit3d();                                     //Initialize
    glutReshapeFunc(myInit3d);                      //Initialize
    glutKeyboardFunc(keyboardCB);
    glutDisplayFunc(myDisplay);                  //callback drawing routine
    glutIdleFunc(myDisplay);                        //run animation
    glutMainLoop();                              //infinite loop
    return 0;
    
}
