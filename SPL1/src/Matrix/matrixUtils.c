#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

MatrixNode *matrixList = NULL;
int matrixListSize = 0;

MatrixNode *mainMatrixList = NULL;
int mainMatrixListSize = 0;

int isMatrix(char *id)
{
    for (int i = 0; i < matrixListSize; i++)
    {
        if (strcmp(matrixList[i].id, id) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int validateMatrixName(char *id)
{
    if (strcmp(id, "I") == 0 || strcmp(id, "U") == 0 || strcmp(id, "R") == 0 || strcmp(id, "Q") == 0 || strcmp(id, "L") == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void setMatrix()
{
    drawTitle(3);
    char id[MAX_INPUT_SIZE];
    printf("Enter matrix name: ");
    getStrInput(id);
    checkInput(id);
    if (isMatrix(id))
    {
        printf("Matrix name already exists or invalid name\n");
        return;
    }
    if (!validateMatrixName(id))
    {
        printf("Invalid matrix name\n");
        return;
    }
    int rows, cols;
    printf("Enter number of rows: ");
    char str[MAX_INPUT_SIZE];
    getStrInput(str);
    checkInput(str);
    rows = atoi(str);
    if (rows <= 0)
    {
        printf("Number of rows must be positive\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    printf("Enter number of columns: ");
    getStrInput(str);
    checkInput(str);
    cols = atoi(str);
    if (cols <= 0)
    {
        printf("Number of columns must be positive\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }

    Matrix *matrix = createMatrix(rows, cols);
    if (!matrix)
    {
        printf("Memory allocation failed\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }

    saveMatrix(id, matrix);
    saveMainMatrix(id, matrix);
    fillMatrix(matrix);
}

void fillMatrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->matrix[i][j] = 0;
        }
    }
    int highLightRow = 0;
    int highLightCol = 0;
    while (1)
    {
        displayMatrix(matrix, highLightRow, highLightCol);
        printf("Enter value for element [%d][%d]: ", highLightRow + 1, highLightCol + 1);
        char str[MAX_INPUT_SIZE];
        getStrInput(str);
        checkInput(str);
        matrix->matrix[highLightRow][highLightCol] = atof(str);
        if (highLightCol == matrix->cols - 1)
        {
            if (highLightRow == matrix->rows - 1)
            {
                break;
            }
            highLightRow++;
            highLightCol = 0;
        }
        else
        {
            highLightCol++;
        }
    }
    displayMatrix(matrix, -1, -1);
    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;
}

void displayMatrix(Matrix *matrix, int highLightRow, int highLightCol)
{
    drawTitle(3);
    printf("Matrix: %s\n", matrixList[matrixListSize - 1].id);
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            if (i == highLightRow && j == highLightCol)
            {
                printf("\033[1;31m");
            }
            printf("%s   ", modifyDouble(matrix->matrix[i][j]));
            printf("\033[0m");
        }
        printf("\n");
    }
    drawLine();
}

void showMatrix()
{
    drawTitle(3);
    char id[MAX_INPUT_SIZE];
    printf("Enter matrix name: ");
    getStrInput(id);
    checkInput(id);
    if (!isMatrix(id))
    {
        printf("Matrix not found\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    Matrix matrix = getMatrix(id);
    if (matrix.matrix == NULL)
    {
        printf("Matrix not found\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    drawTitle(3);
    printf("Matrix: %s\n", id);
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            printf("%s   ", modifyDouble(matrix.matrix[i][j]));
        }
        printf("\n");
    }

    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;
}

void showAllMatrix()
{
    drawTitle(3);
    for (int i = 0; i < mainMatrixListSize; i++)
    {
        Matrix matrix = *mainMatrixList[i].matrix;
        printf("Matrix: %s\n", mainMatrixList[i].id);
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                printf("%-10s", modifyDouble(matrix.matrix[i][j]));
            }
            printf("\n");
        }
        printf("\n");
        drawLine();
    }
    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;
}
void freeMatrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
}

void clearMatrix()
{
    drawTitle(3);
    char id[MAX_INPUT_SIZE];
    printf("Enter matrix name: ");
    getStrInput(id);
    checkInput(id);
    if (!isMatrix(id))
    {
        printf("Matrix not found\n");
        return;
    }
    removeMatrix(id);
}

void clearAllMatrix()
{
    for (int i = 0; i < matrixListSize; i++)
    {
        free(matrixList[i].id);
        if (i < mainMatrixListSize)
        {
            free(mainMatrixList[i].id);
        }
        freeMatrix(matrixList[i].matrix);
    }
    matrixListSize = 0;
    mainMatrixListSize = 0;
    free(matrixList);
    free(mainMatrixList);
}

Matrix *createMatrix(int rows, int cols)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (!matrix)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = (double **)malloc(rows * sizeof(double *));
    if (!matrix->matrix)
    {
        printf("Memory allocation failed\n");
        free(matrix);
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        matrix->matrix[i] = (double *)malloc(cols * sizeof(double));
        if (!matrix->matrix[i])
        {
            printf("Memory allocation failed\n");
            for (int j = 0; j < i; j++)
            {
                free(matrix->matrix[j]);
            }
            free(matrix->matrix);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
Matrix getMatrix(char *id)
{
    for (int i = 0; i < matrixListSize; i++)
    {
        if (strcmp(matrixList[i].id, id) == 0)
        {
            return *matrixList[i].matrix;
        }
    }
    Matrix matrix;
    matrix.rows = 0;
    matrix.cols = 0;
    matrix.matrix = NULL;
    return matrix;
}

void saveMatrix(char *id, Matrix *matrix)
{
    matrixListSize++;
    matrixList = (MatrixNode *)realloc(matrixList, matrixListSize * sizeof(MatrixNode));
    if (!matrixList)
    {
        printf("Memory allocation failed\n");
        freeMatrix(matrix);
        free(matrix);
        matrixListSize--;
        return;
    }

    matrixList[matrixListSize - 1].id = (char *)malloc(strlen(id) + 1);
    if (!matrixList[matrixListSize - 1].id)
    {
        printf("Memory allocation failed\n");
        freeMatrix(matrix);
        free(matrix);
        matrixListSize--;
        return;
    }

    strcpy(matrixList[matrixListSize - 1].id, id);
    matrixList[matrixListSize - 1].matrix = matrix;
}
void saveMainMatrix(char *id, Matrix *matrix)
{
    mainMatrixListSize++;
    mainMatrixList = (MatrixNode *)realloc(mainMatrixList, mainMatrixListSize * sizeof(MatrixNode));
    if (!mainMatrixList)
    {
        printf("Memory allocation failed\n");
        freeMatrix(matrix);
        free(matrix);
        mainMatrixListSize--;
        return;
    }

    mainMatrixList[mainMatrixListSize - 1].id = (char *)malloc(strlen(id) + 1);
    if (!mainMatrixList[mainMatrixListSize - 1].id)
    {
        printf("Memory allocation failed\n");
        freeMatrix(matrix);
        free(matrix);
        mainMatrixListSize--;
        return;
    }

    strcpy(mainMatrixList[mainMatrixListSize - 1].id, id);
    mainMatrixList[mainMatrixListSize - 1].matrix = matrix;
}

void removeMatrix(char *id)
{
    for (int i = 0; i < matrixListSize; i++)
    {
        if (strcmp(matrixList[i].id, id) == 0)
        {
            free(matrixList[i].id);

            for (int j = 0; j < matrixList[i].matrix->rows; j++)
            {
                free(matrixList[i].matrix->matrix[j]);
            }
            free(matrixList[i].matrix->matrix);
            free(matrixList[i].matrix);

            for (int j = i; j < matrixListSize - 1; j++)
            {
                matrixList[j] = matrixList[j + 1];
            }
            matrixListSize--;

            if (matrixListSize > 0)
            {
                matrixList = (MatrixNode *)realloc(matrixList, matrixListSize * sizeof(MatrixNode));
            }
            else
            {
                free(matrixList);
                matrixList = NULL;
            }

            printf("Matrix '%s' has been cleared\n", id);
        }
    }

    for (int i = 0; i < mainMatrixListSize; i++)
    {
        if (strcmp(mainMatrixList[i].id, id) == 0)
        {
            free(mainMatrixList[i].id);

            for (int j = 0; j < mainMatrixList[i].matrix->rows; j++)
            {
                free(mainMatrixList[i].matrix->matrix[j]);
            }
            free(mainMatrixList[i].matrix->matrix);
            free(mainMatrixList[i].matrix);

            for (int j = i; j < mainMatrixListSize - 1; j++)
            {
                mainMatrixList[j] = mainMatrixList[j + 1];
            }
            mainMatrixListSize--;

            if (mainMatrixListSize > 0)
            {
                mainMatrixList = (MatrixNode *)realloc(mainMatrixList, mainMatrixListSize * sizeof(MatrixNode));
            }
            else
            {
                free(mainMatrixList);
                mainMatrixList = NULL;
            }

            printf("Matrix '%s' has been cleared from main list\n", id);
            printf("Press Enter to continue...");
            while (getchar() != '\n')
                ;
            return;
        }
    }

    printf("Matrix '%s' not found\n", id);
    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;
}

Matrix *createIdentityMatrix(int size)
{
    Matrix *matrix = createZeroMatrix(size, size);
    if (!matrix)
    {
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        matrix->matrix[i][i] = 1;
    }
    return matrix;
}

Matrix *createZeroMatrix(int rows, int cols)
{
    Matrix *matrix = createMatrix(rows, cols);
    if (!matrix)
    {
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix->matrix[i][j] = 0;
        }
    }
    return matrix;
}

void matrixReset()
{
    clearAllMatrix();
    clearScreen();
}

void postfixEvaluateMat(Queue *postfix, char *result)
{
    Stack *s = createStack();
    while (!isQueueEmpty(postfix))
    {
        char *token = deQueue(postfix);
        if (isFunction(token))
        {
            if (strcmp(token, "inv") == 0 || strcmp(token, "tra") == 0 || strcmp(token, "ref") == 0 ||
                strcmp(token, "rref") == 0 || strcmp(token, "det") == 0)
            {
                char *id = pop(s);
                if (!id)
                {
                    printf("Invalid expression\n");
                    free(token);
                    freeStack(s);
                    return;
                }

                if (!isMatrix(id))
                {
                    printf("Matrix '%s' not found\n", id);
                    free(id);
                    free(token);
                    freeStack(s);
                    return;
                }

                Matrix matrix = getMatrix(id);
                if (matrix.matrix == NULL)
                {
                    printf("Matrix '%s' not found\n", id);
                    free(id);
                    free(token);
                    freeStack(s);
                    return;
                }

                char *resMatId = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
                if (!resMatId)
                {
                    printf("Memory allocation failed\n");
                    free(id);
                    free(token);
                    freeStack(s);
                    return;
                }

                if (strcmp(token, "inv") == 0)
                {
                    Matrix *inverse = matrixInverse(&matrix);
                    if (!inverse)
                    {
                        free(resMatId);
                        free(id);
                        free(token);
                        freeStack(s);
                        return;
                    }
                    char newId[MAX_INPUT_SIZE];
                    sprintf(newId, "inv(%s)", id);
                    saveMatrix(newId, inverse);
                    strcpy(resMatId, newId);
                }

                else if (strcmp(token, "tra") == 0)
                {
                    Matrix *transpose = matrixTranspose(&matrix);
                    if (!transpose)
                    {
                        free(resMatId);
                        free(id);
                        free(token);
                        freeStack(s);
                        return;
                    }
                    char newId[MAX_INPUT_SIZE];
                    sprintf(newId, "tra(%s)", id);
                    saveMatrix(newId, transpose);
                    strcpy(resMatId, newId);
                }
                else if (strcmp(token, "ref") == 0)
                {
                    Matrix *rowEchelonForm = matrixRowEchelonForm(&matrix);
                    if (!rowEchelonForm)
                    {
                        free(resMatId);
                        free(id);
                        free(token);
                        freeStack(s);
                        return;
                    }
                    char newId[MAX_INPUT_SIZE];
                    sprintf(newId, "ref(%s)", id);
                    saveMatrix(newId, rowEchelonForm);
                    strcpy(resMatId, newId);
                }
                else if (strcmp(token, "rref") == 0)
                {
                    Matrix *reducedRowEchelonForm = matrixReducedRowEchelonForm(&matrix);
                    if (!reducedRowEchelonForm)
                    {
                        free(resMatId);
                        free(id);
                        free(token);
                        freeStack(s);
                        return;
                    }
                    char newId[MAX_INPUT_SIZE];
                    sprintf(newId, "rref(%s)", id);
                    saveMatrix(newId, reducedRowEchelonForm);
                    strcpy(resMatId, newId);
                }
                else if (strcmp(token, "det") == 0)
                {
                    double det = matrixDeterminant(&matrix);
                    sprintf(resMatId, "%s", modifyDouble(det));
                }

                push(s, resMatId);
                free(id);
            }
            else
            {
                char *id2 = pop(s);
                char *id1 = pop(s);

                if (!id1 || !id2)
                {
                    printf("Invalid expression\n");
                    free(token);
                    if (id1)
                        free(id1);
                    if (id2)
                        free(id2);
                    freeStack(s);
                    return;
                }

                char *resMatId = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
                if (!resMatId)
                {
                    printf("Memory allocation failed\n");
                    free(id1);
                    free(id2);
                    free(token);
                    freeStack(s);
                    return;
                }

                if (isMatrix(id1) && isMatrix(id2))
                {
                    if (strcmp(token, "+") == 0)
                    {
                        Matrix matrix1 = getMatrix(id1);
                        Matrix matrix2 = getMatrix(id2);
                        if (matrix1.matrix == NULL || matrix2.matrix == NULL)
                        {
                            printf("Matrix not found\n");
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        Matrix *resMatrix = matrixAdd(&matrix1, &matrix2);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s+%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }

                    else if (strcmp(token, "-") == 0)
                    {
                        Matrix matrix1 = getMatrix(id1);
                        Matrix matrix2 = getMatrix(id2);
                        if (matrix1.matrix == NULL || matrix2.matrix == NULL)
                        {
                            printf("Matrix not found\n");
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        Matrix *resMatrix = matrixSubtract(&matrix1, &matrix2);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s-%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }
                    else if (strcmp(token, "*") == 0)
                    {
                        Matrix matrix1 = getMatrix(id1);
                        Matrix matrix2 = getMatrix(id2);
                        if (matrix1.matrix == NULL || matrix2.matrix == NULL)
                        {
                            printf("Matrix not found\n");
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        Matrix *resMatrix = matrixMultiply(&matrix1, &matrix2);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s*%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }
                }
                else if (isMatrix(id1) && !isMatrix(id2))
                {
                    double scalar = atof(id2);
                    Matrix matrix = getMatrix(id1);
                    if (matrix.matrix == NULL)
                    {
                        printf("Matrix not found\n");
                        free(resMatId);
                        free(id1);
                        free(id2);
                        free(token);
                        freeStack(s);
                        return;
                    }
                    if (strcmp(token, "*") == 0)
                    {
                        Matrix *resMatrix = matrixScalarMultiply(&matrix, scalar);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s*%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }
                    else if (strcmp(token, "/") == 0)
                    {
                        if (scalar == 0)
                        {
                            printf("Cannot divide by zero\n");
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        Matrix *resMatrix = matrixScalarDivide(&matrix, scalar);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s/%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }
                    else if (strcmp(token, "^") == 0)
                    {
                        Matrix *resMatrix = matrixPower(&matrix, (int)scalar);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s^%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }
                }
                else if (!isMatrix(id1) && isMatrix(id2))
                {
                    double scalar = atof(id1);
                    Matrix matrix = getMatrix(id2);
                    if (matrix.matrix == NULL)
                    {
                        printf("Matrix not found\n");
                        free(resMatId);
                        free(id1);
                        free(id2);
                        free(token);
                        freeStack(s);
                        return;
                    }
                    if (strcmp(token, "*") == 0)
                    {
                        Matrix *resMatrix = matrixScalarMultiply(&matrix, scalar);
                        if (!resMatrix)
                        {
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        char newId[MAX_INPUT_SIZE];
                        sprintf(newId, "(%s*%s)", id1, id2);
                        saveMatrix(newId, resMatrix);
                        strcpy(resMatId, newId);
                    }
                }
                else
                {
                    double scalar1 = atof(id1);
                    double scalar2 = atof(id2);
                    double res;

                    if (strcmp(token, "+") == 0)
                    {
                        res = scalar1 + scalar2;
                    }
                    else if (strcmp(token, "-") == 0)
                    {
                        res = scalar1 - scalar2;
                    }
                    else if (strcmp(token, "*") == 0)
                    {
                        res = scalar1 * scalar2;
                    }
                    else if (strcmp(token, "/") == 0)
                    {
                        if (scalar2 == 0)
                        {
                            printf("Cannot divide by zero\n");
                            free(resMatId);
                            free(id1);
                            free(id2);
                            free(token);
                            freeStack(s);
                            return;
                        }
                        res = scalar1 / scalar2;
                    }
                    else if (strcmp(token, "^") == 0)
                    {
                        res = pow(scalar1, scalar2);
                    }
                    sprintf(resMatId, "%s", modifyDouble(res));
                }

                push(s, resMatId);
                free(id1);
                free(id2);
            }
        }
        else
        {
            push(s, token);
        }

        if (isFunction(token))
        {
            free(token);
        }
    }

    char *finalResult = pop(s);
    if (!finalResult)
    {
        printf("Invalid expression\n");
        freeStack(s);
        return;
    }

    strcpy(result, finalResult);
    free(finalResult);
    freeStack(s);
}