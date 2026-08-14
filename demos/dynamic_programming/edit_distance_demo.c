#include "display_header.h"
#include "dynamic_programming.h"
#include "safe_input.h"
#include <stdio.h>
#include <string.h>

void edit_distance_demo(void)
{
    while (1)
    {
        display_header("Edit Distance (Levenshtein) Demo");

        int choice;
        int status = safe_input_int(&choice,
                                    "\nenter 1 to compute Edit Distance\n"
                                    "enter '-1' to exit: ",
                                    1, 1);

        if (status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (status == 0)
        {
            continue;
        }

        char word1[256];
        int w1_status = safe_input_string(word1, sizeof(word1), "\nEnter the first string: ");
        if (w1_status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (w1_status == 0)
        {
            continue;
        }

        char word2[256];
        int w2_status = safe_input_string(word2, sizeof(word2), "Enter the second string: ");
        if (w2_status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (w2_status == 0)
        {
            continue;
        }

        int m = strlen(word1);
        int n = strlen(word2);

        printf("\nCalculating Edit Distance between '%s' and '%s'...\n", word1, word2);

        int result = edit_distance(word1, word2, m, n);

        if (result != -1)
        {
            printf("\nMinimum Operations Required (Edit Distance): %d\n", result);
        }
    }
}
