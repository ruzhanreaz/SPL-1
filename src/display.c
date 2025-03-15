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
    clearScreen();
    char mode[20];
    char degree[10];

    switch (modeNum)
    {
    case 1:
        strcpy(mode, "Computation");
        break;
    case 2:
        strcpy(mode, "Statistics");
        break;
    case 3:
        strcpy(mode, "Graphing");
        break;
    case 4:
        strcpy(mode, "Equation");
        break;
    case 5:
        strcpy(mode, "Matrix");
        break;
    default:
        strcpy(mode, "Computation");
    }

    if (degreeMode)
    {
        strcpy(degree, "Degree");
    }
    else
    {
        strcpy(degree, "Radian");
    }

    if (titleType == 0)
    {
        printf("%s%*s\n", "Main Menu", WIDTH - (int)strlen("Main Menu"), "Press 'q' to quit");
    }

    else if (titleType == 1)
    {
        printf("%s%s%*s\n", mode, " Menu", WIDTH - (int)strlen(mode) - (int)strlen(" Menu"), "Press 'm' to change mode");
        printf("%*s\n", WIDTH, "Press 'q' to quit");
    }

    else if (titleType == 2)
    {
        printf("%s (%s)%*s\n", mode, degree, WIDTH - (int)strlen(mode) - (int)strlen(degree) - 3, "Press 'm' to change mode");
        printf("%*s\n", WIDTH, "Press 'shift + m' for menu");
        printf("%*s\n", WIDTH, "Press 'q' to quit");
    }
    drawLine();
}