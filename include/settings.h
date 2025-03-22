#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

#define MAX_INPUT_SIZE 256
#define PI 3.14159265359
#define E 2.71828182846
#define EPSILON 1e-10
#define WIDTH 80

typedef enum
{
    MODE_COMPUTATION = 1,
    MODE_STATISTICS,
    MODE_MATRIX,
    MODE_EQUATION,
    MODE_GRAPH,
    MODE_EXIT
} CalculatorMode;

extern CalculatorMode mode;
extern bool degreeMode;
extern bool scientificMode;
extern int precision;
extern int regMode;

#endif