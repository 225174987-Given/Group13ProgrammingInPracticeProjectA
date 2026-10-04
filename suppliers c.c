#include <stdio.h>
#include <string.h>

#ifndef MAX_SUPPLIERS
#define MAX_SUPPLIERS 100
#endif

typedef struct
{
    int supplierID;
    char name[100];
    char email[100];
    char telephone[50];
    char location[100];
} Supplier;

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

void addSupplier()
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("\nSupplier storage is full.\n");
        return;
    }

    printf("\n========== ADD SUPPLIER ==========\n");

    printf("Enter Supplier ID: ");
    scanf("%d", &suppliers[supplierCount].supplierID);
    getchar();

    printf("Enter Supplier Name: ");
    fgets(suppliers[supplierCount].name, sizeof(suppliers[supplierCount].name), stdin);
    suppliers[supplierCount].name[strcspn(suppliers[supplierCount].name, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(suppliers[supplierCount].email, sizeof(suppliers[supplierCount].email), stdin);
    suppliers[supplierCount].email[strcspn(suppliers[supplierCount].email, "\n")] = '\0';

    printf("Enter Telephone Number: ");
    fgets(suppliers[supplierCount].telephone, sizeof(suppliers[supplierCount].telephone), stdin);
    suppliers[supplierCount].telephone[strcspn(suppliers[supplierCount].telephone, "\n")] = '\0';

    printf("Enter Town/Location: ");
    fgets(suppliers[supplierCount].location, sizeof(suppliers[supplierCount].location), stdin);
    suppliers[supplierCount].location[strcspn(suppliers[supplierCount].location, "\n")] = '\0';

    supplierCount++;

    printf("\nSupplier added successfully!\n");
}

void displaySuppliers()
{
    int i;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers have been registered.\n");
        return;
    }

    printf("\n========== SUPPLIER LIST ==========\n");

    for (i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier %d\n", i + 1);
        printf("Supplier ID : %d\n", suppliers[i].supplierID);
        printf("Name        : %s\n", suppliers[i].name);
        printf("Email       : %s\n", suppliers[i].email);
        printf("Telephone   : %s\n", suppliers[i].telephone);
        printf("Location    : %s\n", suppliers[i].location);
    }
}

void searchSupplier()
{
    int choice;
    int id;
    int i;
    int found = 0;
    char searchName[100];

    if (supplierCount == 0)
    {
        printf("\nNo suppliers have been registered.\n");
        return;
    }

    printf("\n========== SEARCH SUPPLIER ==========\n");
    printf("1. Search by Supplier ID\n");
    printf("2. Search by Supplier Name\n");
    printf("3. Search by Location\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("Enter Supplier ID: ");
        scanf("%d", &id);
        getchar();

        for (i = 0; i < supplierCount; i++)
        {
            if (suppliers[i].supplierID == id)
            {
                printf("\nSupplier Found!\n");
                printf("Supplier ID : %d\n", suppliers[i].supplierID);
                printf("Name        : %s\n", suppliers[i].name);
                printf("Email       : %s\n", suppliers[i].email);
                printf("Telephone   : %s\n", suppliers[i].telephone);
                printf("Location    : %s\n", suppliers[i].location);

                found = 1;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter Supplier Name: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';

        for (i = 0; i < supplierCount; i++)
        {
            if (strcmp(suppliers[i].name, searchName) == 0)
            {
                printf("\nSupplier Found!\n");
                printf("Supplier ID : %d\n", suppliers[i].supplierID);
                printf("Name        : %s\n", suppliers[i].name);
                printf("Email       : %s\n", suppliers[i].email);
                printf("Telephone   : %s\n", suppliers[i].telephone);
                printf("Location    : %s\n", suppliers[i].location);

                found = 1;
                break;
            }
        }
    }
    else if (choice == 3)
    {
        printf("Enter Town/Location: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';

        for (i = 0; i < supplierCount; i++)
        {
            if (strcmp(suppliers[i].location, searchName) == 0)
            {
                printf("\nSupplier Found!\n");
                printf("Supplier ID : %d\n", suppliers[i].supplierID);
                printf("Name        : %s\n", suppliers[i].name);
                printf("Email       : %s\n", suppliers[i].email);
                printf("Telephone   : %s\n", suppliers[i].telephone);
                printf("Location    : %s\n", suppliers[i].location);

                found = 1;
            }
        }
    }
    else
    {
        printf("\nInvalid choice.\n");
        return;
    }

    if (!found)
    {
        printf("\nSupplier not found.\n");
    }
}

void supplierMenu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("        SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
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
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 4);
}