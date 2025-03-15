#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

typedef struct
{
    char *data;
} Data;

typedef struct
{
    char name[50];
    Data *data;
    int numOfData;
} DataColumn;

int numOfColumn = 0;
DataColumn *dataColumns;
char **name;

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
void statistics()
{
    drawTitle(2);
    char expression[MAX_INPUT_SIZE];

    name = (char **)malloc(numOfColumn * sizeof(char *));
    for (int i = 0; i < numOfColumn; i++)
    {
        name[i] = dataColumns[i].name;
    }
    while (1)
    {
        getStrInput(expression);
        Queue *infixQueue = createQueue();
        int isValid = 1;
        isValid = tokenize(infixQueue, expression);
        if (isQueueEmpty(infixQueue) || !isValid)
        {
            freeQueue(infixQueue);
            continue;
        }
        Queue *postfixQueue = createQueue();
        infixToPostfix(infixQueue, postfixQueue);
        char *result = (char *)malloc(100);
        postfixEvaluateStat(postfixQueue, result);
        freeQueue(infixQueue);
        freeQueue(postfixQueue);
        outputString(result);
        free(result);
    }
}

void setData()
{
    drawTitle(2);
    printf("Enter the name of the column: ");
    char name[50];
    if (scanf("%49[^\n]", name) != 1)
    {
        while (getchar() != '\n')
            ;
        return;
    }
    getchar();
    if (numOfColumn == 0)
    {
        dataColumns = (DataColumn *)malloc(sizeof(DataColumn));
    }
    else
    {
        dataColumns = (DataColumn *)realloc(dataColumns, (numOfColumn + 1) * sizeof(DataColumn));
    }
    strcpy(dataColumns[numOfColumn].name, name);
    dataColumns[numOfColumn].numOfData = 0;
    dataColumns[numOfColumn].data = (Data *)malloc(sizeof(Data));

    printf("Enter the data (comma separated): ");
    char data[256];

    if (scanf("%255[^\n]", data) != 1)
    {
        while (getchar() != '\n')
            ;
        return;
    }
    getchar();

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
    drawTitle(2);
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
    getchar();
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
    drawTitle(2);
    showData();
    printf("Enter the name of the column to clear: ");
    char name[50];
    if (scanf("%49[^\n]", name) != 1)
    {
        while (getchar() != '\n')
            ;
        return;
    }
    getchar();
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Column not found\n");
        getchar();
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
    getchar();
}

void sort(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
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

double sum(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Column not found\n");
        return 0;
    }
    double sum = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        sum += atof(dataColumns[index].data[i].data);
    }
    return sum;
}

double mean(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double sum = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        sum += atof(dataColumns[index].data[i].data);
    }
    return sum / dataColumns[index].numOfData;
}

double median(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double median = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    if (dataColumns[index].numOfData % 2 == 0)
    {
        median = (data[dataColumns[index].numOfData / 2 - 1] + data[dataColumns[index].numOfData / 2]) / 2;
    }
    else
    {
        median = data[dataColumns[index].numOfData / 2];
    }
    free(data);
    return median;
}
double mode(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double mode = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    int maxCount = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        int count = 0;
        for (int j = 0; j < dataColumns[index].numOfData; j++)
        {
            if (data[i] == data[j])
            {
                count++;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            mode = data[i];
        }
    }
    free(data);
    return mode;
}

double range(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double range = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    double min = data[0];
    double max = data[0];
    for (int i = 1; i < dataColumns[index].numOfData; i++)
    {
        if (data[i] < min)
        {
            min = data[i];
        }
        if (data[i] > max)
        {
            max = data[i];
        }
    }
    range = max - min;
    free(data);
    return range;
}

double pvar(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double var = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    double mean = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        mean += data[i];
    }
    mean /= dataColumns[index].numOfData;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        var += pow(data[i] - mean, 2);
    }
    var /= dataColumns[index].numOfData;
    free(data);
    return var;
}

