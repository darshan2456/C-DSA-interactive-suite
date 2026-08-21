#include "../../features/fuzzy_tester/fuzzer.h"
#include "../../src/string_algorithms/string_algorithms.h"
#include <stdlib.h>
#include <string.h>

static void generate_fuzz_string(FuzzerState* fuzzer, char** str, int max_len)
{
    int length = fuzzer_rand_int(fuzzer, 0, max_len);
    *str = (char*)malloc(length + 1);
    if (*str == NULL)
    {
        return;
    }

    if (length == 0)
    {
        (*str)[0] = '\0';
        return;
    }

    int type = fuzzer_rand_int(fuzzer, 0, 3);
    if (type == 0)
    {
        // Repeating character pattern (highly likely to cause worst-case performance/crashes)
        char c = (char)fuzzer_rand_int(fuzzer, 65, 90);
        for (int i = 0; i < length; i++)
        {
            (*str)[i] = c;
        }
    }
    else if (type == 1)
    {
        // Printable ASCII text
        for (int i = 0; i < length; i++)
        {
            (*str)[i] = (char)fuzzer_rand_int(fuzzer, 32, 126);
        }
    }
    else if (type == 2)
    {
        // Standard DNA-style sequence
        const char dna[] = "ACGT";
        for (int i = 0; i < length; i++)
        {
            (*str)[i] = dna[fuzzer_rand_int(fuzzer, 0, 3)];
        }
    }
    else
    {
        // Binary garbage (avoiding null terminators to keep standard string functions happy)
        for (int i = 0; i < length; i++)
        {
            char c = (char)fuzzer_rand_int(fuzzer, 1, 255);
            (*str)[i] = (c != '\0') ? c : 'A';
        }
    }
    (*str)[length] = '\0';
}

void run_string_fuzz(FuzzerState* fuzzer, int ops)
{
    fuzzer_log_op(fuzzer, "--- Starting String Algorithms Fuzz Test (%d ops) ---", ops);

    for (int i = 0; i < ops; i++)
    {
        char* text = NULL;
        char* pattern = NULL;

        generate_fuzz_string(fuzzer, &text, 1000);
        generate_fuzz_string(fuzzer, &pattern, 100);

        if (text == NULL || pattern == NULL)
        {
            if (text != NULL)
                free(text);
            if (pattern != NULL)
                free(pattern);
            continue;
        }

        fuzzer_log_op(fuzzer, "Op %d: Fuzzing text (len %lu) against pattern (len %lu)", i,
                      strlen(text), strlen(pattern));

        // Execute the algorithms
        naive_string_matching(text, pattern);
        kmp_search(text, pattern);
        rabin_karp_search(text, pattern, 101); // 101 is a standard prime for Rabin-Karp

        free(text);
        free(pattern);
    }

    fuzzer_log_op(fuzzer, "--- String Algorithms Fuzz Test Complete ---");
}

int main(void)
{
    FuzzerState fuzzer;

    // Initialize the fuzzer with a fixed seed and 1000 operations
    fuzzer_init(&fuzzer, 12345, 1000);

    // Run our string algorithms fuzzer
    run_string_fuzz(&fuzzer, 1000);

    // Clean up allocated fuzzer memory
    fuzzer_free(&fuzzer);

    return 0;
}
