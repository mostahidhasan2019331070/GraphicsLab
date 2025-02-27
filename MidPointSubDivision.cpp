#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

//--------------------------------------------------------------------
// Clipping Window Boundaries and Tolerance for Subdivision
//--------------------------------------------------------------------
const double x_min = -100, y_min = -100;
const double x_max =  100, y_max =  100;
const double TOL   = 0.5; // Tolerance for recursive subdivision

//--------------------------------------------------------------------
// Helper Functions
//--------------------------------------------------------------------

// Returns true if the point (x, y) is inside the clipping window.
bool isInside(double x, double y) {
    return (x >= x_min && x <= x_max && y >= y_min && y <= y_max);
}

// Quick test: if both endpoints lie completely on one side of the window.
bool triviallyOutside(double x1, double y1, double x2, double y2) {
    if (x1 < x_min && x2 < x_min) return true;
    if (x1 > x_max && x2 > x_max) return true;
    if (y1 < y_min && y2 < y_min) return true;
    if (y1 > y_max && y2 > y_max) return true;
    return false;
}

// Recursively find the intersection between an INSIDE point and an OUTSIDE point.
// The algorithm subdivides until the distance is within TOL.
void findIntersection(double x_in, double y_in, double x_out, double y_out,
                      double tol, double &xi, double &yi) {
    if (fabs(x_in - x_out) < tol && fabs(y_in - y_out) < tol) {
        xi = x_in;
        yi = y_in;
        return;
    }
    double mx = (x_in + x_out) / 2.0;
    double my = (y_in + y_out) / 2.0;
    if (isInside(mx, my))
        findIntersection(mx, my, x_out, y_out, tol, xi, yi);
    else
        findIntersection(x_in, y_in, mx, my, tol, xi, yi);
}

//--------------------------------------------------------------------
// Midpoint Subdivision Line Clipping Algorithm
//--------------------------------------------------------------------
// Given a line from (x1, y1) to (x2, y2), this function returns in (cx1, cy1)
// and (cx2, cy2) the endpoints of the segment that lies inside the clip window.
// It returns true if any part of the line is visible.
bool clipLineMidpoint(double x1, double y1, double x2, double y2,
                      double tol, double &cx1, double &cy1, double &cx2, double &cy2) {
    // Case 1: Entire line is inside.
    if (isInside(x1, y1) && isInside(x2, y2)) {
        cx1 = x1; cy1 = y1; 
        cx2 = x2; cy2 = y2;
        return true;
    }
    // Case 2: Trivial rejection (both endpoints on one side outside).
    if (triviallyOutside(x1, y1, x2, y2))
        return false;
    // Case 3: One endpoint is inside and the other is outside.
    if (isInside(x1, y1) && !isInside(x2, y2)) {
        cx1 = x1; cy1 = y1;
        findIntersection(x1, y1, x2, y2, tol, cx2, cy2);
        return true;
    }
    if (!isInside(x1, y1) && isInside(x2, y2)) {
        cx2 = x2; cy2 = y2;
        findIntersection(x2, y2, x1, y1, tol, cx1, cy1);
        return true;
    }
    // Case 4: Both endpoints are outside, but the line might cross the window.
    double mx = (x1 + x2) / 2.0, my = (y1 + y2) / 2.0;
    if (isInside(mx, my)) {
        // Use the midpoint to find both intersections.
        findIntersection(mx, my, x1, y1, tol, cx1, cy1);
        findIntersection(mx, my, x2, y2, tol, cx2, cy2);
        return true;
    }
    // Otherwise, subdivide further and combine results.
    double rx1, ry1, rx2, ry2, sx1, sy1, sx2, sy2;
    bool leftClip = clipLineMidpoint(x1, y1, mx, my, tol, rx1, ry1, rx2, ry2);
    bool rightClip = clipLineMidpoint(mx, my, x2, y2, tol, sx1, sy1, sx2, sy2);
    if (leftClip && rightClip) {
        cx1 = rx1; cy1 = ry1;
        cx2 = sx2; cy2 = sy2;
        return true;
    }
    else if (leftClip) {
        cx1 = rx1; cy1 = ry1;
        cx2 = rx2; cy2 = ry2;
        return true;
    }
    else if (rightClip) {
        cx1 = sx1; cy1 = sy1;
        cx2 = sx2; cy2 = sy2;
        return true;
    }
    return false;
}

//--------------------------------------------------------------------
// Data Structure for a Line Segment
//--------------------------------------------------------------------
struct LineSegment {
    double x1, y1, x2, y2;
};

// Array of sample line segments covering many combinations.
// Some are completely inside, completely outside, and some cross the clip window.
const int numLines = 6;
LineSegment lines[numLines] = {
    { -150,  50,  150,  50 },   // Crosses window horizontally.
    { -150, -150,  -50,  -50 },   // Completely outside (bottom-left).
    {    0,    0,    80,   80 },   // Completely inside.
    { -120,  120,  120,  120 },   // Horizontal line; top endpoint may be clipped.
    { -120, -120,  120, -120 },   // Horizontal line; bottom endpoint may be clipped.
    {  120, -120, -120,  120 }    // Diagonal crossing the window.
};

//--------------------------------------------------------------------
// OpenGL Display Function
//--------------------------------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw the clipping window (green rectangle)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x_min, y_min);
        glVertex2f(x_max, y_min);
        glVertex2f(x_max, y_max);
        glVertex2f(x_min, y_max);
    glEnd();
    
    // Process each line segment.
    for (int i = 0; i < numLines; i++) {
        LineSegment seg = lines[i];
        
        // Draw the original line in red.
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex2f(seg.x1, seg.y1);
            glVertex2f(seg.x2, seg.y2);
        glEnd();
        
        // Attempt to clip the line.
        double cx1, cy1, cx2, cy2;
        bool visible = clipLineMidpoint(seg.x1, seg.y1, seg.x2, seg.y2, TOL,
                                        cx1, cy1, cx2, cy2);
        // If visible, draw the clipped segment in blue.
        if (visible) {
            glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_LINES);
                glVertex2f(cx1, cy1);
                glVertex2f(cx2, cy2);
            glEnd();
        }
    }
    
    glFlush();
}

//--------------------------------------------------------------------
// OpenGL Initialization
//--------------------------------------------------------------------
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

//--------------------------------------------------------------------
// Main Function
//--------------------------------------------------------------------
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("All Combinations of Line Clipping using Midpoint Subdivision");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
