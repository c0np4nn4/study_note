%{
#include <stdio.h>
#include <ctype.h>
#include "help.h"
int yyerror(const char *msg), yylex();
Node *Root;
%}

%union {
  char *sval;
  int   ival;
  Node *pval;
}

%token <ival> NUM
%token <sval> ID '+' '-' '*' '/'
%type  <pval> Exp Term Factor

%%

Prg   : Exp   { Root = $1; }
      ;

Exp   : Exp '+' Term { printf("[op] +\n"); $$ = mkBopNode("+", $1, $3); }
      | Exp '-' Term { printf("[op] -\n"); $$ = mkBopNode("-", $1, $3); }
      | Term          { $$ = $1; }
      ;

Term  : Term '*' Factor { printf("[op] *\n"); $$ = mkBopNode("*", $1, $3); }
      | Term '/' Factor { printf("[op] /\n"); $$ = mkBopNode("/", $1, $3); }
      | Factor          { $$ = $1; }
      ;

Factor: '(' Exp ')'    { $$ = $2; }
      | NUM            { $$ = mkIntNode($1); }
      | ID             { $$ = mkSymNode($1); }
      | '-' Factor     { $$ = mkUopNode($1, $2);}
      | '+' Factor     { $$ = mkUopNode($1, $2); }
      ;

%%

int main() {
  yyparse();
  printTree(Root, 0);
  return 0;
}

int yyerror(const char *msg) {
  fputs(msg, stderr);
  return -1;
}

