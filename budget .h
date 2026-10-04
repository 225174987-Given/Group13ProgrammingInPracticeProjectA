#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 100

typedef struct {
    int id;
    char department[50];
    double allocated;
    double spent;
    char year[10];
} Budget;

extern Budget budgets[MAX_BUDGETS];
extern int budgetCount;

void addBudget();
void displayBudgets();
void searchBudgetById(int id);
void budgetReport();

#endif
