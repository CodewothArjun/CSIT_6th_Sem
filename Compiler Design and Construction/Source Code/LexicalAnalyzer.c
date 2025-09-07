#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LEN 100
// List of keywords
char *keywords[] = {
    "int", "float", "if", "else", "while", "for", "return", "char", "double", "void"
};
int n_keywords = 10;

// Function to check if a string is keyword
int isKeyword(char *str) {
    for (int i = 0; i < n_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}
// Function to recognize identifiers and keywords
void identifier_or_keyword(char *str) {
    if (isKeyword(str))
        printf("Keyword\t\t%s\n", str);
    else
        printf("Identifier\t%s\n", str);
}

// Function to recognize operators
int isOperator(char c) {
    char operators[] = "+-*/%=<>&|!^";
    for (int i = 0; operators[i]; i++) {
        if (c == operators[i]) return 1;
    }
    return 0;
}

int main() {
	
    FILE *fp;
    char ch, buffer[MAX_LEN];
    int i = 0;

    fp = fopen("lexicalAnalyzer.txt", "r");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            identifier_or_keyword(buffer);
            ungetc(ch, fp);
        }
        // Number (constant)
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            printf("Constant\t%s\n", buffer);
            ungetc(ch, fp);
        }
        // String literal
        else if (ch == '"') {
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != '"' && ch != EOF) {
                buffer[i++] = ch;
            }
            buffer[i++] = '"';
            buffer[i] = '\0';
            i = 0;
            printf("String\t\t%s\n", buffer);
        }
        // Comment (single-line // or multi-line /* */)
        else if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                // single-line
                buffer[i++] = '/';
                buffer[i++] = '/';
                while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
                    buffer[i++] = ch;
                }
                buffer[i] = '\0';
                i = 0;
                printf("Comment\t\t%s\n", buffer);
            } else if (next == '*') {
                // multi-line
                buffer[i++] = '/';
                buffer[i++] = '*';
                while ((ch = fgetc(fp)) != EOF) {
                    buffer[i++] = ch;
                    if (ch == '*' && (ch = fgetc(fp)) == '/') {
                        buffer[i++] = '/';
                        break;
                    } else {
                        ungetc(ch, fp);
                    }
                }
                buffer[i] = '\0';
                i = 0;
                printf("Comment\t\t%s\n", buffer);
            } else {
                printf("Operator\t/\n");
                ungetc(next, fp);
            }
        }
        // Operators
        else if (isOperator(ch)) {
            printf("Operator\t%c\n", ch);
        }
        // Ignore whitespace
        else if (isspace(ch)) {
            continue;
        }
        // Other symbols (punctuation)
        else {
            printf("Symbol\t\t%c\n", ch);
        }
    }
    fclose(fp);
    return 0;
}
