%{
  #include <stdlib.h>
  #include "ast.h"
  #include "y.tab.h"
%}

%option yylineno

%%
[0-9]+ { yylval.ival=atoi(yytext); return NUM; }
[ \t\n] ;

"fn" { return FN; }
"let" { return LET; }
"u8"  { return TYPE_U8; }
"str" { return TYPE_STR; }
"println!" { return MACRO_PRINTLN; }
"main" { return MAIN; }

"("  { return L_PAREN; }
")"  { return R_PAREN; }
"->" { return ARROW; }
"{"  { return L_BRACE; }
"}"  { return R_BRACE; }
";"  { return SEMICOLON; }
":"  { return COLON; }
","  { return COMMA; }
"="  { return OP_ASSIGN; }
"+"  { return OP_ADD; }
"-"  { return OP_SUB; }
"*"  { return OP_MUL; }
"/"  { return OP_DIV; }

[a-z][a-z_]* { yylval.sval = strdup(yytext); return ID; }

\"[^\"\n]*\" { yylval.sval = strdup(yytext + 1); yylval.sval[strlen(yylval.sval)-1] = 0; return STR_LITERAL; }

. { printf("'%c': illegal character\n", yytext[0]); exit(-1); }


%%

int yywrap() { return 1; }
