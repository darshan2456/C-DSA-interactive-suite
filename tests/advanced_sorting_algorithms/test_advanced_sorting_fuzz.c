#include "advanced_sorting.h"
#include "fuzzer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    fuzzer_init(&state, 42, 1000);

    int num_iterations = 100;
    int max_len = 200;

    for (int iter = 0; iter < num_iterations; iter++)
    {
        int n = fuzzer_rand_int(&state, 0, max_len);
        if (n <= 0)
        {
            continue;
        }

        int* original = (int*)malloc(n * sizeof(int));
        int* work = (int*)malloc(n * sizeof(int));
        assert(original != NULL && work != NULL);

        for (int i = 0; i < n; i++)
        {
            original[i] = fuzzer_rand_int(&state, 0, 10000);
        }

        // 1. Quick Sort
        for (int i = 0; i < n; i++)
        {
            work[i] = original[i];
        }
        quicksort(work, 0, n - 1);
        assert(is_sorted(work, n));

        // 2. Merge Sort
        for (int i = 0; i < n; i++)
        {
            work[i] = original[i];
        }
        merge_sort(work, n);
        assert(is_sorted(work, n));

        // 3. Heap Sort
        for (int i = 0; i < n; i++)
        {
            work[i] = original[i];
        }
        heap_sort(work, n);
        assert(is_sorted(work, n));

        // 4. Counting Sort
        for (int i = 0; i < n; i++)
        {
            work[i] = original[i];
        }
        counting_sort(work, n);
        assert(is_sorted(work, n));

        // 5. Bucket Sort
        for (int i = 0; i < n; i++)
        {
            work[i] = original[i];
        }
        bucket_sort(work, n);
        assert(is_sorted(work, n));

        // 6. Radix Sort
        for (int i = 0; i < n; i++)
        {
            work[i] = original[i];
        }
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
