cmake_minimum_required(VERSION 3.30)
project(dev-game-engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(dev-game-engine main.cpp glmatrix.h glmatrix.cpp)
target_link_libraries(dev-game-engine -lOpenGL32 -lfreeGLUT)
