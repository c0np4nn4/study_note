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

%token LET U8 STR
%token MACRO_println
%token <sval> ID
%token <sval> STR_LITERAL
%token '+' '-' '*' '/' '=' '\n' '(' ')' ':' '!' ','
%token <ival> NUM
%type <ival> Exp Term Factor

%%

Prg : Dec Prg
    | MACRO_println '(' STR_LITERAL ')' ';' '\n' { printf("%s\n", $3); return 0;}
    | MACRO_println '(' STR_LITERAL ',' ID ')' ';' '\n' { 
        Data* data = value(table, $5);
        if (data != NULL) {
          char* formatted_string = replace_format_specifier($3, data);
          printf("%s\n", formatted_string); 
          free(formatted_string); 
        }
        return 0;
      }
    ;

Dec : LET ID ':' U8 '=' Exp ';' '\n' { entry(table, $2, (Data){.tag=TINT, .ival=$6}); }
    | LET ID ':' STR '=' STR_LITERAL ';' '\n' { entry(table, $2, (Data){.tag=TSTR, .sval=$6}); }
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
  while (1) {
    yyparse();
    puts("\n");
  }
  return 0;
}

int yyerror(const char *msg) {fputs(msg, stderr);}

