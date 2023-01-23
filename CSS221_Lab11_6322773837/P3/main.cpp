//
//  main.cpp
//  P3
//
//  Created by Ornnicha Phueaksri on 22/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4


GLfloat x=4,y=4.0,z=4.0;
GLfloat lx=0.0,ly=0.0,lz=0.0;
GLfloat ni=50, nj=50;
GLfloat ratio=1;
bool rotate = false;
GLfloat t=0;
GLfloat dt=0.0001;
float red=0, green=0, blue=0;
GLfloat Mred=0,Mgreen=0, Mblue=1;
GLfloat diffuseMaterial[4] = {1, 1, 1, 1.0 };
GLfloat light_position[] = {0.0, 0.5, 0.0, 1.0 };
GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
GLfloat Light[] = {1.0, 1.0, 1.0, 0.0};
float ax[3]={5,0,0}; float ay[3]={0,5,0}; float az[3]={0,0,5};
const float pi = 3.14159;

void output_Text(float x, float y, char* text, int red, int green, int blue)
{  int len, i;
    char W[7]=" White";
    glColor3f(red, green, blue);
    if ((red==1) and (green==1) and (blue==1)) glColor3f(0,0,0);
    glPushMatrix();
    glRotated(45,0,1,0);
    glRasterPos3f(x, y, 0);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
    if ((red==1) and (green==1) and (blue==1))
    {
        for (i = 0; i < 6; i++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, W[i]);
    }
    glPopMatrix();
}

void plot_Arrow(float v1[3], float v2[3])
{
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3])
{
    float zero[3]={0,0,0};
    plot_Arrow(zero,v);
}
void plot_Axis()
{
    glColor3f(1,0,0);
    plot_Vector(ax);
    glColor3f(0,1,0);
    plot_Vector(ay);
    glColor3f(0,0,1);
    plot_Vector(az);
}
void initlights(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set up the light position
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light);//this sets the diffuse light
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light);//this sets the ambient light
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);//30 degree light cone
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);//sets the spot light direction
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);//concentration at the center of the spot
    glEnable(GL_LIGHTING);//enable lighting
    glEnable(GL_LIGHT0); //enable light 0
    glEnable(GL_DEPTH_TEST);//enables the depth buffer: closer objects will obstruct objects located farther
    glColorMaterial(GL_FRONT, GL_DIFFUSE);//diffuse light is reflected by the front face
    glEnable(GL_COLOR_MATERIAL);//enable reflection by material
    glShadeModel(GL_SMOOTH);//smooth shades
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
              lx,ly,lz,
              0.0,1.0,0.0);
}
float flx(float t)
{
    return 2 * cos(3*t);
}
float fly(float t)
{
    return 0.5;
}
float flz(float t)
{
    return 2 * sin(2*t);
}
float sx(float u,float v)
{return u;}
float sy(float u,float v)
{return 0;}
float sz(float u,float v)
{return v;}
float nx(float u,float v)
{return 0;}
float ny(float u,float v)
{return 1;}
float nz(float u,float v)
{return 0;}
void initScene() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_FLAT);
}
void displayPath()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    for(float tp = 0; tp <= 2*pi; tp+=0.01){
        glVertex3f(flx(tp),fly(tp),flz(tp));
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void updateLight()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPointSize(5);
    glColor4fv(diffuseMaterial);
    glBegin(GL_POINTS);
    glVertex3f(flx(t),fly(t),flz(t));
    glEnd();
    glPointSize(1);
    
    light_position[0] = flx(t);
    light_position[1] = fly(t);
    light_position[2] = flz(t);
    //spot_direction[0] = flx(t);
    //spot_direction[1] = -1.0;
    //spot_direction[2] = flz(t);
    initlights();
}

void displaySurface()
{
    int i, j;
    float stepi,stepj,ui,vj,uip1,vjp1;
    float xij,yij,zij;
    float xip1j,yip1j,zip1j;
    float xijp1,yijp1,zijp1;
    float xip1jp1,yip1jp1,zip1jp1;
    stepi=float(4/ni);
    stepj=float(4/nj);
    for (j = 0; j <= nj-1; j++) {
        for (i = 0; i <= ni-1; i++) {
            ui=-2+i*stepi;
            vj=-2+j*stepj;
            uip1=-2+(i+1)*stepi;
            vjp1=-2+(j+1)*stepj;
            xij=sx(ui,vj);
            yij=sy(ui,vj);
            zij=sz(ui,vj);
            xip1j=sx(uip1,vj);
            yip1j=sy(uip1,vj);
            zip1j=sz(uip1,vj);
            xip1jp1=sx(uip1,vjp1);
            yip1jp1=sy(uip1,vjp1);
            zip1jp1=sz(uip1,vjp1);
            xijp1=sx(ui,vjp1);
            yijp1=sy(ui,vjp1);
            zijp1=sz(ui,vjp1);
            //draw quads
            glColor4fv(diffuseMaterial);
            //glDisable(GL_LIGHTING);
            glBegin(GL_QUADS);
            glNormal3f(nx(ui,vj),ny(ui,vj),nz(ui,vj));
            glVertex3f(xij,yij,zij);
            glNormal3f(nx(uip1,vj),ny(uip1,vj),nz(uip1,vj));
            glVertex3f(xip1j,yip1j,zip1j);
            glNormal3f(nx(uip1,vjp1),ny(uip1,vjp1),nz(uip1,vjp1));
            glVertex3f(xip1jp1,yip1jp1,zip1jp1);
            glNormal3f(nx(ui,vjp1),ny(ui,vjp1),nz(ui,vjp1));
            glVertex3f(xijp1,yijp1,zijp1);
            glEnd();
            glDisable(GL_LIGHTING);
            glColor4fv(diffuseMaterial);
            glColor3f(Mred,Mgreen,Mblue);
            glBegin(GL_LINE_LOOP);
            glVertex3f(xij,yij+0.01,zij);
            glVertex3f(xip1j,yip1j+0.01,zip1j);
            glVertex3f(xip1jp1,yip1jp1+0.01,zip1jp1);
            glVertex3f(xijp1,yijp1+0.01,zijp1);
            glEnd();
            glEnable(GL_LIGHTING );
        }
    }
}
void output_TextAll()
{
    glDisable(GL_LIGHTING);
    output_Text(-6,-8,"Plane color",Mred,Mgreen,Mblue);
    glEnable(GL_LIGHTING );
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    displaySurface();
    displayPath();
    plot_Axis();
    updateLight();
    t+=dt;
    output_TextAll();
    glutSwapBuffers();
}

void Material_color(int option)
{
    switch (option)
    {
        case RED : Mred = 1.0; Mgreen = 0.0; Mblue = 0.0; break;
        case GREEN : Mred = 0.0; Mgreen = 1.0; Mblue = 0.0; break;
        case BLUE : Mred= 0.0; Mgreen= 0.0; Mblue = 1.0; break;
        case WHITE : Mred= 1.0; Mgreen = 1.0; Mblue = 1.0; break;
    }
    initlights();
}

void createGLUTMenus()
{
    int color_menu=glutCreateMenu(Material_color);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("White",WHITE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("Problem 3. Bonus. Spotlight with a menu");
    init();
    initlights();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    createGLUTMenus();
    glutMainLoop();
    return(0);
}
