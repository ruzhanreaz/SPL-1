#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "normal.h"
#include "menu.h"

int main()
{
    int isRunning = 1;
    while (isRunning)
    {
        isRunning = showMenu();
    }
    clearScreen();
    return 0;
}