double svar(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double var = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    double mean = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        mean += data[i];
    }
    mean /= dataColumns[index].numOfData;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        var += pow(data[i] - mean, 2);
    }
    var /= dataColumns[index].numOfData - 1;
    free(data);
    return var;
}

double pstd(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double std = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    double mean = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        mean += data[i];
    }
    mean /= dataColumns[index].numOfData;
    double var = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        var += pow(data[i] - mean, 2);
    }
    var /= dataColumns[index].numOfData;
    std = sqrt(var);
    free(data);
    return std;
}

double sstd(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double std = 0;
    double *data = (double *)malloc(dataColumns[index].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        data[i] = atof(dataColumns[index].data[i].data);
    }
    double mean = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        mean += data[i];
    }
    mean /= dataColumns[index].numOfData;
    double var = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        var += pow(data[i] - mean, 2);
    }
    var /= dataColumns[index].numOfData - 1;
    std = sqrt(var);
    free(data);
    return std;
}

double cov(char *name1, char *name2)
{
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name1, dataColumns[i].name) == 0)
        {
            index1 = i;
        }
        if (strcmp(name2, dataColumns[i].name) == 0)
        {
            index2 = i;
        }
    }
    double cov = 0;
    double *data1 = (double *)malloc(dataColumns[index1].numOfData * sizeof(double));
    double *data2 = (double *)malloc(dataColumns[index2].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        data1[i] = atof(dataColumns[index1].data[i].data);
    }
    for (int i = 0; i < dataColumns[index2].numOfData; i++)
    {
        data2[i] = atof(dataColumns[index2].data[i].data);
    }
    double mean1 = 0;
    double mean2 = 0;
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        mean1 += data1[i];
    }
    mean1 /= dataColumns[index1].numOfData;
    for (int i = 0; i < dataColumns[index2].numOfData; i++)
    {
        mean2 += data2[i];
    }
    mean2 /= dataColumns[index2].numOfData;
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        cov += (data1[i] - mean1) * (data2[i] - mean2);
    }
    cov /= dataColumns[index1].numOfData;
    free(data1);
    free(data2);
    return cov;
}

double corr(char *name1, char *name2)
{
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name1, dataColumns[i].name) == 0)
        {
            index1 = i;
        }
        if (strcmp(name2, dataColumns[i].name) == 0)
        {
            index2 = i;
        }
    }
    double corr = 0;
    double *data1 = (double *)malloc(dataColumns[index1].numOfData * sizeof(double));
    double *data2 = (double *)malloc(dataColumns[index2].numOfData * sizeof(double));
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        data1[i] = atof(dataColumns[index1].data[i].data);
    }
    for (int i = 0; i < dataColumns[index2].numOfData; i++)
    {
        data2[i] = atof(dataColumns[index2].data[i].data);
    }
    double mean1 = 0;
    double mean2 = 0;
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        mean1 += data1[i];
    }
    mean1 /= dataColumns[index1].numOfData;
    for (int i = 0; i < dataColumns[index2].numOfData; i++)
    {
        mean2 += data2[i];
    }
    mean2 /= dataColumns[index2].numOfData;
    double cov = 0;
    double var1 = 0;
    double var2 = 0;
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        cov += (data1[i] - mean1) * (data2[i] - mean2);
        var1 += pow(data1[i] - mean1, 2);
        var2 += pow(data2[i] - mean2, 2);
    }
    cov /= dataColumns[index1].numOfData;
    var1 /= dataColumns[index1].numOfData;
    var2 /= dataColumns[index2].numOfData;
    corr = cov / sqrt(var1 * var2);
    free(data1);
    free(data2);
    return corr;
}

double max(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double max = atof(dataColumns[index].data[0].data);
    for (int i = 1; i < dataColumns[index].numOfData; i++)
    {
        if (atof(dataColumns[index].data[i].data) > max)
        {
            max = atof(dataColumns[index].data[i].data);
        }
    }
    return max;
}

