#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

Matrix *matrixAdd(Matrix *matrix1, Matrix *matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        printf("Matrix dimensions do not match\n");
        return NULL;
    }
    Matrix *result = createMatrix(matrix1->rows, matrix1->cols);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix1->rows; i++)
    {
        for (int j = 0; j < matrix1->cols; j++)
        {
            result->matrix[i][j] = matrix1->matrix[i][j] + matrix2->matrix[i][j];
        }
    }
    return result;
}

Matrix *matrixSubtract(Matrix *matrix1, Matrix *matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        printf("Matrix dimensions do not match\n");
        return NULL;
    }
    Matrix *result = createMatrix(matrix1->rows, matrix1->cols);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix1->rows; i++)
    {
        for (int j = 0; j < matrix1->cols; j++)
        {
            result->matrix[i][j] = matrix1->matrix[i][j] - matrix2->matrix[i][j];
        }
    }
    return result;
}

Matrix *matrixMultiply(Matrix *matrix1, Matrix *matrix2)
{
    if (matrix1->cols != matrix2->rows)
    {
        printf("Matrix dimensions do not match\n");
        return NULL;
    }
    Matrix *result = createMatrix(matrix1->rows, matrix2->cols);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix1->rows; i++)
    {
        for (int j = 0; j < matrix2->cols; j++)
        {
            result->matrix[i][j] = 0;
            for (int k = 0; k < matrix1->cols; k++)
            {
                result->matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
            }
        }
    }
    return result;
}

double matrixDeterminant(Matrix *matrix)
{
    if (matrix->rows != matrix->cols)
    {
        printf("Matrix is not square\n");
        return 0;
    }
    if (matrix->rows == 1)
    {
        return matrix->matrix[0][0];
    }
    if (matrix->rows == 2)
    {
        return matrix->matrix[0][0] * matrix->matrix[1][1] - matrix->matrix[0][1] * matrix->matrix[1][0];
    }
    double det = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        Matrix *minor = createMatrix(matrix->rows - 1, matrix->cols - 1);
        if (!minor)
        {
            return 0;
        }
        for (int j = 1; j < matrix->rows; j++)
        {
            for (int k = 0; k < matrix->cols; k++)
            {
                if (k < i)
                {
                    minor->matrix[j - 1][k] = matrix->matrix[j][k];
                }
                else if (k > i)
                {
                    minor->matrix[j - 1][k - 1] = matrix->matrix[j][k];
                }
            }
        }
        double sign;
        if (i % 2 == 0)
        {
            sign = 1;
        }
        else
        {
            sign = -1;
        }
        det += sign * matrix->matrix[0][i] * matrixDeterminant(minor);
        freeMatrix(minor);
    }
    return det;
}

Matrix *matrixInverse(Matrix *matrix)
{
    if (matrix->rows != matrix->cols)
    {
        printf("Matrix is not square\n");
        return NULL;
    }
    double det = matrixDeterminant(matrix);
    if (det == 0)
    {
        printf("Matrix is singular\n");
        return NULL;
    }
    Matrix *result = createMatrix(matrix->rows, matrix->cols);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            Matrix *minor = createMatrix(matrix->rows - 1, matrix->cols - 1);
            if (!minor)
            {
                return NULL;
            }
            for (int k = 0; k < matrix->rows; k++)
            {
                if (k == i)
                {
                    continue;
                }
                for (int l = 0; l < matrix->cols; l++)
                {
                    if (l == j)
                    {
                        continue;
                    }
                    int row, col;
                    if (k < i)
                    {
                        row = k;
                    }
                    else
                    {
                        row = k - 1;
                    }
                    if (l < j)
                    {
                        col = l;
                    }
                    else
                    {
                        col = l - 1;
                    }
                    minor->matrix[row][col] = matrix->matrix[k][l];
                }
            }
            double sign = (i + j) % 2 == 0 ? 1 : -1;
            result->matrix[j][i] = sign * matrixDeterminant(minor) / det;
            freeMatrix(minor);
        }
    }
    return result;
}

Matrix *matrixDivide(Matrix *matrix1, Matrix *matrix2)
{
    Matrix *inverse = matrixInverse(matrix2);
    if (!inverse)
    {
        return NULL;
    }
    Matrix *result = matrixMultiply(matrix1, inverse);
    freeMatrix(inverse);
    return result;
}

