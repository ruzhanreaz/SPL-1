#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Matrix *matrixList[10];
int matrixCount = 0;
char **matrixName;

int isMatrix(char *name)
{
    for (int i = 0; i < matrixCount; i++)
    {
        if (strcmp(matrixList[i]->id, name) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int validMatrixName(char *name)
{
    if (strcmp(name, "I") == 0 || strcmp(name, "U") == 0 || strcmp(name, "R") == 0 || strcmp(name, "Q") == 0 || strcmp(name, "L") == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void getMatrix(char *name, double ***matrix, int *rows, int *cols)
{
    for (int i = 0; i < matrixCount; i++)
    {
        if (strcmp(matrixList[i]->id, name) == 0)
        {
            *matrix = matrixList[i]->matrix;
            *rows = matrixList[i]->rows;
            *cols = matrixList[i]->cols;
            break;
        }
    }
}
void setMatrix()
{
    drawTitle(2);

    char name[10];
    if (luMode)
    {
        strcpy(name, "A");
    }
    else
    {
        printf("Enter the name of the matrix: ");
        getStrInput(name);
    }

    if (isMatrix(name) || !validMatrixName(name))
    {
        printf("Invalid name. Please try again.\n");
        return;
    }
    int rows = 0;
    int cols = 0;
    if (luMode)
    {
        printf("Enter the number of rows or cols: ");
        char input[10];
        if (scanf("%9s", input) != 1)
        {
            while (getchar() != '\n')
                ;
        }
        else
        {
            rows = atoi(input);
            cols = rows;
        }
    }

    else
    {
        while (rows <= 0)
        {
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
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 1);
    strcpy(matrixList[matrixCount]->id, name);
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrixList[matrixCount]->matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    fillMatrix(matrixList[matrixCount]->matrix, rows, cols);
    getchar();
    matrixCount++;
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
    drawTitle(2);
    printf("Matrix %s:\n", matrixList[matrixCount]->id);
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

void clearAMatrix()
{
    drawTitle(2);
    char name[10];
    printf("Enter the name of the matrix: ");
    getStrInput(name);
    if (!isMatrix(name))
    {
        printf("Matrix not found. Please try again.\n");
        return;
    }
    for (int i = 0; i < matrixCount; i++)
    {
        if (strcmp(matrixList[i]->id, name) == 0)
        {
            for (int j = 0; j < matrixList[i]->rows; j++)
            {
                free(matrixList[i]->matrix[j]);
            }
            free(matrixList[i]->matrix);
            free(matrixList[i]->id);
            free(matrixList[i]);
            for (int j = i; j < matrixCount - 1; j++)
            {
                matrixList[j] = matrixList[j + 1];
            }
            matrixCount--;
            break;
        }
    }
}
void clearAllMatrix()
{
    for (int i = 0; i < matrixCount; i++)
    {
        for (int j = 0; j < matrixList[i]->rows; j++)
        {
            free(matrixList[i]->matrix[j]);
        }
        free(matrixList[i]->matrix);
        free(matrixList[i]->id);
        free(matrixList[i]);
    }
    matrixCount = 0;
}
void showAMatrix()
{
    drawTitle(2);
    char name[10];
    printf("Enter the name of the matrix: ");
    getStrInput(name);
    if (!isMatrix(name))
    {
        printf("Matrix not found. Please try again.\n");
        return;
    }
    for (int i = 0; i < matrixCount; i++)
    {
        if (strcmp(matrixList[i]->id, name) == 0)
        {
            printf("Matrix %s:\n", matrixList[i]->id);
            for (int j = 0; j < matrixList[i]->rows; j++)
            {
                for (int k = 0; k < matrixList[i]->cols; k++)
                {
                    printf("%-10.2f", matrixList[i]->matrix[j][k]);
                }
                printf("\n");
            }
            drawLine();
            break;
        }
    }
}
void showAllMatrix()
{
    drawTitle(2);
    for (int i = 0; i < matrixCount; i++)
    {
        printf("Matrix %s:\n", matrixList[i]->id);
        for (int j = 0; j < matrixList[i]->rows; j++)
        {
            for (int k = 0; k < matrixList[i]->cols; k++)
            {
                printf("%-10.2f", matrixList[i]->matrix[j][k]);
            }
            printf("\n");
        }
        drawLine();
    }
}

void matrix()
{
    drawTitle(2);
    char expression[100];

    matrixName = (char **)malloc(matrixCount * sizeof(char *));
    for (int i = 0; i < matrixCount; i++)
    {
        matrixName[i] = matrixList[i]->id;
    }

    while (1)
    {
        getStrInput(expression);
        Queue *infixQueue = createQueue();
        int isValid = 1;
        isValid = tokenize(infixQueue, expression);
        // printQueue(infixQueue);
        if (isQueueEmpty(infixQueue) || !isValid)
        {
            freeQueue(infixQueue);
            continue;
        }
        Queue *postfixQueue = createQueue();
        infixToPostfix(infixQueue, postfixQueue);
        // printQueue(postfixQueue);
        char *result = (char *)malloc(100);
        postfixEvaluateMat(postfixQueue, result);

        drawTitle(2);
        for (int i = 0; i < matrixCount; i++)
        {
            if (strcmp(matrixList[i]->id, result) == 0)
            {
                printf("Result:\n");
                for (int j = 0; j < matrixList[i]->rows; j++)
                {
                    for (int k = 0; k < matrixList[i]->cols; k++)
                    {
                        printf("%-10.2f", matrixList[i]->matrix[j][k]);
                    }
                    printf("\n");
                }
                drawLine();
                break;
            }
        }

        freeQueue(infixQueue);
        freeQueue(postfixQueue);
        free(result);
    }
}
void createIdentityMatrix(int row, int col, char *name)
{
    double **matrix = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (double *)malloc(col * sizeof(double));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 1);
    strcpy(matrixList[matrixCount]->id, name);
    matrixList[matrixCount]->rows = row;
    matrixList[matrixCount]->cols = col;
    matrixList[matrixCount]->matrix = matrix;
    matrixCount++;
}
void matrixMulScalar(char *name, double scalar, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    double **result = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        result[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 2);
    strcpy(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, "*");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}
void matrixDivScalar(char *name, double scalar, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    double **result = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        result[i] = (double *)malloc(cols * sizeof(double));
    }
    if (scalar == 0)
    {
        printf("Error: Division by zero\n");
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix[i][j] / scalar;
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 2);
    strcpy(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, "/");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}

void matrixAdd(char *name1, char *name2, char *resMatrix)
{
    double **matrix1;
    double **matrix2;
    int rows1, cols1, rows2, cols2;
    getMatrix(name1, &matrix1, &rows1, &cols1);
    getMatrix(name2, &matrix2, &rows2, &cols2);
    if (rows1 != rows2 || cols1 != cols2)
    {
        printf("Error: Matrix dimensions do not match\n");
        return;
    }
    double **result = (double **)malloc(rows1 * sizeof(double *));
    for (int i = 0; i < rows1; i++)
    {
        result[i] = (double *)malloc(cols1 * sizeof(double));
    }
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name1) + strlen(name2) + 2);
    strcpy(matrixList[matrixCount]->id, name1);
    strcat(matrixList[matrixCount]->id, "+");
    strcat(matrixList[matrixCount]->id, name2);
    matrixList[matrixCount]->rows = rows1;
    matrixList[matrixCount]->cols = cols1;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}
void matrixSub(char *name1, char *name2, char *resMatrix)
{
    double **matrix1;
    double **matrix2;
    int rows1, cols1, rows2, cols2;
    getMatrix(name1, &matrix1, &rows1, &cols1);
    getMatrix(name2, &matrix2, &rows2, &cols2);
    if (rows1 != rows2 || cols1 != cols2)
    {
        printf("Error: Matrix dimensions do not match\n");
        return;
    }
    double **result = (double **)malloc(rows1 * sizeof(double *));
    for (int i = 0; i < rows1; i++)
    {
        result[i] = (double *)malloc(cols1 * sizeof(double));
    }
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name1) + strlen(name2) + 2);
    strcpy(matrixList[matrixCount]->id, name1);
    strcat(matrixList[matrixCount]->id, "-");
    strcat(matrixList[matrixCount]->id, name2);
    matrixList[matrixCount]->rows = rows1;
    matrixList[matrixCount]->cols = cols1;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}
void matrixMul(char *name1, char *name2, char *resMatrix)
{
    double **matrix1;
    double **matrix2;
    int rows1, cols1, rows2, cols2;
    getMatrix(name1, &matrix1, &rows1, &cols1);
    getMatrix(name2, &matrix2, &rows2, &cols2);
    if (cols1 != rows2)
    {
        printf("Error: Matrix dimensions do not match\n");
        return;
    }
    double **result = (double **)malloc(rows1 * sizeof(double *));
    for (int i = 0; i < rows1; i++)
    {
        result[i] = (double *)malloc(cols2 * sizeof(double));
    }
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name1) + strlen(name2) + 2);
    strcpy(matrixList[matrixCount]->id, name1);
    strcat(matrixList[matrixCount]->id, "*");
    strcat(matrixList[matrixCount]->id, name2);
    matrixList[matrixCount]->rows = rows1;
    matrixList[matrixCount]->cols = cols2;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}

