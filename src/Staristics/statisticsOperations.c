#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

double sum(char *titleName)
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
        return 0;
    }
    double sum = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        sum += atof(dataColumns[index].data[i].data);
    }
    return sum;
}

double sumsqr(char *titleName)
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
        return 0;
    }
    double sumsqr = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        sumsqr += pow(atof(dataColumns[index].data[i].data), 2);
    }
    return sumsqr;
}

double sumxy(char *titleName1, char *titleName2)
{
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName1, dataColumns[i].name) == 0)
        {
            index1 = i;
        }
        if (strcmp(titleName2, dataColumns[i].name) == 0)
        {
            index2 = i;
        }
    }
    if (index1 == -1 || index2 == -1)
    {
        printf("Column not found\n");
        return 0;
    }
    double sumxy = 0;
    for (int i = 0; i < dataColumns[index1].numOfData; i++)
    {
        sumxy += atof(dataColumns[index1].data[i].data) * atof(dataColumns[index2].data[i].data);
    }
    return sumxy;
}

double mean(char *titleName)
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
    double sum = 0;
    for (int i = 0; i < dataColumns[index].numOfData; i++)
    {
        sum += atof(dataColumns[index].data[i].data);
    }
    return sum / dataColumns[index].numOfData;
}

double median(char *titleName)
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
double modeStat(char *titleName)
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
    double modeStat = 0;
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
            modeStat = data[i];
        }
    }
    free(data);
    return modeStat;
}

double range(char *titleName)
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

double pvar(char *titleName)
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

double svar(char *titleName)
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

double pstd(char *titleName)
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

double sstd(char *titleName)
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

double pcov(char *titleName1, char *titleName2)
{
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName1, dataColumns[i].name) == 0)
        {
            index1 = i;
        }
        if (strcmp(titleName2, dataColumns[i].name) == 0)
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

