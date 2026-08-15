#include "safe_input.h"
#include "searching_algorithms.h"
#include "sorting_algorithms_n2.h"
#include <stdio.h>
#include <time.h>

static int min_val(int a, int b)
{
    return (a < b) ? a : b;
}

static int exponential_search_demo_impl(const int arr[], int target, int length_of_array)
{
    if (length_of_array <= 0)
    {
        return -1;
    }

    if (arr[0] == target)
    {
        printf("\n[Step 1] arr[0] == %d (target found at index 0)\n", target);
        return 0;
    }

    printf("\n[Step 1] arr[0] = %d != target %d. Beginning exponential jumping steps...\n", arr[0],
           target);

    int i = 1;
    while (i < length_of_array && arr[i] <= target)
    {
        printf(" -> Exponential jump: checking index %d (value = %d) <= target (%d)\n", i, arr[i],
               target);
        if (arr[i] == target)
        {
            printf(" -> Target %d found during exponential jump at index %d!\n", target, i);
            return i;
        }
        i = i * 2;
    }

    int low = i / 2;
    int high = min_val(i, length_of_array - 1);

    if (i < length_of_array)
    {
        printf(" -> Exponential jump: index %d (value = %d) > target (%d)\n", i, arr[i], target);
    }
    else
    {
        printf(" -> Exponential jump: index %d reached end of array (length = %d)\n", i,
               length_of_array);
    }

    printf("\n[Step 2] Binary search range identified: index %d to %d\n", low, high);

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        printf(" -> Binary search: low = %d, mid = %d, high = %d, arr[mid] = %d\n", low, mid, high,
               arr[mid]);
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

void exponential_search_demo(void)
{
    while (1)
    {
        clock_t start_t, end_t;
        double total_t;
        int length_of_array;
        int target;
        int exponential_search_status;

        printf("\nExponential search demo :- \n");
        exponential_search_status = safe_input_int(
            &length_of_array, "\nenter length of array, (between 1 and 100), enter '-1' to exit:- ",
            1, 100);

        if (exponential_search_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting exponential search demo....\n");
            return;
        }

        if (exponential_search_status == 0)
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
                printf("\nExiting exponential search demo....\n");
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
                printf("\nExiting exponential search demo....\n");
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
        int res = exponential_search_demo_impl(arr, target, length_of_array);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("\nelement found at index %d.", res);
        if (res == -1)
        {
            printf("\nelement not found in the given array");
        }

        printf("\ntotal CPU time taken for exponential search:- %f seconds", total_t);
        printf("\n(most probably execution time would be lesser than clock resolution, resulting "
               "in 0.00)\n");
    }
}
