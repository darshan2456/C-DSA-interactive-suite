#include "advanced_sorting.h"
#include "safe_input.h"
#include "sorting_telemetry.h"
#include "sorting_visualizer.h"
#include "telemetry.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int get_max(int arr[], int n, SortingTelemetry* telemetry)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        sorting_telemetry_add_comparison(telemetry, 1);
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

static void radix_counting_sort(int arr[], int n, int exp, SortingTelemetry* telemetry)
{
    int* output = malloc(sizeof(int) * n);
    if (output == NULL)
    {
        return;
    }
    int count[10] = {0};

    for (int i = 0; i < n; i++)
    {
        int digit = abs((arr[i] / exp) % 10);
        count[digit]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = abs((arr[i] / exp) % 10);
        output[count[digit] - 1] = arr[i];
        sorting_telemetry_add_copy(telemetry, 1);
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
        sorting_telemetry_add_copy(telemetry, 1);
        visualize_sort(arr, n, i, -1, -1, "Radix Sort: Copying elements back after digit-sorting");
    }

    free(output);
}

void radix_sort_with_telemetry(int arr[], int n, SortingTelemetry* telemetry)
{
    if (n <= 1)
    {
        return;
    }

    if (telemetry)
    {
        sorting_telemetry_init(telemetry, "Radix Sort");
        sorting_telemetry_start(telemetry);
    }
    telemetry_init("radix_sort");

    int* neg = malloc(sizeof(int) * n);
    int* pos = malloc(sizeof(int) * n);
    if (!neg || !pos)
    {
        if (neg)
            free(neg);
        if (pos)
            free(pos);
        telemetry_close();
        if (telemetry)
            sorting_telemetry_stop(telemetry);
        return;
    }

    int neg_cnt = 0, pos_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            neg[neg_cnt++] = -arr[i];
        }
        else
        {
            pos[pos_cnt++] = arr[i];
        }
    }

    if (neg_cnt > 0)
    {
        int max_neg = get_max(neg, neg_cnt, telemetry);
        for (int exp = 1; max_neg / exp > 0; exp *= 10)
        {
            sorting_telemetry_add_pass(telemetry, 1);
            radix_counting_sort(neg, neg_cnt, exp, telemetry);
        }
    }

    if (pos_cnt > 0)
    {
        int max_pos = get_max(pos, pos_cnt, telemetry);
        for (int exp = 1; max_pos / exp > 0; exp *= 10)
        {
            sorting_telemetry_add_pass(telemetry, 1);
            radix_counting_sort(pos, pos_cnt, exp, telemetry);
        }
    }

    for (int i = 0; i < neg_cnt; i++)
    {
        arr[i] = -neg[neg_cnt - 1 - i];
        if (telemetry)
            sorting_telemetry_add_copy(telemetry, 1);
        visualize_sort(arr, n, i, -1, -1, "Radix Sort: Restoring negative elements");
    }

    for (int i = 0; i < pos_cnt; i++)
    {
        arr[neg_cnt + i] = pos[i];
        if (telemetry)
            sorting_telemetry_add_copy(telemetry, 1);
        visualize_sort(arr, n, neg_cnt + i, -1, -1, "Radix Sort: Restoring positive elements");
    }

    free(neg);
    free(pos);

    telemetry_close();
    if (telemetry)
    {
        sorting_telemetry_stop(telemetry);
    }
}

void radix_sort(int arr[], int n)
{
    radix_sort_with_telemetry(arr, n, NULL);
}
