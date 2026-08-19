#include <assert.h>
#include <stdio.h>

/* Forward declarations */
int linear_search(int arr[], int target, int length_of_array);
int binary_search(int arr[], int target, int length_of_array);
int binary_search_recursive(int arr[], int target, int low, int high);
int interpolation_search(int arr[], int target, int length_of_array);
int jump_search(int arr[], int target, int length_of_array);
int exponential_search(int arr[], int target, int length_of_array);
int ternary_search(int arr[], int target, int length_of_array);
int ternary_search_recursive(int arr[], int target, int low, int high);

void test_linear_search()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(linear_search(arr1, 1, 5) == 0);
    assert(linear_search(arr1, 5, 5) == 4);
    assert(linear_search(arr1, 3, 5) == 2);
    assert(linear_search(arr1, 10, 5) == -1);

    int arr2[] = {42};
    assert(linear_search(arr2, 42, 1) == 0);
    assert(linear_search(arr2, 1, 1) == -1);

    int arr3[] = {5, 5, 5};
    assert(linear_search(arr3, 5, 3) == 0); // first occurrence

    printf("Linear search tests passed\n");
}

void test_binary_search()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(binary_search(arr1, 1, 5) == 0);
    assert(binary_search(arr1, 5, 5) == 4);
    assert(binary_search(arr1, 3, 5) == 2);
    assert(binary_search(arr1, 10, 5) == -1);

    int arr2[] = {42};
    assert(binary_search(arr2, 42, 1) == 0);
    assert(binary_search(arr2, 1, 1) == -1);

    int arr3[] = {2, 4, 6, 8, 10, 12};
    assert(binary_search(arr3, 8, 6) == 3);

    printf("Binary search tests passed\n");
}

void test_binary_search_recursive()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(binary_search_recursive(arr1, 1, 0, 4) == 0);
    assert(binary_search_recursive(arr1, 5, 0, 4) == 4);
    assert(binary_search_recursive(arr1, 3, 0, 4) == 2);
    assert(binary_search_recursive(arr1, 10, 0, 4) == -1);

    int arr2[] = {42};
    assert(binary_search_recursive(arr2, 42, 0, 0) == 0);
    assert(binary_search_recursive(arr2, 1, 0, 0) == -1);

    int arr3[] = {2, 4, 6, 8, 10, 12};
    assert(binary_search_recursive(arr3, 8, 0, 5) == 3);

    printf("Recursive binary search tests passed\n");
}

void test_interpolation_search()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(interpolation_search(arr1, 1, 5) == 0);
    assert(interpolation_search(arr1, 5, 5) == 4);
    assert(interpolation_search(arr1, 3, 5) == 2);
    assert(interpolation_search(arr1, 10, 5) == -1);

    int arr2[] = {42};
    assert(interpolation_search(arr2, 42, 1) == 0);
    assert(interpolation_search(arr2, 1, 1) == -1);

    int arr3[] = {2, 4, 6, 8, 10, 12};
    assert(interpolation_search(arr3, 8, 6) == 3);

    printf("Interpolation search tests passed\n");
}

void test_jump_search()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(jump_search(arr1, 1, 5) == 0);
    assert(jump_search(arr1, 5, 5) == 4);
    assert(jump_search(arr1, 3, 5) == 2);
    assert(jump_search(arr1, 10, 5) == -1);

    int arr2[] = {42};
    assert(jump_search(arr2, 42, 1) == 0);
    assert(jump_search(arr2, 1, 1) == -1);

    int arr3[] = {2, 4, 6, 8, 10, 12};
    assert(jump_search(arr3, 8, 6) == 3);

    printf("Jump search tests passed\n");
}

void test_exponential_search()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(exponential_search(arr1, 1, 5) == 0);
    assert(exponential_search(arr1, 5, 5) == 4);
    assert(exponential_search(arr1, 3, 5) == 2);
    assert(exponential_search(arr1, 10, 5) == -1);

    int arr2[] = {42};
    assert(exponential_search(arr2, 42, 1) == 0);
    assert(exponential_search(arr2, 1, 1) == -1);

    int arr3[] = {2, 4, 6, 8, 10, 12};
    assert(exponential_search(arr3, 8, 6) == 3);

    printf("Exponential search tests passed\n");
}

