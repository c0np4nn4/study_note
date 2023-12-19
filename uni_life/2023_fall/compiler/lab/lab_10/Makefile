all: table

y.tab.c: table.y
	bison -dy table.y

y.tab.h: table.y
	bison -dy table.y

table: lex.yy.c y.tab.c y.tab.h table.c table.h
	gcc lex.yy.c y.tab.c table.c -o table

lex.yy.c: table.l
	flex table.l

clean:
	rm -f table lex.yy.c y.tab.c y.tab.h table.zip

zip: Makefile table.l table.y table.c table.h README
	zip table.zip Makefile table.l table.y table.c table.h README

