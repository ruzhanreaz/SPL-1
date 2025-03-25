#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int isArithmeticOperator(char *str)
{
    return (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0 || strcmp(str, "^") == 0);
}

int isTrigonometricFunction(char *str)
{
    return (strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 || strcmp(str, "csc") == 0 || strcmp(str, "sec") == 0 || strcmp(str, "cot") == 0);
}

int isInverseTrigonometricFunction(char *str)
{
    return (strcmp(str, "asin") == 0 || strcmp(str, "acos") == 0 || strcmp(str, "atan") == 0 || strcmp(str, "acsc") == 0 || strcmp(str, "asec") == 0 || strcmp(str, "acot") == 0);
}

int isLogarithmicFunction(char *str)
{
    return (strcmp(str, "log") == 0 || strcmp(str, "ln") == 0) || strcmp(str, "log_") == 0;
}

int isStatisticalFunction(char *str)
{
    return (strcmp(str, "mean") == 0 || strcmp(str, "sort") == 0 || strcmp(str, "sumsqr") == 0 || strcmp(str, "sumxy") == 0 || strcmp(str, "median") == 0 || strcmp(str, "mode") == 0 || strcmp(str, "range") == 0 || strcmp(str, "svar") == 0 || strcmp(str, "sstd") == 0 || strcmp(str, "pvar") == 0 || strcmp(str, "pstd") == 0 || strcmp(str, "pcov") == 0 || strcmp(str, "scov") == 0 || strcmp(str, "corr") == 0 || strcmp(str, "max") == 0 || strcmp(str, "min") == 0 || strcmp(str, "sum") == 0);
}

int isMatrixFunction(char *str)
{
    return (strcmp(str, "det") == 0 || strcmp(str, "rref") == 0 || strcmp(str, "inv") == 0 || strcmp(str, "tra") == 0 || strcmp(str, "ref") == 0 || strcmp(str, "rank") == 0);
}

int isConstant(char *str)
{
    if (mode == MODE_COMPUTATION)
        return (strcmp(str, "pi") == 0 || strcmp(str, "e") == 0) || strcmp(str, "%") == 0;
    else
        return (strcmp(str, "pi") == 0 || strcmp(str, "e") == 0);
}

