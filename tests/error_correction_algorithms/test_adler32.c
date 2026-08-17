#include "error_correction_algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_adler32_null_and_empty(void)
{
    assert(calculate_adler32(NULL, 0) == 0x00000001U);
    assert(calculate_adler32("", 0) == 0x00000001U);
    printf("test_adler32_null_and_empty passed\n");
}

void test_adler32_single_char(void)
{
    // 'a' = 97 (0x61). A = 1 + 97 = 98 (0x62), B = 98 (0x62) => 0x00620062
    assert(calculate_adler32("a", 1) == 0x00620062U);
    printf("test_adler32_single_char passed\n");
}

void test_adler32_known_vectors(void)
{
    const char* wiki = "Wikipedia";
    assert(calculate_adler32(wiki, strlen(wiki)) == 0x11E60398U);

    const char* digits = "123456789";
    assert(calculate_adler32(digits, strlen(digits)) == 0x091E01DEU);

    const char* abc = "abc";
    assert(calculate_adler32(abc, strlen(abc)) == 0x024D0127U);

    printf("test_adler32_known_vectors passed\n");
}

void test_adler32_long_string(void)
{
    char long_buf[10000];
    memset(long_buf, 'A', sizeof(long_buf));
    uint32_t checksum = calculate_adler32(long_buf, sizeof(long_buf));
    assert(checksum != 0);

    // Deterministic verify
    uint32_t checksum2 = calculate_adler32(long_buf, sizeof(long_buf));
    assert(checksum == checksum2);

    printf("test_adler32_long_string passed\n");
}

int main(void)
{
    test_adler32_null_and_empty();
    test_adler32_single_char();
    test_adler32_known_vectors();
    test_adler32_long_string();

    printf("All Adler-32 checksum tests passed successfully!\n");
    return 0;
}
