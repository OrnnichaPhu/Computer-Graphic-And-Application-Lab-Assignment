//
//  main.cpp
//  Problem_1
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

//coordinate axes
float ax[3] = {30, 0, 0};
float ay[3] = {0, 30, 0};
float az[3] = {0, 0, 30};

bool finish=false;

float t=0, dt=0.01;
float t1=0, dt1=0.01;
float t2=0, dt2=0.01;

double xp[]={0,0,0,0};
double yp[]={3,2,1,0};
double zp[]={0,0,0,0};

double shiftx,shifty,shiftz;//position of the RectX
double shiftx2,shifty2,shiftz2;//position of the RectY
double shiftx3,shifty3,shiftz3;//position of the RectZ

int n=(int)sizeof(xp)/sizeof(double);//number of points

double f(double *p,double t){
    int i;
    double returnf;
    for (i=1;i<=n-1;i++)
        if ((t<=i)&&(t>=i-1))
        {
            returnf=p[i]*(t-i+1)+p[i-1]*(i-t);
            break;
        }
    return returnf;
}// general interpolation based on array p;
double x1(double t){return f(xp,t);}// x- interpolation
double y1(double t){return f(yp,t);} //y interpolation
double z1(double t){return f(zp,t);} //- z interpolation


double x2(double t){return f(xp,t);}// x- interpolation
double y2(double t){return f(yp,t);} //y interpolation
double z2(double t){return f(zp,t);} //- z interpolation

double x3(double t){return f(xp,t);}// x- interpolation
double y3(double t){return f(yp,t);} //y interpolation
double z3(double t){return f(zp,t);} //- z interpolation

void Trajectory1(){
    shiftx=x1(t);
    shifty=y1(t);
    shiftz=z1(t);
}//changes global variables shiftx, shifty, shiftz to move the RectX

void Trajectory2(){
    shiftx2=x2(t1);
    shifty2=y2(t1);
    shiftz2=z2(t1);
    
}//changes global variables shiftx, shifty, shiftz to move the RectY

void Trajectory3(){
    shiftx3=x3(t2);
    shifty3=y3(t2);
    shiftz3=z3(t2);
    
}//changes global variables shiftx, shifty, shiftz to move the RectZ


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
    glColor3f(0, 0, 0);
    plot_Vector(ax);
    glColor3f(0, 0, 0);
    plot_Vector(ay);
    glColor3f(0, 0, 0);
    plot_Vector(az);
}//plot axis

void myInit3d(GLsizei w, GLsizei h){
    glClearColor(1, 1, 1, 0);
    glColor3f(1.0, 0.0, 0.0);     // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); // reset the Current Modelview Matrix //
    //glViewport(0, 0, w, h);
    //glOrtho(-1,1,-1,1,-1,1);//ortho view
    gluPerspective(70, 1.0,0.01, 1000);//perspective view
    gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //the coordinate system, the window and glLookAt in your assignment
    //can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}

void draw_Circle(GLfloat R, GLint N, GLint s){
    glPushMatrix();
    //glColor3f(0, 0, 1);
    glutWireSphere(R, N, s);
    glPopMatrix();
}

void Move_Circle1(){
    glPushMatrix();
    Trajectory1();
    glTranslatef(shiftx,shifty,shiftz);
    glColor3f(0.0, 0.0, 1.0);
    draw_Circle(1, 25, 25);
    glPopMatrix();
}

void Move_Circle2(){
    glPushMatrix();
    Trajectory2();
    glTranslatef(shiftx2,shifty2,shiftz2);
    glColor3f(1.0, 0.0, 0.0);
    draw_Circle(0.5, 25, 25);
    glPopMatrix();
}

void Move_Circle3(){
    glPushMatrix();
    Trajectory3();
    glTranslatef(shiftx3,shifty3,shiftz3);
    glColor3f(0.0, 0.0, 0.0);
    draw_Circle(0.25, 25, 25);
    glPopMatrix();
}

void draw_Something(){
    glPushMatrix();
    plot_Axis();
    Move_Circle1();
    t=t+dt;
    if (t>=n-1) t=n-1;
    if (t == n-1){
        Move_Circle2();
        t1=t1+dt1;
        if (t1>n-1) t1=n-1;
        if (t1 == n-1) {
            Move_Circle3();
            t2 = t2+dt2;
        }
        if (t2>n-1) {
            t2=n-1;
            finish=true;
        }
    }
    
    glPopMatrix();

}


void myDisplay(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_Something();
    glutSwapBuffers(); // for swap draw animation
}
void Do_Nothing(){}

void Idle_Function(){
    if (finish) Do_Nothing(); else myDisplay();
}



int main(int argc, char **argv){
    glutInit(&argc, argv);                       //should be called before any other GLUT routine.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode
    glutInitWindowSize(500, 500);           //Set the window size.
    glutInitWindowPosition(500, 550);                //position of the OpenGL window
    glutCreateWindow("Final-exam | Problem 1");                   // Create an OpenGL window with a title.
    //myInit3d();                                     //Initialize
    glutReshapeFunc(myInit3d);                      //Initialize
    glutDisplayFunc(myDisplay);                  //callback drawing routine
    glutIdleFunc(Idle_Function);                        //run animation
    glutMainLoop();                              //infinite loop
    return 0;
}
