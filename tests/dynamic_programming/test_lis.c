#include "dynamic_programming.h"
#include <assert.h>
#include <stdio.h>

// If the test framework needs to suppress prints, we could use mock_printf.h,
// but since we only print when not interactive, we can just test the logic directly.
// We'll directly include the source to allow testing without linking issues in some environments,
// consistent with test_lcs.c
#include "../../src/dynamic_programming/lis.c"

void test_lis_base_cases(void)
{
    int empty_arr[] = {0}; // Dummy value
    assert(lis(empty_arr, 0) == 0);
    assert(lis(NULL, 5) == 0);

    int single_arr[] = {42};
    assert(lis(single_arr, 1) == 1);
}

void test_lis_normal_case(void)
{
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    // The LIS is {10, 22, 33, 50, 60, 80} which has length 6
    assert(lis(arr, n) == 6);
}

void test_lis_increasing(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    // The LIS is the entire array
    assert(lis(arr, n) == 5);
}

void test_lis_decreasing(void)
{
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    // The LIS is any single element
    assert(lis(arr, n) == 1);
}

void test_lis_duplicates(void)
{
    int arr[] = {2, 2, 2, 2, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    // Since it's strictly increasing, LIS is 1
    assert(lis(arr, n) == 1);
}

int main(void)
{
    test_lis_base_cases();
    test_lis_normal_case();
    test_lis_increasing();
    test_lis_decreasing();
    test_lis_duplicates();

    fprintf(stdout, "All LIS tests passed successfully!\n");
    return 0;
}
