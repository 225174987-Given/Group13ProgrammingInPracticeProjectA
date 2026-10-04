/*============================================================
  PAP521S - Programming in Practice
  PROJECT A: Municipal Financial Management System (MFMS)
  File: employees.h
  Purpose: Declaration of the employee data arrays and the
           prototypes of every employee function.
============================================================*/

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define NAME_LEN 50

#include "common.h"

/* ---------- Employee data stored in parallel arrays ---------- */
extern int   employeeIDs[MAX_EMPLOYEES];
extern char  employeeNames[MAX_EMPLOYEES][NAME_LEN];
extern char  employeeDepartments[MAX_EMPLOYEES][NAME_LEN];
extern float employeeBasic[MAX_EMPLOYEES];
extern float employeeHousing[MAX_EMPLOYEES];
extern float employeeTransport[MAX_EMPLOYEES];
extern int   employeeCount;

/* ---------- Function prototypes (Week 8) ---------- */
void  addEmployee(void);
void  displayEmployees(void);
void  searchEmployee(void);
void  calculateSalary(void);
float calculateGrossSalary(float basic, float housing, float transport);
float calculateNetSalary(float gross, float tax);
int   findEmployeeIndex(int employeeID);
int   employeeCountInDepartment(char department[]);
float totalBasicSalary(void);
float averageBasicSalary(void);
float highestBasicSalary(void);
float lowestBasicSalary(void);

#endif
