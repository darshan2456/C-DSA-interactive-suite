#include "../utils/config.h"
#include "backtracking.h"
#include <stdio.h>
#include <string.h>
#include "cross_platform_timer.h"


 //Swaps two characters in the string.
static void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Displays the current state of the permutation tree.
 *
 * depth  : Current recursion depth
 * choice : Character position selected at this level
 * length : Length of the input string
 * last   : Tracks whether each ancestor is the last branch,
 *          allowing the tree connectors to be displayed correctly.
 */
static void print_permutation_state(const char* str, int depth, int choice,
                                    int length, const bool last[])
{
    const char* GREEN = "\x1b[32m";
    const char* RED = "\x1b[31m";
    const char* RESET = "\x1b[0m";

    // Print indentation based on the state of ancestor branches
    for (int i = 0; i < depth; i++)
    {
        if (last[i])
            printf("    ");
        else
            printf("│   ");
    }

    // Select the appropriate tree connector for the current branch
    if (choice == length - 1)
        printf("└── ");
    else
        printf("├── ");

    // Print the characters selected so far in green
    printf("%s", GREEN);

    for (int i = 0; i <= depth; i++)
        printf("%c", str[i]);

    printf("%s", RESET);

    // Display the remaining unselected positions as red underscores
    printf("%s", RED);

    for (int i = depth + 1; i < length; i++)
        printf("_");

    printf("%s\n", RESET);

    // Pause briefly so the recursive process can be observed
    dynamic_sleep();
}

/*
 * Generates all permutations of the string using backtracking.
 *
 * At each recursion level, every remaining character is selected
 * for the current position. After recursively exploring that choice,
 * the swap is undone to restore the previous state.
 */
int solve_string_permutation(char str[], int depth, int length, bool last[], bool visualize)
{
    if (depth == length)
        return 1;

    int count=0;
    // Try every remaining character at the current position
    for (int choice = depth; choice < length; choice++)
    {
        
        swap(&str[depth], &str[choice]);

        // Track whether this is the last branch at this depth
        last[depth] = (choice == length - 1);

        // Display the current state of the recursion tree only during demo, and not during tests
        if(visualize)
            print_permutation_state(str, depth, choice, length, last);

        // Recursively generate permutations for the next position and accumulate count
        count+=solve_string_permutation(str, depth + 1, length, last,visualize);

        //Backtrack by restoring the string to its previous state
        swap(&str[depth], &str[choice]);
    }

    return count;
}