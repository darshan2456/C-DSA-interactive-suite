#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

// insert functions returns 1 on succesful insertion and -1 on malloc failure
// delete functions return 1 on successful deletion and -1 on failure due to empty list
// methods implemented are - insertAtBeginning, insertAtEnd, printlist, search, deleteAtBeginning,
// deleteAtEnd, deleteByValue, insertAtPosition, deleteAtPosition and reverselist

int dll_insertAtBeginning(doubly_ll_Node** head_ref, void* value)
{
    if (head_ref == NULL)
        return -1;

    doubly_ll_Node* newnode = malloc(sizeof(doubly_ll_Node));
    if (newnode == NULL)
        return -1;
    newnode->data = value;
    if (*head_ref == NULL)
    {
        newnode->next = NULL;
        newnode->prev = NULL;
        *head_ref = newnode;
        return 1;
    }
    newnode->next = *head_ref;
    newnode->prev = NULL;
    (*head_ref)->prev = newnode;
    *head_ref = newnode;
    return 1;
}

int dll_insertAtEnd(doubly_ll_Node** head_ref, void* value)
{
    if (head_ref == NULL)
        return -1;

    doubly_ll_Node* newnode = malloc(sizeof(doubly_ll_Node));
    if (newnode == NULL)
        return -1;
    newnode->data = value;
    if (*head_ref == NULL)
    {
        newnode->next = NULL;
        newnode->prev = NULL;
        *head_ref = newnode;
        return 1;
    }
    doubly_ll_Node* temp = *head_ref;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    newnode->prev = temp;
    newnode->next = NULL;
    temp->next = newnode;
    return 1;
}

void dll_printlist(const doubly_ll_Node* head, void (*print_element)(const void*))
{
    printf("\nHEAD<-> ");
    while (head != NULL)
    {
        if (print_element != NULL)
        {
            print_element(head->data);
        }
        else
        {
            printf("%p", head->data);
        }
        printf(" <->");
        head = head->next;
    }
    printf("NULL");
}

int dll_search(const doubly_ll_Node* head, const void* key,
               int (*compare)(const void*, const void*))
{
    int index = 0;
    while (head != NULL)
    {
        if (compare != NULL)
        {
            if (compare(head->data, key) == 0)
            {
                return index; // if value found returns index number
            }
        }
        else
        {
            if (head->data == key)
            {
                return index;
            }
        }
        head = head->next;
        index++;
    }
    return -1; // otherwise returns -1
}

int dll_deleteAtBeginning(doubly_ll_Node** head_ref, void (*free_data)(void*))
{
    if (*head_ref == NULL)
        return -1;
    doubly_ll_Node* temp = *head_ref;
    if (temp->next == NULL)
    {
        if (free_data != NULL)
        {
            free_data(temp->data);
        }
        free(temp);
        *head_ref = NULL;
        return 1;
    }
    doubly_ll_Node* secondnode = temp->next;
    if (free_data != NULL)
    {
        free_data(temp->data);
    }
    free(temp);
    secondnode->prev = NULL;
    *head_ref = secondnode;
    return 1;
}

