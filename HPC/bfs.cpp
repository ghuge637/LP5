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
#include <queue>
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

// Parallel BFS
void parallelBFS(Node* root)
{
    if(root == NULL)
    {
        return;
    }

    queue<Node*> q;
    q.push(root);

    cout << "Parallel BFS Traversal:\n";

    while(!q.empty())
    {
        Node* current = q.front();
        q.pop();

        // Thread-safe print
        #pragma omp critical
        {
            cout << current->data << " ";
        }

        // Parallel sections for left and right child
        #pragma omp parallel sections
        {
            // Left Child
            #pragma omp section
            {
                if(current->left != NULL)
                {
                    #pragma omp critical
                    {
                        q.push(current->left);
                    }
                }
            }

            // Right Child
            #pragma omp section
            {
                if(current->right != NULL)
                {
                    #pragma omp critical
                    {
                        q.push(current->right);
                    }
                }
            }
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

    parallelBFS(root);

    return 0;
}
