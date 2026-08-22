#include "fuzzer.h"
#include "step_debugger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    setenv("DSA_TEST_MODE", "1", 1);
    set_step_mode(0);
    set_paused(0);
    unsigned int seed = (unsigned int)time(NULL);
    FuzzerState fuzzer;
    printf("Starting Graph Fuzzing with seed: %u\n", seed);

    fuzzer_init(&fuzzer, seed, 600);
    run_unweighted_graph_fuzz(&fuzzer, fuzzer_get_iterations(300), 80);
    run_weighted_graph_fuzz(&fuzzer, fuzzer_get_iterations(300), 80);
    fuzzer_free(&fuzzer);

    printf("Graph Fuzzing completed successfully!\n");
    return 0;
}
