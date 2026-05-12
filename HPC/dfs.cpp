#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS Utility
    void dfsUtil(int node, vector<bool>& visited) {

        visited[node] = true;

        cout << node << " ";

        for (int neighbor : adj[node]) {

            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    // Parallel DFS
    void parallelDFS(int start) {

        vector<bool> visited(V, false);

        cout << "Parallel DFS Traversal: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                dfsUtil(start, visited);
            }
        }

        cout << endl;
    }
};

int main() {

    Graph g(8);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 7);

    g.parallelDFS(0);

    return 0;
}
