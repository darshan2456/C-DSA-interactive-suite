#include "../../src/searching_algorithms/searching_algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FUZZ_ITERATIONS 1000

// Helper function for qsort
static int compare_ints(const void* a, const void* b)
{
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    if (int_a < int_b)
        return -1;
    if (int_a > int_b)
        return 1;
    return 0;
}

// Generate random lengths with some weighting
static int get_fuzz_length(int max_len)
{
    int r = rand() % 100;
    int len = 0;
    if (r < 80)
    {
        len = rand() % 100;
    }
    else if (r < 98)
    {
        len = rand() % 1000;
    }
    else
    {
        len = rand() % (max_len + 1);
    }
    return len;
}

// Generate random array
static void generate_random_array(int* arr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        // Generate values in a reasonable range to prevent massive overflows in interpolation
        // search but still allow negative and positive numbers
        arr[i] = (rand() % 20000) - 10000;
    }
}

// Test positive cases where target is guaranteed to exist
static void test_positive_search(int* arr, int len, int target)
{
    int idx;

    idx = linear_search(arr, target, len);
    assert(idx >= 0 && idx < len && arr[idx] == target);

    idx = binary_search(arr, target, len);
    assert(idx >= 0 && idx < len && arr[idx] == target);

    idx = binary_search_recursive(arr, target, 0, len - 1);
    assert(idx >= 0 && idx < len && arr[idx] == target);

    idx = interpolation_search(arr, target, len);
    assert(idx >= 0 && idx < len && arr[idx] == target);

    idx = jump_search(arr, target, len);
    assert(idx >= 0 && idx < len && arr[idx] == target);
}

// Test negative cases where target is guaranteed NOT to exist
static void test_negative_search(int* arr, int len, int target)
{
    assert(linear_search(arr, target, len) == -1);
    assert(binary_search(arr, target, len) == -1);
    assert(binary_search_recursive(arr, target, 0, len - 1) == -1);
    assert(interpolation_search(arr, target, len) == -1);
    assert(jump_search(arr, target, len) == -1);
}

static void test_searching_fuzz(void)
{
    for (int i = 0; i < FUZZ_ITERATIONS; ++i)
    {
        int len = get_fuzz_length(10000);

        int* arr = NULL;
        if (len > 0)
        {
            arr = malloc((size_t)len * sizeof(int));
            assert(arr != NULL);
            generate_random_array(arr, len);

            // Add extreme edge cases sometimes (all duplicates)
            if (rand() % 20 == 0)
            {
                int val = (rand() % 20000) - 10000;
                for (int j = 0; j < len; ++j)
                {
                    arr[j] = val;
                }
            }

            // Sort array as prerequisite for binary/interpolation search
            qsort(arr, (size_t)len, sizeof(int), compare_ints);
        }

        if (len > 0)
        {
            // Positive Test: pick a random existing element
            int target_idx = rand() % len;
            int target = arr[target_idx];
            test_positive_search(arr, len, target);

            // Negative Test: pick a value smaller than minimum or larger than maximum, or
            // completely random
            int neg_target;
            int rand_choice = rand() % 3;
            if (rand_choice == 0)
            {
                neg_target = arr[0] - (rand() % 1000) - 1; // Strictly smaller than min
            }
            else if (rand_choice == 1)
            {
                neg_target = arr[len - 1] + (rand() % 1000) + 1; // Strictly larger than max
            }
            else
            {
                // Find a missing element by binary search
                neg_target = arr[0];
                while (binary_search(arr, neg_target, len) != -1)
                {
                    neg_target = (rand() % 40000) - 20000;
                }
            }
            test_negative_search(arr, len, neg_target);
        }
        else
        {
            // Array length 0: negative test only
            test_negative_search(arr, 0, 42);
        }

        if (arr != NULL)
        {
            free(arr);
        }
    }
    printf("Searching algorithms fuzz tests passed\n");
}

int main(void)
{
    srand((unsigned int)time(NULL));

    test_searching_fuzz();

    return 0;
}
