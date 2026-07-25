#include "bit_manipulation.h"
#include <assert.h>
#include <stdio.h>

/* --- set_bit tests --- */
void test_set_bit(void)
{
    assert(set_bit(0, 0) == 1);
    assert(set_bit(0, 3) == 8);
    assert(set_bit(5, 1) == 7);
    assert(set_bit(-1, 0) == -1); /* all bits already set */

    printf("set_bit tests passed\n");
}

/* --- clear_bit tests --- */
void test_clear_bit(void)
{
    assert(clear_bit(7, 0) == 6);
    assert(clear_bit(8, 3) == 0);
    assert(clear_bit(0, 5) == 0); /* no-op: bit already clear */

    printf("clear_bit tests passed\n");
}

/* --- toggle_bit tests --- */
void test_toggle_bit(void)
{
    assert(toggle_bit(0, 2) == 4);
    assert(toggle_bit(7, 1) == 5);
    assert(toggle_bit(toggle_bit(10, 0), 0) == 10); /* double toggle = no change */

    printf("toggle_bit tests passed\n");
}

/* --- check_bit tests --- */
void test_check_bit(void)
{
    assert(check_bit(5, 0) == 1); /* 5 = 101, bit 0 is set */
    assert(check_bit(5, 1) == 0); /* 5 = 101, bit 1 is clear */
    assert(check_bit(5, 2) == 1); /* 5 = 101, bit 2 is set */
    assert(check_bit(0, 7) == 0); /* no bits set */

    printf("check_bit tests passed\n");
}

/* --- count_set_bits tests --- */
void test_count_set_bits(void)
{
    assert(count_set_bits(0) == 0);
    assert(count_set_bits(1) == 1);
    assert(count_set_bits(7) == 3);   /* 111 */
    assert(count_set_bits(255) == 8); /* 11111111 */
    assert(count_set_bits(-1) == 32); /* all 32 bits set in two's complement */

    printf("count_set_bits tests passed\n");
}

/* --- is_power_of_two tests --- */
void test_is_power_of_two(void)
{
    assert(is_power_of_two(1) == 1);
    assert(is_power_of_two(2) == 1);
    assert(is_power_of_two(16) == 1);
    assert(is_power_of_two(1024) == 1);
    assert(is_power_of_two(0) == 0); /* zero is not a power of two */
    assert(is_power_of_two(3) == 0);
    assert(is_power_of_two(6) == 0);
    assert(is_power_of_two(-4) == 0); /* negative numbers are not powers of two */

    printf("is_power_of_two tests passed\n");
}

/* --- find_unique tests --- */
void test_find_unique(void)
{
    int arr1[] = {1, 2, 1, 3, 2};
    assert(find_unique(arr1, 5) == 3);

    int arr2[] = {7};
    assert(find_unique(arr2, 1) == 7);

    int arr3[] = {4, 4, 8, 8, 15};
    assert(find_unique(arr3, 5) == 15);

    printf("find_unique tests passed\n");
}

int main(void)
{
    test_set_bit();
    test_clear_bit();
    test_toggle_bit();
    test_check_bit();
    test_count_set_bits();
    test_is_power_of_two();
    test_find_unique();

    printf("All Bit Manipulation Tests Passed!\n");

    return 0;
}
