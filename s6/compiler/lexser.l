%option noyywrap
%option caseless
%{
#include "compiler.h"
#include "parser.tab.h"
#include <stdio.h>
int yyerror(char*);

%}

%%

"FUN"                      return FUN;
"argc"                     {
                                 yylval = (tnode*) malloc(sizeof(tnode));
                                 yylval->t = argument;
                                 return ARGC;
                           }
"if"                       return IF;
"else"                     return ELSE;
"read"                     return READ;
"write"                    return WRITE;
"return"                   return RETURN;
"<="                       return LE;
">="                       return GE;
"=="                       return EE;
"!="                       return NE;
">"                        return GT;
"<"                        return LT;
"+"                        return ADD;
"-"                        return SUB;
"*"                        return MULT;
"="                        return EQ;
[(){};]                    return *yytext;
[ \t\r\n]                  ;
[a-zA-z][0-9a-zA-Z]*       {
                                 yylval = lookup(yytext);
                                 return VAR;
                           }
[0-9]+                     {
                                 yylval = makeLeafNode(atoi(yytext));
                                 return NUM;
                           }
.                          {
                                 printf("%s\n", yytext);
                                 yyerror("Invalid token");
                                 exit(1);
                           }

%%
