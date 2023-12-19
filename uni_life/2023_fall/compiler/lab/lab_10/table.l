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
\n return '\n';
[a-z]+ { yylval.sval = strdup(yytext); return ID; }
%%

int yywrap() { return 1; }
