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
    // Shift logs up
    memmove(logs[0], logs[1], sizeof(logs[0]));
    memmove(logs[1], logs[2], sizeof(logs[1]));
    snprintf(logs[2], sizeof(logs[2]), "%s", message);
}

static void get_phil_box(PhilosopherState state, int id, char* box_buf)
{
    const char* state_color;
    const char* state_name;
    switch (state)
    {
        case EATING:
            state_color = "\033[1;32m"; // Green
            state_name = "EATING  ";
            break;
        case HUNGRY:
            state_color = "\033[1;33m"; // Yellow
            state_name = "HUNGRY  ";
            break;
        default:
            state_color = "\033[1;36m"; // Cyan
            state_name = "THINKING";
            break;
    }
    // Printable length inside box is exactly 12 characters, e.g. "P0: THINKING" or "P1: EATING  "
    snprintf(box_buf, 64, "%sP%d: %s\033[0m", state_color, id, state_name);
}

static void get_chopstick_str(int id, const int* chopsticks, char* buf)
{
    if (chopsticks[id] == -1)
    {
        snprintf(buf, 64, "\033[0;37mC%d: FREE\033[0m", id);
    }
    else
    {
        snprintf(buf, 64, "\033[1;31mC%d: P%d  \033[0m", id, chopsticks[id]);
    }
}

void display_table_state(const int* chopsticks, const PhilosopherState* phil_states, int strategy)
{
    char box0[64], box1[64], box2[64], box3[64], box4[64];
    char c0[64], c1[64], c2[64], c3[64], c4[64];

    get_phil_box(phil_states[0], 0, box0);
    get_phil_box(phil_states[1], 1, box1);
    get_phil_box(phil_states[2], 2, box2);
    get_phil_box(phil_states[3], 3, box3);
    get_phil_box(phil_states[4], 4, box4);

    get_chopstick_str(0, chopsticks, c0);
    get_chopstick_str(1, chopsticks, c1);
    get_chopstick_str(2, chopsticks, c2);
    get_chopstick_str(3, chopsticks, c3);
    get_chopstick_str(4, chopsticks, c4);

    const char* strategy_name = "Unknown";
    if (strategy == 0)
        strategy_name = "Naive (Allows Deadlock)";
    else if (strategy == 1)
        strategy_name = "Asymmetric (Odd/Even ID)";
    else if (strategy == 2)
        strategy_name = "Arbitrator (State Check)";

    printf("\n\033[1;34m┌────────────────────────────────────────────────────────┐\033[0m");
    printf("\n\033[1;34m│               DINING PHILOSOPHERS TABLE                │\033[0m");
    printf("\n\033[1;34m├────────────────────────────────────────────────────────┤\033[0m");
    printf("\n│ Strategy: %-44s │", strategy_name);
    printf("\n\033[1;34m├────────────────────────────────────────────────────────┤\033[0m\n");

    printf("                      ┌──────────────┐\n");
    printf("                      │ %s │\n", box0);
    printf("                      └──────────────┘\n");
    printf("                %s          %s\n", c0, c1);
    printf("                       │              │\n");
    printf("        ┌──────────────┴───┐      ┌───┴──────────────┐\n");
    printf("        │   %s   │      │   %s   │\n", box4, box1);
    printf("        └──────────────────┘      └──────────────────┘\n");
    printf("           %s                  %s\n", c4, c2);
    printf("               │                              │\n");
    printf("        ┌──────┴───────────┐      ┌───────────┴──────┐\n");
    printf("        │   %s   │──────│   %s   │\n", box3, box2);
    printf("        └──────────────────┘      └──────────────────┘\n");
    printf("                       %s\n", c3);

    printf("\033[1;34m└────────────────────────────────────────────────────────┘\033[0m\n");
}

static void test_arbitrator(int i, int* chopsticks, PhilosopherState* phil_states)
{
    int left_neighbor = (i + 4) % 5;
    int right_neighbor = (i + 1) % 5;
    if (phil_states[i] == HUNGRY && phil_states[left_neighbor] != EATING &&
        phil_states[right_neighbor] != EATING)
    {
        phil_states[i] = EATING;
        chopsticks[i] = i;
        chopsticks[right_neighbor] = i;

        char msg[128];
        snprintf(msg, sizeof(msg), "Arbitrator: P%d acquired chopsticks %d & %d. Starts EATING!", i,
                 i, right_neighbor);
        add_log(msg);
    }
}

