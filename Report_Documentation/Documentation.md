# CMPE322-OS-Scheduler

### Simulating a Preemptive Priority Scheduling
### Created by Halit Özsoy - 2016400141

## Project Details

In summary, the objective was to create a process scheduling simulator for a one core/one cpu environment such that,

* It reads "definition.txt" to obtain the process unique names, paths, priorities and arrival times to simulate them.
* Then, it simulates running these processes which are defined as a couple of instructions.
    * List of instructions should be read from <program_name>.txt
    * Each instruction is defined as name and execution time.
    * Each program file includes a special instruction, `exit` which should finish the process.
* An instruction cannot be blocked by an interrupt but a process can be.
* Smaller priority number means higher priority.
* When two processes have the same priority number, their priority is decided in FCFS (First Come First Serve) order. 
* After each instruction, the next instruction of the highest priority process should be run.
* When a process with a higher priority then the current running process arrives, after current process' current instruction finishes, current state of the current process is saved and the new process is ran instead.
* Simulate running these processes and output program states when a change in ReadyQueue happens (a new process arrives/an old process finishes)
* Also, output analysis for each process in the end by calculating and outputting waiting and turnaround time of each process ordered by their arrival time.

## My Solution

I've taken an OOP approach, (although there're no extending classes or polymorphism but there're children&parent class objects)

I've created Classes which are responsible for only their tasks.

As a result, every object has its own responsibilities and their internal logic for completing these without interfering with each other's responsibilities.

### Source Code Documentation

#### The hierarchy of the files can be shown as
* Main Source: `main.cpp`
    * Simulation Class: `simulation`
        * ProcessScheduler Class: `processScheduler`
            * ReadyQueue Class: `readyQueue`
                * Process Queue: `priority_queue<Process *> queue`
                    * Process Class
            * ProcessReader Class `processReader`
                * Process Class `nextProcess`
                * Process Stream: `std::istream processStream` 
            * Process List: `vector<Process *> processList`
                * Process Class


* Process Class
    * InstructionReader: `instructionReader`
        * Instruction: `nextInstruction`
        * Instruction Stream: `std::istream instructionStream`
                        
#### Description of the source classes and main.cpp

* Instruction Class
    * Should know its `name` and `execution_time`
    * Can be run updating given global time and given process running time
    * Should return a different signal when run, if it's an `exit` instruction
    * Should define `>> operator` (how it can be read from i/o)
    
* InstructionReader Class
    * Should know where to read instructions of a program
    * Should handle reading next instruction from i/o
    * Should be able to read and return next instruction
    
