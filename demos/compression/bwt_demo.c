#include "../utils/config.h"
#include "clear_screen.h"
#include "compression.h"
#include "cross_platform_timer.h"
#include "safe_input.h"

#include <stdio.h>
#include <string.h>

void bwt_mtf_demo(void)
{
    while (1)
    {
        if (!is_instant())
            clear_screen();

        printf("\n\033[1;36m=== BURROWS-WHEELER TRANSFORM & MOVE-TO-FRONT DEMO ===\033[0m\n");

        printf("Enter a string (-1 to exit): ");

        char input[256];

        int status = safe_input_string(input, sizeof(input), "");

        if (status == INPUT_EXIT_SIGNAL)
            break;

        int len = strlen(input);

        if (len == 0)
        {
            printf("\nEmpty string!\n");
            sleep_seconds(1.0f);
            continue;
        }

        char bwt[256];
        char restored[256];

        char mtf[256];
        char decoded[256];

        int primary;

        int bwt_len = bwt_forward(input, bwt, &primary);

        if (bwt_len < 0)
        {
            printf("\nBWT failed!\n");
            sleep_seconds(1.0f);
            continue;
        }

        mtf_encode(bwt, mtf, bwt_len);

        mtf_decode(mtf, decoded, bwt_len);

        bwt_inverse(decoded, primary, restored);

        printf("\nOriginal String : %s\n", input);
        printf("BWT Output      : %s\n", bwt);
        printf("Primary Index   : %d\n", primary);

        printf("\nMTF Output      : ");

        for (int i = 0; i < bwt_len; i++)
        {
            printf("%d ", (unsigned char)mtf[i]);
        }

        printf("\n");

        printf("\nDecoded MTF     : %s\n", decoded);
        printf("Recovered Text  : %s\n", restored);

        if (strcmp(input, restored) == 0)
            printf("\n\033[1;32mRound-trip Successful!\033[0m\n");
        else
            printf("\n\033[1;31mRound-trip Failed!\033[0m\n");

        printf("\nPress ENTER to continue...");
        getchar();
    }
}