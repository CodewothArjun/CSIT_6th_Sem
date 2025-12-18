#include <stdio.h>
#include <string.h>

#define MAX 50

char stack[MAX];
char input[MAX];
int top = -1, ip = 0;

// Push to stack
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Pop n characters
void pop(int n) {
    top -= n;
    stack[top + 1] = '\0';
}

// Display stack and input
void display(char *action) {
    printf("%-15s %-15s %s\n", stack, input + ip, action);
}

// Try reductions
int reduce() {
    // E → a
    if (top >= 0 && stack[top] == 'a') {
        pop(1);
        push('E');
        display("Reduce E->a");
        return 1;
    }

    // E → E+E
    if (top >= 2 &&
        stack[top] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top - 2] == 'E') {
        pop(3);
        push('E');
        display("Reduce E->E+E");
        return 1;
    }

    // E → E*E
    if (top >= 2 &&
        stack[top] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top - 2] == 'E') {
        pop(3);
        push('E');
        display("Reduce E->E*E");
        return 1;
    }

    // E → (E)
    if (top >= 2 &&
        stack[top] == ')' &&
        stack[top - 1] == 'E' &&
        stack[top - 2] == '(') {
        pop(3);
        push('E');
        display("Reduce E->(E)");
        return 1;
    }

    return 0;
}

int main() {
    strcpy(input, "a+a*a$");

    printf("%-15s %-15s %s\n", "STACK", "INPUT", "ACTION");
    printf("-------------------------------------------\n");

    while (1) {
        // SHIFT
        if (input[ip] != '$') {
            push(input[ip++]);
            display("Shift");
        }

        // REDUCE as much as possible
        while (reduce());

        // ACCEPT condition
        if (input[ip] == '$' && strcmp(stack, "E") == 0) {
            printf("\nString Accepted \n");
            break;
        }
    }
    return 0;
}
