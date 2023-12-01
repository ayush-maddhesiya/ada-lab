#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent a vertex in the graph
struct Vertex {
    int parent;
    int key;
    bool inMST;
};

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adjacencyMatrix; // Adjacency matrix to store edge weights

    // Constructor
    Graph(int vertices) : V(vertices), adjacencyMatrix(vertices, vector<int>(vertices, 0)) {}

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjacencyMatrix[src][dest] = weight;
        adjacencyMatrix[dest][src] = weight;
    }

    // Function to find the vertex with the minimum key value, from the set of vertices not yet included in the MST
    int minKey(const vector<Vertex>& vertices) {
        int minKey = INT_MAX, minIndex;

        for (int v = 0; v < V; v++) {
            if (!vertices[v].inMST && vertices[v].key < minKey) {
                minKey = vertices[v].key;
                minIndex = v;
            }
        }

        return minIndex;
    }

    // Function to print the minimum spanning tree
    void printMST(const vector<Vertex>& vertices) {
        cout << "Minimum Spanning Tree using Prim's Algorithm:" << endl;

        for (int i = 1; i < V; i++) {
            cout << vertices[i].parent << " - " << i << " (" << adjacencyMatrix[i][vertices[i].parent] << ")" << endl;
        }
    }

    // Function to apply Prim's algorithm to find the minimum spanning tree
    void prim() {
        vector<Vertex> vertices(V, { -1, INT_MAX, false });

        // Start with the first vertex
        vertices[0].key = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(vertices);
            vertices[u].inMST = true;

            for (int v = 0; v < V; v++) {
                if (adjacencyMatrix[u][v] && !vertices[v].inMST && adjacencyMatrix[u][v] < vertices[v].key) {
                    vertices[v].parent = u;
                    vertices[v].key = adjacencyMatrix[u][v];
                }
            }
        }

        // Print the minimum spanning tree
        printMST(vertices);
    }
};

int main() {
    // Create a graph with 5 vertices
    Graph graph(5);

    // Add edges to the graph
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    // Apply Prim's algorithm to find the minimum spanning tree
    graph.prim();

    return 0;
}
