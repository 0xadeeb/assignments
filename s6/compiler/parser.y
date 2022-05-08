%{
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char*);
extern FILE *yyin;
int count = 0;
%}

%token NUM
%token EQ
%token FUN
%token IF
%token ELSE
%token READ
%token WRITE
%token VAR
%token RETURN
%token ARGC
%nonassoc GE LE EE NE GT LT
%left ADD SUB
%left MULT

%%

Program:        READ '(' ARGC ')' ';' ARGC EQ FUN '(' ARGC ')' '{' Stmts '}' WRITE '(' ARGC ')' ';'
                {
                        generateCode($13);
                }
        ;

Stmts:          Stmt Stmts {$$ = connectNodes($1, $2);}
        |       Stmt {$$ = $1;}
        ;

Stmt:           AsgStmt {$$ = $1;}
        |       IfStmt {$$ = $1;}
        |       IfElseStmt {$$ = $1;}
        |       RetStmt {$$ = $1;}
        ;

AsgStmt:        varr EQ E ';'  {$$ = makeOpNode(EQ, $1, $3);}
        ;

varr:           VAR {$$ = $1;}
        |       ARGC {$$ = $1;}
        ;

IfStmt:         IF '(' E ')' '{' Stmts '}' {$$ = makeIfNode(IF, $6, $3, NULL);}
        ;

IfElseStmt:     IF '(' E ')' '{' Stmts '}' ELSE '{' Stmts '}' {$$ = makeIfNode(IF, $6, $3, $10);}
        ;

RetStmt:        RETURN E ';' {$$ = makeOpNode(RETURN, $2, NULL);}
        ;

E:              E MULT E {$$ = makeOpNode(MULT, $1, $3);}
        |       E ADD E {$$ = makeOpNode(ADD, $1, $3);}
        |       E SUB E {$$ = makeOpNode(SUB, $1, $3);}
        |       E GE E {$$ = makeOpNode(GE, $1, $3);}
        |       E GT E {$$ = makeOpNode(GT, $1, $3);}
        |       E LT E {$$ = makeOpNode(LT, $1, $3);}
        |       E LE E {$$ = makeOpNode(LE, $1, $3);}
        |       E EE E {$$ = makeOpNode(EE, $1, $3);}
        |       E NE E {$$ = makeOpNode(NE, $1, $3);}
        |       '(' E ')' {$$ = $2;}
        |       varr {$$ = $1;}
        |       NUM {$$ = $1;}
        |       FUN '(' E ')' {$$ = makeOpNode(FUN, $3, NULL);}
        ;

%%

int yyerror(char *s) {
        printf("Error: %s\n", s);
        return 1;
}

int main(int argc, char** argv) {
        yyin = fopen(argv[1], "r");
        yyparse();
        return 0;
 }
