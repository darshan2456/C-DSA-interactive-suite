#include "help.h"
#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>

static void print_help_banner(void)
{
    printf("\033[1;33m"); /* Bold yellow */
    printf("  ██╗  ██╗███████╗██╗     ██████╗      \n");
    printf("  ██║  ██║██╔════╝██║     ██╔══██╗     \n");
    printf("  ███████║█████╗  ██║     ██████╔╝     \n");
    printf("  ██╔══██║██╔══╝  ██║     ██╔═══╝      \n");
    printf("  ██║  ██║███████╗███████╗██║          \n");
    printf("  ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝          \n");
    printf("\033[0;36m");
    printf("  ███╗   ███╗ █████╗ ███╗   ██╗██╗   ██╗ █████╗ ██╗     \n");
    printf("  ████╗ ████║██╔══██╗████╗  ██║██║   ██║██╔══██╗██║     \n");
    printf("  ██╔████╔██║███████║██╔██╗ ██║██║   ██║███████║██║     \n");
    printf("  ██║╚██╔╝██║██╔══██║██║╚██╗██║██║   ██║██╔══██║██║     \n");
    printf("  ██║ ╚═╝ ██║██║  ██║██║ ╚████║╚██████╔╝██║  ██║███████╗\n");
    printf("  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝\n");
    printf("\033[0m");
    printf("\033[90m  Your interactive guide to Data Structures & Algorithms in C.\033[0m\n\n");
}

void launch_help_page(void)
{
    static int in_help = 0;
    if (in_help)
    {
        printf("\n[Notice] You are already inside the Help Manual.\n");
        return;
    }
    in_help = 1;

    while (1)
    {
        display_header("C DSA INTERACTIVE SUITE - HELP MANUAL");
        print_help_banner();

        printf("\033[1mSelect a module to view its help page:\033[0m\n\n");
        printf("1. Data Structures Help\n");
        printf("2. Expression Evaluation Help\n");
        printf("3. O(N^2) Sorting Algorithms Help\n");
        printf("4. Advanced Sorting Algorithms Help\n");
        printf("5. Searching Algorithms Help\n");
        printf("6. Trees Help\n");
        printf("7. Graph Traversals Help\n");
        printf("8. Advanced Heaps Help\n");
        printf("9. Hashing Help\n");
        printf("10. String Algorithms & Compression Help\n");
        printf("11. Dynamic Programming Help\n");
        printf("12. Spatial Indexing Help\n");
        printf("13. Probabilistic Data Structures Help\n");
        printf("14. Error Correction Help\n");
        printf("15. Bit Manipulation Help\n");
        printf("16. Process Synchronization Help\n");
        printf("17. Job Scheduling Help\n");
        printf("18. Backtracking Algorithms Help\n");
        printf("19. Advanced Graph Algorithms & Network Resilience Help\n");
        printf("20. System Utilities, Telemetry & Serialization Help\n");
        printf("21. Cache Replacement Simulator Help\n");
        printf("22. Navigation, CLI Flags & General Info\n");

        int choice;
        int status =
            safe_input_int(&choice, "\nenter choice (\'-1\' to exit, or \'help\') : ", 1, 22);

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
                help_data_structures_menu();
                break;
            case 2:
                help_expression_evaluation_menu();
                break;
            case 3:
                help_sorting_algorithms_n2_menu();
                break;
            case 4:
                help_advanced_sorting_algorithms_menu();
                break;
            case 5:
                help_searching_algorithms_menu();
                break;
            case 6:
                help_trees_menu();
                break;
            case 7:
                help_graph_traversals_menu();
                break;
            case 8:
                help_advanced_heaps_menu();
                break;
            case 9:
                help_hashing_menu();
                break;
            case 10:
                help_string_compression_menu();
                break;
            case 11:
                help_bit_manipulation_menu();
                break;
            case 12:
                help_spatial_indexing_menu();
                break;
            case 13:
                help_probabilistic_data_structures_menu();
                break;
            case 14:
                help_advanced_graph_algorithms_menu();
                break;
            case 15:
                help_bit_manipulation_menu();
                break;
            case 16:
                help_process_synchronization_menu();
                break;
            case 17:
                help_job_scheduling_menu();
                break;
            case 18:
                help_backtracking_menu();
                break;
            case 19:
                help_advanced_graph_algorithms_menu();
                break;
            case 20:
                help_system_utilities_menu();
                break;
            case 21:
                help_cache_simulator_menu();
                break;
            case 22:
                display_header("General Navigation, CLI Flags & Commands");
                printf("DESCRIPTION\n");
                printf("    The C DSA Interactive Suite is a terminal-based application\n");
                printf("    designed to help you visualize and interact with Data Structures\n");
                printf("    and Algorithms implemented in C.\n\n");
                printf("NAVIGATION & COMMANDS\n");
                printf("    help               - Launches this help page from any input prompt.\n");
                printf("    -1                 - Exits the current menu, sub-suite, or app.\n");
                printf("    Numbers            - Choose specific menu items or menu paths.\n\n");
                printf("CLI ARGUMENTS & FLAGS\n");
                printf("    --profile                  - Enable memory tracking reports.\n");
                printf("    --export-trace             - Enable execution telemetry tracing.\n");
                printf("    --export-trace-path <path> - Target path for trace file exports.\n");
                printf("    --load-bst <path>          - Load a BST from a serialized file.\n");
                printf("    --load-avl <path>          - Load an AVL from a serialized file.\n");
                printf("    --load-graph <path>        - Load an unweighted Graph from file.\n");
                printf("    --load-wgraph <path>       - Load a Weighted Graph from file.\n\n");
                printf("=================================================================\n");
                printf("Press [ENTER] to return to the main help menu...\n");
                printf("=================================================================\n");
                press_enter_to_continue();
                break;
        }
    }

    in_help = 0;
    /* Clear screen again to restore the clean look of the app menu. */
    printf("\033[H\033[2J");
}