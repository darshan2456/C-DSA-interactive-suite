#include "algorithm_search.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_algorithm_registry_get(void)
{
    printf("Running test_algorithm_registry_get...\n");
    const AlgorithmRegistry* reg = get_algorithm_registry();
    assert(reg != NULL);
    assert(reg->count >= 50);
    assert(reg->entries != NULL);
    printf("--> test_algorithm_registry_get PASSED! (Total Registered: %lu)\n",
           (unsigned long)reg->count);
}

void test_search_algorithms_exact_and_keyword(void)
{
    printf("Running test_search_algorithms_exact_and_keyword...\n");
    const AlgorithmEntry* results[10];

    size_t count = search_algorithms("dijkstra", results, 10);
    assert(count >= 1);

    count = search_algorithms("avl", results, 10);
    assert(count >= 1);

    count = search_algorithms("tarjan", results, 10);
    assert(count >= 1);

    count = search_algorithms("bloom", results, 10);
    assert(count >= 1);

    count = search_algorithms("quadtree", results, 10);
    assert(count >= 1);

    count = search_algorithms("tree", results, 10);
    assert(count >= 2);

    count = search_algorithms("nonexistent_algorithm_xyz", results, 10);
    assert(count == 0);

    printf("--> test_search_algorithms_exact_and_keyword PASSED!\n");
}

void test_search_algorithms_invalid_args(void)
{
    printf("Running test_search_algorithms_invalid_args...\n");
    const AlgorithmEntry* results[10];

    assert(search_algorithms(NULL, results, 10) == 0);
    assert(search_algorithms("tree", NULL, 10) == 0);
    assert(search_algorithms("tree", results, 0) == 0);

    printf("--> test_search_algorithms_invalid_args PASSED!\n");
}

int main(void)
{
    test_algorithm_registry_get();
    test_search_algorithms_exact_and_keyword();
    test_search_algorithms_invalid_args();
    printf("All Algorithm Search Tests Passed!\n");
    return 0;
}
