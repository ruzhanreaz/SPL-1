#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

typedef struct
{
    char *name;
    char *value;
} Variable;

Variable *variables = NULL;
char **varList;
int numVariables = 0;

void addVariable(char *name)
{
    varList = realloc(varList, (numVariables + 1) * sizeof(char *));
    variables = realloc(variables, (numVariables + 1) * sizeof(Variable));
    varList[numVariables] = strdup(name);
    variables[numVariables].name = strdup(name);
    variables[numVariables].value = NULL;
    numVariables++;
}
int isVarExist(char *name)
{
    for (int i = 0; i < numVariables; i++)
    {
        if (strcmp(varList[i], name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void setVarValue(char *name, char *value)
{
    for (int i = 0; i < numVariables; i++)
    {
        if (strcmp(varList[i], name) == 0)
        {
            variables[i].value = strdup(value);
            return;
        }
    }
    printf("Variable %s not found\n", name);
}

void getVarValue(char *name, char *value)
{
    for (int i = 0; i < numVariables; i++)
    {
        if (strcmp(varList[i], name) == 0)
        {
            strcpy(value, variables[i].value);
            return;
        }
    }
    printf("Variable %s not found\n", name);
}

void equation()
{
    drawTitle(2);

    char eqn[MAX_INPUT_SIZE];
    while (1)
    {
        getStrInput(eqn);

        if (strchr(eqn, '=') == NULL)
        {
            char *temp = strdup(eqn);
            char *ptr = temp;
            while (*ptr)
            {
                if (isalpha(*ptr))
                {
                    char *start = ptr;
                    while (isalpha(*ptr))
                    {
                        ptr++;
                    }
                    char *var = malloc(ptr - start + 1);
                    strncpy(var, start, ptr - start);
                    var[ptr - start] = '\0';
                    if (!isVarExist(var))
                        addVariable(var);
                    free(var);
                }
                else
                {
                    ptr++;
                }
            }
            free(temp);
            for (int i = 0; i < numVariables; i++)
            {
                printf("%s : ", varList[i]);
                char value[MAX_INPUT_SIZE];
                getStrInput(value);
                setVarValue(varList[i], value);
            }
            Queue *infixQueue = createQueue();
            int valid = 1;
            valid = tokenize(infixQueue, eqn);
            if (isQueueEmpty(infixQueue) || !valid)
            {
                freeQueue(infixQueue);
                return;
            }
            Queue *postfixQueue = createQueue();
            infixToPostfix(infixQueue, postfixQueue);
            char *result = (char *)malloc(100);
            postfixEvaluateComp(postfixQueue, result);
            freeQueue(infixQueue);
            freeQueue(postfixQueue);
            outputString(result);
            free(result);
            free(varList);
            free(variables);
            numVariables = 0;
        }
        else
        {
            char *modEqn = (char *)calloc(100, sizeof(char));
            modifyEqn(eqn, modEqn);
            solve(modEqn);
            free(modEqn);
        }
    }
}

void modifyEqn(char *str, char *modEqn)
{
    char *lhs = malloc(MAX_INPUT_SIZE);
    char *rhs = malloc(MAX_INPUT_SIZE);
    char *eqnCopy = strdup(str);
    lhs = strtok(eqnCopy, "=");
    rhs = strtok(NULL, "=");
    // printf("lhs: %s\n", lhs);
    // printf("rhs: %s\n", rhs);

    char *rhs_copy = malloc(strlen(rhs) + 1);
    strcpy(rhs_copy, rhs);

    while (*rhs_copy != '\0')
    {
        if (*rhs_copy == '+')
        {
            *rhs_copy = '-';
        }
        else if (*rhs_copy == '-')
        {
            *rhs_copy = '+';
        }
        rhs_copy++;
    }

    rhs_copy -= strlen(rhs);
    // printf("rhs_copy: %s\n", rhs_copy);
    char *tempStr = malloc(strlen(lhs) + strlen(rhs) + 4);
    if (*rhs_copy == '-' || *rhs_copy == '+')
        sprintf(tempStr, "%s%s", lhs, rhs_copy);
    else if (*rhs_copy == '0')
        sprintf(tempStr, "%s", lhs);
    else
        sprintf(tempStr, "%s-%s", lhs, rhs_copy);
    Queue *infixQueue = createQueue();
    int valid = 1;
    valid = tokenize(infixQueue, tempStr);
    if (isQueueEmpty(infixQueue) || !valid)
    {
        freeQueue(infixQueue);
        return;
    }
    // printQueue(infixQueue);
    queueToString(infixQueue, modEqn);
    // printf("Modified eqn: %s\n", modEqn);
    free(tempStr);
    free(rhs_copy);

    free(eqnCopy);
    freeQueue(infixQueue);
}

int validVar(char *str)
{
    return (strcmp(str, "x") == 0 || strcmp(str, "y") == 0 || strcmp(str, "z") == 0);
}
void checkNumberOfVariable(char *str)
{
    int count = 0;

    if (strchr(str, 'x') != NULL)
    {
        count++;
    }
    if (strchr(str, 'y') != NULL)
    {
        count++;
    }
    if (strchr(str, 'z') != NULL)
    {
        count++;
    }

    if (count == 0)
    {
        printf("Invalid input\n");
        return;
    }
    else if (count == 1)
    {
        solveLinear(str);
    }
    else if (count == 2)
    {
        solve2Variable(str);
    }
    else
    {
        solve3Variable(str);
    }
}
void solve(char *str)
{
    int degree = 0;
    if (strstr(str, "^3") != NULL)
    {
        degree = 3;
    }
    else if (strstr(str, "^2") != NULL)
    {
        degree = 2;
    }
    else
    {
        degree = 1;
    }

    switch (degree)
    {
    case 3:
        solveCubic(str);
        drawLine();
        break;
    case 2:
        solveQuadratic(str);
        drawLine();
        break;
    case 1:
        checkNumberOfVariable(str);
        drawLine();
        break;
    default:

        break;
    }
}
void solveQuadratic(char *str)
{
    double a, b, c;
    if (sscanf(str, "%lfx^2%lfx%lf", &a, &b, &c) != 3)
    {
        printf("Invalid input\n");
        return;
    }
    // printf("a = %lf, b = %lf, c = %lf\n", a, b, c);
    double d = b * b - 4 * a * c;
    if (d < 0)
    {
        printf("No real roots\n");
    }
    else if (d == 0)
    {
        double x = -b / (2 * a);
        printf("x = %lf\n", x);
    }
    else
    {
        double x1 = (-b + sqrt(d)) / (2 * a);
        double x2 = (-b - sqrt(d)) / (2 * a);
        printf("x1 = %lf\n", x1);
        printf("x2 = %lf\n", x2);
    }
}
void solveCubic(char *str)
{
    double a, b, c, d;
    if (sscanf(str, "%lfx^3%lfx^2%lfx%lf", &a, &b, &c, &d) != 4)
    {
        printf("Invalid input\n");
        return;
    }
    // printf("a = %lf, b = %lf, c = %lf, d = %lf\n", a, b, c, d);
    double p = c / a - (b * b) / (3 * a * a);
    double q = 2 * (b * b * b) / (27 * a * a * a) - (b * c) / (3 * a * a) + d / a;
    double delta = (q * q) / 4 + (p * p * p) / 27;
    if (delta > 0)
    {
        double u = cbrt(-q / 2 + sqrt(delta));
        double v = cbrt(-q / 2 - sqrt(delta));
        double x1 = u + v - b / (3 * a);
        printf("x1 = %lf\n", x1);
    }
    else if (delta == 0)
    {
        double u = cbrt(-q / 2);
        double v = cbrt(-q / 2);
        double x1 = u + v - b / (3 * a);
        double x2 = -0.5 * (u + v) - b / (3 * a);
        printf("x1 = %lf\n", x1);
        printf("x2 = %lf\n", x2);
    }
    else
    {
        double r = sqrt((-p * p * p) / 27);
        double theta = acos(-q / (2 * r));
        double x1 = 2 * cbrt(r) * cos(theta / 3) - b / (3 * a);
        double x2 = 2 * cbrt(r) * cos((theta + 2 * PI) / 3) - b / (3 * a);
        double x3 = 2 * cbrt(r) * cos((theta + 4 * PI) / 3) - b / (3 * a);
        printf("x1 = %lf\n", x1);
        printf("x2 = %lf\n", x2);
        printf("x3 = %lf\n", x3);
    }
}
void solveLinear(char *str)
{
    double a, b;
    if (sscanf(str, "%lfx%lf", &a, &b) != 2)
    {
        printf("Invalid input\n");
        return;
    }
    if (a == 0)
    {
        printf("No solution\n");
    }
    else
    {
        double x = -b / a;
        printf("x = %g\n", x);
    }
}

void solve2Variable(char *str)
{
    char *eqn1 = (char *)malloc(strlen(str) + 1);
    strcpy(eqn1, str);
    char tempEqn2[128];
    getStrInput(tempEqn2);
    char eqn2[128] = {0};

    modifyEqn(tempEqn2, eqn2);
    double a1, b1, c1, a2, b2, c2;
    if (sscanf(eqn1, "%lfx%lfy%lf", &a1, &b1, &c1) != 3)
    {
        printf("Invalid input\n");
        return;
    }
    if (sscanf(eqn2, "%lfx%lfy%lf", &a2, &b2, &c2) != 3)
    {
        printf("Invalid input\n");
        return;
    }
    double d = a1 * b2 - a2 * b1;
    double dx = c1 * b2 - c2 * b1;
    double dy = a1 * c2 - a2 * c1;
    if (d == 0)
    {
        if (dx == 0 && dy == 0)
        {
            printf("Infinite solutions\n");
        }
        else
        {
            printf("No solution\n");
        }
    }
    else
    {
        double x = -dx / d;
        double y = -dy / d;
        printf("x = %g\n", x);
        printf("y = %g\n", y);
    }
    free(eqn1);
}

void solve3Variable(char *str)
{
    char *eqn1 = (char *)malloc(strlen(str) + 1);
    strcpy(eqn1, str);
    char tempEqn2[128];
    getStrInput(tempEqn2);
    char eqn2[128] = {0};
    modifyEqn(tempEqn2, eqn2);

    char tempEqn3[128];
    getStrInput(tempEqn3);
    char eqn3[128] = {0};
    modifyEqn(tempEqn3, eqn3);

    double a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3;
    if (sscanf(eqn1, "%lfx%lfy%lfz%lf", &a1, &b1, &c1, &d1) != 4)
    {
        printf("Invalid input\n");
        return;
    }
    if (sscanf(eqn2, "%lfx%lfy%lfz%lf", &a2, &b2, &c2, &d2) != 4)
    {
        printf("Invalid input\n");
        return;
    }
    if (sscanf(eqn3, "%lfx%lfy%lfz%lf", &a3, &b3, &c3, &d3) != 4)
    {
        printf("Invalid input\n");
        return;
    }
    double d = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
    double dx = d1 * (b2 * c3 - b3 * c2) - b1 * (d2 * c3 - d3 * c2) + c1 * (d2 * b3 - d3 * b2);
    double dy = a1 * (d2 * c3 - d3 * c2) - d1 * (a2 * c3 - a3 * c2) + c1 * (a2 * d3 - a3 * d2);
    double dz = a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2) + d1 * (a2 * b3 - a3 * b2);
    if (d == 0)
    {
        if (dx == 0 && dy == 0 && dz == 0)
        {
            printf("Infinite solutions\n");
        }
        else
        {
            printf("No solution\n");
        }
    }
    else
    {
        double x = -dx / d;
        double y = -dy / d;
        double z = -dz / d;
        printf("x = %g\n", x);
        printf("y = %g\n", y);
        printf("z = %g\n", z);
    }
    free(eqn1);
}
