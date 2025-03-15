#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void getStrInput(char *str)
{
    fgets(str, MAX_INPUT_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    int strLength = strlen(str);
    if (strLength == 0)
    {
        printf("Invalid input. Please try again.\n");
        getStrInput(str);
    }
    else if (strLength == 1 && (str[0] == 'q' || str[0] == 'Q'))
    {
        clearScreen();
        printf("Exiting program...\n");
        exit(0);
    }
    else if (strLength == 1 && (str[0] == 'm') && modeNum != 0)
    {
        showMainMenu();
    }
    else if (strLength == 1 && (str[0] == 'M') && modeNum != 0)
    {
        showModeMenu();
    }
}
void outputString(char *str)
{
    printf("%*s\n", WIDTH, modifyDouble(str));
    drawLine();
}
char *modifyDouble(char *str)
{
    double num = atof(str);

    if (scientificMode)
        snprintf(str, 100, "%.*e", precision, num);
    else
    {
        snprintf(str, 100, "%.*f", precision, num);

        char *p = str + strlen(str) - 1;
        while (*p == '0' && p > str)
            p--;

        if (*p == '.')
            p--;
        *(p + 1) = '\0';

        if (strchr(str, '.') && atof(str) == (int)atof(str))
        {
            *strchr(str, '.') = '\0';
        }
    }

    return str;
}
