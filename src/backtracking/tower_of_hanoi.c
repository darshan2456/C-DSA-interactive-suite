#include "backtracking.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_HANOI_DISKS 10

static const char* disk_colors[] = {
    "\x1b[0m",  // Reset
    "\x1b[31m", // 1 Red
    "\x1b[32m", // 2 Green
    "\x1b[33m", // 3 Yellow
    "\x1b[34m", // 4 Blue
    "\x1b[35m", // 5 Magenta
    "\x1b[36m", // 6 Cyan
    "\x1b[91m", // 7 Bright Red
    "\x1b[92m", // 8 Bright Green
    "\x1b[93m", // 9 Bright Yellow
    "\x1b[94m"  // 10 Bright Blue
};

// Internal function to print the current state of the pegs
void print_towers_state(int total_disks, int pegs[3][MAX_HANOI_DISKS], int counts[3])
{
    printf("\n");
    // Print row by row, from top (total_disks - 1) to bottom (0)
    for (int row = total_disks - 1; row >= 0; row--)
    {
        for (int p = 0; p < 3; p++)
        {
            if (row < counts[p])
            {
                int disk_size = pegs[p][row];
                int spaces = total_disks - disk_size;

                // Print leading spaces
                for (int i = 0; i < spaces; i++)
                    printf(" ");

                // Print left half of disk with color
                printf("%s", disk_colors[disk_size % 11]);
                for (int i = 0; i < disk_size; i++)
                    printf("=");

                // Print peg
                printf("\x1b[0m|");

                // Print right half of disk with color
                printf("%s", disk_colors[disk_size % 11]);
                for (int i = 0; i < disk_size; i++)
                    printf("=");
                printf("\x1b[0m");

                // Print trailing spaces
                for (int i = 0; i < spaces; i++)
                    printf(" ");
            }
            else
            {
                // Print empty peg line
                for (int i = 0; i < total_disks; i++)
                    printf(" ");
                printf("|");
                for (int i = 0; i < total_disks; i++)
                    printf(" ");
            }
            printf("   "); // Space between pegs
        }
        printf("\n");
    }

    // Base
    for (int p = 0; p < 3; p++)
    {
        for (int i = 0; i < total_disks * 2 + 1; i++)
            printf("-");
        printf("   ");
    }
    printf("\n");

    // Labels
    int center = total_disks;
    for (int p = 0; p < 3; p++)
    {
        for (int i = 0; i < center; i++)
            printf(" ");
        printf("%c", 'A' + p);
        for (int i = 0; i < center; i++)
            printf(" ");
        printf("   ");
    }
    printf("\n\n");

    dynamic_sleep();
}

int solve_tower_of_hanoi(int n, int source, int auxiliary, int destination, int disks,
                         int pegs[3][MAX_HANOI_DISKS], int counts[3])
{
    if (n == 1)
    {
        // Move one disk from source to destination
        int disk = pegs[source][counts[source] - 1];
        counts[source]--;

        pegs[destination][counts[destination]] = disk;
        counts[destination]++;

        // Visualize if disks > 0 (during tests we can pass disks=0 to skip prints)
        if (disks > 0)
        {
            printf("\nMove disk %d from %c to %c:\n", disk, 'A' + source, 'A' + destination);
            print_towers_state(disks, pegs, counts);
        }
        return 1;
    }

    int moves = 0;
    moves += solve_tower_of_hanoi(n - 1, source, destination, auxiliary, disks, pegs, counts);
    moves += solve_tower_of_hanoi(1, source, auxiliary, destination, disks, pegs, counts);
    moves += solve_tower_of_hanoi(n - 1, auxiliary, source, destination, disks, pegs, counts);

    return moves;
}
