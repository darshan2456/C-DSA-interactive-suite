#include "help.h" 
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int safe_input_string(char* buffer, size_t buffer_size, const char* prompt)
{
    if (getenv("DSA_TEST_MODE") != NULL)
    {
        return 0;
    }

    while (1)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(buffer, buffer_size, stdin) == NULL)
        {
            return 0;
        }

        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
            len--;
        }
        else if (len == buffer_size - 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        if (len == 0) 
        {
            continue;
        }

        if (strcmp(buffer, "help") == 0)
        {
            launch_help_page(); 
            continue;           
        }

        if (strcmp(buffer, "X") == 0)
        {
            return INPUT_EXIT_SIGNAL;
        }

        return 1;
    }
}
