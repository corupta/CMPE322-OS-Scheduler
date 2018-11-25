cmake_minimum_required(VERSION 2.8)
project(cmpe322_project_1)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(INSTRUCTION_CLASS src/instruction.h src/instruction.cpp)
set(INSTRUCTION_READER_CLASS src/instructionReader.h src/instructionReader.cpp)
set(PROCESS_CLASS src/process.h src/process.cpp)
set(READY_QUEUE_CLASS src/readyQueue.h src/readyQueue.cpp)
set(PROCESS_READER_CLASS src/processReader.h src/processReader.cpp)
set(PROCESS_SCHEDULER_CLASS src/processScheduler.h src/processScheduler.cpp)
set(SIMULATION_CLASS src/simulation.h src/simulation.cpp)

set(CLASS_FILES ${INSTRUCTION_CLASS} ${INSTRUCTION_READER_CLASS} ${PROCESS_CLASS} ${READY_QUEUE_CLASS} ${PROCESS_READER_CLASS} ${PROCESS_SCHEDULER_CLASS} ${SIMULATION_CLASS})

set(SOURCE_FILES main.cpp ${CLASS_FILES})

add_executable(cmpe322_project_1 ${SOURCE_FILES})