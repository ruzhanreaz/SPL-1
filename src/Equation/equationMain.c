#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

void equationMenu()
{
    while (1)
    {
        drawTitle(2);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Solve\n");
        printf("4. Clear\n");
        printf("5. Back\n");
        printf("6. Exit\n");
        drawLine();
        printf("Select mode: ");
        char str[MAX_INPUT_SIZE];
        getStrInput(str);
        checkInput(str);
        int choice = atoi(str);
        switch (choice)
        {
        case 1:
            degreeMode = 1;
            equation();
            break;
        case 2:
            degreeMode = 0;
            equation();
            break;
        case 3:
            equation();
            break;
        case 4:
            clearVariables();
            equation();
            break;
        case 5:
            equation();
            break;
        case 6:
            clearScreen();
            printf("Exiting calculator. Goodbye!\n");
            exit(0);
        default:
            equation();
            break;
        }
    }
}

void equation()
{
    drawTitle(3);

    char eqn[MAX_INPUT_SIZE];
    while (1)
    {
        varList = NULL;
        variables = NULL;
        numVariables = 0;

        getStrInput(eqn);
        checkInput(eqn);

        if (strchr(eqn, '=') == NULL)
        {
            char *temp = strdup(eqn);
            char *ptr = temp;
            while (*ptr)
            {
                if (isalpha(*ptr))
                {
                    char *start = ptr;
                    while (isalpha(*ptr))
                    {
                        ptr++;
                    }
                    char *var = malloc(ptr - start + 1);
                    strncpy(var, start, ptr - start);
                    var[ptr - start] = '\0';
                    if (!isVarExist(var) && !isFunction(var))
                        addVariable(var);
                    else
                    {
                        free(var);
                    }
                }
                else
                {
                    ptr++;
                }
            }
            free(temp);
            for (int i = 0; i < numVariables; i++)
            {
                printf("%s : ", varList[i]);
                char value[MAX_INPUT_SIZE];
                getStrInput(value);
                checkInput(value);
                setVarValue(varList[i], value);
            }
            Queue *infixQueue = createQueue();
            int valid = 1;
            valid = tokenize(infixQueue, eqn);
            if (isQueueEmpty(infixQueue) || !valid)
            {
                freeQueue(infixQueue);
                return;
            }
            Queue *postfixQueue = createQueue();
            infixToPostfix(infixQueue, postfixQueue);
            char *result = (char *)malloc(100);
            postfixEvaluateComp(postfixQueue, result);
            freeQueue(infixQueue);
            freeQueue(postfixQueue);
            outputString(result);
            free(result);
        }
        else
        {
            char *modEqn = (char *)calloc(100, sizeof(char));
            modifyEqn(eqn, modEqn);
            solve(modEqn);
            free(modEqn);
        }
        if (varList != NULL)
        {
            for (int i = 0; i < numVariables; i++)
            {
                if (varList[i] != NULL)
                    free(varList[i]);
                if (variables[i].varName != NULL)
                    free(variables[i].varName);
                if (variables[i].value != NULL)
                    free(variables[i].value);
            }
            free(varList);
            free(variables);
            varList = NULL;
            variables = NULL;
            numVariables = 0;
        }
    }
}
