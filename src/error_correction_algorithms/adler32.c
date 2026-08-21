#include "error_correction_algorithms.h"
#include <stddef.h>
#include <stdint.h>

#define MOD_ADLER 65521

uint32_t calculate_adler32(const char* data, size_t length)
{
    if (data == NULL)
    {
        return 1U;
    }

    uint32_t a = 1;
    uint32_t b = 0;

    for (size_t i = 0; i < length; i++)
    {
        a = (a + (uint8_t)data[i]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}
