#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdio.h>
#include <string.h>

void crc_xor_operation(char* dividend, const char* divisor, int pos)
{
    int n = (int)strlen(divisor);

    for (int i = 0; i < n; i++)
    {
        dividend[pos + i] = (dividend[pos + i] == divisor[i]) ? '0' : '1';
    }
}

// crc_generate: computes the CRC remainder for `data` using `generator` via
// modulo-2 (XOR) division.  The remainder is written to `remainder_out` and,
// if `codeword_out` is not NULL, the full transmitted codeword (data + CRC) is
// written there too.
void crc_generate(const char* data, const char* generator, char* remainder_out, char* codeword_out)
{
    int data_len = (int)strlen(data);
    int generator_len = (int)strlen(generator);

    // Append (generator_len - 1) zero bits to data to form the dividend
    char dividend[(CHECKSUM_MAX_BITS * 2) + 1];

    /* Reject inputs that would overflow the fixed-size dividend buffer */
    if (data_len <= 0 || generator_len <= 0 ||
        data_len + generator_len - 1 > (int)(sizeof(dividend) - 1))
    {
        if (remainder_out)
            remainder_out[0] = '\0';
        if (codeword_out)
            codeword_out[0] = '\0';
        return;
    }

    strncpy(dividend, data, sizeof(dividend) - 1);
    dividend[sizeof(dividend) - 1] = '\0';
    for (int i = 0; i < generator_len - 1; i++)
    {
        dividend[data_len + i] = '0';
    }
    int dividend_len = data_len + generator_len - 1;
    dividend[dividend_len] = '\0';

    // Modulo-2 division
    for (int i = 0; i <= dividend_len - generator_len; i++)
    {
        if (dividend[i] == '1')
        {
            crc_xor_operation(dividend, generator, i);
        }
    }

    // Extract the remainder (last generator_len-1 bits)
    for (int i = 0; i < generator_len - 1; i++)
    {
        remainder_out[i] = dividend[dividend_len - (generator_len - 1) + i];
    }
    remainder_out[generator_len - 1] = '\0';

    if (codeword_out != NULL)
    {
        strncpy(codeword_out, data, (CHECKSUM_MAX_BITS * 2));
        codeword_out[(CHECKSUM_MAX_BITS * 2)] = '\0';
        strcat(codeword_out, remainder_out);
    }
}

// crc_verify: re-divides a received `codeword` by `generator`.  If the
// remainder is all zeros the frame is clean and 1 is returned; otherwise 0 is
// returned (error detected).  The computed remainder is optionally written to
// `remainder_out`.
int crc_verify(const char* codeword, const char* generator, char* remainder_out)
{
    int generator_len = (int)strlen(generator);
    int codeword_len = (int)strlen(codeword);

    char dividend[(CHECKSUM_MAX_BITS * 2) + 1];
    strncpy(dividend, codeword, sizeof(dividend) - 1);
    dividend[sizeof(dividend) - 1] = '\0';

    for (int i = 0; i <= codeword_len - generator_len; i++)
    {
        if (dividend[i] == '1')
        {
            crc_xor_operation(dividend, generator, i);
        }
    }

    // The remainder is the last (generator_len-1) bits
    char remainder[CHECKSUM_MAX_BITS + 1];
    strncpy(remainder, &dividend[codeword_len - (generator_len - 1)], sizeof(remainder) - 1);
    remainder[sizeof(remainder) - 1] = '\0';

    if (remainder_out != NULL)
    {
        strncpy(remainder_out, remainder, CHECKSUM_MAX_BITS);
        remainder_out[CHECKSUM_MAX_BITS] = '\0';
    }

    for (int i = 0; remainder[i] != '\0'; i++)
    {
        if (remainder[i] == '1')
        {
            return 0; // Error detected
        }
    }
    return 1; // No error
}