void matrixTranspose(char *name, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    double **result = (double **)malloc(cols * sizeof(double *));
    for (int i = 0; i < cols; i++)
    {
        result[i] = (double *)malloc(rows * sizeof(double));
    }
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            result[i][j] = matrix[j][i];
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 2);
    strcpy(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, "T");
    matrixList[matrixCount]->rows = cols;
    matrixList[matrixCount]->cols = rows;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}

void matrixInverse(char *name, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    if (rows != cols)
    {
        printf("Error: Matrix is not square\n");
        return;
    }
    double **result = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        result[i] = (double *)malloc(cols * sizeof(double));
    }
    double **temp = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        temp[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = matrix[i][j];
            if (i == j)
            {
                result[i][j] = 1;
            }
            else
            {
                result[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        double pivot = temp[i][i];
        if (pivot == 0)
        {
            printf("Error: Matrix is singular\n");
            return;
        }
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] /= pivot;
            result[i][j] /= pivot;
        }
        for (int j = 0; j < rows; j++)
        {
            if (i != j)
            {
                double factor = temp[j][i];
                for (int k = 0; k < cols; k++)
                {
                    temp[j][k] -= factor * temp[i][k];
                    result[j][k] -= factor * result[i][k];
                }
            }
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 4);
    strcpy(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, "^-1");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}

