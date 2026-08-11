#include "advanced_graph_algorithms.h"
#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bridges_demo(void)
{
    while (1)
    {
        display_header("Bridges (Critical Edges) Demo");

        int choice;
        int status = safe_input_int(&choice,
                                    "\n1. Create Custom Graph\n"
                                    "2. Load Graph from CSV\n"
                                    "-1 to exit: ",
                                    1, 2);

        if (status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (status == 0)
        {
            continue;
        }

        Graph* g = NULL;
        if (choice == 1)
        {
            int v;
            if (safe_input_int(&v, "Enter number of vertices: ", 2, 100) != 1)
            {
                continue;
            }
            g = create_graph(v);

            while (1)
            {
                int u;
                if (safe_input_int(&u, "Enter edge source (-1 to stop adding edges): ", -1,
                                   v - 1) != 1)
                {
                    continue;
                }
                if (u == -1)
                {
                    break;
                }

                int dst;
                if (safe_input_int(&dst, "Enter edge destination: ", 0, v - 1) != 1)
                {
                    continue;
                }

                add_edge_undirected(g, u, dst);
            }
        }
        else
        {
            char path[256];
            if (safe_input_string(path, sizeof(path), "Enter CSV path: ") != 1)
            {
                continue;
            }
            g = load_graph_from_csv(path);
            if (g == NULL)
            {
                printf("Failed to load graph.\n");
                continue;
            }
        }

        int count = 0;
        int** bridges = find_bridges(g, &count);

        printf("\n--- Bridges Analysis ---\n");
        printf("Total Bridges: %d\n", count);
        if (bridges != NULL && count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                printf("Edge (%d - %d)\n", bridges[i][0], bridges[i][1]);
            }
        }
        else
        {
            printf("No Bridges found. Graph is edge-biconnected.\n");
        }
        printf("------------------------\n\n");

        free_bridges(bridges, count);
        free_graph(g);

        int cont;
        if (safe_input_int(&cont, "Press 1 to analyze another graph, -1 to return: ", -1, 1) ==
            INPUT_EXIT_SIGNAL)
        {
            return;
        }
    }
}
