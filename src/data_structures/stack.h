#ifndef STACK_H
#define STACK_H

#include "sll.h"
#include <stdbool.h>

// For Stack
typedef struct stack
{
    Node* top;
} stack;

// Create a new stack. Returns Pointer to the created stack, or NULL on failure.
stack* createStack(void);

// Push a value onto the stack. Returns 1 on success, -1 if the stack is invalid.
int push(stack* s, void* value);

// Pop a value from the stack. Returns The popped value.
void* pop(stack* s);

// Check if the stack is empty. Returns true if empty, false otherwise.
bool isEmpty(const stack* s);

// Destroy a stack and free its resources.
void destroyStack(stack* s, void (*free_data)(void*));

// Peek at the top value of the stack without popping it. Returns The top value.
void* peek(const stack* s);

// Print the stack contents using characters.
void printStack(const stack* s);

// Print the stack contents using integer values.
void printStackAsInts(const stack* s);

// Run the stack demonstration module.
void stack_demo(void);

// Returns the number of elements currently in the stack. Returns 0 if the stack is NULL or empty.
int get_stack_size(const stack* s);

#endif
