//
// Created by corupta on 25.11.2018.
//

#include "instructionReader.h"

InstructionReader::InstructionReader(const std::string & programPath) {
  this->programStream.open(programPath, std::ifstream::in);
}

InstructionReader::~InstructionReader() {
  this->programStream.close();
}

Instruction* InstructionReader::next() {
  Instruction* instruction;
  instruction = new Instruction;
  this->programStream >> *instruction;
  return instruction;
}
