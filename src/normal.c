#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "normal.h"
#include "constant.h"
#include "menu.h"
#include <stdbool.h>

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
    else if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "tan") == 0 || strcmp(op, "asin") == 0 || strcmp(op, "acos") == 0 || strcmp(op, "atan") == 0 || strcmp(op, "log") == 0 || strcmp(op, "ln") == 0)
    {
        return 3;
    }
    else if (strcmp(op, "^") == 0 || strcmp(op, "exp") == 0)
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
    return strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0 || strcmp(str, "^") == 0 || strcmp(str, "exp") == 0 || strcmp(str, "log") == 0 || strcmp(str, "ln") == 0;
}

int isTrigFunction(char *str)
{
    return strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 || strcmp(str, "asin") == 0 || strcmp(str, "acos") == 0 || strcmp(str, "atan") == 0;
}

bool degreeMode = false;

void enableDegreeMode()
{
    degreeMode = true;
}

void disableDegreeMode()
{
    degreeMode = false;
}

bool isDegreeModeEnabled()
{
    return degreeMode;
}

void infixToPostfix(Queue *infix, Queue *postfix)
{
    Stack *opStack = createStack();
    while (!isQueueEmpty(infix))
    {
        char *token = dequeue(infix);
        if (strcmp(token, "%") == 0)
        {
            enqueue(postfix, "0.01");
            enqueue(postfix, "*");
            break;
        }

        if (strcmp(token, "(") == 0)
        {
            push(opStack, token);
        }
        else if (strcmp(token, ")") == 0)
        {
            while (strcmp(peek(opStack), "(") != 0)
            {
                enqueue(postfix, pop(opStack));
            }
            pop(opStack);
        }
        else if (isOperator(token) || isFunction(token))
        {
            while (!isStackEmpty(opStack) && getPrecedence(peek(opStack)) >= getPrecedence(token) && !rightAssociative(token))
            {
                enqueue(postfix, pop(opStack));
            }
            push(opStack, token);
        }

        else
        {
            enqueue(postfix, token);
        }
    }

    while (!isStackEmpty(opStack))
    {
        enqueue(postfix, pop(opStack));
    }

    freeStack(opStack);
}
void check_number(double num)
{
    if (num == (long)num)
    {
        printf("%*ld\n", 80, (long)num);

        // printLine();
    }
    else
    {
        double fractional_part = num - (int)num;
        int decimal_places = 0;

        while (fractional_part != (int)fractional_part && decimal_places < 10)
        {
            fractional_part *= 10;
            decimal_places++;
        }

        printf("%*.*lf\n", 80, decimal_places, num);
        // printLine();
    }
}

void postfixEvaluate(Queue *postfix)
{
    Stack *s = createStack();
    while (!isQueueEmpty(postfix))
    {
        char *token = dequeue(postfix);
        if (strcmp(token, "pi") == 0)
        {
            char *pi = (char *)malloc(100);
            sprintf(pi, "%lf", PI);
            enqueueAtFront(postfix, pi);
            continue;
        }
        if (strcmp(token, "e") == 0)
        {
            char *e = (char *)malloc(100);
            sprintf(e, "%lf", E);
            enqueueAtFront(postfix, e);
            continue;
        }

        if (isOperator(token) || isFunction(token))
        {
            double result;

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
                    result = sin(atof(op));
                }
                else if (strcmp(token, "cos") == 0)
                {
                    result = cos(atof(op));
                }
                else if (strcmp(token, "tan") == 0)
                {
                    result = tan(atof(op));
                }
                else if (strcmp(token, "asin") == 0)
                {
                    if (degreeMode)
                    {
                        result = asin(atof(op)) * 180 / PI;
                    }
                    else
                        result = asin(atof(op));
                }
                else if (strcmp(token, "acos") == 0)
                {
                    if (degreeMode)
                    {
                        result = acos(atof(op)) * 180 / PI;
                    }
                    else
                        result = acos(atof(op));
                }
                else if (strcmp(token, "atan") == 0)
                {
                    if (degreeMode)
                    {
                        result = atan(atof(op)) * 180 / PI;
                    }
                    else
                        result = atan(atof(op));
                }
                else if (strcmp(token, "exp") == 0)
                {
                    result = exp(atof(op));
                }
                else if (strcmp(token, "log") == 0)
                {
                    result = log10(atof(op));
                }
                else if (strcmp(token, "ln") == 0)
                {
                    result = log(atof(op));
                }
                free(op);
            }
            else
            {

                char *op2 = pop(s);
                char *op1 = pop(s);

                if (strcmp(token, "+") == 0)
                {
                    result = atof(op1) + atof(op2);
                }
                else if (strcmp(token, "-") == 0)
                {
                    result = atof(op1) - atof(op2);
                }
                else if (strcmp(token, "*") == 0)
                {
                    result = atof(op1) * atof(op2);
                }
                else if (strcmp(token, "/") == 0)
                {
                    result = atof(op1) / atof(op2);
                }

                else if (strcmp(token, "^") == 0)
                {
                    result = pow(atof(op1), atof(op2));
                }
                free(op1);
                free(op2);
            }

            char *resultStr = (char *)malloc(100);
            sprintf(resultStr, "%lf", result);
            push(s, resultStr);
        }
        else
        {
            push(s, token);
        }
    }

    check_number(atof(pop(s)));
    printLine();
    freeStack(s);
}

int normal(char *mode)
{
    clearScreen();
    drawTitle(mode);
    char str[100];
    while (1)
    {
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = '\0';
        if (str[0] == 'm' || str[0] == 'M')
            return 1;
        else if (str[0] == 'q' || str[0] == 'Q')
            return 0;

        Queue *infixQueue = createQueue();

        bool valid = false;
        valid = tokenize(infixQueue, str);

        if (isQueueEmpty(infixQueue) || !valid)
        {
            freeQueue(infixQueue);
            continue;
        }

        Queue *postfixQueue = createQueue();
        infixToPostfix(infixQueue, postfixQueue);
        // printQueue(postfixQueue);
        postfixEvaluate(postfixQueue);
        freeQueue(infixQueue);
        freeQueue(postfixQueue);
    }
}
