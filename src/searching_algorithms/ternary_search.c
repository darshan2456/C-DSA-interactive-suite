#include "searching_algorithms.h"
#include <stdio.h>

int ternary_search(int arr[], int target, int length_of_array)
{
    if (arr == NULL || length_of_array <= 0)
    {
        return -1;
    }

    int low = 0;
    int high = length_of_array - 1;

    while (low <= high)
    {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if (arr[mid1] == target)
        {
            return mid1;
        }
        if (arr[mid2] == target)
        {
            return mid2;
        }

        if (target < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (target > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int ternary_search_recursive(int arr[], int target, int low, int high)
{
    if (arr == NULL || low < 0 || low > high)
    {
        return -1;
    }

    int mid1 = low + (high - low) / 3;
    int mid2 = high - (high - low) / 3;

    if (arr[mid1] == target)
    {
        return mid1;
    }
    if (arr[mid2] == target)
    {
        return mid2;
    }

    if (target < arr[mid1])
    {
        return ternary_search_recursive(arr, target, low, mid1 - 1);
    }
    else if (target > arr[mid2])
    {
        return ternary_search_recursive(arr, target, mid2 + 1, high);
    }
    else
    {
        return ternary_search_recursive(arr, target, mid1 + 1, mid2 - 1);
    }
}
