#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#define MAXSIZE 800
#define dimension 1000
float zoom = 0.5;
float windowx = 0.5, windowy = 0.5;
struct stackx
{
    int stk[MAXSIZE];
    int top;
};
struct stacky
{
    int stk1[MAXSIZE];
    int top1;
};
typedef struct stackx STACK;
typedef struct stacky STACK1;
STACK s;
STACK1 s1;
void push (float x,float y)
{
    s.top = s.top + 1;
    s.stk[s.top] = x;
    s1.top1 = s1.top1 + 1;
    s1.stk1[s1.top1] = y;
    
    return;
}
void reset()
{
    s1.top1=-1;
    s.top=-1;
    
}

void draw_line(float xa,float ya,float xb,float yb)
{    glBegin(GL_LINES);
    glVertex2f(xa,ya);
    glVertex2f(xb,yb);
    glEnd();
    glFlush();
    glutSwapBuffers();
    
    
    
}
void setcolor(int length)
{
    if(length<30)
    {
        glColor3f(0,1,0);
    }
    if(length>30)
    {
        glColor3f(0.3,0.1,0);
    }
}
void drawTree(float x,float y,float a,float b,int length)
{       usleep(1100);//to delay the drawing
    float ra = a*3.14/180;
    float rb = b*3.14/180;
    setcolor(length);
    if(length<0)
    {
        return;
    }
    push(x,y);
    draw_line(x,y,x+length*sin(ra),y+length*cos(ra));
    draw_line(x,y,x-length*sin(rb),y+length*cos(rb));
    float right=a+30;
    float left=b-30;
    drawTree(x+length*sin(ra),y+length*cos(ra),right,left,length-10);
    right=a-30;
    left=b+30;
    drawTree(x-length*sin(rb),y+length*cos(rb),right,left,length-10);
    
}
void myMouseMove( int x, int y)
{
    int dimensionx = x-10;
    int dimensiony = y;
    
    //glutPostRedisplay();
}

float angle=25;
void display()
{       s.top=-1;
    s1.top1=-1;
    glClear(GL_COLOR_BUFFER_BIT);
    push(600,0.0);
    glBegin(GL_LINES);
    glVertex2f(s.stk[s.top],s1.stk1[s1.top1]);
    glVertex2f(s.stk[s.top],s1.stk1[s1.top1+100]);
    glEnd();
    glFlush();
    glutSwapBuffers();
}
int val=20;int n=0;
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'a':
        n++;
        if(n<=6)
        {drawTree(s.stk[s.top],s1.stk1[s1.top1+100],angle,angle,val);
            val+=10;}
        else
        {  n=0;
            //  myMouseMove(800,800);
        }
        
        break;
    }}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,512.0);
    glColor3f(1,0,0);
}

int main( int argc, char* argv[] )
{
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(dimension,dimension);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Fractal Tree");
    glutDisplayFunc(display);
    glutPassiveMotionFunc( myMouseMove);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}

