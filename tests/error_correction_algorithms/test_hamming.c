#include "error_correction_algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_hamming_generate_and_verify(void)
{
    // Test data: "1001101" (7 data bits)
    // Parity bits needed: r=4 since 2^4 >= 7+4+1 (16 >= 12)
    // Codeword length: n = 11
    const char* data = "1001101";
    char codeword[128];

    hamming_generate(data, codeword);
    assert(strlen(codeword) == 11);

    // Verify error-free reception
    char corrected[128];
    char data_recovered[128];
    int syndrome = hamming_verify(codeword, corrected, data_recovered);
    assert(syndrome == 0); // No error
    assert(strcmp(corrected, codeword) == 0);
    assert(strcmp(data_recovered, data) == 0);

    // Simulate single-bit error at position 5
    // 1-based index 5 corresponds to 0-based index 4 in C string
    char corrupt_codeword[128];
    strncpy(corrupt_codeword, codeword, sizeof(corrupt_codeword) - 1);
    corrupt_codeword[sizeof(corrupt_codeword) - 1] = '\0';
    corrupt_codeword[4] = (corrupt_codeword[4] == '1') ? '0' : '1';

    int error_pos = hamming_verify(corrupt_codeword, corrected, data_recovered);
    assert(error_pos == 5);                    // Error detected at position 5
    assert(strcmp(corrected, codeword) == 0);  // Should be corrected back to original codeword
    assert(strcmp(data_recovered, data) == 0); // Data should be recovered successfully

    // Simulate error in parity bit at position 1 (0-based index 0)
    strncpy(corrupt_codeword, codeword, sizeof(corrupt_codeword) - 1);
    corrupt_codeword[sizeof(corrupt_codeword) - 1] = '\0';
    corrupt_codeword[0] = (corrupt_codeword[0] == '1') ? '0' : '1';

    error_pos = hamming_verify(corrupt_codeword, corrected, data_recovered);
    assert(error_pos == 1); // Error detected at parity bit position 1
    assert(strcmp(corrected, codeword) == 0);
    assert(strcmp(data_recovered, data) == 0);

    printf("test_hamming_generate_and_verify passed\n");
}

int main(void)
{
    test_hamming_generate_and_verify();

    printf("All Hamming tests passed successfully!\n");
    return 0;
}
