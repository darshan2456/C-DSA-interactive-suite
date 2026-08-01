#include "../utils/config.h"
#include "cache.h"
#include "clear_screen.h"
#include "cross_platform_timer.h"
#include "safe_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cache_lru_demo(void)
{
    Cache cache;
    int capacity;

    printf("\n=== LRU PAGE REPLACEMENT DEMO ===\n");
    printf("Enter cache capacity (1-%d): ", CACHE_MAX_CAPACITY);

    if (safe_input_int(&capacity, "", 1, CACHE_MAX_CAPACITY) != 1)
        return;

    cache_init(&cache, capacity);

    while (1)
    {
        if (!is_instant())
            clear_screen();

        printf("\n\033[1;36m=== LEAST RECENTLY USED (LRU) PAGE REPLACEMENT ===\033[0m\n");

        cache_visualize(&cache, cache.last_accessed_slot, cache.last_accessed_slot != -1);

        cache_print_status(&cache);

        printf("\nLRU Statistics\n");
        printf("Slot\tPage\tLast Access\n");

        for (int i = 0; i < cache.capacity; i++)
        {
            if (cache.blocks[i].is_valid)
            {
                printf("%d\t%d\t%d\n", i, cache.blocks[i].page_id,
                       cache.blocks[i].last_access_time);
            }
            else
            {
                printf("%d\t-\t-\n", i);
            }
        }

        printf("\nOptions\n");
        printf("1. Read Page\n");
        printf("2. Write Page\n");
        printf("3. Auto Simulation\n");
        printf("4. Reset Cache\n");
        printf("Enter option (-1 to exit): ");

        int choice;

        int status = safe_input_int(&choice, "", 1, 4);

        if (status == INPUT_EXIT_SIGNAL || choice == -1)
            break;

        if (status != 1)
            continue;

        switch (choice)
        {
            case 1:
            case 2:
            {
                int page;

                printf("\nEnter page number: ");

                if (safe_input_int(&page, "", 0, 999) != 1)
                    break;

                bool hit = cache_access_lru(&cache, page, choice == 2);

                printf("\n%s : Page %d\n", hit ? "CACHE HIT" : "CACHE MISS", page);

                sleep_seconds(1.0f);
                break;
            }

            case 3:
            {
                int steps;

                printf("Number of steps (1-20): ");

                if (safe_input_int(&steps, "", 1, 20) != 1)
                    break;

                srand((unsigned)time(NULL));

                for (int i = 0; i < steps; i++)
                {
                    int page = rand() % 10;
                    bool write = rand() % 2;

                    cache_access_lru(&cache, page, write);

                    if (!is_instant())
                    {
                        clear_screen();

                        printf("\nAuto Simulation (%d/%d)\n\n", i + 1, steps);

                        cache_visualize(&cache, cache.last_accessed_slot, false);

                        cache_print_status(&cache);

                        printf("\nLRU Statistics\n");
                        printf("Slot\tPage\tLast Access\n");

                        for (int j = 0; j < cache.capacity; j++)
                        {
                            if (cache.blocks[j].is_valid)
                            {
                                printf("%d\t%d\t%d\n", j, cache.blocks[j].page_id,
                                       cache.blocks[j].last_access_time);
                            }
                            else
                            {
                                printf("%d\t-\t-\n", j);
                            }
                        }

                        sleep_seconds(1.0f);
                    }
                }

                break;
            }

            case 4:
                cache_init(&cache, capacity);
                printf("\nCache Reset Successfully!\n");
                sleep_seconds(0.8f);
                break;
        }
    }
}