void matrixRRF(char *name, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    double **result = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        result[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        double pivot = result[i][i];
        if (pivot == 0)
        {
            printf("Error: Matrix is singular\n");
            return;
        }
        for (int j = 0; j < cols; j++)
        {
            result[i][j] /= pivot;
        }
        for (int j = i + 1; j < rows; j++)
        {
            double factor = result[j][i];
            for (int k = 0; k < cols; k++)
            {
                result[j][k] -= factor * result[i][k];
            }
        }
    }
    for (int i = rows - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            double factor = result[j][i];
            for (int k = 0; k < cols; k++)
            {
                result[j][k] -= factor * result[i][k];
            }
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 4);
    strcpy(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, "RRF");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}

void matrixRREF(char *name, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    double **result = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        result[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        double pivot = result[i][i];
        if (pivot == 0)
        {
            printf("Error: Matrix is singular\n");
            return;
        }
        for (int j = 0; j < cols; j++)
        {
            result[i][j] /= pivot;
        }
        for (int j = 0; j < rows; j++)
        {
            if (i != j)
            {
                double factor = result[j][i];
                for (int k = 0; k < cols; k++)
                {
                    result[j][k] -= factor * result[i][k];
                }
            }
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 5);
    strcpy(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, "RREF");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = result;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}

void matrixDet(char *name, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    if (rows != cols)
    {
        printf("Error: Matrix is not square\n");
        return;
    }
    double **temp = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        temp[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = matrix[i][j];
        }
    }
    double det = 1;
    for (int i = 0; i < rows; i++)
    {
        double pivot = temp[i][i];
        if (pivot == 0)
        {
            printf("Error: Matrix is singular\n");
            return;
        }
        det *= pivot;
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] /= pivot;
        }
        for (int j = i + 1; j < rows; j++)
        {
            double factor = temp[j][i];
            for (int k = 0; k < cols; k++)
            {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        free(temp[i]);
    }
    free(temp);
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 4);
    strcpy(matrixList[matrixCount]->id, "det(");
    strcat(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, ")");
    matrixList[matrixCount]->rows = 1;
    matrixList[matrixCount]->cols = 1;
    matrixList[matrixCount]->matrix = (double **)malloc(sizeof(double *));
    matrixList[matrixCount]->matrix[0] = (double *)malloc(sizeof(double));
    matrixList[matrixCount]->matrix[0][0] = det;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}
