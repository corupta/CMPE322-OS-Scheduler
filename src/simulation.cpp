//
// Created by corupta on 25.11.2018.
//

#include "simulation.h"

Simulation::Simulation(std::ostream* & out) {
  this->out = out;
  this->processScheduler = new ProcessScheduler("definition.txt");
  // create a process scheduler to read definition.txt and run the defined processes there.
}
Simulation::~Simulation() {
  if (this->processScheduler != nullptr) {
    // destroy ProcessScheduler which internally destroys all used objects
    delete this->processScheduler;
  }
}

void Simulation::printState() {
  *(this->out) << this->currentTime << ":" << *(this->processScheduler) << std::endl;
}

void Simulation::printProcessAnalysis(Process *&process) {
  *(this->out) << "Turnaround time for " << process->getProcessName();
  *(this->out) << " = " << process->getTurnaroundTime() << " ms" << std::endl;
  *(this->out) << "Waiting time for " << process->getProcessName();
  *(this->out) << " = " << process->getWaitingTime();

}

int Simulation::simulate() {
  // print initial state
  this->printState();
  // run process scheduler and print states whenever necessary
  while(!this->processScheduler->isFinished()) {
    if (this->processScheduler->next(this->currentTime)) {
      // processScheduler->next returns true if a change in queue happens
      // (if the currentState should be printed)
      this->printState();
    }
  }
  // processScheduler finished all processes
  // print out analysis for each process
  std::vector<Process *>* processList;
  processList = this->processScheduler->getProcessList();
  for (auto processIterator = processList->begin(); processIterator != processList->end(); ++processIterator) {
    *(this->out) << std::endl;
    printProcessAnalysis(*processIterator);
  }
  // successfully finished, return 0;
  // commented newline because the output.txt in Provided Files did not have an endline at the end
  // if you'd like the program to print an endline in the end, just uncomment the next line
  // *(this->out) << std::endl; // uncomment this line to toggle printing endline in the end of file
  return 0;
}
