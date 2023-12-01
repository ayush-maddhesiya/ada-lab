#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

// Structure to represent a vertex in the graph
struct Vertex {
    int index;
    int distance;

    // Comparison function to sort vertices based on their distances
    bool operator<(const Vertex& other) const {
        return distance < other.distance;
    }
};

class Graph {
public:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adjacencyList; // Adjacency list to store weighted edges

    // Constructor
    Graph(int vertices) : V(vertices), adjacencyList(vertices) {}

    // Function to add a weighted edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjacencyList[src].push_back({dest, weight});
        adjacencyList[dest].push_back({src, weight});
    }

    // Function to find the single-source shortest paths using Dijkstra's algorithm
    void dijkstra(int source) {
        // Initialize distances to infinity
        vector<int> distances(V, INT_MAX);
        distances[source] = 0;

        // Create a set to store vertices and their distances
        set<Vertex> vertexSet;
        for (int i = 0; i < V; i++)
            vertexSet.insert({i, distances[i]});

        while (!vertexSet.empty()) {
            // Extract the vertex with the minimum distance
            Vertex currentVertex = *vertexSet.begin();
            vertexSet.erase(vertexSet.begin());

            // Update distances of adjacent vertices
            for (const auto& neighbor : adjacencyList[currentVertex.index]) {
                int destination = neighbor.first;
                int weight = neighbor.second;

                if (distances[currentVertex.index] != INT_MAX &&
                    distances[currentVertex.index] + weight < distances[destination]) {
                    // Update the distance in the set and distances array
                    vertexSet.erase({destination, distances[destination]});
                    distances[destination] = distances[currentVertex.index] + weight;
                    vertexSet.insert({destination, distances[destination]});
                }
            }
        }

        // Print the distances from the source
        cout << "Shortest Distances from Source (" << source << "):" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            if (distances[i] == INT_MAX)
                cout << "Infinity" << endl;
            else
                cout << distances[i] << endl;
        }
    }
};

int main() {
    // Create a graph with 6 vertices
    Graph graph(6);

    // Add weighted edges to the graph
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 5);
    graph.addEdge(4, 5, 2);

    // Apply Dijkstra's algorithm to find the single-source shortest paths
    graph.dijkstra(0);

    return 0;
}
