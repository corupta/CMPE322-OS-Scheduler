//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_INSTRUCTIONREADER_H
#define CMPE322_PROJECT_1_INSTRUCTIONREADER_H

#include <fstream>
#include "instruction.h"

class InstructionReader {
private:
  std::ifstream programStream;
public:
  InstructionReader(const char*);
  ~InstructionReader();
  Instruction* next();
};


#endif //CMPE322_PROJECT_1_INSTRUCTIONREADER_H
