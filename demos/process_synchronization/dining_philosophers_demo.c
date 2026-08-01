#include "../utils/config.h"
#include "clear_screen.h"
#include "cross_platform_timer.h"
#include "process_synchronization.h"
#include "safe_input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char logs[3][128] = {"", "", ""};

static void dp_init(DiningTable* table)
{
    for (int c = 0; c < 5; c++)
        table->chopsticks[c] = -1;
    for (int p = 0; p < 5; p++)
        table->phil_states[p] = THINKING;
    table->strategy = 0; // Default to Naive
    for (int i = 0; i < 3; i++)
        strcpy(logs[i], "");
}

void dining_philosophers_demo(void)
{
    DiningTable table;
    dp_init(&table);

    while (1)
    {
        if (!is_instant())
        {
            clear_screen();
        }
        printf("\n\033[1;36m=== DINING PHILOSOPHERS PROBLEM SIMULATOR ===\033[0m\n");
        printf(
            "This simulation models the classic Dining Philosophers synchronization challenge.\n");

        display_table_state(table.chopsticks, table.phil_states, table.strategy);

        // Check for deadlock
        bool is_deadlocked = dp_is_deadlocked(&table);

        if (is_deadlocked)
        {
            printf("\n\033[1;31m⚠️ DEADLOCK DETECTED!\033[0m\n");
            printf("\033[1;31m- All 5 philosophers are HUNGRY and holding exactly 1 "
                   "chopstick.\033[0m\n");
            printf("\033[1;31m- Circular wait condition is met. No philosopher can "
                   "progress.\033[0m\n");
            printf("\033[1;33mTip: Change strategy (Option 3) or reset simulation (Option 4) to "
                   "resolve.\033[0m\n");
        }

        printf("\n\033[1;35mRecent Activity Logs:\033[0m\n");
        for (int i = 0; i < 3; i++)
        {
            if (strlen(logs[i]) > 0)
            {
                printf(" - %s\n", logs[i]);
            }
            else
            {
                printf(" -\n");
            }
        }

        printf("\nOptions:\n");
        printf("1. Trigger Philosopher state change (0-4)\n");
        printf("2. Auto-simulate random steps\n");
        printf("3. Change Deadlock Prevention Strategy\n");
        printf("4. Reset simulation table\n");
        printf("Enter option (-1 to return to main menu): ");
        fflush(stdout);

        int choice;
        int status = safe_input_int(&choice, "", 1, 4);
        if (status == INPUT_EXIT_SIGNAL || choice == -1)
        {
            break;
        }
        if (status == 0)
        {
            continue;
        }

        if (choice == 1)
        {
            printf("\nEnter Philosopher ID (0-4): ");
            int p_id;
            int p_status = safe_input_int(&p_id, "", 0, 4);
            if (p_status == 1)
            {
                trigger_philosopher(p_id, table.strategy, table.chopsticks, table.phil_states);
            }
        }
        else if (choice == 2)
        {
            printf("\nEnter number of auto-simulation steps: ");
            int steps;
            int s_status = safe_input_int(&steps, "", 1, 1000);
            if (s_status == 1)
            {
                printf("Choose step mode:\n");
                printf("1. Instant (no delay)\n");
                printf("2. Step-by-step (press Enter to proceed)\n");
                printf("Enter step mode (1-2): ");
                int step_mode;
                int sm_status = safe_input_int(&step_mode, "", 1, 2);
                if (sm_status == 1)
                {
                    dp_auto_simulate(&table, steps, step_mode);
                }
            }
        }
        else if (choice == 3)
        {
            if (!is_instant())
            {
                clear_screen();
            }
            printf("\n\033[1;36m=== Choose Deadlock Prevention Strategy ===\033[0m\n");
            printf("1. Naive (Philosophers pick left then right; allows deadlock)\n");
            printf("2. Asymmetric (Even philosophers pick left first; odd pick right first; "
                   "prevents deadlock)\n");
            printf("3. Arbitrator (Philosophers only acquire chopsticks if both are free; prevents "
                   "deadlock)\n");
            printf("\nEnter strategy (1-3): ");

            int strat_choice;
            int stra_status = safe_input_int(&strat_choice, "", 1, 3);
            if (stra_status == 1)
            {
                dp_change_strategy(&table, strat_choice - 1);
            }
        }
        else if (choice == 4)
        {
            dp_reset(&table);
            printf("\nSimulation state has been reset!\n");
            sleep_seconds(0.8f);
        }
    }
}
