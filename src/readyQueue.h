//
// Created by corupta on 25.11.2018.
//

#ifndef CMPE322_PROJECT_1_READYQUEUE_H
#define CMPE322_PROJECT_1_READYQUEUE_H

#include <iostream>
#include <queue>
#include <vector>
#include "process.h"

class ReadyQueue {
private:
  std::priority_queue<Process *, std::vector<Process *>, Process::Compare> queue;
public:
  ReadyQueue() = default;
  ~ReadyQueue();
  void push(Process *);
  Process* pop();
  bool shouldInterrupt(Process * &);
  friend std::ostream& operator<<(std::ostream&, const ReadyQueue &);
};


#endif //CMPE322_PROJECT_1_READYQUEUE_H
