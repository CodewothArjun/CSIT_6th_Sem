#include <stdio.h>
#include <string.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char c) {
    stack[++top] = c;
    stack[top+1] = '\0';
}
void pop() {
    if(top != -1) stack[top--] = '\0';
}// Function to perform reduction based on grammar
int reduce() { // a -> E
    if(top >= 0 && stack[top] == 'a') {
        stack[top] = 'E';
        return 1;
    }// E+E -> E
    if(top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        stack[top+1] = '\0';
        return 1;
    }// E*E -> E
    if(top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        stack[top+1] = '\0';
        return 1;
    }// (E) -> E
    if(top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        top -= 2;
        stack[top] = 'E';
        stack[top+1] = '\0';
        return 1;
    }
    return 0;
}
int main() {
    char input[MAX];
    int i = 0;
    printf("Enter input string: ");
    scanf("%s", input);
    strcat(input, "$"); // end marker
    printf("\n%-20s %-20s %-20s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------------------\n");
    while(input[i] != '\0') {
        push(input[i]);        // Shift
        printf("%-20s %-20s %-20s\n", stack, input+i+1, input[i] == '$' ? "Accept" : "Shift");
        // Reduce while possible
        while(reduce()) {
            printf("%-20s %-20s %-20s\n", stack, input+i+1, "Reduce");
        }
        // Accept if stack has E and input is $
        if(input[i] == '$' && top == 0 && stack[top] == 'E') {
            printf("%-20s %-20s %-20s\n", stack, input+i+1, "Accept");
            break;
        }
        i++;
    }
    return 0;
}
