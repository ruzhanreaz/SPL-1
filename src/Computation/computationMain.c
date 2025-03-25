#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void computationMenu()
{
    while (1)
    {
        drawTitle(2);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Scientific Output Format\n");
        printf("4. Normal Output Format\n");
        printf("5. Back\n");
        printf("6. Exit\n");
        drawLine();
        printf("Select mode: ");
        char str[MAX_INPUT_SIZE];
        getStrInput(str);
        checkInput(str);
        int modeNum = atoi(str);
        if (modeNum > 6 || modeNum < 1)
        {
            printf("Invalid option. Try again.\n");
            continue;
        }
        switch (modeNum)
        {
        case 1:
            degreeMode = 1;
            computation();
            break;
        case 2:
            degreeMode = 0;
            computation();
            break;
        case 3:
            scientificMode = 1;
            printf("Set Precision(1~12): ");
            int p = 0;
            getStrInput(str);
            checkInput(str);
            p = atoi(str);
            if (p < 1 || p > 12)
            {
                printf("Invalid precision. Try again.\n");
                continue;
            }
            precision = p;
            computation();
            break;
        case 4:
            scientificMode = 0;
            printf("Set Precision(1~12): ");
            p = 0;
            getStrInput(str);
            checkInput(str);
            p = atoi(str);
            if (p < 1 || p > 12)
            {
                printf("Invalid precision. Try again.\n");
                continue;
            }
            precision = p;
            computation();
            break;
        case 5:
            return;
        case 6:
            clearScreen();
            printf("Exiting calculator. Goodbye!\n");
            exit(0);
        default:
            computation();
            break;
        }
    }
}

void computation()
{
    while (1)
    {
        drawTitle(3);
        char str[MAX_INPUT_SIZE];
        while (1)
        {
            getStrInput(str);
            checkInput(str);
            Queue *infixQueue = createQueue();
            int isValid = 1;
            isValid = tokenize(infixQueue, str);
            if (isQueueEmpty(infixQueue) || !isValid)
            {
                printf("Invalid expression. Try again.\n");
                freeQueue(infixQueue);
                continue;
            }
            Queue *postfixQueue = createQueue();
            infixToPostfix(infixQueue, postfixQueue);
            char *result = (char *)malloc(100);
            postfixEvaluateComp(postfixQueue, result);
            outputString(result);
            freeQueue(infixQueue);
            freeQueue(postfixQueue);
            free(result);
        }
    }
}