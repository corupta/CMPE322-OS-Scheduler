//
// Created by corupta on 25.11.2018.
//

#include <string.h>
#include "process.h"

Process::Process(const char* processName, int priority, const char* programFile, int arrivalTime) {
  this->processName = strcpy(new char[strlen(processName) + 1], processName);
  this->programFile = strcpy(new char[strlen(programFile) + 5], programFile);
  // +5: 1 for \0 character 4 for .txt
  this->programFile = strcat(this->programFile, ".txt");
  this->priority = priority;
  this->arrivalTime = arrivalTime;
  this->instructionReader = new InstructionReader(this->programFile);
}

Process::~Process() {
  delete this->instructionReader;
  delete[] this->processName;
  delete[] this->programFile;
}

int Process::next(int & currentTime) {
  Instruction* instruction = this->instructionReader->next();
  int result = instruction->run(currentTime);
  ++this->programCounter;
  delete instruction;
  return result;
  // result=1 means exit, 0 means o/w
}

std::istream& operator>>(std::istream & in, Process & process) {
  return in >> process.processName >> process.priority >> process.programFile >> process.arrivalTime;
}
std::istream& operator>>(std::istream & in, Process* & process) {
  process = new Process;
  return in >> process;
}
std::ostream& operator<<(std::ostream & out, const Process & process) {
  return out << process.processName << "[" << process.programCounter + 1 << "]";
}
std::ostream& operator<<(std::ostream & out, const Process* & process) {
  return out << *process;
}
bool operator<(Process & processA, Process & processB) {
  if (processA.priority === processB.priority) {
    return processA.arrivalTime < processB.arrivalTime;
  }
  return processA.priority < processB.priority;
}

