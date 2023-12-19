%{
  #include <stdlib.h>
  #include "table.h"
  #include "y.tab.h"
%}

%%

[0-9]+ { yylval.ival=atoi(yytext); return NUM; }
[ \t] ;
\+ return '+';
\- return '-';
\* return '*';
\/ return '/';
\( return '(';
\) return ')';
\= return '=';
\: return ':';
\; return ';';
\, return ',';
\n return '\n';

"let" { return LET; }
"u8"  { return U8; }
"str" { return STR; }
"println!" { return MACRO_println; }

[a-z]+ { yylval.sval = strdup(yytext); return ID; }
\"[^\"\n]*\" { yylval.sval = strdup(yytext + 1); yylval.sval[strlen(yylval.sval)-1] = 0; return STR_LITERAL; }


%%

int yywrap() { return 1; }
