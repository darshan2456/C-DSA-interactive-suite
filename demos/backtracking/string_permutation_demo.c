#include "../utils/config.h"
#include "backtracking.h"
#include "safe_input.h"

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 5

void string_permutation_demo(void)
{
    while (1)
    {
        char str[MAX_STRING_LENGTH + 1];

        int status = safe_input_string(str, sizeof(str),
                                       "\nEnter a string (maximum 5 characters), or X to exit: ");

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting String Permutation Solver...\n");
            return;
        }

        if (status == 0)
        {
            continue;
        }

        int length = strlen(str);
        bool last[MAX_STRING_LENGTH] = {false};

        printf("\nStarting String Permutation Solver...\n");

        const char* RED = "\x1b[31m";
        const char* RESET = "\x1b[0m";

        for (int i = 0; i < length; i++)
            printf("%s_%s", RED, RESET);

        printf("\n\n");

        dynamic_sleep();

        int count = solve_string_permutation(str, 0, length, last, true);

        printf("\nTotal Permutations:%d\n", count);

        printf("\nString permutation completed successfully!\n");
    }
}