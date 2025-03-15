#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void showMainMenu()
{

    while (1)
    {
        drawTitle(0);
        printf("1. computation\n");
        printf("2. Statistics\n");
        printf("3. Graphing\n");
        printf("4. Equation\n");
        printf("5. Matrix\n");
        // printf("6. Back\n");
        drawLine();
        printf("Enter your choice: ");
        char choice[10];
        getStrInput(choice);
        if (strcmp(choice, "1") == 0)
        {
            modeNum = 1;
            computation();
            break;
        }
        else if (strcmp(choice, "2") == 0)
        {
            modeNum = 2;
            statistics();
            break;
        }
        else if (strcmp(choice, "3") == 0)
        {
            modeNum = 3;
            graphing();
            break;
        }
        else if (strcmp(choice, "4") == 0)
        {
            modeNum = 4;
            equation();
            break;
        }
        else if (strcmp(choice, "5") == 0)
        {
            modeNum = 5;
            matrix();
            break;
        }
        // else if (strcmp(choice, "6") == 0)
        // {

        //     break;
        //      }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void showModeMenu()
{
    if (modeNum == 1)
    {
        showComputationMenu();
    }
    else if (modeNum == 2)
    {
        showStatisticsMenu();
    }
    else if (modeNum == 3)
    {
        showGraphingMenu();
    }
    else if (modeNum == 4)
    {
        showEquationMenu();
    }
    else if (modeNum == 5)
    {
        showMatrixMenu();
    }
}

void showComputationMenu()
{
    while (1)
    {
        drawTitle(1);
        printf("1.Degree\n");
        printf("2.Radian\n");
        printf("3.Scientific\n");
        printf("4.Normal\n");
        // printf("5.Back\n");

        drawLine();
        printf("Enter your choice: ");
        char choice[10];
        getStrInput(choice);
        if (strcmp(choice, "1") == 0)
        {
            degreeMode = 1;
            computation();
            break;
        }
        else if (strcmp(choice, "2") == 0)
        {
            degreeMode = 0;
            computation();
            break;
        }
        else if (strcmp(choice, "3") == 0)
        {
            scientificMode = 1;
            printf("Enter precision(1~10): ");
            int p;
            scanf("%d", &p);
            if (p < 1 || p > 10)
            {
                printf("Invalid input. Please try again.\n");
                continue;
            }
            precision = p;
            getchar();
            computation();
            break;
        }
        else if (strcmp(choice, "4") == 0)
        {
            scientificMode = 0;
            printf("Enter precision(1~10): ");
            int p;
            scanf("%d", &p);
            if (p < 1 || p > 10)
            {
                printf("Invalid input. Please try again.\n");
                continue;
            }
            precision = p;
            getchar();
            computation();
            break;
        }
        // else if (strcmp(choice, "5") == 0)
        // {
        //     break;
        // }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
}
void showStatisticsMenu()
{
    while (1)
    {
        drawTitle(1);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Set Data\n");
        printf("4. Show Data\n");
        // printf("5. Regression\n");
        // printf("6. Plot\n");
        printf("7. Clear a Column\n");
        printf("8. Clear All Data\n");
        // printf("9. Back\n");
        drawLine();
        printf("Enter your choice: ");
        char choice[10];
        getStrInput(choice);
        if (strcmp(choice, "1") == 0)
        {
            degreeMode = 1;
            statistics();
            break;
        }
        else if (strcmp(choice, "2") == 0)
        {
            degreeMode = 0;
            statistics();
            break;
        }
        else if (strcmp(choice, "3") == 0)
        {
            setData();
            statistics();
            break;
        }
        else if (strcmp(choice, "4") == 0)
        {
            showData();
            statistics();
            break;
        }
        else if (strcmp(choice, "5") == 0)
        {
            // regression();
            statistics();
            break;
        }
        else if (strcmp(choice, "6") == 0)
        {
            // plot();
            statistics();
            break;
        }
        else if (strcmp(choice, "7") == 0)
        {
            clearColumn();
            statistics();
            break;
        }
        else if (strcmp(choice, "8") == 0)
        {
            clearAllData();
            statistics();
            break;
        }
        // else if (strcmp(choice, "9") == 0)
        // {
        //     break;
        // }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void showGraphingMenu()
{
    int valid = 0;
    while (1)
    {
        drawTitle(1);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Plot\n");
        printf("4. Clear\n");
        // printf("5. Back\n");
        drawLine();

        printf("Enter your choice: ");
        char choice[10];
        getStrInput(choice);
        if (strcmp(choice, "1") == 0)
        {
            degreeMode = 1;
            graphing();
            break;
        }
        else if (strcmp(choice, "2") == 0)
        {
            degreeMode = 0;
            graphing();
            break;
        }
        else if (strcmp(choice, "3") == 0)
        {
            valid = plot();
            if (valid == 0)
                break;
            else
                continue;
            break;
        }
        else if (strcmp(choice, "4") == 0)
        {
            clearGraph();
            valid = plot();
            if (valid == 0)
                break;
            else
                continue;

            break;
        }
        // else if (strcmp(choice, "5") == 0)
        // {
        //     break;
        // }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void showEquationMenu()
{
    while (1)
    {
        drawTitle(1);
        printf("1. Degree\n");
        printf("2. Radian\n");
        printf("3. Solve\n");
        printf("4. Clear\n");
        // printf("5. Back\n");
        drawLine();
        printf("Enter your choice: ");
        char choice[10];
        getStrInput(choice);
        if (strcmp(choice, "1") == 0)
        {
            degreeMode = 1;
            equation();
            break;
        }
        else if (strcmp(choice, "2") == 0)
        {
            degreeMode = 0;
            equation();
            break;
        }
        else if (strcmp(choice, "3") == 0)
        {
            equation();
            break;
        }
        else if (strcmp(choice, "4") == 0)
        {
            // clearGraph();
            break;
        }
        // else if (strcmp(choice, "5") == 0)
        // {
        //     break;
        // }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void showMatrixMenu()
{
    while (1)
    {
        drawTitle(1);
        printf("1. Set Matrix\n");
        printf("2. Show a Matrix\n");
        printf("3. Show All Matrix\n");
        printf("4. A=LU\n");
        // printf("5. A=QR\n");
        printf("6. Clear a Matrix\n");
        printf("7. Clear All Matrix\n");
        // printf("8. Back\n");
        drawLine();
        printf("Enter your choice: ");
        char choice[10];
        getStrInput(choice);

        if (strcmp(choice, "1") == 0)
        {
            setMatrix();
            break;
        }
        else if (strcmp(choice, "2") == 0)
        {
            showAMatrix();
            matrix();
            break;
        }
        else if (strcmp(choice, "3") == 0)
        {
            showAllMatrix();
            matrix();
            break;
        }
        else if (strcmp(choice, "4") == 0)
        {
            luMode = 1;
            lu();
            break;
        }
        else if (strcmp(choice, "5") == 0)
        {
            // qr();
            break;
        }
        else if (strcmp(choice, "6") == 0)
        {
            clearAMatrix();
            matrix();
            break;
        }
        else if (strcmp(choice, "7") == 0)
        {
            clearAllMatrix();
            matrix();
            break;
        }
        // else if (strcmp(choice, "8") == 0)
        // {
        //     break;
        // }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
}