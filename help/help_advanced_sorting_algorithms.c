#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_advanced_sorting_algorithms_menu(void)
{
    display_header("Help - Advanced Sorting Algorithms");
    printf("QUICK SORT:\n");
    printf("    Divide-and-conquer algorithm. Picks an element as pivot and partitions the "
           "array around it.\n\n");
    printf("MERGE SORT:\n");
    printf("    Divide-and-conquer algorithm. Recursively splits array in halves, sorts them, "
           "and merges them.\n\n");
    printf("HEAP SORT:\n");
    printf("    Comparison-based sorting technique based on Binary Heap data structure.\n\n");
    printf("BUCKET SORT:\n");
    printf("    Distributes elements into buckets, sorts each bucket, and concatenates them.\n");
    printf("    Average O(N + K) for uniformly distributed input.\n\n");
    printf("RADIX SORT:\n");
    printf("    Non-comparison sort that processes digits from least to most significant.\n");
    printf("    O(D * (N + K)) where D is the number of digits.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
