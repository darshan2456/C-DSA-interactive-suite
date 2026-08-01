#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_trees_menu(void)
{
    display_header("Help - Trees");
    printf("BINARY SEARCH TREE (BST):\n");
    printf("    Node-based binary tree where left child < parent and right child > parent.\n\n");
    printf("AVL TREE:\n");
    printf("    Self-balancing binary search tree where heights of children differ by at "
           "most 1.\n\n");
    printf("TRIE:\n");
    printf("    Search tree used to store associative structures, typically keys are strings.\n\n");
    printf("B-TREE & B+ TREE:\n");
    printf("    Self-balancing search trees optimized for systems that read/write large blocks of "
           "data.\n\n");
    printf("RED-BLACK TREE:\n");
    printf("    Self-balancing BST using node colors (red/black) to guarantee O(log N) "
           "operations.\n\n");
    printf("SPLAY TREE:\n");
    printf("    Self-adjusting BST that moves recently accessed nodes to the root (splaying).\n\n");
    printf("SEGMENT TREE & FENWICK TREE (BIT):\n");
    printf("    Trees for fast range queries (sum, min, max) and point updates in O(log N).\n\n");
    printf("THREADED BINARY TREE:\n");
    printf("    Binary tree where NULL child pointers are reused as \"threads\" to in-order "
           "neighbors,\n");
    printf("    allowing traversal without recursion or a stack.\n\n");
    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
