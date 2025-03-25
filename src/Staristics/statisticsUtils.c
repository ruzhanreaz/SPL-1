#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

int numOfColumn = 0;
DataColumn *dataColumns = NULL;
char **titleNameList = NULL;

Point *points = NULL;
int numOfPoints = 0;

int isStatOperand(char *str)
{
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(str, dataColumns[i].name) == 0)
        {
            return 1;
        }
    }
    return 0;
}
void setData()
{
    drawTitle(3);
    printf("Enter the name of the column: ");
    char titleName[50];
    getStrInput(titleName);
    checkInput(titleName);
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName, dataColumns[i].name) == 0)
        {
            printf("Column already exists\n");
            printf("Press Enter to continue...");
            while (getchar() != '\n')
                ;
            return;
        }
    }
    if (numOfColumn == 0)
    {
        dataColumns = (DataColumn *)malloc(sizeof(DataColumn));
    }
    else
    {
        dataColumns = (DataColumn *)realloc(dataColumns, (numOfColumn + 1) * sizeof(DataColumn));
    }
    strcpy(dataColumns[numOfColumn].name, titleName);
    dataColumns[numOfColumn].numOfData = 0;
    dataColumns[numOfColumn].data = (Data *)malloc(sizeof(Data));

    printf("Enter the data (comma separated): ");
    char data[256];
    getStrInput(data);
    checkInput(data);
    char *token = strtok(data, ",");
    while (token != NULL)
    {
        if (dataColumns[numOfColumn].numOfData == 0)
        {
            dataColumns[numOfColumn].data = (Data *)malloc(sizeof(Data));
        }
        else
        {
            dataColumns[numOfColumn].data = (Data *)realloc(dataColumns[numOfColumn].data, (dataColumns[numOfColumn].numOfData + 1) * sizeof(Data));
        }
        dataColumns[numOfColumn].data[dataColumns[numOfColumn].numOfData].data = (char *)malloc(strlen(token) + 1);
        strcpy(dataColumns[numOfColumn].data[dataColumns[numOfColumn].numOfData].data, token);
        dataColumns[numOfColumn].numOfData++;
        token = strtok(NULL, ",");
    }
    numOfColumn++;
    showData();
}
void showData()
{
    drawTitle(3);
    for (int i = 0; i < numOfColumn; i++)
    {
        printf("%s\t", dataColumns[i].name);
    }
    printf("\n");

    int maxRows = 0;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (dataColumns[i].numOfData > maxRows)
        {
            maxRows = dataColumns[i].numOfData;
        }
    }
    for (int j = 0; j < maxRows; j++)
    {
        for (int i = 0; i < numOfColumn; i++)
        {
            if (j < dataColumns[i].numOfData)
            {
                printf("%s\t", dataColumns[i].data[j].data);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
    drawLine();
    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;
}

void clearAllData()
{
    for (int i = 0; i < numOfColumn; i++)
    {
        for (int j = 0; j < dataColumns[i].numOfData; j++)
        {
            free(dataColumns[i].data[j].data);
        }
        free(dataColumns[i].data);
    }
    free(dataColumns);
    numOfColumn = 0;
}

void clearColumn()
{
    drawTitle(3);
    showData();
    printf("Enter the name of the column to clear: ");
    char titleName[50];
    getStrInput(titleName);
    checkInput(titleName);
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Column not found\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        free(dataColumns[index].data[i].data);
    }
    free(dataColumns[index].data);
    for (int i = index; i < numOfColumn - 1; i++)
    {
        dataColumns[i] = dataColumns[i + 1];
    }
    numOfColumn--;
    showData();
}

void sort(char *titleName)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Column not found\n");
        return;
    }
    for (int i = 0; i < dataColumns[index].numOfData - 1; i++)
    {
        for (int j = 0; j < dataColumns[index].numOfData - i - 1; j++)
        {
            if (atof(dataColumns[index].data[j].data) > atof(dataColumns[index].data[j + 1].data))
            {
                for (int k = 0; k < numOfColumn; k++)
                {
                    char *temp = dataColumns[k].data[j].data;
                    dataColumns[k].data[j].data = dataColumns[k].data[j + 1].data;
                    dataColumns[k].data[j + 1].data = temp;
                }
            }
        }
    }
}

void sortData()
{
    drawTitle(3);
    showData();
    printf("Enter the name of the column to sort: ");
    char titleName[50];
    getStrInput(titleName);
    checkInput(titleName);
    sort(titleName);
    showData();
}

void regression()
{
    drawTitle(3);
    printf("Enter the name of the column for x: ");
    char xTitleName[50];
    getStrInput(xTitleName);
    checkInput(xTitleName);
    int xIndex = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(xTitleName, dataColumns[i].name) == 0)
        {
            xIndex = i;
            break;
        }
    }
    if (xIndex == -1)
    {
        printf("Column not found\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    printf("Enter the name of the column for y: ");
    char yTitleName[50];
    getStrInput(yTitleName);
    checkInput(yTitleName);
    int yIndex = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(yTitleName, dataColumns[i].name) == 0)
        {
            yIndex = i;
            break;
        }
    }
    if (yIndex == -1)
    {
        printf("Column not found\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    if (dataColumns[xIndex].numOfData != dataColumns[yIndex].numOfData)
    {
        printf("Number of data in x and y are not equal\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    double *x = (double *)malloc(dataColumns[xIndex].numOfData * sizeof(double));
    double *y = (double *)malloc(dataColumns[yIndex].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[xIndex].numOfData; i++)
    {
        x[i] = atof(dataColumns[xIndex].data[i].data);
        y[i] = atof(dataColumns[yIndex].data[i].data);
    }
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;
    double sumY2 = 0;
    for (int i = 0; i < dataColumns[xIndex].numOfData; i++)
    {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
        sumY2 += y[i] * y[i];
    }
    double n = dataColumns[xIndex].numOfData;
    double a = (sumY * sumX2 - sumX * sumXY) / (n * sumX2 - sumX * sumX);
    double b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double r = (n * sumXY - sumX * sumY) / sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));
    if (b < 0 && a < 0)
    {
        printf("y = %fx %f\n", b, a);
    }
    else if (b < 0 && a >= 0)
    {
        printf("y = %fx + %f\n", b, a);
    }
    else if (b >= 0 && a < 0)
    {
        printf("y = %fx %f\n", b, a);
    }
    else
    {
        printf("y = %fx + %f\n", b, a);
    }
    printf("r = %f\n", r);

    for (int i = 0; i < dataColumns[xIndex].numOfData; i++)
    {
        addPoint(x[i], y[i]);
    }

    //drawALinearEquation(b, a);
    free(x);
    free(y);
    printf("Press Enter to continue...");

    while (getchar() != '\n')
        ;
    // clearAllGraph();
    // closeGraphWindow();
    regMode = 0;
}

void addPoint(double x, double y)
{
    if (numOfPoints == 0)
    {
        points = (Point *)malloc(sizeof(Point));
    }
    else
    {
        points = (Point *)realloc(points, (numOfPoints + 1) * sizeof(Point));
    }
    points[numOfPoints].x = x;
    points[numOfPoints].y = y;
    numOfPoints++;
}