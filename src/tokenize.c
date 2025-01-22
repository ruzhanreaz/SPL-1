#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "tokenize.h"
#include "menu.h"

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, char *data)
{
    Token *temp = (Token *)malloc(sizeof(Token));
    temp->data = strdup(data);
    temp->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

char *dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        return NULL;
    }
    Token *temp = q->front;
    char *data = strdup(temp->data);
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp->data);
    free(temp);
    return data;
}

void enqueueAtFront(Queue *q, char *data)
{
    Token *temp = (Token *)malloc(sizeof(Token));
    temp->data = strdup(data);
    temp->next = q->front;
    q->front = temp;
    if (q->rear == NULL)
    {
        q->rear = temp;
    }
}

int isQueueEmpty(Queue *q)
{
    return q->front == NULL;
}

void freeQueue(Queue *q)
{
    while (!isQueueEmpty(q))
    {
        free(dequeue(q));
    }
    free(q);
}

void printQueue(Queue *q)
{
    Token *temp = q->front;
    while (temp != NULL)
    {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int isFunction(char *str)
{
    return strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 ||
           strcmp(str, "asin") == 0 || strcmp(str, "acos") == 0 || strcmp(str, "atan") == 0 ||
           strcmp(str, "exp") == 0 || strcmp(str, "log") == 0 || strcmp(str, "ln") == 0;
}
int isConstant(char *str)
{
    return strcmp(str, "pi") == 0 || strcmp(str, "e") == 0 || strcmp(str, "%") == 0;
}
void removeSpaces(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

bool tokenize(Queue *q, char *str)
{
    removeSpaces(str);
    size_t len = strlen(str);

    if (*str == '-')
    {
        enqueue(q, "0");
    }
    if (*str == '*' || *str == '/' || *str == '^' || *str == '%' || *str == ')')
    {
        printf("Syntax error: expression cannot start with '%c'\n", *str);
        printLine();
        return false;
    }
    if (len > 0 && (str[len - 1] == '*' || str[len - 1] == '/' || str[len - 1] == '^' || str[len - 1] == '+' || str[len - 1] == '-' || str[len - 1] == '('))
    {
        printf("Syntax error: expression cannot end with '%c'\n", str[len - 1]);
        printLine();
        return false;
    }

    while (*str)
    {
        if (isdigit(*str) || (*str == '-' && !isdigit(*(str - 1))))
        {
            char *start = str;
            if (*str == '-')
            {
                str++;
            }
            while (isdigit(*str) || *str == '.')
            {
                str++;
            }
            char *number = (char *)malloc(str - start + 1);
            strncpy(number, start, str - start);
            number[str - start] = '\0';
            enqueue(q, number);
            free(number);
            if (isalpha(*str))
            {
                enqueue(q, "*");
            }
        }
        else if (*str == '(' && isdigit(*(str - 1)))
        {
            enqueue(q, "*");
            enqueue(q, "(");
            str++;
        }
        else if (*str == ')' && isdigit(*(str + 1)))
        {
            enqueue(q, ")");
            enqueue(q, "*");
            str++;
        }
        else if (*str == '%' && isdigit(*(str + 1)))
        {
            printf("Syntax error\n");
            printLine();
            return false;
        }

        else if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^')
        {
            if ((*(str + 1) == '*' || *(str + 1) == '/') && (*str == '*' || *str == '/'))
            {
                printf("Syntax error: consecutive '*' or '/' detected.\n");
                printLine();
                return false;
            }
            char operator[2] = { *str,
                                 '\0' };
            enqueue(q, operator);
            str++;
        }
        else if (*str == '(' || *str == ')')
        {
            char paren[2] = {*str, '\0'};
            enqueue(q, paren);
            str++;
        }
        else if (isalpha(*str) || *str == '%')
        {
            char *start = str;
            while (isalpha(*str) || *str == '%')
            {
                str++;
            }
            char *function = (char *)malloc(str - start + 1);
            strncpy(function, start, str - start);
            function[str - start] = '\0';
            if (isFunction(function))
            {

                enqueue(q, function);
            }
            else if (isConstant(function))
            {
                enqueue(q, function);
            }
            else
            {
                printf("Error: Unrecognized token '%s'\n", function);
                printLine();
                return false;
            }
            free(function);
        }
        else
        {
            printf("Error: Unrecognized character '%c'\n", *str);
            printLine();
            return false;
            str++;
        }
    }
    return true;
}
