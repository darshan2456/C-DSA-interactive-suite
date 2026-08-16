#include "display_header.h"
#include "dynamic_programming.h"
#include "safe_input.h"
#include <stdio.h>

void dynamic_programming_demo(void)
{
    int dp_status, dp_choice;
    while (1)
    {
        display_header("Dynamic Programming Algorithms");

        dp_status = safe_input_int(&dp_choice,
                                   "\nenter 1 for 0/1 Knapsack demo"
                                   "\nenter 2 for Longest Common Subsequence (LCS) demo"
                                   "\nenter 3 for Fibonacci sequence demo"
                                   "\nenter 4 for Matrix Chain Multiplication (MCM) demo"
                                   "\nenter 5 for Edit Distance (Levenshtein) demo"
                                   "\nenter 6 for Coin Change demo"
                                   "\nenter 7 for Travelling Salesperson Problem (TSP) demo"
                                   "\nenter 8 for Longest Increasing Subsequence (LIS) demo"
                                   "\nenter choice (\'-1\' to exit, or \'help\') : ",
                                   1, 8);

        if (dp_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Dynamic Programming demo....\n");
            return;
        }

        if (dp_status == 0)
        {
            continue;
        }

        switch (dp_choice)
        {
            case 1:
                display_header("0/1 Knapsack");
                knapsack_demo();
                break;
            case 2:
                display_header("Longest Common Subsequence");
                lcs_demo();
                break;
            case 3:
                display_header("Fibonacci Sequence");
                fibonacci_demo();
                break;
            case 4:
                display_header("Matrix Chain Multiplication");
                mcm_demo();
                break;
            case 5:
                display_header("Edit Distance");
                edit_distance_demo();
                break;
            case 6:
                display_header("Coin Change");
                coin_change_demo();
                break;
            case 7:
                display_header("Travelling Salesperson Problem");
                tsp_demo();
                break;
            case 8:
                display_header("Longest Increasing Subsequence");
                lis_demo();
                break;
        }
    }
}
