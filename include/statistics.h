#ifndef STAT_H
#define STAT_H

typedef struct
{
    char *data;
} Data;

typedef struct
{
    char name[50];
    Data *data;
    int numOfData;
} DataColumn;

typedef struct
{
    double x;
    double y;
} Point;

extern Point *points;
extern int numOfPoints;
extern int numOfColumn;
extern DataColumn *dataColumns;
extern char **titleNameList;

void statistics();
void addPoint(double x, double y);
void showData();
void clearAllData();
void clearColumn();
void setData();

int isStatOperand(char *str);

double sum(char *name);
double sumsqr(char *name);
double sumxy(char *name1, char *name2);
double mean(char *name);
double median(char *name);
double modeStat(char *name);
double range(char *name);
double pvar(char *name);
double pstd(char *name);
double svar(char *name);
double sstd(char *name);
double max(char *name);
double min(char *name);
void sort(char *name);
void sortData();

double scov(char *name1, char *name2);
double pcov(char *name1, char *name2);

double corr(char *name1, char *name2);

void postfixEvaluateStat(Queue *postfixQueue, char *result);

void statisticsMenu();

void regression();

#endif