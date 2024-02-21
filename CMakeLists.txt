cmake_minimum_required(VERSION 3.10)
project("3dEngine")

set(CMAKE_CXX_STANDARD 11) # no explicit compiler flags if possible

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# Specify the toolchain file for MinGW-w64
set(CMAKE_TOOLCHAIN_FILE "/usr/share/mingw-w64/toolchain-file")

set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

add_executable("3dEngine" "3dEngine.cpp")
target_link_libraries(3dEngine ${OPENGL_LIBRARIES} glfw)
