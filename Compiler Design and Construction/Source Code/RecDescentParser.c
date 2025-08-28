#include <stdio.h>
#include <string.h>

char input[100];   // input string
int pos = 0;       // current position in input
int length;        // length of input

// Function declarations
int S();
int A();

// Function to match a character
int match(char expected) {
    if (pos < length && input[pos] == expected) {
        pos++;
        return 1; // success
    }
    return 0; // failure
}

// Grammar rule: S → a A b
int S() {
    int start = pos;
    if (match('a')) {
        if (A()) {
            if (match('b')) {
                return 1; // success
            }
        }
    }
    pos = start; // backtrack
    return 0;
}

// Grammar rule: A → a | ε
int A() {
    int start = pos;
    if (match('a')) {
        return 1; // matched 'a'
    }
    // ε (empty string) is always valid
    return 1;
}

int main() {
    printf("Enter a string: ");
    scanf("%s", input);

    length = strlen(input);

    if (S() && pos == length) {
        printf("String is accepted by the grammar.\n");
    } else {
        printf("String is rejected by the grammar.\n");
    }

    return 0;
}
