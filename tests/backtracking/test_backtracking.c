#include "../../src/backtracking/backtracking.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// --- 1. N-Queens Tests ---
void test_n_queens()
{
    printf("[TEST] Running N-Queens...\n");
    assert(run_n_queens_test(4) == true && "N=4 should have a solution");
    assert(run_n_queens_test(8) == true && "N=8 should have a solution");
    assert(run_n_queens_test(3) == false && "N=3 has no valid solutions");
    printf("  --> PASSED\n");
}

// --- 2. Sudoku 6x6 Tests ---
void test_sudoku_6x6()
{
    printf("[TEST] Running Sudoku 6x6...\n");
    int solvable_board[6][6] = {{1, 5, 3, 4, 6, 0}, {4, 6, 2, 0, 1, 3}, {2, 4, 5, 6, 3, 1},
                                {0, 1, 6, 2, 4, 5}, {5, 3, 4, 1, 2, 6}, {6, 0, 1, 3, 5, 4}};
    assert(run_sudoku_test(solvable_board) == true && "Valid board should be solvable");

    int unsolvable_board[6][6] = {{1, 5, 3, 4, 6, 1}, {4, 6, 2, 0, 1, 3}, {2, 4, 5, 6, 3, 1},
                                  {0, 1, 6, 2, 4, 5}, {5, 3, 4, 1, 2, 6}, {6, 0, 1, 3, 5, 4}};
    assert(run_sudoku_test(unsolvable_board) == false && "Invalid board should fail");
    printf("  --> PASSED\n");
}

// --- 3. Rat in a Maze 6x6 Tests ---
void test_rat_in_maze()
{
    printf("[TEST] Running Rat in a Maze 6x6...\n");
    int solvable_maze[6][6] = {{1, 1, 1, 1, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1},
                               {0, 1, 0, 0, 0, 1}, {1, 1, 0, 1, 1, 1}, {1, 0, 0, 1, 0, 1}};
    assert(run_rat_in_maze_test(solvable_maze) == true && "Valid maze should have a path");

    int blocked_maze[6][6] = {{1, 0, 1, 1, 0, 1}, {0, 0, 0, 1, 0, 1}, // Blocked at spawn
                              {1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 1},
                              {1, 1, 0, 1, 1, 1}, {1, 0, 0, 1, 0, 1}};
    assert(run_rat_in_maze_test(blocked_maze) == false && "Blocked maze should return false");
    printf("  --> PASSED\n");
}

// --- 4. Graph Coloring Tests ---
void test_graph_coloring()
{
    printf("[TEST] Running Graph Coloring (K4)...\n");
    assert(run_graph_coloring_test(3) == false && "K4 needs exactly 4 colors");
    assert(run_graph_coloring_test(4) == true && "K4 is solvable with 4 colors");
    printf("  --> PASSED\n");
}

// --- 5. Knight's Tour Tests ---
void test_knights_tour()
{
    printf("[TEST] Running Knight's Tour...\n");
    assert(run_knights_tour_test(5) == true && "5x5 board should be solvable");
    printf("  --> PASSED\n");
}

// --- 6. Tower of Hanoi Tests ---
void test_tower_of_hanoi()
{
    printf("[TEST] Running Tower of Hanoi...\n");

    // Test 3 disks
    int pegs3[3][10] = {0};
    int counts3[3] = {3, 0, 0};
    for (int i = 0; i < 3; i++)
        pegs3[0][i] = 3 - i;
    assert(solve_tower_of_hanoi(3, 0, 1, 2, 0, pegs3, counts3) == 7 &&
           "3 disks should take exactly 7 moves");

    // Test 4 disks
    int pegs4[3][10] = {0};
    int counts4[3] = {4, 0, 0};
    for (int i = 0; i < 4; i++)
        pegs4[0][i] = 4 - i;
    assert(solve_tower_of_hanoi(4, 0, 1, 2, 0, pegs4, counts4) == 15 &&
           "4 disks should take exactly 15 moves");

    // Test 5 disks
    int pegs5[3][10] = {0};
    int counts5[3] = {5, 0, 0};
    for (int i = 0; i < 5; i++)
        pegs5[0][i] = 5 - i;
    assert(solve_tower_of_hanoi(5, 0, 1, 2, 0, pegs5, counts5) == 31 &&
           "5 disks should take exactly 31 moves");

    printf("  --> PASSED\n");
}

// --- 7. String Permutation Tests ---
void test_string_permutation()
{
    printf("[TEST] Running String Permutation...\n");

    char str1[] = "a";
    bool last1[5] = {false};
    assert(solve_string_permutation(str1, 0, 1, last1,false) == 1 &&
           "1 character should have exactly 1 permutation");

    char str2[] = "ab";
    bool last2[5] = {false};
    assert(solve_string_permutation(str2, 0, 2, last2,false) == 2 &&
           "2 characters should have exactly 2 permutations");

    char str3[] = "abc";
    bool last3[5] = {false};
    assert(solve_string_permutation(str3, 0, 3, last3,false) == 6 &&
           "3 characters should have exactly 6 permutations");

    char str4[] = "abcd";
    bool last4[5] = {false};
    assert(solve_string_permutation(str4, 0, 4, last4,false) == 24 &&
           "4 characters should have exactly 24 permutations");

    char str5[] = "abcde";
    bool last5[5] = {false};
    assert(solve_string_permutation(str5, 0, 5, last5,false) == 120 &&
           "5 characters should have exactly 120 permutations");

    printf(" --> PASSED\n");
}

int main()
{
    printf("\n===================================\n");
    printf("   Running Backtracking Test Suite \n");
    printf("===================================\n\n");

    test_n_queens();
    test_sudoku_6x6();
    test_rat_in_maze();
    test_graph_coloring();
    test_knights_tour();
    test_tower_of_hanoi();
    test_string_permutation();

    printf("\n===================================\n");
    printf(" ✅ ALL BACKTRACKING TESTS PASSED!\n");
    printf("===================================\n\n");

    return 0;
}