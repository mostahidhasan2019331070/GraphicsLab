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


void Bresenham_circle1(int p)
{  
    int c=25;

    int x=0,y=5*c;
    int d=3-2*5;
    while(x<=y)
    {
        if(p==1)
        {
            setPixel(-x+5*c,-y+5*c);
            setPixel(-y+5*c,-x+5*c);
        }
        else if(p==2)
        {
            setPixel(y-5*c,-x+5*c);
            setPixel(x-5*c,-y+5*c);
        }
            else if(p==3)
        {
            setPixel(x-5*c,y-5*c);
            setPixel(y-5*c,x-5*c);
        }
        else if(p==4)
        {
            setPixel(-x+5*c,y-5*c);
            setPixel(-y+5*c,x-5*c);
        }
        
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
void drawCircle_Bresenham_15_60(int h,int k,int r)
{
    // 60 to 45 - for reflection
   int x=r*cos(60*M_PI/180.0);
   int y=r*sin(60*M_PI/180.0);
   int d=3-2*r;
   while(x<=y)
   {
    setPixel(x+h,y+k);
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
   // 45 to 75 - for reflection for 15 to 45
   int x1=r*cos(75*M_PI/180.0);
   int y1=r*sin(75*M_PI/180.0);
   int d1=3-2*r;
   while(x1<=y1)
   {
    setPixel(y1+h,x1+k);
    if(d1<0)
    {
        d1=d1+4*x1+6;
    }
    else
    {
        d1=d1+4*(x1-y1)+10;
        y1--;
    }
    x1++;
   }
}

void drawCircle_Bresenham_120_160(int h,int k,int r)
{
    // 60 to 45 - for reflection
    int x=(r * cos(60*M_PI/180.0));
    int y=(r * sin(60*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        setPixel(h - x, k + y);  // -x for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    x=(r * cos(70*M_PI/180.0));
    y=(r * sin(70*M_PI/180.0));
    d = 3 - 2 * r;
    while(x<=y)
    {
        setPixel(h-y,k+x);  //swap and -(x) for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void drawCircle_Bresenham_210_260(int h,int k,int r)
{
    // 80 to 30 - for reflection
    int x=(r * cos(80*M_PI/180.0));
    int y=(r * sin(80*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        setPixel(-x+h, -y+k );  // -(x) and -(y) for reflection respect to y axis and x axis respectively
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    x=(r * cos(60*M_PI/180.0));
    y=(r * sin(60*M_PI/180.0));
    d = 3 - 2 * r;
    while(x<=y)
    {
        setPixel(-y+h, -x+k );  // swap, reflec x and y axis
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }


}

void drawCircle_Bresenham_280_340(int h,int k,int r)
{
    // 80to45 - 280to315
    int x=(r * cos(80*M_PI/180.0));
    int y=(r * sin(80*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        setPixel(h + x, -y+k);  //  -(y) for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    // 20to45 or 70to45 - 315to340
    x=(r * cos(70*M_PI/180.0));
    y=(r * sin(70*M_PI/180.0));
    d = 3 - 2 * r;
    while(x<=y)
    {
        setPixel(h + y,  -x+k);  // swap and -(y) for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
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
for(int i=1;i<=4;i++)
{
    Bresenham_circle1(i);
   
}
// Bresenham_circle1(5*c,5*c,5*c);
// Bresenham_circle2(-5*c,5*c,5*c);
// Bresenham_circle4(-5*c,-5*c,5*c);
// Bresenham_circle3(5*c,-5*c,5*c);
// drawCircle_Bresenham_15_60(5*c,5*c,5*c);
//drawCircle_Bresenham_120_160(5*c,5*c,5*c);
//drawCircle_Bresenham_210_260(5*c,5*c,5*c);
//drawCircle_Bresenham_280_340(5*c,5*c,5*c);

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
    glOrtho(-500.0, 500.0, -500.0, 500.0, -10.0, 10.0);
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
    glutInitWindowSize (1000, 1000);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Demo");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
