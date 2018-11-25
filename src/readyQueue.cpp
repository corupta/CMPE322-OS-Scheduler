//
// Created by corupta on 25.11.2018.
//

#include "readyQueue.h"

ReadyQueue::~ReadyQueue() {
  while (!this->queue.empty()) {
    this->queue.pop();
  }
}

void ReadyQueue::push(Process* nextProcess) {
  this->queue.push(nextProcess);
}

Process* ReadyQueue::pop() {
  Process *nextProcess = nullptr;
  if (!this->queue.empty()) {
    nextProcess = this->queue.top();
    this->queue.pop();
  }
  return nextProcess;
}

bool ReadyQueue::shouldInterrupt(Process* & currentProcess) {
  Process *nextProcess;
  if (this->queue.empty()) {
    return false;
    // there's no process in ready queue, thus no interrupt
  }
  nextProcess = this->queue.top();
  return *currentProcess < *nextProcess;
  // return whether nextProcess has a higher priority than the current one;
}

std::ostream& operator<<(std::ostream & out, const ReadyQueue & readyQueue) {
  std::priority_queue<Process*, std::vector<Process*>, Process::Compare> print_queue = readyQueue.queue;
  while (!print_queue.empty()) {
    out << "-" << *(print_queue.top());
    print_queue.pop();
  }
  return out;
}
