//
//  main.cpp
//  P2
//
//  Created by Ornnicha Phueaksri on 22/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define TORUS_COLOR 1
#define SPHERE_SMALL_COLOR 2
#define SPHERE_BIG_COLOR 3

#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define WHITE 5

#define XAXIS 1
#define YAXIS 2
#define ZAXIS 3
#define DIAGONAL 4

#define DIRECTIONAL 1
#define POSITIONAL 2

#define S_ON 1
#define S_OFF 2

#define DUMMY 0

int swidth=500, sheight=500;
float ax[3]={5,0,0}; float ay[3]={0,5,0}; float az[3]={0,0,5};//axes
float angle=0; float dangle =0.5;
float red=0, green=0, blue=0;
float tred=1, tgreen=1, tblue=1;//torus color
float ssred=0, ssgreen=1, ssblue=0;//smal sphere color
float sbred=0, sbgreen=0, sbblue=1;//big sphere color
float Lred=1, Lgreen=1, Lblue=1;//LIGHT0 color

GLfloat Dir=0;//directional or positional light
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.0 };
GLfloat light_position[] = {0.0, 0.0, 1.0, Dir }; //on Z axis
GLfloat Light[] = {Lred, Lgreen, Lblue, 0}; //white light
//These are additional functions to output  the text on the screen. You do not need to learn them
bool specular = true;

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
//These are additional functions to plot axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glPointSize(10);
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
void plot_Axis()
{
    glColor3f(1,0,0);
    plot_Vector(ax);
    glColor3f(0,1,0);
    plot_Vector(ay);
    glColor3f(0,0,1);
    plot_Vector(az);
}
void Time_Delay(GLint dur)  //time delay
{clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    {         }
}
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,float(swidth)/float(sheight),0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);
}
void initlights(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set up the light position
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  Light);//this sets the diffuse light
    glEnable(GL_LIGHTING);//enable lighting
    glEnable(GL_LIGHT0); //enable light 0
    glEnable(GL_DEPTH_TEST);//enables the depth buffer: closer objects
    //close objects obstruct far  objects
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}
void display_All()//plot the scene
{
    glPushMatrix();     // send the preceding transformation matrix to stack
    plot_Axis();
    glColor3f(tred,tgreen,tblue);
    glutSolidTorus (0.5, 1, 20, 20);
    glColor3f(ssred,ssgreen,ssblue);
    glutSolidSphere(0.4,15,15);
    glColor3f(sbred,sbgreen,sbblue);
    glTranslated(0,2,0);
    glutSolidSphere (1, 20, 16);
    glPopMatrix();
}
void output_TextAll()
{
    glDisable(GL_LIGHTING);
    output_Text(-5.8,-5.3,"Specular-",0,0,0);
    output_Text(-6,-6,"Torus",tred,tgreen,tblue);
    output_Text(-6.1,-6.6,"Big Sphere",sbred,sbgreen,sbblue);
    output_Text(-6.35,-7.3,"Small Sphere",ssred,ssgreen,ssblue);
    if (Dir==0)
        output_Text(-6.55,-8.15,"Light-Pos",Lred,Lgreen,Lblue);
    else
        output_Text(-6.55,-8.15,"Light-Dir",Lred,Lgreen,Lblue);
    glEnable(GL_LIGHTING  );
}
void display(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_All();
    output_TextAll();
    glutSwapBuffers();
}
void process_Menu_Events(int option)
{
    
}
void Color_Torus(int option) {
    switch (option)
    {
        case RED : tred = 1.0; tgreen = 0.0; tblue = 0.0; break;
        case GREEN : tred = 0.0; tgreen = 1.0; tblue = 0.0; break;
        case BLUE : tred = 0.0; tgreen = 0.0;tblue = 1.0; break;
        case BLACK : tred = 0.0; tgreen = 0.0; tblue = 0.0; break;
        case  WHITE : tred = 1.0; tgreen = 1.0; tblue = 1.0; break;
    }
}
void Color_SmallSphere(int option) {
    switch (option)
    {
        case RED : ssred = 1.0; ssgreen = 0.0; ssblue = 0.0; break;
        case GREEN : ssred = 0.0; ssgreen = 1.0; ssblue = 0.0; break;
        case BLUE : ssred= 0.0; ssgreen= 0.0; ssblue  = 1.0; break;
        case BLACK : ssred  = 0.0; ssgreen = 0.0; ssblue  = 0.0; break;
        case  WHITE : ssred= 1.0; ssgreen = 1.0; ssblue  = 1.0; break;
    }
}

