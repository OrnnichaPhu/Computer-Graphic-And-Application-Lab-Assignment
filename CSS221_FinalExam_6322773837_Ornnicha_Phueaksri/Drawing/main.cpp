//
//  main.cpp
//  Drawing
//
//  Created by Ornnicha Phueaksri on 7/5/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLsizei screen_height = 500;
int px=25, py=25;
float red=1, green=0, blue=0;
bool grab=false;
unsigned char data[4];
void reDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(red,green,blue);
    glRectd(px-25,py-25,px+25,py+25);
    printf("pgx=%d,pgy=%d\n",px,py);
    glutSwapBuffers();
}
void Reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, w, 0.0, h); // set a new math coordinate system which fits the window
    glClearColor(1, 1, 1, 0);//clear the screen
    glMatrixMode(GL_MODELVIEW);
    screen_height = h;
    reDraw();
}
void myMove(int x, int y)
{
    printf("call mymove, grab=%d\n",grab);
    if (grab) // if the mouse pressed
    {
        px=x; //new coordinates
        py=screen_height-y;
        reDraw();//redraw with the new coordinates
        
    }
}
void myColor()
{
    red=1-red; //swap the colors and redraw
    blue=1-blue;
    reDraw();
}
void NormalKeys(unsigned char key, int x, int y)
{
    if ((key=='c') || key=='C') myColor();
}
void myRead(GLfloat x, GLfloat y)//generate grab=true or false
{ //if the glReadPixels reads red or blue pixel grab=true
    // the color range is 0-255, 255 = max intensity
    glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE, data);//read pixel
    //data[0]-red, data[1]- green, data[2]- blue
    grab=false;
    if ((data[0]==255)&&(data[1]==0)&data[2]==0) grab=true;
    if ((data[0]==0)&&(data[1]==0)&& data[2]==255) grab=true;
    printf("p0=%u,p1=%u,p2=%u,p3=%u\n",data[0],data[1],data[2],data[3]);
}
void mouse(int button, int state, int x, int y)
{
    if (state== GLUT_DOWN)
        myRead(x,screen_height-y);//read pixel on left
    printf("call mouse, grab=%d\n",grab);
}
void Init(void) {
    glClearColor(1, 1, 1, 0);
    glColor3d(1,0,0);
    glPointSize(2);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Example 11 grab");
    Init();
    glutDisplayFunc(reDraw);
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(myMove);
    glutKeyboardFunc(NormalKeys);
    glutMainLoop();
}
