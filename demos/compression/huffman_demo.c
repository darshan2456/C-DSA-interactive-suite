#include "../utils/config.h"
#include "clear_screen.h"
#include "compression.h"
#include "cross_platform_timer.h"
#include "safe_input.h"

#include <stdio.h>
#include <string.h>

void huffman_demo(void)
{
    char input[256];
    char encoded[2048];
    char decoded[256];
    char codes[256][256] = {{0}};
    char current_code[256];

    while (1)
    {
        if (!is_instant())
            clear_screen();

        printf("\n\033[1;36m=== HUFFMAN CODING DEMO ===\033[0m\n");
        printf("This demo builds a Huffman Tree, generates codes,\n");
        printf("encodes the input string and decodes it back.\n\n");

        printf("Enter a string (-1 to exit): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "-1") == 0)
            break;

        if (strlen(input) == 0)
        {
            printf("\nInput cannot be empty!\n");
            sleep_seconds(1.2f);
            continue;
        }

        HuffmanNode* root = build_huffman_tree(input);

        if (root == NULL)
        {
            printf("\nFailed to build Huffman Tree!\n");
            sleep_seconds(1.2f);
            continue;
        }

        memset(codes, 0, sizeof(codes));
        generate_huffman_codes(root, codes, current_code, 0);

        printf("\n==============================\n");
        printf("HUFFMAN TREE\n");
        printf("==============================\n");

        print_huffman_tree_visual(root, "", false);

        printf("\n==============================\n");
        printf("HUFFMAN DICTIONARY\n");
        printf("==============================\n");

        print_huffman_dictionary(root, codes);

        if (huffman_encode(input, codes, encoded, sizeof(encoded)) < 0)
        {
            printf("\nEncoding Failed!\n");
            free_huffman_tree(root);
            sleep_seconds(1.2f);
            continue;
        }

        if (huffman_decode(encoded, root, decoded, sizeof(decoded)) < 0)
        {
            printf("\nDecoding Failed!\n");
            free_huffman_tree(root);
            sleep_seconds(1.2f);
            continue;
        }

        printf("\n==============================\n");
        printf("RESULTS\n");
        printf("==============================\n");

        printf("Original String : %s\n", input);
        printf("Encoded Bitstream : %s\n", encoded);
        printf("Decoded String : %s\n", decoded);

        printf("\nOriginal Size : %lu bytes\n", (unsigned long)strlen(input));
        printf("Encoded Bits  : %lu bits\n", (unsigned long)strlen(encoded));

        free_huffman_tree(root);

        printf("\nPress Enter to continue...");
        getchar();
    }
}