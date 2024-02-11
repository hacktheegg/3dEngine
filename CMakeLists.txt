cmake_minimum_required(VERSION 3.10)
project("3dEngine")

set(CMAKE_CXX_STANDARD 11) # no explicit compiler flags if possible

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

add_executable("3dEngine" "3dEngine.cpp")
target_link_libraries(3dEngine ${OPENGL_LIBRARIES} glfw)
