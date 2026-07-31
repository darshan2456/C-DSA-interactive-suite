#include "clear_screen.h"
#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

static void display_telemetry_help(void)
{
    clear_screen();
    display_header("MANUAL: Telemetry & Memory Profiler Engine");
    printf("\n"
           "================================================================================\n"
           " 1. SORTING TELEMETRY DASHBOARD\n"
           "================================================================================\n"
           " Concept:\n"
           "   Tracks real-time algorithmic operations, comparisons, swaps, and execution\n"
           "   timers.\n"
           "   - Features: Real-time swap counters, time-series metrics, comparative\n"
           "     dashboards.\n\n"
           "================================================================================\n"
           " 2. MEMORY INSPECTOR & PROFILER\n"
           "================================================================================\n"
           " Concept:\n"
           "   Intercepts malloc/free allocations to audit heap usage and detect memory leaks.\n"
           "   - Features: Active allocation tracking, byte leakage alerts, pointer\n"
           "     inspection.\n\n"
           " Press [ENTER] to return to System Utilities Help Menu...");
    getchar();
}

static void display_serialization_help(void)
{
    clear_screen();
    display_header("MANUAL: State Serialization & Persistence Engine");
    printf("\n"
           "================================================================================\n"
           " STATE SERIALIZATION & DESERIALIZATION\n"
           "================================================================================\n"
           " Concept:\n"
           "   Serializes live in-memory data structures (BST, AVL Trees, Graphs) to binary\n"
           "   payload files on disk and restores exact state during application execution.\n"
           "   - Supported Structures: Binary Search Trees, AVL Trees, Weighted Graphs.\n"
           "   - Data Integrity: Checksum-verified binary payloads.\n\n"
           " Press [ENTER] to return to System Utilities Help Menu...");
    getchar();
}

static void display_diagnostics_help(void)
{
    clear_screen();
    display_header("MANUAL: Developer Utilities & Diagnostics");
    printf("\n"
           "================================================================================\n"
           " 1. STOCHASTIC FUZZ TESTING ENGINE\n"
           "================================================================================\n"
           " Concept:\n"
           "   Bombards algorithms with randomized, edge-case inputs to verify robust constraint\n"
           "   handling and uncover unexpected segfaults.\n\n"
           "================================================================================\n"
           " 2. EMPIRICAL BIG-O VERIFIER\n"
           "================================================================================\n"
           " Concept:\n"
           "   Runs algorithms against scaling dataset sizes (e.g., 10^2 to 10^6) and curves\n"
           "   the runtime mathematically to empirically prove O(N log N), O(N^2), etc.\n\n"
           "================================================================================\n"
           " 3. STANDALONE FILE EXPORTER\n"
           "================================================================================\n"
           " Concept:\n"
           "   Exports internal arrays, graphs, or trees to .csv or .md files for external\n"
           "   analysis and cross-referencing.\n\n"
           " HOW TO RUN IN THIS SUITE:\n"
           "   Main Menu ➔ Option 19 (System Utilities & Diagnostics)\n\n"
           " Press [ENTER] to return to System Utilities Help Menu...");
    getchar();
}

static void display_benchmarking_help(void)
{
    clear_screen();
    display_header("Help - Benchmarking & Profiling");
    printf("\n"
           "================================================================================\n"
           " ALGORITHM BENCHMARKING & PROFILING\n"
           "================================================================================\n"
           " Concept:\n"
           "   Measures and compares execution time, memory usage, or operational\n"
           "   efficiency across different algorithms under uniform conditions.\n\n"
           " CONFIGURATION SETTINGS:\n"
           "   • Iterations: Define how many times each algorithm is executed to calculate\n"
           "                 an accurate average time (mitigates CPU spike anomalies).\n"
           "   • Export Format: Save the benchmark results to external report files in CSV,\n"
           "                    Markdown, or JSON formats.\n\n"
           " BENCHMARK SUITES:\n"
           "   1. Sorting Algorithms           8. Hash Map Collision Resolution\n"
           "   2. Searching Algorithms         9. Trees Lookup Performance\n"
           "   3. Graph Shortest Paths         10. Backtracking Algorithms\n"
           "   4. Minimum Spanning Trees (MST) 11. Network Flow Algorithms\n"
           "   5. Job Scheduling               12. Advanced Heaps\n"
           "   6. String Matching              13. Cache Replacement Simulator\n"
           "   7. DP vs Naive Recursion        14. Compression & Encoding\n\n"
           " HOW TO RUN IN THIS SUITE:\n"
           "   Main Menu ➔ Option 15 (Benchmarking Suite)\n\n"
           " Press [ENTER] to return to System Utilities Help Menu...");
    getchar();
}

void help_system_utilities_menu(void)
{
    while (1)
    {
        clear_screen();
        display_header("Help: System Utilities, Telemetry & Serialization");

        int choice;
        int status = safe_input_int(&choice,
                                    "\nSystem Utilities Topics:\n"
                                    "------------------------\n"
                                    "1. Sorting Telemetry & Memory Profiler Engine\n"
                                    "2. State Serialization & Binary Disk Persistence\n"
                                    "3. Developer Diagnostics (Fuzzing, Big-O, Exporter)\n"
                                    "4. Algorithm Benchmarking & Profiling\n"
                                    "\nenter choice ('-1' to return): ",
                                    1, 4);

        if (status == INPUT_EXIT_SIGNAL)
        {
            return;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                display_telemetry_help();
                break;
            case 2:
                display_serialization_help();
                break;
            case 3:
                display_diagnostics_help();
                break;
            case 4:
                display_benchmarking_help();
                break;
        }
    }
}
