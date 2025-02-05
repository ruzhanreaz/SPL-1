#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int degreeMode = 0;

void showMenu()
{

    int choice = 0;

    while (choice < 1 || choice > 10)
    {
        drawTitle("Menu", -1);
        const char *menuItems[] = {
            "1. Computation", "2. STAT", "3. Equation", "4. Matrix",
            "5. Graph", "6. Toggle Degree Mode"};

        for (int i = 0; i < 6; i += 2)
        {
            if (i + 1 < 6)
            {
                printf("%-15s%-15s\n", menuItems[i], menuItems[i + 1]);
            }
            else
            {
                printf("%-15s\n", menuItems[i]);
            }
        }
        drawLine();
        printf("Enter your choice(1-6): ");
        char input[10];
        if (scanf("%9s", input) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
            continue;
        }
        if (input[0] == 'q' || input[0] == 'Q')
        {
            clearScreen();
            printf("Exiting program...\n");
            exit(0);
        }
        choice = atoi(input);
    }
    getchar();
    switchMode(choice);
}

void switchMode(int choice)
{
    switch (choice)
    {
    case 1:
        computation(degreeMode);
        break;
    case 2:
        break;
    case 3:
        equation(degreeMode);
        break;
    case 4:
        matrix(degreeMode);
        break;
    case 5:
        break;
    case 6:
        degreeMode = !degreeMode;
        showMenu();
        break;
    default:
        break;
    }
}
