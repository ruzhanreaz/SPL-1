#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    char id;
    double **matrix;
    int rows;
    int cols;
} Matrix;

typedef struct MatrixNode
{
    Matrix matrix;
    struct MatrixNode *next;
} MatrixNode;
typedef struct MatrixStack
{
    MatrixNode *top;
} MatrixStack;

void pushMatrix(MatrixStack *stack, Matrix matrix);
Matrix popMatrix(MatrixStack *stack);
int isEmptyMatrixStack(MatrixStack *stack);

void displayMatrix(double **matrix, int rows, int cols, int highLightRow, int highLightCol);
void fillMatrix(double **matrix, int rows, int cols);
void setMatrix();
void matrixMenu();
void matrix(int degreeMode);
int isMatrix(MatrixNode *head, char id);

#endif