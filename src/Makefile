
# Makefile for GameOfLife
# Both with NCurses and without support for it.

CC=gcc
CCOPTS=-g -Wall -Werror -O2


all: gameOfLife

gameOfLife: gameOfLife-curses gameOfLife-nocurses
	ln -s gameOfLife-curses gameOfLife

gameOfLife-nocurses
	${CC} ${CCOPTS} gameOfLife.c -o gameOfLife-nocurses

gameOfLife-curses:
	${CC} ${CCOPTS} -lcurses -DNCURSES gameOfLife.c -o gameOfLife-curses

run-curses: gameOfLife-curses
	./gameOfLife-curses

run-nocurse: gameOfLife-nocurses
	./gameOfLife-nocurses