Matrix *matrixPower(Matrix *matrix, int power)
{
    if (matrix->rows != matrix->cols)
    {
        printf("Matrix is not square\n");
        return NULL;
    }
    if (power < 0)
    {
        Matrix *inverse = matrixInverse(matrix);
        if (!inverse)
        {
            return NULL;
        }

        Matrix *result = createIdentityMatrix(matrix->rows);
        if (!result)
        {
            return NULL;
        }
        for (int i = 0; i < -power; i++)
        {
            Matrix *temp = matrixMultiply(result, inverse);
            freeMatrix(result);
            result = temp;
        }
        freeMatrix(inverse);
        return result;
    }
    else
    {
        Matrix *result = createIdentityMatrix(matrix->rows);
        if (!result)
        {
            return NULL;
        }
        for (int i = 0; i < power; i++)
        {
            Matrix *temp = matrixMultiply(result, matrix);
            freeMatrix(result);
            result = temp;
        }
        return result;
    }
}

Matrix *matrixTranspose(Matrix *matrix)
{
    Matrix *result = createMatrix(matrix->cols, matrix->rows);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            result->matrix[j][i] = matrix->matrix[i][j];
        }
    }
    return result;
}

Matrix *matrixScalarMultiply(Matrix *matrix, double scalar)
{
    Matrix *result = createMatrix(matrix->rows, matrix->cols);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            result->matrix[i][j] = matrix->matrix[i][j] * scalar;
        }
    }
    return result;
}

Matrix *matrixScalarDivide(Matrix *matrix, double scalar)
{
    if (scalar == 0)
    {
        printf("Cannot divide by zero\n");
        return NULL;
    }
    return matrixScalarMultiply(matrix, 1 / scalar);
}

Matrix *matrixRowEchelonForm(Matrix *matrix)
{
    Matrix *result = createMatrix(matrix->rows, matrix->cols);
    if (!result)
    {
        return NULL;
    }
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            result->matrix[i][j] = matrix->matrix[i][j];
        }
    }
    int lead = 0;
    for (int r = 0; r < result->rows; r++)
    {
        if (result->cols <= lead)
        {
            break;
        }
        int i = r;
        while (result->matrix[i][lead] == 0)
        {
            i++;
            if (result->rows == i)
            {
                i = r;
                lead++;
                if (result->cols == lead)
                {
                    break;
                }
            }
        }
        for (int j = 0; j < result->cols; j++)
        {
            double temp = result->matrix[r][j];
            result->matrix[r][j] = result->matrix[i][j];
            result->matrix[i][j] = temp;
        }
        double div = result->matrix[r][lead];
        for (int j = 0; j < result->cols; j++)
        {
            result->matrix[r][j] /= div;
        }
        for (int j = 0; j < result->rows; j++)
        {
            if (j == r)
            {
                continue;
            }
            double sub = result->matrix[j][lead];
            for (int k = 0; k < result->cols; k++)
            {
                result->matrix[j][k] -= sub * result->matrix[r][k];
            }
        }
        lead++;
    }
    return result;
}
Matrix *matrixReducedRowEchelonForm(Matrix *matrix)
{
    Matrix *result = matrixRowEchelonForm(matrix);
    if (!result)
    {
        return NULL;
    }
    int lead = 0;
    for (int r = 0; r < result->rows; r++)
    {
        if (result->cols <= lead)
        {
            break;
        }
        if (result->matrix[r][lead] == 0)
        {
            lead++;
            if (result->cols == lead)
            {
                break;
            }
        }
        double div = result->matrix[r][lead];
        for (int j = 0; j < result->cols; j++)
        {
            result->matrix[r][j] /= div;
        }
        for (int j = 0; j < result->rows; j++)
        {
            if (j == r)
            {
                continue;
            }
            double sub = result->matrix[j][lead];
            for (int k = 0; k < result->cols; k++)
            {
                result->matrix[j][k] -= sub * result->matrix[r][k];
            }
        }
        lead++;
    }
    return result;
}
int matrixRank(Matrix *matrix)
{
    Matrix *rowEchelonForm = matrixRowEchelonForm(matrix);
    if (!rowEchelonForm)
    {
        return -1;
    }
    int rank = 0;
    for (int i = 0; i < rowEchelonForm->rows; i++)
    {
        for (int j = 0; j < rowEchelonForm->cols; j++)
        {
            if (rowEchelonForm->matrix[i][j] != 0)
            {
                rank++;
                break;
            }
        }
    }
    freeMatrix(rowEchelonForm);
    return rank;
}

Matrix *matrixAddScalar(Matrix *matrix, double scalar)
{
    if (matrix->cols != matrix->rows)
    {
        printf("Matrix is not square\n");
        return NULL;
    }
    Matrix *result = createMatrix(matrix->rows, matrix->cols);
    if (!result)
    {
        return NULL;
    }

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            if (i == j)
            {
                result->matrix[i][j] = matrix->matrix[i][j] + scalar;
            }
            else
            {
                result->matrix[i][j] = matrix->matrix[i][j];
            }
        }
    }
    return result;
}

