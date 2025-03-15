#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"
#include "header.h"

void postfixEvaluateComp(Queue *postfix, char *result)
{
    Stack *s = createStack();
    while (!isQueueEmpty(postfix))
    {
        char *token = deQueue(postfix);

        if (isFunction(token))
        {
            double res;

            if (isTrigonometricFunction(token) || isInverseTrigonometricFunction(token) || strcmp(token, "ln") == 0 || strcmp(token, "log") == 0)
            {
                if (degreeMode && (isTrigonometricFunction(token)))
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
                else if (strcmp(token, "csc") == 0)
                {
                    double value = sin(atof(op));
                    if (value == 0)
                    {
                        printf("Error: Division by zero in csc\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    res = 1 / value;
                }
                else if (strcmp(token, "sec") == 0)
                {
                    double value = cos(atof(op));
                    if (value == 0)
                    {
                        printf("Error: Division by zero in sec\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    res = 1 / value;
                }
                else if (strcmp(token, "cot") == 0)
                {
                    double value = tan(atof(op));
                    if (value == 0)
                    {
                        printf("Error: Division by zero in cot\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    res = 1 / value;
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
                else if (strcmp(token, "acsc") == 0)
                {
                    double value = atof(op);
                    if (value == 0)
                    {
                        printf("Error: Division by zero in acsc\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    value = 1 / value;
                    if (value < -1 || value > 1)
                    {
                        printf("Error: acsc out of range\n");
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
                else if (strcmp(token, "asec") == 0)
                {
                    double value = atof(op);
                    if (value == 0)
                    {
                        printf("Error: Division by zero in asec\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    value = 1 / value;
                    if (value < -1 || value > 1)
                    {
                        printf("Error: asec out of range\n");
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
                else if (strcmp(token, "acot") == 0)
                {
                    double value = atof(op);
                    if (value == 0)
                    {
                        printf("Error: Division by zero in acot\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    value = 1 / value;
                    if (degreeMode)
                    {
                        res = atan(value) * 180 / PI;
                    }
                    else
                    {
                        res = atan(value);
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

char *compOperation(char *str)
{

    Queue *infixQueue = createQueue();
    int isValid = 1;
    isValid = tokenize(infixQueue, str);
    // printQueue(infixQueue);

    if (isQueueEmpty(infixQueue) || !isValid)
    {
        freeQueue(infixQueue);
        return NULL;
    }

    Queue *postfixQueue = createQueue();
    infixToPostfix(infixQueue, postfixQueue);
    // printQueue(postfixQueue);
    char *result = (char *)malloc(100);
    postfixEvaluateComp(postfixQueue, result);
    freeQueue(infixQueue);
    freeQueue(postfixQueue);

    return result;
}
void computation()
{
    drawTitle(2);
    char expression[MAX_INPUT_SIZE];

    while (1)
    {
        getStrInput(expression);
        if (compOperation(expression) == NULL)
        {
            continue;
        }
        else
            outputString(compOperation(expression));
    }
}