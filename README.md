# CMPE322-OS-Scheduler

### Simulating a Preemptive Priority Scheduling

##Project Details

That's a project I've created at university homework for the course, 
CMPE 322 - Operating Systems on Nov 25th, 2018

What the project is about can be found via [Project1.pdf](./Project1.pdf)

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

 
    
  

