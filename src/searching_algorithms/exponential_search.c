#include "searching_algorithms.h"
#include <stdio.h>

static int min_val(int a, int b)
{
    return (a < b) ? a : b;
}

int exponential_search(int arr[], int target, int length_of_array)
{
    if (length_of_array <= 0)
    {
        return -1;
    }

    if (arr[0] == target)
    {
        return 0;
    }

    int i = 1;
    while (i < length_of_array && arr[i] <= target)
    {
        i = i * 2;
    }

    int low = i / 2;
    int high = min_val(i, length_of_array - 1);

    return binary_search_recursive(arr, target, low, high);
}
