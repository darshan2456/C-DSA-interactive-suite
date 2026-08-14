#include "sorting_telemetry.h"
#include <stdio.h>
#include <string.h>

void sorting_telemetry_init(SortingTelemetry* t, const char* algorithm_name)
{
    if (!t)
        return;
    memset(t, 0, sizeof(SortingTelemetry));
    t->algorithm_name = algorithm_name ? algorithm_name : "Unknown Algorithm";
    t->is_active = false;
}

void sorting_telemetry_reset(SortingTelemetry* t)
{
    if (!t)
        return;
    const char* name = t->algorithm_name;
    memset(t, 0, sizeof(SortingTelemetry));
    t->algorithm_name = name;
}

void sorting_telemetry_start(SortingTelemetry* t)
{
    if (!t)
        return;
    t->is_active = true;
    gettimeofday(&t->start_time, NULL);
}

void sorting_telemetry_stop(SortingTelemetry* t)
{
    if (!t || !t->is_active)
        return;
    gettimeofday(&t->end_time, NULL);
    t->is_active = false;
    double start_us = (double)t->start_time.tv_sec * 1000000.0 + (double)t->start_time.tv_usec;
    double end_us = (double)t->end_time.tv_sec * 1000000.0 + (double)t->end_time.tv_usec;
    t->elapsed_microseconds = end_us - start_us;
}

void sorting_telemetry_add_comparison(SortingTelemetry* t, long long count)
{
    if (t)
    {
        t->comparisons += count;
    }
}

void sorting_telemetry_add_swap(SortingTelemetry* t, long long count)
{
    if (t)
    {
        t->swaps += count;
    }
}

void sorting_telemetry_add_copy(SortingTelemetry* t, long long count)
{
    if (t)
    {
        t->copies += count;
    }
}

void sorting_telemetry_enter_recursion(SortingTelemetry* t)
{
    if (t)
    {
        t->current_recursion_depth++;
        if (t->current_recursion_depth > t->max_recursion_depth)
        {
            t->max_recursion_depth = t->current_recursion_depth;
        }
    }
}

void sorting_telemetry_exit_recursion(SortingTelemetry* t)
{
    if (t && t->current_recursion_depth > 0)
    {
        t->current_recursion_depth--;
    }
}

void sorting_telemetry_add_pass(SortingTelemetry* t, int count)
{
    if (t)
    {
        t->pass_count += count;
    }
}

void sorting_telemetry_print_summary(const SortingTelemetry* t)
{
    if (!t)
        return;
    printf("\n=== Telemetry Summary: %s ===\n", t->algorithm_name);
    printf("  Execution Time      : %.2f us (%.4f ms)\n", t->elapsed_microseconds,
           t->elapsed_microseconds / 1000.0);
    printf("  Comparisons         : %I64d\n", t->comparisons);
    printf("  Swaps               : %I64d\n", t->swaps);
    printf("  Copies/Writes       : %I64d\n", t->copies);
    printf("  Max Recursion Depth : %d\n", t->max_recursion_depth);
    printf("  Pass Count          : %d\n", t->pass_count);
    printf("=======================================\n");
}