Matrix *matrixSubtractScalar(Matrix *matrix, double scalar)
{
    if (matrix->cols != matrix->rows)
    {
        printf("Matrix is not square\n");
        return NULL;
    }
    Matrix *result = createMatrix(matrix->rows, matrix->cols);
    if (!result)
    {
        return NULL;
    }

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            if (i == j)
            {
                result->matrix[i][j] = matrix->matrix[i][j] - scalar;
            }
            else
            {
                result->matrix[i][j] = matrix->matrix[i][j];
            }
        }
    }
    return result;
}
void luDecomposition()
{
    drawTitle(3);
    printf("Enter matrix name: ");
    char id[MAX_INPUT_SIZE];
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
    if (matrix.rows != matrix.cols)
    {
        printf("Matrix is not square\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }
    Matrix *l = createIdentityMatrix(matrix.rows);
    if (!l)
    {
        return;
    }
    Matrix *u = createZeroMatrix(matrix.rows, matrix.cols);
    if (!u)
    {
        freeMatrix(l);
        return;
    }
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = i; j < matrix.cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += l->matrix[i][k] * u->matrix[k][j];
            }
            u->matrix[i][j] = matrix.matrix[i][j] - sum;
        }
        for (int j = i + 1; j < matrix.rows; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += l->matrix[j][k] * u->matrix[k][i];
            }
            l->matrix[j][i] = (matrix.matrix[j][i] - sum) / u->matrix[i][i];
        }
    }
    drawTitle(3);
    printf("Matrix: %s\n", id);
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            printf("%-10s", modifyDouble(matrix.matrix[i][j]));
        }
        printf("\n");
    }
    drawLine();
    printf("L:\n");
    for (int i = 0; i < l->rows; i++)
    {
        for (int j = 0; j < l->cols; j++)
        {
            printf("%-10s", modifyDouble(l->matrix[i][j]));
        }
        printf("\n");
    }
    drawLine();
    printf("U:\n");
    for (int i = 0; i < u->rows; i++)
    {
        for (int j = 0; j < u->cols; j++)
        {
            printf("%-10s", modifyDouble(u->matrix[i][j]));
        }
        printf("\n");
    }
    drawLine();
    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;
    freeMatrix(l);
    freeMatrix(u);
}

void qrDecomposition()
{
    drawTitle(3);
    printf("Enter matrix name: ");
    char id[MAX_INPUT_SIZE];
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

    int m = matrix.rows;
    int n = matrix.cols;

    Matrix *Q = createZeroMatrix(m, n);
    Matrix *R = createZeroMatrix(n, n);

    if (!Q || !R)
    {
        if (Q)
            freeMatrix(Q);
        if (R)
            freeMatrix(R);
        printf("Memory allocation failed\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n')
            ;
        return;
    }

    // Gram-Schmidt Process
    for (int j = 0; j < n; j++)
    {
        // Copy column j from matrix to vector v
        for (int i = 0; i < m; i++)
        {
            Q->matrix[i][j] = matrix.matrix[i][j];
        }

        for (int k = 0; k < j; k++)
        {
            double dot = 0.0;
            for (int i = 0; i < m; i++)
            {
                dot += Q->matrix[i][k] * matrix.matrix[i][j];
            }
            R->matrix[k][j] = dot;

            for (int i = 0; i < m; i++)
            {
                Q->matrix[i][j] -= dot * Q->matrix[i][k];
            }
        }

        double norm = 0.0;
        for (int i = 0; i < m; i++)
        {
            norm += Q->matrix[i][j] * Q->matrix[i][j];
        }
        norm = sqrt(norm);
        R->matrix[j][j] = norm;

        if (norm == 0)
        {
            printf("Matrix has linearly dependent columns; QR decomposition not possible.\n");
            freeMatrix(Q);
            freeMatrix(R);
            printf("Press Enter to continue...");
            while (getchar() != '\n')
                ;
            return;
        }

        for (int i = 0; i < m; i++)
        {
            Q->matrix[i][j] /= norm;
        }
    }

    drawTitle(3);
    printf("Matrix: %s\n", id);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%-10s", modifyDouble(matrix.matrix[i][j]));
        }
        printf("\n");
    }

    drawLine();
    printf("Q:\n");
    for (int i = 0; i < Q->rows; i++)
    {
        for (int j = 0; j < Q->cols; j++)
        {
            printf("%-10s", modifyDouble(Q->matrix[i][j]));
        }
        printf("\n");
    }

    drawLine();
    printf("R:\n");
    for (int i = 0; i < R->rows; i++)
    {
        for (int j = 0; j < R->cols; j++)
        {
            printf("%-10s", modifyDouble(R->matrix[i][j]));
        }
        printf("\n");
    }

    drawLine();
    printf("Press Enter to continue...");
    while (getchar() != '\n')
        ;

    freeMatrix(Q);
    freeMatrix(R);
}
