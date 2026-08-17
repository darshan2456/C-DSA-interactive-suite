#include "../../src/utils/display_header.h"
#include "../../src/utils/safe_input.h"
#include "error_correction_algorithms.h"
#include <stdio.h>
#include <string.h>

void adler32_demo(void)
{
    display_header("Adler-32 Checksum Demonstration");

    char buffer[256];
    int status = safe_input_string(buffer, sizeof(buffer),
                                   "Enter string data for Adler-32 checksum computation: ");
    if (status == INPUT_EXIT_SIGNAL || status == 0)
    {
        return;
    }

    uint32_t checksum = calculate_adler32(buffer, strlen(buffer));

    printf("\nInput String: %s\n", buffer);
    printf("Adler-32 Checksum (Hex): 0x%08X\n", checksum);
    printf("Adler-32 Checksum (Dec): %u\n\n", checksum);
}
