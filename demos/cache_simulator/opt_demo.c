#include "../utils/config.h"
#include "cache.h"
#include "clear_screen.h"
#include "cross_platform_timer.h"
#include "safe_input.h"

#include <stdio.h>

#define MAX_REF_LEN 30

void cache_opt_demo(void)
{
    Cache cache;
    int capacity;

    printf("\n=== OPTIMAL PAGE REPLACEMENT DEMO ===\n");
    printf("Enter cache capacity (1-%d): ", CACHE_MAX_CAPACITY);

    if (safe_input_int(&capacity, "", 1, CACHE_MAX_CAPACITY) != 1)
        return;

    cache_init(&cache, capacity);

    int ref_str[MAX_REF_LEN];
    int ref_len;

    printf("Enter reference string length (1-%d): ", MAX_REF_LEN);

    if (safe_input_int(&ref_len, "", 1, MAX_REF_LEN) != 1)
        return;

    printf("Enter %d page numbers:\n", ref_len);

    for (int i = 0; i < ref_len; i++)
    {
        printf("Page %d: ", i + 1);
        if (safe_input_int(&ref_str[i], "", 0, 999) != 1)
            return;
    }

    int current = 0;

    while (1)
    {
        if (!is_instant())
            clear_screen();

        printf("\n\033[1;36m=== OPTIMAL PAGE REPLACEMENT ===\033[0m\n");

        cache_visualize(&cache, cache.last_accessed_slot, cache.last_accessed_slot != -1);

        cache_print_status(&cache);

        printf("\nReference String:\n");

        for (int i = 0; i < ref_len; i++)
        {
            if (i == current)
                printf("[%-2d] ", ref_str[i]);
            else
                printf(" %-2d  ", ref_str[i]);
        }

        printf("\n\nCurrent Position : %d / %d\n", current + 1, ref_len);

        printf("\nOptions\n");
        printf("1. Execute Next Reference\n");
        printf("2. Auto Simulation\n");
        printf("3. Reset Cache\n");
        printf("Enter option (-1 to exit): ");

        int choice;

        int status = safe_input_int(&choice, "", 1, 3);

        if (status == INPUT_EXIT_SIGNAL || choice == -1)
            break;

        if (status != 1)
            continue;

        switch (choice)
        {
            case 1:
            {
                if (current >= ref_len)
                {
                    printf("\nReference string completed.\n");
                    sleep_seconds(1.0f);
                    break;
                }

                bool hit =
                    cache_access_opt(&cache, ref_str[current], ref_str, ref_len, current, false);

                printf("\n%s : Page %d\n", hit ? "CACHE HIT" : "CACHE MISS", ref_str[current]);

                current++;

                sleep_seconds(1.0f);
                break;
            }

            case 2:
            {
                while (current < ref_len)
                {
                    cache_access_opt(&cache, ref_str[current], ref_str, ref_len, current, false);

                    current++;

                    if (!is_instant())
                    {
                        clear_screen();

                        printf("\nAuto Simulation (%d/%d)\n\n", current, ref_len);

                        cache_visualize(&cache, cache.last_accessed_slot, false);

                        cache_print_status(&cache);

                        printf("\nReference String:\n");

                        for (int i = 0; i < ref_len; i++)
                        {
                            if (i == current)
                                printf("[%-2d] ", ref_str[i]);
                            else
                                printf(" %-2d  ", ref_str[i]);
                        }

                        sleep_seconds(1.0f);
                    }
                }

                printf("\nReference string completed.\n");
                sleep_seconds(1.0f);
                break;
            }

            case 3:
                cache_init(&cache, capacity);
                current = 0;
                printf("\nCache Reset Successfully!\n");
                sleep_seconds(0.8f);
                break;
        }
    }
}