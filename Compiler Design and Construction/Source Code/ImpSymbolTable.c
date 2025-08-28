#include <stdio.h>
#include <string.h>

#define SIZE 50   // max number of symbols

// Structure of a symbol table entry
struct Symbol {
    char name[30];
    char type[10];
    char scope[10];
};

struct Symbol table[SIZE];
int count = 0;

// Insert into symbol table
void insert(char name[], char type[], char scope[]) {
    // check duplicate
    for(int i=0; i<count; i++) {
        if(strcmp(table[i].name, name)==0 && strcmp(table[i].scope, scope)==0) {
            printf("Error: Duplicate entry for %s in scope %s\n", name, scope);
            return;
        }
    }
    strcpy(table[count].name, name);
    strcpy(table[count].type, type);
    strcpy(table[count].scope, scope);
    count++;
    printf("Inserted: %s, %s, %s\n", name, type, scope);
}

// Lookup in symbol table
int lookup(char name[], char scope[]) {
    for(int i=0; i<count; i++) {
        if(strcmp(table[i].name, name)==0 && strcmp(table[i].scope, scope)==0)
            return i;
    }
    return -1;
}

// Display symbol table
void display() {
    printf("\n--- Symbol Table ---\n");
    printf("%-15s %-10s %-10s\n", "Identifier", "Type", "Scope");
    printf("-----------------------------------\n");
    for(int i=0; i<count; i++) {
        printf("%-15s %-10s %-10s\n", table[i].name, table[i].type, table[i].scope);
    }
}

int main() {
    insert("x","int","global");
    insert("y","float","global");
    insert("x","int","local");
    insert("z","char","local");

    display();

    char id[10]="x", sc[10]="local";
    int pos = lookup(id, sc);
    if(pos!=-1)
        printf("\nLookup: %s found at position %d with type %s\n", id, pos, table[pos].type);
    else
        printf("\nLookup: %s not found in scope %s\n", id, sc);

    return 0;
}
