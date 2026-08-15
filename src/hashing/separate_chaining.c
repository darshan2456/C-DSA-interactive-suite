#include "hash.h"
#include "safe_input.h"
#include "sll.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Returns 1 on success, -1 on hash error, -2 on invalid arguments or malloc failure
int separate_chaining_insert(Node* table[], int length_of_array, int value)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return -2;
    }

    int hash_location = hash_function(value, length_of_array);
    if (hash_location == -1)
    {
        return -1;
    }

    int result = sll_insertAtEnd(&table[hash_location], (void*)(intptr_t)value);
    if (result == -1)
    {
        return -2;
    }
    return 1;
}

// Returns 1 if found, -1 if not found, -2 on invalid arguments
int separate_chaining_search(Node* table[], int length_of_array, int value)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return -2;
    }

    int hash_location = hash_function(value, length_of_array);
    if (hash_location == -1)
    {
        return -1;
    }

    Node* current = table[hash_location];
    while (current != NULL)
    {
        if ((intptr_t)current->data == (intptr_t)value)
        {
            return 1;
        }
        current = current->next;
    }
    return -1;
}

// Returns 1 on success, -1 if not found, -2 on invalid arguments
int separate_chaining_delete(Node* table[], int length_of_array, int value)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return -2;
    }

    int hash_location = hash_function(value, length_of_array);
    if (hash_location == -1)
    {
        return -1;
    }

    int result =
        sll_deleteByValue(&table[hash_location], (void*)(intptr_t)value, NULL, NULL);
    if (result == 1)
    {
        return 1;
    }
    return -1;
}
