#include <GL/gl.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>



struct vector3d {
  float x,y,z;
};

struct triangle {
  vector3d p[3];
};

struct mesh {
  std::vector<triangle> tris;
};

struct matrix4by4 {
  float m[4][4] = { 0 }; // [row][column]
};




class engine3d {
  private:
    mesh meshCube;
    matrix4by4 matrixProjection;

    float fTheta;

    void multiplyMatrixVector(vector3d &i, vector3d &o, matrix4by4 &m) {
      o.x = (i.x * m.m[0][0]) + (i.y * m.m[1][0]) + (i.z * m.m[2][0]) + m.m[3][0];
      o.y = (i.x * m.m[0][1]) + (i.y * m.m[1][1]) + (i.z * m.m[2][1]) + m.m[3][1];
      o.z = (i.x * m.m[0][2]) + (i.y * m.m[1][2]) + (i.z * m.m[2][2]) + m.m[3][2];
      float w = (i.x * m.m[0][3]) + (i.y * m.m[1][3]) + (i.z * m.m[2][3]) + m.m[3][3];

      if (w != 0.0f) {
        o.x /= w; o.y /= w; o.z /= w;
      }
    }

  public:
    void onCreate(GLFWwindow* window) {

      meshCube.tris = {

        // SOUTH
        { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

        // EAST                                                      
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

        // NORTH                                                     
        { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

        // WEST                                                      
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

        // TOP                                                       
        { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
        { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

        // BOTTOM                                                    
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f }

      };

      float fNear = 0.1f;
      float fFar = 1000.0f;
      float fFov = 90.0f;

      // GLFWwindow* window = *//* your GLFW window object *//*;
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      float fAspectRatio = height / width;
      float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

      matrixProjection.m[0][0] = fAspectRatio * fFovRad;
      matrixProjection.m[1][1] = fFovRad;
      matrixProjection.m[2][2] = fFar / (fFar - fNear);
      matrixProjection.m[3][2] = (-fFar * fNear) / (fFar - fNear);
      matrixProjection.m[2][3] = 1.0f;
      matrixProjection.m[3][3] = 0.0f;
    }



    int mainLoop(GLFWwindow* window) {

      double elapsedTime = glfwGetTime();

      int width, height;
      glfwGetWindowSize(window, &width, &height);
      
      // Loop until the user closes the window
      while (!glfwWindowShouldClose(window)) {
        // Render here
        glClearColor(0.2f,  0.3f,  0.3f,  1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        matrix4by4 matrixRotationX, matrixRotationZ;

        double deltaTime = glfwGetTime() - elapsedTime; // Change in Time
        elapsedTime = glfwGetTime(); // Time passed from Initialize
        fTheta += 1.0f * deltaTime;

        // Rotation Z
        matrixRotationZ.m[0][0] = cosf(fTheta);
        matrixRotationZ.m[0][1] = sinf(fTheta);
        matrixRotationZ.m[1][0] = -sinf(fTheta);
        matrixRotationZ.m[1][1] = cosf(fTheta);
        matrixRotationZ.m[2][2] = 1;
        matrixRotationZ.m[3][3] = 1;

        // Rotation Z
        matrixRotationX.m[0][0] = 1;
        matrixRotationX.m[1][1] = cosf(fTheta * 0.5f);
        matrixRotationX.m[1][2] = sinf(fTheta * 0.5f);
        matrixRotationX.m[2][1] = -sinf(fTheta * 0.5f);
        matrixRotationX.m[2][2] = cosf(fTheta * 0.5f);
        matrixRotationX.m[3][3] = 1;

        // Draw Triangles
        for (auto tri : meshCube.tris) {
          triangle triangleProjected, triangleTranslated, triangleRotatedZ, triangleRotatedZX;

          // Rotate in Z-Axis
          multiplyMatrixVector(tri.p[0], triangleRotatedZ.p[0], matrixRotationZ);
          multiplyMatrixVector(tri.p[1], triangleRotatedZ.p[1], matrixRotationZ);
          multiplyMatrixVector(tri.p[2], triangleRotatedZ.p[2], matrixRotationZ);

          // Rotate in X-Axis
          multiplyMatrixVector(triangleRotatedZ.p[0], triangleRotatedZX.p[0], matrixRotationX);
          multiplyMatrixVector(triangleRotatedZ.p[1], triangleRotatedZX.p[1], matrixRotationX);
          multiplyMatrixVector(triangleRotatedZ.p[2], triangleRotatedZX.p[2], matrixRotationX);

          // Offset into the Screen
          triangleTranslated = triangleRotatedZX;
          triangleTranslated.p[0].z = triangleRotatedZX.p[0].z + 3.0f;
          triangleTranslated.p[1].z = triangleRotatedZX.p[1].z + 3.0f;
          triangleTranslated.p[2].z = triangleRotatedZX.p[2].z + 3.0f;

          // Project Triangles from 3D --> 2D
          multiplyMatrixVector(triangleTranslated.p[0], triangleProjected.p[0], matrixProjection);
          multiplyMatrixVector(triangleTranslated.p[1], triangleProjected.p[1], matrixProjection);
          multiplyMatrixVector(triangleTranslated.p[2], triangleProjected.p[2], matrixProjection);

          // Scale into View {I genuinely have no idea what this means}
          triangleProjected.p[0].x += 1.0f; triangleProjected.p[0].y += 1.0f;
          triangleProjected.p[1].x += 1.0f; triangleProjected.p[1].y += 1.0f;
          triangleProjected.p[2].x += 1.0f; triangleProjected.p[2].y += 1.0f;
          triangleProjected.p[0].x *= 0.5f * width;
          triangleProjected.p[0].y *= 0.5f * height;
          triangleProjected.p[1].x *= 0.5f * width;
          triangleProjected.p[1].y *= 0.5f * height;
          triangleProjected.p[2].x *= 0.5f * width;
          triangleProjected.p[2].y *= 0.5f * height;

          // Rasterize Triangle (Actually Display Them)
          glColor3d(0, 0, 0);
          glBegin(GL_POLYGON);

          glVertex2d(triangleProjected.p[0].x, triangleProjected.p[0].y);
          glVertex2d(triangleProjected.p[1].x, triangleProjected.p[1].y);
          glVertex2d(triangleProjected.p[2].x, triangleProjected.p[2].y);

          glEnd();

        }

        // drawSquare(0.0, 0.0, 0.2);
        /*double halfSide = 0.2;

        glColor3d(0, 0, 0);
        glBegin(GL_POLYGON);

        glVertex2d(0.0f + halfSide, 0.0f + halfSide);
        glVertex2d(0.0f + halfSide, 0.0f - halfSide);
        glVertex2d(0.0f - halfSide, 0.0f - halfSide);
        glVertex2d(0.0f - halfSide, 0.0f + halfSide);

        glEnd();*/





        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
      }

      glfwTerminate();
      return 0;
    }

};



int main() {
  // Initialize the library
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }
  // Create a windowed mode window and its OpenGL context
  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  
  // Make the window's context current
  glfwMakeContextCurrent(window);


  engine3d engine;
  engine.onCreate(window);
  int var = engine.mainLoop(window);
  return var;
}












/*
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
}*/
