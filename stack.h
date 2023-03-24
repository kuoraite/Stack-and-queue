#ifndef STACK_H
#define STACK_H

typedef struct StackNode StackNode;
typedef struct Stack Stack;

struct StackNode
{
    void *data;
    StackNode *next;
};

struct Stack
{
    StackNode *head;
    int size;
};

Stack createStack(); // Returns an empty Stack.
int isEmpty(Stack stack); // Returns 1 (Stack is empty) or 0 (Stack is not empty).
int countElements(Stack stack); // Returns the size of the Stack.
int push(Stack *stack, void *value); // Returns 1 if the operation has been successful. Returns -1 if an error has occurred. 
void *pop(Stack *stack); // Returns a pointer to the data of the removed StackNode. Returns NULL if the Stack the stack was empty.
int deleteStack(Stack *stack); // Returns 1 if the Stack was deleted successfully. Returns 2 if the Stack was already empty.
void *peek(Stack stack); // Returns a pointer to the data of the Stack head StackNode. Returns NULL if the Stack is empty.

#endif