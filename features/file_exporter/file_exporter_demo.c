#include "display_header.h"
#include "file_exporter.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_exporter_demo(void)
{
    while (1)
    {
        display_header("Standalone File Exporter Engine");
        printf("click 1 for sll export\n");
        printf("click 2 for dll export\n");
        printf("click 3 for binary search tree export\n");
        printf("click 4 for circular queue export\n");
        printf("click 5 for stack export\n");
        printf("click 6 for avl tree export\n");
        printf("click 7 for advanced heaps export\n");
        printf("-1. Return to Main Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 7);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting File Exporter Dashboard...\n");
            return;
        }

        if (status == 0)
        {
            continue;
        }

        char dest_dir[256] = {0};
        int input_res = safe_input_string(
            dest_dir, sizeof(dest_dir), "\nEnter destination directory to export files (e.g. ./exported_files): ");
        if (input_res == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting File Exporter Dashboard...\n");
            return;
        }
        if (strlen(dest_dir) == 0)
        {
            strncpy(dest_dir, "./exported_files", sizeof(dest_dir));
        }

        bool success = false;
        const char* target_name = "";

        switch (choice)
        {
            case 1:
                target_name = "Singly-Linked List (sll.c / sll.h)";
                success = export_sll(".", dest_dir);
                break;
            case 2:
                target_name = "Doubly-Linked List (dll.c / dll.h)";
                success = export_dll(".", dest_dir);
                break;
            case 3:
                target_name = "Binary Search Tree (bst.c / bst.h)";
                success = export_bst(".", dest_dir);
                break;
            case 4:
                target_name = "Circular Queue (circular_queue.c / queue.h)";
                success = export_circular_queue(".", dest_dir);
                break;
            case 5:
                target_name = "Stack (stack.c / stack.h)";
                success = export_stack(".", dest_dir);
                break;
            case 6:
                target_name = "AVL Tree (avl.c / avl.h)";
                success = export_avl(".", dest_dir);
                break;
            case 7:
                target_name = "Advanced Heaps (priority_queue.c / priority_queue.h)";
                success = export_heaps(".", dest_dir);
                break;
        }

        printf("\n------------------------------------------------------------------------\n");
        if (success)
        {
            printf("[SUCCESS] Exported %s to '%s'\n", target_name, dest_dir);
        }
        else
        {
            printf("[FAILED] Could not locate or export %s\n", target_name);
        }
        printf("------------------------------------------------------------------------\n");
    }
}
