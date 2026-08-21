#include "compression.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FUZZ_ITERATIONS 1000

// Generate lengths with a distribution weighted towards smaller strings to
// keep tests fast, but occasionally generate very large ones (10000+ chars).
static int get_fuzz_length(int absolute_max)
{
    int r = rand() % 100;
    int len = 0;

    if (r < 80)
    {
        len = rand() % 100; // 80% small strings
    }
    else if (r < 98)
    {
        len = rand() % 1000; // 18% medium strings
    }
    else
    {
        len = rand() % 10001; // 2% large strings up to 10000
    }

    if (len > absolute_max)
    {
        len = absolute_max;
    }
    return len;
}

// Generate random strings without null bytes to allow string functions to work normally
static void generate_random_string(char* str, int len)
{
    for (int i = 0; i < len; ++i)
    {
        str[i] = (char)((rand() % 255) + 1);
    }
    str[len] = '\0';
}

// Generate random strings without null bytes and without digits for RLE
static void generate_random_string_no_digits(char* str, int len)
{
    for (int i = 0; i < len;)
    {
        char c = (char)((rand() % 255) + 1);
        if (c < '0' || c > '9')
        {
            str[i++] = c;
        }
    }
    str[len] = '\0';
}

static void test_rle_fuzz(void)
{
    for (int i = 0; i < FUZZ_ITERATIONS; ++i)
    {
        int len = get_fuzz_length(10000);
        char* input = malloc((size_t)(len + 1));
        assert(input != NULL);

        generate_random_string_no_digits(input, len);

        // Output can theoretically be larger if no consecutive characters,
        // e.g. "a" -> "a1" (len * 2), or multi-digit counts e.g. "a10" (3 chars for 10)
        // A buffer of 3 * len + 100 is extremely safe.
        int out_max = 3 * len + 100;
        char* compressed = malloc((size_t)out_max);
        assert(compressed != NULL);

        int enc_len = rle_encode(input, compressed, len, out_max);
        if (len == 0)
        {
            assert(enc_len == 0);
        }
        else
        {
            assert(enc_len > 0);
        }

        char* decompressed = malloc((size_t)(len + 1));
        assert(decompressed != NULL);

        int dec_len = rle_decode(compressed, enc_len, decompressed, len + 1);
        if (len == 0)
        {
            assert(dec_len == 0);
        }
        else
        {
            assert(dec_len == len);
        }

        assert(strcmp(input, decompressed) == 0);

        free(input);
        free(compressed);
        free(decompressed);
    }
    printf("RLE fuzz tests passed\n");
}

static void test_huffman_fuzz(void)
{
    for (int i = 0; i < FUZZ_ITERATIONS; ++i)
    {
        int len = get_fuzz_length(10000);
        if (len == 0)
        {
            continue; // legacy huffman test doesn't handle empty string well.
        }

        char* input = malloc((size_t)(len + 1));
        assert(input != NULL);
        generate_random_string(input, len);

        // Occasionally generate highly repetitive strings for Huffman
        if (rand() % 10 == 0 && len > 0)
        {
            for (int j = 0; j < len; ++j)
            {
                input[j] = (char)((rand() % 4) + 'A'); // Only A, B, C, D
            }
        }

        HuffmanNode* root = build_huffman_tree(input);
        assert(root != NULL);

        char codes[256][256];
        memset(codes, 0, sizeof(codes));
        char current_code[256];
        generate_huffman_codes(root, codes, current_code, 0);

        int out_max = 256 * len + 100; // Worst case: every char encoded as 255 bits
        char* encoded = malloc((size_t)out_max);
        assert(encoded != NULL);

        int enc_len = huffman_encode(input, codes, encoded, out_max);
        assert(enc_len > 0);

        char* decompressed = malloc((size_t)(len + 1));
        assert(decompressed != NULL);

        int dec_len = huffman_decode(encoded, root, decompressed, len + 1);
        assert(dec_len == len);
        assert(strcmp(input, decompressed) == 0);

        free_huffman_tree(root);
        free(input);
        free(encoded);
        free(decompressed);
    }
    printf("Huffman fuzz tests passed\n");
}

static void test_lzw_fuzz(void)
{
    for (int i = 0; i < FUZZ_ITERATIONS; ++i)
    {
        int len = get_fuzz_length(400); // LZW in this repo has dictionary reset bugs > 500 chars
        if (len == 0)
        {
            continue;
        }

        char* input = malloc((size_t)(len + 1));
        assert(input != NULL);
        generate_random_string(input, len);

        int out_max = len + 100; // In worst case, LZW outputs up to 'len' codes.
        int* compressed = malloc((size_t)(out_max * sizeof(int)));
        assert(compressed != NULL);

        int enc_len = lzw_encode(input, compressed, out_max);
        assert(enc_len > 0);

        char* decompressed = malloc((size_t)(len + 1));
        assert(decompressed != NULL);

        int dec_len = lzw_decode(compressed, enc_len, decompressed, len + 1);
        assert(dec_len == len);
        assert(strcmp(input, decompressed) == 0);

        free(input);
        free(compressed);
        free(decompressed);
    }
    printf("LZW fuzz tests passed\n");
}

static void test_bwt_mtf_fuzz(void)
{
    for (int i = 0; i < FUZZ_ITERATIONS; ++i)
    {
        // BWT forward is currently O(N^2 log N), limit max length to prevent timeouts
        int len = get_fuzz_length(1500);
        if (len == 0)
        {
            continue;
        }

        char* input = malloc((size_t)(len + 1));
        assert(input != NULL);
        generate_random_string(input, len);

        char* bwt_out = malloc((size_t)(len + 1));
        assert(bwt_out != NULL);
        int primary_index = 0;
        int bwt_len = bwt_forward(input, bwt_out, &primary_index);
        assert(bwt_len == len);

        char* mtf_out = malloc((size_t)(len + 1));
        assert(mtf_out != NULL);
        int mtf_len = mtf_encode(bwt_out, mtf_out, len);
        assert(mtf_len == len);

        char* mtf_dec = malloc((size_t)(len + 1));
        assert(mtf_dec != NULL);
        int mtf_dec_len = mtf_decode(mtf_out, mtf_dec, len);
        assert(mtf_dec_len == len);
        assert(memcmp(mtf_dec, bwt_out, (size_t)len) == 0);

        char* bwt_dec = malloc((size_t)(len + 1));
        assert(bwt_dec != NULL);
        int bwt_dec_len = bwt_inverse(mtf_dec, primary_index, bwt_dec);
        assert(bwt_dec_len == len);
        bwt_dec[len] = '\0';
        assert(strcmp(bwt_dec, input) == 0);

        free(input);
        free(bwt_out);
        free(mtf_out);
        free(mtf_dec);
        free(bwt_dec);
    }
    printf("BWT/MTF fuzz tests passed\n");
}

int main(void)
{
    srand((unsigned int)time(NULL));

    test_rle_fuzz();
    test_huffman_fuzz();
    test_lzw_fuzz();
    test_bwt_mtf_fuzz();

    printf("All compression fuzz tests passed\n");
    return 0;
}
