#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <fstream>
#include <vector>
using namespace std;
int main(int argc, char** argv) {
	cout << "Hello TSP" << endl;
	if (argc != 2)
		cout << "No argument provided." << endl;
	else {
		string line;
		ifstream myfile(argv[1]);
		if(!myfile) {
			cout << "Cannot open the file." << endl;
			return -1;
		}
		// creating this to avoid first 6 lines that only contain string
		int line_count = 0;
		int a, b, c;
		// this vector stores coordinates of all nodes read fromt the file
		/** 
		  * Note to self: in C++ arrays cannot be stored inside a vector. It is because
		  * arrays cannot be copy constructed  or assigned.
		  * work around this problem is that C++ introduced std::array which is 
		  * just a container that encapsulates fixed size arrays.
		**/
		vector<array<int,2>> nodesVector;
		while(getline(myfile,line)) {
			if (line_count < 6) {
				line_count +=1;
				continue;
			}
			istringstream iss(line);
			iss >> a >> b >> c;
			// cout << a << " " << b << " " << c << endl;
			// if a is zero then it means it is the last line. It is a duplicate. I have
			// no idea why it is printing the last element twice. 
			if(a!=0) {
				array<int, 2> nodeArray = {b,c};
				nodesVector.push_back(nodeArray);
			}
			line_count += 1;
		}
		myfile.close(); 
		cout << "Total " << nodesVector.size() << " nodes read from tsp file " << endl;
	}
	return 0;
}