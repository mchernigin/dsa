#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "sorts/quick_sort.h"
#include "sorts/merge_sort.h"
#include "sorts/heap_sort.h"

#define TIMES 5

#define N_SIZES 4
int arr_sizes[] = { 50000, 100000, 500000, 1000000 };

#define ARR_SIZE 1000000
int arr[ARR_SIZE];

double results[N_SIZES][TIMES];

void generate_arr();
void print_arr();
double average(double * arr, int size);
void create_csv_header();
void save_results(char * sort_name);
void benchmark_sort();
bool is_sorted();

int
main(void)
{
    create_csv_header();

    // Benchmark all sorts
    benchmark_sort("Quick Sort", quick_sort);
    benchmark_sort("Merge Sort", merge_sort);
    benchmark_sort("Heap Sort", heap_sort);

    return (EXIT_SUCCESS);
}


void
generate_arr(int size)
{
    for (int i = 0; i < size; ++i)
        arr[i] = rand();
}

void
print_arr(int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void
benchmark_sort(char * sort_name, void sort())
{
    for (int i = 0; i < N_SIZES; ++i) {
        for (int experiment = 0; experiment < TIMES; ++experiment) {
            int size = arr_sizes[i];
            generate_arr(size);

            clock_t begin = clock();
            sort(arr, size);
            clock_t end = clock();

            double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
            results[i][experiment] = time_spent;

            if (!is_sorted(arr_sizes[i])) {
                printf("🚫 %s failed: array was not sorted\n", sort_name);
                exit (EXIT_FAILURE);
            }
        }
    }

    save_results(sort_name);
}

void
create_csv_header()
{
    FILE * out_file = fopen("results.csv", "w");

    fprintf(out_file, "Sort Name");
    for (int i = 0; i < N_SIZES; ++i)
        fprintf(out_file, ",%d", arr_sizes[i]);
    fprintf(out_file, "\n");

    fclose(out_file);
}

void
save_results(char * sort_name)
{
    FILE * out_file = fopen("results.csv", "a");

    fprintf(out_file, "%s", sort_name);
    for (int i = 0; i < N_SIZES; ++i)
        fprintf(out_file, ",%f", average(results[i], TIMES));
    fprintf(out_file, "\n");

    fclose(out_file);
}

double
average(double * arr, int size)
{
    double sum = 0;
    for (int i = 0; i < size; ++i)
        sum += arr[i];

    return (sum / size);
}

bool
is_sorted(int size)
{
    for (int i = 0; i < size - 1; ++i)
        if (arr[i] > arr[i + 1])
            return (false);
    return (true);
}
