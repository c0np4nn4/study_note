all: main

y.tab.c: parser.y
	bison -dy parser.y -Wcounterexamples

y.tab.h: parser.y
	bison -dy parser.y

main: lex.yy.c y.tab.c y.tab.h ast.c ast.h
	gcc lex.yy.c y.tab.c ast.c -o main

lex.yy.c: token.l
	flex token.l

clean:
	rm -rf main lex.yy.c y.tab.c y.tab.h ast.zip

zip: Makefile token.l parser.y ast.c ast.h README
	zip ast.zip Makefile token.l  parser.y ast.c ast.h README


