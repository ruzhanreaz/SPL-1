#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "equation.h"

double **matrix;

void showEqnMenu()
{
    // int temp = 1;
    clearScreen();
    int choice = 0;
    // char *result;

    while (choice < 1 || choice > 4)
    {
        printf("Equation\n");
        printLine();
        printf("1: aₙX + bₙY = cₙ\n");
        printf("2: aₙX + bₙY + cₙZ = dₙ\n");
        printf("3: aₙX² + bₙX + cₙ = 0\n");
        printf("4: aX³ + bX² + cX + d = 0\n");

        printLine();
        printf("Enter your choice (1-4): ");

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
            linEqn2();
            break;

        case 2:
            linEqn3();
            break;

        case 3:

            break;

        case 4:

            break;
        default:
            break;
        }
    }
}
int equation(char *mode)
{
    clearScreen();
    drawTitle(mode);
    showEqnMenu();
    char str[100];
    while (1)
    {
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = '\0';
        if (str[0] == 'm' || str[0] == 'M')
            return 1;
        else if (str[0] == 'q' || str[0] == 'Q')
            return 0;
    }
}
void linEqn2()
{
    int row = 2;
    int col = 3;
    drawTitle("Equation");
    fillMatrix(row, col);
    solveLinEqn2();
}

void linEqn3()
{
    int row = 3;
    int col = 4;
    drawTitle("Equation");
    fillMatrix(row, col);
    solveLinEqn3();
}
void fillMatrix(int row, int col)
{
    matrix = malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++)
    {
        matrix[i] = malloc(col * sizeof(double));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = 0.0;
        }
    }

    int highlight_row = 0;
    int highlight_col = 0;

    while (1)
    {
        drawTitle("Equation");
        displayMatrix(row, col, highlight_row, highlight_col);
        if (highlight_row == 0)
        {
            if (highlight_col == 0)
            {
                printf("a₁: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 1)
            {
                printf("b₁: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 2)
            {
                printf("c₁: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 3)
            {
                printf("d₁: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
        }
        else if (highlight_row == 1)
        {
            if (highlight_col == 0)
            {
                printf("a₂: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 1)
            {
                printf("b₂: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 2)
            {
                printf("c₂: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 3)
            {
                printf("d₂: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
        }
        else if (highlight_row == 2)
        {
            if (highlight_col == 0)
            {
                printf("a₃: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 1)
            {
                printf("b₃: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 2)
            {
                printf("c₃: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
            else if (highlight_col == 3)
            {
                printf("d₃: ");
                scanf("%lf", &matrix[highlight_row][highlight_col]);
            }
        }
        highlight_col++;
        if (highlight_col == col)
        {
            highlight_col = 0;
            highlight_row++;
            if (highlight_row == row)
            {
                break;
            }
        }
    }
    displayMatrix(row, col, -1, -1);
    // printf("\nMatrix filled successfully!\n");
    printLine();
}
void displayMatrix(int row, int col, int highlight_row, int highlight_col)
{
    clearScreen();
    drawTitle("Equation");
    // printf("%*c%*c%*c\n", 10, 'a', 10, 'b', 10, 'c');
    for (int i = 0; i < col; i++)
    {
        if (i == 0)
            printf("%*c", 13, 'a');
        else if (i == 1)
            printf("%*c", 12, 'b');
        else if (i == 2)
            printf("%*c", 12, 'c');
        else if (i == 3)
            printf("%*c", 12, 'd');
    }
    printf("\n");
    for (int i = 0; i < row; i++)
    {
        printf("%d ", i + 1);
        for (int j = 0; j < col; j++)
        {
            if (i == highlight_row && j == highlight_col)
            {

                double num = matrix[i][j];
                if (num == (long)num)
                {
                    printf("\033[41;97m %10ld \033[0m", (long)num);
                    // printLine();
                }
                else
                {
                    double fractional_part = num - (int)num;
                    int decimal_places = 0;

                    while (fractional_part != (int)fractional_part && decimal_places < 10)
                    {
                        fractional_part *= 10;
                        decimal_places++;
                    }

                    printf("\033[41;97m %10.*lf \033[0m", decimal_places, num);
                    // printLine();
                }
            }
            else
            {
                double num = matrix[i][j];
                if (num == (long)num)
                    printf(" %10ld ", (long)num);
                else
                {
                    double fractional_part = num - (int)num;
                    int decimal_places = 0;

                    while (fractional_part != (int)fractional_part && decimal_places < 10)
                    {
                        fractional_part *= 10;
                        decimal_places++;
                    }

                    printf(" %10.*lf ", decimal_places, num);
                }
            }
        }
        printf("\n");
    }
    printLine();
}
void solveLinEqn2()
{
    double a1 = matrix[0][0];
    double b1 = matrix[0][1];
    double c1 = matrix[0][2];
    double a2 = matrix[1][0];
    double b2 = matrix[1][1];
    double c2 = matrix[1][2];

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        printf("The system has no unique solution.\n");
    }
    else
    {
        double x = (c1 * b2 - c2 * b1) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        printf("The solution is: X = %lf, Y = %lf\n", x, y);
    }
    printLine();
}

void solveLinEqn3()
{
    double a1 = matrix[0][0];
    double b1 = matrix[0][1];
    double c1 = matrix[0][2];
    double d1 = matrix[0][3];
    double a2 = matrix[1][0];
    double b2 = matrix[1][1];
    double c2 = matrix[1][2];
    double d2 = matrix[1][3];
    double a3 = matrix[2][0];
    double b3 = matrix[2][1];
    double c3 = matrix[2][2];
    double d3 = matrix[2][3];

    double determinant = a1 * (b2 * c3 - c2 * b3) - b1 * (a2 * c3 - c2 * a3) + c1 * (a2 * b3 - b2 * a3);

    if (determinant == 0)
    {
        printf("The system has no unique solution.\n");
    }
    else
    {
        double x = (d1 * (b2 * c3 - c2 * b3) - b1 * (d2 * c3 - c2 * d3) + c1 * (d2 * b3 - b2 * d3)) / determinant;
        double y = (a1 * (d2 * c3 - c2 * d3) - d1 * (a2 * c3 - c2 * a3) + c1 * (a2 * d3 - d2 * a3)) / determinant;
        double z = (a1 * (b2 * d3 - d2 * b3) - b1 * (a2 * d3 - d2 * a3) + d1 * (a2 * b3 - b2 * a3)) / determinant;
        printf("The solution is: X = %lf, Y = %lf, Z = %lf\n", x, y, z);
    }
    printLine();
}