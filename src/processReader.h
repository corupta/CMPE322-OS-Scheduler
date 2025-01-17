//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_PROCESSREADER_H
#define CMPE322_PROJECT_1_PROCESSREADER_H

#include <string>
#include <fstream>
#include "process.h"

class ProcessReader {
private:
  std::ifstream processStream;
  Process* nextProcess;
  std::string lastProcessName = "";
  void readNext(); // internally used to read next process onto nextProcess buffer
public:
  explicit ProcessReader(const std::string &);
  ~ProcessReader();
  Process* next(const int &); // returns next arrived process or null
  Process* skipToNext(int &); // wait until next process arrives;
};


#endif //CMPE322_PROJECT_1_PROCESSREADER_H
