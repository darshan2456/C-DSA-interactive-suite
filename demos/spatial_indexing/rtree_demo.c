#include "display_header.h"
#include "rtree.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void rtree_demo(void)
{
    display_header("R-Tree (Spatial Bounding Box Index)");

    RTree* tree = rtree_create(4, 2);
    if (!tree)
    {
        printf("Failed to initialize R-Tree.\n");
        return;
    }

    printf("Inserting Minimum Bounding Rectangles (MBRs)...\n");
    MBR b1 = {1.0, 1.0, 3.0, 3.0};
    MBR b2 = {4.0, 4.0, 6.0, 6.0};
    MBR b3 = {10.0, 10.0, 15.0, 15.0};

    rtree_insert(tree, b1, NULL);
    rtree_insert(tree, b2, NULL);
    rtree_insert(tree, b3, NULL);

    printf("Total Items Indexed: %zu\n", tree->total_items);

    MBR search_query = {0.0, 0.0, 5.0, 5.0};
    RTreeItem* results = NULL;
    size_t count = rtree_search_mbr(tree, search_query, &results);

    printf("\nSpatial Intersects Query [0,5]x[0,5] Found %zu MBRs:\n", count);
    for (size_t i = 0; i < count; i++)
    {
        printf(" -> MBR %zu: Min(%.1f, %.1f) Max(%.1f, %.1f)\n", i + 1, results[i].mbr.min_x,
               results[i].mbr.min_y, results[i].mbr.max_x, results[i].mbr.max_y);
    }

    free(results);
    rtree_free(tree);
    press_enter_to_continue();
}
