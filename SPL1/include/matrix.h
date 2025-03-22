#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    double **matrix;
    int rows;
    int cols;
} Matrix;

typedef struct
{
    char *id;
    Matrix *matrix;
} MatrixNode;

extern MatrixNode *matrixList;
extern int matrixListSize;

extern MatrixNode *mainMatrixList;
extern int mainMatrixListSize;

void matrix();
void matrixMenu();
void setMatrix();
int validateMatrixName(char *id);
void displayMatrix(Matrix *matrix, int highLightRow, int highLightCol);
void fillMatrix(Matrix *matrix);
int isMatrix(char *id);
void showMatrix();
void showAllMatrix();
void clearMatrix();
void clearAllMatrix();
void luDecomposition();
void qrDecomposition();
void matrixReset();

Matrix *createMatrix(int rows, int cols);
Matrix *createIdentityMatrix(int size);
Matrix *createZeroMatrix(int rows, int cols);
Matrix getMatrix(char *id);
void saveMatrix(char *id, Matrix *matrix);
void saveMainMatrix(char *id, Matrix *matrix);
void removeMatrix(char *id);
void freeMatrix(Matrix *matrix);

Matrix *matrixAdd(Matrix *matrix1, Matrix *matrix2);
Matrix *matrixSubtract(Matrix *matrix1, Matrix *matrix2);
Matrix *matrixMultiply(Matrix *matrix1, Matrix *matrix2);
Matrix *matrixDivide(Matrix *matrix1, Matrix *matrix2);
Matrix *matrixPower(Matrix *matrix, int power);
Matrix *matrixTranspose(Matrix *matrix);
Matrix *matrixInverse(Matrix *matrix);
Matrix *matrixAddScalar(Matrix *matrix, double scalar);
Matrix *matrixSubtractScalar(Matrix *matrix, double scalar);
Matrix *matrixScalarMultiply(Matrix *matrix, double scalar);
Matrix *matrixScalarDivide(Matrix *matrix, double scalar);
double matrixDeterminant(Matrix *matrix);
int matrixRank(Matrix *matrix);
Matrix *matrixRowEchelonForm(Matrix *matrix);
Matrix *matrixReducedRowEchelonForm(Matrix *matrix);

void postfixEvaluateMat(Queue *postfix, char *result);

#endif