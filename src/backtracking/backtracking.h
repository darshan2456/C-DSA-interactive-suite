#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <stdbool.h>

#define MAX_V 10

// Graph Coloring Topology Structure
typedef struct
{
    const char* name;
    int num_vertices;
    int matrix[MAX_V][MAX_V];
} GraphTopology;

// Demos
void backtracking_demo(void);
void n_queens_demo(void);
void sudoku_demo(void);
void rat_in_maze_demo(void);
void graph_coloring_demo(void);
void knights_tour_demo(void);
void tower_of_hanoi_demo(void);
void string_permutation_demo(void);

// Exposed Solvers & Visualization Helper Functions

void print_towers_state(int total_disks, int pegs[3][10], int counts[3]);

int solve_string_permutation(char str[], int depth, int length, bool last[], bool visualize);

int solve_tower_of_hanoi(int n, int source, int auxiliary, int destination, int disks,
                         int pegs[3][10], int counts[3]);
bool solve_n_queens_util(int N, char board[8][8], int col);

bool solve_sudoku_util(int grid[6][6], int row, int col);
void print_sudoku_board(int grid[6][6], int original_grid[6][6]);

bool solve_maze_util(int maze[6][6], int x, int y, int solution[6][6]);
void print_maze_state(int maze[6][6], int solution[6][6]);

int solve_standard(int x, int y, int move_count, int board[8][8], int N);
int solve_warnsdorff(int x, int y, int move_count, int board[8][8], int N);
void print_knights_tour_board(int N, int board[8][8], int curr_x, int curr_y);

int solve_graph_coloring_util(const GraphTopology* graph, int m, int colors[MAX_V], int v,
                              int delay_time);
void print_graph_state(const GraphTopology* graph, int colors[MAX_V], int current_vertex,
                       const char* stage_msg, int delay_time);

// Test Wrappers
bool run_n_queens_test(int n);
bool run_sudoku_test(int test_grid[6][6]);
bool run_rat_in_maze_test(int test_maze[6][6]);
bool run_knights_tour_test(int n);
bool run_graph_coloring_test(int colors_allowed);

#endif // BACKTRACKING_H
