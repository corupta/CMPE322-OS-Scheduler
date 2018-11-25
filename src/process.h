//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_PROCESS_H
#define CMPE322_PROJECT_1_PROCESS_H

#include <string>
#include <iostream>
#include "instructionReader.h"

class Process {
private:
  std::string processName;
  int priority = -1;
  std::string programFile;
  int arrivalTime = -1;
  int finishTime = -1;
  int runningTime = 0;
  int programCounter = 0;
  InstructionReader* instructionReader = nullptr;
public:
  Process() = default; // to be used by istream with pointer only
  Process(const std::string &, int, const std::string &, int);
  ~Process();
  int next(int &);
  bool arrive(const int &); // returns true if the process should be arrived by now
  void waitForArrival(int &); // skip time to process' arrival
  friend std::istream& operator>>(std::istream&, Process &);
  friend std::ostream& operator<<(std::ostream&, const Process &);
  friend bool operator <(Process &, Process &);
  std::string getProcessName();
  int getWaitingTime();
  int getTurnaroundTime();
  class Compare {
  public:
    bool operator() (Process*, Process*);
  };
};


#endif //CMPE322_PROJECT_1_PROCESS_H
