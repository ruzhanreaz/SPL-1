#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    else if (strLength == 1 && (str[0] == 'm'))
    {
        showMenu();
    }
}