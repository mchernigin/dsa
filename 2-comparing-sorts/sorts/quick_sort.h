#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "common.h"

void
quick_sort_internal(int * arr, int left_bound, int right_bound)
{
    if (left_bound >= right_bound)
        return;

    // Pick a pivot
    int pivot = arr[right_bound];

    // Partition based on pivot
    int left = left_bound;
    int right = right_bound;
    while (left < right) {
        while (arr[left] <= pivot && left < right)
            ++left;
        while (arr[right] >= pivot && left < right)
            --right;

        swap(&arr[left], &arr[right]);
    }
    swap(&arr[left], &arr[right_bound]);

    // Sort left and right halves
    quick_sort_internal(arr, left_bound, left - 1);
    quick_sort_internal(arr, right + 1, right_bound);
}

void
quick_sort(int * arr, int size)
{
    quick_sort_internal(arr, 0, size - 1);
}

#endif // QUICK_SORT_H
