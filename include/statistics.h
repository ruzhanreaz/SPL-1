#ifndef STAT_H
#define STAT_H

void statistics();
void showData();
void clearAllData();
void clearColumn();
void setData();

int isStatOperand(char *str);

double sum(char *name);
double mean(char *name);
double median(char *name);
double mode(char *name);
double range(char *name);
double pvar(char *name);
double pstd(char *name);
double svar(char *name);
double sstd(char *name);
double max(char *name);
double min(char *name);
void sort(char *name);

double cov(char *name1, char *name2);
double corr(char *name1, char *name2);

void postfixEvaluateStat(Queue *postfixQueue, char *result);

#endif