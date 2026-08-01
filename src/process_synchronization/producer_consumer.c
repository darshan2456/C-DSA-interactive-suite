#include "../utils/config.h"
#include "clear_screen.h"
#include "cross_platform_timer.h"
#include "process_synchronization.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5

void display_buffer_state(const int* buffer, int in, int out, int mutex, int empty, int full,
                          int prod_blocked, int cons_blocked)
{
    printf("\n\033[1;34m┌────────────────────────────────────────────────────────┐\033[0m");
    printf("\n\033[1;34m│                 PRODUCER-CONSUMER STATE                │\033[0m");
    printf("\n\033[1;34m├────────────────────────────────────────────────────────┤\033[0m");
    printf("\n│ Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (buffer[i] == 0)
        {
            printf("  -  ");
        }
        else
        {
            printf(" P%-3d", buffer[i]);
        }
        if (i < BUFFER_SIZE - 1)
        {
            printf(" |");
        }
    }
    printf(" ]           │");
    printf("\n│           in = %d, out = %d                              │", in, out);
    printf("\n\033[1;34m├────────────────────────────────────────────────────────┤\033[0m");
    printf("\n│ Semaphores:                                            │");
    printf("\n│   mutex     = %-10d (Mutual exclusion lock)       │", mutex);
    printf("\n│   empty_sem = %-10d (Available empty slots)       │", empty);
    printf("\n│   full_sem  = %-10d (Filled item slots)           │", full);
    printf("\n\033[1;34m├────────────────────────────────────────────────────────┤\033[0m");
    printf("\n│ Process States:                                        │");
    printf("\n│   Producer : %-50s   │", prod_blocked ? "\033[1;31mBLOCKED (Buffer Full)\033[0m"
                                                      : "\033[1;32mACTIVE/READY\033[0m");
    printf("\n│   Consumer : %-50s   │", cons_blocked ? "\033[1;31mBLOCKED (Buffer Empty)\033[0m"
                                                      : "\033[1;32mACTIVE/READY\033[0m");
    printf("\n\033[1;34m└────────────────────────────────────────────────────────┘\033[0m\n");
}

void pc_init(ProducerConsumerState* pc_state)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
        pc_state->buffer[i] = 0;
    pc_state->in = 0;
    pc_state->out = 0;
    pc_state->mutex = 1;
    pc_state->empty = BUFFER_SIZE;
    pc_state->full = 0;
    pc_state->item_counter = 1;
    pc_state->prod_blocked = 0;
    pc_state->cons_blocked = 0;
}

void producer_step(ProducerConsumerState* pc_state)
{
    int* buffer = pc_state->buffer;
    if (pc_state->empty == 0)
    {
        pc_state->prod_blocked = 1;
        printf("\033[1;31mProducer: Empty Semaphore is 0 (Buffer full). Producer is "
               "BLOCKED.\033[0m\n");
    }
    else
    {
        // wait(mutex)
        if (pc_state->mutex == 0)
        {
            printf("Producer: Mutex is held by another process. Waiting.\n");
        }
        else
        {
            pc_state->prod_blocked = 0;
            pc_state->empty--;
            pc_state->mutex--; // acquire lock

            buffer[pc_state->in] = pc_state->item_counter++;
            int produced = buffer[pc_state->in];
            printf("\033[1;32mProducer: Acquired mutex, placed item P%d at slot %d.\033[0m\n",
                   produced, pc_state->in);
            pc_state->in = (pc_state->in + 1) % BUFFER_SIZE;

            pc_state->mutex++; // release lock
            pc_state->full++;

            if (pc_state->cons_blocked)
            {
                pc_state->cons_blocked = 0;
                printf("\033[1;32mProducer: Signal(full_sem) sent. Consumer is now "
                       "UNBLOCKED.\033[0m\n");
            }
        }
    }
}

void pc_auto_stimulate(ProducerConsumerState* pc_state, int steps, int step_mode)
{
    srand((unsigned int)time(NULL));

    for (int s = 0; s < steps; s++)
    {
        if (!is_instant())
        {
            clear_screen();
        }
        printf("\n\033[1;36m=== Auto-Simulation (Step %d of %d) ===\033[0m\n", s + 1, steps);
        display_buffer_state(pc_state->buffer, pc_state->in, pc_state->out, pc_state->mutex,
                             pc_state->empty, pc_state->full, pc_state->prod_blocked,
                             pc_state->cons_blocked);

        int act = rand() % 2; // 0 = produce, 1 = consume
        if (act == 0)
        {
            printf("\n\033[1;33m[Simulated Event: Producer attempts action]\033[0m\n");
            producer_step(pc_state);
        }
        else
        {
            printf("\n\033[1;33m[Simulated Event: Consumer attempts action]\033[0m\n");
            consumer_step(pc_state);
        }

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

void consumer_step(ProducerConsumerState* pc_state)
{
    int* buffer = pc_state->buffer;
    if (pc_state->full == 0)
    {
        pc_state->cons_blocked = 1;
        printf("\033[1;31mConsumer: Full Semaphore is 0 (Buffer empty). Consumer is "
               "BLOCKED.\033[0m\n");
    }
    else
    {
        // wait(mutex)
        if (pc_state->mutex == 0)
        {
            printf("Consumer: Mutex is held by another process. Waiting.\n");
        }
        else
        {
            pc_state->cons_blocked = 0;
            pc_state->full--;
            pc_state->mutex--; // acquire lock

            int consumed = buffer[pc_state->out];
            buffer[pc_state->out] = 0;
            printf("\033[1;32mConsumer: Acquired mutex, consumed item P%d from slot %d.\033[0m\n",
                   consumed, pc_state->out);
            pc_state->out = (pc_state->out + 1) % BUFFER_SIZE;

            pc_state->mutex++; // release lock
            pc_state->empty++;

            if (pc_state->prod_blocked)
            {
                pc_state->prod_blocked = 0;
                printf("\033[1;32mConsumer: Signal(empty_sem) sent. Producer is now "
                       "UNBLOCKED.\033[0m\n");
            }
        }
    }
}
