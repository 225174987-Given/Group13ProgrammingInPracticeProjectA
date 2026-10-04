#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

// We use extern - these arrays are created by Member 1-4
extern struct Employee employees[];
extern int employeeCount;

void displayReportsMenu() {
    printf("\n========================================\n");
    printf(" REPORTS MODULE\n");
    printf("========================================\n");
    printf("1. Employee Report\n");
    printf("2. Budget Report\n");
    printf("3. Supplier Report\n");
    printf("4. Asset Report\n");
    printf("5. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void displayReports() {
    int choice;
    do {
        displayReportsMenu();
        scanf("%d", &choice);
        if(choice == 1) generateEmployeeReport();
        else if(choice == 2) generateBudgetReport();
        else if(choice == 3) generateSupplierReport();
        else if(choice == 4) generateAssetReport();
        else if(choice == 5) break;
        else printf("Invalid choice! Try again.\n");
    } while(1);
}

void generateEmployeeReport() {
    if(employeeCount == 0) {
        printf("\nNo employees registered yet.\n");
        return;
    }
    float total = 0, highest = employees[0].basicSalary, lowest = employees[0].basicSalary;
    for(int i=0; i<employeeCount; i++) {
        if(strlen(employees[i].name) == 0) continue;
        total += employees[i].basicSalary;
        if(employees[i].basicSalary > highest) highest = employees[i].basicSalary;
        if(employees[i].basicSalary < lowest) lowest = employees[i].basicSalary;
    }
    printf("\n--- Employee Report ---\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n", total / employeeCount);
    printf("Highest Salary: N$%.2f\n", highest);
    printf("Lowest Salary: N$%.2f\n", lowest);
}

void generateBudgetReport() {
    // Temporary - Member 2 will give you real variables
    printf("\n--- Budget Report ---\n");
    printf("Call budget module functions here\n");
}

void generateSupplierReport() {
    printf("\n--- Supplier Report ---\n");
    printf("Call supplier display here\n");
}

void generateAssetReport() {
    printf("\n--- Asset Report ---\n");
    printf("Call asset display here\n");
}
