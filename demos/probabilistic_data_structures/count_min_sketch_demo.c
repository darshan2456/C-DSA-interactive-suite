#include "count_min_sketch.h"
#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_min_sketch_demo(void)
{
    display_header("Count-Min Sketch (Frequency Estimation)");

    CountMinSketch* sketch = cms_init(0.001, 0.01);
    if (!sketch)
    {
        printf("Failed to initialize Count-Min Sketch.\n");
        return;
    }

    printf("[INITIALIZED] Matrix Dimensions: %lu Width x %lu Depth\n",
           (unsigned long)sketch->width, (unsigned long)sketch->depth);

    printf("Simulating data stream insertion...\n");
    cms_add(sketch, "HTTP_GET_/api/v1/user", strlen("HTTP_GET_/api/v1/user"), 500);
    cms_add(sketch, "HTTP_POST_/api/v1/login", strlen("HTTP_POST_/api/v1/login"), 250);
    cms_add(sketch, "HTTP_GET_/api/v1/items", strlen("HTTP_GET_/api/v1/items"), 120);

    printf("\nFrequency Estimates:\n");
    printf(" 'HTTP_GET_/api/v1/user'  (Actual: 500) -> Estimated: %u\n",
           cms_estimate(sketch, "HTTP_GET_/api/v1/user", strlen("HTTP_GET_/api/v1/user")));
    printf(" 'HTTP_POST_/api/v1/login' (Actual: 250) -> Estimated: %u\n",
           cms_estimate(sketch, "HTTP_POST_/api/v1/login", strlen("HTTP_POST_/api/v1/login")));
    printf(" 'HTTP_DELETE_/admin'     (Actual:   0) -> Estimated: %u\n",
           cms_estimate(sketch, "HTTP_DELETE_/admin", strlen("HTTP_DELETE_/admin")));

    cms_free(sketch);
}
