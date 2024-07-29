%{
  #include <stdio.h>
  int word_cnt = 0;
  int symb_cnt = 0;
%}

word [a-zA-Z0-9']*
symbol [!@#$%^&*()-_+=|\\/<>,:;"'‘’~{}[\].]*
newline \n
whitespace [ \t]+

%%
{word} {
  ++word_cnt;
}

{symbol} {
  ++symb_cnt;
}

{newline} {
  printf("%d %d\n", word_cnt, symb_cnt);
  word_cnt = 0;
  symb_cnt = 0;
}

{whitespace} {
  // ignore
}

%%

int main() {
  yylex();
  return 0;
}

int yywrap() {
  return 1;
}
