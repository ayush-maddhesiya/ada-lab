#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adjacencyMatrix; // Adjacency matrix to store edge weights

    // Constructor
    Graph(int vertices) : V(vertices), adjacencyMatrix(vertices, vector<int>(vertices, INT_MAX)) {}

    // Function to add a weighted edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjacencyMatrix[src][dest] = weight;
    }

    // Function to apply Floyd-Warshall algorithm to find all pairs shortest paths
    void floydWarshall() {
        // Initialize the distance matrix with the adjacency matrix
        vector<vector<int>> distanceMatrix = adjacencyMatrix;

        // Update the distance matrix by considering all vertices as intermediate vertices
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    // If vertex k is on the shortest path from i to j, update the distance
                    if (distanceMatrix[i][k] != INT_MAX && distanceMatrix[k][j] != INT_MAX &&
                        distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]) {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    }
                }
            }
        }

        // Print the result
        cout << "Shortest Distances (All Pairs) using Floyd-Warshall Algorithm:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (distanceMatrix[i][j] == INT_MAX)
                    cout << "INF ";
                else
                    cout << distanceMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create a graph with 4 vertices
    Graph graph(4);

    // Add weighted edges to the graph
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 3, 10);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 1);

    // Apply Floyd-Warshall algorithm to find all pairs shortest paths
    graph.floydWarshall();

    return 0;
}
