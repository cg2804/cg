#include <GL/glut.h>
#include <cmath>
#include <iostream>

struct Point {
    int x, y;
};

// Bresenham's Circle Drawing Algorithm
void bresenhamCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        // Draw the eight symmetric points of the circle
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        glEnd();

        x++;

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
    }
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
    glPointSize(2.0);                    // Set point size for drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set 2D orthographic projection
}

// Display function to clear the screen and draw the circle
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set circle parameters
    int centerX = 250, centerY = 250, radius = 100;

    // Call Bresenham's circle drawing algorithm to draw the circle
    bresenhamCircle(centerX, centerY, radius);

    glFlush();  // Render the OpenGL output
}

// Main function to set up the window and OpenGL loop
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Use single buffering and RGB color model
    glutInitWindowSize(500, 500);                // Set window size
    glutCreateWindow("Bresenham Circle Algorithm in OpenGL");

    initOpenGL();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register display callback function
    glutMainLoop();            // Start the OpenGL main loop

    return 0;
}
