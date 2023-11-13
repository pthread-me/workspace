cmake_minimum_required(VERSION 3.25)
project(matrix_mul C)

set(CMAKE_C_STANDARD 11)

add_executable(matrix_mul src/main.c lib/Matrix.c lib/Matrix.h)
