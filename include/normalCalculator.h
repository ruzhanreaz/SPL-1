#ifndef NORMALCALCULATOR_H
#define NORMALCALCULATOR_H

int precedence(char operator);
void infixToPostfix(char *infix, char *postfix);
int evaluatePostfix(char *postfix);

#endif