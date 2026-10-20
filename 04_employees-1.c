/*============================================================
  PAP521S - Programming in Practice
  PROJECT A: Municipal Financial Management System (MFMS)
  File: employees.c
  Purpose: Employee Management module.
  Concepts: arrays, strings, functions, conditions, loops,
            validation, pass-by-value, strcmp().
============================================================*/

#include <stdio.h>
#include <string.h>

#include "03_employees.h"
void readNonEmpty(char *dest, int maxLen, const char *prompt);
float readPositiveFloat(const char *prompt);
void clearInputBuffer(void);

/* ---------- Parallel arrays holding the employee records ---------- */
int   employeeIDs[MAX_EMPLOYEES];
char  employeeNames[MAX_EMPLOYEES][NAME_LEN];
char  employeeDepartments[MAX_EMPLOYEES][NAME_LEN];
float employeeBasic[MAX_EMPLOYEES];
float employeeHousing[MAX_EMPLOYEES];
float employeeTransport[MAX_EMPLOYEES];
int   employeeCount = 0;

/* ----------------------------------------------------------------
   calculateGrossSalary()
   Gross Salary = Basic Salary + Housing Allowance + Transport
   The function receives COPIES of the three values (pass-by-value)
   and returns the gross salary.
---------------------------------------------------------------- */
float calculateGrossSalary(float basic, float housing, float transport)
{
    float gross;

    gross = basic + housing + transport;

    return gross;
}

/* ----------------------------------------------------------------
   calculateNetSalary()
   Net Salary = Gross Salary - Tax
---------------------------------------------------------------- */
float calculateNetSalary(float gross, float tax)
{
    float net;

    net = gross - tax;

    return net;
}

/* ----------------------------------------------------------------
   findEmployeeIndex()
   Linear search through the employee ID array.
   Returns the position of the employee, or -1 when the employee
   is not found. This follows the searchEmployee() example from
   the Week 8 notes.
---------------------------------------------------------------- */
int findEmployeeIndex(int employeeID)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employeeIDs[i] == employeeID)
        {
            return i;
        }
    }

    return -1;
}

/* ----------------------------------------------------------------
   addEmployee()
   Captures a new employee record after validating every field.
---------------------------------------------------------------- */
void addEmployee(void)
{
    int newID;
    int i;

    printf("\n--- ADD EMPLOYEE ---\n");

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("The employee register is full (%d employees).\n", MAX_EMPLOYEES);
        return;
    }

    printf("Enter employee ID (for example 101): ");
    if (scanf("%d", &newID) != 1)
    {
        printf("Invalid employee ID. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (newID <= 0)
    {
        printf("Employee ID must be greater than zero.\n");
        return;
    }

    if (findEmployeeIndex(newID) != -1)
    {
        printf("An employee with ID %d already exists.\n", newID);
        return;
    }

    employeeIDs[employeeCount] = newID;

    /* Names and departments may contain spaces, so we read a
       whole line instead of using scanf("%s", ...)          */
    readNonEmpty(employeeNames[employeeCount], NAME_LEN, "employee name");
    readNonEmpty(employeeDepartments[employeeCount], NAME_LEN, "department");

    employeeBasic[employeeCount]     = readPositiveFloat("basic salary");
    employeeHousing[employeeCount]   = readPositiveFloat("housing allowance");
    employeeTransport[employeeCount] = readPositiveFloat("transport allowance");

    employeeCount++;

    printf(GREEN "\nEmployee %d added successfully.\n" RESET, newID);

    /* strcat() is used here to build the confirmation message */
    strcat(employeeNames[employeeCount - 1], "");
}

/* ----------------------------------------------------------------
   displayEmployees()
   Prints every employee record in a table and shows the
   calculated gross salary for each one.
---------------------------------------------------------------- */
void displayEmployees(void)
{
    int i;
    float gross;

    printf("\n--- EMPLOYEE REGISTER (%d employee(s)) ---\n", employeeCount);

    if (employeeCount == 0)
    {
        printf("No employees have been captured yet.\n");
        return;
    }

    printf("%-6s %-22s %-16s %12s %12s\n",
           "ID", "Name", "Department", "Basic", "Gross");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < employeeCount; i++)
    {
        gross = calculateGrossSalary(employeeBasic[i],
                                     employeeHousing[i],
                                     employeeTransport[i]);

        printf("%-6d %-22s %-16s %12.2f %12.2f\n",
               employeeIDs[i],
               employeeNames[i],
               employeeDepartments[i],
               employeeBasic[i],
               gross);
    }

    printf("--------------------------------------------------------------------\n");
}

