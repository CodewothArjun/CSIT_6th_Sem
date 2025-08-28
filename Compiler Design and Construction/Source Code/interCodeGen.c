#include <stdio.h>
#include <string.h>

int main() {
    char expr[100];
    char op1, op2, op3;
    int tempCount = 1;

    printf("Enter the expression (example: a=b+c*d): ");
    scanf("%s", expr);

    // For simplicity, assuming expression in form: a=b+c*d
    op1 = expr[2];  // c
    op2 = expr[4];  // d
    op3 = expr[6];  // (operator after c)

    // Detect operator precedence (* before +)
    if (expr[4] == '+' || expr[4] == '-') {
        // Handle only + or - first
        printf("t%d = %c %c %c\n", tempCount, expr[2], expr[4], expr[3]);
        printf("%c = t%d\n", expr[0], tempCount);
    } else {
        // Multiplication/division first
        printf("t%d = %c %c %c\n", tempCount, expr[4], expr[5], expr[6]);
        printf("t%d = %c %c t%d\n", tempCount + 1, expr[2], expr[3], tempCount);
        printf("%c = t%d\n", expr[0], tempCount + 1);
    }

    return 0;
}
