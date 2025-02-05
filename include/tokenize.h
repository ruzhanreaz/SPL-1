#ifndef TOKENIZE_H
#define TOKENIZE_H

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
typedef struct Variable
{
    char *name;
    double value;
    double coefficient;
    struct Variable *next;
} Variable;

int isFunction(char *str);
int isConstant(char *str);
int isOperator(char *str);
int isVariable(char *str, Variable *head);
int isMatrixOperator(char *str);

int isQueueEmpty(Queue *queue);
int tokenize(Queue *queue, char *str, Variable *head);
int tokenizeMatrix(Queue *queue, char *str, MatrixNode *head);
void enQueue(Queue *queue, char *token);
void freeQueue(Queue *queue);
void printQueue(Queue *queue);
void removeSpaces(char *str);
char *deQueue(Queue *queue);
Queue *createQueue();
Variable *createVariable(char *name, double value);
void getVariableValue(Variable *head, char *name, double *value);
void printVariables(Variable *head);
void addVariable(Variable **head, char *name, double value);
void editVariable(Variable *head, char *name, double value);

#endif
