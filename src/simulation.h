//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_SIMULATION_H
#define CMPE322_PROJECT_1_SIMULATION_H

#include <iostream>
#include "processScheduler.h"
#include "process.h"

class Simulation {
private:
  ProcessScheduler* processScheduler;
  std::ostream* out;
  int currentTime = 0;
  void printState();
  void printProcessAnalysis(Process* & process);
public:
  explicit Simulation(std::ostream* &);
  ~Simulation();
  int simulate();
};


#endif //CMPE322_PROJECT_1_SIMULATION_H
