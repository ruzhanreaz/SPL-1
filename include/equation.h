#ifndef EQUTATION_H
#define EQUTATION_H

typedef struct Equation
{
    char *equation;
    struct Equation *next;
} Equation;

void equation(int degreeMode);
void printEquations(Equation *head);
void addEquation(Equation **head, const char *equation);
void freeEquationList(Equation *head);
void freeEquationNode(Equation *node);
int validateEquationInput(const char *input);
void solveEquation(int numOfEqn, const char *title);
void solve2VarLinEqn();
void solve3VarLinEqn();
void solveQuadratic(const char *equation);
void solveCubic(const char *equation);
void processEquation(const char *lhs, const char *rhs, Equation **equationHead);
void extractCoefficients(const char *equation, double *coefficients, int size);
void freeVariableList(Variable *head);

#endif