#include <GL/glut.h>
#include <iostream>

using namespace std;

void myInit()
{
    gluOrtho2D(0, 500, 0, 500);
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glColor3f(0, 1, 0); // Set boundary color to green
}

void plotPixel(int x, int y, float* fill_color)
{
    glColor3f(fill_color[0], fill_color[1], fill_color[2]);

    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();

    glFlush();    
}

void boundaryFill(int x, int y, float* fill_color, float* boundary_color)
{
    float current[3];

    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, current);

    if((current[0] != boundary_color[0] || current[1] != boundary_color[1] || current[2] != boundary_color[2]) &&
       (current[0] != fill_color[0] || current[1] != fill_color[1] || current[2] != fill_color[2]))
    {
        plotPixel(x, y, fill_color);
        boundaryFill(x + 1, y, fill_color, boundary_color);
        boundaryFill(x, y + 1, fill_color, boundary_color);
        boundaryFill(x - 1, y, fill_color, boundary_color);
        boundaryFill(x, y - 1, fill_color, boundary_color);
    }
}

void squareShape()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing a square with the following coordinates
    glBegin(GL_LINE_LOOP);
        glColor3f(0, 1, 0); // Set boundary color to green
        glVertex2i(100, 100);  // Bottom-left corner
        glVertex2i(400, 100);  // Bottom-right corner
        glVertex2i(400, 400);  // Top-right corner
        glVertex2i(100, 400);  // Top-left corner
    glEnd();

    glFlush();

    // Boundary and fill colors
    float boundary_color[3], fill_color[3];

    // Boundary color (Green)
    boundary_color[0] = 0;
    boundary_color[1] = 1;
    boundary_color[2] = 0;

    // Fill color (Red)
    fill_color[0] = 1;
    fill_color[1] = 0;
    fill_color[2] = 0;

    // Starting point for boundary fill
    boundaryFill(102, 102, fill_color, boundary_color);
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);  // Initializing the library
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(400, 150);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutCreateWindow("Boundary Fill - Square");

   myInit(); 
   glutDisplayFunc(squareShape);

   glutMainLoop(); 
   return 0;
}