void matrixRank(char *name, char *resMatrix)
{
    double **matrix;
    int rows, cols;
    getMatrix(name, &matrix, &rows, &cols);
    double **temp = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        temp[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        double pivot = temp[i][i];
        if (pivot == 0)
        {
            printf("Error: Matrix is singular\n");
            return;
        }
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] /= pivot;
        }
        for (int j = i + 1; j < rows; j++)
        {
            double factor = temp[j][i];
            for (int k = 0; k < cols; k++)
            {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }
    int rank = 0;
    for (int i = 0; i < rows; i++)
    {
        int allZero = 1;
        for (int j = 0; j < cols; j++)
        {
            if (temp[i][j] != 0)
            {
                allZero = 0;
                break;
            }
        }
        if (!allZero)
        {
            rank++;
        }
    }
    for (int i = 0; i < rows; i++)
    {
        free(temp[i]);
    }
    free(temp);
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(strlen(name) + 5);
    strcpy(matrixList[matrixCount]->id, "rank(");
    strcat(matrixList[matrixCount]->id, name);
    strcat(matrixList[matrixCount]->id, ")");
    matrixList[matrixCount]->rows = 1;
    matrixList[matrixCount]->cols = 1;
    matrixList[matrixCount]->matrix = (double **)malloc(sizeof(double *));
    matrixList[matrixCount]->matrix[0] = (double *)malloc(sizeof(double));
    matrixList[matrixCount]->matrix[0][0] = rank;
    strcpy(resMatrix, matrixList[matrixCount]->id);
    matrixCount++;
}
void postfixEvaluateMat(Queue *postfix, char *result)
{
    Stack *s = createStack();
    while (!isQueueEmpty(postfix))
    {
        char *token = deQueue(postfix);

        if (isFunction(token))
        {
            char *resMatrix = (char *)malloc(100);
            if (strcmp(token, "inv") == 0 || strcmp(token, "tra") == 0 || strcmp(token, "rrf") == 0 ||
                strcmp(token, "rref") == 0 || strcmp(token, "rank") == 0 || strcmp(token, "det") == 0)
            {
                char *name = pop(s);
                if (strcmp(token, "inv") == 0)
                {
                    matrixInverse(name, resMatrix);
                }
                else if (strcmp(token, "tra") == 0)
                {
                    matrixTranspose(name, resMatrix);
                }
                else if (strcmp(token, "rrf") == 0)
                {
                    matrixRRF(name, resMatrix);
                }
                else if (strcmp(token, "rref") == 0)
                {
                    matrixRREF(name, resMatrix);
                }
                else if (strcmp(token, "rank") == 0)
                {
                    matrixRank(name, resMatrix);
                }
                else if (strcmp(token, "det") == 0)
                {
                    matrixDet(name, resMatrix);
                }
                push(s, resMatrix);
                free(name);
            }
            else
            {
                char *op2 = pop(s);
                char *op1 = pop(s);
                if (isMatrix(op1) && isMatrix(op2))
                {
                    if (strcmp(token, "+") == 0)
                    {
                        matrixAdd(op1, op2, resMatrix);
                    }
                    else if (strcmp(token, "-") == 0)
                    {
                        matrixSub(op1, op2, resMatrix);
                    }
                    else if (strcmp(token, "*") == 0)
                    {
                        matrixMul(op1, op2, resMatrix);
                    }
                }
                else if (isMatrix(op1) && !isMatrix(op2))
                {
                    double scalar = atof(op2);
                    if (strcmp(token, "*") == 0)
                    {
                        matrixMulScalar(op1, scalar, resMatrix);
                    }
                    else if (strcmp(token, "/") == 0)
                    {
                        matrixDivScalar(op1, scalar, resMatrix);
                    }
                    else if (strcmp(token, "+") == 0)
                    {
                        char *name = (char *)malloc(100);
                        createIdentityMatrix(matrixList[matrixCount]->rows, matrixList[matrixCount]->cols, "I");
                        matrixMulScalar("I", scalar, name);

                        matrixAdd(op1, name, resMatrix);
                        free(name);
                    }
                    else if (strcmp(token, "-") == 0)
                    {
                        char *name = (char *)malloc(100);
                        createIdentityMatrix(matrixList[matrixCount]->rows, matrixList[matrixCount]->cols, "I");
                        matrixMulScalar("I", scalar, name);

                        matrixSub(op1, name, resMatrix);
                        free(name);
                    }
                }
                else if (!isMatrix(op1) && isMatrix(op2))
                {
                    double scalar = atof(op1);
                    if (strcmp(token, "*") == 0)
                    {
                        matrixMulScalar(op2, scalar, resMatrix);
                    }
                    else if (strcmp(token, "/") == 0)
                    {
                        matrixDivScalar(op2, scalar, resMatrix);
                    }
                    else if (strcmp(token, "+") == 0)
                    {
                        char *name = (char *)malloc(100);
                        createIdentityMatrix(matrixList[matrixCount]->rows, matrixList[matrixCount]->cols, "I");
                        matrixMulScalar("I", scalar, name);

                        matrixAdd(op2, name, resMatrix);
                        free(name);
                    }
                    else if (strcmp(token, "-") == 0)
                    {
                        char *name = (char *)malloc(100);
                        createIdentityMatrix(matrixList[matrixCount]->rows, matrixList[matrixCount]->cols, "I");
                        matrixMulScalar("I", scalar, name);

                        matrixSub(op2, name, resMatrix);
                        free(name);
                    }
                }
                else
                {
                    double res = 0;
                    double val1 = atof(op1);
                    double val2 = atof(op2);
                    if (strcmp(token, "+") == 0)
                    {
                        res = val1 + val2;
                    }
                    else if (strcmp(token, "-") == 0)
                    {
                        res = val1 - val2;
                    }
                    else if (strcmp(token, "*") == 0)
                    {
                        res = val1 * val2;
                    }
                    else if (strcmp(token, "/") == 0)
                    {
                        res = val1 / val2;
                    }
                    char *resultStr = (char *)malloc(100);
                    sprintf(resultStr, "%lf", res);
                    push(s, resultStr);
                }
                free(op1);
                free(op2);
            }
            char *resultStr = (char *)malloc(100);
            strcpy(resultStr, resMatrix);
            push(s, resultStr);
            free(resMatrix);
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
void lu()
{
    setMatrix();

    double **matrix;
    int rows, cols;
    getMatrix("A", &matrix, &rows, &cols);
    double **L = (double **)malloc(rows * sizeof(double *));
    double **U = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        L[i] = (double *)malloc(cols * sizeof(double));
        U[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }
    for (int i = 0; i < rows; i++)
    {
        L[i][i] = 1;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = matrix[i][j] - sum;
        }
        for (int j = i + 1; j < rows; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = (matrix[j][i] - sum) / U[i][i];
        }
    }
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(2);
    strcpy(matrixList[matrixCount]->id, "L");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = L;
    matrixCount++;
    matrixList[matrixCount] = (Matrix *)malloc(sizeof(Matrix));
    matrixList[matrixCount]->id = (char *)malloc(2);
    strcpy(matrixList[matrixCount]->id, "U");
    matrixList[matrixCount]->rows = rows;
    matrixList[matrixCount]->cols = cols;
    matrixList[matrixCount]->matrix = U;
    matrixCount++;
    drawTitle(2);
    printf("Matrix L:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%-10.2f", L[i][j]);
        }
        printf("\n");
    }
    drawLine();
    printf("Matrix U:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%-10.2f", U[i][j]);
        }
        printf("\n");
    }
    drawLine();
    luMode = 0;
}