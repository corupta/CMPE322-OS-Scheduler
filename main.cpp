//
// Created by corupta on 24.11.2018.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include "src/simulation.h"

int main(int argc, char**argv) {
  std::ostream* outputStream;
  std::ofstream outputFileStream;
  int outputType; // 0 means output to cout, 1 means output to file
  if (argc == 1 || argc == 2) {
    if (argc == 2 && strcmp(argv[1], "stdout") == 0) {
      std::cout << "Starting the program in test environment." << std::endl;
      std::cout << "Printing the results into stdout" << std::endl << std::endl;
      outputStream = &std::cout;
      outputType = 0;
    } else {
      if (argc == 1) {
        std::cout << "Program started with no arguments." << std::endl;
        std::cout << "Defaulting output to \"output.txt\"" << std::endl;
        std::cout << "Starting the program in production environment." << std::endl;
        std::cout << "Printing the results into file, output.txt" << std::endl;
        std::cout << "Be aware that if there's a file named output.txt it will be OVERWRITTEN." << std::endl;
        outputFileStream.open("output.txt", std::ofstream::out);
        outputStream = &outputFileStream;
        outputType = 1;
      } else {
        std::cout << "Program started with a output file-path argument." << std::endl;
        std::cout << "Starting the program in production environment." << std::endl;
        std::cout << "Printing the results into file, " << argv[1] << std::endl;
        std::cout << "Be aware that if there's a file named " << argv[1] << " it will be OVERWRITTEN." << std::endl;
        outputFileStream.open(argv[1], std::ofstream::out);
        outputStream = &outputFileStream;
        outputType = 1;
      }
    }
  } else {
    std::cout << "ERROR: Program started with more than one argument." << std::endl;
    std::cout << "Please, call it as \"program\" to run it on production environment, printing to \"output.txt\" by default." << std::endl;
    std::cout << "Or, call it as \"program <file_path>\" to run it on production environment, printing to a file in given <file_path>." << std::endl;
    std::cout << "Or, call it as \"program stdout\" to run it on test environment, printing to stdout." << std::endl;
    std::cout << "If your <file_path> includes spaces, please encapsulate it with quotes. Ex:" << std::endl;
    std::cout << "program \"output folder/out.txt\"" << std::endl;
    std::cout << "Be aware that if there's a file named <file_path> it will be OVERWRITTEN." << std::endl;
    return 0;
  }

  Simulation* simulation;
  simulation = new Simulation(outputStream);
  // create a simulation with the provided outputStream
  int result = simulation->simulate(); // return 0 on success;
  // run the simulation
  delete simulation;
  // destroy the simulation

  if (outputType == 1) { // 1 means output to file
    outputFileStream.close();
    // close output file stream
  }
  // result is 0 if simulation succeeded
  return result;
}