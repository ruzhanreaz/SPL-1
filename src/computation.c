#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

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
    else if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "tan") == 0 || strcmp(op, "asin") == 0 || strcmp(op, "acos") == 0 || strcmp(op, "atan") == 0 || strcmp(op, "log") == 0 || strcmp(op, "ln") == 0 || strcmp(op, "log_") == 0)
    {
        return 3;
    }
    else if (strcmp(op, "^") == 0 || strcmp(op, "exp") == 0 || strcmp(op, "'") == 0 || strcmp(op, "^-1") == 0 || strcmp(op, "inv") == 0 || strcmp(op, "T") == 0)
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
    if (strcmp(op, "^") == 0)
    {
        return 1;
    }
    return 0;
}

int isOperator(char *str)
{
    return strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0 || strcmp(str, "^") == 0 || strcmp(str, "exp") == 0 || strcmp(str, "log") == 0 || strcmp(str, "ln") == 0 || strcmp(str, "log_") == 0;
}

int isTrigFunction(char *str)
{
    return strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 || strcmp(str, "asin") == 0 || strcmp(str, "acos") == 0 || strcmp(str, "atan") == 0;
}

void infixToPostfix(Queue *infix, Queue *postfix, Variable *head)
{
    Stack *opStack = createStack();
    while (!isQueueEmpty(infix))
    {
        char *token = deQueue(infix);
        if (strcmp(token, "%") == 0)
        {
            enQueue(postfix, "0.01");
            continue;
        }
        if (strcmp(token, "pi") == 0)
        {
            enQueue(postfix, "3.14159265359");
            continue;
        }
        if (strcmp(token, "e") == 0)
        {
            enQueue(postfix, "2.71828182846");
            continue;
        }
        if (isVariable(token, head))
        {
            double value;
            getVariableValue(head, token, &value);
            char *valueStr = (char *)malloc(100);
            sprintf(valueStr, "%lf", value);
            enQueue(postfix, valueStr);
            continue;
        }
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
        else if (isOperator(token) || isFunction(token))
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

void postfixEvaluate(Queue *postfix, int degreeMode, char *result)
{
    Stack *s = createStack();
    while (!isQueueEmpty(postfix))
    {
        char *token = deQueue(postfix);

        if (isOperator(token) || isFunction(token))
        {
            double res;

            if (strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0 ||
                strcmp(token, "asin") == 0 || strcmp(token, "acos") == 0 || strcmp(token, "atan") == 0 ||
                strcmp(token, "exp") == 0 || strcmp(token, "log") == 0 || strcmp(token, "ln") == 0)
            {
                if (degreeMode && (strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0))
                {
                    char *op = pop(s);
                    double angle = atof(op);
                    angle = angle * PI / 180;
                    free(op);
                    char *angleStr = (char *)malloc(100);
                    sprintf(angleStr, "%lf", angle);
                    push(s, angleStr);
                }
                char *op = pop(s);
                if (strcmp(token, "sin") == 0)
                {
                    res = sin(atof(op));
                }
                else if (strcmp(token, "cos") == 0)
                {
                    res = cos(atof(op));
                }
                else if (strcmp(token, "tan") == 0)
                {
                    res = tan(atof(op));
                }
                else if (strcmp(token, "asin") == 0)
                {
                    double value = atof(op);
                    if (value < -1 || value > 1)
                    {
                        printf("Error: asin out of range\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    if (degreeMode)
                    {
                        res = asin(value) * 180 / PI;
                    }
                    else
                    {
                        res = asin(value);
                    }
                }
                else if (strcmp(token, "acos") == 0)
                {
                    double value = atof(op);
                    if (value < -1 || value > 1)
                    {
                        printf("Error: acos out of range\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    if (degreeMode)
                    {
                        res = acos(value) * 180 / PI;
                    }
                    else
                    {
                        res = acos(value);
                    }
                }
                else if (strcmp(token, "atan") == 0)
                {
                    if (degreeMode)
                    {
                        res = atan(atof(op)) * 180 / PI;
                    }
                    else
                    {
                        res = atan(atof(op));
                    }
                }
                else if (strcmp(token, "exp") == 0)
                {
                    res = exp(atof(op));
                }
                else if (strcmp(token, "log") == 0)
                {
                    if (atof(op) > 0)
                    {
                        res = log10(atof(op));
                    }
                    else
                    {
                        printf("Error: Logarithm of non-positive number\n");
                        drawLine();
                        free(op);
                        return;
                    }
                }
                else if (strcmp(token, "ln") == 0)
                {
                    if (atof(op) > 0)
                    {
                        res = log(atof(op));
                    }
                    else
                    {
                        printf("Error: Natural logarithm of non-positive number\n");
                        drawLine();
                        free(op);
                        return;
                    }
                }
                free(op);
            }
            else
            {

                char *op2 = pop(s);
                char *op1 = pop(s);

                if (strcmp(token, "+") == 0)
                {
                    res = atof(op1) + atof(op2);
                }
                else if (strcmp(token, "-") == 0)
                {
                    res = atof(op1) - atof(op2);
                }
                else if (strcmp(token, "*") == 0)
                {
                    res = atof(op1) * atof(op2);
                }
                else if (strcmp(token, "/") == 0)
                {
                    if (atof(op2) == 0)
                    {
                        printf("Error: Division by zero\n");
                        drawLine();
                        free(op1);
                        free(op2);
                        return;
                    }
                    else
                    {
                        res = atof(op1) / atof(op2);
                    }
                }
                else if (strcmp(token, "^") == 0)
                {
                    res = pow(atof(op1), atof(op2));
                }
                else if (strcmp(token, "log_") == 0)
                {
                    if (atof(op1) > 0 && atof(op2) > 0)
                    {
                        res = log(atof(op2)) / log(atof(op1));
                    }
                    else
                    {
                        printf("Error: Logarithm of non-positive number\n");
                        drawLine();
                        free(op1);
                        free(op2);
                        return;
                    }
                }
                free(op1);
                free(op2);
            }

            char *resultStr = (char *)malloc(100);
            sprintf(resultStr, "%lf", res);
            push(s, resultStr);
        }
        else
        {
            push(s, token);
        }
    }
    char *finalResult = pop(s);
    strcpy(result, finalResult);
    free(finalResult);
    freeStack(s);
}

char *compOperation(char *str, int degreeMode, Variable *head)
{

    Queue *infixQueue = createQueue();
    int isValid = 1;
    isValid = tokenize(infixQueue, str, head);
    // printQueue(infixQueue);

    if (isQueueEmpty(infixQueue) || !isValid)
    {
        freeQueue(infixQueue);
        return NULL;
    }

    Queue *postfixQueue = createQueue();
    infixToPostfix(infixQueue, postfixQueue, head);
    // printQueue(postfixQueue);
    char *result = (char *)malloc(100);
    postfixEvaluate(postfixQueue, degreeMode, result);
    freeQueue(infixQueue);
    freeQueue(postfixQueue);

    return result;
}

void computation(int degreeMode)
{
    char *mode = "Computation";
    drawTitle(mode, degreeMode);
    char str[128];

    while (1)
    {
        getStrInput(str);
        if (compOperation(str, degreeMode, NULL) == NULL)
        {
            continue;
        }
        else
            outputString(compOperation(str, degreeMode, NULL));
    }
}
