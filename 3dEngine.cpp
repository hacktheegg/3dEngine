#include <GL/gl.h>
#include <iostream>
#include <GLFW/glfw3.h>



void drawSquare(double x1, double y1, double sideLength) {
  double halfSide = sideLength;

  glColor3d(0, 0, 0);
  glBegin(GL_POLYGON);

  glVertex2d(x1 + halfSide, y1 + halfSide);
  glVertex2d(x1 + halfSide, y1 - halfSide);
  glVertex2d(x1 - halfSide, y1 - halfSide);
  glVertex2d(x1 - halfSide, y1 + halfSide);

  glEnd();
}



int main() {
    // Initialize the library
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640,  480, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClearColor(0.2f,  0.3f,  0.3f,  1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawSquare(0.0, 0.0, 0.2);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return  0;
}
