#include "sorting_algorithms_n2.h"

void cocktail_shaker_sort(int arr[], int n)
{
    if (arr == NULL || n <= 0)
    {
        return;
    }
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped)
    {
        swapped = 0;

        // Forward pass (like standard Bubble Sort)
        for (int i = start; i < end; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;

        swapped = 0;
        --end;

        // Backward pass (catching the turtles)
        for (int i = end - 1; i >= start; --i)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        ++start;
    }
}
