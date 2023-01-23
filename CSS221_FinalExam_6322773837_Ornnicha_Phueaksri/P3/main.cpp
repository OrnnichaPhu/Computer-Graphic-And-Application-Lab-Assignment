//
//  main.cpp
//  P3
//
//  Created by Ornnicha Phueaksri on 7/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
GLfloat angle=0,dt=1;
bool rotate = false;

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
    //glViewport(0, 0, w, h);
    gluOrtho2D(-400, 400, -400, 400);
    //glOrtho(-1,1,-1,1,-1,1);//ortho view
    //gluPerspective(45, 1.33, .01, 1000);//perspective view
    //gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //the coordinate system, the window and glLookAt in your assignment
    //can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
   // glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
    angle=0.0;
}


void Draw_RotateRec(){
    glColor3d(0, 0, 1);
    glPushMatrix();
    glTranslatef(-150, -150, 0);
    glRotatef(angle, 0, 0, 1);
    glRecti(-50, -50, 50, 50);
    glPopMatrix();
    Time_Delay(50);
    glutSwapBuffers();
}
void draw_Something(){
  
    Draw_RotateRec();
 
}

void myDisplay(void){
   
    glClear(GL_COLOR_BUFFER_BIT);
    draw_Something();
    if(rotate)
        angle += dt;
    else
        angle = 0;
  
    
    
}
void Do_Nothing(void) {
    Draw_RotateRec();
   
}
void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        rotate = !rotate;
    glutIdleFunc(myDisplay);
    
    
    
}

int main(int argc, char **argv){
    glutInit(&argc, argv);                       //should be called before any other GLUT routine.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500);           //Set the window size.
    glutInitWindowPosition(480, 580);                //position of the OpenGL window
    glutCreateWindow("Practice_Test2");                   // Create an OpenGL window with a title.
    glutReshapeFunc(myInit3d);                                     //Initialize
    glutDisplayFunc(myDisplay);                  //callback drawing routine
    //glutIdleFunc(myDisplay);                        //run animation
    glutMouseFunc(mouse);
    glutMainLoop();                              //infinite loop
    return 0;
    
}
