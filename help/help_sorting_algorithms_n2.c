#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_sorting_algorithms_n2_menu(void)
{
    display_header("Help - O(N^2) Sorting Algorithms");
    printf("BUBBLE SORT:\n");
    printf("    Repeatedly steps through the list, compares adjacent elements, and swaps them if "
           "in wrong order.\n\n");
    printf("SELECTION SORT:\n");
    printf("    Divides input into sorted and unsorted parts. Repeatedly finds minimum element "
           "and moves it to sorted part.\n\n");
    printf("INSERTION SORT:\n");
    printf("    Builds final sorted array one item at a time by inserting elements into their "
           "correct position.\n\n");
    printf("SHELL SORT:\n");
    printf("    A generalization of Insertion Sort that allows the exchange of far-apart\n");
    printf("    elements, reducing the array's inversion count step-by-step using a gap "
           "sequence.\n\n");

    printf("RELATIONSHIPS & COMPARISONS:\n");
    printf("    • Bubble vs. Selection vs. Insertion:\n");
    printf("      - Bubble Sort is generally the least efficient due to excessive swaps.\n");
    printf("      - Selection Sort minimizes write operations (ideal when memory writes are "
           "costly).\n");
    printf("      - Insertion Sort is extremely fast for nearly-sorted or small datasets.\n");
    printf("    • Insertion vs. Shell Sort:\n");
    printf("      - Shell Sort acts as a bridge between simple O(N^2) and fast O(N log N) "
           "sorts.\n");
    printf("      - By doing long-distance swaps, Shell Sort reduces inversions quickly, "
           "allowing\n");
    printf("        subsequent passes to run in near-linear time.\n\n");

    printf("WHEN TO USE WHAT & REAL-WORLD USE CASES:\n");
    printf("    • Use Insertion Sort for small arrays (typically N < 15) or nearly-sorted lists\n");
    printf("      (often used as the base-case cutoff for Quick Sort and Merge Sort).\n");
    printf("    • Use Shell Sort in embedded systems with strict memory bounds where recursive\n");
    printf("      stack overhead (of Quick Sort) or auxiliary memory (of Merge Sort) is "
           "unacceptable.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
