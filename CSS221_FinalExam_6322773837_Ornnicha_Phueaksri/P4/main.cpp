//
//  main.cpp
//  P4
//
//  Created by Ornnicha Phueaksri on 8/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//coordinate axes
float ax[3] = {30, 0, 0};
float ay[3] = {0, 30, 0};
float az[3] = {0, 0, 30};


float t=0, dt=0.09;
float t1=0, dt1=0.09;
float t2=0, dt2=0.09;

double xp[]={0,0,0,0,0,0,0};
double yp[]={30,25,20,15,10,5,0};
double zp[]={0,0,0,0,0,0,0};

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

void Time_Delay(int dur){
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur){}
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
    glColor3f(1, 0, 0); //x-red
    plot_Vector(ax);
    glColor3f(0, 1, 0); //y-green
    plot_Vector(ay);
    glColor3f(0, 0, 1); //z-blue
    plot_Vector(az);
}//plot axis

void Plot_RectX(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 5, -2.5);
    glVertex3f(0, 5, 2.5);
    glVertex3f(0, 0, 2.5);
    glVertex3f(0, 0, -2.5);
    glEnd();
    glFlush();
}

void Plot_RectY(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-2.5, 5, 0);
    glVertex3f(2.5, 5, 0);
    glVertex3f(2.5, 0, 0);
    glVertex3f(-2.5, 0, 0);
    glEnd();
    glFlush();
}

void Plot_RectZ(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-2.5, 5, 2.5);
    glVertex3f(2.5, 5, -2.5);
    glVertex3f(2.5, 0, -2.5);
    glVertex3f(-2.5, 0, 2.5);
    glEnd();
    glFlush();
}

void Move_RactX(){
    glPushMatrix();
    Trajectory1();
    glTranslatef(shiftx,shifty,shiftz);
    Plot_RectX();
    glPopMatrix();
}

void Move_RactY(){
    glPushMatrix();
    Trajectory2();
    glTranslatef(shiftx2,shifty2,shiftz2);
    Plot_RectY();
    glPopMatrix();
}

void Move_RactZ(){
    glPushMatrix();
    Trajectory3();
    glTranslatef(shiftx3,shifty3,shiftz3);
    Plot_RectZ();
    glPopMatrix();
}

void draw_Something(){
    glPushMatrix();
    plot_Axis();
    Move_RactX();
    t=t+dt;
    if (t>=n-1) t=n-1;
    if (t == n-1){
        Move_RactY();
        t1=t1+dt1;
        if (t1>n-1) t1=n-1;
        if (t1 == n-1) {
            Move_RactZ();
            t2 = t2+dt2;
        }
        if (t2>n-1) t2=n-1;
    }
    
    glPopMatrix();
}

void myDisplay(void){
    // glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_Something();
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
