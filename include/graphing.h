#ifndef GRAPHING_H
#define GRAPHING_H
#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

typedef struct
{
    char *equation;
    int color;
} Equation;

bool createGraphWindow();
void closeGraphWindow();
void drawGraph(Equation *equations, int numOfEquations);
void drawText(const char *text, int x, int y);
void graphing();
int plot();
void clearGraph();
void getXValue(char *value);
double evaluateExpression(char *expression, double x);
void setXValue(double x);

#endif