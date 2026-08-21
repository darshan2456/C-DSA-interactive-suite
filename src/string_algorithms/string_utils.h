#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

// Checks if a given string is a palindrome (reads the same forwards and backwards)
bool is_palindrome(const char* str);

// Checks if two strings are anagrams of each other (contain the exact same characters in any order)
bool is_anagram(const char* str1, const char* str2);

#endif // STRING_UTILS_H
