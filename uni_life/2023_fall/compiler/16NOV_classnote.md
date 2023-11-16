yacc (bison) 이용

- expr.y
```y
%{
#include <stdio.h>
#include <ctype.h>
int yylex();
void yyerror(const char* s);
%}

%token NUM

%%

EXP	: EXP '+' NUM 	{ puts("E -> E + N"); }
	| NUM		{ puts("E -> N"); }
	;

%%

int main() { yyparse(); return 0;}
void yyerror(const char *msg) { fputs(msg, stderr); }
int yylex() {
	char c = getchar();
	return c == ' ' ? yylex() : (c == '\n') ? 0 : isdigit(c) ? NUM : c;
}
```

- yacc, compile
```bash
bison -dy expr.y
gcc y.tab.c
a.exe
```
- ambiguous grammar 는 conflict 가 일어난다.
