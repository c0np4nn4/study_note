%{
  #include <stdio.h>
  #include <string.h>
  #include "helper.h"

  int yylex();
  int yyerror(const char *s);

  extern int yylineno;

  Pair* symbol_table;
  Pair* fn_table;

  extern FILE* yyin;
%}

%union {
  char *sval;
  signed int ival;
}

%token L_PAREN R_PAREN L_BRACE R_BRACE ARROW SEMICOLON COLON COMMA DOUBLE_QUOTE
%token MACRO_PRINTLN FN LET TYPE_I32 TYPE_STR MAIN  
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_ASSIGN

%token <ival> NUM
%token <sval> ID STR_LITERAL

%type <ival> Param Expr Term Factor
%type <sval> Formatted_string

%start Pgm


%%

Pgm : Fn_decl Pgm
    | Fn_main { return 0; }
    ;

Fn_main : FN MAIN L_PAREN R_PAREN L_BRACE Body R_BRACE        
        ;

Fn_decl : FN ID L_PAREN TYPES ARROW TYPES R_PAREN L_BRACE Body R_BRACE 
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

Macro_println : MACRO_PRINTLN L_PAREN Formatted_string R_PAREN {
                  printf("%s\n", $3);
                }
              ;

Formatted_string : Formatted_string COMMA ID {
                    Data* data = value(symbol_table, $3);
                    char* formatted_string = replace_format_specifier($1, data);
                    $$ = formatted_string;
                   }
                | Formatted_string COMMA Expr {
                    Data* data = (Data*)malloc(sizeof(Data));
                    data->tag=TINT;
                    data->ival=$3;

                    char* formatted_string = replace_format_specifier($1, data);
                    $$ = formatted_string;
                  }
                  
                | Formatted_string COMMA STR_LITERAL {
                    Data* data = (Data*)malloc(sizeof(Data));
                    data->tag=TSTR;
                    data->sval=$3;

                    char* formatted_string = replace_format_specifier($1, data);
                    $$ = formatted_string;
                   }
                 | STR_LITERAL { $$ = replace_escapes($1); }
                 | { $$ = ""; }
                 ;

TYPES : TYPE_I32 
      | TYPE_STR
      | TYPE_I32 COMMA TYPES
      | TYPE_STR COMMA TYPES
      ;

Params : Param COMMA Params
       | Param
       |
       ;

Param : Expr { $$ = $1; }
      ;

Stmt_Assign : LET ID COLON TYPE_I32 OP_ASSIGN Expr { 
                entry(symbol_table, $2, (Data){.tag=TINT, .ival=$6}); 
              }
            | LET ID COLON TYPE_STR OP_ASSIGN STR_LITERAL { 
                entry(symbol_table, $2, (Data){.tag=TSTR, .sval=$6}); 
              }
            | LET ID COLON TYPE_I32 OP_ASSIGN ID { 
                Data* data = value(symbol_table, $6);
                transfer_ownership(symbol_table, $2, $6, data);
              }
            | LET ID COLON TYPE_STR OP_ASSIGN ID { 
                Data* data = value(symbol_table, $6);
                transfer_ownership(symbol_table, $2, $6, data);
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

Factor  : L_PAREN Expr R_PAREN { $$ = $2; }
        | OP_SUB Factor { $$ = -1 * $2; }
        | OP_ADD Factor { $$ = +1 * $2; }
        | NUM { $$ = $1; }
        | ID { $$ = value(symbol_table, $1)->ival; }
        ;

%%

int main(int argc, char *argv[]) {
  // 환경 생성
  symbol_table = mkEnv();
  fn_table = mkEnv();

  // 인자 확인
  if (argc < 2) {
    fprintf(stderr, "사용법: %s <filename.srs>\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];
  char *ext = strrchr(filename, '.');

  // 확장자가 .srs인지 확인
  if (ext == NULL || strcmp(ext, ".srs") != 0) {
    fprintf(stderr, "Error: '.srs' 확장자를 가진 파일만 처리 가능합니다.\n");
    return 1;
  }

  // 파일 열기
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "파일 '%s'를 열 수 없습니다.\n", filename);
    return 1;
  }

  // Bison의 파서에 파일 스트림을 설정
  yyin = file;

  // 파싱 시작
  yyparse();

  // 파일 닫기
  fclose(file);

  return 0;
}

int yyerror(const char *s) {
  fprintf(stderr, "Error: %s at line %d. Unexpected token: \n", s, yylineno);
  return 0;
}

