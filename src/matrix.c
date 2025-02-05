#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define MAX_MATRICES 26

void pushMatrix(MatrixStack *stack, Matrix matrix)
{
    MatrixNode *newNode = (MatrixNode *)malloc(sizeof(MatrixNode));
    newNode->matrix = matrix;
    newNode->next = stack->top;
    stack->top = newNode;
}

Matrix popMatrix(MatrixStack *stack)
{
    if (stack->top == NULL)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    MatrixNode *temp = stack->top;
    Matrix matrix = temp->matrix;
    stack->top = stack->top->next;
    free(temp);
    return matrix;
}

int isEmptyMatrixStack(MatrixStack *stack)
{
    return stack->top == NULL;
}

MatrixNode *matrixList = NULL;
int matrixCount = 0;
char mode[10];

int isMatrix(MatrixNode *matrixList, char id)
{
    MatrixNode *temp = matrixList;
    if (id == 'I')
    {
        return 1;
    }
    while (temp != NULL)
    {
        if (temp->matrix.id == id)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void createNullMatrix(double ***matrix, int rows, int cols)
{
    *matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        (*matrix)[i] = (double *)malloc(cols * sizeof(double));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            (*matrix)[i][j] = 0;
        }
    }
}

void createIdentityMatrix(double ***matrix, int rows, int cols)
{
    *matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        (*matrix)[i] = (double *)malloc(cols * sizeof(double));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == j)
            {
                (*matrix)[i][j] = 1;
            }
            else
            {
                (*matrix)[i][j] = 0;
            }
        }
    }
}

void printMatrixList(MatrixNode *matrixList)
{
    MatrixNode *temp = matrixList;
    while (temp != NULL)
    {
        printf("Matrix %c\n", temp->matrix.id);
        for (int i = 0; i < temp->matrix.rows; i++)
        {
            for (int j = 0; j < temp->matrix.cols; j++)
            {
                printf("%-10.2f", temp->matrix.matrix[i][j]);
            }
            printf("\n");
        }
        temp = temp->next;
    }
}

void setMatrix()
{
    if (matrixCount >= MAX_MATRICES)
    {
        printf("Matrix limit reached.\n");
        return;
    }

    sprintf(mode, "Matrix %c", 'A' + matrixCount);

    int rows = 0;
    int cols = 0;
    while (rows <= 0)
    {
        drawTitle(mode, -1);
        printf("Enter the number of rows: ");
        char input[10];
        if (scanf("%9s", input) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }
        rows = atoi(input);
    }
    while (cols <= 0)
    {
        drawTitle(mode, -1);
        printf("Enter the number of columns: ");
        char input[10];
        if (scanf("%9s", input) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }
        cols = atoi(input);
    }

    double **matrix;
    createNullMatrix(&matrix, rows, cols);
    fillMatrix(matrix, rows, cols);

    MatrixNode *newNode = (MatrixNode *)malloc(sizeof(MatrixNode));
    newNode->matrix.id = 'A' + matrixCount;
    newNode->matrix.matrix = matrix;
    newNode->matrix.rows = rows;
    newNode->matrix.cols = cols;
    newNode->next = matrixList;
    matrixList = newNode;
    matrixCount++;
    getchar();
}

void fillMatrix(double **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = 0;
        }
    }
    int highLightRow = 0;
    int highLightCol = 0;

    while (1)
    {
        drawTitle(mode, -1);
        displayMatrix(matrix, rows, cols, highLightRow, highLightCol);
        printf("Enter value for element [%d][%d]: ", highLightRow + 1, highLightCol + 1);
        if (scanf("%lf", &matrix[highLightRow][highLightCol]) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }

        highLightCol++;
        if (highLightCol == cols)
        {
            highLightCol = 0;
            highLightRow++;
            if (highLightRow == rows)
            {
                break;
            }
        }
    }
    displayMatrix(matrix, rows, cols, -1, -1);
}

void displayMatrix(double **matrix, int rows, int cols, int highLightRow, int highLightCol)
{
    drawTitle(mode, -1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == highLightRow && j == highLightCol)
            {
                printf("\033[1;31m");
            }
            printf("%-10.2f", matrix[i][j]);
            printf("\033[0m");
        }
        printf("\n");
    }
    drawLine();
}

void matrixMenu()
{
    int choice = 0;
    while (choice < 1 || choice > 3)
    {
        drawTitle("Matrix Menu", -1);
        const char *menuItems[] = {
            "1. Set Matrix"};
        for (int i = 0; i < 1; i++)
        {
            printf("%-15s\n", menuItems[i]);
        }

        drawLine();
        printf("Enter your choice(1-3): ");
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
    switch (choice)
    {
    case 1:
        setMatrix();
        break;
    }
}

void matrixAdd(Matrix *result, Matrix *op1, Matrix *op2)
{
    if (op1->rows != op2->rows || op1->cols != op2->cols)
    {
        printf("Error: Matrices must have the same dimensions\n");
        return;
    }
    result->rows = op1->rows;
    result->cols = op1->cols;
    createNullMatrix(&result->matrix, result->rows, result->cols);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->matrix[i][j] = op1->matrix[i][j] + op2->matrix[i][j];
        }
    }
}