/* ----------------------------------------------------------------
   searchEmployee()
   Asks for an employee ID and describes the record when found.
---------------------------------------------------------------- */
void searchEmployee(void)
{
    int searchID;
    int position;
    float gross;
    char copyOfName[NAME_LEN];

    printf("\n--- SEARCH EMPLOYEE ---\n");
    printf("Enter the employee ID to search for: ");

    if (scanf("%d", &searchID) != 1)
    {
        printf("Invalid employee ID. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    position = findEmployeeIndex(searchID);

    if (position == -1)
    {
        printf(RED "Employee with ID %d was not found.\n" RESET, searchID);
        return;
    }

    /* strcpy() is used to keep a backup copy of the name
       before it is displayed.                              */
    strcpy(copyOfName, employeeNames[position]);

    gross = calculateGrossSalary(employeeBasic[position],
                                 employeeHousing[position],
                                 employeeTransport[position]);

    printf(GREEN "\nEmployee found at position %d.\n" RESET, position);
    printf("----------------------------------------\n");
    printf("Employee ID      : %d\n", employeeIDs[position]);
    printf("Name             : %s\n", copyOfName);
    printf("Name length      : %d characters\n", (int) strlen(copyOfName));
    printf("Department       : %s\n", employeeDepartments[position]);
    printf("Basic Salary     : N$%.2f\n", employeeBasic[position]);
    printf("Housing Allow.   : N$%.2f\n", employeeHousing[position]);
    printf("Transport Allow. : N$%.2f\n", employeeTransport[position]);
    printf("Gross Salary     : N$%.2f\n", gross);
}

/* ----------------------------------------------------------------
   calculateSalary()
   Works out gross salary, tax, net salary and an income band for
   one employee, using the formula from the Week 3 laboratory.
---------------------------------------------------------------- */
void calculateSalary(void)
{
    int searchID;
    int position;
    float tax;
    float gross;
    float net;

    printf("\n--- CALCULATE EMPLOYEE SALARY ---\n");
    printf("Enter the employee ID: ");

    if (scanf("%d", &searchID) != 1)
    {
        printf("Invalid employee ID. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    position = findEmployeeIndex(searchID);

    if (position == -1)
    {
        printf(RED "Employee with ID %d was not found.\n" RESET, searchID);
        return;
    }

    gross = calculateGrossSalary(employeeBasic[position],
                                 employeeHousing[position],
                                 employeeTransport[position]);

    tax = readPositiveFloat("tax amount to be deducted");

    net = calculateNetSalary(gross, tax);

    printf("\n--- SALARY SLIP ---\n");
    printf("Employee        : %s (ID %d)\n",
           employeeNames[position], employeeIDs[position]);
    printf("Department      : %s\n", employeeDepartments[position]);
    printf("Basic Salary    : N$%.2f\n", employeeBasic[position]);
    printf("Housing         : N$%.2f\n", employeeHousing[position]);
    printf("Transport       : N$%.2f\n", employeeTransport[position]);
    printf("Gross Salary    : N$%.2f\n", gross);
    printf("Tax             : N$%.2f\n", tax);
    printf("Net Salary      : N$%.2f\n", net);

    /* Decision making - the income band rule from the Week 3
       consolidated exercise.                                */
    if (net >= 20000)
    {
        printf("Income Band     : " YELLOW "High Income\n" RESET);
    }
    else if (net > 0)
    {
        printf("Income Band     : Standard Income\n");
    }
    else
    {
        printf("Income Band     : " RED "Below zero - check the tax amount\n" RESET);
    }
}

/* ----------------------------------------------------------------
   Helper functions used by the Reports module
---------------------------------------------------------------- */
int employeeCountInDepartment(char department[])
{
    int i;
    int total = 0;

    for (i = 0; i < employeeCount; i++)
    {
        if (strcmp(employeeDepartments[i], department) == 0)
        {
            total++;
        }
    }

    return total;
}

float totalBasicSalary(void)
{
    int i;
    float total = 0;

    for (i = 0; i < employeeCount; i++)
    {
        total = total + employeeBasic[i];
    }

    return total;
}

float averageBasicSalary(void)
{
    float average;

    if (employeeCount == 0)
    {
        return 0;
    }

    average = totalBasicSalary() / employeeCount;

    return average;
}

float highestBasicSalary(void)
{
    int i;
    float highest = 0;

    if (employeeCount == 0)
    {
        return 0;
    }

    /* The first salary initialises highest, as explained in the
       Week 5 notes.                                         */
    highest = employeeBasic[0];

    for (i = 1; i < employeeCount; i++)
    {
        if (employeeBasic[i] > highest)
        {
            highest = employeeBasic[i];
        }
    }

    return highest;
}

float lowestBasicSalary(void)
{
    int i;
    float lowest = 0;

    if (employeeCount == 0)
    {
        return 0;
    }

    lowest = employeeBasic[0];

    for (i = 1; i < employeeCount; i++)
    {
        if (employeeBasic[i] < lowest)
        {
            lowest = employeeBasic[i];
        }
    }

    return lowest;
}
void clearInputBuffer(void) {
    while (getchar() != '\n');
}

float readPositiveFloat(const char *prompt) {
    float val;
    printf("%s", prompt);
    while (scanf("%f", &val) != 1 || val < 0) {
        while (getchar() != '\n');
        printf("Invalid input. Please enter a positive number: ");
    }
    while (getchar() != '\n');
    return val;
}

void readNonEmpty(char *dest, int maxLen, const char *prompt) {
    printf("%s", prompt);
    while (fgets(dest, maxLen, stdin) == NULL || dest[0] == '\n' || dest[0] == '\0') {
        printf("Input cannot be empty. Please enter a valid value: ");
    }
    // Remove trailing newline character if it exists
    dest[strcspn(dest, "\n")] = '\0';
}