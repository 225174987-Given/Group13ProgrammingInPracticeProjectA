#include <stdio.h>
#include <stdlib.h>
#include "03_employees.h"
#include "05_budget .h"
#include "07_suppliers.h"
#include "09_assets .h"
#include "11_Report .h"

// Clears the screen to keep the system looking clean and uniform across menus
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Student 1: Employee Management Submenu Integration Loop
void employeeMenuLoop() {
    int choice;
    do {
        printf("\n========================================\n");
        printf(" EMPLOYEE MANAGEMENT MODULE\n");
        printf("========================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search for an Employee\n");
        printf("4. Calculate Salary Information\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear keyboard buffer from invalid text
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n'); // Strip trailing newline

        switch(choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: calculateSalary(); break;
            case 5: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Please select an option between 1-5.\n");
        }
    } while(choice != 5);
}

// Student 2: Budget Management Submenu Integration Loop
void budgetMenuLoop() {
    int choice;
    do {
        printf("\n========================================\n");
        printf(" BUDGET MANAGEMENT MODULE\n");
        printf("========================================\n");
        printf("1. Enter Departmental Budget\n");
        printf("2. Display Budgets and Balances\n");
        printf("3. Search Budget by ID\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: {
                int id;
                printf("Enter Budget ID to search: ");
                if(scanf("%d", &id) == 1) {
                    searchBudgetById(id);
                } else {
                    printf("Invalid numeric ID format.\n");
                }
                while(getchar() != '\n');
                break;
            }
            case 4: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Please select an option between 1-4.\n");
        }
    } while(choice != 4);
}

// Student 4: Asset Management Submenu Integration Loop
void assetMenuLoop() {
    int choice;
    do {
        printf("\n========================================\n");
        printf(" ASSET MANAGEMENT MODULE\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Asset Register\n");
        printf("3. Search Asset Information\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Please select an option between 1-4.\n");
        }
    } while(choice != 4);
}

// Foundation System Entry Point
int main() {
    int choice = 0;
    
    do {
        printf("\n========================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM \n");
        printf("========================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Supplier Management\n");
        printf("4. Asset Management\n");
        printf("5. Reports\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Prevent infinite loop crash on character entry
            clearScreen();
            printf("Invalid format entry! Select a numeric option between 1 and 6.\n");
            continue;
        }
        while (getchar() != '\n'); // Clean standard input carriage returns

        switch (choice) {
            case 1: employeeMenuLoop(); break;
            case 2: budgetMenuLoop(); break;
            case 3: supplierMenu(); break; // Student 3 built their own loop structure internally
            case 4: assetMenuLoop(); break;
            case 5: displayReports(); break;
            case 6: printf("\nShutting down Municipal Management System. All live session caches cleared safely.\n"); break;
            default: printf("Invalid menu range choice! Please select an option from 1 to 6.\n");
        }
    } while (choice != 6);
    
    return 0;
}