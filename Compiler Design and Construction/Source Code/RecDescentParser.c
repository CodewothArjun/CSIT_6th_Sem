#include <stdio.h>
#include <string.h>
char input[100];  // Input string
int i = 0;        // Current position in input
// Function prototypes
int S();
int A();
// Function to match the current character
int match(char c) {
    if (input[i] == c) {
        printf("Matched '%c'\n", c);
        i++;
        return 1; // Matched successfully
    }
    return 0; // Did not match
}
// Function for S -> a A b
int S() {
    printf("Applying production: S -> a A b\n");
    if (match('a')) {      // Match 'a'
        if (A()) {         // Parse A
            if (match('b')) { // Match 'b'
                return 1;      // Successfully parsed S
            }}}
    return 0; // Parsing failed
}
// Function for A -> a | e
int A() {
    if (input[i] == 'a') {
        printf("Applying production: A -> a\n");
        if (match('a')) {
            return 1;
        }}
    printf("Applying production: A -> e\n");
    return 1; // e (empty string)
}
int main() {
    // Print grammar
    printf("Grammar:\n");
    printf("S -> a A b\n");
    printf("A -> a | e\n\n");
    // Augmented grammar
    printf("Augmented Grammar:\n");
    printf("S' -> .S\n");
    printf("S  -> .a A b\n");
    printf("A  -> .a | e\n\n");
    // Input
    printf("Enter input string: ");
    scanf("%s", input);
    printf("\n--- Parsing Steps ---\n");
    if (S() && input[i] == '\0') {
        printf("\nString is Accepted!\n");
    } else {
        printf("\nString is Rejected!\n");
    }
    return 0;
}
