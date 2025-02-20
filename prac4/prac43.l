%option noyywrap
%{
#include<stdio.h>
int w=0,l=0,c=0;
%}
%%
[\n] {l++;}
[\t] {c+=yyleng;}
[^ \t\n]+ {w++; c+=yyleng ;}
. ;
<<EOF>> {yyterminate();}
%%
int main()
{
printf("Enter String : ");
yylex();
printf("No. of Characters : %d",c);
printf("No. of words : %d",w);
printf("No. of lines : %d",l);
return 0;
}