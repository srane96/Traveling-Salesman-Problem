# Traveling-Salesman-Problem
This C++ code solves a metric TSP using MST.

## Directory structure
* Input files are in the /input directory
* Output tours are generated inside the /outputTours directory
* Randomly generated .tsp files are inside /RandomInstances directory
* C++ header files are inside /include directory
* C++ source files are inside /src directory

## Make sure you have cmake installed in your system.

## Program running instructions
* to create the executable, run the following commands : </br>
	`mkdir build` </br>
	`cd build/` </br>
	`cmake ..` </br>
	`make` </br>

* now to run the program, use the following command inside the build directory: </br>
	'./src/tsp /full path to the tsp file/'
* for example, to run eil51.tsp this command used.(Make sure you add full
directory path to the .tsp file) </br>
	`./src/tsp ~/Desktop/Traveling-Salesman-Problem/input/eil101.tsp`
* corresponding tour is generated inside /outputTours directory
