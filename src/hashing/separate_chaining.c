#include "hash.h"
#include "safe_input.h"
#include "sll.h"
#include <stdio.h>
#include <string.h>

static int compare_ints(const void* a, const void* b)
{
    int val_a = (int)(intptr_t)a;
    int val_b = (int)(intptr_t)b;
    return (val_a > val_b) - (val_a < val_b);
}

int separate_chaining_insert(Node* table[], int length_of_array, int value)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return 0;
    }

    int hash_location = hash_function(value, length_of_array);
    if (hash_location == -1)
    {
        return 0;
    }

    sll_insertAtEnd(&table[hash_location], (void*)(intptr_t)value);
    return 1;
}

int separate_chaining_search(Node* table[], int length_of_array, int search_val)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return 0;
    }

    int hash_location = hash_function(search_val, length_of_array);
    if (hash_location == -1)
    {
        return 0;
    }

    int idx = sll_search(table[hash_location], (void*)(intptr_t)search_val, compare_ints);
    return idx != -1 ? 1 : 0;
}

int separate_chaining_delete(Node* table[], int length_of_array, int value)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return 0;
    }

    int hash_location = hash_function(value, length_of_array);
    if (hash_location == -1)
    {
        return 0;
    }

    int res = sll_deleteByValue(&table[hash_location], (void*)(intptr_t)value, compare_ints, NULL);
    return res == 1 ? 1 : 0;
}
