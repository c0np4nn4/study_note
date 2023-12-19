%{
  #include <stdio.h>
  #include "table.h"

  int yylex();
  int yyerror(const char *s);
  Pair* table;
%}

%union {
  char *sval;
  int ival;
  duo pval;
}

%token <ival> NUM
%token <sval> ID '+' '-' '*' '/' '=' '\n' '(' ')'
%type <ival> Exp Term Factor

%%

Prg : Dec Prg
    | Exp { printf("(INT, %d)", $1); return 0;}
    ;

Dec : ID '=' Exp '\n' { entry(table, $1, (Data){.tag=TINT, .ival=$3}); }
    ;

Exp : Exp '+' Term { $$ = $1 + $3; }
    | Exp '-' Term { $$ = $1 - $3; }
    | Term { $$ = $1; }
    ;

Term  : Term '*' Factor { $$ = $1 * $3; }
      | Term '/' Factor { $$ = $1 / $3; }
      | Factor { $$ = $1; }
      ;

Factor  : '(' Exp ')' { $$ = $2; }
        | '-' Factor { $$ = -1 * $2; }
        | '+' Factor { $$ = $2; }
        | NUM { $$ = $1; }
        | ID { $$ = value(table, $1)->ival; }
        ;

%%

int main() {
  table = mkEnv();
  yyparse();
  return 0;
}

int yyerror(const char *msg) {fputs(msg, stderr);}
