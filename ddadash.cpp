#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Function to implement DDA Dash Line Drawing Algorithm
void ddaDashLine(int x0, int y0, int x1, int y1, int dashLength, int gapLength) {
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
    bool draw = true; // Boolean flag to decide whether to draw a dash or a gap

    // Plot the points (dashed line)
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        // Draw a point if we're in a "dash" phase
        if (draw) {
            glVertex2i(round(x), round(y));
        }

        // Increment the point coordinates
        x += xIncrement;
        y += yIncrement;

        // Increment the counter for the next point
        counter++;

        // After drawing a "dashLength" number of points, switch to a "gap" phase
        if (counter == dashLength) {
            draw = false; // Switch to gap
        }

        // After skipping a "gapLength" number of points, switch back to "dash"
        if (counter == dashLength + gapLength) {
            draw = true;  // Switch back to drawing
            counter = 0;  // Reset counter for the next segment
        }
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

// Display function to clear the screen and draw the dashed line
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a dashed line using DDA (example: from (50, 50) to (400, 300) with dash length 10 and gap length 5)
    ddaDashLine(50, 50, 400, 300, 10, 5);

    glFlush();  // Render the OpenGL output
}

// Main function to set up the window and OpenGL loop
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Use single buffering and RGB color model
    glutInitWindowSize(500, 500);                 // Set window size
    glutCreateWindow("DDA Dash Line Drawing Algorithm");

    initOpenGL();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register display callback function
    glutMainLoop();            // Start the OpenGL main loop

    return 0;
}
