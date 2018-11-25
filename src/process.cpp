//
// Created by corupta on 25.11.2018.
//

#include "process.h"

Process::Process(const std::string & processName, int priority, const std::string & programFile, int arrivalTime) {
  this->processName = processName;
  this->programFile = programFile;
  this->programFile += ".txt";
  this->priority = priority;
  this->arrivalTime = arrivalTime;
  this->instructionReader = new InstructionReader(this->programFile);
}

Process::~Process() {
  delete this->instructionReader;
}

int Process::next(int & currentTime) {
  Instruction* instruction = this->instructionReader->next();
  int result = instruction->run(currentTime, this->runningTime);
  ++this->programCounter;
  delete instruction;
  if (result == 1) {
    this->finishTime = currentTime;
  }
  return result;
  // result=1 means exit, 0 means o/w
}

bool Process::arrive(int & currentTime) {
  return this->arrivalTime <= currentTime;
}

void Process::waitForArrival(int & currentTime) {
  if (this->arrivalTime > currentTime) {
    currentTime = this->arrivalTime;
  }
}

std::istream& operator>>(std::istream & in, Process & process) {
  in >> process.processName >> process.priority >> process.programFile >> process.arrivalTime;
  process.programFile += ".txt";
  process.instructionReader = new InstructionReader(process.programFile);
  return in;
}
std::ostream& operator<<(std::ostream & out, const Process & process) {
  return out << process.processName << "[" << process.programCounter + 1 << "]";
}
bool operator<(Process & processA, Process & processB) {
  // is processA is less prioritized than processB
  if (processA.priority == processB.priority) {
    return processA.arrivalTime > processB.arrivalTime;
    // higher arrivalTime is less prioritized
  }
  return processA.priority > processB.priority;
  // higher priority is less prioritized
}

std::string Process::getProcessName() {
  return this->processName;
}

int Process::getWaitingTime() {
  return this->getTurnaroundTime() - this->runningTime;
}

int Process::getTurnaroundTime() {
  return this->finishTime - this->arrivalTime;
}

bool Process::Compare::operator()(Process * processA, Process * processB) {
  return *processA < *processB;
}