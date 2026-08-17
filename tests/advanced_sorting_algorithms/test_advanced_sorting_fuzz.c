#include "advanced_sorting.h"
#include "fuzzer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int is_sorted(const int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

static void test_fuzz_advanced_sorting(unsigned int seed, int num_runs)
{
    FuzzerState fuzzer;
    fuzzer_init(&fuzzer, seed, num_runs * 10);

    for (int run = 0; run < num_runs; run++)
    {
        int n;
        if (run == 0)
        {
            n = 0;
        }
        else if (run == 1)
        {
            n = 1;
        }
        else
        {
            n = fuzzer_rand_int(&fuzzer, 2, 500);
        }

        int min_val, max_val;
        int mode = fuzzer_rand_int(&fuzzer, 0, 3);
        if (mode == 0)
        {
            min_val = -10;
            max_val = 10;
        }
        else if (mode == 1)
        {
            min_val = -5000;
            max_val = 5000;
        }
        else if (mode == 2)
        {
            min_val = 0;
            max_val = 100000;
        }
        else
        {
            min_val = -1000;
            max_val = 1000;
        }

        int* orig = (int*)malloc(sizeof(int) * (n > 0 ? n : 1));
        assert(orig != NULL);

        if (mode == 3 && n > 1)
        {
            for (int i = 0; i < n; i++)
            {
                orig[i] = n - i;
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                orig[i] = fuzzer_rand_int(&fuzzer, min_val, max_val);
            }
        }

        int* work = (int*)malloc(sizeof(int) * (n > 0 ? n : 1));
        assert(work != NULL);

        // 1. Quicksort
        if (n > 0)
        {
            memcpy(work, orig, sizeof(int) * n);
        }
        quicksort(work, 0, n - 1);
        assert(is_sorted(work, n));

        // 2. Merge Sort
        if (n > 0)
        {
            memcpy(work, orig, sizeof(int) * n);
        }
        merge_sort(work, n);
        assert(is_sorted(work, n));

        // 3. Heap Sort
        if (n > 0)
        {
            memcpy(work, orig, sizeof(int) * n);
        }
        heap_sort(work, n);
        assert(is_sorted(work, n));

        // 4. Bucket Sort
        if (n > 0)
        {
            memcpy(work, orig, sizeof(int) * n);
        }
        bucket_sort(work, n);
        assert(is_sorted(work, n));

        // 5. Counting Sort
        if (n > 0)
        {
            memcpy(work, orig, sizeof(int) * n);
        }
        counting_sort(work, n);
        assert(is_sorted(work, n));

        // 6. Radix Sort (only if all elements are non-negative)
        int has_negative = 0;
        for (int i = 0; i < n; i++)
        {
            if (orig[i] < 0)
            {
                has_negative = 1;
                break;
            }
        }
        if (!has_negative)
        {
            if (n > 0)
            {
                memcpy(work, orig, sizeof(int) * n);
            }
            radix_sort(work, n);
            assert(is_sorted(work, n));
        }

        free(orig);
        free(work);
    }

    fuzzer_free(&fuzzer);
}

int main(void)
{
    unsigned int seed = (unsigned int)time(NULL);
    printf("Starting Advanced Sorting Fuzz Tests with seed: %u\n", seed);

    test_fuzz_advanced_sorting(seed, 50);

    printf("All Advanced Sorting Fuzz Tests passed successfully!\n");
    return 0;
}
