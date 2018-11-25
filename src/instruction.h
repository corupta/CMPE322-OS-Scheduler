//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_INSTRUCTION_H
#define CMPE322_PROJECT_1_INSTRUCTION_H

#include <iostream>

class Instruction {
private:
  char* name,
  int executionTime;
public:
  Instruction() = default;
  Instruction(const char*, int);
  ~Instruction();
  int run(int &);
  friend std::istream& operator>>(std::istream&, Instruction &);
  friend std::istream& operator>>(std::istream&, Instruction* &);
  friend std::ostream& operator<<(std::ostream&, const Instruction &);
  friend std::ostream& operator<<(std::ostream&, const Instruction* &);
};


#endif //CMPE322_PROJECT_1_INSTRUCTION_H
