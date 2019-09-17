#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <array>
#include "Graph.h"
Graph::Graph(const int& v) :
	m_NoOfNodes(v)
{
	m_AdjGraph = new double*[m_NoOfNodes];
	for (int i=0; i<m_NoOfNodes; i++) {
		m_AdjGraph[i] = new double[m_NoOfNodes];
	}	
}

Graph::~Graph()
{
	for (int i=0; i<m_NoOfNodes; i++) {
		delete[] m_AdjGraph[i];
	}
	delete[] m_AdjGraph;
}

void Graph::createAdjacencyMatrix(std::vector<std::array<int,2>> nodesVector)
{
	int xi, xj, yi, yj;
	for (int i=0; i<m_NoOfNodes; i++) {
		xi = nodesVector[i][0];
		yi = nodesVector[i][1];
		for(int j=0; j<m_NoOfNodes; j++) {
			xj = nodesVector[j][0];
			yj = nodesVector[j][1];
			m_AdjGraph[i][j] = sqrt(pow(xj-xi,2) + pow(yj-yi,2));
		}
	}
}

int Graph::getMinWeight(int weights[], bool visited[]) {
	int minWeight = 9999999;
	int minIndex = 0;
	for(int i=0; i < m_NoOfNodes; i++) {
		if(weights[i] < minWeight && !visited[i]) {
			minWeight = weights[i];
			minIndex = i;
		}
	}
	return minIndex;
}

std::vector<int> Graph::metricTSP(int startingNode,std::string file_name)
{
	// Following section implements Prim's algorithm to get MST
	//
	// Create an array for weights, parents, visited - initialize for v values
	int weights[m_NoOfNodes];
	int parents[m_NoOfNodes];
	bool visited[m_NoOfNodes]; // visited nodes for MST generation
	bool visitedDFS[m_NoOfNodes]; // visited nodes for DFS
	int startingIndex = startingNode - 1; // Because array index starts from 0
	// Initialize keys to maximum 
	for (int i=0; i < m_NoOfNodes; i++) {
		weights[i] = 999999;
		parents[i] = -1;
		visited[i] = false;
		visitedDFS[i] = false;
	}
	weights[startingIndex] = 0;
	/**
	*	Prim's algorithm
	*	1. start from the starting node
	*	2. update weights of all it's neighbours by dist betn them
	*		(if it is less than already existing weight)
	*	3. go to node with the shortest weight and repeat the process.
	*/
	int curr_node_index;
	for(int i=0; i < m_NoOfNodes; i++) {
		curr_node_index = getMinWeight(weights, visited);
		visited[curr_node_index] = true;
		for(int j=0; j < m_NoOfNodes; j++) {
			if(m_AdjGraph[curr_node_index][j] < weights[j] && !visited[j]){
				weights[j] = m_AdjGraph[curr_node_index][j];
				parents[j] = curr_node_index;
			}
		}
	}
	// Print parent index of each node
	//std::cout << "Parents " << std::endl;
	//for(int i=0; i < m_NoOfNodes; i++) {
	//	std::cout << i << ": " << parents[i] << std::endl;
	//}
	//std::cout << "end" << std::endl;
	/**
	* Note: Now parents array has parent of each node. Now using that I can
	* either create an adjacency list or a node class structure.
	*/
	/**
	*	create vector of vectors to represent MST
	*/
	std::vector<std::vector<int>> mstVector;
	for (int i=0; i < m_NoOfNodes; i++) {
		std::vector<int> children;
		for(int j=0; j < m_NoOfNodes; j++) {
			if(parents[j] == i)
				children.push_back(j);
		}
		mstVector.push_back(children);
	}
	// print MST cost
	int mstCost = 0;
	for(int i=0; i < mstVector.size(); i++) {
		for(int j=0; j<mstVector[i].size(); j++) {
			int child = mstVector[i][j];
			mstCost += m_AdjGraph[i][child];
		}
	}
	std::cout << "MST Cost: " << mstCost << std::endl;
	//
	// print each node with its children in MST 
	// Uncomment this to view the output
	/**
	for (int i=0; i<mstVector.size(); i++) {
		std::cout << i << ":";
		for(int j=0; j<mstVector[i].size(); j++)
			std::cout << mstVector[i][j] << " ";
		std::cout << std::endl;
	}
	**/
	// Create DFS search on mstVector
	std::vector<int> finalPath;
	std::stack<int> s;
	s.push(startingIndex);
	while(!s.empty()) {
		int curr_node = s.top();
		s.pop();
		visitedDFS[curr_node] = true;
 		for(int k=0; k<mstVector[curr_node].size(); k++) {
 			int c = mstVector[curr_node][k]; // get the child
 			if(!visitedDFS[c]) {
 				s.push(c);
 			} 
 		}
 		finalPath.push_back(curr_node); // +1 because index start from 0
	}
	finalPath.push_back(startingIndex); // Add first element in the end
	std::cout << std::endl;
	// Print final path
	std::cout << "Path without heuristics" << std::endl;
	for(int i=0; i<finalPath.size(); i++) {
		std::cout << finalPath[i]+1 << " ";
	}
	std::cout << std::endl;
	// Final path length
	double path_length = 0;
	for(int i=0; i<finalPath.size()-1; i++) {
		int first = finalPath[i];
		int second = finalPath[i+1];
		path_length += m_AdjGraph[first][second];
	}
	std::cout << "Path length Without Heuristics: " << path_length << std::endl;

	// print the final path to an output file
	std::ofstream outputFile;
	std::string outputName = file_name + ".out.tour";
	outputFile.open(outputName);
	outputFile << "Name: " << outputName << std::endl;
	outputFile << "COMMENT: Tour for " << outputName << std::endl;
	outputFile << "TYPE: TOUR" << std::endl;
	outputFile << "DIMENSION: " << m_NoOfNodes << std::endl;
	outputFile << "TOUR SECTION " << std::endl;
	for(int i=0; i<finalPath.size(); i++) {
		outputFile << finalPath[i] +1 << std::endl;
	}
	outputFile << -1 << std::endl;
	outputFile << "EOF" << std::endl;

	return finalPath;
}

