%{
  #include <stdio.h>
  #include "ast.h"

  int yylex();
  int yyerror(const char *s);

  extern int yylineno;
%}

%union {
  char *sval;
  int ival;
}

%token NEWLINE FN L_PAREN R_PAREN L_BRACE R_BRACE MAIN
%token LET TYPE_U8 TYPE_STR
%token MACRO_PRINTLN ARROW SEMICOLON COLON COMMA
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_ASSIGN
%token STR_LITERAL

%token <ival> NUM
%token <sval> ID
%type <ival> Param Expr Term Factor


%%
PGM : FN_MAIN 
    ;

FN_MAIN : FN MAIN L_PAREN R_PAREN L_BRACE BODY R_BRACE        
        ;

BODY  : Stmt SEMICOLON BODY  
      |
      ;

Stmt : Stmt_Assign
     | Fn_call 
     ;

Fn_call : ID L_PAREN Params R_PAREN
        ;

Params : Param COMMA Params
       | Param
       |
       ;

Param : Expr { $$ = $1; }
      ;

Stmt_Assign : ID OP_ASSIGN Expr
            ;

Expr  : Expr OP_ADD Term { $$ = $1 + $3; }
      | Expr OP_SUB Term { $$ = $1 - $3; }
      | Term { $$ = $1; }
      ; 

Term  : Term OP_MUL Factor  { $$ = $1 * $3; }
      | Term OP_DIV Factor { $$ = $1 / $3; }
      | Factor { $$ = $1; }
      ;

Factor  : L_BRACE Expr R_BRACE { $$ = $2; }
        | OP_SUB Factor { $$ = -1 * $2; }
        | OP_ADD Factor { $$ = +1 * $2; }
        | NUM { $$ = $1; }
        | ID { $$ = 100; }
        ;

%%

int main() {
  yyparse();
  return 0;
}

int yyerror(const char *s) {
  fprintf(stderr, "Error: %s at line %d. Unexpected token: \n", s, yylineno);
  return 0;
}

