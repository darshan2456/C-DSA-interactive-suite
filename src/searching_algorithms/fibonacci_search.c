#include "sorting_algorithms_n2.h"

int fibonacci_search(int arr[], int target, int length_of_array)
{
    if (length_of_array == 0)
    {
        return -1;
    }

    int fib_m2 = 0;              // (m-2)'th Fibonacci No.
    int fib_m1 = 1;              // (m-1)'th Fibonacci No.
    int fib_m = fib_m2 + fib_m1; // m'th Fibonacci No.

    while (fib_m < length_of_array)
    {
        fib_m2 = fib_m1;
        fib_m1 = fib_m;
        fib_m = fib_m2 + fib_m1;
    }

    int offset = -1;

    while (fib_m > 1)
    {
        int i = (offset + fib_m2 < length_of_array - 1) ? offset + fib_m2 : length_of_array - 1;

        if (arr[i] < target)
        {
            fib_m = fib_m1;
            fib_m1 = fib_m2;
            fib_m2 = fib_m - fib_m1;
            offset = i;
        }
        else if (arr[i] > target)
        {
            fib_m = fib_m2;
            fib_m1 = fib_m1 - fib_m2;
            fib_m2 = fib_m - fib_m1;
        }
        else
        {
            return i;
        }
    }

    if (fib_m1 && offset + 1 < length_of_array && arr[offset + 1] == target)
    {
        return offset + 1;
    }

    return -1;
}
