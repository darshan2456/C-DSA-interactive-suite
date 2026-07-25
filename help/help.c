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
        printf("3. Sorting & Searching Help\n");
        printf("4. Graphs & Trees Help\n");
        printf("5. Hashing Help\n");
        printf("6. Advanced & Specialized Topics Help\n");
        printf("7. Error Correction Help\n");
        printf("8. Navigation, CLI Flags & General Info\n");
        int choice;
        int status =
            safe_input_int(&choice, "\nenter choice (\'-1\' to exit, or \'help\') : ", 1, 8);

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
                help_sorting_searching_menu();
                break;
            case 4:
                help_graphs_trees_menu();
                break;
            case 5:
                help_hashing_menu();
                break;
            case 6:
                help_advanced_topics_menu();
                break;
            case 7:
                help_error_correction_menu();
                break;
            case 8:
                display_header("General Navigation, CLI Flags & Commands");
                printf("DESCRIPTION\n");
                printf("    The C DSA Interactive Suite is a terminal-based application\n");
                printf("    designed to help you visualize and interact with Data Structures\n");
                printf("    and Algorithms implemented in C.\n\n");
                printf("NAVIGATION & COMMANDS\n");
                printf("    help               - Launches this help page from any input prompt.\n");
                printf("    -1                 - Exits the current menu, sub-suite, or "
                       "application.\n");
                printf("    Numbers            - Choose specific menu items or menu paths.\n\n");
                printf("CLI ARGUMENTS & FLAGS\n");
                printf("    --profile                  - Enable memory tracking and allocation "
                       "reports.\n");
                printf("    --export-trace             - Enable execution telemetry tracing.\n");
                printf("    --export-trace-path <path> - Specify a target path for trace file "
                       "exports.\n");
                printf("    --load-bst <path>          - Load and visualize a BST from a "
                       "serialized file.\n");
                printf("    --load-avl <path>          - Load and visualize an AVL Tree from a "
                       "serialized file.\n");
                printf("    --load-graph <path>        - Load and print an unweighted Graph from a "
                       "file.\n");
                printf("    --load-wgraph <path>       - Load and print a Weighted Graph from a "
                       "file.\n\n");
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