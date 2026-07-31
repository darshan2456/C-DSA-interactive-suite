#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_graph_traversals_menu(void)
{
    display_header("Help - Graph Traversals & Spanning Trees");
    printf("BFS & DFS:\n");
    printf("    • Breadth-First Search: Explores vertices layer-by-layer using a Queue.\n");
    printf("    • Depth-First Search: Explores as deep as possible before backtracking using a "
           "Stack.\n\n");
    printf("SHORTEST PATHS:\n");
    printf("    • Dijkstra: Finds single-source shortest path for non-negative weights.\n");
    printf("    • Bellman-Ford: Finds single-source shortest path; handles negative weights.\n");
    printf("    • A* Search: Uses heuristics to speed up shortest-path searches.\n");
    printf("    • Greedy Best-First Search: Expands the node closest to the goal according to a "
           "heuristic.\n");
    printf("    • Floyd-Warshall: Computes shortest paths between all pairs of vertices.\n\n");
    printf("TOPOLOGICAL SORT:\n");
    printf("    Linear ordering of a DAG's vertices such that every edge (u, v) has u before v "
           "(Kahn's algorithm).\n\n");
    printf("SPANNING TREES:\n");
    printf("    • Prim's & Kruskal's algorithms to find Minimum Spanning Trees (MST).\n\n");
    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
