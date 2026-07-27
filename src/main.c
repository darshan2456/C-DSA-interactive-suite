#include <stdio.h>
#include <string.h>

#include "advanced_graph_algorithms.h"
#include "advanced_heaps.h"
#include "advanced_sorting.h"
#include "array.h"
#include "backtracking.h"
#include "benchmark.h"
#include "bigo_verifier.h"
#include "bit_manipulation.h"
#include "cache.h"
#include "compression.h"
#include "config.h"
#include "dcll.h"
#include "display_header.h"
#include "dll.h"
#include "dynamic_programming.h"
#include "error_correction_algorithms.h"
#include "expression.h"
#include "file_exporter.h"
#include "fuzzer.h"
#include "graph_traversals.h"
#include "hash.h"
#include "job_scheduling.h"
#include "memory_inspector.h"
#include "memory_tracker.h"
#include "priority_queue.h"
#include "process_synchronization.h"
#include "queue.h"
#include "safe_input.h"
#include "scll.h"
#include "searching_algorithms.h"
#include "serialization.h"
#include "sll.h"
#include "sorting_algorithms_n2.h"
#include "stack.h"
#include "step_debugger.h"
#include "string_algorithms.h"
#include "trees.h"

void run_legacy_menu()
{
    while (1)
    {
        int choice;
        int status = safe_input_int(
            &choice,
            "\nWelcome to DSA library built by Darshan Mukul Parekh"
            "\n(at any point enter '-1' to exit that particular demo, or 'help' for manual)\n\n"
            "click 1 for core data structures demo\n"
            "click 2 for expression evaluation & parsing demo\n"
            "click 3 for sorting algorithms suite demo\n"
            "click 4 for searching algorithms suite demo\n"
            "click 5 for graph traversals & shortest path suite demo\n"
            "click 6 for advanced graph algorithms suite demo\n"
            "click 7 for tree data structures & traversals suite demo\n"
            "click 8 for dynamic programming algorithms demo\n"
            "click 9 for backtracking algorithms demo\n"
            "click 10 for error correction & detection algorithms demo\n"
            "click 11 for job scheduling algorithms demo\n"
            "click 12 for string processing & compression algorithms demo\n"
            "click 13 for advanced heaps & priority queues suite demo\n"
            "click 14 for cache replacement simulator demo\n"
            "click 15 for Developer Console & System Utilities\n"
            "click 16 for Stochastic Fuzz Testing Engine demo\n"
            "click 17 for Empirical Asymptotic Complexity Verifier (Big-O Engine) demo\n"
            "click 18 for Bit Manipulation demo\n"
            "click 19 for Standalone File Exporter Engine demo\n"
            "\nenter choice (\'-1\' to exit, or \'help\') : ",
            1, 19 /* limits */
        );

        if (status == INPUT_EXIT_SIGNAL)
        {
            break;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                // data structures
                break;
            case 2:
                expression_evaluation_demo();
                break;
            case 3:
                while (1)
                {
                    int sort_choice;
                    int sort_status = safe_input_int(&sort_choice,
                                                     "\n--- Sorting Algorithms ---\n"
                                                     "1. O(N^2) Sorting Algorithms Demo\n"
                                                     "2. Advanced Sorting Algorithms Demo\n"
                                                     "\nenter choice (\'-1\' to exit) : ",
                                                     1, 2);
                    if (sort_status == INPUT_EXIT_SIGNAL)
                        break;
                    if (sort_status == 0)
                        continue;
                    if (sort_choice == 1)
                        sorting_algorithms_n2_demo();
                    else if (sort_choice == 2)
                        advanced_sorting_demo();
                }
                break;
            case 4:
                searching_algorithms_demo();
                break;
            case 5:
                graph_traversals_demo();
                break;
            case 6:
                advanced_graph_algorithms_demo();
                break;
            case 7:
                trees_demo();
                break;
            case 8:
                dynamic_programming_demo();
                break;
            case 9:
                backtracking_demo();
                break;
            case 10:
                error_correction_algorithms_demo();
                break;
            case 11:
                job_scheduling_demo();
                break;
            case 12:
                while (1)
                {
                    int string_choice;
                    int string_status = safe_input_int(&string_choice,
                                                       "\n--- String & Compression Suite ---\n"
                                                       "1. String Pattern Matching Demos\n"
                                                       "2. String Compression & Encoding Demos\n"
                                                       "\nenter choice (\'-1\' to exit) : ",
                                                       1, 2);
                    if (string_status == INPUT_EXIT_SIGNAL)
                        break;
                    if (string_status == 0)
                        continue;
                    if (string_choice == 1)
                        string_algorithms_demo();
                    else if (string_choice == 2)
                        compression_demo();
                }
                break;
            case 13:
                advanced_heaps_demo();
                break;
            case 14:
                cache_simulator_demo();
                break;
            case 15:
                while (1)
                {
                    int dev_choice;
                    int dev_status =
                        safe_input_int(&dev_choice,
                                       "\n--- Developer Console & System Utilities ---\n"
                                       "1. Algorithm Benchmarking & Comparative Profiling\n"
                                       "2. Interactive Step-Debugger\n"
                                       "3. Raw Memory Layout Inspector / Hexdump Visualizer\n"
                                       "4. System Settings (Animation Speed, Debugger toggles)\n"
                                       "\nenter choice (\'-1\' to exit) : ",
                                       1, 4);
                    if (dev_status == INPUT_EXIT_SIGNAL)
                        break;
                    if (dev_status == 0)
                        continue;
                    if (dev_choice == 1)
                    {
                        display_header("Algorithm Benchmarking & Profiling");
                        benchmark_menu_demo();
                    }
                    else if (dev_choice == 2)
                        debugger_demo();
                    else if (dev_choice == 3)
                    {
                        display_header("Raw Memory Layout Inspector");
                        memory_inspector_demo();
                    }
                    else if (dev_choice == 4)
                    {
                        display_header("Settings");
                        settings_menu_demo();
                    }
                }
                break;
            case 16:
                display_header("Stochastic Fuzz Testing Engine");
                fuzzer_demo();
                break;
            case 17:
                display_header("Empirical Big-O Verifier");
                bigo_verifier_demo();
                break;
            case 18:
                bit_manipulation_demo();
                break;
            case 19:
                display_header("Standalone File Exporter Engine");
                file_exporter_demo();
                break;
        }
    }
}

void tui_menu()
{
    while (1)
    {
        int choice;
        int status = safe_input_int(
            &choice,
            "\nWelcome to DSA library built by Darshan Mukul Parekh"
            "\n(at any point enter '-1' to exit that particular demo, or 'help' for manual)\n\n"
            "click 1 for legacy menu\n"
            "click 2 for tui menu\n"
            "\nenter choice (\'-1\' to exit, or \'help\') : ",
            1, 2 // limits
        );

        if (status == INPUT_EXIT_SIGNAL)
        {
            break;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                run_legacy_menu();
                break;
            case 2:
                // future menu
                break;
        }
    }
}

int main(void)
{
    tui_menu();
    return 0;
}
