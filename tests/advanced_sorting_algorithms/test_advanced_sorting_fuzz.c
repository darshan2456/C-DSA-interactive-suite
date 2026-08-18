#include "advanced_sorting.h"
#include "fuzzer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_sorted(const int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

void test_advanced_sorting_fuzz(void)
{
    FuzzerState state;
    fuzzer_init(&state, 1337, 1000);

    int num_iterations = 50;
    int max_len = 100;

    for (int iter = 0; iter < num_iterations; iter++)
    {
        int n = fuzzer_rand_int(&state, 5, max_len);

        int* original = (int*)malloc(n * sizeof(int));
        int* work = (int*)malloc(n * sizeof(int));
        assert(original && work);

        int min_val = fuzzer_rand_int(&state, 0, 499);
        int max_val = fuzzer_rand_int(&state, 500, 1000);
        for (int i = 0; i < n; i++)
        {
            original[i] = fuzzer_rand_int(&state, min_val, max_val);
        }

        // 1. Quicksort
        memcpy(work, original, n * sizeof(int));
        quicksort(work, 0, n - 1);
        assert(is_sorted(work, n));

        // 2. Merge Sort
        memcpy(work, original, n * sizeof(int));
        merge_sort(work, n);
        assert(is_sorted(work, n));

        // 3. Heap Sort
        memcpy(work, original, n * sizeof(int));
        heap_sort(work, n);
        assert(is_sorted(work, n));

        // 4. Counting Sort
        memcpy(work, original, n * sizeof(int));
        counting_sort(work, n);
        assert(is_sorted(work, n));

        // 5. Bucket Sort
        memcpy(work, original, n * sizeof(int));
        bucket_sort(work, n);
        assert(is_sorted(work, n));

        // 6. Radix Sort
        memcpy(work, original, n * sizeof(int));
        radix_sort(work, n);
        assert(is_sorted(work, n));

        free(original);
        free(work);
    }
    fuzzer_free(&state);
    printf("Advanced sorting fuzz tests passed successfully!\n");
}

int main(void)
{
    test_advanced_sorting_fuzz();
    return 0;
}
