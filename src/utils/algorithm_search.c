#include "algorithm_search.h"
#include "display_header.h"
#include "safe_input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declarations of demo function pointers */
void trees_demo(void);
void binary_search_tree_demo(void);
void avl_demo(void);
void TBT_demo(void);
void trie_demo(void);
void btree_demo(void);
void bplus_tree_demo(void);
void segment_tree_demo(void);
void fenwick_tree_demo(void);
void splay_tree_demo(void);
void red_black_tree_demo(void);

void advanced_heaps_demo(void);
void run_binomial_demo(void);
void run_dary_demo(void);
void run_fibonacci_demo(void);
void run_leftist_demo(void);
void run_skew_demo(void);
void run_min_max_demo(void);
void run_treap_demo(void);

void sorting_algorithms_n2_demo(void);
void bubble_sort_optimized_demo(void);
void insertion_sort_demo(void);
void selection_sort_demo(void);
void shell_sort_demo(void);

void advanced_sorting_demo(void);
void quicksort_demo(void);
void merge_sort_demo(void);
void heap_sort_demo(void);
void radix_sort_demo(void);
void bucket_sort_demo(void);

void graph_traversals_demo(void);
void bfs_demo(void);
void dfs_demo(void);
void dijkstra_demo(void);
void astar_demo(void);
void greedy_best_first_search_demo(void);
void bellman_ford_demo(void);
void topological_sort_demo(void);
void kruskal_demo(void);
void prim_demo(void);
void floyd_warshall_demo(void);

void advanced_graph_algorithms_demo(void);
void tarjan_scc_demo(void);
void kosaraju_scc_demo(void);
void ford_fulkerson_demo(void);
void edmonds_karp_demo(void);
void dinic_demo(void);
void dinic_bipartite_matching_demo(void);
void hopcroft_karp_demo(void);
void eulerian_path_demo(void);
void articulation_points_demo(void);
void bridges_demo(void);
void network_vulnerability_demo(void);

void dynamic_programming_demo(void);
void knapsack_demo(void);
void lcs_demo(void);
void fibonacci_demo(void);
void mcm_demo(void);
void edit_distance_demo(void);
void coin_change_demo(void);

void probabilistic_ds_demo(void);
void bloom_filter_demo(void);
void count_min_sketch_demo(void);
void hyperloglog_demo(void);

void spatial_indexing_demo(void);
void kd_tree_demo(void);
void quadtree_demo(void);
void rtree_demo(void);

void searching_algorithms_demo(void);
void compression_demo(void);
void string_algorithms_demo(void);

