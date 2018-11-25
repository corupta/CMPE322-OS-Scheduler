cmake_minimum_required(VERSION 3.12)
project(cmpe322_project_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(cmpe322_project_1 main.cpp src/instructionReader.cpp src/instructionReader.h src/instruction.cpp src/instruction.h src/process.cpp src/process.h)