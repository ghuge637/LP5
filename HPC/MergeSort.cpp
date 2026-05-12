// 1) g++ --version

// 2) sudo apt update
//   sudo apt install g++

// 3) g++ MergeSort.cpp -fopenmp -o graph

// 4) ./graph

// If You Get Error: “omp.h not found”

// 1) sudo apt install libomp-dev

// 2) Add this line inside main()
//    cout << "Threads: " << omp_get_max_threads() << endl;
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge Function
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    // Copy data
    for(int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }

    for(int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // Merge arrays
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    // Remaining elements
    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// ================= SEQUENTIAL MERGE SORT =================

void sequentialMergeSort(vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ================= PARALLEL MERGE SORT =================

void parallelMergeSort(vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

// Print Array
void printFirst20(vector<int>& arr)
{
    for(int i = 0; i < 20; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    vector<int> arr1;

    // Large dataset
    for(int i = 100 i >= 1; i--)
    {
        arr1.push_back(i);
    }

    vector<int> arr2 = arr1;

    double start, end;

    // ================= SEQUENTIAL =================

    start = omp_get_wtime();

    sequentialMergeSort(arr1, 0, arr1.size() - 1);

    end = omp_get_wtime();

    cout << "Sequential Merge Sort Completed\n";

    cout << "First 20 Elements:\n";

    printFirst20(arr1);

    cout << "Sequential Time: "
         << end - start
         << " seconds\n\n";

    // ================= PARALLEL =================

    start = omp_get_wtime();

    parallelMergeSort(arr2, 0, arr2.size() - 1);

    end = omp_get_wtime();

    cout << "Parallel Merge Sort Completed\n";

    cout << "First 20 Elements:\n";

    printFirst20(arr2);

    cout << "Parallel Time: "
         << end - start
         << " seconds\n";

    return 0;
}
