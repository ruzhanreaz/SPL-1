#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "normalCalculator.h"
#include "intStack.h"
#include "charStack.h"

int precedence(char operator)
{
    if (operator== '+' || operator== '-')
    {
        return 1;
    }
    else if (operator== '*' || operator== '/')
    {
        return 2;
    }
    else if (operator== '^')
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

void infixToPostfix(char *infix, char *postfix)
{
    int i = 0;
    int j = 0;
    while (infix[i] != '\0')
    {
        if (isdigit(infix[i]))
        {
            while (isdigit(infix[i]))
            {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (infix[i] == '(')
        {
            pushChar(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (peekChar() != '(')
            {
                postfix[j++] = popChar();
                postfix[j++] = ' ';
            }
            popChar();
        }
        else if (infix[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            while (!is_emptyc() && precedence(peekChar()) >= precedence(infix[i]))
            {
                postfix[j++] = popChar();
                postfix[j++] = ' ';
            }
            pushChar(infix[i]);
        }
        i++;
    }
    while (!is_emptyc())
    {
        postfix[j++] = popChar();
        postfix[j++] = ' ';
    }
    postfix[j - 1] = '\0';
}

int evaluatePostfix(char *postfix)
{
    int i = 0;
    int length = strlen(postfix);
    while (i < length)
    {
        if (isdigit(postfix[i]))
        {
            int num = 0;
            while (i < length && isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushInt(num);
            i--;
        }
        else if (postfix[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            int operand2 = popInt();
            int operand1 = popInt();
            int result = 0;
            switch (postfix[i])
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            case '^':
                result = (int)pow(operand1, operand2);
                break;
            }
            pushInt(result);
        }
        i++;
    }

    return popInt();
}