void Color_BigSphere(int option) {
    switch (option)
    {
        case RED : sbred = 1.0; sbgreen = 0.0; sbblue = 0.0; break;
        case GREEN : sbred = 0.0; sbgreen = 1.0; sbblue = 0.0; break;
        case BLUE : sbred= 0.0; sbgreen= 0.0; sbblue  = 1.0; break;
        case BLACK : sbred  = 0.0; sbgreen = 0.0; sbblue  = 0.0; break;
        case  WHITE : sbred= 1.0; sbgreen = 1.0; sbblue  = 1.0; break;
    }
}

void Color_Light(int option) {
    switch (option)
    {
        case RED : Lred = 1.0; Lgreen = 0.0; Lblue = 0.0; break;
        case GREEN : Lred = 0.0; Lgreen = 1.0; Lblue = 0.0; break;
        case BLUE : Lred= 0.0; Lgreen= 0.0; Lblue  = 1.0; break;
        case BLACK : Lred  = 0.0; Lgreen = 0.0; Lblue  = 0.0; break;
        case  WHITE : Lred= 1.0; Lgreen = 1.0; Lblue  = 1.0; break;
    }
    Light[0] = Lred;
    Light[1] = Lgreen;
    Light[2] = Lblue;
    initlights();
}

void Light_Pos(int option) //complete this function
{int i;
    glDisable(GL_LIGHTING);
    switch (option)
    {
        case XAXIS :
            light_position[0]=1;
            light_position[1]=0;
            light_position[2]=0;
            break;
        case YAXIS :
            light_position[0]=0;
            light_position[1]=1;
            light_position[2]=0;
            break;
        case ZAXIS :
            light_position[0]=0;
            light_position[1]=0;
            light_position[2]=1;
            light_position[3]=Dir;
            break;
        case DIAGONAL :
            light_position[0]=1;
            light_position[1]=1;
            light_position[2]=1;
            break;
    };
    initlights();
}

void Light_Type(int option)
{
    switch (option)
    {
        case DIRECTIONAL :Dir=0.0; break;
        case POSITIONAL : Dir=1.0; break;
    }
    light_position[3] = Dir;
    initlights();
}

void Specular_Light(int option)
{
    switch (option)
    {
        case S_ON :
            mat_specular[0] = 1.0;
            mat_specular[1] = 1.0;
            mat_specular[2] = 1.0;
            specular = true;
            break;
        case S_OFF :
            mat_specular[0] = 0.0;
            mat_specular[1] = 0.0;
            mat_specular[2] = 0.0;
            specular = false;
            break;
    }
    initlights();
}
void  Dummy(int option){}

void createGLUTMenus() {
    int dummy_menu=glutCreateMenu(Dummy);
    glutAddMenuEntry("Dummy",DUMMY);
    int coltor_menu = glutCreateMenu(Color_Torus);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int colsb_menu = glutCreateMenu(Dummy);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int colss_menu = glutCreateMenu(Color_SmallSphere);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int colbs_menu = glutCreateMenu(Color_BigSphere);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int coll_menu = glutCreateMenu(Color_Light);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int typelight_menu = glutCreateMenu(Light_Type);
    glutAddMenuEntry("Directional",DIRECTIONAL);
    glutAddMenuEntry("Positional",POSITIONAL);
    int spec_menu = glutCreateMenu(Light_Type);
    glutAddMenuEntry("Specular ON",S_ON);
    glutAddMenuEntry("Specular OFF",S_OFF);
    int lightpos_menu = glutCreateMenu(Light_Pos);
    glutAddMenuEntry("X Axis",XAXIS);
    glutAddMenuEntry("Y Axis",YAXIS);
    glutAddMenuEntry("Z Axis",ZAXIS);
    glutAddMenuEntry("Diagonal",DIAGONAL);
    int menu=glutCreateMenu(NULL);
    glutAddSubMenu("Torus Color",coltor_menu);
    glutAddSubMenu("Small Sphere Color",colss_menu);
    glutAddSubMenu("Big Sphere Color",colbs_menu );
    glutAddSubMenu("Light Color",coll_menu);
    glutAddSubMenu("Light Type",typelight_menu);
    glutAddSubMenu("Light Position",lightpos_menu);
    glutAddSubMenu("Specular Light",spec_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Problem  3. Lighting Menu Project");
    init();
    initlights ();
    createGLUTMenus();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;}

