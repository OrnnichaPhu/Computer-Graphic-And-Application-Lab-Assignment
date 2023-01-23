//
//  main.cpp
//  P0''
//
//  Created by Ornnicha Phueaksri on 22/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


#define Axes 1
#define NoAxes 2
#define ColorAxes  3
#define ShadeSmooth 4
#define ShadeFlat 5

#define Triangle 1
#define Square 2
#define Pentagon 3

#define Hexagon 4
#define Heptagon 5
#define Octagon 6

#define nmax 4

float r[nmax];float g[nmax];float b[nmax]; //nmax colors for nmax vertices.

int n = 3;
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

void Draw_Triangle(){
    glPushMatrix();
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

void draw_Polygon(GLfloat R, GLint N)
{ GLfloat x, y; GLint i;
    glPushMatrix();
    glRotatef(ang,0,0,1);
    glBegin(GL_POLYGON);
    
    for (i=0;i<=N-1;i++)
    {
        x=R*cos(2*M_PI*i/N);
        y=R*sin(2*M_PI*i/N);
        glColor3f(r[i],g[i],b[i]);
        glVertex3f(x,y,0);
    }
    
    glEnd();
    glPopMatrix();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (axesmenu) output_Text(-23,-32,"Left click: color menu, 1,2-menu 1 or 2");
    else output_Text(-23,-32, "Left click: color menu, 1,2-menu 1 or 2");
    ang=ang+dang;
    draw_Polygon(15, n);
    glutSwapBuffers();
    Time_Delay(10);
}


/*
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
*/

void Menu(int option){
    switch (option) {
        //menu1
        case Triangle:  n = 3; break;
        case Square:    n = 4; break;
        case Pentagon:  n = 5; break;
        //menu2
        case Hexagon:   n = 6; break;
        case Heptagon:  n = 7; break;
        case Octagon:   n = 8; break;
        default: break;
    }
}

void createGLUTMenus() //create menus
{
    int menu=glutCreateMenu(Menu);//call processMenuEvents on menu click
    //menu1
    glutAddMenuEntry("Triangle",Triangle);
    glutAddMenuEntry("Square",Square);
    glutAddMenuEntry("Pentagon",Pentagon);
    //menu2
    glutAddMenuEntry("Hexagon",Hexagon);
    glutAddMenuEntry("Heptagon",Heptagon);
    glutAddMenuEntry("Octagon",Octagon);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}





/*
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
*/

void keyboardKeys(unsigned char key){
    switch (key) {
        case '1':
        {
            glutChangeToMenuEntry(1,"Triangle",Triangle);//replace menu
            glutChangeToMenuEntry(2,"Square",Square);
            glutChangeToMenuEntry(3,"Pentagon",Pentagon);
            while (glutGet(GLUT_MENU_NUM_ITEMS)>3)//remove all menu items >2
                glutRemoveMenuItem(4);
            axesmenu=false;
        }
            break;
            
        case '2':
        {
            glutChangeToMenuEntry(1,"Hexagons",Hexagon);
            glutChangeToMenuEntry(2,"Heptagon",Heptagon);
            glutChangeToMenuEntry(3,"Octagon",Octagon);
            glutAddMenuEntry("Color axes",ColorAxes);
            while (glutGet(GLUT_MENU_NUM_ITEMS)>3)//remove all menu items >3
                glutRemoveMenuItem(4);
            axesmenu=true;
        }
        default:
            break;
    }
}

void KeyboardKeys(unsigned char key,int x ,int y)
{
    keyboardKeys(key);
}

void myMouse(int button, int state, int x, int y){
    int i;
    if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN){
        for (i=0;i<=nmax-1;i++){
            //change r,g,b randomly for each vertex  if the left-mouse has been clicked
            r[i]=rand()%1000/1000.;
            g[i]=rand()%1000/1000.;
            b[i]=rand()%1000/1000.;
        }
    }
    else if(button ==GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
    {
        createGLUTMenus();
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
    
    glutMouseFunc(myMouse);
    glutKeyboardFunc(KeyboardKeys);
    
    glutMainLoop();
}
