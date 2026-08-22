#include "../../features/fuzzy_tester/fuzzer.h"

#include "bit_manipulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* --- set_bit tests --- */
void test_set_bit_fuzz(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        int num = rand();
        if (rand() % 2 == 0)
            num = -num; // test negative numbers
        int bit = rand() % 32;
        int result = set_bit(num, bit);

        assert((result & (1U << bit)) != 0);
        // other bits should remain the same
        assert((result & ~(1U << bit)) == (num & ~(1U << bit)));
    }

    // Edge cases from original
    assert(set_bit(0, 0) == 1);
    assert(set_bit(0, 3) == 8);
    assert(set_bit(5, 1) == 7);
    assert(set_bit(-1, 0) == -1); /* all bits already set */
    assert(set_bit(0, 31) == (int)0x80000000);
    assert(set_bit(0, 32) == 0);

    printf("set_bit fuzz tests passed\n");
}

/* --- clear_bit tests --- */
void test_clear_bit_fuzz(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        int num = rand();
        if (rand() % 2 == 0)
            num = -num;
        int bit = rand() % 32;
        int result = clear_bit(num, bit);

        assert((result & (1U << bit)) == 0);
        // other bits should remain the same
        assert((result & ~(1U << bit)) == (num & ~(1U << bit)));
    }

    // Edge cases from original
    assert(clear_bit(7, 0) == 6);
    assert(clear_bit(8, 3) == 0);
    assert(clear_bit(0, 5) == 0); /* no-op: bit already clear */
    assert(clear_bit((int)0x80000000, 31) == 0);
    assert(clear_bit((int)0x80000000, 32) == (int)0x80000000);

    printf("clear_bit fuzz tests passed\n");
}

/* --- toggle_bit tests --- */
void test_toggle_bit_fuzz(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        int num = rand();
        if (rand() % 2 == 0)
            num = -num;
        int bit = rand() % 32;

        int original_bit_val = (num & (1U << bit)) != 0;
        int result = toggle_bit(num, bit);
        int new_bit_val = (result & (1U << bit)) != 0;

        assert(original_bit_val != new_bit_val);
        assert((result & ~(1U << bit)) == (num & ~(1U << bit)));
        assert(toggle_bit(toggle_bit(num, bit), bit) == num);
    }

    // Edge cases from original
    assert(toggle_bit(0, 2) == 4);
    assert(toggle_bit(7, 1) == 5);
    assert(toggle_bit(toggle_bit(10, 0), 0) == 10); /* double toggle = no change */
    assert(toggle_bit(0, 31) == (int)0x80000000);
    assert(toggle_bit(0, 32) == 0);

    printf("toggle_bit fuzz tests passed\n");
}

/* --- check_bit tests --- */
void test_check_bit_fuzz(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        int num = rand();
        if (rand() % 2 == 0)
            num = -num;
        int bit = rand() % 32;

        int expected = (num & (1U << bit)) != 0 ? 1 : 0;
        assert(check_bit(num, bit) == expected);
    }

    // Edge cases from original
    assert(check_bit(5, 0) == 1); /* 5 = 101, bit 0 is set */
    assert(check_bit(5, 1) == 0); /* 5 = 101, bit 1 is clear */
    assert(check_bit(5, 2) == 1); /* 5 = 101, bit 2 is set */
    assert(check_bit(0, 7) == 0); /* no bits set */
    assert(check_bit((int)0x80000000, 31) == 1);
    assert(check_bit(0, 32) == 0);

    printf("check_bit fuzz tests passed\n");
}

/* --- count_set_bits tests --- */
void test_count_set_bits_fuzz(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        int num = rand();
        if (rand() % 2 == 0)
            num = -num;

        int expected = 0;
        unsigned int unum = (unsigned int)num;
        while (unum)
        {
            expected += unum & 1;
            unum >>= 1;
        }

        assert(count_set_bits(num) == expected);
    }

    // Edge cases from original
    assert(count_set_bits(0) == 0);
    assert(count_set_bits(1) == 1);
    assert(count_set_bits(7) == 3);   /* 111 */
    assert(count_set_bits(255) == 8); /* 11111111 */
    assert(count_set_bits(-1) == 32); /* all 32 bits set in two's complement */

    printf("count_set_bits fuzz tests passed\n");
}

/* --- is_power_of_two tests --- */
void test_is_power_of_two_fuzz(int iterations)
{
    // Fuzz with random powers of 2
    for (int i = 0; i < 31; ++i)
    { // up to 2^30
        int power_of_two = 1 << i;
        assert(is_power_of_two(power_of_two) == 1);
    }

    // Fuzz with random numbers, verify they are not power of 2 unless they actually are
    for (int i = 0; i < iterations; ++i)
    {
        int num = rand();
        if (rand() % 2 == 0)
            num = -num;

        int expected = (num > 0 && ((unsigned int)num & ((unsigned int)num - 1)) == 0) ? 1 : 0;
        assert(is_power_of_two(num) == expected);
    }

    // Edge cases from original
    assert(is_power_of_two(1) == 1);
    assert(is_power_of_two(2) == 1);
    assert(is_power_of_two(16) == 1);
    assert(is_power_of_two(1024) == 1);
    assert(is_power_of_two(0) == 0); /* zero is not a power of two */
    assert(is_power_of_two(3) == 0);
    assert(is_power_of_two(6) == 0);
    assert(is_power_of_two(-4) == 0); /* negative numbers are not powers of two */

    printf("is_power_of_two fuzz tests passed\n");
}

/* --- find_unique tests --- */
void test_find_unique_fuzz(int iterations)
{
    for (int iter = 0; iter < iterations; ++iter)
    {
        int pairs = rand() % 50 + 1; // 1 to 50 pairs
        int n = pairs * 2 + 1;
        int* arr = (int*)malloc(n * sizeof(int));

        int unique_val = rand();
        if (rand() % 2 == 0)
            unique_val = -unique_val;

        arr[0] = unique_val;
        for (int i = 1; i < n; i += 2)
        {
            int pair_val = rand();
            if (rand() % 2 == 0)
                pair_val = -pair_val;
            arr[i] = pair_val;
            arr[i + 1] = pair_val;
        }

        // shuffle the array
        for (int i = n - 1; i > 0; --i)
        {
            int j = rand() % (i + 1);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        assert(find_unique(arr, n) == unique_val);
        free(arr);
    }

    // Edge cases from original
    int arr1[] = {1, 2, 1, 3, 2};
    assert(find_unique(arr1, 5) == 3);

    int arr2[] = {7};
    assert(find_unique(arr2, 1) == 7);

    int arr3[] = {4, 4, 8, 8, 15};
    assert(find_unique(arr3, 5) == 15);

    printf("find_unique fuzz tests passed\n");
}

int main(void)
{
    srand((unsigned int)time(NULL));
    int iterations = fuzzer_get_iterations(300);

    test_set_bit_fuzz(iterations);
    test_clear_bit_fuzz(iterations);
    test_toggle_bit_fuzz(iterations);
    test_check_bit_fuzz(iterations);
    test_count_set_bits_fuzz(iterations);
    test_is_power_of_two_fuzz(iterations);
    test_find_unique_fuzz(iterations);

    printf("All Bit Manipulation Fuzz Tests Passed!\n");

    return 0;
}
