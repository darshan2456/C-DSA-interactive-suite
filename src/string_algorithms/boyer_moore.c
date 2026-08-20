#include "string_algorithms.h"
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

// Helper function to get the maximum of two integers
static int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Preprocessing for the bad character heuristic
static void bad_character_heuristic(const char* pattern, int size, int bad_char[ALPHABET_SIZE])
{
    // Initialize all occurrences as -1
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        bad_char[i] = -1;
    }

    // Fill the actual value of last occurrence of a character
    for (int i = 0; i < size; i++)
    {
        bad_char[(unsigned char)pattern[i]] = i;
    }
}

/**
 * Searches for occurrences of a pattern in a text using the Boyer-Moore algorithm.
 * This implementation uses the Bad Character Heuristic.
 *
 * @param text The text to search in.
 * @param pattern The pattern to search for.
 */
void boyer_moore_search(const char* text, const char* pattern)
{
    if (text == NULL || pattern == NULL)
    {
        printf("Text or pattern is NULL.\n");
        return;
    }

    int m = strlen(pattern);
    int n = strlen(text);

    if (m == 0)
    {
        printf("Pattern is empty.\n");
        return;
    }

    if (m > n)
    {
        printf("Pattern is longer than text.\n");
        return;
    }

    int bad_char[ALPHABET_SIZE];
    bad_character_heuristic(pattern, m, bad_char);

    int s = 0; // s is the shift of the pattern with respect to text
    int matches = 0;

    while (s <= (n - m))
    {
        int j = m - 1;

        // Keep reducing index j of pattern while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        // If the pattern is present at current shift
        if (j < 0)
        {
            printf("Pattern found at index %d\n", s);
            matches++;

            // Shift the pattern so that the next character in text aligns with the last occurrence
            // of it in pattern.
            // The condition s+m < n is necessary for the case when pattern occurs at the end of
            // text
            s += (s + m < n) ? m - bad_char[(unsigned char)text[s + m]] : 1;
        }
        else
        {
            // Shift the pattern so that the bad character in text aligns with the last occurrence
            // of it in pattern. The max function is used to make sure that we get a positive shift.
            s += max(1, j - bad_char[(unsigned char)text[s + j]]);
        }
    }

    if (matches == 0)
    {
        printf("Pattern not found in the text.\n");
    }
}
