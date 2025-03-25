#ifndef GRAPHING_H
#define GRAPHING_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct
{
    char *equation;
    int color;
} Equation;

bool createGraphWindow();
void closeGraphWindow();
void updateGraphWindow();

void drawGraph(Equation *equations, int numOfEquations);
void drawALinearEquation(double a, double b);
void drawText(const char *text, int x, int y);
void drawColoredText(const char *text, int x, int y, SDL_Color color, TTF_Font *useFont);
void drawLegend(Equation *equations, int numOfEquations);
void drawGrid();
void drawAxesLabels();

void graphing();
int plot();
void clearGraph();
void clearAllGraph();
void clearAGraph();
void changeXRange();
void addEquation(char *input);

void getXValue(char *value);
double evaluateExpression(char *expression, double x);
void setXValue(double x);

#endif