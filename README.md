# TALC, Teacher's Assistant's Lateness Calculator

## Overview
A tool to aid TAs of the UVM CS department with grading.

## Features 
- Finds potentially modified commits
- Marks repositories with commits past a certain date
- (Coming soon!) Find profanity in commit messages

## Building
### Unix
```
mkdir -p build 
cd build/
cmake ..
make
```
### Windows

#### MinGW Build (GCC)
- The `-G` flag tells cmake which build files we want to create. In this case, we want build files for MinGW. The 
  `make` command may be defined to use MSVC if you have Visual Studio installed, so we use the `mingw32-make` command. 
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
./graphics
```
#### MSVC Build (Visual Studio)
```
mkdir build
cd build
cmake ..
cmake --build .
./graphics
```