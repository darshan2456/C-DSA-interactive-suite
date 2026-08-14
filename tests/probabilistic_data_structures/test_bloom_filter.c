#include "bloom_filter.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_bloom_init(void)
{
    printf("Running test_bloom_init...\n");
    BloomFilter* filter = bloom_init(1000, 0.01);
    assert(filter != NULL);
    assert(filter->expected_items == 1000);
    assert(filter->target_fp_rate == 0.01);
    assert(filter->bit_size > 0);
    assert(filter->num_hashes > 0);
    assert(filter->count == 0);

    bloom_free(filter);
    printf("--> test_bloom_init PASSED!\n");
}

void test_bloom_invalid_params(void)
{
    printf("Running test_bloom_invalid_params...\n");
    assert(bloom_init(0, 0.01) == NULL);
    assert(bloom_init(100, 0.0) == NULL);
    assert(bloom_init(100, 1.0) == NULL);
    assert(bloom_init(100, -0.5) == NULL);

    BloomFilter* filter = bloom_init(100, 0.05);
    assert(filter != NULL);

    assert(bloom_add(NULL, "data", 4) == false);
    assert(bloom_add(filter, NULL, 4) == false);
    assert(bloom_add(filter, "data", 0) == false);

    assert(bloom_check(NULL, "data", 4) == false);
    assert(bloom_check(filter, NULL, 4) == false);
    assert(bloom_check(filter, "data", 0) == false);

    bloom_free(filter);
    bloom_free(NULL);
    printf("--> test_bloom_invalid_params PASSED!\n");
}

void test_bloom_add_and_check(void)
{
    printf("Running test_bloom_add_and_check...\n");
    BloomFilter* filter = bloom_init(500, 0.01);
    assert(filter != NULL);

    const char* words[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    size_t num_words = sizeof(words) / sizeof(words[0]);

    for (size_t i = 0; i < num_words; i++)
    {
        assert(bloom_add(filter, words[i], strlen(words[i])) == true);
    }

    for (size_t i = 0; i < num_words; i++)
    {
        assert(bloom_check(filter, words[i], strlen(words[i])) == true);
    }

    const char* missing[] = {"watermelon", "pineapple", "mango", "strawberry"};
    for (size_t i = 0; i < sizeof(missing) / sizeof(missing[0]); i++)
    {
        /* Absent elements should mostly return false (or false positive within bounds) */
        bloom_check(filter, missing[i], strlen(missing[i]));
    }

    bloom_free(filter);
    printf("--> test_bloom_add_and_check PASSED!\n");
}

void test_bloom_false_positive_rate(void)
{
    printf("Running test_bloom_false_positive_rate...\n");
    size_t n = 1000;
    double target_fp = 0.05;
    BloomFilter* filter = bloom_init(n, target_fp);
    assert(filter != NULL);

    /* Insert 1000 elements */
    char buf[64];
    for (size_t i = 0; i < n; i++)
    {
        snprintf(buf, sizeof(buf), "item_inserted_%lu", (unsigned long)i);
        assert(bloom_add(filter, buf, strlen(buf)) == true);
    }

    /* Check inserted items (must all be true) */
    for (size_t i = 0; i < n; i++)
    {
        snprintf(buf, sizeof(buf), "item_inserted_%lu", (unsigned long)i);
        assert(bloom_check(filter, buf, strlen(buf)) == true);
    }

    /* Query 1000 non-inserted items to measure empirical false positive rate */
    size_t false_positives = 0;
    size_t queries = 1000;
    for (size_t i = 0; i < queries; i++)
    {
        snprintf(buf, sizeof(buf), "item_absent_%lu", (unsigned long)i);
        if (bloom_check(filter, buf, strlen(buf)))
        {
            false_positives++;
        }
    }

    double empirical_fp = (double)false_positives / (double)queries;
    printf("Empirical FP Rate: %.4f (Target: %.4f)\n", empirical_fp, target_fp);
    assert(empirical_fp <= target_fp * 2.5); /* Allow statistical margin */

    bloom_free(filter);
    printf("--> test_bloom_false_positive_rate PASSED!\n");
}

int main(void)
{
    test_bloom_init();
    test_bloom_invalid_params();
    test_bloom_add_and_check();
    test_bloom_false_positive_rate();
    printf("All Bloom Filter Tests Passed!\n");
    return 0;
}