* Process Class
    * Should know its `name`, `arrivalTime`, `runningTime`, `programCounter`, `priority`
    * Should own an `InstructionReader` to get instructions from i/o
    * Should be able to run an instruction, given global time, updating its internal `runningTime` and `programCounter`
    * Should return a different signal when runs an `exit` instruction
    * Should be comparable with each other by their `priority` and `arrivalTime`
    * Should define `>> operator` (how it can be read from i/o)
    * Should define `<< operator` (how it can be printed to i/o `<name>[<programCounter]`
    * Should be able to calculate and return its turnaround time
    * Should be able to calculate and return its waiting time
  
* ProcessReader Class
    * Should know where to read definitions of processes (`definition.txt`)
    * Should handle reading next process from i/o
    * Should be able to buffer next process until its arrivalTime is reached
    * Given global time, should return the next arrived process if one arrives within that time.
    * Given global time, should be able to skip the time to next instructions's arrival, and return that instruction

* ReadyQueue Class
    * Should implement a `priority_queue` structure internally, to order processes by their `priority` and `arrival times`.
    * Should implement pushing and popping a process into its internal priority_queue
    * Given current running process, should be able to return whether it should be interrupted (whether there's a process with higher priority in the queue)
    * Should define `<< operator` (how it can be printed to i/o) `-<process1>-<process2>...` 
  
* ProcessScheduler Class
    * Should own a `ReadyQueue` to decide which process to be run next
    * Should own a `ProcessReader` to get newly arrived processes
    * Should keep track of all arrived processes in their arrival order, so that their time analysis can be printed in the end
    * Should be able to return that process list 
    * Given current global time, should implement a method to execute next instruction of the next/current process, returning a different signal if the queue changes so that the queue should be printed.
    * Should be able to check `ProcessReader` for newly arrived processes after execution of each instruction
    * Should be able to skip to next process' arrival when there're no waiting processes.
    * Should keep track of whether or not all the processes are read & finished.
    * Should be able to return whether all the processes are finished.
 
* Simulation Class
    * Should be created with an output stream, providing it to each output operation.
    * Should own a global time property for the simulation
    * Should own a `ProcessScheduler` to use it for simulation
    * Should run `ProcessScheduler` step by step where one instruction is done in each step (or skipping until next process comes) giving its global time
    * Should print its time and current state of the queue when it receives signal that the queue is changed from ProcessScheduler
    * Should keep running `ProcessScheduler` until receiving finished signal from it.
    * Should get process list from `ProcessScheduler` after the simulation ends.
    * Then it should print process analysis for each process, using these processes' functions.
    * Should be responsible for all printing operations. (Including, calling internal print operations of internal objects)
    * Should `return 0` when it finishes, to mean that it finished successfully. (No error  is thrown)
    
* main.cpp
    * Should be responsible for handling command line arguments and creating output stream.
    * Should print out how the program should be run, when provided with wrong arguments
    * Should be able to run without arguments defaulting the output stream to `output.txt`
    * Should own a `Simulation` object and provide an output stream to it
    * Should not include any logic about simulation
    * Should run simulation method of the `Simulation` object and save its result to return in the end
    * Should close output stream and destroy `Simulation` object in the end.
    * Should return the result of simulation in the end (0 when successful)

### Documentation of Public Functions of Each Class
* Instruction
    * `Instruction()` : default constructor that doesn't set anyting,
    * `Instruction(const std::string & name, int execution_time);` : constructor
    * `~Instruction()` : default destructor
    * `int run(int & currentTime, int & runningTime)` : run the instruction by increasing global simulation time, `currentTime`, and process running time `runningTime`.
        `Returns 1` if the instruction is `exit`, `returns 0` otherwise.
    * `operator >>` print instruction in format `<[name]:[execution_time]ms>` to given `ostream` and return the given `ostream`
    * `operator <<` read instruction name and execution from given `istream` and return the given `istream`
    
* InstructionReader
    * `InstructionReader(const std::string & programPath)` constructor that opens an internal `ifstream` from `programPath`
    * `~InstructionReader()` destructor that closes the open `ifstream`
    * `Instruction* next()` creates and returns new `Instruction` reading from internal `ifstream`
 
* Process
    * `Process()` : default constructor
    * `Process(const std::string & processName, int priority, const std::string & programFile, int arrivalTime)` constructor
    * `~Process()` : destructor, deletes internal `InstructionReader`
    * `int next(int & currentTime)` : runs next instruction, increasing given global simulation time, `returns 1` on `exit` instruction, otherwise `returns 0`
    * `bool arrive(const int & currentTime)` : returns true if the process should be arrived by given global simulation time.
    * `void waitForArrival(int & currentTime)` : skips given global simulation time to the (its) process' arrival
    * `operator >>` and `operator <<` : read process definition from given `istream` and output process status to given `ostream` in format, `<name>[<programCounter>]`, respectively
    * `operator <` : compare with another process by their priority and arrival time. `returns true` if the left hand side process is lower prioritized, otherwise `returns false`
    * `std::string getProcessName()`: return its `name`
    * `int getWaitingTime()` : calculate and return its waiting time
    * `int getTurnaroundTime()` : calculate and return its turnaround time
    * `class Compare` : compare class to be provided to a `priority_queue<Process *>` instead of `priority_queue<Process>`
    
* ProcessReader
    * `ProcessReader(const std::string processPath)` : constructor that opens `processPath` in internal `ifstream`
    * `~ProcessReader()` : destructor that closes internal `ifstream`
    * `Process* next(const int & currentTime)` : read/return `nextProcess` if it is arrived by given global simulation time
    * `Process* skipToNext(int & currentTime)` : read/return `nextProcess` skipping the given global time until that process' `arrival_time`
    
* ReadyQueue
    * `ReadyQueue()` : default constructor
    * `~ReadyQueue()` : destructor that cleans up its `priority_queue`
    * `void push(Process * nextProcess)` : push the given process to its `priority_queue`
    * `Process* pop()` : pop and return the top value of its `priority_queue`
    * `bool shouldInterrupt(Process* & currentProcess)` : `return true` if the top `Process` in its `priority_queue` has a higher priority than the given one, `returns false` otherwise
    * `operator <<` : output all `Processes` in its `priority_queue` in their order in the queue, separated by dashes (`-`) to the given `ostream`
 
* PriorityQueue
    * `ProcessScheduler(const std::string & definitionPath)` : constructor that sets an internal `ProcessReader` with the given definition path
    * `~ProcessScheduler()` : destructor that destroys its inner `ReadyQueue`, `ProcessReader`, `ProcessList` and the all `Process` in the `ProcessList` (all defined processes)
    * `bool next(int & currentTime)` : runs the next instruction from next queued process updating given global simulation time and taking care of newly arrived/finished processes. `returns true` if the queue changes (meaning, it should be printed), `returns false` otherwise
    * `bool isFinished()` : returns true if all processes are read and completed (all processes completed instruction `exit`).
    * `std::vector<Process*>* getProcessList()` : returns the list of all processes by their arrival times, so that their analysis can be printed
    * `operator <<` : prints current state of its `currentProcess` as well as its `readyQueue` to the given stream in the format `HEAD-<currentProcess>-<readyQueue>-TAIL`
    
* Simulation
    * `Simulation(std::ostream *)` : constructor setting its internal `ostream` to the provided one and creating an inner `ProcessScheduler`
    * `~Simulation()` : destructor that destroys its inner `ProcessScheduler`
    * `int simulate()` : simulates the whole processes with the `ProcessScheduler` by running it step by step, printing its state when there's a change in nested queue, until the `ProcessScheduler` returns a `finished` signal. Afterwards, it gets the `ProcessList` from its `ProcessScheduler` and prints the analysis details (`turnaroundTime` and `waitingTime`) of each `Process` in the `Process List`. Finally, it `returns 0` unless an error occurs.
 
* main.cpp
    * `int main(int argc, char **argv)` : main function of the program
        * First, creates a `ostream` with the given `filePath` or `"output.txt"` by default. 
        * Then, it creates a `Simulation` object with that `ostream`. 
        * Then, runs the `Simulation` object, saves it result. 
        * Then, destroys the `Simulation` object and closes the `ostream`.
        * Finally, returns the result of the `Simulation` (`returns 0` on successfull simulation)  
     

## How To Compile

In order to compile this program you need `cmake` and `make` installed.

In a terminal, call commands:
```
cmake CMakeLists.txt
make
```
OR
```
cmake CMakeLists.txt && make
```
OR
```
chmod +x ./build.sh
./build.sh
```
By doing so, a executable called `cmpe_322_project_1` would be created

## How to Run Program
### Running with no arguments
It will read the `definition.txt` and code files in the current directory.
Thus, change directory to where the test case files exist and then call the program from that directory.
```
cd "Provided Files"
../cmpe_322_project_1
```
(Moving the executable also works)
```
mv cmpe_322_project_1 "Provided Files/"
cd "Provided Files"
./cmpe_322_project_1
```
When called with no arguments, it creates an output file called `output.txt` in the current directory.

### Running with one argument
The program also supports running with one argument that specifies the output file.
That path argument is relative to the current directory.
```
cd "Provided Files"
./cmpe_322_project_1 custom_output.txt
```

For testing purposes, if that argument is `stdout` it prints its output to terminal instead of writing to a file.
```
cd "Provided Files"
./cmpe_322_project_1 stdout
```

Also, the program can be run using the run script, `run.sh` in which it outputs `custom_output.txt` to the main directory.
```
chmod +x ./run.sh
./run.sh
```

## Testing with Provided Files
The project includes a test script which moves the original `output.txt` to `original_output.txt` in the `Provided Files` folder, runs the program there creating new `output.txt`

Then it uses `diff output.txt original_output.txt` in that folder and reporting if there are any differences or not.

Then, if there're no differences it deletes the new `output.txt` and moves `original_output.txt` back into `output.txt`

If there are any differences, it outputs the differences and moves the `output.txt` into `test_output.txt` in the main directory for further analysis. Also, it moves `original_output.txt` back into `output.txt`

The test script can be run as follows:

```
chmod +x ./test.sh
./test.sh
``` 

## The Platform I used
I've developed the project using `CLion 2018.2.6` on `Ubuntu 16.04 LTS`

It's developed in `C++11` so it needs to compile using that version. 

(Such configuration are written in `CMakeLists.txt` and it is automatically compiled with that version when compiled with `cmake` tool) 

The program is designed to be mainly used in linux environment, but since it is built with cmake it can be compiled and run in Windows/MacOS environments, too.

Also, I've changed the default `CMakeLists.txt` to increase it's readability, and lowered its minimum version and added extra flags to support older versions of `Linux`, `cmake` and `make`

