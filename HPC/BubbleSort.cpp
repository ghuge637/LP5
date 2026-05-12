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
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort using Odd-Even Transposition
void parallelBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n; i++)
    {
        // Even Phase
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j += 2)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd Phase
        #pragma omp parallel for
        for(int j = 1; j < n - 1; j += 2)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Print Array
void printArray(vector<int>& arr)
{
    for(int num : arr)
    {
        cout << num << " ";
    }

    cout << endl;
}

int main()
{
    vector<int> arr1;
    
    // Large dataset for proper performance comparison
    for(int i = 10000; i >= 1; i--)
    {
        arr1.push_back(i);
    }

    vector<int> arr2 = arr1;

    double start, end;

    // ================= SEQUENTIAL =================

    start = omp_get_wtime();

    sequentialBubbleSort(arr1);

    end = omp_get_wtime();

    cout << "Sequential Bubble Sort Completed\n";

    cout << "First 20 Elements:\n";

    for(int i = 0; i < 20; i++)
    {
        cout << arr1[i] << " ";
    }

    cout << "\n";

    cout << "Sequential Time: "
         << end - start
         << " seconds\n\n";

    // ================= PARALLEL =================

    start = omp_get_wtime();

    parallelBubbleSort(arr2);

    end = omp_get_wtime();

    cout << "Parallel Bubble Sort Completed\n";

    cout << "First 20 Elements:\n";

    for(int i = 0; i < 20; i++)
    {
        cout << arr2[i] << " ";
    }

    cout << "\n";

    cout << "Parallel Time: "
         << end - start
         << " seconds\n";

    return 0;
}