double min(char *name)
{
    int index = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(name, dataColumns[i].name) == 0)
        {
            index = i;
            break;
        }
    }
    double min = atof(dataColumns[index].data[0].data);
    for (int i = 1; i < dataColumns[index].numOfData; i++)
    {
        if (atof(dataColumns[index].data[i].data) < min)
        {
            min = atof(dataColumns[index].data[i].data);
        }
    }
    return min;
}

void postfixEvaluateStat(Queue *postfix, char *result)
{
    Stack *s = createStack();

    while (!isQueueEmpty(postfix))
    {
        char *token = deQueue(postfix);

        if (isFunction(token))
        {
            double res;

            if (strcmp(token, "sum") == 0 || strcmp(token, "mean") == 0 || strcmp(token, "mode") == 0 ||
                strcmp(token, "median") == 0 || strcmp(token, "range") == 0 || strcmp(token, "pvar") == 0 ||
                strcmp(token, "pstd") == 0 || strcmp(token, "svar") == 0 || strcmp(token, "sstd") == 0 || strcmp(token, "sort") == 0 ||
                strcmp(token, "max") == 0 || strcmp(token, "min") == 0 || strcmp(token, "ln") == 0 || strcmp(token, "log") == 0)
            {
                char *op = pop(s);
                if (strcmp(token, "sum") == 0)
                {
                    res = sum(op);
                }
                else if (strcmp(token, "mean") == 0)
                {
                    res = mean(op);
                }
                else if (strcmp(token, "mode") == 0)
                {
                    res = mode(op);
                }
                else if (strcmp(token, "median") == 0)
                {
                    res = median(op);
                }
                else if (strcmp(token, "range") == 0)
                {
                    res = range(op);
                }
                else if (strcmp(token, "pvar") == 0)
                {
                    res = pvar(op);
                }
                else if (strcmp(token, "pstd") == 0)
                {
                    res = pstd(op);
                }
                else if (strcmp(token, "svar") == 0)
                {
                    res = svar(op);
                }
                else if (strcmp(token, "sstd") == 0)
                {
                    res = sstd(op);
                }
                else if (strcmp(token, "sort") == 0)
                {
                    sort(op);
                    res = 0;
                }
                else if (strcmp(token, "max") == 0)
                {
                    res = max(op);
                }
                else if (strcmp(token, "min") == 0)
                {
                    res = min(op);
                }
                else if (strcmp(token, "ln") == 0)
                {
                    res = log(atof(op));
                }
                else if (strcmp(token, "log") == 0)
                {
                    res = log10(atof(op));
                }

                free(op);
            }
            else
            {
                char *op2 = pop(s);
                char *op1 = pop(s);
                if (strcmp(token, "+") == 0)
                {
                    res = atof(op1) + atof(op2);
                }
                else if (strcmp(token, "-") == 0)
                {
                    res = atof(op1) - atof(op2);
                }
                else if (strcmp(token, "*") == 0)
                {
                    res = atof(op1) * atof(op2);
                }
                else if (strcmp(token, "/") == 0)
                {
                    res = atof(op1) / atof(op2);
                }
                else if (strcmp(token, "^") == 0)
                {
                    res = pow(atof(op1), atof(op2));
                }
                else if (strcmp(token, "log_") == 0)
                {
                    if (atof(op1) > 0 && atof(op2) > 0)
                    {
                        res = log(atof(op2)) / log(atof(op1));
                    }
                    else
                    {
                        printf("Error: Logarithm of non-positive number\n");
                        drawLine();
                        free(op1);
                        free(op2);
                        return;
                    }
                }
                else if (strcmp(token, "cov") == 0)
                {
                    res = cov(op1, op2);
                }
                else if (strcmp(token, "corr") == 0)
                {
                    res = corr(op1, op2);
                }
                free(op1);
                free(op2);
            }
            char *resultStr = (char *)malloc(100);
            sprintf(resultStr, "%lf", res);
            push(s, resultStr);
        }
        else
        {
            push(s, token);
        }
    }
    char *finalResult = pop(s);
    strcpy(result, finalResult);
    free(finalResult);
    freeStack(s);
}
