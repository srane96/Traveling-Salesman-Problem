#include <iostream>
#include <cmath>
#include <vector>
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

void Graph::metricTSP(int startingNode)
{
	// Following section implements Prim's algorithm to get MST
	//
	// Create an array for weights, parents, visited - initialize for v values
	int weights[m_NoOfNodes];
	int parents[m_NoOfNodes];
	bool visited[m_NoOfNodes];
	int startingIndex = startingNode - 1; // Because array index starts from 0
	// Initialize keys to maximum 
	for (int i=0; i < m_NoOfNodes; i++) {
		weights[i] = 999999;
		parents[i] = -1;
		visited[i] = false;
	}
	weights[startingIndex] = 0;
	/**
	*	Prim's algorithm
	*	1. start from the starting node
	*	2. update weights of all it's neighbours by dist betn them
	*		(if it is less than already existing weight)
	*	3. go to node with the shortest weight and repeat the process.
	*
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
	std::cout << "Parents " << std::endl;
	for(int i=0; i < m_NoOfNodes; i++) {
		std::cout << i << ": " << parents[i] << std::endl;
	}
	std::cout << "end" << std::endl;
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
	// print each node with its children in MST
	std::cout << "Using vector" << std::endl;
	for (int i=0; i<mstVector.size(); i++) {
		std::cout << i << ":";
		for(int j=0; j<mstVector[i].size(); j++)
			std::cout << mstVector[i][j] << " ";
		std::cout << std::endl;
	}
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