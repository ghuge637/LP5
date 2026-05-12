#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
    vector<int> arr;

    // Large dataset
    for(int i = 1; i <= 1000000; i++)
    {
        arr.push_back(i);
    }

    int minValue = arr[0];
    int maxValue = arr[0];

    long long sum = 0;

    double average;

    double start, end;

    start = omp_get_wtime();

    // Parallel Reduction for Sum
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    // Parallel Reduction for Minimum
    #pragma omp parallel for reduction(min:minValue)
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] < minValue)
        {
            minValue = arr[i];
        }
    }

    // Parallel Reduction for Maximum
    #pragma omp parallel for reduction(max:maxValue)
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    // Average
    average = (double)sum / arr.size();

    end = omp_get_wtime();

    // Display Results

    cout << "Minimum Value: "
         << minValue << endl;

    cout << "Maximum Value: "
         << maxValue << endl;

    cout << "Sum: "
         << sum << endl;

    cout << "Average: "
         << average << endl;

    cout << "Execution Time: "
         << end - start
         << " seconds" << endl;

    return 0;
}
