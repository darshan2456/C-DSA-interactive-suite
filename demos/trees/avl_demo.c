#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "safe_input.h"
#include "serialization.h"
#include "step_debugger.h"

static void scan_avl_nodes(avlNode* root, AlgorithmStateBridge* bridge)
{
    if (root == NULL || bridge->alloc_count >= MAX_TELEMETRY_ALLOCATIONS)
        return;

    int idx = bridge->alloc_count;
    bridge->allocations[idx].address = (void*)root;
    bridge->allocations[idx].size = sizeof(avlNode);
    snprintf(bridge->allocations[idx].label, 31, "Node(%d, H:%d)", root->data, root->height);
    bridge->allocations[idx].active = 1;
    bridge->alloc_count++;

    scan_avl_nodes(root->left, bridge);
    scan_avl_nodes(root->right, bridge);
}

static void update_avl_telemetry(avlNode* root, const char* status)
{
    AlgorithmStateBridge bridge;
    telemetry_bridge_reset("AVL Tree");
    telemetry_bridge_get(&bridge);

    strncpy(bridge.status_message, status, sizeof(bridge.status_message) - 1);

    bridge.var_count = 2;
    strncpy(bridge.variables[0].name, "root", 31);
    snprintf(bridge.variables[0].value, 63, "%p", (void*)root);
    strncpy(bridge.variables[1].name, "height", 31);
    snprintf(bridge.variables[1].value, 63, "%d", root ? root->height : 0);

    scan_avl_nodes(root, &bridge);

    telemetry_bridge_update(&bridge);
}

void avl_demo(void)
{
    while (1)
    {
        printf("\n\nAVL Tree Demo");
        int option;
        int option_status = safe_input_int(&option,
                                           "\n1. Build a new AVL tree\n"
                                           "2. Load AVL tree from file\n"
                                           "\nenter option (or '-1' to exit): ",
                                           1, 2);

        if (option_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting AVL tree demo\n");
            return;
        }
        if (option_status == 0)
        {
            continue;
        }

        avlNode* root = NULL;
        update_avl_telemetry(root, "AVL Tree Initialized Empty");

        if (option == 2)
        {
            char path[256];
            int path_status = safe_input_string(path, sizeof(path), "\nenter filepath to load from:- ");
            if (path_status == INPUT_EXIT_SIGNAL)
            {
                continue;
            }
            root = deserialize_avl_from_file(path);
            if (root == NULL)
            {
                printf("\nfailed to load AVL tree from file.\n");
                continue;
            }
            printf("\nAVL tree loaded successfully from '%s'.\n", path);
            update_avl_telemetry(root, "AVL Tree loaded from file");
            algorithm_step_hook("AVL: Load from File");
        }
        else
        {
            int total_nodes;
            int total_nodes_status =
                safe_input_int(&total_nodes,
                               "\n\nenter total number of nodes you want in the AVL tree, "
                               "(between 1 and 100), enter '-1' to exit:- ",
                               1, 100);

            if (total_nodes_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting AVL tree demo\n");
                return;
            }
            if (total_nodes_status == 0)
            {
                continue;
            }

            int i = 1;
            while (total_nodes > 0)
            {
                int node_value;
                printf("\nenter value of %d AVL node - ", i);
                int node_value_status = safe_input_int(&node_value, NULL, 1, 100);

                if (node_value_status == INPUT_EXIT_SIGNAL)
                {
                    printf("\nExiting AVL tree demo\n");
                    destroy_avl(root);
                    return;
                }
                if (node_value_status == 0)
                {
                    continue;
                }

                int insertion_status = avl_insert(&root, node_value);
                if (insertion_status == 0)
                {
                    printf("\nentered same value. only unique values please");
                    continue;
                }
                if (insertion_status == -1)
                {
                    printf("\ncouldnt insert node due to malloc failure. try again\n");
                    continue;
                }
                i++;
                total_nodes--;

                char status_msg[128];
                snprintf(status_msg, sizeof(status_msg), "Inserted unique value %d", node_value);
                update_avl_telemetry(root, status_msg);
                algorithm_step_hook("AVL: Node Inserted");
            }
        }

        printf("\nheight of the AVL tree is:- %d\n", avl_height(root));

        while (1)
        {
            int traversal_choice;
            int traversal_status =
                safe_input_int(&traversal_choice,
                               "\nenter '1' for inorder, '2' for preorder, "
                               "'3' for postorder, '4' to delete a node, '5' to "
                               "check balance factor, '6' to save to file, and '-1' to exit:- ",
                               1, 6);

            if (traversal_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting AVL tree demo\n");
                destroy_avl(root);
                return;
            }
            if (traversal_status == 0)
            {
                continue;
            }

            if (traversal_choice == 1)
            {
                avl_inorder(root);
                printf("\n");
            }
            else if (traversal_choice == 2)
            {
                avl_preorder(root);
                printf("\n");
            }
            else if (traversal_choice == 3)
            {
                avl_postorder(root);
                printf("\n");
            }
            else if (traversal_choice == 4)
            {
                int delete_value;
                int delete_status;
                bool cancelled = false;
                while (1)
                {
                    delete_status = safe_input_int(
                        &delete_value,
                        "\nenter value to delete (between 1 and 100), enter '-1' to exit:- ", 1,
                        100);
                    if (delete_status == INPUT_EXIT_SIGNAL)
                    {
                        cancelled = true;
                        break;
                    }
                    if (delete_status == 0)
                        continue;
                    break;
                }
                if (cancelled)
                    continue;
                int status = avl_delete(&root, delete_value);
                if (status == 0)
                {
                    printf("\nvalue not found in the tree\n");
                }
                else
                {
                    printf("\nnode deleted. updated inorder traversal: ");
                    avl_inorder(root);
                    printf("\n");

                    char status_msg[128];
                    snprintf(status_msg, sizeof(status_msg), "Deleted value %d", delete_value);
                    update_avl_telemetry(root, status_msg);
                    algorithm_step_hook("AVL: Node Deleted");
                }
            }
            else if (traversal_choice == 5)
            {
                printf("\nbalance factor of root node is: %d\n", avl_balance_factor(root));
            }
            else if (traversal_choice == 6)
            {
                char path[256];
                int path_status = safe_input_string(path, sizeof(path), "\nenter filepath to save to:- ");
                if (path_status != INPUT_EXIT_SIGNAL)
                {
                    if (serialize_avl_to_file(root, path))
                    {
                        printf("\nAVL tree saved successfully to '%s'.\n", path);
                    }
                    else
                    {
                        printf("\nfailed to save AVL tree to file.\n");
                    }
                }
            }
        }
    }
}
