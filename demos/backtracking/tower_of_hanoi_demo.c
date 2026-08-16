#include "backtracking.h"
#include "config.h"
#include "safe_input.h"
#include <stdio.h>

void tower_of_hanoi_demo(void)
{
    while (1)
    {
        int N;
        // Cap at 8 for console formatting visibility
        int status = safe_input_int(
            &N, "\nEnter the number of disks (between 1 and 8), or -1 to exit: ", 1, 8);
        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Tower of Hanoi...\n");
            return;
        }
        if (status == 0)
        {
            continue;
        }

        // Initialize state tracker for the 3 pegs
        int pegs[3][10] = {0};
        int counts[3] = {N, 0, 0};

        // Peg 0 starts with N disks, from largest (N) at bottom to smallest (1) at top
        for (int i = 0; i < N; i++)
        {
            pegs[0][i] = N - i;
        }

        printf("\nStarting Tower of Hanoi for %d disks...\n", N);
        dynamic_sleep();

        printf("\nInitial State:\n");
        print_towers_state(N, pegs, counts);

        // Pass 0 (source), 1 (auxiliary), 2 (destination)
        int total_moves = solve_tower_of_hanoi(N, 0, 1, 2, N, pegs, counts);

        printf("\nSuccessfully completed Tower of Hanoi in %d moves!\n", total_moves);
    }
}
