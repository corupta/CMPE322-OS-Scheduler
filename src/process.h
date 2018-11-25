//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_PROCESS_H
#define CMPE322_PROJECT_1_PROCESS_H

#include "instructionReader.h";

class Process {
private:
  char* processName;
  int priority;
  char* programFile;
  int arrivalTime;
  int programCounter = 0;
  InstructionReader* instructionReader;
public:
  Process() = default;
  Process(const char*, int, const char*, int);
  ~Process();
  int next(int &);
  friend std::istream& operator>>(std::istream&, Process &);
  friend std::istream& operator>>(std::istream&, Process* &);
  friend std::ostream& operator<<(std::ostream&, const Process &);
  friend std::ostream& operator<<(std::ostream&, const Process* &);
  friend bool operator <(Process &, Process &);
};


#endif //CMPE322_PROJECT_1_PROCESS_H
