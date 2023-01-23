//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 7/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define XAXIS 1
#define YAXIS 2
#define ZAXIS 3
#define DIAGONAL 4

#define BLACK 1
#define DARKGREY 2
#define GREY 3

//coordinate axes
float ax[3] = {25, 0, 0};
float ay[3] = {0, 20, 0};
float az[3] = {0, 0, 25};

//coordination camera
GLfloat x=20.0, y=20.0, z=20.0;
GLfloat vx=0.0, vy=1.0, vz=0.0;

//Solid color
GLfloat red=0.0, green=0.0, blue=0.0;
bool Posmenu = true;

void Time_Delay(int dur){
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur){}
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


void DrawShape() {
    glColor3f(red, green, blue);
   
    glPushMatrix();
    
    glutSolidSphere(5.5,20,20);
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(5.5,20,10);
    
    glPushMatrix();
    
    glColor3f(red, green, blue);
    glTranslatef(0.0f, 8.0, 0.0f);
    glutSolidSphere(2.5,20,20);
    glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(2.5,20,10);
    
    glPopMatrix();

    glColor3f(red, green, blue);
    glTranslatef(5.5, 0.5, 0.0);
    glutSolidSphere(2.5,20,20);
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(2.5,20,10);
    
    glPopMatrix();
    
}


void myInit3d(void){
    glClearColor(1, 1, 1, 0);
    glColor3f(1.0, 0.0, 0.0);     // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); // reset the Current Modelview Matrix //
    glOrtho(-1,1,-1,1,-1,1);//ortho view
    gluPerspective(45, 1.33, .01, 1000);//perspective view
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, vx, vy, vz);
    //the coordinate system, the window and glLookAt in your assignment
    //can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    // glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}


void draw_Something(){
    glPushMatrix();
    plot_Axis();
    DrawShape();
    glPopMatrix();
}

void myDisplay(void){
    // glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_Something();
    glutSwapBuffers(); // for swap draw animation
}

void Menu_View(int option){
    switch (option){
        case XAXIS : x = 30.0; y = 0.0; z = 0.0;  vx =0.0; vy =1.0; vz =0.0; break;
        case YAXIS : x = 0.0; y = 30.0;  z = 0.0; vx =1.0; vy =1.0; vz =0.0; break;
        case ZAXIS : x = 0.0; y = 0.0;  z = 30.0; vx =0.0; vy =1.0; vz =0.0; break;
        case DIAGONAL : x =20.0; y =20.0; z =20.0; vx =0.0; vy =1.0; vz =0.0; break;
            
    }
    myInit3d();
}

void Menu_color(int option){
    switch (option){
        case BLACK : red = 0.0; green = 0.0; blue = 0.0; break;
        case DARKGREY : red= 0.4; green= 0.4; blue = 0.4; break;
        case GREY : red= 0.8; green = 0.8; blue = 0.8; break;
    }
    
}

void createGLUTMenus1(){
    int Position_menu = glutCreateMenu(Menu_View);
    glutAddMenuEntry("X Axis",XAXIS);
    glutAddMenuEntry("Y Axis",YAXIS);
    glutAddMenuEntry("Z Axis",ZAXIS);
    glutAddMenuEntry("Diagonal",DIAGONAL);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

void createGLUTMenus2(){
    int color_menu = glutCreateMenu(Menu_color);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("Darkgrey",DARKGREY);
    glutAddMenuEntry("Grey",GREY);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void SpecialKeys(int c, int x, int y){
    if (c == GLUT_KEY_F1) {
        Posmenu= !Posmenu;
    }
    if(Posmenu)
        createGLUTMenus1();
    else
        createGLUTMenus2();
}

void keyboardCB( unsigned char key, int x, int y ){
    switch ( key ){
        case 27: exit (0); break; // Escape key
    }
    glutPostRedisplay();
}//Close Window

int main(int argc, char **argv){
    glutInit(&argc, argv);                       //should be called before any other GLUT routine.
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // Set display mode
    glutInitWindowSize(500, 500);           //Set the window size.
    glutInitWindowPosition(480, 580);                //position of the OpenGL window
    glutCreateWindow("Practice_Test2");                   // Create an OpenGL window with a title.
    myInit3d();                                     //Initialize
    glutDisplayFunc(myDisplay);                  //callback drawing routine
    glutIdleFunc(myDisplay);                        //run animation
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(keyboardCB);
    createGLUTMenus1();
    glutMainLoop();                              //infinite loop
    return 0;
}
