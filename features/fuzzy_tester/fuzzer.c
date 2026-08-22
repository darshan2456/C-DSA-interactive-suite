#include "fuzzer.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fuzzer_init(FuzzerState* fuzzer, unsigned int seed, int max_ops)
{
    fuzzer->seed = seed;
    fuzzer->current_op = 0;
    fuzzer->max_ops = max_ops;
    fuzzer->log_capacity = 1000;
    fuzzer->op_log = (char**)malloc(fuzzer->log_capacity * sizeof(char*));
    if (fuzzer->op_log != NULL)
    {
        for (int i = 0; i < fuzzer->log_capacity; i++)
        {
            fuzzer->op_log[i] = NULL;
        }
    }
}

void fuzzer_free(FuzzerState* fuzzer)
{
    if (fuzzer->op_log != NULL)
    {
        for (int i = 0; i < fuzzer->current_op; i++)
        {
            if (fuzzer->op_log[i] != NULL)
            {
                free(fuzzer->op_log[i]);
            }
        }
        free(fuzzer->op_log);
        fuzzer->op_log = NULL;
    }
}

void fuzzer_log_op(FuzzerState* fuzzer, const char* format, ...)
{
    if (fuzzer->op_log == NULL || fuzzer->current_op >= fuzzer->max_ops)
    {
        return;
    }

    if (fuzzer->current_op >= fuzzer->log_capacity)
    {
        int new_capacity = fuzzer->log_capacity * 2;
        char** new_log = (char**)realloc(fuzzer->op_log, new_capacity * sizeof(char*));
        if (new_log == NULL)
        {
            return;
        }
        fuzzer->op_log = new_log;
        for (int i = fuzzer->log_capacity; i < new_capacity; i++)
        {
            fuzzer->op_log[i] = NULL;
        }
        fuzzer->log_capacity = new_capacity;
    }

    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    fuzzer->op_log[fuzzer->current_op] = strdup(buffer);
    fuzzer->current_op++;
}

void fuzzer_dump_log(const FuzzerState* fuzzer)
{
    printf("\n=== STOCHASTIC FUZZER REPLAY LOG ===\n");
    printf("Seed: %u\n", fuzzer->seed);
    printf("Total Operations executed: %d\n", fuzzer->current_op);
    if (fuzzer->op_log != NULL)
    {
        for (int i = 0; i < fuzzer->current_op; i++)
        {
            if (fuzzer->op_log[i] != NULL)
            {
                printf("[%d] %s\n", i, fuzzer->op_log[i]);
            }
        }
    }
    printf("====================================\n\n");
}

int fuzzer_rand_int(FuzzerState* fuzzer, int min, int max)
{
    if (min >= max)
    {
        return min;
    }
    fuzzer->seed = fuzzer->seed * 1103515245 + 12345;
    unsigned int val = (fuzzer->seed / 65536) % 32768;
    return min + (int)(val % (unsigned int)(max - min + 1));
}

int fuzzer_get_iterations(int default_iterations)
{
    const char* valgrind_mode = getenv("VALGRIND_MODE");
    if (valgrind_mode != NULL && strcmp(valgrind_mode, "1") == 0)
    {
        return 20;
    }
    return default_iterations;
}