static const AlgorithmEntry GLOBAL_ALGORITHM_TABLE[] = {
    /* Trees Category */
    {"Binary Search Tree (BST) Interactive Demo", "Trees",
     "bst binary search tree node insert delete search", 7, binary_search_tree_demo},
    {"AVL Self-Balancing Tree Interactive Demo", "Trees",
     "avl tree balance factor rotations self balancing search", 7, avl_demo},
    {"Threaded Binary Tree (TBT) Interactive Demo", "Trees",
     "threaded tbt binary tree traversal null pointers", 7, TBT_demo},
    {"Trie Prefix Tree Interactive Demo", "Trees",
     "trie prefix tree string dictionary auto complete search", 7, trie_demo},
    {"B-Tree Self-Balancing Search Tree Demo", "Trees",
     "btree b-tree multiway disk storage database index", 7, btree_demo},
    {"B+ Tree Indexing Interactive Demo", "Trees",
     "bplus b+tree sequential leaf range query database index", 7, bplus_tree_demo},
    {"Segment Tree Range Query Interactive Demo", "Trees",
     "segment tree range query min max sum update array", 7, segment_tree_demo},
    {"Fenwick Tree (Binary Indexed Tree) Demo", "Trees",
     "fenwick bit binary indexed tree prefix sum point update", 7, fenwick_tree_demo},
    {"Splay Tree Self-Adjusting Search Tree Demo", "Trees",
     "splay tree self adjusting cache recent access search", 7, splay_tree_demo},
    {"Red-Black Balanced Search Tree Demo", "Trees",
     "red black tree rbt color balance self balancing search", 7, red_black_tree_demo},
    {"Trees & Advanced Tree Structures Suite", "Trees",
     "bst avl red black splay segment fenwick trie btree", 7, trees_demo},

    /* Advanced Heaps Category */
    {"Binomial Heap Priority Queue Demo", "Advanced Heaps",
     "binomial heap priority queue merge union min heap", 9, run_binomial_demo},
    {"D-ary Heap Multi-way Priority Queue Demo", "Advanced Heaps",
     "dary d-ary heap multiway priority queue min heap", 9, run_dary_demo},
    {"Fibonacci Heap Amortized Priority Queue Demo", "Advanced Heaps",
     "fibonacci heap priority queue amortized decrease key min heap", 9, run_fibonacci_demo},
    {"Leftist Heap Meldable Priority Queue Demo", "Advanced Heaps",
     "leftist heap meldable priority queue merge null path length", 9, run_leftist_demo},
    {"Skew Heap Self-Adjusting Priority Queue Demo", "Advanced Heaps",
     "skew heap self adjusting meldable priority queue merge", 9, run_skew_demo},
    {"Min-Max Double-Ended Priority Queue Demo", "Advanced Heaps",
     "min max min-max heap double ended priority queue depq", 9, run_min_max_demo},
    {"Treap Randomized Search Tree & Heap Demo", "Advanced Heaps",
     "treap randomized binary search tree priority heap cartesian", 9, run_treap_demo},
    {"Advanced Heaps & Priority Queues Suite", "Advanced Heaps",
     "heaps binomial fibonacci dary leftist skew treap minmax", 9, advanced_heaps_demo},

    /* Searching & Sorting Category */
    {"Bubble Sort Interactive Demo", "Sorting", "bubble sort elementary exchange n2", 3,
     bubble_sort_optimized_demo},
    {"Selection Sort Interactive Demo", "Sorting", "selection sort elementary select minimum n2", 3,
     selection_sort_demo},
    {"Insertion Sort Interactive Demo", "Sorting", "insertion sort elementary insert online n2", 3,
     insertion_sort_demo},
    {"Shell Sort Diminishing Increment Demo", "Sorting",
     "shell sort diminishing increment gap insertion n2", 3, shell_sort_demo},
    {"O(N^2) Elementary Sorting Suite", "Sorting",
     "bubble selection insertion shell sort elementary n2", 3, sorting_algorithms_n2_demo},

    {"Quick Sort Divide & Conquer Demo", "Sorting",
     "quick sort partition divide conquer pivot nlogn", 3, quicksort_demo},
    {"Merge Sort Stable Sorting Demo", "Sorting",
     "merge sort divide conquer stable sub arrays nlogn", 3, merge_sort_demo},
    {"Heap Sort In-place Comparison Demo", "Sorting",
     "heap sort binary heap in place priority nlogn", 3, heap_sort_demo},
    {"Radix Sort Non-comparison Integer Sorting Demo", "Sorting",
     "radix sort counting digit non comparison linear", 3, radix_sort_demo},
    {"Bucket Sort Distribution Sorting Demo", "Sorting",
     "bucket sort distribution floating point linear", 3, bucket_sort_demo},
    {"O(N log N) Advanced Sorting Suite", "Sorting",
     "quick merge heap radix bucket sort advanced nlogn", 3, advanced_sorting_demo},

    /* Graph Traversals Category */
    {"Breadth-First Search (BFS) Traversal Demo", "Graph Traversals",
     "bfs breadth first search queue shortest path unweighted graph", 5, bfs_demo},
    {"Depth-First Search (DFS) Traversal Demo", "Graph Traversals",
     "dfs depth first search stack recursion component cycle graph", 5, dfs_demo},
    {"Dijkstra Shortest Path Single-Source Demo", "Graph Traversals",
     "dijkstra shortest path single source non negative priority queue graph", 5, dijkstra_demo},
    {"A* Heuristic Shortest Path Search Demo", "Graph Traversals",
     "astar a* heuristic shortest path euclidean manhattan grid graph", 5, astar_demo},
    {"Greedy Best-First Search Interactive Demo", "Graph Traversals",
     "greedy best first search heuristic grid pathfinding graph", 5, greedy_best_first_search_demo},
    {"Bellman-Ford Negative Weight Edge Path Demo", "Graph Traversals",
     "bellman ford shortest path negative weight edge cycle detection graph", 5, bellman_ford_demo},
    {"Topological Sort Directed Acyclic Graph Demo", "Graph Traversals",
     "topological sort dag dependency order indegree kahn kahn's graph", 5, topological_sort_demo},
    {"Kruskal Minimum Spanning Tree (MST) Demo", "Graph Traversals",
     "kruskal mst minimum spanning tree disjoint set union find greedy graph", 5, kruskal_demo},
    {"Prim Minimum Spanning Tree (MST) Demo", "Graph Traversals",
     "prim mst minimum spanning tree priority queue greedy graph", 5, prim_demo},
    {"Floyd-Warshall All-Pairs Shortest Path Demo", "Graph Traversals",
     "floyd warshall all pairs shortest path matrix dynamic programming graph", 5,
     floyd_warshall_demo},
    {"Graph Traversals & Pathfinding Suite", "Graph Traversals",
     "bfs dfs dijkstra astar bellman ford kruskal prim floyd warshall", 5, graph_traversals_demo},

    /* Advanced Graph Algorithms Category */
    {"Tarjan Strongly Connected Components (SCC) Demo", "Advanced Graphs",
     "tarjan scc strongly connected components lowlink dfs graph", 6, tarjan_scc_demo},
    {"Kosaraju Strongly Connected Components (SCC) Demo", "Advanced Graphs",
     "kosaraju scc strongly connected components transpose dfs graph", 6, kosaraju_scc_demo},
    {"Ford-Fulkerson Maximum Network Flow Demo", "Advanced Graphs",
     "ford fulkerson max flow residual capacity augmenting path graph", 6, ford_fulkerson_demo},
    {"Edmonds-Karp BFS Maximum Flow Demo", "Advanced Graphs",
     "edmonds karp max flow bfs shortest augmenting path graph", 6, edmonds_karp_demo},
    {"Dinic Blocking Flow Maximum Network Flow Demo", "Advanced Graphs",
     "dinic max flow level graph blocking flow network graph", 6, dinic_demo},
    {"Dinic Bipartite Matching Interactive Demo", "Advanced Graphs",
     "dinic bipartite matching maximum matching flow graph", 6, dinic_bipartite_matching_demo},
    {"Hopcroft-Karp Bipartite Matching Demo", "Advanced Graphs",
     "hopcroft karp bipartite matching maximum cardinality graph", 6, hopcroft_karp_demo},
    {"Eulerian Path & Circuit Interactive Demo", "Advanced Graphs",
     "eulerian path circuit walk degree hierholzer graph", 6, eulerian_path_demo},
    {"Articulation Points Cut Vertex Analysis Demo", "Advanced Graphs",
     "articulation points cut vertex critical node network graph", 6, articulation_points_demo},
    {"Bridges Critical Edge Network Analysis Demo", "Advanced Graphs",
     "bridges critical edge network vulnerability connectivity graph", 6, bridges_demo},
    {"Network Vulnerability & Resilience Simulator", "Advanced Graphs",
     "network vulnerability simulator resilience critical nodes edges graph", 6,
     network_vulnerability_demo},
    {"Advanced Graph Algorithms Suite", "Advanced Graphs",
     "dinic ford fulkerson edmonds karp scc bipartite matching bridges articulation", 6,
     advanced_graph_algorithms_demo},

    /* Dynamic Programming Category */
    {"0/1 Knapsack Problem DP Interactive Demo", "Dynamic Programming",
     "knapsack 0/1 weight value capacity optimization dp", 8, knapsack_demo},
    {"Longest Common Subsequence (LCS) DP Demo", "Dynamic Programming",
     "lcs longest common subsequence string alignment dp", 8, lcs_demo},
    {"Fibonacci Sequence Memoization & Tabulation Demo", "Dynamic Programming",
     "fibonacci memoization tabulation recurrence golden ratio dp", 8, fibonacci_demo},
    {"Matrix Chain Multiplication (MCM) DP Demo", "Dynamic Programming",
     "mcm matrix chain multiplication parenthesization cost dp", 8, mcm_demo},
    {"Edit Distance (Levenshtein Distance) DP Demo", "Dynamic Programming",
     "edit distance levenshtein insert delete replace string dp", 8, edit_distance_demo},
    {"Coin Change Minimum Coins DP Demo", "Dynamic Programming",
     "coin change minimum coins ways amount denomination dp", 8, coin_change_demo},
    {"Dynamic Programming Algorithms Suite", "Dynamic Programming",
     "knapsack lcs mcm fibonacci coin change edit distance dp", 8, dynamic_programming_demo},

    /* Probabilistic Data Structures Category */
    {"Bloom Filter Set Membership Demo", "Probabilistic DS",
     "bloom filter fnv hash set membership false positive rate probabilistic", 16,
     bloom_filter_demo},
    {"Count-Min Sketch Frequency Estimator Demo", "Probabilistic DS",
     "count min sketch frequency estimator sublinear heavy hitter probabilistic", 16,
     count_min_sketch_demo},
    {"HyperLogLog Cardinality Estimator Demo", "Probabilistic DS",
     "hyperloglog hll cardinality estimator unique count harmonic mean probabilistic", 16,
     hyperloglog_demo},
    {"Probabilistic Data Structures Suite", "Probabilistic DS",
     "bloom filter count min sketch hyperloglog hll probabilistic", 16, probabilistic_ds_demo},

    /* Spatial Indexing Category */
    {"k-d Tree Multi-Dimensional Point Indexing Demo", "Spatial Indexing",
     "kd kdtree k-d tree point indexing nearest neighbor range search spatial", 17, kd_tree_demo},
    {"QuadTree 2D Spatial Partitioning Demo", "Spatial Indexing",
     "quadtree 2d spatial partitioning bounding box point region spatial", 17, quadtree_demo},
    {"R-Tree Minimum Bounding Rectangle (MBR) Demo", "Spatial Indexing",
     "rtree r-tree minimum bounding rectangle mbr spatial indexing range search", 17, rtree_demo},
    {"Spatial & Multi-Dimensional Indexing Suite", "Spatial Indexing",
     "kd kdtree quadtree rtree spatial 2d mbr point range search", 17, spatial_indexing_demo},

    /* Searching & Compression Suites */
    {"Searching Algorithms Suite (Binary, Linear, Jump, Interpolation)", "Searching",
     "binary linear interpolation jump exponential search", 4, searching_algorithms_demo},
    {"String Processing & Compression Algorithms Suite", "String & Compression",
     "huffman rle lzw bwt kmp rabin karp string compression", 12, compression_demo}};

