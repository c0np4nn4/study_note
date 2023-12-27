all: simple_rs

lex.yy.c: token.l
	flex token.l

y.tab.c: parser.y
	bison -dy parser.y

y.tab.h: parser.y
	bison -dy parser.y

simple_rs: lex.yy.c y.tab.c y.tab.h helper.c helper.h
	gcc lex.yy.c y.tab.c helper.c -o simple_rs

clean:
	rm -rf simple_rs lex.yy.c y.tab.c y.tab.h simple_rs.zip

zip: Makefile token.l parser.y helper.c helper.h README.txt
	zip -r simple_rs.zip Makefile token.l  parser.y helper.c helper.h README.txt example/

