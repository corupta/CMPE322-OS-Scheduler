//
// Created by corupta on 25.11.2018.
//

#include <string.h>
#include "instruction.h"

Instruction::Instruction(const char *name, int execution_time) {
  this->name = strcpy(new char[strlen(name) + 1], name);
  this->executionTime = execution_time;
}

Instruction::~Instruction() {
  delete[] this->name;
}

int Instruction::run(int &currentTime) {
  // update currentTime by adding execution_time of the instruction.
  currentTime += this->executionTime;
  if (strcmp(this->name, "exit") == 0) {
    // return 1 if the instruction is exit
    return 1;
  }
  // return 0 otherwise
  return 0;
}

std::istream& operator>>(std::istream & in, Instruction& instruction) {
  return in >> instruction.name >> instruction.executionTime;
}

std::istream& operator>>(std::istream & in, Instruction *& instruction) {
  instruction = new Instruction;
  return in >> instruction;
}

std::ostream& operator<<(std::ostream & out, const Instruction & instruction) {
  return out << "<" << instruction.name << " : " << instruction.executionTime << "ms> ";
}

std::ostream& operator<<(std::ostream & out, const Instruction* & instruction) {
  return out << *instruction;
}
