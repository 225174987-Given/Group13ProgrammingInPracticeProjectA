#include <stdio.h>
#include <string.h>
#include "budget.h"

Budget budgets[MAX_BUDGETS];
int budgetCount = 0;

void addBudget() {
    if (budgetCount >= MAX_BUDGETS) {
        printf("Budget storage full!\n");
        return;
    }
    Budget b;
    printf("Enter Budget ID: ");
    scanf("%d", &b.id);
    getchar();

    for(int i=0; i<budgetCount; i++) {
        if(budgets[i].id == b.id) {
            printf("Error: Budget ID already exists!\n");
            return;
        }
    }

    printf("Enter Department: ");
    fgets(b.department, sizeof(b.department), stdin);
    b.department[strcspn(b.department, "\n")] = 0;

    printf("Enter Allocated Amount: ");
    scanf("%lf", &b.allocated);
    getchar();
    if(b.allocated <= 0) { printf("Invalid amount!\n"); return; }

    printf("Enter Spent Amount: ");
    scanf("%lf", &b.spent);
    getchar();

    printf("Enter Year: ");
    fgets(b.year, sizeof(b.year), stdin);
    b.year[strcspn(b.year, "\n")] = 0;

    budgets[budgetCount++] = b;
    printf("Budget added successfully!\n");
}

void displayBudgets() {
    if(budgetCount==0){ printf("No budgets to display.\n"); return; }
    printf("\n%-5s %-20s %-12s %-12s %-6s %-10s\n", "ID", "Department", "Allocated", "Spent", "Year", "Balance");
    for(int i=0; i<budgetCount; i++) {
        double bal = budgets[i].allocated - budgets[i].spent;
        printf("%-5d %-20s %-12.2f %-12.2f %-6s %-10.2f\n", budgets[i].id, budgets[i].department, budgets[i].allocated, budgets[i].spent, budgets[i].year, bal);
    }
}

void searchBudgetById(int id) {
    for(int i=0; i<budgetCount; i++) {
        if(budgets[i].id == id) {
            double bal = budgets[i].allocated - budgets[i].spent;
            printf("\nFound: ID=%d Dept=%s Allocated=%.2f Spent=%.2f Year=%s Balance=%.2f\n", budgets[i].id, budgets[i].department, budgets[i].allocated, budgets[i].spent, budgets[i].year, bal);
            return;
        }
    }
    printf("Budget ID %d not found.\n", id);
}

void budgetReport() {
    double totalAlloc=0, totalSpent=0;
    for(int i=0; i<budgetCount; i++){ totalAlloc+=budgets[i].allocated; totalSpent+=budgets[i].spent; }
    printf("\n--- Budget Report ---\nTotal Budgets: %d\nTotal Allocated: %.2f\nTotal Spent: %.2f\nRemaining: %.2f\n", budgetCount, totalAlloc, totalSpent, totalAlloc-totalSpent);
}