static const AlgorithmRegistry GLOBAL_REGISTRY = {
    GLOBAL_ALGORITHM_TABLE, sizeof(GLOBAL_ALGORITHM_TABLE) / sizeof(GLOBAL_ALGORITHM_TABLE[0])};

const AlgorithmRegistry* get_algorithm_registry(void)
{
    return &GLOBAL_REGISTRY;
}

static bool string_contains_case_insensitive(const char* haystack, const char* needle)
{
    if (!haystack || !needle)
    {
        return false;
    }

    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);
    if (needle_len == 0 || needle_len > haystack_len)
    {
        return false;
    }

    for (size_t i = 0; i <= haystack_len - needle_len; i++)
    {
        bool match = true;
        for (size_t j = 0; j < needle_len; j++)
        {
            if (tolower((unsigned char)haystack[i + j]) != tolower((unsigned char)needle[j]))
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return true;
        }
    }
    return false;
}

size_t search_algorithms(const char* query, const AlgorithmEntry** results, size_t max_results)
{
    if (!query || !results || max_results == 0)
    {
        return 0;
    }

    size_t found = 0;
    const AlgorithmRegistry* reg = get_algorithm_registry();

    for (size_t i = 0; i < reg->count && found < max_results; i++)
    {
        const AlgorithmEntry* entry = &reg->entries[i];
        if (string_contains_case_insensitive(entry->name, query) ||
            string_contains_case_insensitive(entry->category, query) ||
            string_contains_case_insensitive(entry->keywords, query))
        {
            results[found++] = entry;
        }
    }

    return found;
}

