#include "error_correction_algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_lrc_calculate(void)
{
    // 3 data words, each 4 bits wide
    // "1100"
    // "1010"
    // "0110"
    // Column XOR: col0=1^1^0=0, col1=1^0^1=0, col2=0^1^1=0, col3=0^0^0=0
    const char* words[] = {"1100", "1010", "0110"};
    char lrc[5];
    lrc_calculate(words, 3, 4, lrc);
    assert(strcmp(lrc, "0000") == 0);

    // Another test: "1011", "0110" → XOR col-by-col: 1,1,0,1
    const char* words2[] = {"1011", "0110"};
    lrc_calculate(words2, 2, 4, lrc);
    assert(strcmp(lrc, "1101") == 0);

    printf("test_lrc_calculate passed\n");
}

void test_lrc_verify_clean(void)
{
    const char* words[] = {"10110011", "11001100", "01100110"};
    char lrc[9];
    lrc_calculate(words, 3, 8, lrc);

    // Verify the computed LRC passes
    int result = lrc_verify(words, 3, 8, lrc);
    assert(result == 1);

    printf("test_lrc_verify_clean passed\n");
}

void test_lrc_verify_corrupted(void)
{
    const char* words[] = {"10110011", "11001100", "01100110"};
    char lrc[9];
    lrc_calculate(words, 3, 8, lrc);

    // Flip one bit in the LRC to simulate corruption
    char corrupted_lrc[9];
    strncpy(corrupted_lrc, lrc, sizeof(corrupted_lrc) - 1);
    corrupted_lrc[sizeof(corrupted_lrc) - 1] = '\0';
    corrupted_lrc[0] = (corrupted_lrc[0] == '1') ? '0' : '1';

    int result = lrc_verify(words, 3, 8, corrupted_lrc);
    assert(result == 0); // Should detect error

    printf("test_lrc_verify_corrupted passed\n");
}

int main(void)
{
    test_lrc_calculate();
    test_lrc_verify_clean();
    test_lrc_verify_corrupted();

    printf("All LRC tests passed successfully!\n");
    return 0;
}
