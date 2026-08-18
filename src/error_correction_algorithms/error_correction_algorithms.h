#ifndef ERROR_CORRECTION_ALGORITHMS_H
#define ERROR_CORRECTION_ALGORITHMS_H

#include <stddef.h>
#include <stdint.h>

/*
 * Maximum length of a binary string accepted from the user,
 * including space for the terminating '\0'.
 */
#define CHECKSUM_MAX_BITS 1024

/* Main menu */
void error_correction_algorithms_demo(void);

/* Checksum */
void checksum_demo(void);
void checksum_receiver_demo(void);

/* CRC */
void crc_demo(void);
void crc_receiver_demo(void);

/* LRC */
void lrc_demo(void);
void lrc_receiver_demo(void);

/* VRC */
void vrc_demo(void);
void vrc_receiver_demo(void);

/* Parity Bit */
int generateEvenParity(const char* data);
int generateOddParity(const char* data);
int verifyEvenParity(const char* receivedData);
int verifyOddParity(const char* receivedData);
void parity_bit_demo(void);

/* Hamming Code */
void hamming_demo(void);
void hamming_receiver_demo(void);

/* Adler-32 Checksum */
uint32_t calculate_adler32(const char* data, size_t length);
void adler32_demo(void);

/* Shared checksum helpers (implemented in checksum.c) */
void checksum_print_binary(int value, int bits);
int safe_input_binary_string(char* buff, size_t size, const char* prompt);
int checksum_add(int sum, int word, int k);
int checksum_block_sum(const char* data, int len, int k);
int checksum_bits_to_int(const char* bits, int k);

void crc_xor_operation(char* dividend, const char* divisor, int pos);
void crc_generate(const char* data, const char* generator, char* remainder_out, char* codeword_out);
int crc_verify(const char* codeword, const char* generator, char* remainder_out);

/* LRC Logic */
void lrc_calculate(const char* const* words, int num_words, int word_len, char* lrc_out);
int lrc_verify(const char* const* words, int num_words, int word_len, const char* received_lrc);

/* Hamming Logic */
void hamming_generate(const char* data, char* codeword_out);
int hamming_verify(const char* received_codeword, char* corrected_codeword_out, char* data_out);

#endif /* ERROR_CORRECTION_ALGORITHMS_H */
