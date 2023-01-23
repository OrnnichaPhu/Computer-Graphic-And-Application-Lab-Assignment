//
//  main.cpp
//  P4
//
//  Created by Ornnicha Phueaksri on 8/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<stdio.h>
#include<math.h>




#define ROTATE_SCENE 1
#define MOVE_BALL 2
#define CHANGE_BALL 3
#define ROTATE_CUBE 4

void output_Text(float x,float y,char *text){
    int len,i;
    glColor3f(1,0,0);
    glRasterPos3f(x,y,0);
    len=(int)strlen(text);
    for(i=0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
    }
}

float ax[3]={25,0,0};
float ay[3]={0,25,0};
float az[3]={0,0,25};
void plot_arrow(float v1[3],float v2[3]){
    glBegin(GL_LINES);
        glVertex3fv(v1);
        glVertex3fv(v2);
    glEnd();
}
void plot_vector(float v[3]){
    float zero[3]={0,0,0};
    plot_arrow(zero,v);
}
void plot_axes(){
    glColor3f(0,0,0);
    plot_vector(ax);
    plot_vector(ay);
    plot_vector(az);
}
void draw_1point(double x,double y,double z){
    glColor3d(1,1,0);
    glPointSize(10);
    glBegin(GL_POINTS);
        glVertex3d(x,y,z);
    glEnd();
}

double shiftx,shifty,shiftz;
double angle_sc=-90,angle_cb=0,dangle=0.02;
double t=0, dt=0.05;

double xp[]={0,-0.5,-0.5,0.5,0.5,0,0,0,0};
double yp[]={-0.5,-0.5, 0.5,0.5,-0.5,-0.5,-0.5, 0.5,1.0};
double zp[]={0,0,0,0,0,0,-3,-3,-4};
int n = (int)sizeof(xp)/sizeof(double);
int color_mode = 1;
bool move=false,rotate_sc=false,rotate_cb=false;
bool change_color=true;

double f(double *p,double t){
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
double x(double t){
    return f(xp,t);
}
double y(double t){
    return f(yp,t);
}
double z(double t){
    return f(zp,t);
}

void trajectory(){
    shiftx=x(t);
    shifty=y(t);
    shiftz=z(t);
}
void drawTrajectory(){
    double t,dt=0.5;
    glColor3d(0,0,1);
    glBegin(GL_LINE_STRIP);
        for(t=0;t<=n-1;t+=dt){
            glVertex3d(x(t),y(t),z(t));
        }
    glEnd();
}
void draw_points(){
    glColor3d(0,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
        for(int i=0;i<=n-1;i++){
            glVertex3d(xp[i],yp[i],zp[i]);
        }
    glEnd();
}
void myInit(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25,1.0,.01,10000);
    gluLookAt(15,12,12,0,0,0,0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void display_cube(double R){
    glPushMatrix();
    glTranslated(xp[n-1],yp[n-1],zp[n-1]);
    glRotatef(angle_cb,0,1,0);
    if(rotate_cb){
        glColor3f(1.0,0.0,0.0);
    }else{
        glColor3f(0.0,0.0,0.0);
    }
    glutWireCube(R);
    glPopMatrix();
}

void display_sphere(double R){
    if(change_color){
        if(dt>=0){
            glColor3f(0.8,0.8,0.8);
            color_mode=2;
        }else{
            glColor3f(0,0,0);
            color_mode=1;
        }
    }else{
        if(color_mode==1){
            glColor3f(0,0,0);
        }else{
            glColor3f(0.8,0.8,0.8);
        }
    }
    glutSolidSphere(R,10,10);
    glColor3f(1,1,0);
    glutWireSphere(R+0.01,10,10);
}

void display_move(){
    glPushMatrix();
    glRotatef(angle_sc,0,1,0);
    draw_points();
    drawTrajectory();
    trajectory();
    display_cube(1);
    glTranslated(shiftx,shifty,shiftz);
    display_sphere(0.3);
    glPopMatrix();
    //plot_axes();
    draw_1point(0,0,0);
    output_Text(-5,-10,"right click for menu");
}
void myDisplay(){
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    display_move();
    if(move){t+=dt;}
    if(rotate_sc){angle_sc+=dangle;}
    if(rotate_cb){angle_cb+=dangle;}
    if((fabs(t)>=n-1)||(t<0)){dt*=-1;}
    glutSwapBuffers();
}

void processMenu(int option){
    switch(option){
        case ROTATE_SCENE: rotate_sc=!rotate_sc;       break;
        case MOVE_BALL:    move=!move;                 break;
        case CHANGE_BALL:  change_color=!change_color; break;
        case ROTATE_CUBE:  rotate_cb=!rotate_cb;       break;
        default: break;
    }
}

void createGLUTMenu(){
    int menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Rotate All/Stop",ROTATE_SCENE);
    glutAddMenuEntry("Move Ball/Stop",MOVE_BALL);
    glutAddMenuEntry("Change/Do not change the ball color",CHANGE_BALL);
    glutAddMenuEntry("Rotate/Stop the cube",ROTATE_CUBE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Problem 4");
    myInit();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    createGLUTMenu();
    glutMainLoop();
    return 0;
}
