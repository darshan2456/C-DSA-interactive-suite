#include "hash.h"
#include "sll.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Forward declarations */
int hash_function(int value, int length_of_array);
int separate_chaining_insert(Node* table[], int length_of_array, int value);
int separate_chaining_search(Node* table[], int length_of_array, int value);
int separate_chaining_delete(Node* table[], int length_of_array, int value);
void delete_sll(Node* head, void (*free_data)(void*));

#define TABLE_SIZE 10

static void init_table(Node* table[], int size)
{
    for (int i = 0; i < size; i++)
    {
        table[i] = NULL;
    }
}

static void cleanup_table(Node* table[], int size)
{
    for (int i = 0; i < size; i++)
    {
        delete_sll(table[i], NULL);
        table[i] = NULL;
    }
}

void test_insert()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    assert(separate_chaining_insert(table, TABLE_SIZE, 10) == 1);
    assert(separate_chaining_insert(table, TABLE_SIZE, 20) == 1);
    assert(separate_chaining_insert(table, TABLE_SIZE, 30) == 1);

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining insert test passed\n");
}

void test_search_found()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    separate_chaining_insert(table, TABLE_SIZE, 42);
    separate_chaining_insert(table, TABLE_SIZE, 99);
    separate_chaining_insert(table, TABLE_SIZE, 7);

    assert(separate_chaining_search(table, TABLE_SIZE, 42) == 1);
    assert(separate_chaining_search(table, TABLE_SIZE, 99) == 1);
    assert(separate_chaining_search(table, TABLE_SIZE, 7) == 1);

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining search found test passed\n");
}

void test_search_not_found()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    separate_chaining_insert(table, TABLE_SIZE, 10);
    separate_chaining_insert(table, TABLE_SIZE, 20);

    assert(separate_chaining_search(table, TABLE_SIZE, 999) == -1);
    assert(separate_chaining_search(table, TABLE_SIZE, 0) == -1);

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining search not found test passed\n");
}

void test_delete_found()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    separate_chaining_insert(table, TABLE_SIZE, 50);
    separate_chaining_insert(table, TABLE_SIZE, 60);

    assert(separate_chaining_search(table, TABLE_SIZE, 50) == 1);
    assert(separate_chaining_delete(table, TABLE_SIZE, 50) == 1);
    assert(separate_chaining_search(table, TABLE_SIZE, 50) == -1);

    /* Other values should remain intact */
    assert(separate_chaining_search(table, TABLE_SIZE, 60) == 1);

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining delete found test passed\n");
}

void test_delete_not_found()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    separate_chaining_insert(table, TABLE_SIZE, 10);

    assert(separate_chaining_delete(table, TABLE_SIZE, 999) == -1);

    /* Original value should still exist */
    assert(separate_chaining_search(table, TABLE_SIZE, 10) == 1);

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining delete not found test passed\n");
}

void test_invalid_args()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    /* NULL table */
    assert(separate_chaining_insert(NULL, TABLE_SIZE, 10) == -2);
    assert(separate_chaining_search(NULL, TABLE_SIZE, 10) == -2);
    assert(separate_chaining_delete(NULL, TABLE_SIZE, 10) == -2);

    /* Zero length */
    assert(separate_chaining_insert(table, 0, 10) == -2);
    assert(separate_chaining_search(table, 0, 10) == -2);
    assert(separate_chaining_delete(table, 0, 10) == -2);

    /* Negative length */
    assert(separate_chaining_insert(table, -1, 10) == -2);
    assert(separate_chaining_search(table, -1, 10) == -2);
    assert(separate_chaining_delete(table, -1, 10) == -2);

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining invalid args test passed\n");
}

void test_collision_handling()
{
    Node* table[TABLE_SIZE];
    init_table(table, TABLE_SIZE);

    /* Insert many values that may collide into same buckets */
    for (int i = 0; i < 50; i++)
    {
        assert(separate_chaining_insert(table, TABLE_SIZE, i) == 1);
    }

    /* All should be searchable */
    for (int i = 0; i < 50; i++)
    {
        assert(separate_chaining_search(table, TABLE_SIZE, i) == 1);
    }

    /* Delete every other value */
    for (int i = 0; i < 50; i += 2)
    {
        assert(separate_chaining_delete(table, TABLE_SIZE, i) == 1);
    }

    /* Deleted values should not be found, others should remain */
    for (int i = 0; i < 50; i++)
    {
        if (i % 2 == 0)
        {
            assert(separate_chaining_search(table, TABLE_SIZE, i) == -1);
        }
        else
        {
            assert(separate_chaining_search(table, TABLE_SIZE, i) == 1);
        }
    }

    cleanup_table(table, TABLE_SIZE);
    printf("Separate chaining collision handling test passed\n");
}

int main()
{
    test_insert();
    test_search_found();
    test_search_not_found();
    test_delete_found();
    test_delete_not_found();
    test_invalid_args();
    test_collision_handling();

    printf("All separate chaining tests passed\n");
    return 0;
}
