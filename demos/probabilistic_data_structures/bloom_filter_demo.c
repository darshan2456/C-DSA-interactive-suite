#include "bloom_filter.h"
#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bloom_filter_demo(void)
{
    display_header("Bloom Filter (Set Membership)");

    BloomFilter* filter = bloom_init(100, 0.01);
    if (!filter)
    {
        printf("Failed to initialize Bloom Filter.\n");
        return;
    }

    printf("[INITIALIZED] Bit Array Size: %lu bits (%lu bytes), Hash Functions: %lu\n",
           (unsigned long)filter->bit_size, (unsigned long)((filter->bit_size + 7) / 8),
           (unsigned long)filter->num_hashes);

    const char* sample_items[] = {"user_alice", "user_bob", "user_charlie", "user_david"};
    for (size_t i = 0; i < 4; i++)
    {
        bloom_add(filter, sample_items[i], strlen(sample_items[i]));
        printf(" -> Inserted '%s'\n", sample_items[i]);
    }

    printf("\nTesting Set Membership Queries:\n");
    printf(" 'user_alice'   : %s\n", bloom_check(filter, "user_alice", strlen("user_alice"))
                                         ? "MAY BE PRESENT"
                                         : "DEFINITELY ABSENT");
    printf(" 'user_charlie' : %s\n", bloom_check(filter, "user_charlie", strlen("user_charlie"))
                                         ? "MAY BE PRESENT"
                                         : "DEFINITELY ABSENT");
    printf(" 'user_eve'     : %s\n", bloom_check(filter, "user_eve", strlen("user_eve"))
                                         ? "MAY BE PRESENT"
                                         : "DEFINITELY ABSENT");

    bloom_free(filter);
}
