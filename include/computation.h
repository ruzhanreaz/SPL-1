#ifndef COMPUTATION_H
#define COMPUTATION_H

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

Stack *createStack();
void push(Stack *stack, char *data);
char *pop(Stack *stack);
char *peek(Stack *stack);
int isStackEmpty(Stack *stack);
int getPrecedence(char *operator);
void freeStack(Stack *stack);
void computation(int degreeMode);
void infixToPostfix(Queue *infix, Queue *postfix, Variable *head);
void postfixEvaluate(Queue *postfix, int degreeMode, char *result);

char *compOperation(char *str, int degreeMode, Variable *head);

#endif