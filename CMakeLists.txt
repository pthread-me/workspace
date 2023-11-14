cmake_minimum_required(VERSION 3.25)
project(workspace C)

set(CMAKE_C_STANDARD 11)


add_executable(workspace src/main.c lib/Matrix.c lib/Matrix.h lib/NeuralNetwork.c lib/NeuralNetwork.h)
target_link_libraries(workspace m)