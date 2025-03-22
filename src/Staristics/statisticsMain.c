#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

void statistics()
{
    drawTitle(3);
    char expression[MAX_INPUT_SIZE];

    titleNameList = (char **)malloc(numOfColumn * sizeof(char *));
    for (int i = 0; i < numOfColumn; i++)
    {
        titleNameList[i] = dataColumns[i].name;
    }
    while (1)
    {
        getStrInput(expression);
        checkInput(expression);
        Queue *infixQueue = createQueue();
        // printQueue(infixQueue);
        int isValid = 1;
        isValid = tokenize(infixQueue, expression);
        if (isQueueEmpty(infixQueue) || !isValid)
        {
            freeQueue(infixQueue);
            continue;
        }
        Queue *postfixQueue = createQueue();
        infixToPostfix(infixQueue, postfixQueue);
        // printQueue(postfixQueue);
        char *result = (char *)malloc(100);
        postfixEvaluateStat(postfixQueue, result);
        freeQueue(infixQueue);
        freeQueue(postfixQueue);
        outputString(result);
        free(result);
    }
}

void statisticsMenu()
{
    while (1)
    {
        drawTitle(2);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Add Column\n");
        printf("4. Show data\n");
        printf("5. Sort data\n");
        printf("6. Regression\n");
        printf("7. Clear all data\n");
        printf("8. Clear column\n");
        printf("9. Back\n");
        printf("10. Exit\n");
        drawLine();
        printf("Select option: ");
        char str[MAX_INPUT_SIZE];
        getStrInput(str);
        checkInput(str);
        int modeNum = atoi(str);
        if (modeNum > 8 || modeNum < 1)
        {
            printf("Invalid option. Try again.\n");
            continue;
        }
        switch (modeNum)
        {
        case 1:
            degreeMode = 1;
            statistics();
            break;
        case 2:
            degreeMode = 0;
            statistics();
            break;

        case 3:
            setData();
            statistics();
            break;
        case 4:
            showData();
            statistics();
            break;
        case 5:
            sortData();
            statistics();
            break;
        case 6:
            regMode = 1;
            regression();

            statistics();
            break;
        case 7:
            clearAllData();
            statistics();
            break;
        case 8:
            clearColumn();
            statistics();
            break;
        case 9:
            statistics();
            break;
        case 10:
            clearAllData();
            clearScreen();
            printf("Exiting calculator. Goodbye!\n");
            exit(0);
        default:
            statistics();
            break;
        }
    }
}