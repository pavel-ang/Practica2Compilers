CC = gcc
CFLAGS = -Wall -Wextra -g

BISON = bison
FLEX = flex

all: calc

calc: calc.tab.o lex.yy.o symtab.o
	$(CC) -o calc calc.tab.o lex.yy.o symtab.o $(CFLAGS) -lm

calc.tab.c calc.tab.h: calc.y
	$(BISON) -d -o calc.tab.c calc.y

lex.yy.c: calc.l calc.tab.h
	$(FLEX) -o lex.yy.c calc.l

symtab.o: symtab.c symtab.h
	$(CC) -c symtab.c $(CFLAGS)

calc.tab.o: calc.tab.c symtab.h
	$(CC) -c calc.tab.c $(CFLAGS)

lex.yy.o: lex.yy.c symtab.h
	$(CC) -c lex.yy.c $(CFLAGS)

clean:
	rm -f calc *.o lex.yy.c calc.tab.c calc.tab.h calc.output

.PHONY: all clean
