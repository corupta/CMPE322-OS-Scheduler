//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_PROCESSSCHEDULER_H
#define CMPE322_PROJECT_1_PROCESSSCHEDULER_H

#include <string>
#include <vector>
#include "readyQueue.h"
#include "processReader.h"
#include "process.h"

class ProcessScheduler {
private:
  std::vector<Process*> processList;
  ReadyQueue* readyQueue;
  ProcessReader* processReader;
  Process* currentProcess;
  bool finished = false;
public:
  explicit ProcessScheduler(const std::string &);
  ~ProcessScheduler();
  bool next(int &); // return whether or not to print;
  bool isFinished(); // return whether or not all processes did finished
  std::vector<Process*>* getProcessList();
  friend std::ostream& operator<<(std::ostream&, const ProcessScheduler &);
};


#endif //CMPE322_PROJECT_1_PROCESSSCHEDULER_H
