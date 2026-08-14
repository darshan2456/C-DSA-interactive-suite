#include "cross_platform_timer.h"

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#define _DEFAULT_SOURCE
#include <unistd.h>
#endif

void sleep_seconds(float seconds)
{
    if (getenv("DSA_TEST_MODE") != NULL)
    {
        return;
    }
#ifdef _WIN32
    Sleep((DWORD)(seconds * 1000.0f));
#else
    usleep((useconds_t)(seconds * 1000000.0f));
#endif
}
