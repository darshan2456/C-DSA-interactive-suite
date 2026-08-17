#include "../../src/sorting_algorithms_n2/sorting_algorithms_n2.h"
#include "../../src/utils/display_header.h"
#include "../../src/utils/safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void cocktail_shaker_sort_demo(void)
{
    display_header("Cocktail Shaker Sort Demonstration");

    int n;
    if (safe_input_int(&n, "Enter the number of elements to sort: ", 1, 1000) != 1)
        return;

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
    {
        if (safe_input_int(&arr[i], "> ", -100000, 100000) != 1)
        {
            free(arr);
            return;
        }
    }

    printf("\nOriginal Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    cocktail_shaker_sort(arr, n);

    printf("Sorted Array:   ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    free(arr);
}
