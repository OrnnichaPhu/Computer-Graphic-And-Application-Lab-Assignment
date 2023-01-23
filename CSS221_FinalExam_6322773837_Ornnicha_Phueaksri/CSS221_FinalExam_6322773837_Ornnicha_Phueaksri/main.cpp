//
//  main.cpp
//  CSS221_FinalExam_6322773837_Ornnicha_Phueaksri
//
//  Created by Ornnicha Phueaksri on 7/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLsizei sw=500, screen_height = 500;
int px, py;
bool draw = false;
void reDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glEnd();
    glFlush();
}
void Reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, w, 0.0, h); // set a new math coordinate system which fits the window
    glClearColor(1, 1, 1, 0);//clear the screen
    glMatrixMode(GL_MODELVIEW);
    screen_height = h;
    sw=w;
    reDraw();
}
void myMove(int x, int y)
{
    //draw = true;
    if (draw)
    {
        float p2x=x; //new coordinates
        float p2y=screen_height-y;
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(p2x, p2y);
        glEnd();
        glFlush();
        px = p2x;
        py = p2y;
    }
}
void mouse(int button, int state, int x, int y)
{
    if (button==GLUT_LEFT_BUTTON && state== GLUT_DOWN) {
       px=x; //new coordinates
       py=screen_height-y;
       glBegin(GL_POINTS);
       glVertex2f(px, py);
       glEnd();
       glFlush();
        draw=true;
    }
    if (state== GLUT_UP)
    {
        reDraw();
        draw=false;
    }
}
void Init(void)
{
    glClearColor(1, 1, 1, 0);
    glColor3d(0,0,1);
    glLineWidth(2);
}

void keyboardCB( unsigned char key, int x, int y ){
    switch ( key ){
        case 27: exit (0); break; // Escape key
    }
    glutPostRedisplay();
}//Close Window

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(sw, screen_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Exam problem");
    glutKeyboardFunc(keyboardCB);
    Init();
    glutDisplayFunc(reDraw);
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(myMove);
    glutMainLoop();
}
