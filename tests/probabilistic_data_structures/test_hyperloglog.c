#include "hyperloglog.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_hll_init(void)
{
    printf("Running test_hll_init...\n");
    HyperLogLog* hll = hll_init(12);
    assert(hll != NULL);
    assert(hll->b == 12);
    assert(hll->m == 4096);
    assert(hll_count(hll) == 0);

    hll_free(hll);
    printf("--> test_hll_init PASSED!\n");
}

void test_hll_invalid_args(void)
{
    printf("Running test_hll_invalid_args...\n");
    assert(hll_init(3) == NULL);
    assert(hll_init(17) == NULL);

    HyperLogLog* hll = hll_init(10);
    assert(hll != NULL);

    assert(hll_add(NULL, "data", 4) == false);
    assert(hll_add(hll, NULL, 4) == false);
    assert(hll_add(hll, "data", 0) == false);

    assert(hll_count(NULL) == 0);

    hll_free(hll);
    hll_free(NULL);
    printf("--> test_hll_invalid_args PASSED!\n");
}

void test_hll_cardinality_accuracy(void)
{
    printf("Running test_hll_cardinality_accuracy...\n");
    uint8_t precision = 12; /* 4096 registers, ~1.6% standard error */
    HyperLogLog* hll = hll_init(precision);
    assert(hll != NULL);

    size_t unique_items = 5000;
    char buf[64];

    /* Insert 5000 unique items */
    for (size_t i = 0; i < unique_items; i++)
    {
        snprintf(buf, sizeof(buf), "unique_user_id_%lu", (unsigned long)i);
        assert(hll_add(hll, buf, strlen(buf)) == true);
    }

    /* Insert duplicate items to ensure duplicates don't inflate count */
    for (size_t i = 0; i < 1000; i++)
    {
        snprintf(buf, sizeof(buf), "unique_user_id_%lu", (unsigned long)(i % 100));
        assert(hll_add(hll, buf, strlen(buf)) == true);
    }

    uint64_t est = hll_count(hll);
    printf("Actual Unique Items: %lu, HLL Estimated Cardinality: %I64u\n",
           (unsigned long)unique_items, (unsigned long long)est);

    /* Allow standard error margin for HLL (~3.5%) */
    double lower_bound = (double)unique_items * 0.90;
    double upper_bound = (double)unique_items * 1.10;
    assert((double)est >= lower_bound && (double)est <= upper_bound);

    hll_free(hll);
    printf("--> test_hll_cardinality_accuracy PASSED!\n");
}

int main(void)
{
    test_hll_init();
    test_hll_invalid_args();
    test_hll_cardinality_accuracy();
    printf("All HyperLogLog Tests Passed!\n");
    return 0;
}