void Graph::printAdjacencyMatrix()
{
	std::cout << "Printing matrix " << std::endl;
	for (int i=0; i<m_NoOfNodes; i++) {
		for(int j=0; j<m_NoOfNodes; j++) {
			std::cout << m_AdjGraph[i][j] << " "; 
		}
		std::cout << std::endl;
	}
}

int Graph::getNearestNeighbour(int curr_node, bool visited[]) {
	int minDist = 999999;
	int minIndex = -1;
	for(int i=0; i < m_NoOfNodes; i++) {
		if(m_AdjGraph[curr_node][i] < minDist && !visited[i]) {
			minDist = m_AdjGraph[curr_node][i];
			minIndex = i;
		}
	}
	return minIndex;
}

void Graph::nearestNeighbourHeuristics(int startingNode) {
	int startingIndex = startingNode - 1;
	bool visited[m_NoOfNodes];
	for (int i=0; i < m_NoOfNodes; i++) {
		visited[i] = false;
	}
	int noOfVisitedNodes = 1;
	std::vector<int> finalPath;
	// start from the starting index and loop until you visit all nodes
	int curr_node = startingIndex;
	visited[curr_node] = true;
	finalPath.push_back(curr_node);
	while(noOfVisitedNodes < m_NoOfNodes) {
		curr_node = getNearestNeighbour(curr_node, visited);
		if(curr_node != -1) {
			visited[curr_node] = true;
			finalPath.push_back(curr_node);
		}
		noOfVisitedNodes += 1;
	}
	std::cout << "Path with nearest neighbour approach" << std::endl;
	finalPath.push_back(startingIndex);
	// Print final path
	for(int i=0; i<finalPath.size(); i++) {
		std::cout << finalPath[i]+1 << " ";
	}
	std::cout << std::endl;
	// Final path length
	double path_length = 0;
	for(int i=0; i<finalPath.size()-1; i++) {
		int first = finalPath[i];
		int second = finalPath[i+1];
		path_length += m_AdjGraph[first][second];
	}
	std::cout << "Path length with nearest neighbour: " << path_length << std::endl;
}

