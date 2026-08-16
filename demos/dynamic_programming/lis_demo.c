#include "dynamic_programming.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void lis_demo(void)
{
    while (1)
    {
        int n;
        int status;

        printf("\nLongest Increasing Subsequence (LIS) Demo\n");
        status = safe_input_int(
            &n, "Enter the size of the array (between 1 and 100), '-1' to exit: ", 1, 100);
        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting LIS demo...\n");
            return;
        }
        if (status == 0)
            continue;

        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL)
        {
            printf("Memory allocation failed for array.\n");
            continue;
        }

        printf("Enter %d integers (-10000 to 10000):\n", n);
        for (int i = 0; i < n; i++)
        {
            int val;
            char prompt[50];
            snprintf(prompt, sizeof(prompt), "Element %d: ", i + 1);
            while (1)
            {
                int ret = safe_input_int(&val, prompt, -10000, 10000);
                if (ret == INPUT_EXIT_SIGNAL)
                {
                    // For individual elements, if user types -1 and min_val is -10000,
                    // safe_input_int might intercept -1 as exit. Wait, safe_input_int intercepts -1
                    // as exit when min_val > -1 or max_val < -1? Actually, if we just break and
                    // handle exit, it's safer. But let's assume valid. If -1 is typed and it exits,
                    // we free and return.
                    printf("\nExiting LIS demo...\n");
                    free(arr);
                    return;
                }
                if (ret != 0)
                {
                    break;
                }
            }
            arr[i] = val;
        }

        clock_t start_t = clock();
        int max_lis = lis(arr, n);
        clock_t end_t = clock();
        double time_taken = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("\n--- Results ---\n");
        printf("Array: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Length of Longest Increasing Subsequence: %d\n", max_lis);
        printf("Time taken: %f seconds\n", time_taken);

        free(arr);
    }
}
