%{
  #include <stdlib.h>
  #include "helper.h"
  #include "y.tab.h"
%}

%option yylineno
%x COMMENT
%x CPPCOMMENT

%%
[0-9]+ { yylval.ival=atoi(yytext); return NUM; }
[ \t\n] ;

"fn" { return FN; }
"let" { return LET; }
"i32"  { return TYPE_I32; }
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
\"

[a-z][a-z_0-9]* { yylval.sval = strdup(yytext); return ID; }
\"[^\"\n]*\" { yylval.sval = strdup(yytext + 1); yylval.sval[strlen(yylval.sval)-1] = 0; return STR_LITERAL; }
. { printf("'%c': illegal character\n", yytext[0]); exit(-1); }

"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>.      { /* ignore */ }
<COMMENT>\n     { /* ignore */ }
<COMMENT>\r\n   { /* ignore */ }

"//"            { BEGIN(CPPCOMMENT); }
<CPPCOMMENT>\n  { BEGIN(INITIAL); }
<CPPCOMMENT>.   { /* ignore */ }
<CPPCOMMENT>\r\n { BEGIN(INITIAL); }

%%

int yywrap() { return 1; }
