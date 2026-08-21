#include "display_header.h"
#include "dynamic_programming.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 15
#define INF 999999999

void tsp_demo(void)
{
    while (1)
    {
        display_header("TSP using DP with Bitmasking");

        int n;
        int status =
            safe_input_int(&n, "Enter number of cities (1 to 15, or -1 to return): ", -1, MAX_N);

        if (status == INPUT_EXIT_SIGNAL || n == -1)
        {
            printf("\nExiting TSP demo....\n");
            return;
        }

        if (status != 1 || n < 1)
        {
            continue;
        }

        int** dist = malloc(sizeof(int*) * n);
        for (int i = 0; i < n; i++)
        {
            dist[i] = malloc(sizeof(int) * n);
        }

        int choice;
        status = safe_input_int(&choice,
                                "\n1. Enter custom distances\n"
                                "2. Generate random fully-connected graph\nChoice: ",
                                1, 2);

        if (status != 1)
        {
            for (int i = 0; i < n; i++)
            {
                free(dist[i]);
            }
            free(dist);
            continue;
        }

        if (choice == 1)
        {
            printf("\nEnter adjacency matrix (%d x %d). Use 0 for no edge:\n", n, n);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    char prompt[100];
                    snprintf(prompt, sizeof(prompt), "dist[%d][%d]: ", i, j);
                    int val;
                    if (safe_input_int(&val, prompt, 0, 1000000) != 1)
                    {
                        val = 0;
                    }
                    dist[i][j] = val;
                }
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                    {
                        dist[i][j] = 0;
                    }
                    else
                    {
                        dist[i][j] = (rand() % 99) + 1;
                    }
                }
            }
            printf("\nGenerated Adjacency Matrix:\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    printf("%4d ", dist[i][j]);
                }
                printf("\n");
            }
        }

        printf("\nStarting TSP DP + Bitmasking Execution...\n");
        int* path = NULL;
        int cost = solve_tsp(n, dist, &path);

        printf("\n=== TSP Final Result ===\n");
        if (cost >= INF || path == NULL)
        {
            printf("\033[1;31mNo valid Hamiltonian cycle exists (Unreachable).\033[0m\n");
        }
        else
        {
            printf("Minimum Cost Tour: \033[1;32m%d\033[0m\n", cost);
            printf("Optimal Sequence: ");
            for (int i = 0; i <= n; i++)
            {
                printf("%d", path[i]);
                if (i < n)
                {
                    printf(" -> ");
                }
            }
            printf("\n");
        }

        if (path)
        {
            free(path);
        }
        for (int i = 0; i < n; i++)
        {
            free(dist[i]);
        }
        free(dist);

        int cont;
        if (safe_input_int(&cont, "\nPress 1 to continue, -1 to return: ", -1, 1) ==
            INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting TSP demo....\n");
            return;
        }
    }
}
