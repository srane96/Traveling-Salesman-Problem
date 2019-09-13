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
		 * @ brief helper function to get the index of node with minimum weight
		 * @ param weights - array of weights
		 * @ return index of the node
		 */
		int getMinWeight(int weights[], bool visited[]);
		/*!
		 * @ brief Calculates the tour length for MTSP
		 * @ param Index of starting node. Starting from 1
		 */
		void metricTSP(int startingNode);
		/*!
		 * @ brief Print adjacency matrix
		 */
		void printAdjacencyMatrix();
		/*!
		 * @ brief 
		 */
};
#endif // GRAPH_DEFINED