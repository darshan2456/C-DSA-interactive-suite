#include "dynamic_programming.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Calculates the Longest Increasing Subsequence of an array using Dynamic Programming.
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 *
 * @param arr The input array of integers
 * @param n   The size of the input array
 * @return    The length of the Longest Increasing Subsequence
 */
int lis(const int arr[], int n)
{
    if (arr == NULL || n <= 0)
    {
        return 0;
    }

    int* dp = (int*)malloc(n * sizeof(int));
    if (dp == NULL)
    {
        printf("Memory allocation failed for DP array in lis().\n");
        return -1;
    }

    // Initialize all DP values to 1, as the minimum LIS ending at any element is 1 (the element
    // itself)
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    // Build the DP array from left to right
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }
    }

    // Find the maximum value in the DP array
    int max_lis = 0;
    for (int i = 0; i < n; i++)
    {
        if (dp[i] > max_lis)
        {
            max_lis = dp[i];
        }
    }

    free(dp);
    return max_lis;
}