int dll_deleteAtEnd(doubly_ll_Node** head_ref, void (*free_data)(void*))
{
    if (*head_ref == NULL)
        return -1;
    doubly_ll_Node* temp = *head_ref;
    if (temp->next == NULL)
    {
        if (free_data != NULL)
        {
            free_data(temp->data);
        }
        free(temp);
        *head_ref = NULL;
        return 1;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    doubly_ll_Node* secondlast = temp->prev;
    if (free_data != NULL)
    {
        free_data(temp->data);
    }
    free(temp);
    secondlast->next = NULL;
    return 1;
}

int dll_deleteByValue(doubly_ll_Node** head_ref, const void* key,
                      int (*compare)(const void*, const void*), void (*free_data)(void*))
{
    if (*head_ref == NULL)
        return -2;

    doubly_ll_Node* temp = *head_ref;
    while (temp != NULL)
    {
        int match = 0;
        if (compare != NULL)
        {
            match = (compare(temp->data, key) == 0);
        }
        else
        {
            match = (temp->data == key);
        }

        if (match)
        {
            doubly_ll_Node* beforekey = temp->prev;
            doubly_ll_Node* afterkey = temp->next;
            if (beforekey == NULL)
            {
                *head_ref = temp->next;
                if (*head_ref != NULL)
                {
                    (*head_ref)->prev = NULL;
                }
                if (free_data != NULL)
                {
                    free_data(temp->data);
                }
                free(temp);
                return 1;
            }
            beforekey->next = afterkey;
            if (afterkey != NULL)
            {
                afterkey->prev = beforekey;
            }
            if (free_data != NULL)
            {
                free_data(temp->data);
            }
            free(temp);
            return 1;
        }
        temp = temp->next;
    }

    return -1;
}

void delete_dll(doubly_ll_Node* head, void (*free_data)(void*))
{
    while (head != NULL)
    {
        doubly_ll_Node* upcoming = head->next;
        if (free_data != NULL)
        {
            free_data(head->data);
        }
        free(head);
        head = upcoming;
    }
}

// returns -2 if list is empty. -1 if list is a single node list and 1 on successful reversal.
int dll_reverselist(doubly_ll_Node** head_ref)
{
    if (head_ref == NULL)
        return -1;

    doubly_ll_Node* temp = NULL;
    doubly_ll_Node* current = *head_ref;

    if (current == NULL)
    {
        return -2;
    }
    if (current->next == NULL)
    {
        return -1;
    }

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL)
    {
        *head_ref = temp->prev;
    }

    return 1;
}

// Helper function to get the length of the doubly linked list
int dll_getLength(const doubly_ll_Node* head)
{
    int length = 0;
    while (head != NULL)
    {
        length++;
        head = head->next;
    }
    return length;
}

// Insert at a specific position (0-indexed)
// Returns 1 on success, -1 on malloc failure, -2 on invalid position
int dll_insertAtPosition(doubly_ll_Node** head_ref, void* value, int position)
{
    if (head_ref == NULL)
        return -1;

    int length = dll_getLength(*head_ref);

    if (position < 0 || position > length)
    {
        return -2;
    }

    doubly_ll_Node* newnode = malloc(sizeof(doubly_ll_Node));
    if (newnode == NULL)
        return -1;

    newnode->data = value;

    if (position == 0)
    {
        if (*head_ref == NULL)
        {
            newnode->next = NULL;
            newnode->prev = NULL;
            *head_ref = newnode;
        }
        else
        {
            newnode->next = *head_ref;
            newnode->prev = NULL;
            (*head_ref)->prev = newnode;
            *head_ref = newnode;
        }
        return 1;
    }

    doubly_ll_Node* temp = *head_ref;
    for (int i = 0; i < position - 1; i++)
    {
        temp = temp->next;
    }

    newnode->next = temp->next;
    newnode->prev = temp;
    if (temp->next != NULL)
    {
        temp->next->prev = newnode;
    }
    temp->next = newnode;
    return 1;
}

// Delete at a specific position (0-indexed)
// Returns 1 on success, -1 on empty list, -2 on invalid position
int dll_deleteAtPosition(doubly_ll_Node** head_ref, int position, void (*free_data)(void*))
{
    if (*head_ref == NULL)
    {
        return -1;
    }

    int length = dll_getLength(*head_ref);

    if (position < 0 || position >= length)
    {
        return -2;
    }

    doubly_ll_Node* temp = *head_ref;

    if (position == 0)
    {
        if (temp->next != NULL)
        {
            temp->next->prev = NULL;
            *head_ref = temp->next;
        }
        else
        {
            *head_ref = NULL;
        }
        if (free_data != NULL)
        {
            free_data(temp->data);
        }
        free(temp);
        return 1;
    }

    for (int i = 0; i < position; i++)
    {
        temp = temp->next;
    }

    doubly_ll_Node* prevnode = temp->prev;
    if (temp->next != NULL)
    {
        temp->next->prev = prevnode;
    }
    prevnode->next = temp->next;
    if (free_data != NULL)
    {
        free_data(temp->data);
    }
    free(temp);
    return 1;
}
