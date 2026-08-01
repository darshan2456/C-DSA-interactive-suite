#include "../utils/config.h"
#include "clear_screen.h"
#include "cross_platform_timer.h"
#include "process_synchronization.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char logs[3][128] = {"", "", ""};

static void add_log(const char* message)
{
    memmove(logs[0], logs[1], sizeof(logs[0]));
    memmove(logs[1], logs[2], sizeof(logs[1]));
    snprintf(logs[2], sizeof(logs[2]), "%s", message);
}

void step_process(int i, int* flag, int* turn, int* pc)
{
    int j = 1 - i;
    char msg[128];

    switch (pc[i])
    {
        case 0: // l1/m1: non-critical section
            pc[i] = 1;
            snprintf(msg, sizeof(msg), "P%d left non-critical section, ready to request entry.", i);
            add_log(msg);
            break;
        case 1: // l2/m2: ready := true
            flag[i] = 1;
            pc[i] = 2;
            snprintf(msg, sizeof(msg), "P%d set flag[%d] = 1 (ready%s = true).", i, i,
                     i == 0 ? "A" : "B");
            add_log(msg);
            break;
        case 2: // l3/m3: turn := other
            *turn = j;
            pc[i] = 3;
            snprintf(msg, sizeof(msg), "P%d set turn = %d (turn = %s).", i, j, j == 0 ? "A" : "B");
            add_log(msg);
            break;
        case 3: // l4/m4: await (ready_other == false || turn == self)
            if (flag[j] == 0 || *turn == i)
            {
                pc[i] = 4;
                snprintf(msg, sizeof(msg), "P%d evaluated await (free): entered CS! 🎉", i);
                add_log(msg);
            }
            else
            {
                snprintf(msg, sizeof(msg), "P%d evaluated await (busy): must busy-wait.", i);
                add_log(msg);
            }
            break;
        case 4: // l5/m5: critical section
            pc[i] = 5;
            snprintf(msg, sizeof(msg), "P%d finished critical section, ready to release flag.", i);
            add_log(msg);
            break;
        case 5: // l6/m6: ready := false
            flag[i] = 0;
            pc[i] = 0;
            snprintf(msg, sizeof(msg), "P%d reset flag[%d] = 0 (ready%s = false).", i, i,
                     i == 0 ? "A" : "B");
            add_log(msg);
            break;
    }
}

void petersons_init(int* flag, int* turn, int* pc)
{
    flag[0] = 0;
    flag[1] = 0;
    *turn = 0;
    pc[0] = 0;
    pc[1] = 0;
}

void petersons_reset(int* flag, int* turn, int* pc)
{
    petersons_init(flag, turn, pc);
    for (int i = 0; i < 3; i++)
        strcpy(logs[i], "");
    add_log("Peterson's Algorithm Simulation Reset Successfully.");
}
