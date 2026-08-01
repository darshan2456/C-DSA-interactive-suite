#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_bit_manipulation_menu(void)
{
    display_header("Help - Bit Manipulation");

    printf("BIT MANIPULATION & MASKING:\n");
    printf("    Bit manipulation is the act of algorithmically\n");
    printf("    manipulating bits or other pieces of data shorter\n");
    printf("    than a byte. Bit masking involves using a \"mask\"\n");
    printf("    (a binary pattern) to keep, change, or remove\n");
    printf("    specific bits of a value.\n\n");

    printf("WHY IT'S CRUCIAL:\n");
    printf("    • Competitive Programming: Offers fast O(1) solutions\n");
    printf("      for math problems, subset generation, and DP.\n");
    printf("    • Networking & Cryptography: IP subnetting, checksums,\n");
    printf("      and encryption rely on shifting and XORing bits.\n");
    printf("    • Memory-Constrained Environments: Embedded systems\n");
    printf("      pack boolean flags into integers to save RAM.\n\n");

    printf("CORE OPERATIONS:\n");
    printf("    • Set Bit (x | (1 << k)): Turns k-th bit to 1.\n");
    printf("    • Clear Bit (x & ~(1 << k)): Turns k-th bit to 0.\n");
    printf("    • Toggle Bit (x ^ (1 << k)): Flips the k-th bit.\n");
    printf("    • Check Bit ((x >> k) & 1): Returns k-th bit (0 or 1).\n\n");

    printf("ADVANCED TECHNIQUES:\n");
    printf("    • Brian Kernighan's: x = x & (x - 1)\n");
    printf("      Clears the lowest set bit. Counts set bits in O(K).\n");
    printf("    • Power of Two: (x > 0) && ((x & (x - 1)) == 0).\n");
    printf("    • XOR Swap: a ^= b; b ^= a; a ^= b; (no temp var).\n");
    printf("    • Rightmost Set Bit: (x & -x) extracts lowest 1.\n\n");

    printf("ALGORITHMIC APPLICATIONS:\n");
    printf("    • Find Unique Element: In an array where every element\n");
    printf("      appears twice except one, XORing all elements\n");
    printf("      leaves the unique one (since x ^ x = 0).\n");
    printf("    • Subset Generation: A set of N elements has 2^N\n");
    printf("      subsets. Looping from 0 to 2^N-1 and treating the\n");
    printf("      loop counter's bits as include flags generates\n");
    printf("      all combinations (Power Set).\n\n");

    printf("INTERACTIVE 32-BIT VISUALIZER:\n");
    printf("    • Bit Grid Display: Renders 32-bit integers as formatted 4-byte grids.\n");
    printf("    • Interactive Bit Toggling: Interactively flip individual bit positions.\n");
    printf("    • Real-time Formats: View signed/unsigned decimal, hex (0x), and binary.\n\n");

    printf("HOW TO RUN IN THIS SUITE:\n");
    printf("    1. Exit to the main menu and select option 18.\n");
    printf("    2. Choose from the sub-menu to visualize algorithms.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
