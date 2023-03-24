#include "stack.h"
#include <stdlib.h>

Stack createStack()
{
    Stack stack;
    stack.head = NULL;
    stack.size = 0;
    return stack;
}

int isEmpty(Stack stack) 
{
    return !(stack.head);
}

int countElements(Stack stack) 
{
    return stack.size;
}

int push(Stack *stack, void *value) 
{
    StackNode *newElement = (StackNode*)malloc(sizeof(StackNode));
    if(!newElement)
    {
        return -1;
    }
    newElement->data = value;
    newElement->next = stack->head;

    stack->head = newElement;
    ++(*stack).size;

    return 1;
}

void *pop(Stack *stack) 
{
    if(isEmpty(*stack))
    {
        return NULL;
    }
    StackNode *currentElement = stack->head;
    stack->head = currentElement->next;
    void *value = currentElement->data;
    free(currentElement);
    --(*stack).size;
    return value;
}

int deleteStack(Stack *stack) 
{
    if(isEmpty(*stack))
    {
        return 2;
    }
    StackNode *currentElement = stack->head;
    StackNode *temp;

    while(currentElement != NULL)
    {
        temp = currentElement->next;
        free(currentElement);
        currentElement = temp;
    }

    stack->head = NULL;
    return 1;
}

void *peek(Stack stack) 
{
    if(isEmpty(stack))
    {
        return NULL;
    }
    return stack.head->data;
}
