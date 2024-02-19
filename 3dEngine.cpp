#include <GL/gl.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>





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

    void MultiplyMatrixVector(vector3d &i, vector3d &o, matrix4by4 &m) {
      o.x = (i.x * m.m[0][0]) + (i.y * m.m[1][0]) + (i.z * m.m[2][0]) + m.m[3][0];
      o.y = (i.x * m.m[0][1]) + (i.y * m.m[1][1]) + (i.z * m.m[2][1]) + m.m[3][1];
      o.z = (i.x * m.m[0][2]) + (i.y * m.m[1][2]) + (i.z * m.m[2][2]) + m.m[3][2];
      float w = (i.x * m.m[0][3]) + (i.y * m.m[1][3]) + (i.z * m.m[2][3]) + m.m[3][3];

      if (w != 0.0f) {
        o.x /= w; o.y /= w; o.z /= w;
      }
    }
  public:
    bool onCreate(GLFWwindow* window) {
      
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

      // GLFWwindow* window = /* your GLFW window object */;
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      float fAspectRatio = static_cast<float>(height) / static_cast<float>(width);
      float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

      matrixProjection.m[0][0] = fAspectRatio * fFovRad;
      matrixProjection.m[1][1] = fFovRad;
      matrixProjection.m[2][2] = fFar / (fFar - fNear);
      matrixProjection.m[3][2] = (-fFar * fNear) / (fFar - fNear);
      matrixProjection.m[2][3] = 1.0f;
      matrixProjection.m[3][3] = 0.0f;



      return true;
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
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Render here
    glClearColor(0.2f,  0.3f,  0.3f,  1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // drawSquare(0.0, 0.0, 0.2);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
  return  0;

}






/*
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
  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
*/
