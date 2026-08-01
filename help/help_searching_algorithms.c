#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_searching_algorithms_menu(void)
{
    display_header("Help - Searching Algorithms");
    printf("LINEAR SEARCH:\n");
    printf("    Checks every element of the list sequentially until a match is found. O(N) "
           "complexity.\n\n");
    printf("BINARY SEARCH:\n");
    printf("    Finds position of target value within a sorted array by repeatedly halving the "
           "search interval. O(log N).\n\n");
    printf("JUMP SEARCH:\n");
    printf("    Searches in a sorted array by jumping ahead by fixed steps (usually sqrt(N)).\n\n");
    printf("INTERPOLATION SEARCH:\n");
    printf("    Improved binary search for uniformly distributed sorted arrays. O(log log N) "
           "average case.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
