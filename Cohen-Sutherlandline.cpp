#include <GL/glut.h>
#include <iostream>
using namespace std;

//---------------------------------------------------------
// Clipping Window Boundaries and Cohen–Sutherland Constants
//---------------------------------------------------------
const int x_min = -100, y_min = -100;
const int x_max =  100, y_max =  100;

const int INSIDE = 0;  // 0000
const int LEFT   = 1;  // 0001
const int RIGHT  = 2;  // 0010
const int BOTTOM = 4;  // 0100
const int TOP    = 8;  // 1000

//---------------------------------------------------------
// Data Structure for a Line Segment
//---------------------------------------------------------
struct LineSegment {
    double x1, y1, x2, y2;
};

//---------------------------------------------------------
// Compute Region Code for a Point (x, y)
//---------------------------------------------------------
int computeCode(double x, double y) {
    int code = INSIDE;
    if (x < x_min)       code |= LEFT;
    if (x > x_max)       code |= RIGHT;
    if (y < y_min)       code |= BOTTOM;
    if (y > y_max)       code |= TOP;
    return code;
}

//---------------------------------------------------------
// Cohen-Sutherland Line Clipping Algorithm
//---------------------------------------------------------
// The endpoints of the line segment are updated in place.
// Returns true if a (possibly clipped) segment is visible.
bool CohenSutherlandClip(double &x1, double &y1, double &x2, double &y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;
    
    while (true) {
        // Case 1: Both endpoints inside.
        if (code1 == 0 && code2 == 0) {
            accept = true;
            break;
        }
        // Case 2: Logical AND is not zero (both endpoints share an outside zone).
        else if (code1 & code2) {
            break;
        }
        // Case 3: At least one endpoint is outside.
        else {
            double x, y;
            int codeOut = code1 ? code1 : code2;
            
            // Find intersection point with one of the boundaries.
            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }
            
            // Replace the outside point with the intersection point.
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    return accept;
}

//---------------------------------------------------------
// Array of Line Segments for Demonstration
//---------------------------------------------------------
const int numLines = 7;
LineSegment lines[numLines] = {
    // Crossing the window horizontally.
    { -150,  50,  150,  50 },
    // Crossing the window vertically.
    {   0, -150,   0,  150 },
    // Diagonal from bottom-left to top-right.
    { -150, -150, 150, 150 },
    // Completely inside.
    {  -50,  -50,   50,  50 },
    // Completely outside (to the left).
    { -150,   0, -120,  50 },
    // Completely outside (above).
    {  -50,  150,  50,  150 },
    // Crossing from inside to outside.
    {  50,   50, 150, -50 }
};

//---------------------------------------------------------
// OpenGL Display Function
//---------------------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw the clipping window (green rectangle)
    glColor3f(0.0, 1.0, 0.0); // Green
    glBegin(GL_LINE_LOOP);
        glVertex2f(x_min, y_min);
        glVertex2f(x_max, y_min);
        glVertex2f(x_max, y_max);
        glVertex2f(x_min, y_max);
    glEnd();
    
    // Process each line segment
    for (int i = 0; i < numLines; i++) {
        LineSegment seg = lines[i];
        
        // Draw the original line in red.
        glColor3f(1.0, 0.0, 0.0); // Red
        glBegin(GL_LINES);
            glVertex2f(seg.x1, seg.y1);
            glVertex2f(seg.x2, seg.y2);
        glEnd();
        
        // Prepare a copy for clipping.
        double cx1 = seg.x1, cy1 = seg.y1, cx2 = seg.x2, cy2 = seg.y2;
        
        // Apply the Cohen-Sutherland algorithm.
        bool visible = CohenSutherlandClip(cx1, cy1, cx2, cy2);
        
        // If a portion is visible, draw the clipped segment in blue.
        if (visible) {
            glColor3f(0.0, 0.0, 1.0); // Blue
            glBegin(GL_LINES);
                glVertex2f(cx1, cy1);
                glVertex2f(cx2, cy2);
            glEnd();
        }
    }
    
    glFlush();
}

//---------------------------------------------------------
// OpenGL Initialization Function
//---------------------------------------------------------
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

//---------------------------------------------------------
// Main Function
//---------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("All Combinations of Cohen-Sutherland Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
