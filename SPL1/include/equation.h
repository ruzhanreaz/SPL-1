#ifndef EQUTATION_H
#define EQUTATION_H

typedef struct {
    char *varName;
    char *value;
    int isBeingEvaluated; 
} Variable;

extern Variable *variables;
extern char **varList;
extern int numVariables;

void equation();
void addVariable(char *name);
int isVarExist(char *name);
void setVarValue(char *name, char *value);
void getVarValue(char *name, char *value);
int validVar(char *str);
void checkNumberOfVariable(char *str);
void clearVariables();

void solve(char *str);
void modifyEqn(char *str, char *modEqn);
void solveQuadratic(char *str);
void solveCubic(char *str);
void solveLinear(char *str);
void solve2Variable(char *str);
void solve3Variable(char *str);

void equationMenu();

#endif