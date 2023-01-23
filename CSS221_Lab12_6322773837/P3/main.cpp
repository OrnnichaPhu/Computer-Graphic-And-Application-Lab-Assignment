//
//  main.cpp
//  P3
//
//  Created by Ornnicha Phueaksri on 29/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <cstdlib>

#define ROTATE 1
#define STOP 2

#define RED 3
#define GREEN 4
#define BLUE 5

GLfloat wire_red=1,wire_green=0,wire_blue=0;
GLfloat sph_red=0.7,sph_green=0.7,sph_blue=0.7;
GLfloat x=0,y=0,z=0;
GLfloat t=0,dt=0.01;
GLfloat ang=0,dang=0.25;
float xp[]={3.00,-1.50,-1.50,3.00};
float yp[]={   0, 2.60,-2.60,   0};
float zp[]={   0,    0,    0,   0};
int n = (int)(sizeof(xp)/sizeof(float));
int color_mode=1;

bool animate=false,rotate=true,flag=false;

void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {}
}

float ax[3]={5,0,0}; float ay[3]={0,5,0}; float az[3]={0,0,5};//axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
     glVertex3fv(v1);
     glVertex3fv(v2);
     glEnd();
}

void plot_Vector(float v[3]){ //plot vector
    float zero[3]={0,0,0};
    plot_Arrow(zero,v);
}

void plot_Axis(){
    glColor3f(1,0,0);
    plot_Vector(ax);
    glColor3f(0,1,0);
    plot_Vector(ay);
    glColor3f(0,0,1);
    plot_Vector(az);
}

void output_Text(float x, float y, float z,char *text){ //output a text at x,y
    int len, i;
    glColor3f(0, 0, 0);
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void output_Number(float x, float y, float z, double v){ //output a number at x,y
  int len, i;
  char text [20]={'\0'};
  sprintf(text, "%lf", v); //converts v to the string "text"
  output_Text(x,y,z,text);
}

//Interpolation
float f(float *p,float t){
    int i;
    double returnf;
    for(i=1;i<=n-1;i++){
        if((t<=i)&&(t>=i-1)){
            returnf=p[i]*(t-i+1)+p[i-1]*(i-t);
            break;
        }
    }
    return returnf;
}

float xt(float t){
    return f(xp,t);
}

float yt(float t){
    return f(yp,t);
}

float zt(float t){
    return f(zp,t);
}

void drawPoint(float x,float y,float z){
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
}

void drawSphere(){
    glColor3f(sph_red,sph_green,sph_blue);
    glutSolidSphere(0.5,15,15);
    glColor3f(wire_red,wire_green,wire_blue);
    glutWireSphere(0.52,15,15);
    if(dt>=0){
        sph_red=0.7;sph_green=0.7;sph_blue=0.7;
        color_mode=2;
    }else{
        sph_red=0;sph_green=0;sph_blue=0;
        color_mode=1;
    }
}

void drawTrajectory(){
    GLfloat tt;
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
        for(tt=0;tt<=n-1;tt+=0.01){
            glVertex3f(xt(tt),yt(tt),zt(tt));
        }
    glEnd();
    glColor3f(0,0,0);
    for(int i=0;i<n;i++){
        drawPoint(xp[i],yp[i],zp[i]);
    }
}

void displayMove(){
    glPushMatrix();
    glRotatef(ang,0,1,0);
    drawTrajectory();
    float shiftx=xt(t);
    float shifty=yt(t);
    float shiftz=zt(t);
    if(shiftx==0&&shifty==0&&shiftz==0){
        shiftx=xp[0];
        shifty=yp[0];
        shiftz=zp[0];
    }
    //f(animate) printf("%f %f %f\n",shiftx,shifty,shiftz);
    glTranslatef(shiftx,shifty,shiftz);
    drawSphere();
    glPopMatrix();
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    //plot_Axis();
    glColor3f(1,1,0);
    drawPoint(0,0,0);
    output_Text(-1,-4.0,2,"Left-Click Move/Stop Sphere");
    output_Text(-1,-4.4,2,"Right-Click Menu");
    output_Text(-1,-4.8,2,"1,2 Change Menu");
    displayMove();
    glutSwapBuffers();
    if(animate){t+=dt;}
    if(rotate){ang+=dang;}
    if((fabs(t)>=n-1)||(t<0)){dt*=-1;}
    Time_Delay(25);
}

void myInit3d(void){
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluPerspective(25,1.0,.01,10000);
    gluLookAt(12,12,12,0,0,0,0,1,0);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
}

void doNothing(void){}

void processMenu(int option){
    switch(option){
    case ROTATE: rotate=true; break;
    case STOP: rotate=false; break;
    case RED:   wire_red=1;wire_green=0;wire_blue=0;break;
    case GREEN: wire_red=0;wire_green=1;wire_blue=0;break;
    case BLUE:  wire_red=0;wire_green=0;wire_blue=1;break;
    default: break;
    }
}

void processMenuStatus(int status,int x,int y){
    if(status==GLUT_MENU_IN_USE){
        flag=true;
    }else{
        flag=false;
    }
}

void createGLUTmenu(){
    int menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Rotate",ROTATE);
    glutAddMenuEntry("Stop",STOP);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processNormalKey(unsigned char key, int x,int y){
    if(!flag){
        switch(key){
            case '1':
                glutChangeToMenuEntry(1,"Rotate",ROTATE);
                glutChangeToMenuEntry(2,"Stop",STOP);
                while(glutGet(GLUT_MENU_NUM_ITEMS)>2){
                    glutRemoveMenuItem(3);
                }
                break;
            case '2':
                glutChangeToMenuEntry(1,"Red",RED);
                glutChangeToMenuEntry(2,"Green",GREEN);
                glutAddMenuEntry("Blue",BLUE);
                while(glutGet(GLUT_MENU_NUM_ITEMS)>3){
                    glutRemoveMenuItem(4);
                }
                break;
            default: break;
        }
    }
}

void myMouse(GLint button, GLint state, GLint x, GLint y){
    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN){
            animate=!animate;
        }
        break;
    default: break;
    }
}

int main(int argc, char **argv){
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Pre-exam | Problem 3");
   myInit3d();
   glutDisplayFunc(myDisplay);
   glutIdleFunc(myDisplay);
   createGLUTmenu();
   glutMenuStatusFunc(processMenuStatus);
   glutKeyboardFunc(processNormalKey);
   glutMouseFunc(myMouse);
   glutMainLoop();
}
