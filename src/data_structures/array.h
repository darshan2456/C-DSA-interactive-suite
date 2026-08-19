#ifndef ARRAY_H
#define ARRAY_H

// Swap adjacent pairs in an integer array.
void swap_adjacent_pairs(int arr[], int length_of_array);

// Find the maximum element in an integer array. Returns The maximum value in the array.
int max_array(const int arr[], int length_of_array);

// Find the minimum element in an integer array. Returns The minimum value in the array.
int min_array(const int arr[], int length_of_array);

// Calculate the sum of all elements in an integer array. Returns the total sum.
int sum_array(const int arr[], int length_of_array);

// Calculate the average of all elements in an integer array. Returns the average as a double.
double average_array(const int arr[], int length_of_array);

// Print the contents of an integer array.
void print_array(const int arr[], int length_of_array);

// Reverse the contents of an integer array in place.
void reverse_array(int arr[], int length_of_array);

// Rotate the contents of an integer array to the right by k steps in place.
void rotate_array(int arr[], int length_of_array, int k);

// Run the array demonstration module.
void array_demo(void);

// Create a deep copy of an integer array. Returns a pointer to the newly allocated array.
int* clone_array(const int arr[], int length_of_array);

#endif
