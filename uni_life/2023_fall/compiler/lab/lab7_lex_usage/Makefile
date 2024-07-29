all: simple

simple: lex.yy.c
	gcc lex.yy.c -o simple

# lex.yy.c: test.l
# 	flex test.l
lex.yy.c: simple.l
	flex simple.l

clean:
	rm -f lex.yy.c simple simple.zip

test: simple simple.l
	./simple < simple.l

zip:
	zip simple.zip Makefile simple.l
