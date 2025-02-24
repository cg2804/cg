#include <GL/glut.h>
#include <iostream>

void floodFill(int x, int y, float fillColor[3], float oldColor[3]);

// Function to get pixel color at (x, y)
void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

// Function to set pixel color
void setPixelColor(int x, int y, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Recursive Flood Fill Algorithm
void floodFill(int x, int y, float fillColor[3], float oldColor[3]) {
    float pixelColor[3];
    getPixelColor(x, y, pixelColor);

    // If the current pixel color is not the oldColor or is already filled, return
    if ((pixelColor[0] != oldColor[0] || pixelColor[1] != oldColor[1] || pixelColor[2] != oldColor[2]) ||
        (pixelColor[0] == fillColor[0] && pixelColor[1] == fillColor[1] && pixelColor[2] == fillColor[2]))
        return;

    // Fill the current pixel
    setPixelColor(x, y, fillColor);

    // Recursive calls in 4 directions
    floodFill(x + 1, y, fillColor, oldColor);
    floodFill(x - 1, y, fillColor, oldColor);
    floodFill(x, y + 1, fillColor, oldColor);
    floodFill(x, y - 1, fillColor, oldColor);
}

// Mouse click event handler
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oldColor[3];
        float fillColor[3] = {1.0, 0.0, 0.0}; // Red fill color

        int adjustedY = 400 - y; // Adjusting OpenGL coordinates

        getPixelColor(x, adjustedY, oldColor);
        floodFill(x, adjustedY, fillColor, oldColor);
    }
}

// Function to draw a sample boundary (closed shape)
void drawBoundary() {
    glColor3f(1.0, 1.0, 1.0); // White boundary
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(100, 300);
    glEnd();
    glFlush();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoundary();
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glColor3f(1.0, 1.0, 1.0); // White drawing color
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0); // 2D coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL Flood Fill Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
