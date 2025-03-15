#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    char *id;
    double **matrix;
    int rows;
    int cols;
} Matrix;

void displayMatrix(double **matrix, int rows, int cols, int highLightRow, int highLightCol);
void fillMatrix(double **matrix, int rows, int cols);
void setMatrix();
void matrix();
int isMatrix(char *name);
void showAMatrix();
void showAllMatrix();
void clearAMatrix();
void clearAllMatrix();
void matrixAdd(char *name1, char *name2, char *resMatrix);
void matrixSubtract(char *name1, char *name2, char *resMatrix);
void matrixMultiply(char *name1, char *name2, char *resMatrix);
void matrixTranspose(char *name, char *resMatrix);
void matrixInverse(char *name, char *resMatrix);
void matrixMulScalar(char *name, double scalar, char *resMatrix);
void matrixDivScalar(char *name, double scalar, char *resMatrix);
void createIdentityMatrix(int n, int m, char *name);
void lu();
//void qr();
void getMatrix(char *name, double ***matrix, int *rows, int *cols);

void postfixEvaluateMat(Queue *postfix, char *result);

#endif