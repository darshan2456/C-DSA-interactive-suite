#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_error_correction_menu(void)
{
    display_header("Help - Error Detection & Correction");

    printf("--- PARITY BIT (SIMPLE PARITY CHECK) ---\n\n");
    printf("SIMPLE PARITY CHECK:\n");
    printf("    A simple error detection scheme where a single redundant bit (parity bit)\n");
    printf("    is added to a block of data to make the total number of 1s either even\n");
    printf("    (Even Parity) or odd (Odd Parity).\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • Even Parity: If the data has an odd number of 1s, the parity bit is set\n");
    printf("      to 1. If it has an even number of 1s, the parity bit is set to 0.\n");
    printf("    • Odd Parity: If the data has an even number of 1s, the parity bit is set\n");
    printf("      to 1. If it has an odd number of 1s, the parity bit is set to 0.\n\n");
    printf("LIMITATIONS:\n");
    printf("    • Can only detect single-bit errors (or an odd number of bit errors).\n");
    printf("    • Cannot detect even number of bit errors (they cancel each other out).\n");
    printf("    • Cannot correct any errors.\n\n");

    printf("--- VERTICAL REDUNDANCY CHECK (VRC) ---\n\n");
    printf("VERTICAL REDUNDANCY CHECK (VRC):\n");
    printf("    Also known as Character Parity. In this method, a parity bit is added\n");
    printf("    to each character (or byte/data word) in a block of data.\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • Each data word/character is processed individually.\n");
    printf("    • A parity bit (even or odd) is appended to each character block.\n");
    printf("    • Commonly used in asynchronous data transmission.\n\n");
    printf("LIMITATIONS:\n");
    printf("    • Only detects single-bit errors within each individual character.\n");
    printf("    • Cannot detect errors if two bits in the same character are flipped.\n\n");

    printf("--- LONGITUDINAL REDUNDANCY CHECK (LRC) ---\n\n");
    printf("LONGITUDINAL REDUNDANCY CHECK (LRC):\n");
    printf("    Also known as Block Parity. Instead of applying parity to individual\n");
    printf("    characters alone, VRC characters are grouped in blocks, and a parity\n");
    printf("    bit is calculated for each column of the entire block.\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • Data is organized in a grid (rows and columns).\n");
    printf("    • A Block Check Character (BCC) is generated where each bit in the BCC\n");
    printf("      represents the parity of the corresponding column.\n\n");
    printf("ADVANTAGES & LIMITATIONS:\n");
    printf("    • Better than VRC: Can detect burst errors within a block.\n");
    printf("    • If two bits in the same column flip, the column parity check will\n");
    printf("      fail to detect the error.\n\n");

    printf("--- CHECKSUM ---\n\n");
    printf("CHECKSUM:\n");
    printf("    A redundancy error-detection scheme used heavily in network protocols\n");
    printf("    (like TCP/IP and UDP).\n\n");
    printf("HOW IT WORKS (Sender Side):\n");
    printf("    • The data unit is divided into k sections of n bits each.\n");
    printf("    • All sections are added together using one's complement arithmetic.\n");
    printf("    • The sum is complemented (complemented sum = Checksum) and appended\n");
    printf("      to the data block.\n\n");
    printf("HOW IT WORKS (Receiver Side):\n");
    printf("    • The receiver divides the received data into sections and adds them.\n");
    printf("    • If the sum's complement is 0, the data is accepted; else, rejected.\n\n");
    printf("LIMITATIONS:\n");
    printf("    • If the values of two data blocks shift in opposite directions by the\n");
    printf("      same amount, the sum remains unchanged, failing to detect the error.\n\n");

    printf("--- ADLER-32 CHECKSUM ---\n\n");
    printf("ADLER-32 CHECKSUM:\n");
    printf("    A checksum algorithm invented by Mark Adler. It is a modification of the\n");
    printf(
        "    Fletcher checksum, trading some reliability for software speed compared to CRC.\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • Computes two 16-bit sums: A (sum of bytes) and B (sum of all individual A "
           "values).\n");
    printf("    • Both sums are calculated modulo 65521 (the largest prime less than 2^16).\n");
    printf("    • The final 32-bit checksum is concatenated as (B << 16) | A.\n\n");
    printf("LIMITATIONS:\n");
    printf("    • Weak for very short messages (under a few hundred bytes) because the sums\n");
    printf("      do not wrap around the modulo, leading to poor bit mixing.\n\n");
    printf("--- CYCLIC REDUNDANCY CHECK (CRC) ---\n\n");
    printf("CYCLIC REDUNDANCY CHECK (CRC):\n");
    printf("    A highly powerful algebraic error detection method based on binary division.\n");
    printf("    Data bits are treated as polynomial coefficients.\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • A predetermined Generator Polynomial (Divisor) is chosen.\n");
    printf("    • The sender appends n zero bits to the data block (where n is the degree\n");
    printf("      of the generator polynomial).\n");
    printf("    • The sender performs modulo-2 binary division on the appended data.\n");
    printf("    • The remainder of this division is the CRC checksum (replaced in the\n");
    printf("      appended zero slots).\n");
    printf("    • The receiver performs modulo-2 division on the incoming data using the\n");
    printf("      same divisor. If the remainder is zero, no error occurred.\n\n");
    printf("ADVANTAGES:\n");
    printf("    • Detects single, double, odd-numbered, and burst errors very reliably.\n\n");

    printf("--- HAMMING CODE (ERROR CORRECTION) ---\n\n");
    printf("HAMMING CODE (ERROR CORRECTION):\n");
    printf("    An error-detecting and error-correcting code developed by Richard Hamming.\n");
    printf("    Unlike parity or CRC, it can locate and correct a single-bit error.\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • Redundant parity bits are inserted at positions that are powers of 2\n");
    printf("      (positions 1, 2, 4, 8, etc.).\n");
    printf("    • Each parity bit checks specific data bits according to their binary\n"
           "      positions.\n");
    printf("    • At the receiver, parity checks are verified. The sum of the positions of\n");
    printf("      failed parity checks yields the exact index of the corrupted bit (Syndrome).\n");
    printf("    • The corrupted bit is flipped back to correct the error.\n\n");
    printf("CAPABILITIES:\n");
    printf("    • Single Error Correction (SEC).\n");
    printf("    • Double Error Detection (DED) when an extra overall parity bit is added.\n\n");

    printf("--- RELATIONSHIPS & USE CASES ---\n\n");
    printf("RELATIONSHIPS BETWEEN SCHEMES:\n");
    printf("    • Simple Parity (1D check):\n");
    printf("      Smallest overhead (1 bit). Only checks a single dimension.\n");
    printf("    • VRC & LRC (2D check):\n");
    printf("      VRC checks each row (character) and LRC checks each column (block).\n");
    printf("      Combining them allows the receiver to detect and locate a single-bit\n");
    printf("      error (at the intersection of the failed row and column).\n");
    printf("    • Checksum (Sum-based):\n");
    printf("      Lightweight addition operations. Good at catching random bit flips,\n");
    printf("      but weak against balanced errors where values shift by equal/opposite\n"
           "      amounts.\n");
    printf("    • Adler-32 (Rolling Checksum):\n");
    printf("      Computes two running sums modulo a prime number. Faster in software than\n");
    printf("      CRC but has weaker collision resistance, especially for short data.\n");
    printf("    • CRC (Division-based polynomial):\n");
    printf("      Very strong mathematical guarantees. Treats data as a bitstream\n");
    printf("      divided by a generator polynomial. Excellent at catching burst errors.\n");
    printf("    • Hamming Code (Distance-based correction):\n");
    printf("      Calculates multiple overlapping parities. Unlike all of the above\n");
    printf("      (which only detect errors), Hamming Code can locate the exact position\n");
    printf("      of a corrupted bit to flip and correct it.\n\n");
    printf("WHEN TO USE WHAT:\n");
    printf("    • Use Simple Parity / VRC when transmission is slow/short and overhead\n");
    printf("      must be kept at an absolute minimum.\n");
    printf("    • Use Checksum when software efficiency is key (network stack headers)\n");
    printf("      and checksum generation must be fast in software.\n");
    printf("    • Use Adler-32 when you need a fast, software-efficient checksum for large\n");
    printf("      payloads, such as compressed data streams.\n");
    printf("    • Use CRC when high reliability error detection is required over noisy\n");
    printf("      mediums (like hard disks or wireless signals).\n");
    printf("    • Use Hamming Code when error correction is required without retransmission\n");
    printf("      (low latency, memory access).\n\n");
    printf("REAL-WORLD APPLICATIONS:\n");
    printf("    • Simple Parity: Serial communications (UART, modems).\n");
    printf("    • Checksum: IP, TCP, and UDP headers in networking packets.\n");
    printf("    • Adler-32: Used extensively in the zlib compression library and rsync.\n");
    printf("    • CRC: Ethernet frames, Wi-Fi packets, SATA/Hard disk controllers,\n");
    printf("      ZIP/PNG file integrity checks.\n");
    printf("    • Hamming Code: ECC (Error-Correcting Code) RAM modules, RAID 2 storage.\n\n");

    printf("
Press [ENTER] to return...\n");
    press_enter_to_continue();
}
