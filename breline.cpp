#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Bresenham's Line Algorithm
void bresenhamLine(int x0, int y0, int x1, int y1) {
    // Calculate differences and error margins
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // Draw the current point
        glBegin(GL_POINTS);
        glVertex2i(x0, y0);
        glEnd();

        // Check if we reached the endpoint
        if (x0 == x1 && y0 == y1) break;

        // Calculate the error and update the coordinates
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background to black
    glPointSize(2.0);                    // Set the point size for drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set 2D orthographic projection
}

// Display function to clear the screen and draw the line
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Call Bresenham's line algorithm to draw a line
    bresenhamLine(50, 50, 400, 400);  // Example: Drawing from (50, 50) to (400, 400)

    glFlush();  // Render the OpenGL output
}

// Main function to set up the window and OpenGL loop
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Use single buffering and RGB color model
    glutInitWindowSize(500, 500);                // Set window size to 500x500
    glutCreateWindow("Bresenham Line Algorithm in OpenGL");

    initOpenGL();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register display callback function
    glutMainLoop();            // Start the OpenGL main loop

    return 0;
}
