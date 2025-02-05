#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enQueue(Queue *queue, char *token)
{
    Token *temp = (Token *)malloc(sizeof(Token));
    temp->token = strdup(token);
    temp->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}

char *deQueue(Queue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    Token *temp = queue->front;
    char *token = strdup(temp->token);
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp->token);
    free(temp);
    return token;
}

int isQueueEmpty(Queue *queue)
{
    return queue->front == NULL;
}

void freeQueue(Queue *queue)
{
    while (!isQueueEmpty(queue))
    {
        free(deQueue(queue));
    }
    free(queue);
}

void printQueue(Queue *queue)
{
    Token *temp = queue->front;
    while (temp != NULL)
    {
        printf("%s ", temp->token);
        temp = temp->next;
    }
    printf("\n");
}

int isFunction(char *str)
{
    return strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 ||
           strcmp(str, "asin") == 0 || strcmp(str, "acos") == 0 || strcmp(str, "atan") == 0 ||
           strcmp(str, "exp") == 0 || strcmp(str, "log") == 0 || strcmp(str, "ln") == 0 || strcmp(str, "log_") == 0;
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

Variable *createVariable(char *name, double value)
{
    Variable *variable = (Variable *)malloc(sizeof(Variable));
    variable->name = strdup(name);
    variable->value = value;
    variable->next = NULL;
    return variable;
}

void editVariable(Variable *head, char *name, double value)
{
    Variable *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
}

void addVariable(Variable **head, char *name, double value)
{
    Variable *temp = *head;
    if (temp == NULL)
    {
        *head = createVariable(name, value);
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = createVariable(name, value);
}

void getVariableValue(Variable *head, char *name, double *value)
{
    Variable *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            *value = temp->value;
            return;
        }
        temp = temp->next;
    }
}

void printVariables(Variable *head)
{
    Variable *temp = head;
    while (temp != NULL)
    {
        printf("%s = %lf\n", temp->name, temp->value);
        temp = temp->next;
    }
}
int isVariable(char *str, Variable *head)
{
    Variable *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, str) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int tokenize(Queue *queue, char *str, Variable *head)
{

    removeSpaces(str);
    int foundNum = 0;
    int const len = strlen(str);
    if (*str == '-' || *str == '+')
    {
        enQueue(queue, "0");
    }
    if (*str == '*' || *str == '/' || *str == '^' || *str == '%' || *str == ')')
    {
        printf("Syntax error: expression cannot start with '%c'\n", *str);
        drawLine();
        return 0;
    }
    if (len > 0 && (str[len - 1] == '+' || str[len - 1] == '-' || str[len - 1] == '*' || str[len - 1] == '/' || str[len - 1] == '^' || str[len - 1] == '('))
    {
        printf("Syntax error: expression cannot end with '%c'\n", str[len - 1]);
        drawLine();
        return 0;
    }

    while (*str)
    {
        if ((*str == '-' || *str == '+') && (*(str - 1) == '('))
        {
            enQueue(queue, "0");
            if (*str == '-')
                enQueue(queue, "-");
            else
                enQueue(queue, "+");
            str++;
        }
        else if (isdigit(*str) || (*str == '-' && !isdigit(*(str - 1)) && *(str - 1) != '(') || *str == '.')
        {
            foundNum = 0;
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
            enQueue(queue, number);
            foundNum = 1;
            free(number);
            if (isalpha(*str) || *str == '%')
            {
                enQueue(queue, "*");
            }
        }
        else if (*str == '(' && isdigit(*(str - 1)) && *(str - 2) != '_')
        {
            enQueue(queue, "*");
            enQueue(queue, "(");
            str++;
        }
        else if (*str == ')' && isdigit(*(str + 1)))
        {
            enQueue(queue, ")");
            enQueue(queue, "*");
            str++;
        }
        else if (*str == '%' && isdigit(*(str + 1)))
        {
            printf("Syntax error\n");
            drawLine();
            return 0;
        }
        else if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^')
        {
            if (((*(str + 1) == '*' || *(str + 1) == '/') && (*str == '*' || *str == '/')) || *(str + 1) == '%')
            {
                printf("Syntax error: consecutive '%c' and '%c' operators\n", *str, *(str + 1));
                drawLine();
                return 0;
            }
            char *op = (char *)malloc(2);
            op[0] = *str;
            op[1] = '\0';
            enQueue(queue, op);
            free(op);
            str++;
        }
        else if (*str == '(' || *str == ')')
        {
            char *paren = (char *)malloc(2);
            paren[0] = *str;
            paren[1] = '\0';
            enQueue(queue, paren);
            free(paren);
            str++;
        }
        else if (isalpha(*str) || *str == '%' || *str == '_')
        {
            char *start = str;
            while (isalpha(*str) || *str == '_' || *str == '%')
            {
                str++;
            }
            char *word = (char *)malloc(str - start + 1);
            strncpy(word, start, str - start);
            word[str - start] = '\0';
            if (isFunction(word))
            {
                enQueue(queue, word);
            }
            else if (isConstant(word))
            {
                enQueue(queue, word);
            }
            else if (isVariable(word, head))
            {

                enQueue(queue, word);
            }
            else
            {
                if (!foundNum)
                {
                    addVariable(&head, word, 0);
                    char *temp = (char *)malloc(strlen(word) + 2);
                    strcpy(temp, "1");
                    strcat(temp, word);
                    enQueue(queue, temp);
                    free(temp);
                }
                else
                {
                    addVariable(&head, word, 0);
                    enQueue(queue, word);
                }
            }
            free(word);
        }
        else
        {
            printf("Syntax error: invalid character '%c'\n", *str);
            drawLine();
            str++;
            return 0;
        }
    }
    return 1;
}

