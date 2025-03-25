#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void clearScreen()
{
    printf("\033[H\033[J");
}

void drawLine()
{
    for (int i = 0; i < WIDTH; i++)
    {
        printf("-");
    }
    printf("\n");
}

void drawTitle(int titleType)
{
    closeGraphWindow();
    clearScreen();
    char modeStr[20];
    char degreeStr[20];
    switch (mode)
    {
    case 1:
        strcpy(modeStr, "Computation");
        break;
    case 2:
        strcpy(modeStr, "Statistics");
        break;
    case 3:
        strcpy(modeStr, "Matrix");
        break;
    case 4:
        strcpy(modeStr, "Equation");
        break;
    case 5:
        strcpy(modeStr, "Graph");
        break;
    default:
        strcpy(modeStr, "Computation");
        break;
    }
    if (degreeMode)
    {
        strcpy(degreeStr, "Degree");
    }
    else
    {
        strcpy(degreeStr, "Radian");
    }

    switch (titleType)
    {
    case 1:
        printf("%s\n", "Main Menu");
        break;
    case 2:
        printf("%s%s%*s\n", modeStr, " Menu", WIDTH - (int)strlen(modeStr) - (int)strlen(" Menu"), "Press 'm' to change mode");
        break;
    case 3:
        printf("%s (%s)%*s\n", modeStr, degreeStr, WIDTH - (int)strlen(modeStr) - (int)strlen(degreeStr) - 3, "Press 'm' to change mode");
        printf("%*s\n", WIDTH, "Press 'shift + m' for menu");
        break;
    default:
        printf("%s\n", "Main Menu");
        break;
    }

    drawLine();
}

void mainMenu()
{
    while (1)
    {
        drawTitle(0);
        printf("1. Computation\n");
        printf("2. Statistics\n");
        printf("3. Matrix\n");
        printf("4. Equation\n");
        printf("5. Graph\n");
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
        case MODE_COMPUTATION:
            mode = MODE_COMPUTATION;
            computationMenu();
            break;
        case MODE_STATISTICS:
            mode = MODE_STATISTICS;
            statisticsMenu();
            break;
        case MODE_MATRIX:
            mode = MODE_MATRIX;
            matrixMenu();
            break;
        case MODE_EQUATION:
            mode = MODE_EQUATION;
            equationMenu();
            break;
        case MODE_GRAPH:
            mode = MODE_GRAPH;
            graphing();
            break;
        case MODE_EXIT:
            mode = MODE_EXIT;
            clearScreen();
            printf("Exiting calculator. Goodbye!\n");
            exit(0);
        default:
            mode = MODE_COMPUTATION;
            computationMenu();
            break;
        }
    }
}
void modeMenu()
{
    switch (mode)
    {
    case MODE_COMPUTATION:
        computationMenu();
        break;
    case MODE_STATISTICS:
        statisticsMenu();
        break;
    case MODE_MATRIX:
        matrixMenu();
        break;
    case MODE_EQUATION:
        equationMenu();
        break;
    case MODE_GRAPH:
        graphing();
        break;
    default:
        computationMenu();
        break;
    }
}