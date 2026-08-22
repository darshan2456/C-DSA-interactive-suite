#include "fuzzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    unsigned int seed = (unsigned int)time(NULL);
    FuzzerState fuzzer;

    printf("Starting Tree Fuzzing with seed: %u\n", seed);

    printf("--- Running BST Fuzz Tests ---\n");
    fuzzer_init(&fuzzer, seed, 900);
    run_bst_fuzz(&fuzzer, fuzzer_get_iterations(300));
    fuzzer_free(&fuzzer);

    printf("\n--- Running AVL Fuzz Tests ---\n");
    fuzzer_init(&fuzzer, seed, 900);
    run_avl_fuzz(&fuzzer, fuzzer_get_iterations(300));
    fuzzer_free(&fuzzer);

    printf("\n--- Running Trie Fuzz Tests ---\n");
    fuzzer_init(&fuzzer, seed, 900);
    run_trie_fuzz(&fuzzer, fuzzer_get_iterations(300));
    fuzzer_free(&fuzzer);

    printf("Tree Fuzzing completed successfully!\n");
    return 0;
}
