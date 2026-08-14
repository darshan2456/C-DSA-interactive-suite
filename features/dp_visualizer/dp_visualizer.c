#include "dp_visualizer.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

void visualize_dp_table_1d(const char* label, const long long* table, int size, int active_index)
{
    if (table == NULL || size <= 0 || !is_terminal_interactive())
    {
        return;
    }

    // Clear terminal screen using ANSI code
    printf("\033[H\033[J");

    if (label)
    {
        printf("\n=== %s ===\n\n", label);
    }

    int start = 0;
    int end = size;
    if (size > 10)
    {
        start = active_index - 4;
        if (start < 0)
            start = 0;
        end = start + 9;
        if (end > size)
        {
            end = size;
            start = end - 9;
            if (start < 0)
                start = 0;
        }
    }

    // Top border
    printf("+");
    if (start > 0)
        printf("-----+");
    for (int i = start; i < end; i++)
    {
        printf("---------+");
    }
    if (end < size)
        printf("-----+");
    printf("\n");

    // Index header row
    printf("| Index   |");
    if (start > 0)
        printf(" ... |");
    for (int i = start; i < end; i++)
    {
        if (i == active_index)
        {
            printf(" \033[1;33m%7d\033[0m |", i); // Yellow active
        }
        else
        {
            printf(" %7d |", i);
        }
    }
    if (end < size)
        printf(" ... |");
    printf("\n");

    // Middle border
    printf("+---------+");
    if (start > 0)
        printf("-----+");
    for (int i = start; i < end; i++)
    {
        printf("---------+");
    }
    if (end < size)
        printf("-----+");
    printf("\n");

    // Values row
    printf("| Value   |");
    if (start > 0)
        printf(" ... |");
    for (int i = start; i < end; i++)
    {
        if (table[i] == -1)
        {
            printf(" %7s |", "-");
        }
        else
        {
            if (i == active_index)
            {
                printf(" \033[1;31m%7I64d\033[0m |", table[i]); // Red active value
            }
            else
            {
                printf(" %7I64d |", table[i]);
            }
        }
    }
    if (end < size)
        printf(" ... |");
    printf("\n");

    // Bottom border
    printf("+---------+");
    if (start > 0)
        printf("-----+");
    for (int i = start; i < end; i++)
    {
        printf("---------+");
    }
    if (end < size)
        printf("-----+");
    printf("\n\n");
    fflush(stdout);

    dynamic_sleep();
}

void visualize_dp_table_2d(const char* label, int** table, int rows, int cols,
                           const char* row_labels, const char* col_labels, int active_row,
                           int active_col)
{
    if (table == NULL || rows <= 0 || cols <= 0 || !is_terminal_interactive())
    {
        return;
    }

    // Clear terminal screen using ANSI code
    printf("\033[H\033[J");

    if (label)
    {
        printf("\n=== %s ===\n\n", label);
    }

    int start_col = 0;
    int end_col = cols;
    if (cols > 10)
    {
        start_col = active_col - 4;
        if (start_col < 0)
            start_col = 0;
        end_col = start_col + 9;
        if (end_col > cols)
        {
            end_col = cols;
            start_col = end_col - 9;
            if (start_col < 0)
                start_col = 0;
        }
    }

    int start_row = 0;
    int end_row = rows;
    if (rows > 12)
    {
        start_row = active_row - 5;
        if (start_row < 0)
            start_row = 0;
        end_row = start_row + 10;
        if (end_row > rows)
        {
            end_row = rows;
            start_row = end_row - 10;
            if (start_row < 0)
                start_row = 0;
        }
    }

    // Print column labels if present
    if (col_labels)
    {
        printf("           ");
        if (start_col > 0)
            printf("      ");
        for (int j = start_col; j < end_col; j++)
        {
            if (j - 1 >= 0 && j - 1 < (int)strlen(col_labels))
            {
                printf("    %c     ", col_labels[j - 1]);
            }
            else
            {
                printf("    -     ");
            }
        }
        printf("\n");
    }

    // Top border
    printf("     +");
    if (start_col > 0)
        printf("-----+");
    for (int j = start_col; j < end_col; j++)
    {
        printf("---------+");
    }
    if (end_col < cols)
        printf("-----+");
    printf("\n");

    // Column indices row
    printf("     |         |");
    if (start_col > 0)
        printf(" ... |");
    for (int j = start_col; j < end_col; j++)
    {
        if (j == active_col)
        {
            printf(" \033[1;33mcol %-3d\033[0m |", j);
        }
        else
        {
            printf(" col %-3d |", j);
        }
    }
    if (end_col < cols)
        printf(" ... |");
    printf("\n");

    // Separator border
    printf("-----+---------+");
    if (start_col > 0)
        printf("-----+");
    for (int j = start_col; j < end_col; j++)
    {
        printf("---------+");
    }
    if (end_col < cols)
        printf("-----+");
    printf("\n");

    if (start_row > 0)
    {
        printf("  .  | row ... |");
        if (start_col > 0)
            printf(" ... |");
        for (int j = start_col; j < end_col; j++)
        {
            printf("    .    |");
        }
        if (end_col < cols)
            printf(" ... |");
        printf("\n");
        printf("-----+---------+");
        if (start_col > 0)
            printf("-----+");
        for (int j = start_col; j < end_col; j++)
        {
            printf("---------+");
        }
        if (end_col < cols)
            printf("-----+");
        printf("\n");
    }

    // Rows
    for (int i = start_row; i < end_row; i++)
    {
        // Row label (character)
        char row_char = '-';
        if (row_labels && i - 1 >= 0 && i - 1 < (int)strlen(row_labels))
        {
            row_char = row_labels[i - 1];
        }
        printf("  %c  | row %-3d |", row_char, i);

        if (start_col > 0)
            printf(" ... |");
        for (int j = start_col; j < end_col; j++)
        {
            if (table[i][j] == -1)
            {
                printf(" %7s |", "-");
            }
            else
            {
                if (i == active_row && j == active_col)
                {
                    printf(" \033[1;31m%7d\033[0m |", table[i][j]); // Red active cell
                }
                else
                {
                    printf(" %7d |", table[i][j]);
                }
            }
        }
        if (end_col < cols)
            printf(" ... |");
        printf("\n");

        // Row separator border
        printf("-----+---------+");
        if (start_col > 0)
            printf("-----+");
        for (int j = start_col; j < end_col; j++)
        {
            printf("---------+");
        }
        if (end_col < cols)
            printf("-----+");
        printf("\n");
    }

    if (end_row < rows)
    {
        printf("  .  | row ... |");
        if (start_col > 0)
            printf(" ... |");
        for (int j = start_col; j < end_col; j++)
        {
            printf("    .    |");
        }
        if (end_col < cols)
            printf(" ... |");
        printf("\n");
        printf("-----+---------+");
        if (start_col > 0)
            printf("-----+");
        for (int j = start_col; j < end_col; j++)
        {
            printf("---------+");
        }
        if (end_col < cols)
            printf("-----+");
        printf("\n");
    }

    printf("\n");
    fflush(stdout);

    dynamic_sleep();
}

