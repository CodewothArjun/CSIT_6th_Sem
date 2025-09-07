#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 20
#define MAX_RHS 20
typedef struct {
    char lhs; char rhs[MAX_RHS]; int dot; // Dot position in RHS
} Item;
typedef struct {
    char lhs; char rhs[MAX_RHS];
} Production;
Production grammar[MAX_ITEMS];
int nprod;
// Check if a symbol is non-terminal
int isNonTerminal(char c, char nonterminals[], int nnonterm) {
    for (int i = 0; i < nnonterm; i++)
        if (nonterminals[i] == c) return 1;
    return 0;
} // Print set of items
void printItems(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c -> ", items[i].lhs);
        for (int j = 0; j <= strlen(items[i].rhs); j++) {
            if (j == items[i].dot) printf(".");
            if (items[i].rhs[j] != '\0') printf("%c", items[i].rhs[j]);
        }
        printf("\n");
    }} // Generate closure
int closure(Item items[], int n, char nonterminals[], int nnonterm) {
    int added = 1;
    while (added) {
        added = 0;
        for (int i = 0; i < n; i++) {
            if (items[i].dot < strlen(items[i].rhs)) {
                char symbol = items[i].rhs[items[i].dot];
                if (isNonTerminal(symbol, nonterminals, nnonterm)) {
                    // Add all productions of this non-terminal
                    for (int k = 0; k < nprod; k++) {
                        if (grammar[k].lhs == symbol) {
                            // Check if already in closure
                            int exists = 0;
                            for (int j = 0; j < n; j++) {
                                if (items[j].lhs == grammar[k].lhs &&
                                    strcmp(items[j].rhs, grammar[k].rhs) == 0 &&
                                    items[j].dot == 0) {
                                    exists = 1; break;
                                }}
                            if (!exists) {
                                items[n].lhs = grammar[k].lhs;
                                strcpy(items[n].rhs, grammar[k].rhs);
                                items[n].dot = 0;
                                n++;
                                added = 1;
                            }}}}}}}
    return n;
}
int main() {
    char nonterminals[MAX_ITEMS];
    int nnonterm = 0;
    printf("Enter number of productions: ");
    scanf("%d", &nprod);
    printf("Enter productions (without spaces):\n");
    for (int i = 0; i < nprod; i++) {
        char prod[20];
        scanf("%s", prod);
        grammar[i].lhs = prod[0];
        strcpy(grammar[i].rhs, prod + 3);
    } // Print original productions
    printf("\nGiven Productions:\n");
    for (int i = 0; i < nprod; i++) {
        printf("%c -> %s\n", grammar[i].lhs, grammar[i].rhs);
    } // Collect non-terminals
    for (int i = 0; i < nprod; i++) {
        int exists = 0;
        for (int j = 0; j < nnonterm; j++)
            if (nonterminals[j] == grammar[i].lhs) { exists = 1; break; }
        if (!exists) nonterminals[nnonterm++] = grammar[i].lhs;
    } // Get start symbol
    char start;
    printf("\nEnter start symbol: ");
    scanf(" %c", &start); 
    printf("\nAugmented Grammar:\n");    // Augment grammar
    printf("S' -> %c\n", start); 
    Item items[MAX_ITEMS];    // Initial item(s)
    int n = 0; 
    // Add augmented production as initial item
    items[n].lhs = 'S';  // Augmented start symbol (S')
    items[n].rhs[0] = start;
    items[n].rhs[1] = '\0';
    items[n].dot = 0;
    n++;
    printf("\nInitial Item(s):\n");    // Print initial item(s)
    printItems(items, n); 
    n = closure(items, n, nonterminals, nnonterm);     // Compute closure
    printf("\nClosure Set:\n");
    printItems(items, n); 
    return 0;
}
