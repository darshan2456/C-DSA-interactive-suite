#ifndef SLL_H
#define SLL_H

#include "memory_inspector.h"
#include <stdint.h>

/**
 * @brief Node structure for generic Singly Linked List.
 */
typedef struct Node
{
    void* data;        /**< Pointer to payload data. */
    struct Node* next; /**< Pointer to the next node in the list. */
} Node;

/**
 * @brief Prints the elements of a singly linked list.
 * @param head Pointer to the head node.
 * @param print_element Callback function to format and print a single element payload.
 */
void sll_printlist(const Node* head, void (*print_element)(const void*));

/**
 * @brief Inserts a value at the end of a singly linked list.
 * @param head_ref Double pointer to the head node.
 * @param value Pointer to the value payload to insert.
 * @return 1 on success, -1 on allocation failure.
 */
int sll_insertAtEnd(Node** head_ref, void* value);

/**
 * @brief Deletes the first element from a singly linked list.
 * @param head_ref Double pointer to the head node.
 * @param free_data Callback function to free payload memory (can be NULL).
 * @return 1 on success, -1 if list is empty.
 */
int sll_deleteAtBeginning(Node** head_ref, void (*free_data)(void*));

/**
 * @brief Deletes the last element from a singly linked list.
 * @param head_ref Double pointer to the head node.
 * @param free_data Callback function to free payload memory (can be NULL).
 * @return 1 on success, -1 if list is empty.
 */
int sll_deleteAtEnd(Node** head_ref, void (*free_data)(void*));

/**
 * @brief Deletes the first occurrence of a value from a singly linked list.
 * @param head_ref Double pointer to the head node.
 * @param value Pointer to the target comparison value.
 * @param compare Callback function returning 0 when values match.
 * @param free_data Callback function to free payload memory.
 * @return 1 on success, -2 if list is empty, -1 if not found.
 */
int sll_deleteByValue(Node** head_ref, const void* value, int (*compare)(const void*, const void*),
                      void (*free_data)(void*));

/**
 * @brief Inserts a value at the beginning of a singly linked list.
 * @param head_ref Double pointer to the head node.
 * @param value Pointer to the value payload to insert.
 * @return 1 on success, -1 on allocation failure.
 */
int sll_insertAtBeginning(Node** head_ref, void* value);

/** @brief Runs the interactive Singly Linked List demonstration module. */
void sll_demo(void);

/**
 * @brief Searches for a key in a singly linked list.
 * @param head Pointer to the head node.
 * @param key Pointer to target search key.
 * @param compare Callback comparison function.
 * @return 0-based index of key, or -1 if not found.
 */
int sll_search(const Node* head, const void* key, int (*compare)(const void*, const void*));

/**
 * @brief Reverses a singly linked list in place.
 * @param head_ref Double pointer to the head node.
 * @return 1 on success, -2 if empty, -1 if single node.
 */
int sll_reverseList(Node** head_ref);

/**
 * @brief Frees all nodes in a singly linked list.
 * @param head Pointer to head node.
 * @param free_data Callback function to free payload memory.
 */
void delete_sll(Node* head, void (*free_data)(void*));

/**
 * @brief Gets total number of nodes in a singly linked list.
 * @param head Pointer to head node.
 * @return Node count.
 */
int sll_getLength(const Node* head);

/**
 * @brief Inserts a value at a 1-based index position in a singly linked list.
 * @param head_ref Double pointer to head node.
 * @param value Pointer to value payload.
 * @param position 1-based target insertion index.
 * @return 1 on success, -1 on allocation failure, -2 on invalid position.
 */
int sll_insertAtPosition(Node** head_ref, void* value, int position);

/**
 * @brief Deletes a node at a 1-based index position in a singly linked list.
 * @param head_ref Double pointer to head node.
 * @param position 1-based target deletion index.
 * @param free_data Callback function to free payload memory.
 * @return 1 on success, -1 if list is empty, -2 on invalid position.
 */
int sll_deleteAtPosition(Node** head_ref, int position, void (*free_data)(void*));

/**
 * @brief Detects whether a singly linked list contains a cycle using Floyd's
 *        Cycle-Finding Algorithm (Tortoise and Hare).
 * @param head Pointer to the head node.
 * @return 1 if a cycle is detected, 0 if no cycle exists.
 */
int sll_hasCycle(const Node* head);

#endif
