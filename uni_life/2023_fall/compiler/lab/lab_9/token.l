%{
  #include <stdlib.h>
  #include <string.h>
  #include "ast.h"
  #include "y.tab.h"
%}

%%

[0-9]+ {yylval.ival = atoi(yytext); return (NUM);}
[a-zA-Z]+ {yylval.sval = strdup(yytext); return(ID);}
[ \t] ;

\( {yylval.sval = strdup(yytext); return('(');}
\) {yylval.sval = strdup(yytext); return(')');}
\+ {yylval.sval = strdup(yytext); return('+');}
\- {yylval.sval = strdup(yytext); return('-');}
\* {yylval.sval = strdup(yytext); return('*');}
\/ {yylval.sval = strdup(yytext); return('/');}
\n return(0);
. { printf("'%c': illegal character\n", yytext[0]); exit(-1); }

%%

int yywrap() { return 1; }

