//
//  main.cpp
//  P8
//
//  Created by Ornnicha Phueaksri on 18/3/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <cstdlib> //this is for randomization "rand"
#include <math.h> // math functions

bool start = false;
GLint wx=500;
GLint wy=500;
GLfloat X=250,Y=150;
GLfloat Size=100;
GLfloat Color[]={0,0,1,0};
const float Pi=3.14159265358979323846;
int set = 1;
bool decrease = true;
bool square = true;


void draw_Rectangle(GLfloat X, GLfloat Y,GLfloat size)
{
    glBegin (GL_POLYGON);
    glVertex2f(X-size/2,Y-size/2);
    glVertex2f(X+size/2,Y-size/2);
    glVertex2f(X+size/2,Y+size/2);
    glVertex2f(X-size/2,Y+size/2);
    glEnd ( );
}

void draw_Polygon(GLfloat xc, GLfloat yc,GLint N, GLfloat R){
    glBegin(GL_POLYGON);
    glColor3f(0,0,1);
    for (int i=0;i<=N;i++){
        glVertex2f(xc + R*cos(2*Pi*i/N), yc + R*sin(2*Pi*i/N));
    }
    glEnd();
    glFlush();
    
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4fv(Color);
    if(square)
        draw_Rectangle(X,Y,Size);
    else
        draw_Polygon(X,Y,100,40);
    glFlush();
}
void mouse(GLint button, GLint state, GLint x, GLint y)
{
    float Y1=wy-Y;
    if ((button==GLUT_RIGHT_BUTTON) and (state==GLUT_DOWN))
    {
     if (square)
         square = false;
    else
        square = true;
    myDisplay();
    }
    
    if ((button==GLUT_LEFT_BUTTON) and (state==GLUT_DOWN))
    {
        if ((x>=X-Size/2) && (x<=X+Size/2) && (y>=Y1-Size/2) && (y<=Y1+Size/2))
        {
            switch (set) {
                case 1:
                case 2:
                case 3:set++;
                    if(decrease)
                        Size/=2;
                    else
                        Size*=2;
                    break;
                case 4:set = 2;
                    if(decrease){
                        decrease = false;
                        Size*=2;
                    }
                    else{
                        decrease = true;
                        Size/=2;
                    }
                    break;
            }
        }
    }
    myDisplay();

}
void resize(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0*w, 0.0, 1.0*h);
    wx=w;
    wy=h;
}
void myInit(void)
{
    glClearColor(1, 1, 1, 0);
    glColor4fv(Color);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, wx, 0.0, wy); // set the word coordinate system
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wx, wy);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("problem 8");
    myInit();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutMainLoop(); }
