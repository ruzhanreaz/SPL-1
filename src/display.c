#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"

int width = 80;

void clearScreen()
{
    printf("\033[H\033[J");
}

void drawLine()
{
    for (int i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("\n");
}

void drawTitle(char *mode, int degOrRad)
{
    clearScreen();
    if (degOrRad == 1)
    {
        printf("%s (%s)%*s\n", mode, "Degree", width - (int)strlen(mode) - (int)strlen("Degree") - 3, "Press 'm' to change mode");
        printf("%*s\n", width, "Press 'shift + m' for menu");
        printf("%*s\n", width, "Press 'q' to quit");
        drawLine();
    }
    else if (degOrRad == 0)
    {
        printf("%s (%s)%*s\n", mode, "Radian", width - (int)strlen(mode) - (int)strlen("Radian") - 3, "Press 'm' to change mode");
        printf("%*s\n", width, "Press 'shift + m' for menu");
        printf("%*s\n", width, "Press 'q' to quit");
        drawLine();
    }
    else if (degOrRad == -1)
    {
        printf("%s%*s\n", mode, width - (int)strlen(mode), "Press 'q' to quit");
        drawLine();
    }
    else
    {
        printf("%s%*s\n", mode, width - (int)strlen(mode), "Press 'm' to change mode");
        printf("%*s\n", width, "Press 'q' to quit");
        drawLine();
    }
}

void outputString(char *str)
{
    double num = atof(str);
    if (num - (long)num == 0)
    {
        printf("%*ld\n", width, (long)num);
    }
    else
    {
        printf("%*s\n", width, str);
    }
    drawLine();
}