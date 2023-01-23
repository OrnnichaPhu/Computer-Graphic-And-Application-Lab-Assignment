//
//  main.cpp
//  P0
//
//  Created by Ornnicha Phueaksri on 22/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <time.h>
#include <stdlib.h>

#define Axes 1
#define NoAxes 2
#define ColorAxes  3
#define ShadeSmooth 4
#define ShadeFlat 5
int  axes=1;
bool shade=false;
bool flag=false;
bool axesmenu=true;
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0 }; //specular light
GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0 }; //directional diagonal light
GLfloat DiffuseLight[4]={1,1,1,0};
GLfloat ang=0,dang=1;
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
float ax[3]={25,0,0}; float ay[3]={0,25,0}; float az[3]={0,0,25};//axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
     glVertex3fv(v1);
     glVertex3fv(v2);
     glEnd();
    }
void plot_Vector(float v[3]) //plot vector
{
float zero[3]={0,0,0};
plot_Arrow(zero,v);
}
void plot_Color_Axes()
{
glColor3f(1,0,0);
plot_Vector(ax);
glColor3f(0,1,0);
plot_Vector(ay);
glColor3f(0,0,1);
plot_Vector(az);
}
void plot_Black_Axes()
{
glColor3f(0,0,0);
plot_Vector(ax);
plot_Vector(ay);
plot_Vector(az);
}
void output_Text(float x, float y, char *text)
{  int len, i;
  glColor3f(0, 0, 0);
  glRasterPos3f(x, y, 0);
  len = (int)strlen(text);
  for (i = 0; i < len; i++) {
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
  }
}
void initlights(void)
{
glClearColor(0.0, 0.0, 0.0, 0.0);
glEnable(GL_DEPTH_TEST);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialf(GL_FRONT, GL_SHININESS, 125.0);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glLightfv(GL_LIGHT0, GL_DIFFUSE,  DiffuseLight);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glColorMaterial(GL_FRONT, GL_DIFFUSE);
glEnable(GL_COLOR_MATERIAL);
}
void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //reset the current Projection Matrix
    gluPerspective(45, 1.33, .01, 1000);//perspective view
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);// position and aim the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();// reset the current Modelview Matrix
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}
void Draw_Triangle()
{       glPushMatrix();
        glRotated(ang,1,0,0);
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(1, 0, 0);
        glColor3f(0,1,0);
        glVertex3f(20, 0, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 20, 0);
        glEnd();
        glPopMatrix();
        ang=ang+dang;
}
void myDisplay(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   if (shade) glShadeModel(GL_SMOOTH); else glShadeModel(GL_FLAT);
   if (axes==Axes) plot_Black_Axes();
   if (axes==ColorAxes)  plot_Color_Axes();
   if (axesmenu) output_Text(-10,-32,"Right click:Axes menu, F2-change");
   else output_Text(-10,-32, "Right click:Shade menu, F1-change");
   Draw_Triangle();
   glutSwapBuffers();
   Time_Delay(10);
}
void Menu(int option)
{
switch(option)
{
case Axes:        axes=1; break;
case NoAxes:      axes=2; break;
case ColorAxes:   axes=3; break;
case ShadeSmooth: shade=true; break;
case ShadeFlat:   shade=false; break;
}
}
void createGLUTMenus() //create menus
{
    int menu=glutCreateMenu(Menu);//call processMenuEvents on menu click
    glutAddMenuEntry("Draw axes",Axes);
    glutAddMenuEntry("Remove axes",NoAxes);
    glutAddMenuEntry("Color axes",ColorAxes);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
void processMenuStatus(int status, int x, int y) {
    if (status == GLUT_MENU_IN_USE)
        flag = true; else flag = false;
//check whether the menu is in use
// if it is in use you can not swap between them
}
void SpecialKeys(int c, int x, int y)
{
if ((c == GLUT_KEY_F2)&&(!flag)) // F2 pressed and menu is not in use
{
glutChangeToMenuEntry(1,"Shade Smooth",ShadeSmooth);//replace menu
glutChangeToMenuEntry(2,"Shade Flat",ShadeFlat);
while (glutGet(GLUT_MENU_NUM_ITEMS)>2)//remove all menu items >2
glutRemoveMenuItem(3);
axesmenu=false;
}
if ((c == GLUT_KEY_F1)&&(!flag)) // F1 pressed and menu is not in use
{
glutChangeToMenuEntry(1,"Draw axes",Axes);
glutChangeToMenuEntry(2,"Remove axes",NoAxes);
glutAddMenuEntry("Color axes",ColorAxes);
while (glutGet(GLUT_MENU_NUM_ITEMS)>3)//remove all menu items >3
glutRemoveMenuItem(4);
axesmenu=true;
}
}
int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Example 0 Triangle. Modifiable menu");
   myInit3d();
   glutDisplayFunc(myDisplay);
   glutIdleFunc(myDisplay);
   glutSpecialFunc(SpecialKeys);
   glutMenuStatusFunc(processMenuStatus);
   createGLUTMenus();
   glutMainLoop();
}
