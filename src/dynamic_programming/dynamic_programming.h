#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

void dynamic_programming_demo(void);

void knapsack_demo(void);
int knapsack(int W, int wt[], int val[], int n);

void lcs_demo(void);
int lcs(char* X, char* Y, int m, int n);

void fibonacci_demo(void);
long long fibonacci_recursive(int n, long long memo[]);
long long fibonacci_iterative(int n);

int matrix_chain_order(int p[], int n);
void mcm_demo(void);

void edit_distance_demo(void);
int edit_distance(char* word1, char* word2, int m, int n);

void coin_change_demo(void);
int coin_change_min_coins(int coins[], int n, int amount);
int coin_change_ways(int coins[], int n, int amount);

void tsp_demo(void);
int tsp_dp(int mask, int pos, int n, int** dist, int** memo);
int* reconstruct_tsp_path(int n, int** dist, int** memo, int min_cost);
int solve_tsp(int n, int** dist, int** path_out);

int lis(const int arr[], int n);
void lis_demo(void);

#endif // DYNAMIC_PROGRAMMING_H
