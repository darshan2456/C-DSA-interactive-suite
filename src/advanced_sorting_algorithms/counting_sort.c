#include "advanced_sorting.h"
#include "safe_input.h"
#include "sorting_telemetry.h"
#include "sorting_visualizer.h"
#include "telemetry.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void counting_sort_with_telemetry(int arr[], int n, SortingTelemetry* telemetry)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    if (telemetry)
    {
        sorting_telemetry_init(telemetry, "Counting Sort");
        sorting_telemetry_start(telemetry);
    }
    telemetry_init("counting_sort");

    int min_val = arr[0];
    int max_val = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (telemetry)
        {
            sorting_telemetry_add_comparison(telemetry, 2);
        }
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    if (min_val == max_val)
    {
        telemetry_close();
        if (telemetry)
        {
            sorting_telemetry_stop(telemetry);
        }
        return;
    }

    long long range_ll = (long long)max_val - min_val + 1;
    if (range_ll <= 0 || range_ll > 100000000)
    {
        telemetry_close();
        if (telemetry)
        {
            sorting_telemetry_stop(telemetry);
        }
        return;
    }

    size_t range = (size_t)range_ll;
    int* count = (int*)calloc(range, sizeof(int));
    if (count == NULL)
    {
        telemetry_close();
        if (telemetry)
        {
            sorting_telemetry_stop(telemetry);
        }
        return;
    }

    int* output = (int*)malloc((size_t)n * sizeof(int));
    if (output == NULL)
    {
        free(count);
        telemetry_close();
        if (telemetry)
        {
            sorting_telemetry_stop(telemetry);
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        count[arr[i] - min_val]++;
    }

    for (size_t i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
        if (telemetry)
        {
            sorting_telemetry_add_copy(telemetry, 1);
        }
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
        if (telemetry)
        {
            sorting_telemetry_add_copy(telemetry, 1);
        }
        visualize_sort(arr, n, i, -1, -1, "Counting Sort: Copying sorted elements back");
    }

    free(output);
    free(count);

    telemetry_close();
    if (telemetry)
    {
        sorting_telemetry_stop(telemetry);
    }
}

void counting_sort(int arr[], int n)
{
    counting_sort_with_telemetry(arr, n, NULL);
}
