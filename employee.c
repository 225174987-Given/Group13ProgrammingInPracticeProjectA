/*============================================================
  PAP521S - Programming in Practice
  PROJECT A: Municipal Financial Management System (MFMS)
  File: employees.c
  Purpose: Employee Management module.
============================================================*/

#include <stdio.h>
#include <string.h>
#include "employees.h"

/* ---------- Input helper functions ---------- */

void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear input buffer */
    }
}

void readNonEmpty(char str[], int size, const char prompt[])
{
    do
    {
        printf("Enter %s: ", prompt);

        if (fgets(str, size, stdin) == NULL)
        {
            str[0] = '\0';
            continue;
        }

        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == 0)
        {
            printf("Input cannot be empty. Try again.\n");
        }

    } while (strlen(str) == 0);
}

float readPositiveFloat(const char prompt[])
{
    float value;
    int result;

    do
    {
        printf("Enter %s: ", prompt);

        result = scanf("%f", &value);

        if (result != 1)
        {
            printf("Please enter a valid number.\n");
            clearInputBuffer();
            value = -1;
        }
        else if (value < 0)
        {
            printf("Value cannot be negative.\n");
            clearInputBuffer();
        }

    } while (value < 0);

    clearInputBuffer();

    return value;
}

/* ---------- Parallel arrays holding employee records ---------- */

int employeeIDs[MAX_EMPLOYEES];
char employeeNames[MAX_EMPLOYEES][NAME_LEN];
char employeeDepartments[MAX_EMPLOYEES][NAME_LEN];

float employeeBasic[MAX_EMPLOYEES];
float employeeHousing[MAX_EMPLOYEES];
float employeeTransport[MAX_EMPLOYEES];

int employeeCount = 0;


/* ---------- Salary Functions ---------- */

float calculateGrossSalary(float basic, float housing, float transport)
{
    return basic + housing + transport;
}

float calculateNetSalary(float gross, float tax)
{
    return gross - tax;
}


/* ---------- Find Employee ---------- */

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


/* ---------- Add Employee ---------- */

void addEmployee(void)
{
    int newID;

    printf("\n--- ADD EMPLOYEE ---\n");

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("The employee register is full (%d employees).\n",
               MAX_EMPLOYEES);
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

    readNonEmpty(
        employeeNames[employeeCount],
        NAME_LEN,
        "employee name"
    );

    readNonEmpty(
        employeeDepartments[employeeCount],
        NAME_LEN,
        "department"
    );

    employeeBasic[employeeCount] =
        readPositiveFloat("basic salary");

    employeeHousing[employeeCount] =
        readPositiveFloat("housing allowance");

    employeeTransport[employeeCount] =
        readPositiveFloat("transport allowance");

    employeeCount++;

    printf("\nEmployee %d added successfully.\n", newID);
}


/* ---------- Display Employees ---------- */

void displayEmployees(void)
{
    int i;
    float gross;

    printf("\n--- EMPLOYEE REGISTER (%d employee(s)) ---\n",
           employeeCount);

    if (employeeCount == 0)
    {
        printf("No employees have been captured yet.\n");
        return;
    }

    printf("%-6s %-22s %-16s %12s %12s\n",
           "ID",
           "Name",
           "Department",
           "Basic",
           "Gross");

    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < employeeCount; i++)
    {
        gross = calculateGrossSalary(
            employeeBasic[i],
            employeeHousing[i],
            employeeTransport[i]
        );

        printf("%-6d %-22s %-16s %12.2f %12.2f\n",
               employeeIDs[i],
               employeeNames[i],
               employeeDepartments[i],
               employeeBasic[i],
               gross);
    }

    printf("--------------------------------------------------------------------\n");
}


/* ---------- Search Employee ---------- */

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
        printf("Employee with ID %d was not found.\n", searchID);
        return;
    }

    strcpy(copyOfName, employeeNames[position]);

    gross = calculateGrossSalary(
        employeeBasic[position],
        employeeHousing[position],
        employeeTransport[position]
    );

    printf("\nEmployee found at position %d.\n", position);

    printf("----------------------------------------\n");

    printf("Employee ID      : %d\n",
           employeeIDs[position]);

    printf("Name             : %s\n",
           copyOfName);

    printf("Name length      : %d characters\n",
           (int)strlen(copyOfName));

    printf("Department       : %s\n",
           employeeDepartments[position]);

    printf("Basic Salary     : N$%.2f\n",
           employeeBasic[position]);

    printf("Housing Allow.   : N$%.2f\n",
           employeeHousing[position]);

    printf("Transport Allow. : N$%.2f\n",
           employeeTransport[position]);

    printf("Gross Salary     : N$%.2f\n",
           gross);
}


/* ---------- Calculate Salary ---------- */

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
        printf("Employee with ID %d was not found.\n", searchID);
        return;
    }

    gross = calculateGrossSalary(
        employeeBasic[position],
        employeeHousing[position],
        employeeTransport[position]
    );

    tax = readPositiveFloat("tax amount to be deducted");

    net = calculateNetSalary(gross, tax);

    printf("\n--- SALARY SLIP ---\n");

    printf("Employee        : %s (ID %d)\n",
           employeeNames[position],
           employeeIDs[position]);

    printf("Department      : %s\n",
           employeeDepartments[position]);

    printf("Basic Salary    : N$%.2f\n",
           employeeBasic[position]);

    printf("Housing         : N$%.2f\n",
           employeeHousing[position]);

    printf("Transport       : N$%.2f\n",
           employeeTransport[position]);

    printf("Gross Salary    : N$%.2f\n", gross);

    printf("Tax             : N$%.2f\n", tax);

    printf("Net Salary      : N$%.2f\n", net);

    if (net >= 20000)
    {
        printf("Income Band     : High Income\n");
    }
    else if (net > 0)
    {
        printf("Income Band     : Standard Income\n");
    }
    else
    {
        printf("Income Band     : Below zero - check the tax amount\n");
    }
}


/* ---------- Reports Helper Functions ---------- */

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
    float total = 0.0f;

    for (i = 0; i < employeeCount; i++)
    {
        total += employeeBasic[i];
    }

    return total;
}


float averageBasicSalary(void)
{
    if (employeeCount == 0)
    {
        return 0.0f;
    }

    return totalBasicSalary() / employeeCount;
}


float highestBasicSalary(void)
{
    int i;
    float highest;

    if (employeeCount == 0)
    {
        return 0.0f;
    }

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
    float lowest;

    if (employeeCount == 0)
    {
        return 0.0f;
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