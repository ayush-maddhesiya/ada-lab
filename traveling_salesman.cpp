#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class TSP {
public:
    int V; // Number of vertices (cities)
    vector<vector<int>> graph; // Adjacency matrix to store distances between cities

    TSP(int vertices) : V(vertices), graph(vertices, vector<int>(vertices, INF)) {}

    // Function to add an edge between two cities with a given distance
    void addEdge(int src, int dest, int distance) {
        graph[src][dest] = distance;
        graph[dest][src] = distance;
    }

    // Function to calculate the total cost of a given tour
    int calculateTourCost(const vector<int>& tour) {
        int cost = 0;
        for (int i = 0; i < V - 1; ++i) {
            cost += graph[tour[i]][tour[i + 1]];
        }
        cost += graph[tour[V - 1]][tour[0]]; // Return to the starting city
        return cost;
    }

    // Function to find the minimum cost using brute-force
    void solveTSPBruteForce() {
        vector<int> tour(V);
        for (int i = 0; i < V; ++i) {
            tour[i] = i;
        }

        int minCost = INF;
        vector<int> minTour;

        // Generate all possible permutations of the tour
        do {
            int currentCost = calculateTourCost(tour);

            // Update the minimum cost and tour if a better solution is found
            if (currentCost < minCost) {
                minCost = currentCost;
                minTour = tour;
            }

        } while (next_permutation(tour.begin() + 1, tour.end()));

        // Print the result
        cout << "Optimal Tour: ";
        for (int city : minTour) {
            cout << city << " ";
        }
        cout << minTour[0] << endl;
        cout << "Total Cost: " << minCost << endl;
    }
};

int main() {
    // Create a TSP instance with 4 cities
    TSP tsp(4);

    // Add edges between cities with their respective distances
    tsp.addEdge(0, 1, 10);
    tsp.addEdge(0, 2, 15);
    tsp.addEdge(0, 3, 20);
    tsp.addEdge(1, 2, 35);
    tsp.addEdge(1, 3, 25);
    tsp.addEdge(2, 3, 30);

    // Solve the TSP using brute-force
    tsp.solveTSPBruteForce();

    return 0;
}
