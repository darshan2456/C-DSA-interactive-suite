#include <stdio.h>
#include <string.h>

#include "advanced_graph_algorithms.h"
#include "advanced_heaps.h"
#include "advanced_sorting.h"
#include "algorithm_search.h"
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
#include "serialization_demo.h"
#include "sll.h"
#include "sorting_algorithms_n2.h"
#include "stack.h"
#include "step_debugger.h"
#include "string_algorithms.h"
#include "trees.h"
#include "tui.h"

void probabilistic_ds_demo(void);
void spatial_indexing_demo(void);

void run_legacy_menu(void)
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
            "click 6 for hashing algorithms suite demo\n"
            "click 7 for tree data structures & traversals suite demo\n"
            "click 8 for error correction & detection algorithms demo\n"
            "click 9 for OS algorithms (job scheduling & process synchronization) demo\n"
            "click 10 for backtracking algorithms demo\n"
            "click 11 for dynamic programming algorithms demo\n"
            "click 12 for string processing & compression algorithms demo\n"
            "click 13 for advanced heaps & priority queues suite demo\n"
            "click 14 for Bit Manipulation demo\n"
            "click 15 for Developer Console & System Utilities\n"
            "click 16 for Probabilistic Data Structures Module\n"
            "click 17 for Spatial Indexing Module\n"
            "click 18 for Interactive Algorithm Quick-Search Finder\n"
            "\nenter choice (\'-1\' to exit, or \'help\') : ",
            1, 18 /* limits */
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
                while (1)
                {
                    int ds_type;
                    int ds_status =
                        safe_input_int(&ds_type,
                                       "\n--- Core Data Structures ---\n"
                                       "1. Linear Data Structures (SLL, DLL, Array, Queue, PQ)\n"
                                       "2. Circular Data Structures (CQ, SCLL, DCLL, Deque)\n"
                                       "\nenter choice (\'-1\' to exit) : ",
                                       1, 2);
                    if (ds_status == INPUT_EXIT_SIGNAL)
                        break;
                    if (ds_status == 0)
                        continue;

                    if (ds_type == 1)
                    {
                        while (1)
                        {
                            int lin_choice;
                            int lin_status = safe_input_int(&lin_choice,
                                                            "\n--- Linear Data Structures ---\n"
                                                            "1. Singly Linked List\n"
                                                            "2. Doubly Linked List\n"
                                                            "3. Array\n"
                                                            "4. Priority Queue\n"
                                                            "5. Linear Queue\n"
                                                            "\nenter choice (\'-1\' to exit) : ",
                                                            1, 5);
                            if (lin_status == INPUT_EXIT_SIGNAL)
                                break;
                            if (lin_status == 0)
                                continue;
                            if (lin_choice == 1)
                                sll_demo();
                            else if (lin_choice == 2)
                                dll_demo();
                            else if (lin_choice == 3)
                                array_demo();
                            else if (lin_choice == 4)
                                priority_queue_demo();
                            else if (lin_choice == 5)
                                simple_queue_demo();
                        }
                    }
                    else if (ds_type == 2)
                    {
                        while (1)
                        {
                            int circ_choice;
                            int circ_status = safe_input_int(&circ_choice,
                                                             "\n--- Circular Data Structures ---\n"
                                                             "1. Circular Queue\n"
                                                             "2. Singly Circular Linked List\n"
                                                             "3. Doubly Circular Linked List\n"
                                                             "4. Double-ended Queue\n"
                                                             "\nenter choice (\'-1\' to exit) : ",
                                                             1, 4);
                            if (circ_status == INPUT_EXIT_SIGNAL)
                                break;
                            if (circ_status == 0)
                                continue;
                            if (circ_choice == 1)
                                circular_queue_demo();
                            else if (circ_choice == 2)
                                scll_demo();
                            else if (circ_choice == 3)
                                dcll_demo();
                            else if (circ_choice == 4)
                                deque_demo();
                        }
                    }
                }
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
                while (1)
                {
                    int graph_choice;
                    int graph_status = safe_input_int(&graph_choice,
                                                      "\n--- Graph Algorithms ---\n"
                                                      "1. Graph Traversals & Spanning Trees Demo\n"
                                                      "2. Advanced Graph Algorithms Demo\n"
                                                      "\nenter choice (\'-1\' to exit) : ",
                                                      1, 2);
                    if (graph_status == INPUT_EXIT_SIGNAL)
                        break;
                    if (graph_status == 0)
                        continue;
                    if (graph_choice == 1)
                        graph_traversals_demo();
                    else if (graph_choice == 2)
                        advanced_graph_algorithms_demo();
                }
                break;
            case 6:
                hashing_algorithms_demo();
                break;
            case 7:
                trees_demo();
                break;
            case 8:
                error_correction_algorithms_demo();
                break;
            case 9:
                while (1)
                {
                    int os_choice;
                    int os_status =
                        safe_input_int(&os_choice,
                                       "\n--- Operating System Algorithms ---\n"
                                       "1. CPU Job Scheduling Simulators\n"
                                       "2. Process Synchronization Problems (Semaphores / Mutex)\n"
                                       "\nenter choice (\'-1\' to exit) : ",
                                       1, 2);
                    if (os_status == INPUT_EXIT_SIGNAL)
                        break;
                    if (os_status == 0)
                        continue;
                    if (os_choice == 1)
                        job_scheduling_demo();
                    else if (os_choice == 2)
                        process_synchronization_demo();
                }
                break;
            case 10:
                backtracking_demo();
                break;
            case 11:
                dynamic_programming_demo();
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
                bit_manipulation_demo();
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
                                       "5. Cache Replacement Simulator\n"
                                       "6. Stochastic Fuzz Testing Engine\n"
                                       "7. Empirical Big-O Verifier\n"
                                       "8. Standalone File Exporter Engine\n"
                                       "9. State Serialization & Deserialization Engine\n"
                                       "\nenter choice (\'-1\' to exit) : ",
                                       1, 9);
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
                    else if (dev_choice == 5)
                    {
                        display_header("Cache Replacement Simulator");
                        cache_simulator_demo();
                    }
                    else if (dev_choice == 6)
                    {
                        display_header("Stochastic Fuzz Testing Engine");
                        fuzzer_demo();
                    }
                    else if (dev_choice == 7)
                    {
                        display_header("Empirical Big-O Verifier");
                        bigo_verifier_demo();
                    }
                    else if (dev_choice == 8)
                    {
                        display_header("Standalone File Exporter Engine");
                        file_exporter_demo();
                    }
                    else if (dev_choice == 9)
                    {
                        display_header("State Serialization Engine");
                        serialization_demo();
                    }
                }
                break;
            case 16:
                display_header("Probabilistic Data Structures Module");
                probabilistic_ds_demo();
                break;
            case 17:
                display_header("Spatial Indexing Module");
                spatial_indexing_demo();
                break;
            case 18:
                run_algorithm_search_menu();
                break;
        }
    }
}

void tui_menu(void)
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
                tui_run();
                break;
        }
    }
}

int main(void)
{
    tui_menu();
    return 0;
}
