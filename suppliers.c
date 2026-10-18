#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

/*
 * Supplier records are stored in memory while the program is running.
 * They are not saved to a file, so records are lost when the program exits.
 */
static Supplier suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

/* Read a line safely, remove its newline, and discard excess characters. */
static int readLine(const char *prompt, char buffer[], size_t size)
{
    size_t length;
    int ch;

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        /* Input was longer than the buffer; clear the rest of the line. */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard */
        }
    }

    /* Remove a trailing carriage return if input uses CRLF line endings. */
    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[length - 1] = '\0';
    }

    return 1;
}

/* Read an integer without leaving invalid characters in the input stream. */
static int readInteger(const char *prompt, int *value)
{
    char line[100];
    char *start;
    char *end;
    long parsed;

    if (!readLine(prompt, line, sizeof(line))) {
        return 0;
    }

    /* Skip leading whitespace without modifying the array name. */
    start = line;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '\0') {
        return -1;
    }

    parsed = strtol(start, &end, 10);

    if (end == start) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0' || parsed < -2147483647L - 1L ||
        parsed > 2147483647L) {
        return -1;
    }

    *value = (int)parsed;
    return 1;
}

/* Return 1 if the ID is already registered; otherwise return 0. */
static int supplierIDExists(int id)
{
    int i;

    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].supplierID == id) {
            return 1;
        }
    }

    return 0;
}

/* Basic email validation suitable for this introductory project. */
int isValidEmail(const char email[])
{
    const char *at;
    const char *dot;

    if (email == NULL || email[0] == '\0') {
        return 0;
    }

    at = strchr(email, '@');

    /* Require exactly one @, with text before and after it. */
    if (at == NULL || at == email || at[1] == '\0') {
        return 0;
    }

    if (strchr(at + 1, '@') != NULL) {
        return 0;
    }

    /* Require a dot in the domain, not immediately after @ or at the end. */
    dot = strrchr(at + 1, '.');

    if (dot == NULL || dot == at + 1 || dot[1] == '\0') {
        return 0;
    }

    /* Reject spaces. */
    if (strchr(email, ' ') != NULL || strchr(email, '\t') != NULL) {
        return 0;
    }

    return 1;
}

/*
 * Accept digits, spaces, +, -, and parentheses.
 * Require between 7 and 15 digits. A plus sign may only appear first.
 */
int isValidTelephone(const char telephone[])
{
    size_t i;
    int digits = 0;

    if (telephone == NULL || telephone[0] == '\0') {
        return 0;
    }

    for (i = 0; telephone[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)telephone[i];

        if (isdigit(ch)) {
            digits++;
        } else if (ch == '+' && i == 0) {
            /* Optional international prefix. */
        } else if (ch == ' ' || ch == '-' || ch == '(' || ch == ')') {
            /* Common telephone-number separators. */
        } else {
            return 0;
        }
    }

    return digits >= 7 && digits <= 15;
}

void addSupplier(void)
{
    Supplier s;
    int result;

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("\nSupplier database is full. Maximum: %d suppliers.\n",
               MAX_SUPPLIERS);
        return;
    }

    printf("\n--- ADD SUPPLIER ---\n");

    result = readInteger("Enter Supplier ID: ", &s.supplierID);
    if (result == 0) {
        printf("\nInput ended. Supplier was not added.\n");
        return;
    }
    if (result != 1) {
        printf("Error: Supplier ID must be a valid integer.\n");
        return;
    }
    if (s.supplierID <= 0) {
        printf("Error: Supplier ID must be positive.\n");
        return;
    }
    if (supplierIDExists(s.supplierID)) {
        printf("Error: Supplier ID already exists.\n");
        return;
    }

    if (!readLine("Enter Supplier Name: ", s.name, sizeof(s.name))) {
        printf("\nInput ended. Supplier was not added.\n");
        return;
    }
    if (strlen(s.name) < 2) {
        printf("Error: Supplier name must contain at least 2 characters.\n");
        return;
    }

    if (!readLine("Enter Email: ", s.email, sizeof(s.email))) {
        printf("\nInput ended. Supplier was not added.\n");
        return;
    }
    if (!isValidEmail(s.email)) {
        printf("Error: Invalid email. Example: abc@nust.na\n");
        return;
    }

    if (!readLine("Enter Telephone: ", s.telephone, sizeof(s.telephone))) {
        printf("\nInput ended. Supplier was not added.\n");
        return;
    }
    if (!isValidTelephone(s.telephone)) {
        printf("Error: Invalid telephone number. Use 7-15 digits; spaces, +, - "
               "and parentheses are allowed.\n");
        return;
    }

    if (!readLine("Enter Town/Location: ", s.town, sizeof(s.town))) {
        printf("\nInput ended. Supplier was not added.\n");
        return;
    }
    if (strlen(s.town) == 0) {
        printf("Error: Town/Location cannot be empty.\n");
        return;
    }

    /* Copy the validated record into the supplier array. */
    suppliers[supplierCount].supplierID = s.supplierID;
    strcpy(suppliers[supplierCount].name, s.name);
    strcpy(suppliers[supplierCount].email, s.email);
    strcpy(suppliers[supplierCount].telephone, s.telephone);
    strcpy(suppliers[supplierCount].town, s.town);

    supplierCount++;
    printf("Supplier added successfully! Total suppliers: %d\n",
           supplierCount);
}

