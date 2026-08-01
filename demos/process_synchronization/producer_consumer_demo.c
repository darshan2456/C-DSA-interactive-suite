#include "../utils/config.h"
#include "clear_screen.h"
#include "cross_platform_timer.h"
#include "process_synchronization.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5

void producer_consumer_demo(void)
{
    ProducerConsumerState pc_state;
    pc_init(&pc_state);
    while (1)
    {
        if (!is_instant())
        {
            clear_screen();
        }
        printf("\n\033[1;36m=== PRODUCER-CONSUMER PROBLEM SIMULATOR ===\033[0m\n");
        printf("This demo visualizes the behavior of Producer and Consumer processes\n");
        printf("synchronizing over a bounded circular buffer using Semaphores.\n");

        display_buffer_state(pc_state.buffer, pc_state.in, pc_state.out, pc_state.mutex,
                             pc_state.empty, pc_state.full, pc_state.prod_blocked,
                             pc_state.cons_blocked);

        printf("\nOptions:\n");
        printf("1. Run Producer (attempt to produce)\n");
        printf("2. Run Consumer (attempt to consume)\n");
        printf("3. Auto-simulate (runs random steps automatically)\n");
        printf("4. Reset Buffer state\n");
        printf("Enter option (-1 to return to menu): ");
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
            printf("\n\033[1;33m[Action: Producer Attempting to Produce]\033[0m\n");
            producer_step(&pc_state);
            printf("\nPress Enter to continue...");
            getchar();
        }
        else if (choice == 2)
        {
            printf("\n\033[1;33m[Action: Consumer Attempting to Consume]\033[0m\n");
            consumer_step(&pc_state);
            printf("\nPress Enter to continue...");
            getchar();
        }
        else if (choice == 3)
        {
            printf("\nEnter number of simulation steps to run automatically (1 to 20): ");
            int steps;
            int step_status = safe_input_int(&steps, "", 1, 20);
            if (step_status != 1)
                continue;

            int step_mode = 1; // Default to Animated Playback
            if (!is_instant())
            {
                int mode_choice;
                int mode_status = safe_input_int(
                    &mode_choice,
                    "\nSelect Simulation Playback Mode:\n1. Animated Playback (Automatic)\n2. "
                    "Step-by-Step (Manual)\nEnter choice (1 or 2), or '-1' to exit: ",
                    1, 2);
                if (mode_status == INPUT_EXIT_SIGNAL)
                {
                    continue;
                }
                if (mode_status == 1)
                {
                    step_mode = mode_choice;
                }
            }

            pc_auto_stimulate(&pc_state, steps, step_mode);
        }
        else if (choice == 4)
        {
            for (int i = 0; i < BUFFER_SIZE; i++)
                pc_state.buffer[i] = 0;
            pc_state.in = 0;
            pc_state.out = 0;
            pc_state.mutex = 1;
            pc_state.empty = BUFFER_SIZE;
            pc_state.full = 0;
            pc_state.prod_blocked = 0;
            pc_state.cons_blocked = 0;
            printf("\nBuffer has been reset successfully!\n");
            sleep_seconds(0.8f);
        }
    }
}
