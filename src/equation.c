#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

Equation *equationHead = NULL;

void freeEquationNode(Equation *node)
{
    if (node)
    {
        free(node->equation);
        free(node);
    }
}

void freeEquationList(Equation *head)
{
    Equation *current = head;
    while (current != NULL)
    {
        Equation *temp = current;
        current = current->next;
        freeEquationNode(temp);
    }
}

void addEquation(Equation **head, const char *equation)
{
    if (equation == NULL || *equation == '\0')
    {
        return;
    }

    Equation *newNode = (Equation *)malloc(sizeof(Equation));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed for equation\n");
        return;
    }

    newNode->equation = strdup(equation);
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Equation *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printEquations(Equation *head)
{
    if (head == NULL)
    {
        printf("No equations stored.\n");
        return;
    }

    printf("Stored Equations:\n");
    Equation *temp = head;
    int count = 1;
    while (temp != NULL)
    {
        printf("%d. %s\n", count++, temp->equation);
        temp = temp->next;
    }
}

int validateEquationInput(const char *input)
{
    if (input == NULL || strlen(input) == 0)
    {
        return 0;
    }

    char *equalSign = strchr(input, '=');
    if (equalSign == NULL)
    {
        return 0;
    }

    if (equalSign == input || *(equalSign + 1) == '\0')
    {
        return 0;
    }

    return 1;
}

void processVariableAssignment(const char *lhsStr, const char *rhsStr, Variable **head, int degreeMode)
{
    int isValid = 1;
    Queue *infixQueue = createQueue();
    Queue *postfixQueue = createQueue();
    char *rhsResult = (char *)malloc(100);

    isValid = tokenize(infixQueue, (char *)rhsStr, *head);
    if (isValid)
    {
        infixToPostfix(infixQueue, postfixQueue, *head);
        postfixEvaluate(postfixQueue, degreeMode, rhsResult);

        if (!isVariable((char *)lhsStr, *head))
            addVariable(head, (char *)lhsStr, atof(rhsResult));
        else
            editVariable(*head, (char *)lhsStr, atof(rhsResult));
    }
    else
    {
        printf("Invalid expression for variable assignment\n");
    }

    free(rhsResult);
    freeQueue(infixQueue);
    freeQueue(postfixQueue);
}

void processEquation(const char *lhsStr, const char *rhsStr, Equation **equationHead)
{
    char *newLhsStr = (char *)malloc(strlen(lhsStr) + strlen(rhsStr) + 20);

    sprintf(newLhsStr, "%s-(%s)=0.0", lhsStr, rhsStr);
    addEquation(equationHead, newLhsStr);

    free(newLhsStr);
}
void solveEquation(int numOfEqn, const char *title)
{
    drawTitle((char *)title, -1);
    char input[128];

    while (numOfEqn > 0)
    {
        getStrInput(input);

        if (!validateEquationInput(input))
        {
            printf("Invalid equation format. Please try again.\n");
            continue;
        }

        char *lhsStr = strtok(input, "=");
        char *rhsStr = strtok(NULL, "=");

        removeSpaces(lhsStr);
        removeSpaces(rhsStr);

        processEquation(lhsStr, rhsStr, &equationHead);
        numOfEqn--;
    }

    printEquations(equationHead);
    freeEquationList(equationHead);
}

void solve2VarLinEqn()
{
    solveEquation(2, "2 Variable Linear Equation");
}

void solve3VarLinEqn()
{
    solveEquation(3, "3 Variable Linear Equation");
}

void solveQuadraticEqn()
{
    solveEquation(1, "Quadratic Equation");
}

void solveCubicEqn()
{
    solveEquation(1, "Cubic Equation");
}

void equationMenu()
{
    int choice = 0;

    while (choice < 1 || choice > 4)
    {
        drawTitle("Equation Menu", -1);
        const char *menuItems[] = {
            "1. 2 variable linear equation", "2. 3 variable linear equation",
            "3. Quadratic equation", "4. Cubic equation"};

        for (int i = 0; i < 4; i += 2)
        {
            if (i + 1 < 4)
            {
                printf("%-30s%-30s\n", menuItems[i], menuItems[i + 1]);
            }
            else
            {
                printf("%-30s\n", menuItems[i]);
            }
        }
        drawLine();
        printf("Enter your choice(1-4): ");
        char input[10];
        if (scanf("%9s", input) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
            continue;
        }
        choice = atoi(input);
    }
    while (getchar() != '\n' && getchar() != EOF)
        ;
    switch (choice)
    {
    case 1:
        solve2VarLinEqn();
        break;
    case 2:
        solve3VarLinEqn();
        break;
    case 3:
        solveQuadraticEqn();
        break;
    case 4:
        solveCubicEqn();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

void equation(int degreeMode)
{
    drawTitle("Equation", degreeMode);

    char *input = (char *)malloc(128);

    Variable *variableHead = NULL;
    Equation *equationHead = NULL;

    while (1)
    {
        getStrInput(input);
        if (strlen(input) == 1 && input[0] == 'M')
        {
            equationMenu();
        }
        else
        {
            if (!validateEquationInput(input))
            {
                char *result = compOperation(input, degreeMode, variableHead);
                if (result == NULL)
                {
                    continue;
                }
                else
                {
                    outputString(result);
                }
            }
            else
            {
                char *lhsStr = strtok(input, "=");
                char *rhsStr = strtok(NULL, "=");

                removeSpaces(lhsStr);
                removeSpaces(rhsStr);

                int lhsLen = strlen(lhsStr);
                int lhsIsVariable = 0;
                char *lhsStrCopy = lhsStr;
                while (lhsLen != 0)
                {
                    if (isalpha(*lhsStrCopy))
                    {
                        lhsIsVariable = 1;
                    }
                    else
                    {
                        lhsIsVariable = 0;
                        break;
                    }

                    lhsStrCopy++;
                    lhsLen--;
                }

                if (lhsIsVariable)
                {
                    processVariableAssignment(lhsStr, rhsStr, &variableHead, degreeMode);
                }
                else
                {
                    processEquation(lhsStr, rhsStr, &equationHead);

                    Queue *infixQueue = createQueue();
                    char *lhs = strtok(equationHead->equation, "=");

                    tokenize(infixQueue, lhs, variableHead);
                    printEquations(equationHead);

                    printQueue(infixQueue);
                    printVariables(variableHead);
                    freeQueue(infixQueue);
                }
            }
            printVariables(variableHead);
        }
    }
    free(input);
    freeEquationList(equationHead);
}