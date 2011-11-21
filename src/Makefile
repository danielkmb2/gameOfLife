
# Makefile for GameOfLife
# Both with NCurses and without support for it.

CC=gcc
CCOPTS=-g -Wall -Werror -O2

EXE=gameOfLife-curses gameOfLife-nocurses
DSYM=gameOfLife-curses.dSYM gameOfLife-nocurses.dSYM

all: gameOfLife

gameOfLife: ${EXE}
	ln -s gameOfLife-curses gameOfLife

gameOfLife-nocurses: gameOfLife.c
	${CC} ${CCOPTS} gameOfLife.c -o gameOfLife-nocurses

gameOfLife-curses: gameOfLife.c
	${CC} ${CCOPTS} -lcurses -DNCURSES gameOfLife.c -o gameOfLife-curses

run-curses: gameOfLife-curses
	./gameOfLife-curses

run-nocurse: gameOfLife-nocurses
	./gameOfLife-nocurses

clean:
	rm ${EXE}
	rm gameOfLife
	rm -r ${DSYM}

