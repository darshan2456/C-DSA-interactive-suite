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

        printf("Enter the text to search in (or type 'exit' to quit): ");
        if (fgets(text, sizeof(text), stdin) == NULL)
        {
            break;
        }

        // Remove trailing newline
        size_t len = strlen(text);
        if (len > 0 && text[len - 1] == '\n')
        {
            text[len - 1] = '\0';
        }

        if (strcmp(text, "exit") == 0)
        {
            break;
        }

        printf("Enter the pattern to search for: ");
        if (fgets(pattern, sizeof(pattern), stdin) == NULL)
        {
            break;
        }

        // Remove trailing newline
        len = strlen(pattern);
        if (len > 0 && pattern[len - 1] == '\n')
        {
            pattern[len - 1] = '\0';
        }

        printf("\nSearching for '%s' in '%s'...\n", pattern, text);
        boyer_moore_search(text, pattern);
        printf("\n");
    }

    printf("Exiting Boyer-Moore demo.\n");
}
