#include "display_header.h"
#include "hyperloglog.h"
#include "safe_input.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hyperloglog_demo(void)
{
    display_header("HyperLogLog (Cardinality Estimator)");

    uint8_t precision = 12;
    HyperLogLog* hll = hll_init(precision);
    if (!hll)
    {
        printf("Failed to initialize HyperLogLog.\n");
        return;
    }

    printf("[INITIALIZED] Registers: %lu (2^%d), Memory: %lu bytes\n", (unsigned long)hll->m,
           precision, (unsigned long)hll->m);

    size_t unique_count = 2500;
    printf("Inserting %lu distinct elements into HyperLogLog stream...\n",
           (unsigned long)unique_count);
    char buf[64];
    for (size_t i = 0; i < unique_count; i++)
    {
        snprintf(buf, sizeof(buf), "unique_stream_item_%lu", (unsigned long)i);
        hll_add(hll, buf, strlen(buf));
    }

    uint64_t est = hll_count(hll);
    double error_pct = (fabs((double)est - (double)unique_count) / (double)unique_count) * 100.0;

    printf("\nResults:\n");
    printf(" Actual Unique Count      : %lu\n", (unsigned long)unique_count);
    printf(" HLL Estimated Count     : %I64u\n", (unsigned long long)est);
    printf(" Relative Estimation Error: %.2f%%\n", error_pct);

    hll_free(hll);
}
