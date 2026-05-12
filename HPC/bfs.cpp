// 1) g++ --version

// 2) sudo apt update
//   sudo apt install g++

// 3) g++ bfs.cpp -fopenmp -o graph

// 4) ./graph

// If You Get Error: “omp.h not found”

// 1) sudo apt install libomp-dev

// 2) Add this line inside main()
//    cout << "Threads: " << omp_get_max_threads() << endl;

#include <iostream>
#include <vector>
#include <queue>
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

    // Parallel BFS
    void parallelBFS(int start) {

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS Traversal: ";

        while (!q.empty()) {

            int current = q.front();
            q.pop();

            cout << current << " ";

            // Parallel traversal of neighbors
            #pragma omp parallel for
            for (int i = 0; i < adj[current].size(); i++) {

                int neighbor = adj[current][i];

                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
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

    g.parallelBFS(0);

    return 0;
}