static void attempt_eat(int i, int strategy, int* chopsticks, PhilosopherState* phil_states)
{
    int left = i;
    int right = (i + 1) % 5;
    char msg[128];

    if (strategy == 0)
    { // Naive
        if (chopsticks[left] == i)
        {
            // Already holds left, try right
            if (chopsticks[right] == -1)
            {
                chopsticks[right] = i;
                phil_states[i] = EATING;
                snprintf(msg, sizeof(msg), "P%d acquired Right Chopstick %d and is now EATING! 🎉",
                         i, right);
                add_log(msg);
            }
            else
            {
                snprintf(msg, sizeof(msg), "P%d holds Left C%d; Right C%d is busy (held by P%d).",
                         i, left, right, chopsticks[right]);
                add_log(msg);
            }
        }
        else if (chopsticks[left] == -1)
        {
            chopsticks[left] = i;
            snprintf(msg, sizeof(msg), "P%d acquired Left Chopstick %d.", i, left);
            add_log(msg);

            // Attempt right in the same step
            if (chopsticks[right] == -1)
            {
                chopsticks[right] = i;
                phil_states[i] = EATING;
                snprintf(msg, sizeof(msg), "P%d acquired Right Chopstick %d and is now EATING! 🎉",
                         i, right);
                add_log(msg);
            }
            else
            {
                snprintf(msg, sizeof(msg), "P%d is waiting for Right Chopstick %d.", i, right);
                add_log(msg);
            }
        }
        else
        {
            snprintf(msg, sizeof(msg), "P%d cannot acquire Left Chopstick %d (held by P%d).", i,
                     left, chopsticks[left]);
            add_log(msg);
        }
    }
    else if (strategy == 1)
    { // Asymmetric
        if (i % 2 == 0)
        { // Even ID: Left first, then Right
            if (chopsticks[left] == i)
            {
                if (chopsticks[right] == -1)
                {
                    chopsticks[right] = i;
                    phil_states[i] = EATING;
                    snprintf(msg, sizeof(msg),
                             "P%d acquired Right Chopstick %d and is now EATING! 🎉", i, right);
                    add_log(msg);
                }
                else
                {
                    snprintf(msg, sizeof(msg), "P%d holds Left C%d; Right C%d is held by P%d.", i,
                             left, right, chopsticks[right]);
                    add_log(msg);
                }
            }
            else if (chopsticks[left] == -1)
            {
                chopsticks[left] = i;
                snprintf(msg, sizeof(msg), "P%d (Even) acquired Left Chopstick %d.", i, left);
                add_log(msg);

                if (chopsticks[right] == -1)
                {
                    chopsticks[right] = i;
                    phil_states[i] = EATING;
                    snprintf(msg, sizeof(msg),
                             "P%d acquired Right Chopstick %d and is now EATING! 🎉", i, right);
                    add_log(msg);
                }
                else
                {
                    snprintf(msg, sizeof(msg), "P%d is waiting for Right Chopstick %d.", i, right);
                    add_log(msg);
                }
            }
            else
            {
                snprintf(msg, sizeof(msg), "P%d cannot acquire Left Chopstick %d (held by P%d).", i,
                         left, chopsticks[left]);
                add_log(msg);
            }
        }
        else
        { // Odd ID: Right first, then Left
            if (chopsticks[right] == i)
            {
                if (chopsticks[left] == -1)
                {
                    chopsticks[left] = i;
                    phil_states[i] = EATING;
                    snprintf(msg, sizeof(msg),
                             "P%d acquired Left Chopstick %d and is now EATING! 🎉", i, left);
                    add_log(msg);
                }
                else
                {
                    snprintf(msg, sizeof(msg), "P%d holds Right C%d; Left C%d is held by P%d.", i,
                             right, left, chopsticks[left]);
                    add_log(msg);
                }
            }
            else if (chopsticks[right] == -1)
            {
                chopsticks[right] = i;
                snprintf(msg, sizeof(msg), "P%d (Odd) acquired Right Chopstick %d.", i, right);
                add_log(msg);

                if (chopsticks[left] == -1)
                {
                    chopsticks[left] = i;
                    phil_states[i] = EATING;
                    snprintf(msg, sizeof(msg),
                             "P%d acquired Left Chopstick %d and is now EATING! 🎉", i, left);
                    add_log(msg);
                }
                else
                {
                    snprintf(msg, sizeof(msg), "P%d is waiting for Left Chopstick %d.", i, left);
                    add_log(msg);
                }
            }
            else
            {
                snprintf(msg, sizeof(msg), "P%d cannot acquire Right Chopstick %d (held by P%d).",
                         i, right, chopsticks[right]);
                add_log(msg);
            }
        }
    }
    else if (strategy == 2)
    { // Arbitrator
        test_arbitrator(i, chopsticks, phil_states);
    }
}

