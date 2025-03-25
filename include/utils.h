#ifndef UTILS_H
#define UTILS_H

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;
typedef struct Token
{
    char *token;
    struct Token *next;
} Token;

typedef struct Queue
{
    Token *front;
    Token *rear;
} Queue;

Queue *createQueue();
void enQueue(Queue *queue, char *token);
char *deQueue(Queue *queue);
char *deQueueFromLast(Queue *queue);
void freeQueue(Queue *queue);
void printQueue(Queue *queue);
void queueToString(Queue *queue, char *str);
int isQueueEmpty(Queue *queue);
int tokenize(Queue *queue, char *str);

Stack *createStack();
void push(Stack *stack, char *data);
char *pop(Stack *stack);
char *peek(Stack *stack);
int isStackEmpty(Stack *stack);
int getPrecedence(char *op);
void freeStack(Stack *stack);
void infixToPostfix(Queue *infix, Queue *postfix);

int isArithmeticOperator(char *str);
int isTrigonometricFunction(char *str);
int isInverseTrigonometricFunction(char *str);
int isLogarithmicFunction(char *str);
int isStatisticalFunction(char *str);
int isMatrixFunction(char *str);
int isConstant(char *str);
int isFunction(char *str);
int rightAssociative(char *op);

int graphVariable(char *str);

void removeSpaces(char *str);

#endif