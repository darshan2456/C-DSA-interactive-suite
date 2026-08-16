#include "array.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void swap_adjacent_pairs(int arr[], int length_of_array)
{

    for (int i = 0; i < length_of_array - 1; i += 2)
    {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
}

void reverse_array(int arr[], int length_of_array)
{
    for (int i = 0; i < (length_of_array / 2); i++)
    {
        int temp = arr[i];
        arr[i] = arr[length_of_array - i - 1];
        arr[length_of_array - i - 1] = temp;
    }
}

void rotate_array(int arr[], int length_of_array, int k)
{
    if (length_of_array <= 1)
        return;

    k = k % length_of_array;
    if (k < 0)
    {
        k += length_of_array;
    }
    if (k == 0)
        return;

    reverse_array(arr, length_of_array);
    reverse_array(arr, k);
    reverse_array(arr + k, length_of_array - k);
}

void print_array(const int arr[], int length_of_array)
{
    printf("[");
    for (int i = 0; i < length_of_array; i++)
    {
        printf("%d", arr[i]);
        if (i < length_of_array - 1)
            printf(",");
    }
    printf("]");
}

int max_array(const int arr[], int length_of_array)
{
    if (length_of_array <= 0)
    {
        return INT_MIN;
    }
    int max_element = arr[0];
    for (int i = 1; i < length_of_array; i++)
    {
        if (arr[i] > max_element)
        {
            max_element = arr[i];
        }
    }
    return max_element;
}

int min_array(const int arr[], int length_of_array)
{
    if (length_of_array <= 0)
    {
        return INT_MAX;
    }
    int min_element = arr[0];
    for (int i = 1; i < length_of_array; i++)
    {
        if (arr[i] < min_element)
        {
            min_element = arr[i];
        }
    }
    return min_element;
}

int sum_array(const int arr[], int length_of_array)
{
    int sum = 0;
    for (int i = 0; i < length_of_array; i++)
    {
        sum += arr[i];
    }
    return sum;
}

double average_array(const int arr[], int length_of_array)
{
    if (length_of_array == 0)
    {
        return 0.0;
    }
    return (double)sum_array(arr, length_of_array) / length_of_array;
}