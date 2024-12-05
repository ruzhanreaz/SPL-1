#include <stdio.h>
#include <stdlib.h>
#include "intStack.h"

typedef struct IntStack
{
    int data;
    struct IntStack *next;
} IntStack;

IntStack *topInt = NULL;
void pushInt(int c)
{
    IntStack *new_node = malloc(sizeof(IntStack));
    new_node->data = c;
    new_node->next = topInt;
    topInt = new_node;
}
int popInt(void)
{
    if (topInt == NULL)
    {
        printf("IntStack is empty\n");
        return '\0';
    }
    IntStack *temp = topInt;
    int c = temp->data;
    topInt = topInt->next;
    free(temp);
    return c;
}
int peekInt(void)
{
    if (topInt == NULL)
    {
        printf("IntStack is empty\n");
        return '\0';
    }
    return topInt->data;
}
int is_emptyi(void)
{
    return topInt == NULL;
}