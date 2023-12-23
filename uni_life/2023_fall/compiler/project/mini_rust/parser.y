%{

  #include <stdio.h>
  #include "ast.h"

  int yylex();
  int yyerror(const char *s);

  extern int yylineno;

  Pair* symbol_table;
  Pair* fn_table;

%}

%union {
  char *sval;
  int ival;
}

%token FN L_PAREN R_PAREN L_BRACE R_BRACE MAIN
%token LET TYPE_U8 TYPE_STR
%token MACRO_PRINTLN ARROW SEMICOLON COLON COMMA
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_ASSIGN

%token <ival> NUM
%token <sval> ID STR_LITERAL
%type <ival> Param Expr Term Factor


%%

S : Pgm 
  ;

Pgm : Fn_decl Pgm
    | Fn_main { return 0; }
    ;

Fn_main : FN MAIN L_PAREN R_PAREN L_BRACE Body R_BRACE        
        ;

Fn_decl : FN ID L_PAREN TYPES ARROW TYPES R_PAREN L_BRACE Body R_BRACE { 
          }
        ;

Fn_call : ID L_PAREN Params R_PAREN
        ;

Body  : Stmt SEMICOLON Body  
      | Stmt SEMICOLON
      ;

Stmt : Stmt_Assign
     | Fn_call 
     | Macro_println
     |
     ;

Macro_println : MACRO_PRINTLN L_PAREN STR_LITERAL R_PAREN { printf("%s\n", $3); return 0;}
              | MACRO_PRINTLN L_PAREN STR_LITERAL COMMA ID R_PAREN {
                    Data* data = value(symbol_table, $5);
                    char* formatted_string = replace_format_specifier($3, data);
                    printf("%s\n", formatted_string); 
                }
              ;

TYPES : TYPE_U8 TYPES
      | TYPE_STR TYPES
      | COMMA TYPES
      |
      ;

Params : Param COMMA Params
       | Param
       |
       ;

Param : Expr { $$ = $1; }
      ;

Stmt_Assign : LET ID COLON TYPE_U8 OP_ASSIGN Expr { 
                printf("ID: %d\n", $6);
                entry(symbol_table, $2, (Data){.tag=TINT, .ival=$6}); 
              }
            | LET ID COLON TYPE_STR OP_ASSIGN STR_LITERAL { 
                entry(symbol_table, $2, (Data){.tag=TSTR, .sval=$6}); 
              }
            | LET ID COLON TYPE_U8 OP_ASSIGN ID { 
                printf("ID: %s\n", $6);
                entry(symbol_table, $2, (Data){.tag=TINT, .ival=value(symbol_table, $6)->ival}); 
              }
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
        | ID { $$ = value(symbol_table, $1)->ival; }
        ;

%%

int main() {
  symbol_table = mkEnv();
  fn_table = mkEnv();

  yyparse();
  return 0;
}

int yyerror(const char *s) {
  fprintf(stderr, "Error: %s at line %d. Unexpected token: \n", s, yylineno);
  return 0;
}

