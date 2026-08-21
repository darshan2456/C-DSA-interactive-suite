#include "fuzzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    unsigned int seed = (unsigned int)time(NULL);
    FuzzerState fuzzer;
    printf("Starting Heap Fuzzing with seed: %u\n", seed);

    fuzzer_init(&fuzzer, seed, 2100);
    run_binomial_fuzz(&fuzzer, 300);
    run_fibonacci_fuzz(&fuzzer, 300);
    run_minmax_fuzz(&fuzzer, 300);
    run_leftist_fuzz(&fuzzer, 300);
    run_skew_fuzz(&fuzzer, 300);
    run_dary_fuzz(&fuzzer, 300);
    run_treap_fuzz(&fuzzer, 300);
    fuzzer_free(&fuzzer);

    printf("Heap Fuzzing completed successfully!\n");
    return 0;
}
