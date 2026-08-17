#include "display_header.h"
#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adler32_demo(void)
{
    display_header("Adler-32 Checksum Demonstration");

    char buffer[256];
    int status =
        safe_input_string(buffer, sizeof(buffer), "Enter string data for Adler-32 checksum computation: ");
    if (status == INPUT_EXIT_SIGNAL || status == 0)
    {
        return;
    }

    size_t len = strlen(buffer);
    uint32_t checksum = calculate_adler32(buffer, len);

    printf("\nInput Data: \"%s\"\n", buffer);
    printf("Length:     %zu bytes\n", len);
    printf("Adler-32 Checksum (Hex):     0x%08X\n", checksum);
    printf("Adler-32 Checksum (Decimal): %u\n\n", checksum);
}