int graphVariable(char *str)
{
    if (strcmp(str, "x") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void removeSpaces(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

int isFunction(char *str)
{
    switch (mode)
    {
    case MODE_COMPUTATION:
        return (isArithmeticOperator(str) || isTrigonometricFunction(str) || isInverseTrigonometricFunction(str) || isLogarithmicFunction(str));
    case MODE_STATISTICS:
        return (isStatisticalFunction(str) || isArithmeticOperator(str) || isTrigonometricFunction(str) || isInverseTrigonometricFunction(str) || isLogarithmicFunction(str));
    case MODE_EQUATION:
        return (isArithmeticOperator(str) || isTrigonometricFunction(str) || isInverseTrigonometricFunction(str) || isLogarithmicFunction(str));
    case MODE_GRAPH:
        return (isArithmeticOperator(str) || isTrigonometricFunction(str) || isInverseTrigonometricFunction(str) || isLogarithmicFunction(str));
    case MODE_MATRIX:
        return (isMatrixFunction(str) || isArithmeticOperator(str));
    default:
        return 0;
    }
}
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
char *deQueueFromLast(Queue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    Token *temp = queue->front;
    Token *prev = NULL;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    char *token = strdup(temp->token);
    if (prev == NULL)
    {
        queue->front = queue->rear = NULL;
    }
    else
    {
        prev->next = NULL;
        queue->rear = prev;
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

void queueToString(Queue *queue, char *str)
{
    Token *temp = queue->front;
    while (temp != NULL)
    {
        strcat(str, temp->token);
        temp = temp->next;
    }
}

int tokenize(Queue *queue, char *str)
{
    int foundnumber = 0;
    int bracketCount = 0;
    int removeParen = 0;

    removeSpaces(str);
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
            foundnumber = 0;
        }
        else if (isdigit(*str) || (*str == '-' && !isdigit(*(str - 1)) && *(str - 1) != '(' && !isalpha(*(str - 1)) && (*(str - 1) == '*' || *(str - 1) == '/')) || *str == '.')
        {
            int dotCount = 0;
            char *start = str;

            if (*str == '-')
            {
                str++;
            }
            while (isdigit(*str) || *str == '.')
            {
                if (*str == '.')
                {
                    dotCount++;
                }
                if (dotCount > 1)
                {
                    printf("Syntax error: invalid number '%s'\n", start);
                    drawLine();
                    return 0;
                }
                str++;
            }
            char *number = (char *)malloc(str - start + 1);
            strncpy(number, start, str - start);
            number[str - start] = '\0';
            enQueue(queue, number);
            foundnumber = 1;
            free(number);
        }
        else if (*str == '(' && isdigit(*(str - 1)) && *(str - 2) != '_')
        {
            enQueue(queue, "*");
            enQueue(queue, "(");
            bracketCount++;
            str++;
            foundnumber = 0;
        }
        else if (*str == ')' && isdigit(*(str + 1)))
        {
            enQueue(queue, ")");
            enQueue(queue, "*");
            bracketCount--;
            str++;
            foundnumber = 0;
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
            if (((*(str + 1) == '*' || *(str + 1) == '/') && (*str == '-' || *str == '+')) || *(str + 1) == '%')
            {
                printf("Syntax error: consecutive '%c' and '%c' operators\n", *str, *(str + 1));
                drawLine();
                return 0;
            }
            if (*str == '-' || *str == '+')
            {
                if (*(str + 1) == '-' || *(str + 1) == '+')
                {
                    if (*str == '-' && *(str + 1) == '-')
                    {
                        str++;
                        enQueue(queue, "+");
                    }
                    else if ((*str == '-' && *(str + 1) == '+') || (*str == '+' && *(str + 1) == '-'))
                    {
                        str++;
                        enQueue(queue, "-");
                    }
                    else if (*str == '+' && *(str + 1) == '+')
                    {
                        str++;
                        enQueue(queue, "+");
                    }
                    str++;
                    continue;
                }
            }
            char *op = (char *)malloc(2);
            op[0] = *str;
            op[1] = '\0';
            enQueue(queue, op);
            free(op);
            str++;
            foundnumber = 0;
        }
        else if (*str == '(' || *str == ')')
        {
            if (*str == '(')
                bracketCount++;
            if (*str == ')')
            {
                bracketCount--;
                if (removeParen)
                {
                    removeParen = 0;
                    str++;
                    continue;
                }
            }
            char *paren = (char *)malloc(2);
            paren[0] = *str;
            paren[1] = '\0';
            enQueue(queue, paren);
            free(paren);
            str++;
            foundnumber = 0;
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
                if (foundnumber)
                {
                    enQueue(queue, "*");
                }
                enQueue(queue, word);
            }
            else if (isConstant(word))
            {
                if (foundnumber)
                {
                    enQueue(queue, "*");
                }
                if (strcmp(word, "%") == 0)
                {
                    enQueue(queue, "0.01");
                }
                else if (strcmp(word, "pi") == 0)
                {
                    enQueue(queue, "3.14159265359");
                }
                else if (strcmp(word, "e") == 0)
                {
                    enQueue(queue, "2.71828182846");
                }
            }
            else if (mode == MODE_STATISTICS && isStatOperand(word))
            {
                char *temp1 = deQueueFromLast(queue);
                char *temp2 = deQueueFromLast(queue);

                if (strcmp("scov", temp2) == 0)
                {
                    enQueue(queue, word);
                    enQueue(queue, "scov");
                    removeParen = 1;
                    str++;
                }
                else if (strcmp("pcov", temp2) == 0)
                {
                    enQueue(queue, word);
                    enQueue(queue, "pcov");
                    removeParen = 1;
                    str++;
                }
                else if (strcmp("corr", temp2) == 0)
                {
                    enQueue(queue, word);
                    enQueue(queue, "corr");
                    removeParen = 1;
                    str++;
                }
                else if (strcmp("sumxy", temp2) == 0)
                {
                    enQueue(queue, word);
                    enQueue(queue, "sumxy");
                    removeParen = 1;
                    str++;
                }
                else
                {
                    enQueue(queue, temp2);
                    enQueue(queue, temp1);
                    enQueue(queue, word);
                }
            }
            else if (mode == MODE_EQUATION && isVarExist(word))
            {

                if (foundnumber)
                {
                    enQueue(queue, "*");
                }
                char *value = (char *)malloc(100);
                getVarValue(word, value);
                enQueue(queue, value);
                free(value);
            }
            else if (mode == MODE_EQUATION && validVar(word))
            {
                if (foundnumber)
                {
                    char *temp = deQueueFromLast(queue);
                    strcat(temp, word);
                    enQueue(queue, temp);
                    free(temp);
                }
                else
                {
                    char *temp = (char *)malloc(100);
                    strcpy(temp, "1");
                    strcat(temp, word);
                    enQueue(queue, temp);
                    free(temp);
                }
            }
            else if (mode == MODE_MATRIX && (isMatrix(word) || strcmp(word, "I") == 0))
            {
                if (foundnumber)
                {
                    enQueue(queue, "*");
                }
                enQueue(queue, word);
            }
            else if ((mode == MODE_GRAPH && graphVariable(word)) || (mode == MODE_STATISTICS && regMode))
            {
                if (foundnumber)
                {
                    enQueue(queue, "*");
                }
                char *temp = (char *)malloc(100);
                getXValue(temp);
                enQueue(queue, temp);
                free(temp);
            }
            else
            {
                printf("Syntax error: invalid function '%s'\n", word);
                drawLine();
                return 0;
            }

            free(word);
            foundnumber = 0;
        }
        else
        {
            printf("Syntax error: invalid character '%c'\n", *str);
            drawLine();
            str++;
            return 0;
        }
    }
    if (bracketCount != 0)
    {
        printf("Syntax error: unbalanced brackets\n");
        drawLine();
        return 0;
    }
    return 1;
}

Stack *createStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack *s, char *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

char *pop(Stack *s)
{
    if (s->top == NULL)
    {
        return NULL;
    }
    Node *temp = s->top;
    s->top = s->top->next;
    char *data = temp->data;
    free(temp);
    return data;
}

char *peek(Stack *s)
{
    if (s->top == NULL)
    {
        return NULL;
    }
    return s->top->data;
}

int isStackEmpty(Stack *s)
{
    return s->top == NULL;
}

void freeStack(Stack *s)
{
    while (s->top != NULL)
    {
        Node *temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
}

int getPrecedence(char *op)
{
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
    {
        return 1;
    }
    else if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
    {
        return 2;
    }
    else if (isTrigonometricFunction(op) || isInverseTrigonometricFunction(op) || isLogarithmicFunction(op) || isStatisticalFunction(op))
    {
        return 3;
    }
    else if (strcmp(op, "^") == 0 || isMatrixFunction(op))
    {
        return 4;
    }
    else
    {
        return 0;
    }
}
int rightAssociative(char *op)
{
    return (strcmp(op, "^") == 0);
}

void infixToPostfix(Queue *infix, Queue *postfix)
{
    Stack *opStack = createStack();
    while (!isQueueEmpty(infix))
    {
        char *token = deQueue(infix);
        if (strcmp(token, "(") == 0)
        {
            push(opStack, token);
        }
        else if (strcmp(token, ")") == 0)
        {
            while (strcmp(peek(opStack), "(") != 0)
            {
                enQueue(postfix, pop(opStack));
            }
            pop(opStack);
        }
        else if (isFunction(token))
        {
            while (!isStackEmpty(opStack) && getPrecedence(peek(opStack)) >= getPrecedence(token) && !rightAssociative(token))
            {
                enQueue(postfix, pop(opStack));
            }
            push(opStack, token);
        }

        else
        {
            enQueue(postfix, token);
        }
    }
    while (!isStackEmpty(opStack))
    {
        enQueue(postfix, pop(opStack));
    }

    freeStack(opStack);
}
