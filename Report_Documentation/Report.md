# CMPE322-OS-Scheduler

### Simulating a Preemptive Priority Scheduling
### Created by Halit Özsoy - 2016400141

## The Platform I used
I've developed the project using `CLion 2018.2.6` on `Ubuntu 16.04 LTS`

It's developed in `C++11` so it needs to compile using that version. 

(Such configuration are written in `CMakeLists.txt` and it is automatically compiled with that version when compiled with `cmake` tool) 

The program is designed to be mainly used in linux environment, but since it is built with cmake it can be compiled and run in Windows/MacOS environments, too.

Also, I've changed the default `CMakeLists.txt` to increase it's readability, and lowered its minimum version and added extra flags to support older versions of `Linux`, `cmake` and `make`

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

## Documentation

Full documentation and more details can be found in README.md or Documentation.pdf 