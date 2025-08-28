#include <stdio.h>
#include <string.h>

char input[50];        // input string
char stack[50];        // parsing stack
int top = -1;          // stack pointer
int i = 0;             // input pointer

// Push function
void push(char c) {
    stack[++top] = c;
    stack[top+1] = '\0';
}

// Pop function
void pop() {
    stack[top] = '\0';
    top--;
}

// Try reductions
void check() {
    // E -> a
    if (stack[top] == 'a') {
        pop();
        push('E');
        printf("\t\t\t\tReduce E->a\n");
    }

    // E -> (E)
    if (top >= 2 && stack[top] == ')' && stack[top-2] == '(' && stack[top-1] == 'E') {
        pop(); pop(); pop(); // remove ( E )
        push('E');
        printf("\t\t\t\tReduce E->(E)\n");
    }

    // E -> E+E
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        printf("\t\t\t\tReduce E->E+E\n");
    }

    // E -> E*E
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        printf("\t\t\t\tReduce E->E*E\n");
    }
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nSHIFT-REDUCE PARSING STEPS\n");
    printf("-------------------------------------------\n");
    printf("Stack\t\tInput\t\tAction\n");
    printf("-------------------------------------------\n");

    while (input[i] != '\0') {
        // Shift
        push(input[i]);
        printf("%s\t\t%s\t\tShift\n", stack, input+i+1);
        i++;

        // Try reductions
        check();
    }

    // Final check
    while (top > 0) {
        check();
    }

    if (strcmp(stack, "E") == 0) {
        printf("\nString accepted!\n");
    } else {
        printf("\nString rejected!\n");
    }

    return 0;
}
