#include "clear_screen.h"
#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

static void display_flow_matching_help(void)
{
    clear_screen();
    display_header("MANUAL: Network Flow & Bipartite Matching Algorithms");
    printf(
        "\n"
        "================================================================================\n"
        " 1. FORD-FULKERSON & EDMONDS-KARP MAX FLOW\n"
        "================================================================================\n"
        " Concept:\n"
        "   Computes maximum network flow from source node (s) to sink node (t) in a weighted\n"
        "   directed graph with capacity constraints.\n\n"
        " Complexity Cheat Table:\n"
        "   +-----------------------+------------------------+-------------------+\n"
        "   | Algorithm             | Time Complexity        | Space Complexity  |\n"
        "   +-----------------------+------------------------+-------------------+\n"
        "   | Ford-Fulkerson (DFS)   | O(E * |f_max|)         | O(V + E)          |\n"
        "   | Edmonds-Karp (BFS)    | O(V * E^2)             | O(V + E)          |\n"
        "   | Dinic's Algorithm     | O(V^2 * E)             | O(V + E)          |\n"
        "   +-----------------------+------------------------+-------------------+\n\n"
        "================================================================================\n"
        " 2. BIPARTITE MATCHING (Dinic & Hopcroft-Karp)\n"
        "================================================================================\n"
        " Concept:\n"
        "   Finds maximum cardinality set of edges without common vertices in bipartite graphs.\n"
        "   - Hopcroft-Karp Time Complexity: O(E * sqrt(V))\n"
        "   - Dinic Bipartite Time Complexity: O(E * sqrt(V))\n\n"
        " Press [ENTER] to return to Advanced Graphs Help Menu...");
    getchar();
}

static void display_bridges_articulation_help(void)
{
    clear_screen();
    display_header("MANUAL: Bridges, Articulation Points & Network Vulnerability");
    printf(
        "\n"
        "================================================================================\n"
        " 1. ARTICULATION POINTS (Cut Vertices)\n"
        "================================================================================\n"
        " Concept:\n"
        "   A vertex v is an articulation point if removing v increases the number of connected\n"
        "   components in the graph. Identified using DFS discovery times and lowlink values.\n"
        "   - Condition: tin[u] <= low[v] for non-root, or child_count >= 2 for root node.\n"
        "   - Time Complexity: O(V + E)\n"
        "   - Space Complexity: O(V)\n\n"
        "================================================================================\n"
        " 2. BRIDGES (Critical Edges)\n"
        "================================================================================\n"
        " Concept:\n"
        "   An edge (u, v) is a bridge if removing it disconnects the graph.\n"
        "   - Condition: tin[u] < low[v].\n"
        "   - Time Complexity: O(V + E)\n"
        "   - Space Complexity: O(V + E)\n\n"
        " Press [ENTER] to return to Advanced Graphs Help Menu...");
    getchar();
}

void help_advanced_graph_algorithms_menu(void)
{
    while (1)
    {
        clear_screen();
        display_header("Help: Advanced Graph Algorithms & Network Resilience");

        int choice;
        int status = safe_input_int(
            &choice,
            "\nAdvanced Graph Topics:\n"
            "----------------------\n"
            "1. Network Flow & Bipartite Matching (Ford-Fulkerson, Dinic, Hopcroft-Karp)\n"
            "2. Articulation Points, Bridges & Network Resilience\n"
            "\nenter choice ('-1' to return): ",
            1, 2);

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
                display_flow_matching_help();
                break;
            case 2:
                display_bridges_articulation_help();
                break;
        }
    }
}
