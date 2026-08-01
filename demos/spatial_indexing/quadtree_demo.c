#include "display_header.h"
#include "quadtree.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void quadtree_demo(void)
{
    display_header("QuadTree (2D Spatial Region Partitioning)");

    Rect boundary = {0.0, 0.0, 100.0, 100.0};
    QuadTree* tree = quadtree_create(boundary, 2);
    if (!tree)
    {
        printf("Failed to initialize QuadTree.\n");
        return;
    }

    printf("Inserting points into 2D QuadTree [boundary: (-100, -100) to (100, 100)]...\n");
    quadtree_insert(tree, 10.0, 10.0, NULL);
    quadtree_insert(tree, 20.0, 20.0, NULL);
    quadtree_insert(tree, -50.0, -50.0, NULL);
    quadtree_insert(tree, 80.0, 80.0, NULL);

    printf("Total Points Inserted: %zu (Root Divided: %s)\n", tree->total_points,
           tree->root->divided ? "YES" : "NO");

    Rect query_range = {15.0, 15.0, 15.0, 15.0};
    QuadPoint* results = NULL;
    size_t count = quadtree_query_range(tree, query_range, &results);

    printf("\n2D Bounding Box Query Range [0.0, 30.0] x [0.0, 30.0] Found %zu points:\n", count);
    for (size_t i = 0; i < count; i++)
    {
        printf(" -> Point %zu: (%.1f, %.1f)\n", i + 1, results[i].x, results[i].y);
    }

    free(results);
    quadtree_free(tree);
    press_enter_to_continue();
}
