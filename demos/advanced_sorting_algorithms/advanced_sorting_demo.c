#include "advanced_sorting.h"
#include "display_header.h"
#include "safe_input.h"
#include "sorting_telemetry.h"
#include <stdio.h>

void advanced_sorting_demo(void)
{
    int sorting_algo_status, sorting_algo_choice;
    while (1)
    {
        display_header("Advanced Sorting Algorithms");

        printf("\nAdvanced sorting algorithms demo\n");

        sorting_algo_status =
            safe_input_int(&sorting_algo_choice,
                           "enter '1' for quick sort, '2' for merge sort, '3' "
                           "for heap sort, '4' for radix sort, '5' for bucket sort, '6' for "
                           "counting sort, '7' for "
                           "Comparative Performance Dashboard, '-1' to exit:- ",
                           1, 7);

        if (sorting_algo_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting advanced sorting algorithms demo\n");
            return;
        }

        if (sorting_algo_status == 0)
        {
            continue;
        }

        if (sorting_algo_choice == 1)
        {
            display_header("Quick Sort");
            quicksort_demo();
        }
        else if (sorting_algo_choice == 2)
        {
            display_header("Merge Sort");
            merge_sort_demo();
        }
        else if (sorting_algo_choice == 3)
        {
            display_header("Heap Sort");
            heap_sort_demo();
        }
        else if (sorting_algo_choice == 4)
        {
            display_header("Radix Sort");
            radix_sort_demo();
        }
        else if (sorting_algo_choice == 5)
        {
            display_header("Bucket Sort");
            bucket_sort_demo();
        }
        else if (sorting_algo_choice == 6)
        {
            display_header("Counting Sort");
            counting_sort_demo();
        }
        else if (sorting_algo_choice == 7)
        {
            display_header("Comparative Performance Dashboard");
            sorting_telemetry_dashboard_demo();
        }
    }
}
