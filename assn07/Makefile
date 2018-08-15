CC = gcc
CFLAGS = -g -Wall -lsqlite3

all: prob1 prob1b

prob1: prob1.c
	$(CC) -o prob1 prob1.c $(CFLAGS)

prob1b: prob1b.c
	$(CC) -o prob1b prob1b.c $(CFLAGS)

clean:
	rm -f *.o prob1 prob1b
