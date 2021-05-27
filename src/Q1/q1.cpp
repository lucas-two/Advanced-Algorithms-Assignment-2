/* Q1. Number list, with k-smallest list */
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const int N = 10;           // Number of elements
    const int K = 3;            // K number of smallest elements to track
    const int upperLimit = 100; // Random number generation limit
    vector<int> numbers;        // List storing N random integers
    srand(0);                   // Random number generation seed

    // Insert random numbers into our list
    for (int i = 0; i < N; i++)
    {
        int number = rand() % upperLimit;
        numbers.push_back(i);
    }

    return 0;
}