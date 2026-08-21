#include "display_header.h"
#include "safe_input.h"
#include "searching_algorithms.h"
#include <stdio.h>

void searching_algorithms_demo(void)
{
    int searching_algo_status, searching_algo_choice;
    while (1)
    {
        display_header("Searching Algorithms");

        searching_algo_status = safe_input_int(&searching_algo_choice,
                                               "\nenter 1 for linear search demo"
                                               "\nenter 2 for binary search"
                                               "\nenter 3 for recursive binary search"
                                               "\nenter 4 for interpolation search"
                                               "\nenter 5 for jump search"
                                               "\nenter 6 for exponential search"
                                               "\nenter 7 for ternary search"
                                               "\nenter 8 for fibonacci search"
                                               "\nenter choice (\'-1\' to exit, or \'help\') : ",
                                               1, 8);

        if (searching_algo_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting searching_algorithms_demo....\n");
            return;
        }

        if (searching_algo_status == 0)
            continue;

        switch (searching_algo_choice)
        {
            case 1:
                display_header("Linear Search");
                linear_search_demo();
                break;
            case 2:
                display_header("Binary Search");
                binary_search_demo();
                break;
            case 3:
                display_header("Recursive Binary Search");
                binary_search_recursive_demo();
                break;
            case 4:
                display_header("Interpolation Search");
                interpolation_search_demo();
                break;
            case 5:
                display_header("Jump Search");
                jump_search_demo();
                break;
            case 6:
                display_header("Exponential Search");
                exponential_search_demo();
                break;
            case 7:
                display_header("Ternary Search");
                ternary_search_demo();
                break;
            case 8:
                display_header("Fibonacci Search");
                fibonacci_search_demo();
                break;
        }
    }
}
