#ifndef HELP_H
#define HELP_H

/**
 * @brief Displays an interactive, Linux man-page style help guide.
 * Bypasses normal input flow until the user exits the guide.
 */
void launch_help_page(void);

/**
 * @brief Sub-menu for Data Structures help.
 */
void help_data_structures_menu(void);

/**
 * @brief Sub-menu for O(N^2) Sorting Algorithms help.
 */
void help_sorting_algorithms_n2_menu(void);

/**
 * @brief Sub-menu for Trees help.
 */
void help_trees_menu(void);

/**
 * @brief Sub-menu for Graph Traversals help.
 */
void help_graph_traversals_menu(void);

/**
 * @brief Sub-menu for Advanced Heaps help.
 */
void help_advanced_heaps_menu(void);

/**
 * @brief Sub-menu for String Algorithms & Compression help.
 */
void help_string_compression_menu(void);

/**
 * @brief Sub-menu for Dynamic Programming help.
 */
void help_dynamic_programming_menu(void);

/**
 * @brief Sub-menu for Expression Evaluation help.
 */
void help_expression_evaluation_menu(void);

/**
 * @brief Sub-menu for Hashing help.
 */
void help_hashing_menu(void);

/**
 * @brief Sub-menu for Error Correction help.
 */
void help_error_correction_menu(void);

/**
 * @brief Sub-menu for Bit Manipulation help.
 */
void bit_manipulation_help(void);

/**
 * @brief Sub-menu for Process Synchronization help.
 */
void help_process_synchronization_menu(void);

/**
 * @brief Sub-menu for Backtracking Algorithms help.
 */
void help_backtracking_menu(void);

/**
 * @brief Sub-menu for Advanced Graph Algorithms & Network Resilience help.
 */
void help_advanced_graphs_menu(void);

/**
 * @brief Sub-menu for Telemetry, Memory Inspector & State Serialization help.
 */
void help_system_utilities_menu(void);

/**
 * @brief Sub-menu for Cache Replacement Simulator help.
 */
void help_cache_simulator_menu(void);

#endif // HELP_H