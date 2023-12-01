#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;

    // Comparison function to sort edges based on their weights
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
public:
    int V; // Number of vertices
    vector<Edge> edges; // Vector to store edges of the graph

    // Constructor
    Graph(int vertices) : V(vertices) {}

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    // Function to find the parent of a set
    int find(int parent[], int i) {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    // Function to perform union of two sets
    void unionSets(int parent[], int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);
        parent[xroot] = yroot;
    }

    // Function to apply Kruskal's algorithm to find the minimum spanning tree
    void kruskal() {
        // Sort edges in non-decreasing order of their weights
        sort(edges.begin(), edges.end());

        // Allocate memory for parent array (to track disjoint sets)
        int* parent = new int[V];
        fill(parent, parent + V, -1);

        cout << "Minimum Spanning Tree using Kruskal's Algorithm:" << endl;

        // Iterate through all sorted edges
        for (const Edge& edge : edges) {
            int x = find(parent, edge.src);
            int y = find(parent, edge.dest);

            // Check if including this edge does not form a cycle
            if (x != y) {
                cout << edge.src << " - " << edge.dest << " (" << edge.weight << ")" << endl;
                unionSets(parent, x, y);
            }
        }

        // Deallocate memory
        delete[] parent;
    }
};

int main() {
    // Create a graph with 4 vertices
    Graph graph(4);

    // Add edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    // Apply Kruskal's algorithm to find the minimum spanning tree
    graph.kruskal();

    return 0;
}