void run_algorithm_search_menu(void)
{
    display_header("Interactive Algorithm Quick-Search Finder");

    char query[64] = {0};
    int status = safe_input_string(query, sizeof(query),
                                   "\nEnter search keyword (e.g. 'dijkstra', 'avl', 'sort'): ");
    if (status == INPUT_EXIT_SIGNAL || strlen(query) == 0)
    {
        printf("\nExiting interactive algorithm finder...\n");
        return;
    }

    const AlgorithmEntry* results[60];
    size_t count = search_algorithms(query, results, 60);

    if (count == 0)
    {
        printf("\nNo algorithms matching '%s' were found in the registry.\n", query);
        printf("\nExiting interactive algorithm finder...\n");
        return;
    }

    printf("\nFound %zu matching algorithm demo(s):\n", count);
    for (size_t i = 0; i < count; i++)
    {
        printf("  %zu. %s [%s] (Menu Option %d)\n", i + 1, results[i]->name, results[i]->category,
               results[i]->menu_option);
    }

    int choice;
    status = safe_input_int(&choice, "\nSelect algorithm number to launch demo (-1 to cancel): ", 1,
                            (int)count);
    if (status == INPUT_EXIT_SIGNAL || choice < 1 || (size_t)choice > count)
    {
        printf("\nExiting interactive algorithm finder...\n");
        return;
    }

    printf("\nLaunching '%s' demo...\n\n", results[choice - 1]->name);
    if (results[choice - 1]->demo_fn)
    {
        results[choice - 1]->demo_fn();
    }
}
