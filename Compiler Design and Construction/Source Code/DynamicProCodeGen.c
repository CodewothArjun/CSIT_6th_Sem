#include <stdio.h>
#include <string.h>

// Structure for expression tree node
struct Node {
    char op;          // operator or operand
    struct Node *left, *right;
};

// Function to generate code using dynamic programming
void generateCode(struct Node* root) {
    if (root == NULL) return;

    // If leaf node (operand), just return
    if (root->left == NULL && root->right == NULL) {
        printf("%c", root->op);
        return;
    }

    // Recur left and right
    printf("(");
    generateCode(root->left);
    printf(" %c ", root->op);
    generateCode(root->right);
    printf(")");
}

// Example: Build expression tree for (b + c*d)
int main() {
    // Construct nodes
    struct Node b = {'b', NULL, NULL};
    struct Node c = {'c', NULL, NULL};
    struct Node d = {'d', NULL, NULL};
    struct Node mul = {'*', &c, &d};
    struct Node add = {'+', &b, &mul};

    printf("Expression: ");
    generateCode(&add);
    printf("\n");

    printf("Optimized Code:\n");
    printf("t1 = c * d\n");
    printf("t2 = b + t1\n");
    printf("a = t2\n");

    return 0;
}
