#include "hash.h"
#include <assert.h>
#include <stdio.h>

void test_separate_chaining()
{
    int size = 10;
    Node* table[10] = {NULL};

    // Test search on empty table
    assert(separate_chaining_search(table, size, 5) == 0);

    // Test insertion
    assert(separate_chaining_insert(table, size, 5) == 1);
    assert(separate_chaining_insert(table, size, 15) == 1);
    assert(separate_chaining_insert(table, size, 25) == 1);

    // Test successful search
    assert(separate_chaining_search(table, size, 5) == 1);
    assert(separate_chaining_search(table, size, 15) == 1);
    assert(separate_chaining_search(table, size, 25) == 1);

    // Test failed search
    assert(separate_chaining_search(table, size, 35) == 0);

    // Test deletion of existing element
    assert(separate_chaining_delete(table, size, 15) == 1);
    assert(separate_chaining_search(table, size, 15) == 0); // Should be gone
    assert(separate_chaining_search(table, size, 5) == 1);  // Others still exist

    // Test deletion of non-existent element
    assert(separate_chaining_delete(table, size, 35) == 0);

    // Clean up
    for (int i = 0; i < size; i++)
    {
        if (table[i] != NULL)
        {
            delete_sll(table[i], NULL);
        }
    }
    printf("Separate chaining basic tests passed\n");
}

void test_separate_chaining_edge_cases()
{
    int size = 5;
    Node* table[5] = {NULL};

    // Test invalid array size or null table
    assert(separate_chaining_insert(NULL, size, 1) == 0);
    assert(separate_chaining_insert(table, 0, 1) == 0);
    assert(separate_chaining_search(NULL, size, 1) == 0);
    assert(separate_chaining_search(table, 0, 1) == 0);
    assert(separate_chaining_delete(NULL, size, 1) == 0);
    assert(separate_chaining_delete(table, 0, 1) == 0);

    printf("Separate chaining edge case tests passed\n");
}

int main()
{
    test_separate_chaining();
    test_separate_chaining_edge_cases();
    printf("All separate chaining tests passed\n");
    return 0;
}
