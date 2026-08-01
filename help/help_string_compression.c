#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_string_compression_menu(void)
{
    display_header("Help - Strings & Compression");
    printf("STRING ALGORITHMS:\n");
    printf("    • Naive Matching: Checks the pattern at every position of the text. O(N*M).\n");
    printf("    • KMP (Knuth-Morris-Pratt): Uses a prefix table to skip re-checking "
           "characters. O(N+M).\n");
    printf("    • Rabin-Karp: Uses rolling hashes to compare pattern and text windows.\n");
    printf("    • Suffix Array: Sorted array of all suffixes, enabling fast substring queries.\n");
    printf("    • Kasai's LCP Array: Computes the longest common prefixes between consecutive\n");
    printf("      suffixes in the Suffix Array in O(N) time. Essential for substring "
           "queries.\n\n");

    printf("COMPRESSION & ENCODING:\n");
    printf("    • Huffman Coding: Lossless data compression using variable-length prefix "
           "codes.\n");
    printf("    • Run-Length Encoding (RLE): Simple form of compression for repeating "
           "characters.\n");
    printf("    • LZW (Lempel-Ziv-Welch): Dictionary-based compression algorithm.\n");
    printf("    • BWT (Burrows-Wheeler Transform): Reversible string permutation that groups\n");
    printf("      similar characters together to improve compression ratios.\n");
    printf("    • Move-to-Front (MTF) Transform: Shifts processed symbols to the front of the "
           "alphabet,\n");
    printf("      producing sequences of small numbers for consecutive/repeating characters.\n\n");

    printf("HOW TO RUN IN THIS SUITE:\n");
    printf("    • String Algorithms: Main Menu ➔ Option 13.\n");
    printf("    • String Compression: Main Menu ➔ Option 18.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
