#ifndef GRAPH_DEFINED
#define GRAPH_DEFINED
#include <array>
#include <vector>
class Graph {
	private:
		int m_NoOfNodes = 0;
		// Note to self: ** is a pointer to the int pointer. It is often used
		// to create a dynamic 2d array.
		double **m_AdjGraph;
	public:
		/*!
		 * @ brief Graph Constructor
		 * @ param v - Number of nodes in the graph 
		 */	
		Graph(const int& v);
		/*!
		 * @ brief A default destructor
		 */
		~Graph();
		/*!
		 * @ brief Create an adjacency matrix using vector of nodes
		 * @ param nodesVector - vector of arrays, where each array is a 2D coordinate
		 */
		void createAdjacencyMatrix(std::vector<std::array<int,2>> nodesVector);
		/*!
		 * @ brief Helper function to get the index of node with minimum weight
		 * @ param weights - array of weights
		 * @ return index of the node
		 */
		int getMinWeight(int weights[], bool visited[]);
		/*!
		 * @ brief helper function to print the total cost of the path provided
		 * @ param finalPath - vector with indices of the path nodes in order
		 * @ return total edge cost of the path
		 */
		double getPathLength(std::vector<int> finalPath);
		/*!
		 * @ brief Calculates the tour length for MTSP and prints the log to an output file
		 * @ param Index of starting node. Starting from 1
		 */
		std::vector<int> metricTSP(int startingNode, std::string file_name);
		/*!
		 * @ brief Print adjacency matrix
		 */
		void printAdjacencyMatrix();
		/*!
		 * @ brief Helper function that returns nearest unvisited neighbour
		 * 		   of the current node
		 * @ param curr_node - current node
		 *		   visited - array of visited nodes
		 * @ return index of the nearest unvisited neighbour 
		 */
		int getNearestNeighbour(int curr_node, bool visited[]);
		/*!
		 * @ brief Implements the nearest neighbour heuristics
		 * @ param Index of the starting node. Starting from 1 
		 */
		void nearestNeighbourHeuristics(int startingNode);
		/*!
		 * @ brief this function applies intersection heuristics repeatedly on the computed TSP tour.
		 *	       it performs the loop which stops only after all the intersections have been removed.
		 */
		void intersectionHeuristics(std::vector<int> finalPath, std::vector<std::array<int,2>> nodesCoordinates);
		void createRandom(std::string folder);
};
#endif // GRAPH_DEFINED