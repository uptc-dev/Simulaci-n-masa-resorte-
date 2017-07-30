/*
 * David Sanchez Ruiz
 * Jenny Paola Quesada Hernández
 */
#include <windows.h>
#include <GL\glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
double hM=0;
double Y=0;
double m=0.1;
double k=1;
double b=0.2;
double tf=10;
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void drawSpring(double d)
{
    double hM=1.2;
    double radio=0.2;
    double yV=hM-radio;
    int turn=7;
    double bring=360*turn-90;
    double jump=(hM-d-radio-0.1)/bring;
    glColor3d(0,0,0);
    GLfloat angle=(GLfloat)90*3.14159f/180.0f;
    GLfloat angle2;
    glBegin(GL_LINES);
          glVertex3f(0, 1.2, -4);
          glVertex3f(cos(angle)*radio, yV,-4+sin(angle)*radio);
    glEnd();

    for (int i = 90; i <bring; i+=1) {
            angle = (GLfloat)i*3.14159f/180.0f;
            angle2= (GLfloat)(i+1)*3.14159f/180.0f;
            glBegin(GL_LINES);
                glVertex3f(cos(angle)*radio, yV,-4+sin(angle)*radio);
                glVertex3f(cos(angle2)*radio, yV,-4+sin(angle2)*radio);
            glEnd();
            yV-=jump;
    }
    glBegin(GL_LINES);
          glVertex3f(cos(angle2)*radio, yV+jump, -4+sin(angle2)*radio);
          glVertex3f(0, d, -4);
    glEnd();
}
void drawMass(double h, double sizeMass)
{
    glColor3d(0,1,0);
    glPushMatrix();
        glTranslated(0,h-(sizeMass/2),-4);
        glutSolidCube(sizeMass);
    glPopMatrix();
}
void drawBase()
{
    glColor3d(0,0,1);
    glPushMatrix();
        glTranslated(-0.5,1.5,-4);
        glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,1.5,-4);
        glutSolidCube(0.5);
    glPopMatrix();
     glPushMatrix();
        glTranslated(0.5,1.5,-4);
        glutSolidCube(0.5);
    glPopMatrix();

}
static void display(void){

    double A[2][2]={{0,1},{-k/m,-b/m}};
    double B[2][1]={{0},{1/m}};
    double X[2][1]={{1},{0}};
    double C[2][1]={{1},{1}};
    double u=0;

    double h=0.01;
    double I[2][2]={{1,0},{0,1}};

    double Xe[2][2];
    double Xtemp[2][2];
    vector <double> YV(tf);
    for(int i=1;i<tf/h;i+=1){
            //Vacia Ytemp
            for(int x=0; x<2;x++) for(int y=0; y<2;y++) Xtemp[x][y]=0;
            //Xe=(A*h+I)*X+B*u*h; u es igual a 0 cancela B*u*h
            for(int x=0; x<2;x++) for(int y=0; y<2;y++) Xe[x][y]=A[x][y]*h;
            for(int x=0; x<2;x++) for(int y=0; y<2;y++) Xe[x][y]=Xe[x][y]+I[x][y];
            for(int x=0; x<2;x++) for(int y=0; y<2;y++) for(int z=0; z<2;z++) Xtemp[x][y]+=Xe[x][z]*X[z][y];
            //Y(:,n)=C.*X;
            Y=Xtemp[0][0];
            //t(n)=n*h;
            Sleep(20);
            //X=Xe;
            for(int x=0; x<2;x++) for(int y=0; y<2;y++) X[x][y]=Xtemp[x][y];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Base
    drawBase();
    //Resorte
    drawSpring(Y);
    //Mass
    drawMass(Y, 0.5);
    glutSwapBuffers();
    }

}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            hM+=0.01;
            break;

        case '-':
            hM-=0.01;
         break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    double numero;
    cout<<"Valores por omision 1. Si 2. No"<<endl;
    cin>>numero;
    if(numero==1){
        cout<<"Digite m:"<<endl;
        cin>>m;
        cout<<"Digite k:"<<endl;
        cin>>k;
        cout<<"Digite b:"<<endl;
        cin>>b;
        cout<<"Digite el tiempo final:"<<endl;
        cin>>tf;
    }
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
