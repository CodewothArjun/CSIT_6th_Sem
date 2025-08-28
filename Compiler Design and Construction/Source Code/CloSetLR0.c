#include <stdio.h>
#include <string.h>

#define MAX 10

// Structure for an item
struct Item {
    char lhs;
    char rhs[MAX];
    int dotPos;  // position of the dot
};

// Function to print an item
void printItem(struct Item item) {
    int i;
    printf("%c -> ", item.lhs);
    for (i = 0; i < strlen(item.rhs); i++) {
        if (i == item.dotPos) {
            printf(".");
        }
        printf("%c", item.rhs[i]);
    }
    if (item.dotPos == strlen(item.rhs)) {
        printf(".");
    }
    printf("\n");
}

// Closure function (basic for LR(0))
void closure(struct Item items[], int n) {
    printf("\nClosure Set:\n");
    for (int i = 0; i < n; i++) {
        printItem(items[i]);

        // If dot is before a non-terminal, add its productions
        if (items[i].dotPos < strlen(items[i].rhs)) {
            char nextSymbol = items[i].rhs[items[i].dotPos];

            if (nextSymbol == 'A') {
                struct Item newItem = {'A', "a", 0};
                printItem(newItem);
            }
            else if (nextSymbol == 'B') {
                struct Item newItem = {'B', "b", 0};
                printItem(newItem);
            }
        }
    }
}

int main() {
    // Initial Item: S -> .AB
    struct Item items[MAX];
    int n = 1;

    items[0].lhs = 'S';
    strcpy(items[0].rhs, "AB");
    items[0].dotPos = 0;

    printf("Grammar:\n");
    printf("S -> AB\n");
    printf("A -> a\n");
    printf("B -> b\n");

    closure(items, n);

    return 0;
}