int isMatrixOperator(char *str)
{
    return strcmp(str, "'") == 0 || strcmp(str, "^-1") == 0 || strcmp(str, "*") == 0 || strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "inv") == 0 || strcmp(str, "T") == 0;
}

int tokenizeMatrix(Queue *queue, char *str, MatrixNode *head)
{
    removeSpaces(str);
    int foundNum = 0;
    int const len = strlen(str);
    if (*str == '-' || *str == '+')
    {
        enQueue(queue, "Z");
    }
    if (*str == '*' || *str == '/' || *str == '^' || *str == ')')
    {
        printf("Syntax error: expression cannot start with '%c'\n", *str);
        drawLine();
        return 0;
    }
    if (len > 0 && (str[len - 1] == '+' || str[len - 1] == '-' || str[len - 1] == '*' || str[len - 1] == '/' || str[len - 1] == '^' || str[len - 1] == '('))
    {
        printf("Syntax error: expression cannot end with '%c'\n", str[len - 1]);
        drawLine();
        return 0;
    }

    while (*str)
    {
        if ((*str == '-' || *str == '+') && (*(str - 1) == '('))
        {
            enQueue(queue, "Z");
            if (*str == '-')
                enQueue(queue, "-");
            else
                enQueue(queue, "+");
            str++;
        }
        else if (isdigit(*str) || (*str == '-' && !isdigit(*(str - 1)) && *(str - 1) != '(') || *str == '.')
        {
            foundNum = 0;
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
            enQueue(queue, number);
            foundNum = 1;
            free(number);
            if (isalpha(*str) && !isMatrix(head, *str))
            {
                enQueue(queue, "*");
            }
        }
        else if (*str == '(' && isdigit(*(str - 1)) && *(str - 2) != '_')
        {
            enQueue(queue, "*");
            enQueue(queue, "(");
            str++;
        }
        else if (*str == ')' && isdigit(*(str + 1)))
        {
            enQueue(queue, ")");
            enQueue(queue, "*");
            str++;
        }
        else if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^' || *str == '\'')
        {
            if (((*(str + 1) == '*' || *(str + 1) == '/') && (*str == '*' || *str == '/')))
            {
                printf("Syntax error: consecutive '%c' and '%c' operators\n", *str, *(str + 1));
                drawLine();
                return 0;
            }
            char *op = (char *)malloc(2);
            op[0] = *str;
            op[1] = '\0';
            enQueue(queue, op);
            free(op);
            str++;
        }
        else if (*str == '(' || *str == ')')
        {
            char *paren = (char *)malloc(2);
            paren[0] = *str;
            paren[1] = '\0';
            enQueue(queue, paren);
            free(paren);
            str++;
        }
        else if (isalpha(*str) || *str == '_')
        {
            char *start = str;
            while (isalpha(*str) || *str == '_')
            {
                str++;
            }
            char *word = (char *)malloc(str - start + 1);
            strncpy(word, start, str - start);
            word[str - start] = '\0';
            if (isMatrixOperator(word))
            {
                enQueue(queue, word);
            }
            else if (isMatrix(head, *word))
            {
                enQueue(queue, word);
            }
            else
            {
                printf("Syntax error: invalid matrix '%s'\n", word);
                drawLine();
                return 0;
            }
        }
        else
        {
            printf("Syntax error: invalid character '%c'\n", *str);
            drawLine();
            str++;
            return 0;
        }
    }
    return 1;
}
