# Makefile: TicTacWhoa
# 03/09/21 TH Inital creation

# variable definitions
CC = gcc
DEBUG = -g DDEBUG
CFLAGS = -Wall -ansi -std=c99 -c
LFLAGS = -Wall

# convenience targets
all: TicTacWhoa

clean:
	rm -f TicTacWhoa
	rm -f *.o
	rm -f libai.a	

test:
	valgrind ./TicTacWhoa

# compilation rules for TicTacWhoa
game.o: game.c game.h
	$(CC) $(CFLAGS) game.c -o game.o
inky.o: inky.c AI.h
	$(CC) $(CFLAGS) inky.c -o inky.o
blinky.o: blinky.c AI.h
	$(CC) $(CFLAGS) blinky.c -o blinky.o
pinky.o: pinky.c AI.h
	$(CC) $(CFLAGS) pinky.c -o pinky.o
settings.o: settings.c settings.h
	$(CC) $(CFLAGS) settings.c -o settings.o
#board.o: board.c board.h
#	$(CC) $(CFLAGS) board.c -o board.o
#boardList.o: boardList.c boardList.h board.h
#	$(CC) $(CFLAGS) boardList.c -o boardList.o
libai: inky.o blinky.o pinky.o
	ar rc libai.a inky.o blinky.o pinky.o
	ranlib libai.a
TicTacWhoa.o: TicTacWhoa.c
	$(CC) $(CFLAGS) TicTacWhoa.c -o TicTacWhoa.o

# Generate executable
TicTacWhoa: game.o settings.o libai TicTacWhoa.o
	$(CC) $(LFLAGS) game.o settings.o TicTacWhoa.o -L. -lai -lm -o TicTacWhoa
