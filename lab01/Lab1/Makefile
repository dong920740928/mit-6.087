CC = gcc
CFLAGS = -g -O0 -Wall

all : lab1a.o lab1b.o

lab1a.o : lab1a.c lifegame.c
	$(CC) $(CFLAGS) lab1a.c lifegame.c -o lab1a.o

lab1b.o : lab1b.c lifegame.c
	$(CC) $(CFLAGS) lab1b.c lifegame.c -o lab1b.o

clean:
	rm -f *.o