void trigger_philosopher(int i, int strategy, int* chopsticks, PhilosopherState* phil_states)
{
    char msg[128];
    if (phil_states[i] == EATING)
    {
        if (strategy == 2)
        { // Arbitrator
            phil_states[i] = THINKING;
            chopsticks[i] = -1;
            chopsticks[(i + 1) % 5] = -1;
            snprintf(msg, sizeof(msg), "P%d finished eating and is now THINKING.", i);
            add_log(msg);

            // Test neighbors to unblock them
            test_arbitrator((i + 4) % 5, chopsticks, phil_states);
            test_arbitrator((i + 1) % 5, chopsticks, phil_states);
        }
        else
        {
            chopsticks[i] = -1;
            chopsticks[(i + 1) % 5] = -1;
            phil_states[i] = THINKING;
            snprintf(msg, sizeof(msg), "P%d released chopsticks %d & %d, now THINKING.", i, i,
                     (i + 1) % 5);
            add_log(msg);
        }
    }
    else if (phil_states[i] == THINKING)
    {
        phil_states[i] = HUNGRY;
        snprintf(msg, sizeof(msg), "P%d became HUNGRY.", i);
        add_log(msg);
        attempt_eat(i, strategy, chopsticks, phil_states);
    }
    else if (phil_states[i] == HUNGRY)
    {
        attempt_eat(i, strategy, chopsticks, phil_states);
    }
}

void dp_reset(DiningTable* table)
{
    for (int c = 0; c < 5; c++)
        table->chopsticks[c] = -1;
    for (int p = 0; p < 5; p++)
        table->phil_states[p] = THINKING;
    for (int i = 0; i < 3; i++)
        strcpy(logs[i], "");
    add_log("Simulation table reset successfully.");
}

void dp_change_strategy(DiningTable* table, int new_strategy)
{
    if (new_strategy < 0 || new_strategy > 2)
    {
        add_log("Invalid strategy selection. No changes made.");
        return;
    }
    table->strategy = new_strategy;
    dp_reset(table);
    add_log("Deadlock prevention strategy changed successfully.");
}

bool dp_is_deadlocked(const DiningTable* table)
{
    int hungry_count = 0;
    int eating_count = 0;
    int chopsticks_held_count = 0;
    for (int p = 0; p < 5; p++)
    {
        if (table->phil_states[p] == HUNGRY)
            hungry_count++;
        if (table->phil_states[p] == EATING)
            eating_count++;
    }
    for (int c = 0; c < 5; c++)
    {
        if (table->chopsticks[c] != -1)
            chopsticks_held_count++;
    }

    return (hungry_count == 5 && eating_count == 0 && chopsticks_held_count == 5);
}

void dp_auto_simulate(DiningTable* table, int steps, int step_mode)
{
    srand((unsigned int)time(NULL));

    for (int s = 0; s < steps; s++)
    {
        // Stop if deadlocked
        if (dp_is_deadlocked(table))
        {
            add_log("Auto-simulation stopped due to Deadlock.");
            break;
        }

        if (!is_instant())
        {
            clear_screen();
        }

        printf("\n\033[1;36m=== Auto-Simulation (Step %d of %d) ===\033[0m\n", s + 1, steps);

        display_table_state(table->chopsticks, table->phil_states, table->strategy);

        printf("\n\033[1;35mRecent Activity Logs:\033[0m\n");
        for (int i = 0; i < 3; i++)
        {
            if (strlen(logs[i]) > 0)
                printf(" - %s\n", logs[i]);
            else
                printf(" -\n");
        }

        // Random philosopher action
        int p_id = rand() % 5;
        trigger_philosopher(p_id, table->strategy, table->chopsticks, table->phil_states);

        if (step_mode == 2)
        {
            printf("\nPress [ENTER] to step to next action...");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }
        else if (!is_instant())
        {
            sleep_seconds(1.2f);
        }
    }
    printf("\nAuto-simulation finished. Press Enter to continue...");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}
