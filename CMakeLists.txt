cmake_minimum_required(VERSION 3.30)
project(cpp-game-engine)

set(CMAKE_CXX_STANDARD 20)

# Find the OpenGL package, ensuring CMake knows where OpenGL is installed
find_package(OpenGL REQUIRED)

add_executable(cpp-game-engine main.cpp)

# Link the necessary libraries properly:
# - OpenGL::GL: Standard OpenGL library
# - freeglut: FreeGLUT library (ensure it's installed on the system)
# - glu32: GLU (OpenGL Utility Library) required for gluOrtho2D function
target_link_libraries(cpp-game-engine OpenGL::GL freeglut glu32)
