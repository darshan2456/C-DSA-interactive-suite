#include "display_header.h"
#include "kd_tree.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void kd_tree_demo(void)
{
    display_header("k-d Tree (Multi-Dimensional Index & k-NN)");

    KDTree* tree = kdtree_create(2);
    if (!tree)
    {
        printf("Failed to initialize k-d Tree.\n");
        return;
    }

    printf("Inserting 2D spatial points...\n");
    double points[][2] = {{3.0, 6.0},  {17.0, 15.0}, {13.0, 15.0},
                          {6.0, 12.0}, {9.0, 1.0},   {2.0, 7.0}};
    for (size_t i = 0; i < 6; i++)
    {
        kdtree_insert(tree, points[i], NULL);
        printf(" -> Inserted point (%.1f, %.1f)\n", points[i][0], points[i][1]);
    }

    double query[2] = {9.0, 2.0};
    double dist = 0.0;
    KDNode* nn = kdtree_nearest_neighbor(tree, query, &dist);

    printf("\nNearest Neighbor Query to (%.1f, %.1f):\n", query[0], query[1]);
    if (nn)
    {
        printf(" -> Nearest Found : (%.1f, %.1f)\n", nn->point[0], nn->point[1]);
        printf(" -> Euclidean Dist : %.4f\n", dist);
    }

    double min_pt[2] = {3.0, 3.0};
    double max_pt[2] = {15.0, 15.0};
    KDNode** range_res = NULL;
    size_t count = kdtree_range_search(tree, min_pt, max_pt, &range_res);

    printf("\nRange Search [3.0, 15.0] x [3.0, 15.0] Found %zu points:\n", count);
    for (size_t i = 0; i < count; i++)
    {
        printf(" -> Point %zu: (%.1f, %.1f)\n", i + 1, range_res[i]->point[0],
               range_res[i]->point[1]);
    }

    free(range_res);
    kdtree_free(tree);
    press_enter_to_continue();
}
