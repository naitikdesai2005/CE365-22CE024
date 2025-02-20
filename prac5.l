%option noyywrap
%{
#include <stdio.h>
#include <string.h>
int line_no = 1;
%}

%%
[\t ]+  {}
"int"|"float"|"char"|"return"|"if"|"else"|"while"|"for"|"void"|"bool"|"long"|"break"|"continue"|"case"|"switch"|"default"|"double"|"sizeof"|"auto"|"signed"|"goto"|"enum"|"short"|"static"|"main" { printf("key-word: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("identifier: %s\n", yytext); }

[0-9]+   { printf("Constant: %s\n", yytext); }

[+\-*/=]  { printf("Operators: %s\n", yytext); }

[(){};,'"] {
printf("Special char: %s\n", yytext); }


"//".*  {}

"/*".*"*/"  {}

\n  { line_no++; }

.  { printf("Invalif token: %s\n", yytext); }
%%

int main()
{
    yyin = fopen("input1.c", "r");
    if (!yyin) {
        printf("Error opening file.\n");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}