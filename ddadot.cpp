#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Function to implement DDA Dotted Line Drawing Algorithm
void ddaDottedLine(int x0, int y0, int x1, int y1, int dotInterval) {
    // Calculate differences
    int dx = x1 - x0;
    int dy = y1 - y0;

    // Calculate steps required for generating points
    int steps = std::max(abs(dx), abs(dy));

    // Calculate increment in x and y for each step
    float xIncrement = dx / float(steps);
    float yIncrement = dy / float(steps);

    // Start from the initial point
    float x = x0;
    float y = y0;

    int counter = 0;  // Counter to track when to plot a point

    // Plot the points (dotted line)
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        // Only plot a point after a certain interval (dotInterval)
        if (counter % dotInterval == 0) {
            glVertex2i(round(x), round(y));
        }

        // Update the point coordinates
        x += xIncrement;
        y += yIncrement;
        
        // Increment the counter for the next point
        counter++;
    }
    glEnd();

    glFlush(); // Render the OpenGL output
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
    glPointSize(3.0);                    // Set point size for drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set 2D orthographic projection
}

// Display function to clear the screen and draw the dotted line
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a dotted line using DDA (example: from (50, 50) to (400, 300) with dot interval 5)
    ddaDottedLine(50, 50, 400, 300, 5);

    glFlush();  // Render the OpenGL output
}

// Main function to set up the window and OpenGL loop
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Use single buffering and RGB color model
    glutInitWindowSize(500, 500);                 // Set window size
    glutCreateWindow("DDA Dotted Line Drawing Algorithm");

    initOpenGL();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register display callback function
    glutMainLoop();            // Start the OpenGL main loop

    return 0;
}
