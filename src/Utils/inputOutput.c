#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void getStrInput(char *str)
{
    fgets(str, MAX_INPUT_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
}
void checkInput(char *str)
{
    int strLength = strlen(str);
    char p[MAX_INPUT_SIZE];
    strcpy(p, str);
    if (strLength == 0)
    {
        printf("Invalid input. Please try again.\n");
    }
    else if (strLength == 1 && p[0] == 'm')
    {
        mainMenu();
    }
    else if (strLength == 1 && p[0] == 'M')
    {
        modeMenu();
    }
}
void outputString(char *str)
{
    printf("%*s\n", WIDTH, modifyDoubleStr(str));
    drawLine();
}
char *modifyDoubleStr(char *str)
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
char *modifyDouble(double num)
{
    static char str[100];
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
