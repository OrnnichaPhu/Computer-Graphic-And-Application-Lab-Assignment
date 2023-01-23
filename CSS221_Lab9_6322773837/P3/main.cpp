//
//  main.cpp
//  P3
//
//  Created by Ornnicha Phueaksri on 1/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLfloat mat_specular1[] = { 0.0, 0.1, 0.3, 1.0 }; //blue for the Earth
GLfloat mat_specular2[] = { 0.3, 0.3, 0.0, 1.0 }; //yellow for the Sun
GLfloat mat_specular3[] = { 0.2, 0.2, 0.2, 1.0 }; //grey for the Moon
GLint year_Earth = 0, day_Earth = 0;
GLint year_Moon=0, day_Moon=0;
GLint dyearE=1, ddayE=0.5;
GLint dyearM=2, ddayM=0.25;
int slices=25, stacks=25;

void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.3);
    glShadeModel (GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void drawplanet(GLfloat rad)
{
    glutSolidSphere(rad, slices, stacks);
    glColor3f(0,0,0);//black wire
    glutWireSphere(rad,slices, stacks);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    // Earth matrix
    glPushMatrix();
    glRotatef (year_Earth, 0.0, 1.0, 0.0);
    glTranslatef (2.0, 0.0, 0.0);
    glRotatef (day_Earth, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
    drawplanet(0.5);
    
    // Moon Matrix
    glPushMatrix();
    glRotatef (year_Moon, 0.0, 1.0, 0.0);
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef (day_Moon, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
    drawplanet(0.2);
    
    glPopMatrix();
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
    drawplanet(1);//the Sun
    
    year_Earth=year_Earth+dyearE;
    day_Earth=day_Earth+ddayE;
    year_Moon=year_Moon+dyearM;
    day_Moon=day_Moon+ddayM;
    glutSwapBuffers();
    Time_Delay(50);
}
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("problem 3 Sun-Earth-Moon");
    init ();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
