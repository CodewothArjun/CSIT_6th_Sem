#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
// Structure for a symbol table entry
typedef struct {
    char name[50];   // Identifier name
    char type[20];   // Data type (int, float, etc.)
    char scope[20];  // Scope (global, local)
} Symbol;

// Symbol table and counter
Symbol table[MAX];
int count = 0;

// Function to insert a new identifier
void insert(char *name, char *type, char *scope) {
    // Check if already exists
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0 && strcmp(table[i].scope, scope) == 0) {
            printf("Error: Identifier '%s' already exists in scope '%s'\n", name, scope);
            return;
        }
    }
    strcpy(table[count].name, name);
    strcpy(table[count].type, type);
    strcpy(table[count].scope, scope);
    count++;
    printf("Inserted: %s, %s, %s\n", name, type, scope);
}

// Function to lookup an identifier
void lookup(char *name, char *scope) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0 && strcmp(table[i].scope, scope) == 0) {
            printf("Found: %s, %s, %s\n", table[i].name, table[i].type, table[i].scope);
            return;
        }
    }
    printf("Identifier '%s' not found in scope '%s'\n", name, scope);
}

// Function to display the symbol table
void display() {
    printf("\nSymbol Table:\n");
    printf("%-20s %-10s %-10s\n", "Identifier", "Type", "Scope");
    printf("-------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10s %-10s\n", table[i].name, table[i].type, table[i].scope);
    }
}

int main() {
    int choice;
    char name[50], type[20], scope[20];

    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert\n2. Lookup\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter identifier name: ");
                scanf("%s", name);
                printf("Enter type: ");
                scanf("%s", type);
                printf("Enter scope: ");
                scanf("%s", scope);
                insert(name, type, scope);
                break;
            case 2:
                printf("Enter identifier name to lookup: ");
                scanf("%s", name);
                printf("Enter scope: ");
                scanf("%s", scope);
                lookup(name, scope);
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
