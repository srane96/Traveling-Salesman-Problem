#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <fstream>
#include <vector>
#include "Graph.h"
using namespace std;
int main(int argc, char** argv) {
	// this vector stores coordinates of all nodes read fromt the file
	/** 
	  * Note to self: in C++ arrays cannot be stored inside a vector. It is because
	  * arrays cannot be copy constructed  or assigned.
	  * work around this problem is that C++ introduced std::array which is 
	  * just a container that encapsulates fixed size arrays.
	**/
	vector<array<int,2>> nodesVector;
	string file_name;
	if (argc != 2) {
		cout << "No argument provided." << endl;
		return -1;
	}
	else {
		string line;
		ifstream myfile(argv[1]);
		if(!myfile) {
			cout << "Cannot open the file." << endl;
			return -1;
		}
		// creating this to avoid first 6 lines that only contain strings
		int line_count = 0;
		int a, b, c;
		string temp, inp;
		while(getline(myfile,line)) {
			if (line_count < 6) {
				istringstream iss(line);
				iss >> temp >> temp >> inp;
				// get the file name
				if (line_count == 0) {
					file_name = inp;
				}
				line_count +=1;
				continue;
			}
			istringstream iss(line);
			iss >> a >> b >> c;
			// cout << a << " " << b << " " << c << endl;
			// if a is zero then it means it is the last line. It is a duplicate.
			if(a!=0) {
				array<int, 2> nodeArray = {b,c};
				nodesVector.push_back(nodeArray);
			}
			line_count += 1;
		}
		myfile.close(); 
	}
	// create an adjancy graph using this vector of arrays
	if(nodesVector.size() > 0) {
		int test = 2;
		Graph graph(nodesVector.size());
		graph.createAdjacencyMatrix(nodesVector);
		//graph.printAdjacencyMatrix();
		std::vector<int> finalPath;
		finalPath = graph.metricTSP(1,file_name);
		graph.nearestNeighbourHeuristics(1);
		graph.intersectionHeuristics(finalPath, nodesVector);
		// Uncomment following line to create a random instance in given folder
		//graph.createRandom("300");
	}
	return 0;
}