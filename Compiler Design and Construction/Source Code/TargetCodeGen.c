#include <stdio.h>
#include <string.h>

int main() {
    char expr[50];
    printf("Enter an expression of the form a=b+c*d : ");
    scanf("%s", expr);

    char a, b, c, d;
    // assuming fixed format: a=b+c*d
    a = expr[0];
    b = expr[2];
    c = expr[4];
    d = expr[6];

    printf("\n--- Target Code Generation ---\n");

    printf("MOV R1, %c\n", c);   // R1 = c
    printf("MUL R1, %c\n", d);   // R1 = c * d
    printf("MOV R2, %c\n", b);   // R2 = b
    printf("ADD R2, R1\n");      // R2 = b + (c*d)
    printf("MOV %c, R2\n", a);   // a = result

    return 0;
}
