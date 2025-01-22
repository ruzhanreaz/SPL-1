#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "normal.h"
#include "complex.h"
#include "equation.h"

char mode[16] = "Normal";
int width = 80;

void clearScreen(void)
{
    printf("\033[H\033[J");
}
void drawTitle(char *mode)
{
    char degreeModeStr[10];
    if (isDegreeModeEnabled())
    {
        strcpy(degreeModeStr, "Degree");
    }
    else
    {
        strcpy(degreeModeStr, "Radian");
    }

    printf("%s (%s)%*s\n", mode, degreeModeStr, width - (int)strlen(mode) - (int)strlen(degreeModeStr) - 3, "Press 'm' for Menu");
    printf("%*s\n", width, "'q' to quit");
    printLine();
}
void printLine(void)
{
    for (int i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("\n");
}

int showMenu(void)
{
    int temp = 1;
    clearScreen();
    int choice = 0;

    while (choice < 1 || choice > 9)
    {
        clearScreen();
        printf("\nMenu\n");
        printLine();
        printf("%-15s%-15s\n", "1. Normal", "2. Complex");
        printf("%-15s%-15s\n", "3. STAT", "4. Base-n");
        printf("%-15s%-15s\n", "5. Equation", "6. Matrix");
        printf("%-15s%-15s\n", "7. Graph", "8. Vector");
        printf("%-15s\n", "9. Toggle Degree Mode");
        printLine();
        printf("Enter your choice (%d-%d): ", 1, 9);

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
            continue;
        }

        getchar();

        switch (choice)
        {
        case 1:
            strncpy(mode, "Normal", 15);
            temp = normal(mode);
            break;
        case 2:
            strncpy(mode, "Complex", 15);
            // temp = complex(mode);
            break;
        case 3:
            strncpy(mode, "STAT", 15);
            // temp = stat(mode);
            break;
        case 4:
            strncpy(mode, "Base-n", 15);
            // temp = base_n(mode);
            break;
        case 5:
            strncpy(mode, "Equation", 15);
            temp = equation(mode);
            break;
        case 6:
            strncpy(mode, "Matrix", 15);
            // temp = matrix(mode);
            break;
        case 7:
            strncpy(mode, "Graph", 15);
            // temp = graph(mode);
            break;
        case 8:
            strncpy(mode, "Vector", 15);
            // temp = vector(mode);
            break;
        case 9:
            if (isDegreeModeEnabled())
            {
                disableDegreeMode();
            }
            else
            {
                enableDegreeMode();
            }
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return temp;
}