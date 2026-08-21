#ifndef ARRAY_H
#define ARRAY_H

/**
 * @brief Swap adjacent pairs in an integer array.
 * @param arr The integer array to modify.
 * @param length_of_array The number of elements in the array.
 */
void swap_adjacent_pairs(int arr[], int length_of_array);

/**
 * @brief Find the maximum element in an integer array.
 * @param arr The integer array to search.
 * @param length_of_array The number of elements in the array.
 * @return The maximum value in the array.
 */
int max_array(const int arr[], int length_of_array);

/**
 * @brief Find the minimum element in an integer array.
 * @param arr The integer array to search.
 * @param length_of_array The number of elements in the array.
 * @return The minimum value in the array.
 */
int min_array(const int arr[], int length_of_array);

/**
 * @brief Calculate the sum of all elements in an integer array.
 * @param arr The integer array to sum.
 * @param length_of_array The number of elements in the array.
 * @return The total sum.
 */
int sum_array(const int arr[], int length_of_array);

/**
 * @brief Calculate the average of all elements in an integer array.
 * @param arr The integer array to process.
 * @param length_of_array The number of elements in the array.
 * @return The average as a double.
 */
double average_array(const int arr[], int length_of_array);

/**
 * @brief Print the contents of an integer array.
 * @param arr The integer array to print.
 * @param length_of_array The number of elements in the array.
 */
void print_array(const int arr[], int length_of_array);

/**
 * @brief Reverse the contents of an integer array in place.
 * @param arr The integer array to reverse.
 * @param length_of_array The number of elements in the array.
 */
void reverse_array(int arr[], int length_of_array);

/**
 * @brief Rotate the contents of an integer array to the right by k steps in place.
 * @param arr The integer array to rotate.
 * @param length_of_array The number of elements in the array.
 * @param k The number of steps to rotate.
 */
void rotate_array(int arr[], int length_of_array, int k);

/**
 * @brief Run the array demonstration module.
 */
void array_demo(void);

/**
 * @brief Create a deep copy of an integer array.
 * @param arr The integer array to copy.
 * @param length_of_array The number of elements in the array.
 * @return A pointer to the newly allocated array.
 */
int* clone_array(const int arr[], int length_of_array);

#endif