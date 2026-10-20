#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    int supplierID;
    char name[50];
    char email[50];
    char telephone[20];
    char town[30];
} Supplier;

/* Supplier Management menu and operations */
void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);

/* Validation helpers */
int isValidEmail(const char email[]);
int isValidTelephone(const char telephone[]);

#endif
