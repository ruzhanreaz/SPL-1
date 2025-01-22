#ifndef TOKENIZE_H
#define TOKENIZE_H
#include <stdbool.h>

typedef struct Token
{
    char *data;
    struct Token *next;
} Token;

typedef struct Queue
{
    Token *front;
    Token *rear;
} Queue;

Queue *createQueue();
void enqueue(Queue *q, char *data);
char *dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void freeQueue(Queue *q);
void printQueue(Queue *q);
void removeSpaces(char *str);
int isFunction(char *str);
bool tokenize(Queue *q, char *str);
void enqueueAtFront(Queue *q, char *data);

#endif