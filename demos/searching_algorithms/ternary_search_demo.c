#include "safe_input.h"
#include "searching_algorithms.h"
#include "sorting_algorithms_n2.h"
#include <stdio.h>
#include <time.h>

static int ternary_search_demo_impl(const int arr[], int target, int length_of_array)
{
    if (length_of_array <= 0)
    {
        return -1;
    }

    int low = 0;
    int high = length_of_array - 1;
    int step = 1;

    printf("\nBeginning Ternary Search step-by-step partitioning...\n");

    while (low <= high)
    {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        printf(" -> Step %d: range [%d..%d], mid1 = %d (val = %d), mid2 = %d (val = %d)\n", step++,
               low, high, mid1, arr[mid1], mid2, arr[mid2]);

        if (arr[mid1] == target)
        {
            printf(" -> Target %d found at index %d (mid1)!\n", target, mid1);
            return mid1;
        }
        if (arr[mid2] == target)
        {
            printf(" -> Target %d found at index %d (mid2)!\n", target, mid2);
            return mid2;
        }

        if (target < arr[mid1])
        {
            printf(" -> Target %d < arr[%d] (%d): searching left third [%d..%d]\n", target, mid1,
                   arr[mid1], low, mid1 - 1);
            high = mid1 - 1;
        }
        else if (target > arr[mid2])
        {
            printf(" -> Target %d > arr[%d] (%d): searching right third [%d..%d]\n", target, mid2,
                   arr[mid2], mid2 + 1, high);
            low = mid2 + 1;
        }
        else
        {
            printf(" -> Target %d is between arr[%d] (%d) and arr[%d] (%d): searching middle third "
                   "[%d..%d]\n",
                   target, mid1, arr[mid1], mid2, arr[mid2], mid1 + 1, mid2 - 1);
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

void ternary_search_demo(void)
{
    while (1)
    {
        clock_t start_t, end_t;
        double total_t;
        int length_of_array;
        int target;
        int ternary_search_status;

        printf("\nTernary search demo :- \n");
        ternary_search_status = safe_input_int(
            &length_of_array, "\nenter length of array, (between 1 and 100), enter '-1' to exit:- ",
            1, 100);

        if (ternary_search_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting ternary search demo....\n");
            return;
        }

        if (ternary_search_status == 0)
        {
            continue;
        }

        int arr[length_of_array];

        int element_status;

        for (int i = 0; i < length_of_array; i++)
        {
        retry_element:
            printf("\nenter element no %d, (between 1 and 100), enter '-1' to exit:- ", i);
            element_status = safe_input_int(&arr[i], NULL, 1, 100);

            if (element_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting ternary search demo....\n");
                return;
            }

            if (element_status == 0)
            {
                goto retry_element;
            }
        }

        int target_status;

        while (1)
        {
            target_status = safe_input_int(&target,
                                           "\nEnter target which you want to search, (between 1 "
                                           "and 100), enter '-1' to exit:- ",
                                           1, 100);

            if (target_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting ternary search demo....\n");
                return;
            }

            if (target_status == 0)
            {
                continue;
            }

            break;
        }

        selection_sort(arr, length_of_array);

        printf("\nSorted array elements: ");
        for (int i = 0; i < length_of_array; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        start_t = clock();
        int res = ternary_search_demo_impl(arr, target, length_of_array);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("\nelement found at index %d.", res);
        if (res == -1)
        {
            printf("\nelement not found in the given array");
        }

        printf("\ntotal CPU time taken for ternary search:- %f seconds", total_t);
        printf("\n(most probably execution time would be lesser than clock resolution, resulting "
               "in 0.00)\n");
    }
}
