%{
  #include <stdio.h>
  #include <stdlib.h>
%}
DIGIT [0-9]

%%
{DIGIT}+ {
   printf("An Integer: %s %d\n", yytext, atoi(yytext));
}
%%

int main() {  
  yylex();
}

int yywrap() {
  return 1;
}
