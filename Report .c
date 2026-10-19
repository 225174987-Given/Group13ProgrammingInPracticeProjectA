#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

// Helper function to print the sub-menu options
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

// Main report menu control loop
void displayReports() {
    int choice;
    do {
        displayReportsMenu();
        
        // Validate input to ensure it is a number
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear input buffer
            printf("Invalid choice! Try again.\n");
            continue;
        }
        while(getchar() != '\n'); // Clear trailing newline

        if(choice == 1) generateEmployeeReport();
        else if(choice == 2) generateBudgetReport();
        else if(choice == 3) generateSupplierReport();
        else if(choice == 4) generateAssetReport();
        else if(choice == 5) break;
        else printf("Invalid choice! Try again.\n");
    } while(1);
}

// Pulls real-time calculations directly from Student 1's parallel arrays
void generateEmployeeReport() {
    if(employeeCount == 0) {
        printf("\nNo employees registered yet.\n");
        return;
    }
    printf("\n--- Employee Report ---\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n", averageBasicSalary());
    printf("Highest Salary: N$%.2f\n", highestBasicSalary());
    printf("Lowest Salary: N$%.2f\n", lowestBasicSalary());
}

// Connects directly to Student 2's budget reporting tool
void generateBudgetReport() {
    budgetReport(); 
}

// Connects directly to Student 3's supplier information display
void generateSupplierReport() {
    displaySuppliers(); 
}

// Connects directly to Student 4's asset tracking metrics
void generateAssetReport() {
    assetReport(); 
}
