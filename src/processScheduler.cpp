//
// Created by corupta on 25.11.2018.
//

#include "processScheduler.h"

ProcessScheduler::ProcessScheduler(const std::string & definitionPath) {
  this->processReader = new ProcessReader(definitionPath);
  this->readyQueue = new ReadyQueue;
  this->currentProcess = nullptr;
}

ProcessScheduler::~ProcessScheduler() {
  if (this->processReader != nullptr) {
    delete this->processReader;
  }
  if (this->readyQueue != nullptr) {
    delete this->readyQueue;
  }
  if (this->currentProcess != nullptr) {
    delete this->currentProcess;
  }
  for (auto processIterator = this->processList.begin();  processIterator != this->processList.end(); ++processIterator) {
    delete (*processIterator);
  }
  this->processList.clear();
}

bool ProcessScheduler::next(int & currentTime) {
  bool queueChanged = false;
  if (this->currentProcess != nullptr) {
    // run next instruction if there's a current process
    if (this->currentProcess->next(currentTime) == 1) {
      // 1 means the process did run exit;
      this->currentProcess = nullptr;
      queueChanged = true;
    };
  }
  Process* nextProcess;
  nextProcess = this->processReader->next(currentTime);
  while (nextProcess != nullptr) {
    this->readyQueue->push(nextProcess);
    this->processList.push_back(nextProcess);

    queueChanged = true;
    nextProcess = this->processReader->next(currentTime);
  }
  if (this->currentProcess == nullptr) {
    this->currentProcess = this->readyQueue->pop();
  } else if (this->readyQueue->shouldInterrupt(this->currentProcess)) {
      this->readyQueue->push(this->currentProcess);
      this->currentProcess = this->readyQueue->pop();
      queueChanged = true;
  }
  if (this->currentProcess == nullptr) {
    nextProcess = this->processReader->skipToNext(currentTime);
    while (nextProcess != nullptr) {
      this->readyQueue->push(nextProcess);
      this->processList.push_back(nextProcess);

      queueChanged = true;
      nextProcess = this->processReader->next(currentTime);
    }
    this->currentProcess = this->readyQueue->pop();
    if (this->currentProcess == nullptr) {
      // if there's no current process and no more processes in both readyQueue and processReader
      // then, set finished flag of process scheduler to true;
      this->finished = true;
    }
  }
  return queueChanged;
}

bool ProcessScheduler::isFinished() {
  return this->finished;
}

std::ostream& operator<<(std::ostream & out, const ProcessScheduler & processScheduler) {
  out << "HEAD-";
  if (processScheduler.currentProcess != nullptr) {
    out << *(processScheduler.currentProcess);
    out << *(processScheduler.readyQueue);
  }
  out << "-TAIL";
  return out;
}

std::vector<Process*>* ProcessScheduler::getProcessList() {
  return &(this->processList);
}