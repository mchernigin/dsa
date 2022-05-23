#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "common.h"

void
merge(int * arr, int left_bound, int mid, int right_bound)
{
    // Create 2 arrays (left and right halves)
    int left_size = mid - left_bound + 1;
    int right_size = right_bound - mid;
    int left_half[left_size], right_half[right_size];
    for (int i = 0; i < left_size; ++i)
        left_half[i] = arr[left_bound + i];
    for (int j = 0; j < right_size; ++j)
        right_half[j] = arr[mid + 1 + j];

    // Merge two halves
    int i = 0, j = 0, k = left_bound;
    for (; i < left_size && j < right_size; ++k) {
        if (left_half[i] <= right_half[j]) {
            arr[k] = left_half[i];
            ++i;
        } else {
            arr[k] = right_half[j];
            ++j;
        }
    }

    while (i < left_size) {
        arr[k] = left_half[i];
        ++i;
        ++k;
    }

    while (j < right_size) {
        arr[k] = right_half[j];
        ++j;
        ++k;
    }
}

void
merge_sort_internal(int * arr, int left_bound, int right_bound)
{
    if (left_bound >= right_bound)
        return;

    int mid = left_bound + (right_bound - left_bound) / 2;
    merge_sort_internal(arr, left_bound, mid);
    merge_sort_internal(arr, mid + 1, right_bound);
    merge(arr, left_bound, mid, right_bound);
}

void
merge_sort(int * arr, int size)
{
    merge_sort_internal(arr, 0, size - 1);
}

#endif // MERGE_SORT_H