void matrixSub(Matrix *result, Matrix *op1, Matrix *op2)
{
    if (op1->rows != op2->rows || op1->cols != op2->cols)
    {
        printf("Error: Matrices must have the same dimensions\n");
        return;
    }
    result->rows = op1->rows;
    result->cols = op1->cols;
    createNullMatrix(&result->matrix, result->rows, result->cols);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->matrix[i][j] = op1->matrix[i][j] - op2->matrix[i][j];
        }
    }
}

void matrixMul(Matrix *result, Matrix *op1, Matrix *op2)
{
    if (op1->cols != op2->rows)
    {
        printf("Error: Number of columns in first matrix must be equal to number of rows in second matrix\n");
        return;
    }
    result->rows = op1->rows;
    result->cols = op2->cols;
    createNullMatrix(&result->matrix, result->rows, result->cols);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->matrix[i][j] = 0;
            for (int k = 0; k < op1->cols; k++)
            {
                result->matrix[i][j] += op1->matrix[i][k] * op2->matrix[k][j];
            }
        }
    }
}

void matrixTranspose(Matrix *result, Matrix *op)
{
    result->rows = op->cols;
    result->cols = op->rows;
    createNullMatrix(&result->matrix, result->rows, result->cols);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->matrix[i][j] = op->matrix[j][i];
        }
    }
}

void matrixInverse(Matrix *result, Matrix *op)
{
    if (op->rows != op->cols)
    {
        printf("Error: Matrix must be square\n");
        return;
    }
    int n = op->rows;
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double *)malloc(2 * n * sizeof(double));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = op->matrix[i][j];
            if (i == j)
            {
                matrix[i][j + n] = 1;
            }
            else
            {
                matrix[i][j + n] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (matrix[i][i] == 0)
        {
            printf("Error: Matrix is singular\n");
            return;
        }
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                double ratio = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < 2 * n; k++)
                {
                    matrix[j][k] = matrix[j][k] - ratio * matrix[i][k];
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        double a = matrix[i][i];
        for (int j = 0; j < 2 * n; j++)
        {
            matrix[i][j] = matrix[i][j] / a;
        }
    }
    result->rows = n;
    result->cols = n;
    createNullMatrix(&result->matrix, n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result->matrix[i][j] = matrix[i][j + n];
        }
    }
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void postfixEvaluateMat(Queue *postfix, char *result)
{
    MatrixStack *s = (MatrixStack *)malloc(sizeof(MatrixStack));
    s->top = NULL;
    while (!isQueueEmpty(postfix))
    {
        char *token = deQueue(postfix);
        if (isMatrixOperator(token))
        {
            Matrix op1, op2, result;
            if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0)
            {
                op2 = popMatrix(s);
                op1 = popMatrix(s);
                if (op2.id == 'Z' || op1.id == 'Z')
                {
                    if (op2.id == 'Z')
                    {
                        createNullMatrix(&op2.matrix, op1.rows, op1.cols);
                    }
                    else
                    {
                        createNullMatrix(&op1.matrix, op2.rows, op2.cols);
                    }
                }
                if (strcmp(token, "+") == 0)
                {
                    matrixAdd(&result, &op1, &op2);
                }
                else if (strcmp(token, "-") == 0)
                {
                    matrixSub(&result, &op1, &op2);
                }
                else if (strcmp(token, "*") == 0)
                {
                    matrixMul(&result, &op1, &op2);
                }
                pushMatrix(s, result);
            }
            else if (strcmp(token, "'") == 0 || strcmp(token, "^-1") == 0 || strcmp(token, "inv") == 0 || strcmp(token, "T") == 0)
            {
                op1 = popMatrix(s);
                if (strcmp(token, "'") == 0 || strcmp(token, "T") == 0)
                {
                    matrixTranspose(&result, &op1);
                }
                else if (strcmp(token, "^-1") == 0 || strcmp(token, "inv") == 0)
                {
                    matrixInverse(&result, &op1);
                }
                pushMatrix(s, result);
            }
        }
        else
        {
            MatrixNode *temp = matrixList;
            while (temp != NULL)
            {
                if (temp->matrix.id == token[0])
                {
                    pushMatrix(s, temp->matrix);
                    break;
                }
                temp = temp->next;
            }
        }
    }
    Matrix resultMatrix = popMatrix(s);
    MatrixNode *newNode = (MatrixNode *)malloc(sizeof(MatrixNode));
    newNode->matrix.id = 'R';
    newNode->matrix = resultMatrix;
    newNode->next = matrixList;
    matrixList = newNode;
    matrixCount++;
    displayMatrix(resultMatrix.matrix, resultMatrix.rows, resultMatrix.cols, -1, -1);
    free(s);
}

void matrix(int degreeMode)
{
    drawTitle("Matrix", degreeMode);

    char *input = (char *)malloc(128);
    while (1)
    {
        getStrInput(input);
        if (strlen(input) == 1 && input[0] == 'M')
        {
            matrixMenu();
        }
        else
        {
            int isValid = 1;
            Queue *infixQueue = createQueue();
            isValid = tokenizeMatrix(infixQueue, input, matrixList);
            if (isQueueEmpty(infixQueue) || !isValid)
            {
                freeQueue(infixQueue);
                continue;
            }
            printQueue(infixQueue);
            Queue *postfixQueue = createQueue();
            infixToPostfix(infixQueue, postfixQueue, NULL);
            printQueue(postfixQueue);
            char *result = (char *)malloc(100);
            postfixEvaluateMat(postfixQueue, result);
            freeQueue(infixQueue);
            freeQueue(postfixQueue);
            printMatrixList(matrixList);
        }
    }
    free(input);
}
