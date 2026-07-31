#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_advanced_heaps_menu(void)
{
    display_header("Help - Advanced Heaps");
    printf("D-ARY HEAP:\n");
    printf("    A generalization of a binary heap where each node has D children.\n");
    printf("    - Formula: Parent of index i is (i-1)/D. Children are D*i+1 to D*i+D.\n");
    printf("    - Trade-offs: Speeds up decrease-key operations; slows down "
           "delete-min.\n\n");

    printf("MIN-MAX HEAP:\n");
    printf("    A double-ended priority queue implemented using a binary heap "
           "structure.\n");
    printf("    - Concept: Even levels are Min levels; odd levels are Max levels.\n");
    printf("    - Capabilities: Allows both find-min and find-max in O(1), and pop-min\n");
    printf("      and pop-max in O(log N).\n\n");

    printf("LEFTIST & SKEW HEAPS:\n");
    printf("    - Leftist Heap: A mergeable binary heap where the null path length "
           "(npl)\n");
    printf("      of the left child is always >= that of the right child.\n");
    printf("    - Skew Heap: A self-adjusting version of leftist heap that "
           "unconditionally\n");
    printf("      swaps children during merge (no need to track or compute "
           "balance/npl).\n");
    printf("    - Key Property: Both support O(log N) merge operations.\n\n");

    printf("BINOMIAL HEAP:\n");
    printf("    A collection of binomial trees where each tree satisfies the heap "
           "property\n");
    printf("    and there is at most one binomial tree of any given degree k.\n");
    printf("    - Key Property: Supports O(log N) merge, insert, and extract-min "
           "operations.\n\n");

    printf("FIBONACCI HEAP:\n");
    printf("    A mergeable heap structure optimized for amortized running times.\n");
    printf("    - Amortized Times: O(1) for Insert, Find-Min, Decrease-Key, and Merge.\n");
    printf("      O(log N) for Extract-Min and Delete.\n");
    printf("    - Use Case: Crucial for Dijkstra and Prim algorithms on sparse "
           "graphs.\n\n");

    printf("TREAP:\n");
    printf("    A randomized binary search tree that satisfies both the BST property\n");
    printf("    (on keys) and the Heap property (on randomly assigned priorities).\n");
    printf("    - Key Property: Balanced with high probability, supporting O(log N) "
           "operations.\n\n");

    printf("RELATIONSHIPS BETWEEN HEAPS:\n");
    printf("    • D-Ary vs. Binary Heap:\n");
    printf("      Binary heap is a 2-Ary heap. D-Ary heap generalizes this to D "
           "children.\n");
    printf("    • Leftist vs. Skew:\n");
    printf("      Leftist heap enforces structure using null path length (npl) balance\n");
    printf("      conditions. Skew heap is the self-adjusting version that swaps "
           "children\n");
    printf("      unconditionally, avoiding tracking node state.\n");
    printf("    • Binomial vs. Fibonacci:\n");
    printf("      Binomial heap enforces eager, immediate tree merges. Fibonacci heap\n");
    printf("      implements lazy, delayed merges, postponing sorting/restructuring\n");
    printf("      until extract-min is called (giving it O(1) "
           "insert/merge/decrease-key).\n");
    printf("    • Treap vs. BST:\n");
    printf("      Treap uses randomized priorities to act as a self-balancing BST "
           "without\n");
    printf("      the complex balancing logic of AVL or Red-Black trees.\n\n");

    printf("WHEN TO USE WHAT & REAL-WORLD USE CASES:\n");
    printf("    • Use D-Ary Heap when memory access is a bottleneck (cache-friendly "
           "index\n");
    printf("      layout) or when decrease-key operations outnumber delete-min.\n");
    printf("      - Real-world: External memory databases, network routing tables.\n");
    printf("    • Use Min-Max Heap when double-ended priority access is needed.\n");
    printf("      - Real-world: Job schedulers prioritizing highest and lowest "
           "processes.\n");
    printf("    • Use Leftist / Skew Heaps when merge operations are frequent.\n");
    printf("      - Real-world: Discrete event simulation systems, lazy evaluations.\n");
    printf("    • Use Fibonacci Heap when implementing priority queues in shortest "
           "path\n");
    printf("      algorithms (like Dijkstra's or Prim's) on large, sparse graphs.\n");
    printf("    • Use Treap when you need dynamic sorted indexing with randomized "
           "balance.\n");
    printf("      - Real-world: IP routing tables, randomized database search "
           "indexes.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
