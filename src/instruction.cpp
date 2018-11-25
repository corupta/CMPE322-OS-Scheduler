//
// Created by corupta on 25.11.2018.
//

#include "instruction.h"

Instruction::Instruction(const std::string & name, int execution_time) {
  this->name = name;
  this->executionTime = execution_time;
}

int Instruction::run(int &currentTime, int &runningTime) {
  // update currentTime by adding execution_time of the instruction.
  currentTime += this->executionTime;
  runningTime += this->executionTime;
  if (this->name == "exit") {
    // return 1 if the instruction is exit
    return 1;
  }
  // return 0 otherwise
  return 0;
}

std::istream& operator>>(std::istream & in, Instruction& instruction) {
  return in >> instruction.name >> instruction.executionTime;
}

std::ostream& operator<<(std::ostream & out, const Instruction & instruction) {
  return out << "<" << instruction.name << " : " << instruction.executionTime << "ms> ";
}