// helper function to check the orientation of the three points
int getOrientation(std::array<int,2> p1, std::array<int,2> p2, std::array<int,2> p3){
	/**
	 * the orientation depends on sign of  below expression: 
	 * (y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1)
	 * It is nothing but the difference between the slopes
	 * 0 - colinear
	 * 1 - clockwise
	 * 2 - anticlockwise
	 */
	int slope_diff = ((p2[1] - p1[1]) * (p3[0] - p2[0])) - ((p2[0] - p1[0]) * (p3[1] - p2[1]));
	if(slope_diff == 0)
		return 0;
	else if(slope_diff > 0)
		return 1;
	else return 2;
}

// helper function to check if a point is on line segment
// check if point p is on line segment qr
bool onSegment(std::array<int, 2> p, std::array<int, 2> q, std::array<int, 2> r) {	
	if(p[0] <= std::max(q[0],r[0]) && p[0] >= std::min(q[0],r[0]) && p[1] <= std::max(q[1],r[1]) && p[1] >= std::min(q[1],r[1])) {
		return true;
	}
	else
		return false;
}

// check if given two line segments p1p2 and p3p4 are intersecting
bool intersectionExists(std::array<int, 2> p1, std::array<int, 2> q1, std::array<int, 2> p2, std::array<int, 2> q2) {
	int o1 = getOrientation(p1,q1,p2);
	int o2 = getOrientation(p1,q1,q2);
	int o3 = getOrientation(p2,q2,p1);
	int o4 = getOrientation(p2,q2,q1);

	if (o1 != o2 && o3 != o4)
		return true;
	// Check if three points are colinear and fourth one lies on the segment
	/**
	if(o1 == 0 && onSegment(p2,p1,q1)) return true;
	if(o2 == 0 && onSegment(q2,p1,q1)) return true;
	if(o3 == 0 && onSegment(p1,p2,q2)) return true;
	if(o4 == 0 && onSegment(q1,p2,q2)) return true;
	**/
	return false;
}

double Graph::getPathLength(std::vector<int> finalPath) {
	double path_length = 0;
	for(int i=0; i<finalPath.size()-1; i++) {
		int first = finalPath[i];
		int second = finalPath[i+1];
		path_length += m_AdjGraph[first][second];
	}
	return path_length;
}


void Graph::intersectionHeuristics(std::vector<int> finalPath, std::vector<std::array<int,2>> nodesCoordinates) {
	int count = -1;
	while(count != 0) {
		count = 0;
		for(int i=1; i < finalPath.size() - 3; i++) {
			// get the indices of the vertices from final finalPath.
			for(int j=i+2; j < finalPath.size() - 2; j++) {
				bool intersect = false;
				int i1 = finalPath[i];
				int i2 = finalPath[i+1];
				int i3 = finalPath[j];
				int i4 = finalPath[j+1];
				// get the coordinates of the corresponding indices
				std::array<int,2> P1 = nodesCoordinates[i1];
				std::array<int,2> P2 = nodesCoordinates[i2];
				std::array<int,2> P3 = nodesCoordinates[i3];
				std::array<int,2> P4 = nodesCoordinates[i4];
				intersect = intersectionExists(P1,P2,P3,P4);
				//std::cout << i1 << " " << i2 << " " << i3 << " " << i4 << std::endl;
				if(intersect) {
					// if two points intersect then swap their endpoints
					// to maintain path connectivity connect first point from first segment
					// with first point of second segment.
					// then reverse entire path between these.
					int s = i+1;
					int k = j;
					int temp;
					while(s < k) {
						temp = finalPath[s];
						finalPath[s] = finalPath[k];
						finalPath[k] = temp;
						s += 1;
						k-= 1;
					}
					count += 1;
				}
			}
		}
	}
	double path_length = getPathLength(finalPath);
	std::cout << "P:" << path_length << count;
}