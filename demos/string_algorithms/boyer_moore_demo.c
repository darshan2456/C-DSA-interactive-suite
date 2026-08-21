#include "safe_input.h"
#include "string_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void boyer_moore_demo(void)
{
    printf("\nBoyer-Moore String Search Algorithm Demo\n");

    while (1)
    {
        char text[1024];
        char pattern[256];

        int status_T =
            safe_input_string(text, sizeof(text), "Enter the text to search in, or 'X' to exit: ");
        if (status_T == INPUT_EXIT_SIGNAL)
        {
            break;
        }
        if (status_T == 0)
        {
            continue;
        }

        int status_P = safe_input_string(pattern, sizeof(pattern),
                                         "Enter the pattern to search for, or 'X' to exit: ");
        if (status_P == INPUT_EXIT_SIGNAL)
        {
            break;
        }
        if (status_P == 0)
        {
            continue;
        }

        printf("\nSearching for '%s' in '%s'...\n", pattern, text);
        boyer_moore_search(text, pattern);
        printf("\n");
    }

    printf("Exiting Boyer-Moore demo.\n");
}
