//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_INSTRUCTION_H
#define CMPE322_PROJECT_1_INSTRUCTION_H

#include <iostream>
#include <string>

class Instruction {
private:
  std::string name;
  int executionTime = -1;
public:
  Instruction() = default; // to be used by istream with pointer only
  Instruction(const std::string &, int);
  ~Instruction() = default;
  int run(int &, int &);
  friend std::istream& operator>>(std::istream&, Instruction &);
  friend std::ostream& operator<<(std::ostream&, const Instruction &);
};


#endif //CMPE322_PROJECT_1_INSTRUCTION_H
