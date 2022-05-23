#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "common.h"

void
heapify(int * arr, int size, int i)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[max])
        max = left;
    if (right < size && arr[right] > arr[max])
        max = right;

    if (max != i) {
        swap(&arr[i], &arr[max]);
        heapify(arr, size, max);
    }
}

void
heap_sort(int * arr, int size)
{
    // Build max-heap
    for (int i = size / 2 - 1; i >= 0; --i)
      heapify(arr, size, i);

    // Sort by extracting max elements from heap
    for (int i = size - 1; i >= 0; --i) {
      swap(&arr[0], &arr[i]);
      heapify(arr, i, 0);
    }
}

#endif // HEAP_SORT_H