void visualize_mcm_tables(const int* m, const int* s, int n, int active_i, int active_j)
{
    if (m == NULL || s == NULL || n <= 0 || !is_terminal_interactive())
    {
        return;
    }

    // Clear terminal screen using ANSI code
    printf("\033[H\033[J");

    // Windowing for MCM if n is very large
    int start = 1;
    int end = n;
    if (n > 10)
    {
        start = active_i - 2;
        if (start < 1)
            start = 1;
        end = start + 7;
        if (end > n)
        {
            end = n;
            start = end - 7;
            if (start < 1)
                start = 1;
        }
    }

    printf("\n=== Matrix Chain Multiplication m-table (Minimum Scalar Multiplications) ===\n\n");
    // Column header
    printf("     |");
    if (start > 1)
        printf(" ... |");
    for (int j = start; j < end; j++)
    {
        printf("   %-6d |", j);
    }
    if (end < n)
        printf(" ... |");
    printf("\n-----+");
    if (start > 1)
        printf("-----+");
    for (int j = start; j < end; j++)
    {
        printf("----------+");
    }
    if (end < n)
        printf("-----+");
    printf("\n");

    for (int i = start; i < end; i++)
    {
        printf("  %-2d |", i);
        if (start > 1)
            printf(" ... |");
        for (int j = start; j < end; j++)
        {
            if (i > j)
            {
                printf(" %-8s |", "-");
            }
            else
            {
                int val = m[i * n + j];
                if (i == active_i && j == active_j)
                {
                    printf(" \033[1;31m%-8d\033[0m |", val);
                }
                else
                {
                    printf(" %-8d |", val);
                }
            }
        }
        if (end < n)
            printf(" ... |");
        printf("\n");
        printf("-----+");
        if (start > 1)
            printf("-----+");
        for (int j = start; j < end; j++)
        {
            printf("----------+");
        }
        if (end < n)
            printf("-----+");
        printf("\n");
    }

    printf("\n=== Matrix Chain Multiplication s-table (Bracket Splitting Points) ===\n\n");
    // Column header
    printf("     |");
    if (start > 1)
        printf(" ... |");
    for (int j = start; j < end; j++)
    {
        printf("   %-3d |", j);
    }
    if (end < n)
        printf(" ... |");
    printf("\n-----+");
    if (start > 1)
        printf("-----+");
    for (int j = start; j < end; j++)
    {
        printf("-------+");
    }
    if (end < n)
        printf("-----+");
    printf("\n");

    for (int i = start; i < end; i++)
    {
        printf("  %-2d |", i);
        if (start > 1)
            printf(" ... |");
        for (int j = start; j < end; j++)
        {
            if (i >= j)
            {
                printf(" %-5s |", "-");
            }
            else
            {
                int val = s[i * n + j];
                if (i == active_i && j == active_j)
                {
                    printf(" \033[1;33m%-5d\033[0m |", val);
                }
                else
                {
                    printf(" %-5d |", val);
                }
            }
        }
        if (end < n)
            printf(" ... |");
        printf("\n");
        printf("-----+");
        if (start > 1)
            printf("-----+");
        for (int j = start; j < end; j++)
        {
            printf("-------+");
        }
        if (end < n)
            printf("-----+");
        printf("\n");
    }

    printf("\n");
    fflush(stdout);

    dynamic_sleep();
}

void visualize_dp_bitmask(int mask, int pos, int cost, int N)
{
    if (!is_terminal_interactive())
    {
        return;
    }

    printf("\033[H\033[J");
    printf("\n=== TSP DP Bitmask Visualizer ===\n\n");

    printf("State: [ mask: \033[1;36m");
    for (int i = N - 1; i >= 0; i--)
    {
        if ((mask & (1 << i)))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\033[0m, pos: \033[1;33m%d\033[0m ]\n", pos);

    printf("Visited Cities: ");
    int first = 1;
    for (int i = 0; i < N; i++)
    {
        if ((mask & (1 << i)))
        {
            if (!first)
            {
                printf(", ");
            }
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");

    printf("Current Minimum Cost: ");
    if (cost >= 999999999)
    {
        printf("\033[1;31mINF\033[0m\n");
    }
    else
    {
        printf("\033[1;32m%d\033[0m\n", cost);
    }

    printf("\n-----------------------------------\n");
    fflush(stdout);

    dynamic_sleep();
}