double scov(char *titleName1, char *titleName2)
{
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName1, dataColumns[i].name) == 0)
        {
            index1 = i;
        }
        if (strcmp(titleName2, dataColumns[i].name) == 0)
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
    cov /= dataColumns[index1].numOfData - 1;
    free(data1);
    free(data2);
    return cov;
}
double corr(char *titleName1, char *titleName2)
{
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < numOfColumn; i++)
    {
        if (strcmp(titleName1, dataColumns[i].name) == 0)
        {
            index1 = i;
        }
        if (strcmp(titleName2, dataColumns[i].name) == 0)
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

double max(char *titleName)
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

double min(char *titleName)
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

            if (isTrigonometricFunction(token) || isInverseTrigonometricFunction(token))
            {
                if (degreeMode && (isTrigonometricFunction(token)))
                {
                    char *op = pop(s);
                    double angle = atof(op);
                    angle = angle * (PI / 180);
                    free(op);
                    char *angleStr = (char *)malloc(100);
                    sprintf(angleStr, "%f", angle);
                    push(s, angleStr);
                }
                char *op = pop(s);
                if (strcmp(token, "sin") == 0)
                {
                    res = sin(atof(op));
                }
                else if (strcmp(token, "cos") == 0)
                {
                    res = cos(atof(op));
                }
                else if (strcmp(token, "tan") == 0)
                {
                    res = tan(atof(op));
                }
                else if (strcmp(token, "csc") == 0)
                {
                    double value = sin(atof(op));
                    if (value == 0)
                    {
                        printf("Error: Division by zero in csc\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    res = 1 / value;
                }
                else if (strcmp(token, "sec") == 0)
                {
                    double value = cos(atof(op));
                    if (value == 0)
                    {
                        printf("Error: Division by zero in sec\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    res = 1 / value;
                }
                else if (strcmp(token, "cot") == 0)
                {
                    double value = tan(atof(op));
                    if (value == 0)
                    {
                        printf("Error: Division by zero in cot\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    res = 1 / value;
                }
                else if (strcmp(token, "asin") == 0)
                {
                    double value = atof(op);
                    if (value < -1 || value > 1)
                    {
                        printf("Error: asin out of range\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    if (degreeMode)
                    {
                        res = asin(value) * 180 / PI;
                    }
                    else
                    {
                        res = asin(value);
                    }
                }
                else if (strcmp(token, "acos") == 0)
                {
                    double value = atof(op);
                    if (value < -1 || value > 1)
                    {
                        printf("Error: acos out of range\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    if (degreeMode)
                    {
                        res = acos(value) * 180 / PI;
                    }
                    else
                    {
                        res = acos(value);
                    }
                }
                else if (strcmp(token, "atan") == 0)
                {
                    if (degreeMode)
                    {
                        res = atan(atof(op)) * 180 / PI;
                    }
                    else
                    {
                        res = atan(atof(op));
                    }
                }
                else if (strcmp(token, "acsc") == 0)
                {
                    double value = atof(op);
                    if (value == 0)
                    {
                        printf("Error: Division by zero in acsc\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    value = 1 / value;
                    if (value < -1 || value > 1)
                    {
                        printf("Error: acsc out of range\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    if (degreeMode)
                    {
                        res = asin(value) * 180 / PI;
                    }
                    else
                    {
                        res = asin(value);
                    }
                }
                else if (strcmp(token, "asec") == 0)
                {
                    double value = atof(op);
                    if (value == 0)
                    {
                        printf("Error: Division by zero in asec\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    value = 1 / value;
                    if (value < -1 || value > 1)
                    {
                        printf("Error: asec out of range\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    if (degreeMode)
                    {
                        res = acos(value) * 180 / PI;
                    }
                    else
                    {
                        res = acos(value);
                    }
                }
                else if (strcmp(token, "acot") == 0)
                {
                    double value = atof(op);
                    if (value == 0)
                    {
                        printf("Error: Division by zero in acot\n");
                        drawLine();
                        free(op);
                        return;
                    }
                    value = 1 / value;
                    if (degreeMode)
                    {
                        res = atan(value) * 180 / PI;
                    }
                    else
                    {
                        res = atan(value);
                    }
                }
                free(op);
            }
            else if (strcmp(token, "ln") == 0 || strcmp(token, "log") == 0 || strcmp(token, "sum") == 0 || strcmp(token, "sumsqr") == 0 || strcmp(token, "mean") == 0 || strcmp(token, "mode") == 0 || strcmp(token, "median") == 0 || strcmp(token, "range") == 0 || strcmp(token, "svar") == 0 || strcmp(token, "sstd") == 0 || strcmp(token, "pvar") == 0 || strcmp(token, "pstd") == 0 || strcmp(token, "max") == 0 || strcmp(token, "min") == 0)
            {
                char *op = pop(s);
                if (strcmp(token, "sum") == 0)
                {
                    res = sum(op);
                }
                else if (strcmp(token, "sumsqr") == 0)
                {
                    res = sumsqr(op);
                }
                else if (strcmp(token, "mean") == 0)
                {
                    res = mean(op);
                }
                else if (strcmp(token, "mode") == 0)
                {
                    res = modeStat(op);
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
                else if (strcmp(token, "max") == 0)
                {
                    res = max(op);
                }
                else if (strcmp(token, "min") == 0)
                {
                    res = min(op);
                }
                else if (strcmp(token, "ln") == 0 && !isStatOperand(op))
                {
                    if (atof(op) > 0)
                    {
                        res = log(atof(op));
                    }
                    else
                    {
                        printf("Error: Logarithm of non-positive number\n");
                        drawLine();
                        free(op);
                        return;
                    }
                }
                else if (strcmp(token, "log") == 0 && !isStatOperand(op))
                {
                    if (atof(op) > 0)
                    {
                        res = log10(atof(op));
                    }
                    else
                    {
                        printf("Error: Logarithm of non-positive number\n");
                        drawLine();
                        free(op);
                        return;
                    }
                }
                free(op);
            }
            else if (strcmp(token, "scov") == 0 || strcmp(token, "pcov") == 0 || strcmp(token, "corr") == 0 || strcmp(token, "sumxy") == 0)
            {
                char *op2 = pop(s);
                char *op1 = pop(s);
                if (op1 == NULL || op2 == NULL)
                {
                    printf("Error: Invalid expression\n");
                    drawLine();
                    if (op1)
                        free(op1);
                    if (op2)
                        free(op2);
                    return;
                }
                if (isStatOperand(op1) == 0 || isStatOperand(op2) == 0)
                {
                    printf("Error: Invalid expression\n");
                    drawLine();
                    free(op1);
                    free(op2);
                    return;
                }
                if (strcmp(token, "scov") == 0)
                {
                    res = scov(op1, op2);
                }
                else if (strcmp(token, "pcov") == 0)
                {
                    res = pcov(op1, op2);
                }
                else if (strcmp(token, "corr") == 0)
                {
                    res = corr(op1, op2);
                }
                else if (strcmp(token, "sumxy") == 0)
                {
                    res = sumxy(op1, op2);
                }
                free(op1);
                free(op2);
            }
            else
            {
                char *op2 = pop(s);
                char *op1 = pop(s);
                if (op1 == NULL || op2 == NULL)
                {
                    printf("Error: Invalid expression\n");
                    drawLine();
                    return;
                }
                if (isStatOperand(op1) == 1 || isStatOperand(op2) == 1)
                {
                    printf("Error: Invalid expression\n");
                    drawLine();
                    return;
                }
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
                    if (atof(op2) == 0)
                    {
                        printf("Error: Division by zero\n");
                        drawLine();
                        free(op1);
                        free(op2);
                        return;
                    }
                    res = atof(op1) / atof(op2);
                }
                else if (strcmp(token, "^") == 0)
                {
                    res = pow(atof(op1), atof(op2));
                }
                else if (strcmp(token, "log_") == 0 && !isStatOperand(op1) && !isStatOperand(op2))
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
