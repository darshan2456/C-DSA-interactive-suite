#ifndef FUZZER_H
#define FUZZER_H

typedef struct
{
    unsigned int seed;
    int current_op;
    int max_ops;
    char** op_log;
    int log_capacity;
} FuzzerState;

void fuzzer_init(FuzzerState* fuzzer, unsigned int seed, int max_ops);
void fuzzer_free(FuzzerState* fuzzer);
void fuzzer_log_op(FuzzerState* fuzzer, const char* format, ...);
void fuzzer_dump_log(const FuzzerState* fuzzer);
int fuzzer_rand_int(FuzzerState* fuzzer, int min, int max);

// Shared Fuzz Runners
void run_bst_fuzz(FuzzerState* fuzzer, int ops);
void run_avl_fuzz(FuzzerState* fuzzer, int ops);
void run_trie_fuzz(FuzzerState* fuzzer, int ops);

void run_binomial_fuzz(FuzzerState* fuzzer, int ops);
void run_fibonacci_fuzz(FuzzerState* fuzzer, int ops);
void run_minmax_fuzz(FuzzerState* fuzzer, int ops);
void run_leftist_fuzz(FuzzerState* fuzzer, int ops);
void run_skew_fuzz(FuzzerState* fuzzer, int ops);
void run_dary_fuzz(FuzzerState* fuzzer, int ops);
void run_treap_fuzz(FuzzerState* fuzzer, int ops);

void run_unweighted_graph_fuzz(FuzzerState* fuzzer, int num_nodes, int num_edges);
void run_weighted_graph_fuzz(FuzzerState* fuzzer, int num_nodes, int num_edges);

void run_sudoku_fuzz(FuzzerState* fuzzer, int runs);
void run_maze_fuzz(FuzzerState* fuzzer, int runs);

void run_cache_fuzz(FuzzerState* fuzzer, int ops);
void run_hashing_fuzz(FuzzerState* fuzzer, int ops);
void run_string_fuzz(FuzzerState* fuzzer, int ops);
void run_dp_fuzz(FuzzerState* fuzzer, int ops);

void fuzzer_demo(void);

#endif // FUZZER_H
