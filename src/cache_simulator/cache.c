#include "cache.h"
#include <stdio.h>

void cache_init(Cache* cache, int capacity)
{
    if (capacity > CACHE_MAX_CAPACITY)
    {
        capacity = CACHE_MAX_CAPACITY;
    }
    if (capacity < 1)
    {
        capacity = 1;
    }
    cache->capacity = capacity;
    cache->size = 0;
    cache->fifo_index = 0;
    cache->access_counter = 0;
    cache->last_accessed_slot = -1;
    cache->hits = 0;
    cache->misses = 0;
    for (int i = 0; i < CACHE_MAX_CAPACITY; i++)
    {
        cache->blocks[i].page_id = -1;
        cache->blocks[i].is_valid = false;
        cache->blocks[i].is_dirty = false;
        cache->blocks[i].reference_bit = 0;
        cache->blocks[i].frequency = 0;
        cache->blocks[i].last_access_time = 0;
    }
}

void cache_print_status(const Cache* cache)
{
    printf("Cache state: [ ");
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid)
        {
            printf("%d ", cache->blocks[i].page_id);
        }
        else
        {
            printf("- ");
        }
    }
    printf("] (Hits: %d, Misses: %d)\n", cache->hits, cache->misses);
}

void cache_visualize(const Cache* cache, int highlighted_slot, bool is_hit)
{
    // Draw top border labels
    for (int i = 0; i < cache->capacity; i++)
    {
        printf("   [Frame %d]  ", i);
    }
    printf("\n");

    // Line 1: Top border of boxes
    for (int i = 0; i < cache->capacity; i++)
    {
        if (i == highlighted_slot)
        {
            printf(is_hit ? "\033[1;32m ┌─────────┐ \033[0m" : "\033[1;31m ┌─────────┐ \033[0m");
        }
        else
        {
            printf(" ┌─────────┐ ");
        }
    }
    printf("\n");

    // Line 2: Page ID
    for (int i = 0; i < cache->capacity; i++)
    {
        char page_str[16];
        if (cache->blocks[i].is_valid)
        {
            snprintf(page_str, sizeof(page_str), "Page: %-3d", cache->blocks[i].page_id);
        }
        else
        {
            snprintf(page_str, sizeof(page_str), "Page: -  ");
        }

        if (i == highlighted_slot)
        {
            printf(is_hit ? "\033[1;32m │ %s │ \033[0m" : "\033[1;31m │ %s │ \033[0m", page_str);
        }
        else
        {
            printf(" │ %s │ ", page_str);
        }
    }
    printf("\n");

    // Line 3: Reference bit
    for (int i = 0; i < cache->capacity; i++)
    {
        char ref_str[16];
        snprintf(ref_str, sizeof(ref_str), "Ref:  %-3d", cache->blocks[i].reference_bit);

        if (i == highlighted_slot)
        {
            printf(is_hit ? "\033[1;32m │ %s │ \033[0m" : "\033[1;31m │ %s │ \033[0m", ref_str);
        }
        else
        {
            printf(" │ %s │ ", ref_str);
        }
    }
    printf("\n");

    // Line 4: Frequency
    for (int i = 0; i < cache->capacity; i++)
    {
        char freq_str[16];
        snprintf(freq_str, sizeof(freq_str), "Freq: %-3d", cache->blocks[i].frequency);

        if (i == highlighted_slot)
        {
            printf(is_hit ? "\033[1;32m │ %s │ \033[0m" : "\033[1;31m │ %s │ \033[0m", freq_str);
        }
        else
        {
            printf(" │ %s │ ", freq_str);
        }
    }
    printf("\n");

    // Line 5: Dirty bit
    for (int i = 0; i < cache->capacity; i++)
    {
        char dirty_str[16];
        snprintf(dirty_str, sizeof(dirty_str), "Dirty:%-3s", cache->blocks[i].is_dirty ? "Yes" : "No ");

        if (i == highlighted_slot)
        {
            printf(is_hit ? "\033[1;32m │ %s │ \033[0m" : "\033[1;31m │ %s │ \033[0m", dirty_str);
        }
        else
        {
            printf(" │ %s │ ", dirty_str);
        }
    }
    printf("\n");

    // Line 6: Bottom border of boxes
    for (int i = 0; i < cache->capacity; i++)
    {
        if (i == highlighted_slot)
        {
            printf(is_hit ? "\033[1;32m └─────────┘ \033[0m" : "\033[1;31m └─────────┘ \033[0m");
        }
        else
        {
            printf(" └─────────┘ ");
        }
    }
    printf("\n");

    // Line 7: Clock Hand / Pointer
    for (int i = 0; i < cache->capacity; i++)
    {
        if (i == cache->fifo_index)
        {
            printf("\033[1;33m      ▲      \033[0m");
        }
        else
        {
            printf("             ");
        }
    }
    printf("\n");

    for (int i = 0; i < cache->capacity; i++)
    {
        if (i == cache->fifo_index)
        {
            printf("\033[1;33m  (Clock Hand) \033[0m");
        }
        else
        {
            printf("             ");
        }
    }
    printf("\n\n");
}

void cache_normalize_access_counter(Cache* cache)
{
    if (cache == NULL || cache->access_counter < 1000000)
    {
        return;
    }
    int min_access = cache->access_counter;
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid && cache->blocks[i].last_access_time < min_access)
        {
            min_access = cache->blocks[i].last_access_time;
        }
    }
    int max_access = 0;
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid)
        {
            cache->blocks[i].last_access_time -= min_access;
            if (cache->blocks[i].last_access_time > max_access)
            {
                max_access = cache->blocks[i].last_access_time;
            }
        }
    }
    cache->access_counter = max_access;
}
