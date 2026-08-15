#include "array.h"
#include "safe_input.h"
#include <stdio.h>

void array_demo(void)
{
    while (1)
    {
        int arr_length_status;
        int length_of_array;

    start_array:
        arr_length_status = safe_input_int(
            &length_of_array, // taking length of the array
            "\n\nenter length of the array, (between 1 and 100), enter '-1' to exit :- ", 1, 100);

        if (arr_length_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting array demo\n");
            return;
        }
        if (arr_length_status == 0)
        {
            goto start_array;
        }

        int arr[length_of_array];

        for (int i = 0; i < length_of_array; i++)
        { // main loop which accepts arr elements value
            int arr_element_status;
        enter_arr_element:
            printf("enter array element %d, (between 1 and 100), enter '-1' to exit:- ", i);
            arr_element_status = safe_input_int(&arr[i], NULL, 1, 100);

            if (arr_element_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting array demo");
                return;
            }
            if (arr_element_status == 0)
            {
                goto enter_arr_element;
            }
            printf("\n");
        }

        printf("array you inserted is :- "); // print before swap, as user gave, same to same
        print_array(arr, length_of_array);

        swap_adjacent_pairs(arr, length_of_array); // swapping happens here
        printf("\nafter swap, the array is :- ");
        print_array(arr, length_of_array);

        swap_adjacent_pairs(arr, length_of_array); // revert to normal
        printf("\noriginal array:- ");
        print_array(arr, length_of_array);

        int max_element = max_array(arr, length_of_array); // max element of array
        printf("\n\nmaximum element is :- %d", max_element);

        int min_element = min_array(arr, length_of_array); // min element of array
        printf("\nminimum element is :- %d", min_element);

        int sum = sum_array(arr, length_of_array); // sum of array elements
        printf("\nsum of elements is :- %d", sum);

        double average = average_array(arr, length_of_array); // average of array elements
        printf("\naverage of elements is :- %.2f", average);

        reverse_array(arr, length_of_array); // array is reversed in memory
        printf("\n\nreverse of the array is :- ");
        print_array(arr, length_of_array);

        reverse_array(arr, length_of_array); // revert to normal
        printf("\noriginal array :- ");
        print_array(arr, length_of_array);
    }
}
