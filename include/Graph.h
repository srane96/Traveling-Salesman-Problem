#ifndef GRAPH_DEFINED
#define GRAPH_DEFINED
#include <array>
#include <vector>
class Graph {
	private:
		int m_NoOfNodes = 0;
		// Note to self: ** is a pointer to the int pointer. It is often used
		// to create a dynamic 2d array.
		int **m_AdjGraph;
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
		 * @ brief Print adjacency matrix
		 */
		void printAdjacencyMatrix();
};
#endif // GRAPH_DEFINED