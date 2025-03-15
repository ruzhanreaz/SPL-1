#ifndef EQUTATION_H
#define EQUTATION_H

void equation();
void addVariable(char *name);
int isVarExist(char *name);
void setVarValue(char *name, char *value);
void getVarValue(char *name, char *value);
int validVar(char *str);
void checkNumberOfVariable(char *str);

void solve(char *str);
void modifyEqn(char *str, char *modEqn);
void solveQuadratic(char *str);
void solveCubic(char *str);
void solveLinear(char *str);
void solve2Variable(char *str);
void solve3Variable(char *str);

#endif