//
//  main.cpp
//  P1
//
//  Created by Ornnicha Phueaksri on 22/4/2565 BE.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

int w=500, h=500;
GLfloat colorM[4] = { 0.0, 0.0, 0.0, 0.0 };//initial material color= black
GLfloat DiffuseLight[4]={1,1,1,0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.0 }; //specular light =white
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; //directional diagonal light
float shine =10, dshine=1.0;
bool spec=true;
void output_Text(float x, float y, char *text)
{
    int len, i;
    glPushMatrix();
    glRotated(45,0,1,0);
    glRasterPos3f(x, y, 0);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
    glPopMatrix();
}
void initlights(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);//large shine focused specular reflection
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}
void change_Light(unsigned char C)//write this function
{
    int i;
    switch (C)
    {
        case 'R':DiffuseLight[0]=1;DiffuseLight[1]=0;DiffuseLight[2]=0; break; //Diff light red
        case 'G':DiffuseLight[0]=0;DiffuseLight[1]=1;DiffuseLight[2]=0; break;//Diff light green
        case 'B': DiffuseLight[0]=0;DiffuseLight[1]=0;DiffuseLight[2]=1; break;//Diff light blue
        case 'W': DiffuseLight[0]=1;DiffuseLight[1]=1;DiffuseLight[2]=1; break;//Diff light white
        case '+': shine-=dshine; break;//increase shiness
        case '-': shine+=dshine; break;//decrease shiness
        case 'S': case 's':
            if (spec)
            {
                for (i=0;i<=2;i++) mat_specular[i]=0;
                mat_specular[3]=shine;
                spec=false;
            }
            else
            {
                for (i=0;i<=2;i++) mat_specular[i]=1;
                spec= true;
            }break;//turn specular light on/off
    }
    printf("lred=%5.3f, lgreen=%5.3f, lblue=%5.3f, shine=%5.3f\n",DiffuseLight[0],DiffuseLight[1],DiffuseLight[2], shine);
    if (spec) printf("specular light on\n");
    else printf("specular light off\n");
    initlights();
}
void change_MatColor(unsigned char key)
{switch (key)
{
    case 'r':
        colorM[0] += 0.01;
        if (colorM[0] >= 1.0)
            colorM[0] = 0.0;
        glColor4fv(colorM);
        break;
    case 'g':
        colorM[1] += 0.01;
        if (colorM[1] >= 1.0)
            colorM[1] = 0.0;
        glColor4fv(colorM);
        break;
    case 'b':
        colorM[2] += 0.01;
        if (colorM[2] >= 1.0)
            colorM[2] = 0.0;
        glColor4fv(colorM);
        break;
    case 'w':
        colorM[0] = 1;
        colorM[1] = 1;
        colorM[2] = 1;
        glColor4fv(colorM);
        break;
}
    printf("mred=%5.3f, mgreen=%5.3f, mblue=%5.3f\n", colorM[0],colorM[1],colorM[2]);
}
void processNormalKeys(unsigned char key, int x, int y)
{
    change_MatColor(key);
    change_Light(key);
}
void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidSphere(1.0, 20, 16);
    output_Text(-2,-1.3,"S-specular light on/off, +,- change shiness");
    output_Text(-2,-1.2,"r,g or b, w-material color, R,G,B,W-light color");
    glutSwapBuffers();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5,1.5,-10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4fv(colorM);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 1. Change the material color, specularity and lights");
    initlights();
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return 0;
}
