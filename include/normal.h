#ifndef NORMAL_H
#define NORMAL_H
#include "tokenize.h"

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

typedef struct stack
{
    Node *top;
} Stack;

Stack *createStack();
void push(Stack *s, char *data);
char *pop(Stack *s);
char *peek(Stack *s);
int isStackEmpty(Stack *s);
void freeStack(Stack *s);
int getPrecedence(char *op);
int rightAssociative(char *op);
int isOperator(char *str);
void infixToPostfix(Queue *infix, Queue *postfix);
void postfixEvaluate(Queue *postfix);
int normal(char *mode);
void check_number(double num);
bool isDegreeModeEnabled(void);
void enableDegreeMode(void);
void disableDegreeMode(void);

#endif