void displaySuppliers(void)
{
    int i;

    if (supplierCount == 0) {
        printf("\nNo suppliers registered.\n");
        return;
    }

    printf("\n--- SUPPLIER LIST (%d) ---\n", supplierCount);

    for (i = 0; i < supplierCount; i++) {
        printf("\nID: %d\n", suppliers[i].supplierID);
        printf("Name: %s\n", suppliers[i].name);
        printf("Email: %s\n", suppliers[i].email);
        printf("Telephone: %s\n", suppliers[i].telephone);
        printf("Town: %s\n", suppliers[i].town);
        printf("------------------------------\n");
    }
}

void searchSupplier(void)
{
    char searchName[50];
    int i;
    int found = 0;

    if (supplierCount == 0) {
        printf("\nNo suppliers registered to search.\n");
        return;
    }

    if (!readLine("\nEnter Supplier Name to search: ",
                  searchName, sizeof(searchName))) {
        printf("\nInput ended.\n");
        return;
    }

    if (searchName[0] == '\0') {
        printf("Error: Search name cannot be empty.\n");
        return;
    }

    for (i = 0; i < supplierCount; i++) {
        if (strcmp(suppliers[i].name, searchName) == 0) {
            printf("\nSUPPLIER FOUND\n");
            printf("ID: %d\n", suppliers[i].supplierID);
            printf("Name: %s\n", suppliers[i].name);
            printf("Email: %s\n", suppliers[i].email);
            printf("Telephone: %s\n", suppliers[i].telephone);
            printf("Town: %s\n", suppliers[i].town);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Supplier '%s' not found.\n", searchName);
    }
}

void compareSuppliers(void)
{
    char townSearch[30];
    int i;
    int count = 0;

    if (supplierCount == 0) {
        printf("\nNo suppliers registered to compare.\n");
        return;
    }

    if (!readLine("\nEnter Town/Location to list suppliers: ",
                  townSearch, sizeof(townSearch))) {
        printf("\nInput ended.\n");
        return;
    }

    if (townSearch[0] == '\0') {
        printf("Error: Town/Location cannot be empty.\n");
        return;
    }

    printf("\nSuppliers in %s:\n", townSearch);

    for (i = 0; i < supplierCount; i++) {
        if (strcmp(suppliers[i].town, townSearch) == 0) {
            printf("- ID: %d | %s | %s | %s\n",
                   suppliers[i].supplierID,
                   suppliers[i].name,
                   suppliers[i].email,
                   suppliers[i].telephone);
            count++;
        }
    }

    if (count == 0) {
        printf("No suppliers found in %s.\n", townSearch);
    } else {
        printf("Total suppliers in %s: %d\n", townSearch, count);
    }
}

void supplierMenu(void)
{
    int choice;
    int result;

    do {
        printf("\n=== SUPPLIER MANAGEMENT ===\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare by Town\n");
        printf("5. Back to Main Menu\n");

        result = readInteger("Enter choice: ", &choice);

        if (result == 0) {
            printf("\nInput ended. Returning from Supplier Management.\n");
            return;
        }

        if (result != 1) {
            printf("Invalid input! Please enter a number from 1 to 5.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
            case 4:
                compareSuppliers();
                break;
            case 5:
                printf("Returning to Main Menu...\n");
                return;
            default:
                printf("Invalid choice! Please select a number from 1 to 5.\n");
        }
    } while (1);
}
