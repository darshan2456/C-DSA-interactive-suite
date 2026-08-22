#include "../../features/fuzzy_tester/fuzzer.h"
#include "../../src/dynamic_programming/dynamic_programming.h"
#include <stdlib.h>
#include <string.h>

static void generate_random_string(FuzzerState* fuzzer, char** str, int* length, int max_len)
{
    *length = fuzzer_rand_int(fuzzer, 0, max_len);
    *str = (char*)malloc(*length + 1);
    if (*str != NULL)
    {
        for (int i = 0; i < *length; i++)
        {
            (*str)[i] = (char)fuzzer_rand_int(fuzzer, 65, 90);
        }
        (*str)[*length] = '\0';
    }
}

static int* generate_random_array(FuzzerState* fuzzer, int n, int min_val, int max_val)
{
    if (n <= 0)
    {
        return NULL;
    }
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            arr[i] = fuzzer_rand_int(fuzzer, min_val, max_val);
        }
    }
    return arr;
}

static int** generate_random_matrix(FuzzerState* fuzzer, int n, int min_val, int max_val)
{
    if (n <= 0)
    {
        return NULL;
    }
    int** mat = (int**)malloc(n * sizeof(int*));
    if (mat != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            mat[i] = generate_random_array(fuzzer, n, min_val, max_val);
        }
    }
    return mat;
}

static void free_matrix(int** mat, int n)
{
    if (mat == NULL)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (mat[i] != NULL)
        {
            free(mat[i]);
        }
    }
    free(mat);
}

void run_dp_fuzz(FuzzerState* fuzzer, int ops)
{
    fuzzer_log_op(fuzzer, "--- Starting DP Fuzz Test (%d ops) ---", ops);

    for (int i = 0; i < ops; i++)
    {
        int algo_choice = fuzzer_rand_int(fuzzer, 0, 6);

        if (algo_choice == 0)
        {
            int n = fuzzer_rand_int(fuzzer, 0, 100);
            int W = fuzzer_rand_int(fuzzer, 0, 500);
            int* wt = generate_random_array(fuzzer, n, 1, 50);
            int* val = generate_random_array(fuzzer, n, 1, 100);
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing Knapsack (n=%d, W=%d)", i, n, W);
            knapsack(W, wt, val, n);
            if (wt != NULL)
            {
                free(wt);
            }
            if (val != NULL)
            {
                free(val);
            }
        }
        else if (algo_choice == 1)
        {
            char *X = NULL, *Y = NULL;
            int m = 0, n = 0;
            generate_random_string(fuzzer, &X, &m, 100);
            generate_random_string(fuzzer, &Y, &n, 100);
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing LCS and Edit Distance (m=%d, n=%d)", i, m, n);
            if (X != NULL && Y != NULL)
            {
                lcs(X, Y, m, n);
                edit_distance(X, Y, m, n);
            }
            if (X != NULL)
            {
                free(X);
            }
            if (Y != NULL)
            {
                free(Y);
            }
        }
        else if (algo_choice == 2)
        {
            int n = fuzzer_rand_int(fuzzer, -5, 40);
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing Fibonacci (n=%d)", i, n);
            fibonacci_iterative(n);
        }
        else if (algo_choice == 3)
        {
            int n = fuzzer_rand_int(fuzzer, 1, 50);
            int* p = generate_random_array(fuzzer, n, 1, 100);
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing Matrix Chain Order (n=%d)", i, n);
            if (p != NULL)
            {
                matrix_chain_order(p, n);
                free(p);
            }
        }
        else if (algo_choice == 4)
        {
            int n = fuzzer_rand_int(fuzzer, 1, 20);
            int amount = fuzzer_rand_int(fuzzer, 0, 500);
            int* coins = generate_random_array(fuzzer, n, 1, 50);
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing Coin Change (n=%d, amount=%d)", i, n, amount);
            if (coins != NULL)
            {
                coin_change_min_coins(coins, n, amount);
                coin_change_ways(coins, n, amount);
                free(coins);
            }
        }
        else if (algo_choice == 5)
        {
            int n = fuzzer_rand_int(fuzzer, 1, 10);
            int** dist = generate_random_matrix(fuzzer, n, 1, 100);
            int* path_out = NULL;
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing TSP (n=%d)", i, n);
            if (dist != NULL)
            {
                solve_tsp(n, dist, &path_out);
                if (path_out != NULL)
                {
                    free(path_out);
                }
                free_matrix(dist, n);
            }
        }
        else if (algo_choice == 6)
        {
            int n = fuzzer_rand_int(fuzzer, 0, 200);
            int* arr = generate_random_array(fuzzer, n, -100, 100);
            fuzzer_log_op(fuzzer, "Op %d: Fuzzing LIS (n=%d)", i, n);
            if (arr != NULL)
            {
                lis(arr, n);
                free(arr);
            }
        }
    }
    fuzzer_log_op(fuzzer, "--- DP Fuzz Test Complete ---");
}

int main(void)
{
    FuzzerState fuzzer;
    fuzzer_init(&fuzzer, 42, fuzzer_get_iterations(300));
    run_dp_fuzz(&fuzzer, fuzzer_get_iterations(300));
    fuzzer_free(&fuzzer);
    return 0;
}
