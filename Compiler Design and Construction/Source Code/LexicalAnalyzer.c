#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[8][10] = {"int","float","if","else","while","for","return","char"};

int isKeyword(char *str) {
    for(int i=0;i<8;i++) {
        if(strcmp(str, keywords[i])==0)
            return 1;
    }
    return 0;
}

int main() {
    char src[200];
    printf("Enter source code:\n");
    fgets(src,200,stdin);

    int i=0;
    while(src[i]!='\0') {
        if(isalpha(src[i])) { // identifier or keyword
            char buf[50]; int j=0;
            while(isalnum(src[i])) {
                buf[j++]=src[i++];
            }
            buf[j]='\0';
            if(isKeyword(buf))
                printf("<Keyword, %s>\n", buf);
            else
                printf("<Identifier, %s>\n", buf);
        }
        else if(isdigit(src[i])) { // number
            char buf[50]; int j=0;
            while(isdigit(src[i])) {
                buf[j++]=src[i++];
            }
            buf[j]='\0';
            printf("<Constant, %s>\n", buf);
        }
        else if(src[i]=='"') { // string literal
            char buf[100]; int j=0;
            buf[j++]='"'; i++;
            while(src[i]!='"' && src[i]!='\0') {
                buf[j++]=src[i++];
            }
            if(src[i]=='"') buf[j++]='"';
            buf[j]='\0'; i++;
            printf("<String, %s>\n", buf);
        }
        else if(src[i]=='/' && src[i+1]=='/') { // single-line comment
            while(src[i]!='\n' && src[i]!='\0') i++;
        }
        else if(strchr("+-*/=;(){}",src[i])) { // operators/symbols
            printf("<Operator, %c>\n", src[i]);
            i++;
        }
        else i++; // skip spaces, tabs, etc.
    }
    return 0;
}
