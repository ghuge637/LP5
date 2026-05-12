// 1) g++ --version

// 2) sudo apt update
//   sudo apt install g++

// 3) g++ dfs.cpp -fopenmp -o graph

// 4) ./graph

// If You Get Error: “omp.h not found”

// 1) sudo apt install libomp-dev

// 2) Add this line inside main()
//    cout << "Threads: " << omp_get_max_threads() << endl;

#include <iostream>
#include <omp.h>

using namespace std;

// Tree Node
class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

// Parallel DFS
void parallelDFS(Node* root)
{
    if(root == NULL)
    {
        return;
    }

    #pragma omp critical
    {
        cout << root->data << " ";
    }

    #pragma omp parallel sections
    {
        // Left Subtree
        #pragma omp section
        {
            parallelDFS(root->left);
        }

        // Right Subtree
        #pragma omp section
        {
            parallelDFS(root->right);
        }
    }
}

int main()
{
    // Creating Tree

    Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Parallel DFS Traversal:\n";

    parallelDFS(root);

    return 0;
}