void test_ternary_search()
{
    int arr1[] = {1, 2, 3, 4, 5};
    assert(ternary_search(arr1, 1, 5) == 0);
    assert(ternary_search(arr1, 5, 5) == 4);
    assert(ternary_search(arr1, 3, 5) == 2);
    assert(ternary_search(arr1, 10, 5) == -1);

    assert(ternary_search_recursive(arr1, 1, 0, 4) == 0);
    assert(ternary_search_recursive(arr1, 5, 0, 4) == 4);
    assert(ternary_search_recursive(arr1, 3, 0, 4) == 2);
    assert(ternary_search_recursive(arr1, 10, 0, 4) == -1);

    int arr2[] = {42};
    assert(ternary_search(arr2, 42, 1) == 0);
    assert(ternary_search(arr2, 1, 1) == -1);
    assert(ternary_search_recursive(arr2, 42, 0, 0) == 0);
    assert(ternary_search_recursive(arr2, 1, 0, 0) == -1);

    int arr3[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    assert(ternary_search(arr3, 12, 9) == 5);
    assert(ternary_search_recursive(arr3, 12, 0, 8) == 5);

    printf("Ternary search tests passed\n");
}

void test_searching_advanced_edge_cases()
{
    /* Array with negative numbers */
    int neg_arr[] = {-50, -30, -10, 0, 15, 45, 90};
    int n = 7;
    assert(linear_search(neg_arr, -30, n) == 1);
    assert(binary_search(neg_arr, -30, n) == 1);
    assert(binary_search_recursive(neg_arr, -30, 0, n - 1) == 1);
    assert(interpolation_search(neg_arr, -30, n) == 1);
    assert(jump_search(neg_arr, -30, n) == 1);
    assert(exponential_search(neg_arr, -30, n) == 1);
    assert(ternary_search(neg_arr, -30, n) == 1);
    assert(ternary_search_recursive(neg_arr, -30, 0, n - 1) == 1);

    /* Target smaller than min element */
    assert(linear_search(neg_arr, -100, n) == -1);
    assert(binary_search(neg_arr, -100, n) == -1);
    assert(binary_search_recursive(neg_arr, -100, 0, n - 1) == -1);
    assert(interpolation_search(neg_arr, -100, n) == -1);
    assert(jump_search(neg_arr, -100, n) == -1);
    assert(exponential_search(neg_arr, -100, n) == -1);
    assert(ternary_search(neg_arr, -100, n) == -1);
    assert(ternary_search_recursive(neg_arr, -100, 0, n - 1) == -1);

    /* Target larger than max element */
    assert(linear_search(neg_arr, 500, n) == -1);
    assert(binary_search(neg_arr, 500, n) == -1);
    assert(binary_search_recursive(neg_arr, 500, 0, n - 1) == -1);
    assert(interpolation_search(neg_arr, 500, n) == -1);
    assert(jump_search(neg_arr, 500, n) == -1);
    assert(exponential_search(neg_arr, 500, n) == -1);
    assert(ternary_search(neg_arr, 500, n) == -1);
    assert(ternary_search_recursive(neg_arr, 500, 0, n - 1) == -1);

    /* Large uniform array */
    int uniform[10] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
    assert(linear_search(uniform, 7, 10) == 0);
    assert(binary_search(uniform, 7, 10) >= 0);
    assert(binary_search_recursive(uniform, 7, 0, 9) >= 0);
    assert(interpolation_search(uniform, 7, 10) >= 0);
    assert(jump_search(uniform, 7, 10) >= 0);
    assert(exponential_search(uniform, 7, 10) >= 0);
    assert(ternary_search(uniform, 7, 10) >= 0);
    assert(ternary_search_recursive(uniform, 7, 0, 9) >= 0);

    /* Two element array */
    int duo[2] = {10, 20};
    assert(binary_search(duo, 10, 2) == 0);
    assert(binary_search(duo, 20, 2) == 1);
    assert(binary_search(duo, 15, 2) == -1);
    assert(binary_search_recursive(duo, 10, 0, 1) == 0);
    assert(binary_search_recursive(duo, 20, 0, 1) == 1);
    assert(binary_search_recursive(duo, 15, 0, 1) == -1);
    assert(exponential_search(duo, 10, 2) == 0);
    assert(exponential_search(duo, 20, 2) == 1);
    assert(exponential_search(duo, 15, 2) == -1);
    assert(ternary_search(duo, 10, 2) == 0);
    assert(ternary_search(duo, 20, 2) == 1);
    assert(ternary_search(duo, 15, 2) == -1);

    /* Reverse sorted array searching */
    int rev_search[] = {100, 80, 60, 40, 20, 0};
    assert(linear_search(rev_search, 60, 6) == 2);
    assert(linear_search(rev_search, 999, 6) == -1);

    /* Single element array boundary checks */
    int single_arr[] = {42};
    assert(linear_search(single_arr, 42, 1) == 0);
    assert(linear_search(single_arr, 99, 1) == -1);
    assert(binary_search(single_arr, 42, 1) == 0);
    assert(binary_search(single_arr, 99, 1) == -1);
    assert(binary_search_recursive(single_arr, 42, 0, 0) == 0);
    assert(binary_search_recursive(single_arr, 99, 0, 0) == -1);
    assert(exponential_search(single_arr, 42, 1) == 0);
    assert(exponential_search(single_arr, 99, 1) == -1);
    assert(ternary_search(single_arr, 42, 1) == 0);
    assert(ternary_search(single_arr, 99, 1) == -1);

    printf("Searching advanced edge case tests passed\n");
}

int main()
{
    test_linear_search();
    test_binary_search();
    test_binary_search_recursive();
    test_interpolation_search();
    test_jump_search();
    test_exponential_search();
    test_ternary_search();
    test_searching_advanced_edge_cases();
    printf("All search tests passed\n");
    return 0;
}