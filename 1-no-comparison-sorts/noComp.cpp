#include <iostream>
#include <vector>

void
countingSort(int * arr, int n)
{
    // Find max element in arr
    int max = 0;
    for (int i = 0; i < n; ++i)
        if (arr[i] > max)
            max = arr[i];

    // Count all elements in arr
    int * count = new int[max + 1];
    for (int i = 0; i < n; ++i)
        ++count[arr[i]];

    // Fill arr with elements in sorted order
    int b = 0;
    for (int i = 0; i < max + 1; ++i)
        for (int j = 0; j < count[i]; ++j)
            arr[b++] = i;

    delete [] count;
}

void
lsdSort(int * arr, int n)
{
    std::vector<std::vector<int>> numbers(10);
    bool shouldStop = false;
    int tmp = -1, divisor = 1;

    while (!shouldStop) {
        shouldStop = true;
        for (int i = 0; i < n; ++i) {
            tmp = arr[i] / divisor;
            numbers[tmp % 10].push_back(arr[i]);
            if (shouldStop && tmp > 0)
                shouldStop = false;
        }
        int a = 0;
        for (int b = 0; b < 10; b++) {
            for (auto i : numbers[b])
                arr[a++] = i;
            numbers[b].clear();
        }
        divisor *= 10;
    }
}

int
main(void)
{
    // Get array from user input
    int n;
    std::cin >> n;
    int * arr = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    // Sort an array using counting sort
    countingSort(arr, n);

    // Sort an array using Radix LSD sort
    // lsdSort(arr, n); 

    // Output sorted array
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';

    delete [] arr;
    return 0;
}
