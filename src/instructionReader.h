//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_INSTRUCTIONREADER_H
#define CMPE322_PROJECT_1_INSTRUCTIONREADER_H

#include <fstream>
#include <string>
#include "instruction.h"

class InstructionReader {
private:
  std::ifstream programStream;
public:
  explicit InstructionReader(const std::string &);
  ~InstructionReader();
  Instruction* next();
};


#endif //CMPE322_PROJECT_1_INSTRUCTIONREADER_H
