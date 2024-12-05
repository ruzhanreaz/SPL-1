#include <stdio.h>
#include <stdlib.h>
#include "charStack.h"

typedef struct CharStack
{
    char data;
    struct CharStack *next;
} CharStack;

CharStack *topChar = NULL;
void pushChar(char c)
{
    CharStack *new_node = malloc(sizeof(CharStack));
    new_node->data = c;
    new_node->next = topChar;
    topChar = new_node;
}
char popChar(void)
{
    if (topChar == NULL)
    {
        printf("CharStack is empty\n");
        return '\0';
    }
    CharStack *temp = topChar;
    char c = temp->data;
    topChar = topChar->next;
    free(temp);
    return c;
}
char peekChar(void)
{
    if (topChar == NULL)
    {
        printf("CharStack is empty\n");
        return '\0';
    }
    return topChar->data;
}
int is_emptyc(void)
{
    return topChar == NULL;
}