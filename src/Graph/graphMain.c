#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "header.h"
#include "graph.h"

void graphing()
{
    closeGraphWindow(); 

    while (1)
    {
        drawTitle(1);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Plot\n");
        printf("4. Clear\n");
        printf("5. Clear all\n");
        printf("6. Change x range\n");
        printf("7. Back\n");
        printf("8. Exit\n");
        drawLine();
        printf("Select an option: ");
        char choice[10];
        getStrInput(choice);
        checkInput(choice);
        
        switch (atoi(choice))
        {
        case 1:
            degreeMode = 1;
            break;
        case 2:
            degreeMode = 0;
            break;
        case 3:
            if (plot() != 0)
                continue;
            break;
        case 4:
            clearAGraph();
            break;
        case 5:
            clearAllGraph();
            break;
        case 6:
            changeXRange();
            break;
        case 7:
            return;
        case 8:
            closeGraphWindow();
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
            SDL_Delay(1000);
            break;
        }
    }
}