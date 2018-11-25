//
// Created by corupta on 25.11.2018.
//

#include "processReader.h"

ProcessReader::ProcessReader(const std::string & processPath) {
  this->processStream.open(processPath, std::ifstream::in);
  this->nextProcess = nullptr;
}

ProcessReader::~ProcessReader() {
  this->processStream.close();
}

void ProcessReader::readNext() {
  this->nextProcess = new Process;
  if (this->processStream.good()) {
    // read next process if the stream is good (no EOF reached)
    this->processStream >> *(this->nextProcess); // read next process
  } else {
    // set the next process to null directly
    this->nextProcess = nullptr;
  }
  if (this->nextProcess != nullptr && !this->processStream.good()) {
    // if the process is read successfully (no EOF reached)
    // then the processStream should be good
    // o/w check if the read process has the same name as the last process
    // if it has the same name that means the last line is read again, so return nullptr instead;
    // (if there's an extra space/line at the end of the line,
    // then last line will be read again causing the same processName)
    // if it has an empty name that means an empty line is read in the end of file, so return nullptr instead;
    // (if there's an extra line at the end of the line, then the last process would have empty name)
    if (this->nextProcess->getProcessName() == "" ||
        this->lastProcessName == this->nextProcess->getProcessName()) {
      delete this->nextProcess;
      this->nextProcess = nullptr;
    }
  }
  if (this->nextProcess != nullptr) {
    // if the next process is valid set its name into lastProcessName
    this->lastProcessName = this->nextProcess->getProcessName();
  }
}

Process* ProcessReader::next(int & currentTime) {
  Process * returnProcess = nullptr;
  if (this->nextProcess == nullptr) {
    // if there's no process read, waiting to arrive read next
    this->readNext();
  }
  if (this->nextProcess != nullptr) {
    // there's a process read, waiting to arrive
    if (this->nextProcess->arrive(currentTime)) {
      // if the process should arrive, clear waiting process buffer
      // and return the process
      returnProcess = this->nextProcess;
      this->nextProcess = nullptr;
    } // returns nullptr otherwise
  }
  return returnProcess;
}

Process* ProcessReader::skipToNext(int & currentTime) {
  if (this->nextProcess != nullptr) {
    // if there's a process read, waiting to arrive wait for its arrival
    this->nextProcess->waitForArrival(currentTime);
  }
  return this->next(currentTime);
}