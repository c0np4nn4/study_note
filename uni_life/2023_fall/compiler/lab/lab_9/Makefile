all: main

y.tab.c: ast.y
	bison -dy ast.y

y.tab.h: ast.y
	bison -dy ast.y

main: lex.yy.c y.tab.c y.tab.h ast.c ast.h
	gcc lex.yy.c y.tab.c ast.c -o main

lex.yy.c: token.l
	flex token.l

clean:
	rm -f main lex.yy.c y.tab.c y.tab.h main.zip

zip: Makefile token.l ast.y ast.c ast.h README
	zip main.zip Makefile token.l ast.y ast.c ast.h README

