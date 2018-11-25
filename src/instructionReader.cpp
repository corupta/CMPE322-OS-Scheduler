//
// Created by corupta on 25.11.2018.
//

#include "instructionReader.h"

InstructionReader::InstructionReader(const char * programPath) {
  this->programStream.open(programPath, std::ifstream::in);
}

InstructionReader::~InstructionReader() {
  this->programStream.close();
}

Instruction* InstructionReader::next() {
  Instruction* instruction;
  this->programStream >> instruction;
  return instruction;
}
