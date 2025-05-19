#include <GL/gl.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
void setPixel(int x,int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
     glEnd();
}
void Bresenham_circle2(int h,int k,int r)
{
    int x=0,y=r;
    int d=3-2*r;
    while(x<y)
    {
        setPixel(y+h,-x+k);
        setPixel(x+h,-y+k);
        
        if(d<0)
        {
            d=d+4*x+6;
        }
        else
        {
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
}       


void Bresenham_circle1(int h,int k,int r)
{
    int x=0,y=r;
    int d=3-2*r;
    while(x<y)
    {
        setPixel(-x+h,-y+k);
        setPixel(-y+h,-x+k);
        
        // Update x and y
        if(d<0)
        {
            d = d + 4*x + 6;
        }
        else
        {
            d = d + 4*(x-y) + 10;
            y--;
        }
        x++;
    }
}   
void Bresenham_circle3(int h,int k,int r)
{
    int x=0,y=r;
    int d=3-2*r;
    while(x<y)
    {
        setPixel(-x+h,y+k);
        setPixel(-y+h,x+k);
        if(d<0)
        {
            d=d+4*x+6;
        }
        else
        {
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
}
void Bresenham_circle4(int h,int k,int r)
{
    int x=0,y=r;
    int d=3-2*r;
    while(x<y)
    {
        setPixel(x+h,y+k);
        setPixel(y+h,x+k);
        
        if(d<0)
        {
            d=d+4*x+6;
        }
        else
        {
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
}
void display(void)
{
/* clear all pixels */
    glClear (GL_COLOR_BUFFER_BIT);
/* draw white polygon (rectangle) with corners at
* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
*/
    glColor3f (1.0, 1.0, 1.0);

int c=25;
Bresenham_circle1(5*c,5*c,5*c);
Bresenham_circle2(-5*c,5*c,5*c);
Bresenham_circle4(-5*c,-5*c,5*c);
Bresenham_circle3(5*c,-5*c,5*c);

/* don't wait!
* start processing buffered OpenGL routines
*/
glFlush ();
}
void init (void)
{
/* select clearing (background) color */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -10.0, 10.0);
}
/*
* Declare initial window size, position, and display mode
* (single buffer and RGBA). Open window with "hello"
* in its title bar. Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Demo");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
