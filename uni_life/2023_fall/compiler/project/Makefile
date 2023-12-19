all: main

y.tab.c: parser.y
	bison -dy parser.y

y.tab.h: parser.y
	bison -dy parser.y

main: lex.yy.c y.tab.c y.tab.h table.c table.h
	gcc lex.yy.c y.tab.c table.c -o main

lex.yy.c: token.l
	flex token.l

clean:
	rm -rf main lex.yy.c y.tab.c y.tab.h table.zip

zip: Makefile token.l parser.y table.c table.h README
	zip table.zip Makefile token.l  parser.y table.c table.h README


