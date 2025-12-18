#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 100

// List of keywords
char *keywords[] = {
    "int", "float", "if", "else", "while",
    "for", "return", "char", "double", "void"
};
int n_keywords = 10;

// Check keyword
int isKeyword(char *str) {
    for (int i = 0; i < n_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Identifier or Keyword
void identifier_or_keyword(char *str) {
    if (isKeyword(str))
        printf("Keyword\t\t%s\n", str);
    else
        printf("Identifier\t%s\n", str);
}

// Operator check
int isOperatorChar(char c) {
    char ops[] = "+-*/%=<>&|!^";
    return strchr(ops, c) != NULL;
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

        /* Identifier or Keyword */
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            identifier_or_keyword(buffer);
            ungetc(ch, fp);
        }

        /* Constant (Integer or Float) */
        else if (isdigit(ch)) {
            int isFloat = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF &&
                  (isdigit(ch) || ch == '.')) {
                if (ch == '.') isFloat = 1;
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            printf("Constant\t%s\n", buffer);
            ungetc(ch, fp);
        }

        /* String Literal */
        else if (ch == '"') {
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && ch != '"') {
                buffer[i++] = ch;
            }
            buffer[i++] = '"';
            buffer[i] = '\0';
            i = 0;
            printf("String\t\t%s\n", buffer);
        }

        /* Comments */
        else if (ch == '/') {
            char next = fgetc(fp);

            // Single-line comment
            if (next == '/') {
                buffer[i++] = '/';
                buffer[i++] = '/';
                while ((ch = fgetc(fp)) != EOF && ch != '\n') {
                    buffer[i++] = ch;
                }
                buffer[i] = '\0';
                i = 0;
                printf("Comment\t\t%s\n", buffer);
            }

            // Multi-line comment
            else if (next == '*') {
                buffer[i++] = '/';
                buffer[i++] = '*';
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    buffer[i++] = ch;
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                buffer[i] = '\0';
                i = 0;
                printf("Comment\t\t%s\n", buffer);
            }

            // Division operator
            else {
                printf("Operator\t/\n");
                ungetc(next, fp);
            }
        }

        /* Operators (including multi-character) */
        else if (isOperatorChar(ch)) {
            char next = fgetc(fp);
            if ((ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|')) {

                printf("Operator\t%c%c\n", ch, next);
            } else {
                printf("Operator\t%c\n", ch);
                ungetc(next, fp);
            }
        }

        /* Ignore whitespace */
        else if (isspace(ch)) {
            continue;
        }

        /* Symbols */
        else {
            printf("Symbol\t\t%c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
