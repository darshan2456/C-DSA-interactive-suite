#include "dcll.h"
#include <stdio.h>
#include <stdlib.h>

// Doubly circular linked list. See data_structures.h for the head/tail/length invariant.
//
// A note on traversal: because the list is circular there is no NULL terminator to stop on.
// Every traversal here therefore walks at most `length` nodes, using the idiom
//     cur = head; do { ...; cur = cur->next; } while (cur != head);
// which visits each node exactly once and is guaranteed to terminate (it stops the moment it
// arrives back at head). This is what prevents the infinite loops a circular list invites.
//
// Unlike scll, each node also carries a prev pointer so deletions at the end are O(1) —
// no predecessor walk is needed.

// Allocates a node holding `value`. Returns NULL on malloc failure. The caller is responsible
// for linking it into the ring (next and prev are left as NULL on purpose).

static dcll_Node* dcll_create_node(void* value)
{
    dcll_Node* node = malloc(sizeof(dcll_Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void dcll_init(dcll* list)
{
    if (list == NULL)
        return;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

int dcll_insertAtBeginning(dcll* list, void* value)
{
    if (list == NULL)
        return -1;

    dcll_Node* node = dcll_create_node(value);
    if (node == NULL)
    {
        return -1;
    }

    if (list->head == NULL)
    {
        // First node: it must point to itself so that tail->next == head and head->prev == tail.
        node->next = node;
        node->prev = node;
        list->head = node;
        list->tail = node;
    }
    else
    {
        // New node becomes the head; tail keeps closing the ring onto the new head.
        node->next = list->head;
        node->prev = list->tail;
        list->head->prev = node;
        list->tail->next = node;
        list->head = node;
    }

    list->length++;
    return 1;
}

int dcll_insertAtEnd(dcll* list, void* value)
{
    if (list == NULL)
        return -1;

    dcll_Node* node = dcll_create_node(value);
    if (node == NULL)
    {
        return -1;
    }

    if (list->head == NULL)
    {
        // First node: point to itself in both directions.
        node->next = node;
        node->prev = node;
        list->head = node;
        list->tail = node;
    }
    else
    {
        // Link after the current tail and close the ring back onto head. O(1) thanks to tail.
        node->next = list->head;
        node->prev = list->tail;
        list->tail->next = node;
        list->head->prev = node;
        list->tail = node;
    }

    list->length++;
    return 1;
}

int dcll_insertAtPosition(dcll* list, void* value, int position)
{
    if (list == NULL)
        return -1;

    // Valid insert positions are 0..length (length == append at the end).
    if (position < 0 || position > list->length)
    {
        return -2;
    }

    if (position == 0)
    {
        return dcll_insertAtBeginning(list, value);
    }
    if (position == list->length)
    {
        return dcll_insertAtEnd(list, value);
    }

    // Interior insert: walk to the node just before the target position.
    dcll_Node* node = dcll_create_node(value);
    if (node == NULL)
    {
        return -1;
    }

    dcll_Node* prev = list->head;
    for (int i = 0; i < position - 1; i++)
    {
        prev = prev->next;
    }

    node->next = prev->next;
    node->prev = prev;
    prev->next->prev = node;
    prev->next = node;
    // head and tail are untouched here (position is strictly interior), invariant preserved.

    list->length++;
    return 1;
}

int dcll_deleteAtBeginning(dcll* list, void (*free_data)(void*))
{
    if (list->head == NULL)
    {
        return -1;
    }

    dcll_Node* old_head = list->head;

    if (list->head == list->tail)
    {
        // Single node deletes down to the empty list.
        if (free_data != NULL)
        {
            free_data(old_head->data);
        }
        free(old_head);
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->head = old_head->next;
        list->head->prev = list->tail; // new head's prev closes onto tail
        list->tail->next = list->head; // tail closes ring onto new head
        if (free_data != NULL)
        {
            free_data(old_head->data);
        }
        free(old_head);
    }

    list->length--;
    return 1;
}

int dcll_deleteAtEnd(dcll* list, void (*free_data)(void*))
{
    if (list->head == NULL)
    {
        return -1;
    }

    dcll_Node* old_tail = list->tail;

    if (list->head == list->tail)
    {
        // Single node deletes down to the empty list.
        if (free_data != NULL)
        {
            free_data(old_tail->data);
        }
        free(old_tail);
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        // O(1) because prev pointer gives us the predecessor directly.
        list->tail = old_tail->prev;
        list->tail->next = list->head; // re-close the ring forward
        list->head->prev = list->tail; // re-close the ring backward
        if (free_data != NULL)
        {
            free_data(old_tail->data);
        }
        free(old_tail);
    }

    list->length--;
    return 1;
}

int dcll_deleteByValue(dcll* list, const void* value, int (*compare)(const void*, const void*),
                       void (*free_data)(void*))
{
    if (list->head == NULL)
    {
        return -2;
    }

    int match = 0;
    if (compare != NULL)
    {
        match = (compare(list->head->data, value) == 0);
    }
    else
    {
        match = (list->head->data == value);
    }

    // Deleting the head value is delegated so the head/tail bookkeeping stays in one place.
    if (match)
    {
        return dcll_deleteAtBeginning(list, free_data);
    }

    // Search for the node holding `value`, bounded by one full lap.
    dcll_Node* cur = list->head->next;
    while (cur != list->head)
    {
        int element_match = 0;
        if (compare != NULL)
        {
            element_match = (compare(cur->data, value) == 0);
        }
        else
        {
            element_match = (cur->data == value);
        }

        if (element_match)
        {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            if (cur == list->tail)
            {
                list->tail = cur->prev; // removed the tail: prev becomes the new tail
            }
            if (free_data != NULL)
            {
                free_data(cur->data);
            }
            free(cur);
            list->length--;
            return 1;
        }
        cur = cur->next;
    }

    return -1; // value not present
}

int dcll_deleteAtPosition(dcll* list, int position, void (*free_data)(void*))
{
    if (list->head == NULL)
    {
        return -1;
    }
    // Valid delete positions are 0..length-1.
    if (position < 0 || position >= list->length)
    {
        return -2;
    }

    if (position == 0)
    {
        return dcll_deleteAtBeginning(list, free_data);
    }

    if (position == list->length - 1)
    {
        return dcll_deleteAtEnd(list, free_data);
    }

    // Walk to the target node.
    dcll_Node* target = list->head;
    for (int i = 0; i < position; i++)
    {
        target = target->next;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;
    if (free_data != NULL)
    {
        free_data(target->data);
    }
    free(target);

    list->length--;
    return 1;
}

int dcll_search(const dcll* list, const void* key, int (*compare)(const void*, const void*))
{
    if (list->head == NULL)
    {
        return -1;
    }

    int index = 0;
    const dcll_Node* cur = list->head;
    do
    {
        int match = 0;
        if (compare != NULL)
        {
            match = (compare(cur->data, key) == 0);
        }
        else
        {
            match = (cur->data == key);
        }

        if (match)
        {
            return index;
        }
        cur = cur->next;
        index++;
    } while (cur != list->head);

    return -1;
}

int dcll_getLength(const dcll* list)
{
    if (list == NULL)
        return -1;

    if (list == NULL)
        return -1;

    return list->length;
}

void dcll_printlist(const dcll* list, void (*print_element)(const void*))
{
    printf("HEAD->");
    if (list->head == NULL)
    {
        printf("(empty)");
        return;
    }

    const dcll_Node* cur = list->head;
    do
    {
        if (print_element != NULL)
        {
            print_element(cur->data);
        }
        else
        {
            printf("%p", cur->data);
        }
        printf("->");
        cur = cur->next;
    } while (cur != list->head);

    printf("(back to HEAD)");
}

void dcll_destroy(dcll* list, void (*free_data)(void*))
{
    if (list->head == NULL)
    {
        return;
    }

    // Break the ring first so the walk has a NULL terminator and we never revisit a freed node.
    list->tail->next = NULL;
    dcll_Node* cur = list->head;
    while (cur != NULL)
    {
        dcll_Node* upcoming = cur->next;
        if (free_data != NULL)
        {
            free_data(cur->data);
        }
        free(cur);
        cur = upcoming;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}
